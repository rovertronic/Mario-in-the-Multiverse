//Warning: unfinished, rushed & bad

#include <PR/gbi.h>
#include "levels/e/header.h"
#include "include/behavior_data.h"
#include "include/macros.h"
#include "include/sm64.h"
#include "include/types.h"
#include "src/engine/graph_node.h"
#include "src/engine/math_util.h"
#include "src/engine/surface_collision.h"
#include "e__c9_dobj.h"
#include "e__shotgun_effects.h"
#include "camera.h"
#include "mario_actions_object.h"
#include "object_list_processor.h"
#include "tile_scroll.h"
#include "game_init.h"
#include "level_update.h"
#include "interaction.h"

#include "ge_translation.h"


//--MISC

extern u8 gE_C9MarioHealth;




//-- * Data *


#define C9_BULLET_MAX      50
#define C9_REV_FB_MAX      20
#define C9_CACO_FB_MAX     15
#define C9_MANCUBUS_FB_MAX 30
#define C9_ACID_MAX        10

static struct E_C9Dobj sC9BulletList[C9_BULLET_MAX]          = { 0 };
static struct E_C9Dobj sC9RevFBList[C9_REV_FB_MAX]           = { 0 };
static struct E_C9Dobj sC9CacoFBList[C9_CACO_FB_MAX]         = { 0 };
static struct E_C9Dobj sC9MancubusFBList[C9_MANCUBUS_FB_MAX] = { 0 };
static struct E_C9Dobj sC9AcidList[C9_ACID_MAX]              = { 0 };

static struct E_C9Dobj *sC9DobjLists[5] = {
	sC9BulletList, sC9RevFBList, sC9CacoFBList,sC9MancubusFBList, sC9AcidList
};

static u8 sC9DobjMaxCounts[5] = { C9_BULLET_MAX, C9_REV_FB_MAX, C9_CACO_FB_MAX, C9_MANCUBUS_FB_MAX, C9_ACID_MAX };
static u8 sC9DobjCounts[5] = { 0 };



//-- * Spawn *


void e__spawn_c9_dobj(struct Object *attacker, struct Object *target, s32 type, Vec3f pos, f32 velF, f32 hitSphereSize, s16 yaw) {
	if (sC9DobjCounts[type] == sC9DobjMaxCounts[type]) { return NULL; }

	struct E_C9Dobj *b = sC9DobjLists[type];
	while (b->state & BIT(0)) {
		b++; }
	sC9DobjCounts[type]++;

	b->state = BIT(0);
	vec3f_copy(b->pos, pos);
	Vec3f targetPos = { target->oPosX, (target->oPosY + 120.f), target->oPosZ };//--**
	s16 pitch = calculate_pitch(pos, targetPos);
	if (pitch > DEGREES(60)) {
		pitch = DEGREES(60); }
	if (pitch < -DEGREES(60)) {
		pitch = -DEGREES(60); }
	b->velF = (coss(pitch) * velF);
	b->velY = (sins(pitch) * velF);
	b->hitSphereSize = hitSphereSize;
	b->pitch = pitch;
	b->yaw   = yaw;
	b->timer =  0;
	b->attacker = attacker;
	b->target   = target;
}


static s32 c9dobj_check_collision(struct E_C9Dobj *b, Vec3f vel, s32 damage) {
	//collision
	struct Surface *surf;
	Vec3f hitPos = { 0.f, 0.f, 0.f };
	Vec3f orig = { b->pos[0], b->pos[1], b->pos[2] };
	find_surface_on_ray(orig, vel, &surf, hitPos, (RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL | RAYCAST_FIND_WALL));
	if ((surf != NULL) || (b->timer++ >= 105)) {
		return 1;
	}
	vec3f_add(b->pos, vel);

	//--interaction

	//Mario
  {
	struct MarioState *m = gMarioState;
	Vec3f mPos = { m->pos[0], (m->pos[1] + 80.f), m->pos[2] };
	f32 dist = 0.f;
	vec3f_get_dist(b->pos, mPos, &dist);

	if (dist < (b->hitSphereSize + 80.f)) {
		if (
			((m->actionArg == ACT_ARG_PUNCH_SEQUENCE_CHRONOS_SLASH)
			|| (m->actionArg == ACT_ARG_PUNCH_SEQUENCE_CHRONOS_SLASH_AIR))
			||
			(gMarioState->action == ACT_ABILITY_AXE_JUMP)
		 ) {
			//
			if (!(b->state & BIT(1))) {
				play_sound(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL, m->marioObj->header.gfx.cameraToObject);
				if (abs_angle_diff(m->faceAngle[1],b->yaw) > 0x4000) {
					b->yaw = b->yaw+0x8000;
				} else {
					b->yaw = m->faceAngle[1];
				}
			
				b->hitSphereSize += 50.0f;

				b->velY  =  -b->velY;
				b->pitch =  -b->pitch;
				b->state |=  BIT(1);
			}

		} else if (!(b->state & BIT(1))) {
			//damage
			if ((!((m->action & ACT_FLAG_INTANGIBLE) || (m->action & ACT_FLAG_INVULNERABLE) || (m->invincTimer != 0)))
				&& !(m->flags & MARIO_VANISH_CAP)
				&& (aku_invincibility == 0)
				&& (!using_ability(ABILITY_KNIGHT))) {

				s32 health = (gE_C9MarioHealth - damage);
				if (health <= 0) {
					gE_C9MarioHealth = 0;
					play_sound(SOUND_MARIO_WAAAOOOW, m->marioObj->header.gfx.cameraToObject);

					if (using_ability(ABILITY_E_SHOTGUN)) {
						//-spawn_object(gMarioObject, MODEL_ID_05, bhvStaticObject);
						set_mario_action(m, ACT_E_DOOM_DEATH, 1);
					} else {
						set_mario_action(m, ACT_E_DOOM_DEATH, 0);
					}

					//if (gCamera->mode == CAMERA_MODE_C_UP) {//--**
						set_camera_mode_8_directions(gCamera);
					//}
				} else {
					gE_C9MarioHealth = health;
					play_sound(SOUND_MARIO_UH, m->marioObj->header.gfx.cameraToObject);
					obj_set_model(gMarioObject, 0);
				}

				return 2;
			}
		}
	}
  }

	//obj
  {
	struct ObjectNode *listHead = &gObjectLists[OBJ_LIST_PUSHABLE];
	struct ObjectNode *objNode = listHead->next;
	struct Object *obj;
	s32 attackerNotNull = (b->attacker != NULL);

	while (listHead != objNode) {
		obj = ((struct Object *) objNode);

		if ((obj->behavior == segmented_to_virtual(bhvE_Caco)
		 || (obj->behavior == segmented_to_virtual(bhvE_PistolGuy))
		 || (obj->behavior == segmented_to_virtual(bhvE_ChaingunGuy)))//--**
		 ) {
			s32 diffBhv = FALSE;
			if (attackerNotNull) {//--**
				if (obj->behavior != b->attacker->behavior) {
					diffBhv = TRUE;
				}
			}
			if ((b->state & BIT(1)) || diffBhv) {
				Vec3f oPos = { obj->oPosX, (obj->oPosY + (obj->hitboxHeight * 0.5f)), obj->oPosZ };
				f32 dist = 0.f;
				vec3f_get_dist(b->pos, oPos, &dist);

				if (dist < (b->hitSphereSize + obj->hitboxRadius)) {
					if (b->state & BIT(1)) {
						obj->oHealth-=20.0f;
						obj->oInteractStatus |= INT_STATUS_WAS_ATTACKED;
						return 2;
					}

					//damage
					obj->oAnimState  = ((damage / 100) + (((random_u16()) % 2) == 0));//oEEAttackedByEnemy | damage value also stored in oAnimState
					if (attackerNotNull) {//--**
						if (obj->OBJECT_FIELD_S32(0x4A) == FALSE) {
							obj->OBJECT_FIELD_OBJ(0x22) = b->attacker; }
					}

					return 2;
				}
			}
		}
        objNode = objNode->next;
	}
  }
	return 0;
}

#define RENDER_C9DOBJ(b, mesh, dlH)\
	Mat4 mtxf;\
	Vec3s angle = { -b->pitch, b->yaw, 0 };\
	mtxf_rotate_zxy_and_translate(mtxf, b->pos, angle);\
	RENDER_GE(mesh, 2.f)



//-- * Main *
Gfx *e__c9_dobj(s32 callContext, struct GraphNode *node, UNUSED Mat4 unused) {
	switch (callContext) {
	case GEO_CONTEXT_CREATE:
		gE_C9MarioHealth = 100;//--**
		break;


	case GEO_CONTEXT_AREA_LOAD:
		bzero(sC9BulletList,     (C9_BULLET_MAX      * sizeof(struct E_C9Dobj)));
		bzero(sC9RevFBList,      (C9_REV_FB_MAX      * sizeof(struct E_C9Dobj)));
		bzero(sC9CacoFBList,     (C9_CACO_FB_MAX     * sizeof(struct E_C9Dobj)));
		bzero(sC9MancubusFBList, (C9_MANCUBUS_FB_MAX * sizeof(struct E_C9Dobj)));
		bzero(sC9AcidList,       (C9_ACID_MAX        * sizeof(struct E_C9Dobj)));
	    break;


	case GEO_CONTEXT_RENDER:;
		s32 update = ((!((gTimeStopState & TIME_STOP_ACTIVE)
						|| (gCameraMovementFlags & CAM_MOVE_PAUSE_SCREEN)))
						&& ability_chronos_frame_can_progress());

		Gfx *dlS = alloc_display_list(((1 + (sC9DobjCounts[0] * 4) + 7)
									 + (1 + (sC9DobjCounts[1] * 4) + 7)
									 + (1 + (sC9DobjCounts[2] * 4) + 7)
									 + (1 + (sC9DobjCounts[3] * 4) + 7)
									 + (1 + (sC9DobjCounts[4] * 4) + 7)) * sizeof(Gfx));
		if (dlS == NULL) { return NULL; }
        Gfx *dlH = dlS;


		//bullet
		s32 i = C9_BULLET_MAX;
		struct E_C9Dobj *b = sC9BulletList;

		gSPDisplayList(dlH++, mat_e_bullet_bb_f3d_layer1);
		while (i--) {
			if (b->state & BIT(0)) {
			  if (update) {
				Vec3f vel = { (sins(b->yaw) * b->velF),
							  (b->velY),
							  (coss(b->yaw) * b->velF) };

				if (_60fps_on) {
					vec3_mul_val(vel,0.5f);
				}

				if (c9dobj_check_collision(b, vel, 2)) {			
					struct SGSmoke *smoke = e__sg_smoke(b->pos);
					if (smoke != NULL) {
						smoke->timer = 4;
						smoke->scale = 3.f;
					}
					b->state &= ~BIT(0);
					sC9DobjCounts[0]--;
				}
			  }

				RENDER_C9DOBJ(b, e_bullet_bullet_mesh_tri_0, dlH)	
			}
			b++;
		}
		gSPDisplayList(dlH++, mat_revert_e_bullet_bb_f3d_layer1);
		gDPPipeSync(dlH++);
		gSPSetGeometryMode(dlH++, G_LIGHTING);
		gSPClearGeometryMode(dlH++, G_TEXTURE_GEN);
		gDPSetCombineLERP(dlH++, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT);
		gSPTexture(dlH++, 65535, 65535, 0, 0, 0);
		gSPEndDisplayList(dlH);



		//revenant FB
		i = C9_REV_FB_MAX;
		b = sC9RevFBList;

		gSPDisplayList(dlH++, mat_e_bullet_bb_f3d_layer1);
		while (i--) {
			if (b->state & BIT(0)) {
			  if (update) {
				Vec3f vel = { (sins(b->yaw) * b->velF),
							  (b->velY),
							  (coss(b->yaw) * b->velF) };

				if (c9dobj_check_collision(b, vel, 40)) {
					b->state &= ~BIT(0);
					sC9DobjCounts[0]--;
				}
			  }

				Mat4 mtxf;
				mtxf_billboard(mtxf, mtxf, b->pos, gVec3fOne, gLakituState.roll);
				RENDER_GE(e_caco_fb_bullet_mesh_tri_0, 1.f)	
			}
			b++;
		}
		gSPDisplayList(dlH++, mat_revert_e_bullet_bb_f3d_layer1);
		gDPPipeSync(dlH++);
		gSPSetGeometryMode(dlH++, G_LIGHTING);
		gSPClearGeometryMode(dlH++, G_TEXTURE_GEN);
		gDPSetCombineLERP(dlH++, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT);
		gSPTexture(dlH++, 65535, 65535, 0, 0, 0);
		gSPEndDisplayList(dlH);



		//caco FB
		i = C9_CACO_FB_MAX;
		b = sC9CacoFBList;

		gSPDisplayList(dlH++, mat_e_caco_fb_bb_f3d_layer1);
		while (i--) {
			if (b->state & BIT(0)) {
			  if (update) {
				Vec3f vel = { (sins(b->yaw) * b->velF),
							  (b->velY),
							  (coss(b->yaw) * b->velF) };

				if (_60fps_on) {
					vec3_mul_val(vel,0.5f);
				}

				if (c9dobj_check_collision(b, vel, 28)) {
        			play_sound(SOUND_MITM_LEVEL_E_MISSILE_EXPLODE, o->header.gfx.cameraToObject);
            		struct SGSmoke *newSmoke = e__sg_smoke(b->pos);
					if (newSmoke != NULL) {
						newSmoke->timer = 3; }					
					b->state &= ~BIT(0);
					sC9DobjCounts[2]--;
				}
			  }

				Vec3f scale = { 1.f, 1.f, 1.f };
				if (!(b->state & BIT(0))) {
					vec3f_set(scale, 2.f, 2.f, 2.f); }
				Mat4 mtxf;
				mtxf_billboard(mtxf, mtxf, b->pos, scale, gLakituState.roll);
				RENDER_GE(e_caco_fb_bullet_mesh_tri_0, 1.f)	
			}
			b++;
		}
		gSPDisplayList(dlH++, mat_revert_e_caco_fb_bb_f3d_layer1);
		gDPPipeSync(dlH++);
		gSPSetGeometryMode(dlH++, G_LIGHTING);
		gSPClearGeometryMode(dlH++, G_TEXTURE_GEN);
		gDPSetCombineLERP(dlH++, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT);
		gSPTexture(dlH++, 65535, 65535, 0, 0, 0);
		gSPEndDisplayList(dlH);



		//mancubus FB
		i = C9_MANCUBUS_FB_MAX;
		b = sC9MancubusFBList;

		gSPDisplayList(dlH++, mat_e_bullet_bb_f3d_layer1);
		while (i--) {
			if (b->state & BIT(0)) {
			  if (update) {
				Vec3f vel = { (sins(b->yaw) * b->velF),
							  (b->velY),
							  (coss(b->yaw) * b->velF) };

				c9dobj_check_collision(b, vel, 1);//--**
			  }

				RENDER_C9DOBJ(b, e_bullet_bullet_mesh_tri_0, dlH)

				if (!(b->state & BIT(0))) {
					sC9DobjCounts[0]--;
				}				
			}
			b++;
		}
		gSPDisplayList(dlH++, mat_revert_e_bullet_bb_f3d_layer1);
		gDPPipeSync(dlH++);
		gSPSetGeometryMode(dlH++, G_LIGHTING);
		gSPClearGeometryMode(dlH++, G_TEXTURE_GEN);
		gDPSetCombineLERP(dlH++, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT);
		gSPTexture(dlH++, 65535, 65535, 0, 0, 0);
		gSPEndDisplayList(dlH);		



		//acid
		i = C9_ACID_MAX;
		b = sC9AcidList;

		gSPDisplayList(dlH++, mat_e_bullet_bb_f3d_layer1);
		while (i--) {
			if (b->state & BIT(0)) {
			  if (update) {
				Vec3f vel = { (sins(b->yaw) * b->velF),
							  (b->velY),
							  (coss(b->yaw) * b->velF) };

				//c9dobj_check_collision(b, vel, 1);//--**
			  }

				RENDER_C9DOBJ(b, e_bullet_bullet_mesh_tri_0, dlH)

				if (!(b->state & BIT(0))) {
					sC9DobjCounts[0]--;
				}				
			}
			b++;
		}

		gSPGeometryMode(dlH++, G_TEXTURE_GEN, G_CULL_BACK | G_LIGHTING);
		gDPSetCycleType(dlH++, G_CYC_1CYCLE);
		gDPSetRenderMode(dlH++, G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2);
		gSPSetGeometryMode(dlH++, G_LIGHTING);
		gDPSetCombineLERP(dlH++, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT);
		gSPTexture(dlH++, 65535, 65535, 0, 0, 0);
		gSPEndDisplayList(dlH);

        struct GraphNodeGenerated *graphNode = (struct GraphNodeGenerated *) node;
		SET_GRAPH_NODE_LAYER(graphNode->fnNode.node.flags, LAYER_TRANSPARENT_INTER);
		return dlS;
	}

	return NULL;
}



//--**

Gfx *e__c9_sky(s32 callContext, struct GraphNode *node, Mat4 mtxf) {
	if (callContext == GEO_CONTEXT_RENDER) {
		Gfx *dlE = alloc_display_list(4 * sizeof(Gfx));
		Gfx *dlS = dlE;
		Mtx *mtx = alloc_display_list(sizeof(Mtx));
		guTranslate(mtx, (s32)(gCurGraphNodeCamera->posLerp[0]), (s32)(gCurGraphNodeCamera->posLerp[1]), (s32)(gCurGraphNodeCamera->posLerp[2]));
		gSPMatrix(dlE++, mtx, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
		gSPDisplayList(dlE++, e_sky_main_mesh);
		gSPEndDisplayList(dlE);

        struct GraphNodeGenerated *graphNode = (struct GraphNodeGenerated *) node;
        graphNode->fnNode.node.flags = (graphNode->fnNode.node.flags & 0xFF) | 0x000;
		return dlS;
	}

	return NULL;
}