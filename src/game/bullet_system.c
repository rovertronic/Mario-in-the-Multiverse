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

#include "ge_translation.h"


//--MISC
extern u32 sForwardKnockbackActions[][3];
extern u32 sBackwardKnockbackActions[][3];





//-- * Data *


#define BULLET_MAX  20

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
static void bullet_f_params(struct Bullet *b) {
	b->velF          = 50.f;
	b->gravity       = 0.f;
	b->hitSphereSize = 50.f;
	b->damage        = 2;
}
static void bullet_i_params(struct Bullet *b) {
	b->velF          = 15.f;
	b->gravity       = 0.f;
	b->hitSphereSize = 15.f;
	b->damage        = 2;
}
static void bullet_k_params(struct Bullet *b) {
	b->velF          = 0.f;
	b->gravity       = 0.f;
	b->hitSphereSize = 0.f;
	b->damage        = 0;
}

void dobj_spawn_bullet(Vec3f pos, s16 rX, s16 rY) {
	if (sBulletCount == BULLET_MAX) { return NULL; }

	struct Bullet *b = sBulletList;
	while (b->flags & BULLET_FLAG_ACTIVE) {
		b++; }
	sBulletCount++;

	b->flags |= BULLET_FLAG_ACTIVE;
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
		
		case LEVEL_F:
			sBulletParamFn = bullet_f_params;
			sBulletMat     = mat_e_sg_piece_mat_f3d_layer1;
			sBulletMesh    = fbullet_Cube_mesh;
			break;
		
		case LEVEL_I:
			sBulletParamFn = bullet_i_params;
			sBulletMat     = mat_revert_hoodmonger_bullet_f3dlite_material;
			sBulletMesh    = hoodmonger_bullet_bullet_mesh_layer_5;
			break;
		
		/*
		case LEVEL_K:
			sBulletParamFn = bullet_k_params;
			sBulletMat     = NULL;
			sBulletMesh    = NULL;
			break;
		*/
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
					if ((m->actionArg == ACT_ARG_PUNCH_SEQUENCE_CHRONOS_SLASH)
						|| (m->actionArg == ACT_ARG_PUNCH_SEQUENCE_CHRONOS_SLASH_AIR)) {
						//deflect
						b->yaw   =   m->faceAngle[1];
						b->velY  =  -b->velY;
						b->flags |=  BULLET_FLAG_DEFLECTED;

					} else if (!(b->flags & BULLET_FLAG_DEFLECTED)) {
						//damage
						if ((!((m->action & ACT_FLAG_INVULNERABLE) || (m->invincTimer != 0)))
							&& !(m->flags & MARIO_VANISH_CAP)
							&& (aku_invincibility == 0)
							&& (!using_ability(ABILITY_KNIGHT))) {

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


		//revert for any other generated display list functions after this
		gSPGeometryMode(dlH++, 0, G_LIGHTING);
		gDPSetCycleType(dlH++, G_CYC_1CYCLE);
		gDPSetRenderMode(dlH++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
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