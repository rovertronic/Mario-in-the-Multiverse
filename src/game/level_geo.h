#ifndef LEVEL_GEO_H
#define LEVEL_GEO_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>
//--E
#include "src/game/e__shotgun_effects.h"
#include "src/game/e__door_light.h"
#include "src/game/e__c9_dobj.h"

enum EnvFxMode {
    /* 0*/ ENVFX_MODE_NONE,         // no effects
    /* 1*/ ENVFX_SNOW_NORMAL,       // CCM, SL
    /* 2*/ ENVFX_SNOW_WATER,        // Secret Aquarium, Sunken Ship
    /* 3*/ ENVFX_SNOW_BLIZZARD,     // unused
    /*10*/ ENVFX_BUBBLE_START = 10, // Separates snow effects and flower/bubble effects
    /*11*/ ENVFX_FLOWERS,           // unused
    /*12*/ ENVFX_LAVA_BUBBLES,      // LLL, BitFS, Bowser 2
    /*13*/ ENVFX_WHIRLPOOL_BUBBLES, // DDD
    /*14*/ ENVFX_JETSTREAM_BUBBLES  // JRB, DDD (submarine area)
};

Gfx *geo_envfx_main(s32 callContext, struct GraphNode *node, Mat4 mtxf);
Gfx *geo_skybox_main(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx);
Gfx *geo_update_uv_lights(s32 callContext, struct GraphNode *node, UNUSED void *context);
Gfx *geo_update_j_invisible_path_2(s32 callContext, struct GraphNode *node, UNUSED void *context);
Gfx *geo_update_h_sky(s32 callContext, struct GraphNode *node, UNUSED void *context);
Gfx *geo_zbuffer_clear(s32 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 *mtx);
Gfx *geo_update_f_sky(s32 callContext, struct GraphNode *node, UNUSED void *context);
Gfx *geo_update_f_sky2(s32 callContext, struct GraphNode *node, UNUSED void *context);
Gfx *geo_update_hub_sky(s32 callContext, struct GraphNode *node, UNUSED void *context);
Gfx *geo_update_l_sky(s32 callContext, struct GraphNode *node, UNUSED void *context);
Gfx *geo_update_bowser_course_invisible_path(s32 callContext, struct GraphNode *node, UNUSED void *context);
Gfx *geo_update_bowser_course_sky(s32 callContext, struct GraphNode *node, UNUSED void *context);
Gfx *geo_update_k_sky(s32 callContext, struct GraphNode *node, UNUSED void *context);
Gfx *geo_colorful_env(s32 callContext, struct GraphNode *node, UNUSED void *context);
Gfx *geo_colorful_env_lite(s32 callContext, struct GraphNode *node, UNUSED void *context);
Gfx *geo_update_k_rainbow_triangles(s32 callContext, struct GraphNode *node, UNUSED void *context);
Gfx *geo_update_sb_sky(s32 callContext, struct GraphNode *node, UNUSED void *context);

#endif // LEVEL_GEO_H
