//Warning: rushed & bad

#include <PR/gbi.h>
#include "actors/group0.h"
#include "include/behavior_data.h"
#include "include/macros.h"
#include "include/sm64.h"
#include "include/types.h"
#include "src/engine/graph_node.h"
#include "src/engine/math_util.h"
#include "src/engine/surface_collision.h"
#include "bullet_system.h"
#include "camera.h"
#include "mario_actions_object.h"
#include "object_list_processor.h"
#include "tile_scroll.h"
#include "game_init.h"
#include "level_update.h"
#include "levels/i/hoodmonger_bullet/geo_header.h"
extern Gfx fbullet_Cube_mesh[];
extern Gfx bowser_f_bullet_Cube_mesh[];

#include "ge_translation.h"
#include "levels/B/turret_bullet/geo_header.h"

#include "levels/k/header.h"
#include "levels/bowser_course/header.h"

//--MISC
extern u32 sForwardKnockbackActions[][3];
extern u32 sBackwardKnockbackActions[][3];





//-- * Data *


#define BULLET_MAX  40

static struct Bullet sBulletList[BULLET_MAX] = { 0 };
static void (*sBulletParamFn)(struct Bullet *b) = NULL;
static u8   sBulletCount   = 0;
static Gfx *sBulletMat     = NULL;
static Gfx *sBulletMesh    = NULL;




//-- * Spawn *

static void bullet_default_params(struct Bullet *b) {
	b->velF          = 0.f;
	b->gravity       = 0.f;
	b->hitSphereSize = 0.f;
	b->damage        = 0;
}
static void bullet_b_params(struct Bullet *b) {
	b->velF          = 100.f;
	b->gravity       = 0.f;
	b->hitSphereSize = 100.f;
	b->damage        = 1;
}
static void bullet_f_params(struct Bullet *b) {
	b->velF          = 65.f;
	b->gravity       = 0.f;
	b->hitSphereSize = 60.f;
	b->damage        = 2;
}
static void bullet_k_params(struct Bullet *b) {
	b->velF          = 100.f;
	b->gravity       = 0.f;
	b->hitSphereSize = 100.f;
	b->damage        = 4;
}

void dobj_spawn_bullet(Vec3f pos, s16 rX, s16 rY) {
	if (sBulletCount == BULLET_MAX) { return NULL; }

	struct Bullet *b = sBulletList;
	while (b->flags & BULLET_FLAG_ACTIVE) {
		b++; }
	sBulletCount++;

	b->flags = BULLET_FLAG_ACTIVE;
	b->timer =  0;
	vec3f_copy(b->pos, pos);

	(*sBulletParamFn)(b);

	b->velY = (sins(rX) * b->velF);
	b->yaw  = rY;
}





//--process
#define DELETE_BULLET()                                   \
    struct Object *particle = spawn_object                \
		(gMarioObject, MODEL_MIST, bhvWhitePuffExplosion);\
	vec3f_copy(&particle->oPosX, b->pos);                 \
    particle->oBehParams2ndByte = 2;                      \
    particle->oVelY = 7.f;                                \
	Vec3f scale = { 2.f, 2.f, 2.f };                      \
	vec3f_copy(particle->header.gfx.scale, scale);        \
	sBulletCount--;                                       \
	b->flags = BULLET_FLAG_NONE;                          \
	continue;                        


//-- * Main *
Gfx *dobj_bullets(s32 callContext) {
	switch (callContext) {
	case GEO_CONTEXT_CREATE:
		switch (gCurrLevelNum) {
		
		case LEVEL_B:
			sBulletParamFn = bullet_b_params;
			sBulletMat     = mat_turret_bullet_f3dlite_material_layer7;
			sBulletMesh    = turret_bullet_turret_bullet_mesh_layer_7_tri_0;
			break;
		
		case LEVEL_F:
			sBulletParamFn = bullet_f_params;
			sBulletMat     = mat_e_sg_piece_mat_f3d_layer1;
			sBulletMesh    = fbullet_Cube_mesh;
			break;

		case LEVEL_BOWSER_COURSE:
			sBulletParamFn = bullet_f_params;
			sBulletMat     = mat_e_sg_piece_mat_f3d_layer1;
			sBulletMesh    = bowser_f_bullet_Cube_mesh;
			break;
		
		case LEVEL_K:
			sBulletParamFn = bullet_k_params;
			sBulletMat     = mat_e_sg_piece_mat_f3d_layer1;
			sBulletMesh    = kbul_kbul_mesh;
			break;
		
		//default DL and params, basically just to prevent crashes in case someone forgets to set their DLs,\
		  or if bullets are spawned in a level that wasn't planned to have bullets
		default:
			sBulletParamFn = bullet_default_params;
			sBulletMat     = mat_e_sg_piece_mat_f3d_layer1;
			sBulletMesh    = e_sg_piece_piece_mesh_tri_0;
		}
		break;


	case GEO_CONTEXT_AREA_LOAD:
		bzero(sBulletList, (BULLET_MAX * sizeof(struct Bullet)));
	    break;


	case GEO_CONTEXT_RENDER:
	  {
		s32 update = ((!((gTimeStopState & TIME_STOP_ACTIVE)
						|| (gCameraMovementFlags & CAM_MOVE_PAUSE_SCREEN)))
						&& ability_chronos_frame_can_progress());

		//allocate DL
		Gfx *dlS = alloc_display_list((1 + (sBulletCount * 3) + 8) * sizeof(Gfx));
		if (dlS == NULL) { return NULL; }
        Gfx *dlH = dlS;


		s32 i = BULLET_MAX;
		struct Bullet *b = sBulletList;

		gSPDisplayList(dlH++, sBulletMat);
		while (i--) {
			if (b->flags & BULLET_FLAG_ACTIVE) {
			  if (update) {
				if (b->velY > -40.f) {
					b->velY -= b->gravity; }
				else {
					b->velY = -40.f; }

				Vec3f vel = { (sins(b->yaw) * b->velF),
							  (b->velY),
							  (coss(b->yaw) * b->velF) };

				if (_60fps_on) {
					vec3_mul_val(vel,0.5f);
				}

				vec3f_add(b->pos, vel);

				//collision
				struct Surface *surf;
				Vec3f hitPos = { 0.f, 0.f, 0.f };
				find_surface_on_ray(b->pos, vel, &surf, hitPos, (RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL | RAYCAST_FIND_WALL));
				if ((surf != NULL) || (b->timer++ >= 105)) {
					DELETE_BULLET() }

				//interaction
				struct MarioState *m = gMarioState;
				Vec3f mPos = { m->pos[0], (m->pos[1] + m->marioObj->hitboxHeight), m->pos[2] };
				f32 dist = 0.f;
				vec3f_get_dist(b->pos, mPos, &dist);

				if (dist < b->hitSphereSize) {
					if (
						((m->actionArg == ACT_ARG_PUNCH_SEQUENCE_CHRONOS_SLASH)
						|| (m->actionArg == ACT_ARG_PUNCH_SEQUENCE_CHRONOS_SLASH_AIR))
						||
						(gMarioState->action == ACT_ABILITY_AXE_JUMP)
					 ) {
						//deflect
						if (!(b->flags & BULLET_FLAG_DEFLECTED)) {
							play_sound(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL, m->marioObj->header.gfx.cameraToObject);
							b->yaw   =   b->yaw+0x8000;
							b->velY  =  -b->velY;
							b->flags |=  BULLET_FLAG_DEFLECTED;
						}

					} else if (!(b->flags & BULLET_FLAG_DEFLECTED)) {
						//damage
						if ((!((m->action & ACT_FLAG_INVULNERABLE) || (m->invincTimer != 0)))
							&& !(m->flags & MARIO_VANISH_CAP)
							&& (aku_invincibility == 0)
							&& (!using_ability(ABILITY_KNIGHT)
							&& (m->action != ACT_STAR_DANCE_NO_EXIT) )) {

							m->hurtCounter += (4 * b->damage);
#if ENABLE_RUMBLE
							queue_rumble_data(5, 80);
#endif
							set_camera_shake_from_hit(SHAKE_SMALL_DAMAGE);

							if (b->damage) {
								play_sound(SOUND_MARIO_ATTACKED, m->marioObj->header.gfx.cameraToObject); }


						//--determine_knockback_action
							u32 bonkAction;
							s16 angleToBullet;
							vec3f_get_yaw(m->pos, b->pos, &angleToBullet);
							s16 facingDYaw = (angleToBullet - m->faceAngle[1]);
							s32 remainingHealth = m->health - 0x40 * m->hurtCounter;
							s32 terrainIndex  = 0; // 1 = air, 2 = water, 0 = default
							s32 strengthIndex = 0;

							if (m->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER)) {
								terrainIndex = 2; }
							else if (m->action & (ACT_FLAG_AIR | ACT_FLAG_ON_POLE | ACT_FLAG_HANGING)) {
								terrainIndex = 1; }

							if (remainingHealth < 0x100) {
								strengthIndex = 2; }
							else if (b->damage >= 4) {
								strengthIndex = 2; }
							else if (b->damage >= 2) {
								strengthIndex = 1; }

							m->faceAngle[1] = angleToBullet;

							if (terrainIndex == 2) {
								if (m->forwardVel < 28.f) {
									mario_set_forward_vel(m, 28.f); }

								if (m->pos[1] >= b->pos[1]) {
									if (m->vel[1] < 20.f) {
										m->vel[1] = 20.f; }
								} else {
									if (m->vel[1] > 0.f) {
										m->vel[1] = 0.f; }
								}
							} else {
								if (m->forwardVel < 16.f) {
									mario_set_forward_vel(m, 16.f); }
							}

							if ((-DEGREES(90) <= facingDYaw) && (facingDYaw <= DEGREES(90))) {
								m->forwardVel = -m->forwardVel;
								bonkAction = sBackwardKnockbackActions[terrainIndex][strengthIndex];
							} else {
								m->faceAngle[1] += DEGREES(180);
								bonkAction = sForwardKnockbackActions[terrainIndex][strengthIndex];
							}

							drop_and_set_mario_action(m, bonkAction, b->damage);
							DELETE_BULLET()
						}
					}
				}
			  }

				Mat4  mtxf;
				Vec3s angle = { (atan2s(b->velY, b->velF) + DEGREES(270)), b->yaw, 0 };
				mtxf_rotate_zxy_and_translate(mtxf, b->pos, angle);
				RENDER_GE(sBulletMesh, 2.f)
			}
			b++;
		}


		gSPGeometryMode(dlH++, G_TEXTURE_GEN, G_CULL_BACK | G_LIGHTING);
		gDPSetCycleType(dlH++, G_CYC_1CYCLE);
		gDPSetRenderMode(dlH++, G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2);
		gSPSetGeometryMode(dlH++, G_LIGHTING);
		gSPClearGeometryMode(dlH++, G_TEXTURE_GEN);
		gDPSetCombineLERP(dlH++, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT);
		gSPTexture(dlH++, 65535, 65535, 0, 0, 0);
		gSPEndDisplayList(dlH);
		return dlS;
	  }
	}

	return NULL;
}

s32 obj_hit_by_bullet(struct Object *obj, f32 objHitSphereSize) {
	Vec3f pos = { obj->oPosX, obj->oPosY + (obj->hitboxRadius * 0.5f), obj->oPosZ };
	f32 dist = 0.f;
    for (s32 i = 0; i < BULLET_MAX; i++) {
        struct Bullet *b = &sBulletList[i];

		if (b->flags & BULLET_FLAG_ACTIVE) {
			vec3f_get_dist(pos, b->pos, &dist);

			if (dist < (b->hitSphereSize + objHitSphereSize)) {
				return 1;
			}
		}
    }
    return 0;
}

s32 obj_hit_by_deflected_bullet(struct Object *obj, f32 objHitSphereSize) {
	Vec3f pos = { obj->oPosX, obj->oPosY + (obj->hitboxRadius * 0.5f), obj->oPosZ };
	f32 dist = 0.f;
    for (s32 i = 0; i < BULLET_MAX; i++) {
        struct Bullet *b = &sBulletList[i];

		if (b->flags & BULLET_FLAG_ACTIVE) {
        	vec3f_get_dist_squared(pos, b->pos, &dist);
			f32 hitsphere_squared = (b->hitSphereSize + objHitSphereSize)*(b->hitSphereSize + objHitSphereSize);

			if (dist < hitsphere_squared) {
				if (b->flags & BULLET_FLAG_DEFLECTED) {
					b->flags &= ~BULLET_FLAG_ACTIVE;
					return 1;
				}
			}
		}
    }
    return 0;
} 

void reset_bullet_system(void) {
	sBulletCount = 0;
    for (s32 i = 0; i < BULLET_MAX; i++) {
        struct Bullet *b = &sBulletList[i];
		b->flags = BULLET_FLAG_NONE;
    }
}

#define DANMAKU_MAX 350
struct Danmaku * danmaku_array;//[DANMAKU_MAX];

void create_danmaku(Vec3f pos, Vec3f vel, u8 type) {
	for (int i = 0; i < DANMAKU_MAX; i++) {
		if (!(danmaku_array[i].flags & 1)) {
			danmaku_array[i].flags = 1;
			danmaku_array[i].type = type;
			vec3f_copy(danmaku_array[i].pos,pos);
			vec3f_copy(danmaku_array[i].vel,vel);
			return;
		}
	}
}

#include "levels/sb/header.h"
Gfx *geo_danmaku(s32 callContext, struct GraphNode *node, UNUSED void *context) {
	switch (callContext) {
	case GEO_CONTEXT_AREA_LOAD:
		danmaku_array = main_pool_alloc(DANMAKU_MAX*(sizeof(struct Danmaku)), MEMORY_POOL_LEFT);
		bzero(danmaku_array,DANMAKU_MAX*(sizeof(struct Danmaku)));
		break;
	case GEO_CONTEXT_RENDER:
		{
		s32 update = ((!((gTimeStopState & TIME_STOP_ACTIVE)
						|| (gCameraMovementFlags & CAM_MOVE_PAUSE_SCREEN)))
						&& ability_chronos_frame_can_progress());

		//allocate D
		Gfx *dlS = alloc_display_list(((DANMAKU_MAX * 6) + 15) * sizeof(Gfx));
		if (dlS == NULL) { return NULL; }
        Gfx *dlH = dlS;

		gSPDisplayList(dlH++, mat_sbdms_sb_dm_shadow_layer1);
		//danmaku shadows
		for (int i = 0; i < DANMAKU_MAX; i++) {
			if (danmaku_array[i].flags & 1) { 
				struct Danmaku * d = &danmaku_array[i];

				Mat4  mtxf;
				Vec3s angle = { 0, atan2s(d->vel[2],d->vel[0]), 0 };
				Vec3f pos = {d->pos[0],SB_Y,d->pos[2]};
				mtxf_rotate_zxy_and_translate(mtxf, pos, angle);
				RENDER_GE(sbdms_sbs_mesh_tri_0, 2.f)
			}
		}

		gSPDisplayList(dlH++, mat_sbdm_danmaku_layer1);

		f32 hitradius = 70.0f;
		for (int t = 0; t < 3; t++) {
			Gfx * dmdl = sbdmk_kunai_mesh_tri_0;
			switch(t) {
				case 0:
					gDPSetEnvColor(dlH++,100,0,100,255);
					break;
				case 1:
					gDPSetEnvColor(dlH++,255,255,255,255);
					dmdl = deltarunediamond_deltarunediamond_mesh;
					break;
				case 2:
					gSPDisplayList(dlH++, mat_sbdm_danmaku_layer1);
					gDPSetEnvColor(dlH++,40,0,40,255);
					break;
			}

			for (int i = 0; i < DANMAKU_MAX; i++) {
				if (danmaku_array[i].type == t && (danmaku_array[i].flags & 1)) { 
					struct Danmaku * d = &danmaku_array[i];

					Mat4  mtxf;
					Vec3s angle = { 0/*(atan2s(b->velY, b->velF) + DEGREES(270))*/, atan2s(d->vel[2],d->vel[0]), 0 };
					mtxf_rotate_zxy_and_translate(mtxf, d->pos, angle);
					//RENDER_GE(sbdm_dm_mesh_tri_0, 2.f)
					RENDER_GE(dmdl, 2.f)

					if (update) {
						Vec3f vel;
						vec3f_copy(vel,d->vel);
						if (_60fps_on) {
							vec3_mul_val(vel,0.5f);
						}
						vec3f_add(d->pos,vel);
						if (d->pos[1] < SB_Y+50.0f) {
							d->pos[1] = SB_Y+50.0f;
						}
						if (!_60fps_midframe) {
							d->timer += absf(d->vel[0]) + absf(d->vel[2]); //count taxicab moves
						}
						if (d->timer > 10000) {
							d->flags = 0;
							d->timer = 0;
						}
						f32 distsq;
						vec3f_get_dist_squared(d->pos,gMarioState->pos,&distsq);
						if ((distsq < hitradius*hitradius)&&(gMarioState->invincTimer == 0)) {
							d->flags = 0;
							d->timer = 0;
							gMarioState->hurtCounter += 4;
							gMarioState->invincTimer = 30;
							play_sound(SOUND_MARIO_UH, gMarioState->marioObj->header.gfx.cameraToObject);
						}
					}
				}
			}
		}

		gSPGeometryMode(dlH++, G_TEXTURE_GEN, G_CULL_BACK | G_LIGHTING);
		gDPSetCycleType(dlH++, G_CYC_1CYCLE);
		gDPSetRenderMode(dlH++, G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2);
		gSPSetGeometryMode(dlH++, G_LIGHTING);
		gSPClearGeometryMode(dlH++, G_TEXTURE_GEN);
		gDPSetCombineLERP(dlH++, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT);
		gSPTexture(dlH++, 65535, 65535, 0, 0, 0);
		gSPEndDisplayList(dlH);
		struct GraphNodeGenerated *graphNode = (struct GraphNodeGenerated *) node;
		SET_GRAPH_NODE_LAYER(graphNode->fnNode.node.flags, LAYER_TRANSPARENT_INTER);
		return dlS;
		}
	}

	return NULL;
}