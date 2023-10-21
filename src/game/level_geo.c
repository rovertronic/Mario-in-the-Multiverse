#include <ultra64.h>

#include "sm64.h"
#include "rendering_graph_node.h"
#include "mario_misc.h"
#include "skybox.h"
#include "engine/math_util.h"
#include "camera.h"
#include "envfx_snow.h"
#include "level_geo.h"
#include "level_update.h"
#include "ability.h"

/**
 * Geo function that generates a displaylist for environment effects such as
 * snow or jet stream bubbles.
 */
Gfx *geo_envfx_main(s32 callContext, struct GraphNode *node, Mat4 mtxf) {
    Vec3s marioPos;
    Vec3s camFrom;
    Vec3s camTo;
    void *particleList;
    Gfx *gfx = NULL;

    if (callContext == GEO_CONTEXT_RENDER && gCurGraphNodeCamera != NULL) {
        struct GraphNodeGenerated *execNode = (struct GraphNodeGenerated *) node;
        u32 *params = &execNode->parameter; // accessed a s32 as 2 u16s by pointing to the variable and
                                            // casting to a local struct as necessary.

        if (GET_HIGH_U16_OF_32(*params) != gAreaUpdateCounter) {
            s32 snowMode = GET_LOW_U16_OF_32(*params);

            vec3f_to_vec3s(camTo, gCurGraphNodeCamera->focus);
            vec3f_to_vec3s(camFrom, gCurGraphNodeCamera->pos);
            vec3f_to_vec3s(marioPos, gPlayerCameraState->pos);
            particleList = envfx_update_particles(snowMode, marioPos, camTo, camFrom);
            if (particleList != NULL) {
                Mtx *mtx = alloc_display_list(sizeof(*mtx));

                gfx = alloc_display_list(2 * sizeof(*gfx));
                mtxf_to_mtx(mtx, mtxf);
                gSPMatrix(&gfx[0], VIRTUAL_TO_PHYSICAL(mtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                gSPBranchList(&gfx[1], VIRTUAL_TO_PHYSICAL(particleList));
                SET_GRAPH_NODE_LAYER(execNode->fnNode.node.flags, LAYER_OCCLUDE_SILHOUETTE_ALPHA);
            }
            SET_HIGH_U16_OF_32(*params, gAreaUpdateCounter);
        }
    } else if (callContext == GEO_CONTEXT_AREA_INIT) {
        // Give these arguments some dummy values. Not used in ENVFX_MODE_NONE
        vec3s_copy(camTo, gVec3sZero);
        vec3s_copy(camFrom, gVec3sZero);
        vec3s_copy(marioPos, gVec3sZero);
        envfx_update_particles(ENVFX_MODE_NONE, marioPos, camTo, camFrom);
    }

    return gfx;
}

/**
 * Geo function that generates a displaylist for the skybox. Can be assigned
 * as the function of a GraphNodeBackground.
 */
Gfx *geo_skybox_main(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    Gfx *gfx = NULL;
    struct GraphNodeBackground *backgroundNode = (struct GraphNodeBackground *) node;

    if (callContext == GEO_CONTEXT_AREA_LOAD) {
        backgroundNode->unused = 0;
#ifndef L3DEX2_ALONE
    } else if (callContext == GEO_CONTEXT_RENDER) {
        struct GraphNodeCamera *camNode = (struct GraphNodeCamera *) gCurGraphNodeRoot->views[0];
        struct GraphNodePerspective *camFrustum =
            (struct GraphNodePerspective *) camNode->fnNode.node.parent;
        gfx = create_skybox_facing_camera(0, backgroundNode->background, camFrustum->fov, gLakituState.pos, gLakituState.focus);
#endif
    }

    return gfx;
}

//course O uv light
#include "levels/o/header.inc.h"
extern Gfx o_spooky_sky_Sphere_001_mesh[];

Vtx *uv_light_vtx_list[] = {
    o_dl_zuvlight_mesh_layer_5_vtx_0,
    o_dl_zuvlight_mesh_layer_5_vtx_1,
    o_dl_zuvlight_mesh_layer_5_vtx_2,
    o_dl_zuvlight_mesh_layer_5_vtx_3,
    o_dl_zuvlight_mesh_layer_5_vtx_4,
};

u16 uv_light_vtx_list_sizes[] = {
    sizeof(o_dl_zuvlight_mesh_layer_5_vtx_0),
    sizeof(o_dl_zuvlight_mesh_layer_5_vtx_1),
    sizeof(o_dl_zuvlight_mesh_layer_5_vtx_2),
    sizeof(o_dl_zuvlight_mesh_layer_5_vtx_3),
    sizeof(o_dl_zuvlight_mesh_layer_5_vtx_4),
};

Gfx cool_display_list[4];
Mtx cool_matrix;
Gfx *geo_update_uv_lights(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    s32 i;
    f32 dist;
    s32 light;
    Vtx *vert;
    Vec3s marioPos;

    if (callContext == GEO_CONTEXT_RENDER) {
        vec3f_to_vec3s(marioPos, gMarioState->pos);

        for (int j = 0; j<5; j++) {
            vert = segmented_to_virtual(uv_light_vtx_list[j]);
            if (using_ability(ABILITY_GADGET_WATCH)) {
                //uv light on
                for (i = 0; i < uv_light_vtx_list_sizes[j] / sizeof(o_dl_zuvlight_mesh_layer_5_vtx_0[0]); i++) {
                    dist = sqrtf((marioPos[0] - vert[i].v.ob[0]) * (marioPos[0] - vert[i].v.ob[0]) + 
                                 (marioPos[1] - vert[i].v.ob[1]) * (marioPos[1] - vert[i].v.ob[1]) + 
                                 (marioPos[2] - vert[i].v.ob[2]) * (marioPos[2] - vert[i].v.ob[2]));

                    light = 255 - (dist/4);
                    if (light < 0) {
                        light = 0;
                    }
                    vert[i].v.cn[3] = light;
                }
            } else {
                //uv light off
                for (i = 0; i < uv_light_vtx_list_sizes[j] / sizeof(o_dl_zuvlight_mesh_layer_5_vtx_0[0]); i++) {
                    vert[i].v.cn[3] = 0;
                }
            }

            guTranslate(&cool_matrix, gLakituState.curPos[0], gLakituState.curPos[1], gLakituState.curPos[2]);

            gSPMatrix(&cool_display_list[0], &cool_matrix, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
            gSPDisplayList(&cool_display_list[1], segmented_to_virtual(o_spooky_sky_Sphere_001_mesh));
            gSPPopMatrix(&cool_display_list[2], G_MTX_MODELVIEW);
            gSPEndDisplayList(&cool_display_list[3]);

            geo_append_display_list(cool_display_list, LAYER_FORCE);
        }

    }
    return NULL;
}