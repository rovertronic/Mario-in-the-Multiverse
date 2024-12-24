#include <PR/gbi.h>
#include "actors/group0.h"
#include "include/macros.h"
#include "include/sm64.h"
#include "include/types.h"
#include "src/engine/graph_node.h"
#include "src/engine/math_util.h"
#include "src/engine/surface_collision.h"
#include "e__door_light.h"
#include "camera.h"
#include "object_list_processor.h"
#include "tile_scroll.h"
#include "game_init.h"
#include "level_update.h"
#include "levels/e/header.h"

#include "ge_translation.h"



//--Data

#define E_DOOR_LIGHT_COUNT 1

static struct E_DoorLight sEDoorLightList[E_DOOR_LIGHT_COUNT] = { 0 };



//--Spawn

void e__create_door_light(struct Object *door) {
	return;
	struct E_DoorLight *doorLight = &sEDoorLightList;
	while (doorLight->door) {//find free foor
		doorLight++; }
	doorLight->door = door;

	vec3f_to_vec3s(doorLight->verts[0], &door->oPosX);
	s16 offsetYaw = (door->oFaceAngleYaw + DEGREES(89));
	doorLight->verts[0][0] += (s16)(sins(offsetYaw) * 500.f);
	doorLight->verts[0][2] += (s16)(coss(offsetYaw) * 500.f);
	
	vec3f_to_vec3s(doorLight->verts[1], &door->oPosX);
	offsetYaw = (door->oFaceAngleYaw - DEGREES(89));
	doorLight->verts[1][0] += (s16)(sins(offsetYaw) * 500.f);
	doorLight->verts[1][2] += (s16)(coss(offsetYaw) * 500.f);
}



//--Main
Gfx *e__door_light(s32 callContext, struct GraphNode *node, UNUSED Mat4 unused) {
	switch (callContext) {
	case GEO_CONTEXT_AREA_LOAD:
		bzero(sEDoorLightList, (E_DOOR_LIGHT_COUNT * sizeof(struct E_DoorLight)));
	    break;


	case GEO_CONTEXT_RENDER:;
		Gfx *dlS = alloc_display_list(((4 * E_DOOR_LIGHT_COUNT) + 9) * sizeof(Gfx));
        Gfx *dlH = dlS;
		if (dlS == NULL) { return NULL; }


		gSPDisplayList(dlH++, mat_e_door_light_light_f3d_layer1);
		struct E_DoorLight *doorLight = &sEDoorLightList;
		s32 length = E_DOOR_LIGHT_COUNT;
		while (length--) {
			Vtx *verts = alloc_display_list(4 * sizeof(Vtx));

			vec3s_copy(verts[0].v.ob, doorLight->verts[0]);
			vec3s_copy(verts[1].v.ob, doorLight->verts[1]);
			vec3s_copy(verts[2].v.ob, doorLight->verts[1]);
			vec3s_copy(verts[3].v.ob, doorLight->verts[0]);

			f32 lightLength = ((doorLight->door->oPosY - doorLight->door->oHomeY) * 1.5f);
			s16 sy = (s16)(sins(DEGREES(315)) * lightLength);
			s16 cy = (s16)(coss(DEGREES(315)) * lightLength);
			verts[2].v.ob[0] += sy;
			verts[2].v.ob[2] += cy;
			verts[3].v.ob[0] += sy;
			verts[3].v.ob[2] += cy;
			gSPVertex(dlH++, VIRTUAL_TO_PHYSICAL(verts), 4, 0);

			Mat4 mtxf;
			mtxf_identity(mtxf);
			RENDER_GE(dl_draw_quad_verts_0123, 2.f)
			doorLight++;
		}

		gSPGeometryMode(dlH++, 0, G_LIGHTING);
		gDPSetCycleType(dlH++, G_CYC_1CYCLE);
		gDPSetRenderMode(dlH++, G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2);
		gSPSetGeometryMode(dlH++, G_LIGHTING);
		gSPClearGeometryMode(dlH++, G_TEXTURE_GEN);
		gDPSetCombineLERP(dlH++, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT);
		gSPTexture(dlH++, 65535, 65535, 0, 0, 0);

		gSPEndDisplayList(dlH);

        struct GraphNodeGenerated *graphNode = (struct GraphNodeGenerated *) node;
		SET_GRAPH_NODE_LAYER(graphNode->fnNode.node.flags, LAYER_TRANSPARENT_DECAL);
		return dlS;
	}

	return NULL;
}