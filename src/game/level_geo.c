#include <ultra64.h>

#include "sm64.h"
#include "engine/graph_node.h"
#include "rendering_graph_node.h"
#include "mario_misc.h"
#include "skybox.h"
#include "engine/math_util.h"
#include "camera.h"
#include "envfx_snow.h"
#include "level_geo.h"
#include "level_update.h"
#include "ability.h"
#include "game_init.h"
#include "buffers/buffers.h"

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


Gfx *geo_update_uv_lights(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    s32 i;
    f32 dist;
    s32 light;
    Vtx *vert;
    Vec3s marioPos;
    u8 blood_on = !gSaveBuffer.menuData.config[SETTINGS_BLOOD];

    if (callContext == GEO_CONTEXT_RENDER) {
        Gfx * cool_display_list = alloc_display_list(sizeof(Gfx)*10);
        Mtx * cool_matrix = alloc_display_list(sizeof(Mtx));

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
                    if ((!blood_on) && j == 3) {
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

            guTranslate(cool_matrix, gCurGraphNodeCamera->pos[0], gCurGraphNodeCamera->pos[1], gCurGraphNodeCamera->pos[2]);

            gSPMatrix(&cool_display_list[0], cool_matrix, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
            gSPDisplayList(&cool_display_list[1], segmented_to_virtual(o_spooky_sky_Sphere_001_mesh));
            gSPPopMatrix(&cool_display_list[2], G_MTX_MODELVIEW);
            gSPEndDisplayList(&cool_display_list[3]);

            geo_append_display_list(cool_display_list, LAYER_FORCE);
        }

    }
    return NULL;
}



//Course J invis path
#include "levels/J/header.inc.h"

Gfx *geo_update_j_invisible_path_2(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    s32 i;
    f32 dist;
    s32 light;
    Vtx *vert;
    Vec3s marioPos;

    if (callContext == GEO_CONTEXT_RENDER) {
        vec3f_to_vec3s(marioPos, gMarioState->pos);

        vert = segmented_to_virtual(&J_dl_InvisiblePlatforms_mesh_layer_5_vtx_0);
        if (using_ability(ABILITY_GADGET_WATCH)) {
            //uv light on
            for (i = 0; i < sizeof(J_dl_InvisiblePlatforms_mesh_layer_5_vtx_0) / sizeof(J_dl_InvisiblePlatforms_mesh_layer_5_vtx_0[0]); i++) {
                dist = sqrtf((marioPos[0] - vert[i].v.ob[0]) * (marioPos[0] - vert[i].v.ob[0]) + 
                                (marioPos[1] - vert[i].v.ob[1]) * (marioPos[1] - vert[i].v.ob[1]) + 
                                (marioPos[2] - vert[i].v.ob[2]) * (marioPos[2] - vert[i].v.ob[2]));

                light = 255 - (dist/5);
                if (light < 0) {
                    light = 0;
                }
                vert[i].v.cn[3] = light;
            }
        } else {
            //uv light off
            for (i = 0; i < sizeof(J_dl_InvisiblePlatforms_mesh_layer_5_vtx_0) / sizeof(J_dl_InvisiblePlatforms_mesh_layer_5_vtx_0[0]); i++) {
                vert[i].v.cn[3] = 0;
            }
        }
    }
    return NULL;
}

//Course H skybox
extern Gfx hsky_Sphere_mesh[];
Gfx *geo_update_h_sky(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    s32 i;
    f32 dist;
    s32 light;
    Vtx *vert;
    Vec3s marioPos;

    if (callContext == GEO_CONTEXT_RENDER) {
        Gfx * cool_display_list = alloc_display_list(sizeof(Gfx)*10);
        Mtx * cool_matrix = alloc_display_list(sizeof(Mtx));

        guTranslate(cool_matrix, gCurGraphNodeCamera->pos[0], gCurGraphNodeCamera->pos[1], gCurGraphNodeCamera->pos[2]);

        gSPMatrix(&cool_display_list[0], cool_matrix, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
        gSPDisplayList(&cool_display_list[1], segmented_to_virtual(hsky_Sphere_mesh));
        gSPPopMatrix(&cool_display_list[2], G_MTX_MODELVIEW);
        gSPEndDisplayList(&cool_display_list[3]);

        geo_append_display_list(cool_display_list, LAYER_FORCE);
    }
    return NULL;
}

Gfx *geo_zbuffer_clear(s32 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 *mtx) {
    Gfx *dl = NULL;
        if (callContext == GEO_CONTEXT_RENDER) {
            struct GraphNodeGenerated *asGenerated = (struct GraphNodeGenerated *) node;
            Gfx *dlHead = NULL;
            dl = alloc_display_list(13 * sizeof(*dl));
            dlHead = dl;
            gDPPipeSync(dlHead++);
            gDPSetRenderMode(dlHead++, G_RM_NOOP, G_RM_NOOP2);
            gDPSetCycleType(dlHead++, G_CYC_FILL);
            gDPSetDepthSource(dlHead++, G_ZS_PIXEL);
            gDPSetDepthImage(dlHead++, gPhysicalZBuffer);
            gDPSetColorImage(dlHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, gPhysicalZBuffer);
            gDPSetFillColor(dlHead++,
                            GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0));
            gDPFillRectangle(dlHead++, 0, gBorderHeight, SCREEN_WIDTH - 1,
                            SCREEN_HEIGHT - 1 - gBorderHeight);
            gDPPipeSync(dlHead++);
            gDPSetCycleType(dlHead++, G_CYC_1CYCLE);
            gDPSetColorImage(dlHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH,
                            gPhysicalFramebuffers[sRenderingFramebuffer]);
            gDPSetScissor(dlHead++, G_SC_NON_INTERLACE, 0, gBorderHeight, SCREEN_WIDTH,
                    SCREEN_HEIGHT - gBorderHeight);
            gSPEndDisplayList(dlHead++);
            SET_GRAPH_NODE_LAYER(asGenerated->fnNode.node.flags, LAYER_OPAQUE);
    }
    return dl;
}

//Course F skybox
extern Gfx fsky_sky_mesh[];
extern Gfx fsky2_fsky2_mesh[];
Gfx *geo_update_f_sky(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    s32 i;
    f32 dist;
    s32 light;
    Vtx *vert;
    Vec3s marioPos;
    Gfx *dl = NULL;

    if (callContext == GEO_CONTEXT_RENDER) {
        Gfx * cool_display_list = alloc_display_list(sizeof(Gfx)*10);
        Mtx * cool_matrix = alloc_display_list(sizeof(Mtx));
        Mtx * cool_matrix_2 = alloc_display_list(sizeof(Mtx));

        guTranslate(cool_matrix, gCurGraphNodeCamera->pos[0], gCurGraphNodeCamera->pos[1], gCurGraphNodeCamera->pos[2]);
        gSPMatrix(&cool_display_list[0], cool_matrix, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
        gSPDisplayList(&cool_display_list[1], segmented_to_virtual(fsky2_fsky2_mesh));
        gSPPopMatrix(&cool_display_list[2], G_MTX_MODELVIEW);

        guTranslate(cool_matrix_2, gCurGraphNodeCamera->pos[0]*.75f, gCurGraphNodeCamera->pos[1]*.75f, gCurGraphNodeCamera->pos[2]*.75f);
        gSPMatrix(&cool_display_list[3], cool_matrix_2, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
        gSPDisplayList(&cool_display_list[4], segmented_to_virtual(fsky_sky_mesh));
        gSPPopMatrix(&cool_display_list[5], G_MTX_MODELVIEW);
        gSPEndDisplayList(&cool_display_list[6]);

        geo_append_display_list(cool_display_list, LAYER_FORCE);

        struct GraphNodeGenerated *asGenerated = (struct GraphNodeGenerated *) node;
        Gfx *dlHead = NULL;
        dl = alloc_display_list(13 * sizeof(*dl));
        dlHead = dl;
        gDPPipeSync(dlHead++);
        gDPSetRenderMode(dlHead++, G_RM_NOOP, G_RM_NOOP2);
        gDPSetCycleType(dlHead++, G_CYC_FILL);
        gDPSetDepthSource(dlHead++, G_ZS_PIXEL);
        gDPSetDepthImage(dlHead++, gPhysicalZBuffer);
        gDPSetColorImage(dlHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, gPhysicalZBuffer);
        gDPSetFillColor(dlHead++,
                        GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0));
        gDPFillRectangle(dlHead++, 0, gBorderHeight, SCREEN_WIDTH - 1,
                        SCREEN_HEIGHT - 1 - gBorderHeight);
        gDPPipeSync(dlHead++);
        gDPSetCycleType(dlHead++, G_CYC_1CYCLE);
        gDPSetColorImage(dlHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH,
                        gPhysicalFramebuffers[sRenderingFramebuffer]);
        gDPSetScissor(dlHead++, G_SC_NON_INTERLACE, 0, gBorderHeight, SCREEN_WIDTH,
                SCREEN_HEIGHT - gBorderHeight);
        gSPEndDisplayList(dlHead++);
        //SET_GRAPH_NODE_LAYER(asGenerated->fnNode.node.flags, LAYER_FORCE);
        geo_append_display_list(dl, LAYER_FORCE);
    }
    return NULL;
}

Gfx *geo_update_f_sky2(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    s32 i;
    f32 dist;
    s32 light;
    Vtx *vert;
    Vec3s marioPos;

    if (callContext == GEO_CONTEXT_RENDER) {
        Gfx * cool_display_list = alloc_display_list(sizeof(Gfx)*10);
        Mtx * cool_matrix = alloc_display_list(sizeof(Mtx));

        guTranslate(cool_matrix, gCurGraphNodeCamera->pos[0], gCurGraphNodeCamera->pos[1], gCurGraphNodeCamera->pos[2]);

        gSPMatrix(&cool_display_list[0], cool_matrix, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
        gSPDisplayList(&cool_display_list[1], segmented_to_virtual(fsky2_fsky2_mesh));
        gSPPopMatrix(&cool_display_list[2], G_MTX_MODELVIEW);
        gSPEndDisplayList(&cool_display_list[3]);

        geo_append_display_list(cool_display_list, LAYER_FORCE);
    }
    return NULL;
}

extern Gfx hubsky_1Solar_Winds_mesh[];
extern Gfx hubsky2_1Solar_Winds_002_mesh[];
Gfx *geo_update_hub_sky(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    s32 i;
    f32 dist;
    s32 light;
    Vtx *vert;
    Vec3s marioPos;

    if (callContext == GEO_CONTEXT_RENDER) {
        Gfx * cool_display_list = alloc_display_list(sizeof(Gfx)*10);
        Mtx * cool_matrix = alloc_display_list(sizeof(Mtx));

        guTranslate(cool_matrix, gCurGraphNodeCamera->pos[0], gCurGraphNodeCamera->pos[1], gCurGraphNodeCamera->pos[2]);

        gSPMatrix(&cool_display_list[0], cool_matrix, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
        gSPDisplayList(&cool_display_list[1], segmented_to_virtual(hubsky_1Solar_Winds_mesh));
        gSPDisplayList(&cool_display_list[2], segmented_to_virtual(hubsky2_1Solar_Winds_002_mesh));
        gSPPopMatrix(&cool_display_list[3], G_MTX_MODELVIEW);
        gSPEndDisplayList(&cool_display_list[4]);

        geo_append_display_list(cool_display_list, LAYER_FORCE);
    }
    return NULL;
}

extern Gfx ptbg_Plane_mesh[];
Gfx *geo_update_l_sky(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    s32 i;
    f32 dist;
    s32 light;
    Vtx *vert;
    Vec3s marioPos;

    if (callContext == GEO_CONTEXT_RENDER) {
        Gfx * cool_display_list = alloc_display_list(sizeof(Gfx)*10);
        Mtx * cool_matrix = alloc_display_list(sizeof(Mtx));

        guTranslate(cool_matrix, gCurGraphNodeCamera->pos[0]-(gMarioState->pos[0]/10.0f), gCurGraphNodeCamera->pos[1]-(gMarioState->pos[1]/10.0f), gCurGraphNodeCamera->pos[2]);

        gSPMatrix(&cool_display_list[0], cool_matrix, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
        gSPDisplayList(&cool_display_list[1], segmented_to_virtual(ptbg_Plane_mesh));
        gSPPopMatrix(&cool_display_list[2], G_MTX_MODELVIEW);
        gSPEndDisplayList(&cool_display_list[3]);

        geo_append_display_list(cool_display_list, LAYER_FORCE);
    }
    return NULL;
}



//Bowser Course invis path
#include "levels/bowser_course/header.inc.h"

Gfx *geo_update_bowser_course_invisible_path(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    s32 i;
    f32 dist;
    s32 light;
    Vtx *vert;
    Vec3s marioPos;

    if (callContext == GEO_CONTEXT_RENDER) {
        vec3f_to_vec3s(marioPos, gMarioState->pos);

        vert = segmented_to_virtual(&bowser_course_dl_zuvlightbc_mesh_layer_5_vtx_0);
        if (using_ability(ABILITY_GADGET_WATCH)) {
            //uv light on
            for (i = 0; i < sizeof(bowser_course_dl_zuvlightbc_mesh_layer_5_vtx_0) / sizeof(bowser_course_dl_zuvlightbc_mesh_layer_5_vtx_0[0]); i++) {
                dist = sqrtf((marioPos[0] - vert[i].v.ob[0]) * (marioPos[0] - vert[i].v.ob[0]) + 
                                (marioPos[1] - vert[i].v.ob[1]) * (marioPos[1] - vert[i].v.ob[1]) + 
                                (marioPos[2] - vert[i].v.ob[2]) * (marioPos[2] - vert[i].v.ob[2]));

                light = 255 - (dist/5);
                if (light < 0) {
                    light = 0;
                }
                vert[i].v.cn[3] = light;
            }
        } else {
            //uv light off
            for (i = 0; i < sizeof(bowser_course_dl_zuvlightbc_mesh_layer_5_vtx_0) / sizeof(bowser_course_dl_zuvlightbc_mesh_layer_5_vtx_0[0]); i++) {
                vert[i].v.cn[3] = 0;
            }
        }
    }
    return NULL;
}

extern Gfx mverses_sky_Sphere_mesh[];
Gfx *geo_update_bowser_course_sky(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    s32 i;
    f32 dist;
    s32 light;
    Vtx *vert;
    Vec3s marioPos;

    if (callContext == GEO_CONTEXT_RENDER) {
        Gfx * cool_display_list = alloc_display_list(sizeof(Gfx)*10);
        Mtx * cool_matrix = alloc_display_list(sizeof(Mtx));

        guTranslate(cool_matrix, gCurGraphNodeCamera->pos[0], gCurGraphNodeCamera->pos[1], gCurGraphNodeCamera->pos[2]);

        gSPMatrix(&cool_display_list[0], cool_matrix, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
        gSPDisplayList(&cool_display_list[1], segmented_to_virtual(mverses_sky_Sphere_mesh));
        gSPPopMatrix(&cool_display_list[2], G_MTX_MODELVIEW);
        gSPEndDisplayList(&cool_display_list[3]);

        geo_append_display_list(cool_display_list, LAYER_FORCE);
    }
    return NULL;
}

//Course K skybox
extern Gfx ksky_ksky_mesh[];
Gfx *geo_update_k_sky(s32 callContext, struct GraphNode *node, UNUSED void *context) {

    if (callContext == GEO_CONTEXT_RENDER) {
        Gfx * cool_display_list = alloc_display_list(sizeof(Gfx)*10);
        Mtx * cool_matrix = alloc_display_list(sizeof(Mtx));

        guTranslate(cool_matrix, gCurGraphNodeCamera->pos[0], gCurGraphNodeCamera->pos[1], gCurGraphNodeCamera->pos[2]);

        gSPMatrix(&cool_display_list[0], cool_matrix, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
        gSPDisplayList(&cool_display_list[1], segmented_to_virtual(ksky_ksky_mesh));
        gSPPopMatrix(&cool_display_list[2], G_MTX_MODELVIEW);
        gSPEndDisplayList(&cool_display_list[3]);

        geo_append_display_list(cool_display_list, LAYER_FORCE);
    }
    return NULL;
}

Gfx *geo_colorful_env(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    if (callContext == GEO_CONTEXT_RENDER) {
        Gfx * colorchange = alloc_display_list(sizeof(Gfx)*2);

        s32 r = 120 + sins(gGlobalTimer*0x50 + 0x0000)*120.0f;
        s32 g = 120 + sins(gGlobalTimer*0x50 + 0x5555)*120.0f;
        s32 b = 120 + sins(gGlobalTimer*0x50 + 0xAAAA)*120.0f;

        gDPSetEnvColor(&colorchange[0],r,g,b,255);
        gSPEndDisplayList(&colorchange[1]);

        geo_append_display_list(colorchange, LAYER_OPAQUE);
        geo_append_display_list(colorchange, LAYER_ALPHA);
        geo_append_display_list(colorchange, LAYER_ALPHA_DECAL);
        geo_append_display_list(colorchange, LAYER_TRANSPARENT_DECAL);
    }
    return NULL;
}

Gfx *geo_colorful_env_lite(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    if (callContext == GEO_CONTEXT_RENDER) {
        Gfx * colorchange = alloc_display_list(sizeof(Gfx)*2);

        s32 r = 225 + sins(gGlobalTimer*0x50 + 0x0000)*25.0f;
        s32 g = 225 + sins(gGlobalTimer*0x50 + 0x5555)*25.0f;
        s32 b = 225 + sins(gGlobalTimer*0x50 + 0xAAAA)*25.0f; 

        gDPSetEnvColor(&colorchange[0],r,g,b,255);
        gSPEndDisplayList(&colorchange[1]);

        geo_append_display_list(colorchange, LAYER_OPAQUE);
        geo_append_display_list(colorchange, LAYER_ALPHA);
        geo_append_display_list(colorchange, LAYER_ALPHA_DECAL);
        geo_append_display_list(colorchange, LAYER_TRANSPARENT_DECAL);
        geo_append_display_list(colorchange, LAYER_TRANSPARENT);
    }
    return NULL;
}

#include "levels/k/header.inc.h"
Gfx *geo_update_k_rainbow_triangles(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    s32 i;
    f32 dist;
    s32 light;
    Vtx *vert;
    Vec3s marioPos;

    vert = segmented_to_virtual(&k_dl_visual_mesh_layer_1_vtx_2);

    s32 br = 180 + sins(gGlobalTimer*0x50 + 0x0000)*30.0f;
    s32 bg = 180 + sins(gGlobalTimer*0x50 + 0x5555)*30.0f;
    s32 bb = 180 + sins(gGlobalTimer*0x50 + 0xAAAA)*30.0f;

    if (callContext == GEO_CONTEXT_RENDER) {
        for (i = 0; i < sizeof(k_dl_visual_mesh_layer_1_vtx_2) / sizeof(k_dl_visual_mesh_layer_1_vtx_2[0]); i++) {
            if (!(vert[i].v.cn[0] == 0 && vert[i].v.cn[1] == 0 && vert[i].v.cn[2] == 0)) {
                s32 offset = vert[i].v.cn[3];
                s32 r = sins((gGlobalTimer+offset)*0x300 + 0x0000)*20.0f;
                s32 g = sins((gGlobalTimer+offset)*0x300 + 0x5555)*20.0f;
                s32 b = sins((gGlobalTimer+offset)*0x300 + 0xAAAA)*20.0f;

                vert[i].v.cn[0] = br+r;
                vert[i].v.cn[1] = bg+g;
                vert[i].v.cn[2] = bb+b;
            }
        }
    }
    return NULL;
}

//Mat4 sb_sky_rotation;
//Mat4 sb_sky_rot_offset;

void mtxf_to_mtx_old(Mtx *dest, Mat4 src) {
#ifdef AVOID_UB
    // Avoid type-casting which is technically UB by calling the equivalent
    // guMtxF2L function. This helps little-endian systems, as well.
    guMtxF2L(src, dest);
#else
    s32 asFixedPoint;
    register s32 i;
    register s16 *a3 = (s16 *) dest;      // all integer parts stored in first 16 bytes
    register s16 *t0 = (s16 *) dest + 16; // all fraction parts stored in last 16 bytes
    register f32 *t1 = (f32 *) src;

    for (i = 0; i < 16; i++) {
        asFixedPoint = *t1++ * (1 << 16); //! float-to-integer conversion responsible for PU crashes
        *a3++ = GET_HIGH_S16_OF_32(asFixedPoint); // integer part
        *t0++ = GET_LOW_S16_OF_32(asFixedPoint);  // fraction part
    }
#endif
}

Mat4 sb_sky_rotation;
Mat4 sb_sky_rot_offset;

Vec3s sb_sky_rot_vel = {0,0,0};

#define MAX_SB_SKY_SPEED 0x100

//SB sky
extern u8 sbsky_envcolor;
extern Gfx sbsky_sbsky_mesh[];
Gfx *geo_update_sb_sky(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    if (callContext == GEO_CONTEXT_CREATE) {
        mtxf_identity(sb_sky_rotation);
    }
    if (callContext == GEO_CONTEXT_RENDER) {
        Gfx * cool_display_list = alloc_display_list(sizeof(Gfx)*10);
        Mtx * cool_matrix = alloc_display_list(sizeof(Mtx));
        Gfx * dl = cool_display_list;

        // Update rotation frame
        sb_sky_rot_vel[0] += ((random_u16()%11)-5)*3;
        sb_sky_rot_vel[1] += ((random_u16()%11)-5)*3;
        sb_sky_rot_vel[2] += ((random_u16()%11)-5)*3;

        sb_sky_rot_vel[0] = CLAMP(sb_sky_rot_vel[0],-MAX_SB_SKY_SPEED,MAX_SB_SKY_SPEED);
        sb_sky_rot_vel[1] = CLAMP(sb_sky_rot_vel[1],-MAX_SB_SKY_SPEED,MAX_SB_SKY_SPEED);
        sb_sky_rot_vel[2] = CLAMP(sb_sky_rot_vel[2],-MAX_SB_SKY_SPEED,MAX_SB_SKY_SPEED);


        mtxf_identity(sb_sky_rot_offset);
        Vec3f zro = {0,0,0};
        mtxf_rotate_xyz_and_translate(sb_sky_rot_offset,zro,sb_sky_rot_vel);

        // Set up sky matrix
        Mat4 sb_sky_matrix;
        mtxf_identity(sb_sky_matrix);
        
        mtxf_mul(sb_sky_rotation,sb_sky_rotation,sb_sky_rot_offset);
        vec3f_normalize(&sb_sky_rotation[0][0]);
        vec3f_normalize(&sb_sky_rotation[1][0]);
        vec3f_normalize(&sb_sky_rotation[2][0]);

        mtxf_copy(sb_sky_matrix,sb_sky_rotation);
        vec3f_copy(&sb_sky_matrix[3][0],gCurGraphNodeCamera->pos);

        mtxf_to_mtx_old(cool_matrix,sb_sky_matrix);

        gSPMatrix(cool_display_list++, cool_matrix, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
        gDPSetEnvColor(cool_display_list++,sbsky_envcolor,sbsky_envcolor,sbsky_envcolor,255);
        gSPDisplayList(cool_display_list++, segmented_to_virtual(sbsky_sbsky_mesh));
        gSPPopMatrix(cool_display_list++, G_MTX_MODELVIEW);
        gSPEndDisplayList(cool_display_list++);

        geo_append_display_list(dl, LAYER_FORCE);
    }
    return NULL;
}