#include <PR/gbi.h>
#include "actors/group0.h"
#include "include/macros.h"
#include "include/sm64.h"
#include "include/types.h"
#include "src/engine/graph_node.h"
#include "src/engine/math_util.h"
#include "src/engine/surface_collision.h"
#include "e__shotgun_effects.h"
#include "camera.h"
#include "object_list_processor.h"
#include "tile_scroll.h"
#include "game_init.h"
#include "level_update.h"
//This is a way of dealing with what I mentioned in #mverse-general
#define TRANSLATION_IS_WEIRD



//-- * Data *

#define SG_EFFECT_AMOUNT 4

#define SG_WALL_DAMAGE_MAX 50
#define SG_SMOKE_MAX       50
#define SG_PIECE_MAX       40
#define SG_SPARK_MAX       35

enum {
	SG_EFFECT_TYPE_WALL_DAMAGE,
	SG_EFFECT_TYPE_SMOKE,
	SG_EFFECT_TYPE_PIECE,
	SG_EFFECT_TYPE_SPARK,
};

static struct SGWallDamage sSGWallDamageList[SG_WALL_DAMAGE_MAX] = { 0 };
static struct SGSmoke      sSGSmokeList[SG_SMOKE_MAX]            = { 0 };
static struct SGPiece      sSGPieceList[SG_PIECE_MAX]            = { 0 };
static struct SGSpark      sSGSparkList[SG_SPARK_MAX]            = { 0 };

static u8 sSGEffectCurrCounts[SG_EFFECT_AMOUNT]     = { 0, 0, 0, 0 };




//--Spawn

//individual
struct SGWallDamage *e__sg_wall_damage(Vec3f pos, struct Surface *surf) {
	if (sSGEffectCurrCounts[SG_EFFECT_TYPE_WALL_DAMAGE] == SG_WALL_DAMAGE_MAX) { return NULL; }
	sSGEffectCurrCounts[SG_EFFECT_TYPE_WALL_DAMAGE]++;

	struct SGWallDamage *wallDamageList = &sSGWallDamageList;
	while (wallDamageList->opacity) {//find free effect
		wallDamageList++; }
	wallDamageList->opacity = 0xFF;
	wallDamageList->scale   = (0.5f + random_float());
	vec3f_copy(wallDamageList->pos, pos);
	wallDamageList->surf = surf;
	return wallDamageList;
}
struct SGSmoke *e__sg_smoke(Vec3f pos) {
	if (sSGEffectCurrCounts[SG_EFFECT_TYPE_SMOKE] == SG_SMOKE_MAX) { return NULL; }
	sSGEffectCurrCounts[SG_EFFECT_TYPE_SMOKE]++;

	struct SGSmoke *smokeList = &sSGSmokeList;
	while (smokeList->timer) {//find free effect
		smokeList++; }
	smokeList->timer = 1;
	smokeList->scale = (4.f + (random_float() * 6.f));
	smokeList->homeY = pos[1];
	vec3f_copy(smokeList->pos, pos);
	return smokeList;
}
struct SGPiece *e__sg_piece(Vec3f pos, Vec3f baseVel) {
	if (sSGEffectCurrCounts[SG_EFFECT_TYPE_PIECE] == SG_PIECE_MAX) { return NULL; }
	sSGEffectCurrCounts[SG_EFFECT_TYPE_PIECE]++;

	struct SGPiece *pieceList = &sSGPieceList;
	while (pieceList->scale) {//find free effect
		pieceList++; }
	pieceList->scale = (1.f + random_float());
	vec3f_copy(pieceList->pos, pos);
	Vec3f vel = { ((random_float() * 20.f) - 10.f), ((random_float() * 40.f) - 20.f), ((random_float() * 20.f) - 10.f) };
	vec3f_add(vel, baseVel);
	vec3f_copy(pieceList->vel, vel);
	s16 angle = random_u16();
	pieceList->rX = angle;
	pieceList->rY = angle;
	return pieceList;
}
struct SGSpark *e__sg_spark(Vec3f pos, f32 scale) {
	if (sSGEffectCurrCounts[SG_EFFECT_TYPE_SPARK] == SG_SPARK_MAX) { return NULL; }
	sSGEffectCurrCounts[SG_EFFECT_TYPE_SPARK]++;

	struct SGSpark *sparkList = &sSGSparkList;
	while (sparkList->scale) {//find free effect
		sparkList++; }
	sparkList->scale = scale;
	vec3f_copy(sparkList->pos, pos);
	return sparkList;
}

//preset
void e__sg_obj_shot_sparks(struct Object *obj) {
	s32 i = 3;
	f32 mag = sqrtf(sqr(obj->hitboxRadius) + sqr(obj->hitboxHeight));
	Vec3f pos = { 0.f, 0.f, 0.f };
	while (i--) {
		f32 halfMag = (mag * 0.5f);
		vec3f_set(pos, ((random_float() * mag) - halfMag), ((random_float() * mag) - halfMag), ((random_float() * mag) - halfMag));
		vec3f_add(pos, &obj->oPosX);
		e__sg_spark(pos, (0.5f + (random_float() * 3.f)));
	}
	struct SGSmoke *smoke = e__sg_smoke(pos);
	if (smoke != NULL) {
		smoke->timer = 3;
		smoke->scale = 3.f;
	}
}
void e__sg_obj_explode(struct Object *obj, s32 count) {
	f32 mag = sqrtf(sqr(obj->hitboxRadius) + sqr(obj->hitboxHeight));
	Vec3f pos = { 0.f, 0.f, 0.f };
	while (count--) {
		f32 halfMag = (mag * 0.5f);
		vec3f_set(pos, ((random_float() * mag) - halfMag), ((random_float() * mag) - halfMag), ((random_float() * mag) - halfMag));
		vec3f_add(pos, &obj->oPosX);
		e__sg_spark(pos, (0.5f + (random_float() * 3.f)));
		Vec3f vel = { 10.f, 20.f, 10.f };
		e__sg_piece(pos, vel);
		if ((count % 3) == 0) {
			struct SGSmoke *smoke = e__sg_smoke(pos);
			if (smoke != NULL) {
				smoke->timer = 3; }
		}
	}
}




//--Process

#ifdef TRANSLATION_IS_WEIRD
#define RENDER_SG_EFFECT(mesh_dl, mul)                              \
	Mtx *mtx = alloc_display_list(sizeof(Mtx));                     \
	mtxf[3][0] *= mul; mtxf[3][1] *= mul; mtxf[3][2] *= mul;        \
	mtxf_to_mtx(mtx, mtxf);                                         \
	gSPMatrix(dlH++, mtx, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);\
	gSPDisplayList(dlH++, mesh_dl);                                 \
	gSPPopMatrix(dlH++, G_MTX_MODELVIEW);                           

#else
#define RENDER_SG_EFFECT(mesh_dl, unused)                           \
	Mtx *mtx = alloc_display_list(sizeof(Mtx));                     \
	mtxf_to_mtx(mtx, mtxf);                                         \
	gSPMatrix(dlH++, mtx, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);\
	gSPDisplayList(dlH++, mesh_dl);                                 \
	gSPPopMatrix(dlH++, G_MTX_MODELVIEW);                           
#endif



//--Main
Gfx *e__shotgun_effects(s32 callContext, struct GraphNode *node, UNUSED Mat4 unused) {
	switch (callContext) {
	case GEO_CONTEXT_AREA_LOAD:
		bzero(sSGWallDamageList, (SG_WALL_DAMAGE_MAX * sizeof(struct SGWallDamage)));
		bzero(sSGSmokeList,      (SG_SMOKE_MAX       * sizeof(struct SGSmoke)));
		bzero(sSGPieceList,      (SG_PIECE_MAX       * sizeof(struct SGPiece)));
		bzero(sSGSparkList,      (SG_SPARK_MAX       * sizeof(struct SGSpark)));
		if (gCurrLevelNum == LEVEL_DDD) {
			gE_MaxObjsHitPerShot = 8; }
		else {
			gE_MaxObjsHitPerShot = 4; }
	    break;


	case GEO_CONTEXT_RENDER:
	  {
		s32 update = (!((gTimeStopState & TIME_STOP_ACTIVE) || (gCameraMovementFlags & CAM_MOVE_PAUSE_SCREEN)));
		Gfx *dlS = alloc_display_list(((1 + (sSGEffectCurrCounts[SG_EFFECT_TYPE_WALL_DAMAGE] * 4))
									 + (1 + (sSGEffectCurrCounts[SG_EFFECT_TYPE_SMOKE] * 4))
									 + (1 + (sSGEffectCurrCounts[SG_EFFECT_TYPE_PIECE] * 3))
									 + (1 + (sSGEffectCurrCounts[SG_EFFECT_TYPE_SPARK] * 3))
									 + (SG_EFFECT_AMOUNT * 7)
									 + 1) * sizeof(Gfx));
        Gfx *dlH = dlS;
		if (dlS == NULL) { return NULL; }


		//piece | Note: reordered to be first to avoid mat bleeds (less commands in this function)
		gSPDisplayList(dlH++, mat_e_sg_piece_mat_f3d_layer1);
		struct SGPiece *piece = &sSGPieceList;
		s32 length = SG_PIECE_MAX;
		while (length--) {
			if (piece->scale) {
			  if (update) {
				piece->scale -= 0.02f;
				if (piece->scale <= 0.f) {
					//deactivate
					piece->scale = 0.f;
					sSGEffectCurrCounts[SG_EFFECT_TYPE_PIECE]--;
					piece++;
					continue;
				}
				piece->rX += DEGREES(7);
				piece->rY += DEGREES(3);
				if (piece->vel[1] > -40.f) {
					piece->vel[1] -= 4.f; }
				f32 fh = find_floor_height(piece->pos[0], piece->pos[1], piece->pos[2]);
				if (piece->pos[1] < fh) {
					piece->pos[1] = fh;
					piece->vel[0] *= 0.6f;
					piece->vel[1] *= -0.6f;
					piece->vel[2] *= 0.6f;
				}
				vec3f_add(piece->pos, piece->vel);
			  }
				Mat4 mtxf;
				Vec3f scale = { piece->scale, piece->scale, piece->scale };
				Vec3s angle = { piece->rX, piece->rY, 0 };
				mtxf_rotate_zxy_and_translate(mtxf, piece->pos, angle);
				mtxf_scale_vec3f(mtxf, mtxf, scale);
				RENDER_SG_EFFECT(e_sg_piece_piece_mesh_tri_0, 2.f)
			}
			piece++;
		}


		//wall damage
		gSPDisplayList(dlH++, mat_e_sg_wall_damage_mat_f3d_layer1);
		struct SGWallDamage *wallDamage = &sSGWallDamageList;
		length = SG_WALL_DAMAGE_MAX;
		while (length--) {
			if (wallDamage->opacity) {
			  if (update) {
				if (--wallDamage->opacity == 0) {
					//deactivate
					wallDamage->opacity = 0;
					sSGEffectCurrCounts[SG_EFFECT_TYPE_WALL_DAMAGE]--;
					wallDamage++;
					continue;
				}
			  }
				Mat4 mtxf;
				Vec3f scale = { wallDamage->scale, wallDamage->scale, wallDamage->scale };
				Vec3f upDir;
				surface_normal_to_vec3f(upDir, wallDamage->surf);
				mtxf_shadow(mtxf, ((f32 *)(&wallDamage->surf->normal)), wallDamage->pos, scale, ((s32)(scale[0] * 65536.f)));
				gDPSetEnvColor(dlH++, 0xFF, 0xFF, 0xFF, wallDamage->opacity);
				RENDER_SG_EFFECT(e_sg_wall_damage_wallDamage_mesh_tri_0, 2.f)
			}
			wallDamage++;
		}


		//smoke
		gSPDisplayList(dlH++, mat_e_sg_smoke_mat_f3d_layer1);
		struct SGSmoke *smoke = &sSGSmokeList;
		length = SG_SMOKE_MAX;
		while (length--) {
			if (smoke->timer) {
			  if (update) {
				//randomly generate extra smoke
				switch (smoke->timer) {
				case 21841:
				case 21842:
				case 21843:
					if (random_u16() & 1) {
						Vec3f pos = { smoke->pos[0], smoke->homeY, smoke->pos[2] };
						struct SGSmoke *newSmoke = e__sg_smoke(pos);
						if (newSmoke != NULL) {
							newSmoke->timer = ((smoke->timer - 21840) + 1); }
					}
				}

				if ((smoke->timer += 728) >= 32761) {
					//deactivate
					smoke->timer = 0;
					sSGEffectCurrCounts[SG_EFFECT_TYPE_SMOKE]--;
					smoke++;
					continue;
				}
				smoke->pos[1] += 10.f;
			  }
				Mat4 mtxf;
				Vec3f scale = { smoke->scale, smoke->scale, smoke->scale };
				mtxf_billboard(mtxf, mtxf, smoke->pos, scale, gLakituState.roll);
				gDPSetEnvColor(dlH++, 0xFF, 0xFF, 0xFF, ((s32)(sins(smoke->timer) * 127.f)));
				RENDER_SG_EFFECT(e_sg_smoke_smoke_mesh_tri_0, 1.f)
			}
			smoke++;
		}


		//spark
		gSPDisplayList(dlH++, mat_e_sg_spark_mat_f3d_layer1);
		struct SGSpark *spark = &sSGSparkList;
		length = SG_SPARK_MAX;
		while (length--) {
			if (spark->scale) {
			  if (update) {
				if ((spark->scale -= 0.1f) <= 0.f) {
					//deactivate
					spark->scale = 0.f;
					sSGEffectCurrCounts[SG_EFFECT_TYPE_SPARK]--;
					spark++;
					continue;
				}
				if (spark->scale < 2.f) {
					spark->pos[1] -= ((2.f - spark->scale) * 15.f); }
			  }
				Mat4 mtxf;
				Vec3f scale = { spark->scale, spark->scale, spark->scale };
				mtxf_billboard(mtxf, mtxf, spark->pos, scale, gLakituState.roll);
				RENDER_SG_EFFECT(e_sg_spark_smoke_mesh_tri_0, 1.f)
			}
			spark++;
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

        struct GraphNodeGenerated *graphNode = (struct GraphNodeGenerated *) node;
		graphNode->fnNode.node.flags = (graphNode->fnNode.node.flags & 0xFF) | 0x700;//--GBPI (0x700)
		return dlS;
	  }
	}

	return NULL;
}
