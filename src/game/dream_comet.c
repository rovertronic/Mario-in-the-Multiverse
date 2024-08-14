#include <PR/ultratypes.h>

/*

DREAM COMET

A decomp port of aglab2's code for the blue star mode in SM64: Decades Later
https://github.com/aglab2/sm64asm/blob/master/dl/src/star_radar.cpp

*/


#include "sm64.h"
#include "actors/common1.h"
#include "gfx_dimensions.h"
#include "game_init.h"
#include "level_update.h"
#include "camera.h"
#include "print.h"
#include "ingame_menu.h"
#include "hud.h"
#include "segment2.h"
#include "area.h"
#include "save_file.h"
#include "print.h"
#include "engine/surface_load.h"
#include "engine/math_util.h"
#include "puppycam2.h"
#include "puppyprint.h"
#include "actors/group0.h"
#include "cutscene_manager.h"
#include "mario.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "debug.h"
#include "dialog_ids.h"
#include "engine/behavior_script.h"
#include "engine/geo_layout.h"
#include "engine/surface_collision.h"
#include "helper_macros.h"
#include "interaction.h"
#include "level_table.h"
#include "mario_actions_cutscene.h"
#include "memory.h"
#include "obj_behaviors.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "rendering_graph_node.h"
#include "spawn_object.h"
#include "spawn_sound.h"
#include "ability.h"
#include "dream_comet.h"

extern struct SaveBuffer gSaveBuffer;

s32 level_in_dream_comet_mode(void) {
    return FALSE;
}

u8 get_dream_star_flags(void) {
    return gSaveBuffer.files[gCurrSaveFileNum - 1][0].dreamCatalysts[hub_level_current_index];
}

void set_dream_star(int index) {
    gSaveBuffer.files[gCurrSaveFileNum - 1][0].dreamCatalysts[hub_level_current_index] |= (1 << index);
    gSaveFileModified = TRUE;
}

s32 have_dream_star(int index) {
    return (get_dream_star_flags() & (1 << index));
}

u8 get_dream_star_level_count(void) {
    if (mitm_levels[hub_level_current_index].dream_data == NULL) {
        return 0;
    }
    return mitm_levels[hub_level_current_index].dream_data->dream_star_ct;
}

Texture * star_radar_frames[] = {
    &star_radar_sr1_rgba16,
    &star_radar_sr2_rgba16,
    &star_radar_sr3_rgba16,
    &star_radar_sr4_rgba16,
    &star_radar_sr5_rgba16,
    &star_radar_sr6_rgba16,
    &star_radar_sr7_rgba16,
    &star_radar_sr8_rgba16,
    &star_radar_sr9_rgba16,
    &star_radar_sr10_rgba16,
    &star_radar_sr11_rgba16,
    &star_radar_sr12_rgba16
};
//&star_radar_dc_icon_rgba16

f32 sTimers[8] = { 0 };
f32 verticalCheck(float multi)
{
    /*
    if ((gCurrLevelNum == LEVEL_BITFS)
    || (gCurrLevelNum == LEVEL_BITS)
    || (gCurrLevelNum == LEVEL_BBH && gCurrAreaIndex == 1)
    || (gCurrLevelNum == LEVEL_SSL && gCurrAreaIndex == 3)
    || (gCurrLevelNum == LEVEL_TTC)
    || (gCurrLevelNum == LEVEL_RR)
    )
        return multi;
    else
        return 1.f;
    */
    return 1.f;
}

void render_dream_comet_hud(u8 alpha) {

    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);

    int starsinlevel = get_dream_star_level_count();
    for (int i = 0; i < starsinlevel; i++) {

        if (!have_dream_star(i)) {
            struct Object * star = obj_find_nearest_object_with_behavior_and_bparam2(bhvDreamCatalyst,i);
            if (star) {

                f32 x = star->oPosX - gMarioObject->oPosX;
                f32 y = star->oPosY - gMarioObject->oPosY;
                f32 z = star->oPosZ - gMarioObject->oPosZ;

                f32 d = sqrtf(x * x + y * y * verticalCheck(3.f) + z * z);
                if (d < 100.f)
                    d = 100.f;

                f32 spd = (1200.f / d);
                sTimers[i] += .666f * spd; // go 2/3 the speed of DL because only 12 frames instead of 18

                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, alpha);

                if (spd > 0.11f)
                    gDPSetEnvColor(gDisplayListHead++, 0, 255, 0, alpha);

                if (spd > 0.3f)
                    gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, alpha);

                if (spd > 1.f) {
                    s32 r = 127 + sins(gGlobalTimer*0x600 + 0x0000)*128.0f;
                    s32 g = 127 + sins(gGlobalTimer*0x600 + 0x5555)*128.0f;
                    s32 b = 127 + sins(gGlobalTimer*0x600 + 0xAAAA)*128.0f;
                    gDPSetEnvColor(gDisplayListHead++, r, g, b, alpha);
                }

            } else {
                gDPSetEnvColor(gDisplayListHead++, 255, 0, 0, alpha);
                sTimers[i] = 0.0f;
            }

            s16 curX = 18+(i*17);
            s16 curY = 210;
            gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, star_radar_frames[(int)sTimers[i] % 12]);
            gSPDisplayList(gDisplayListHead++, dl_rgba16_load_tex_block);
            gSPTextureRectangle(gDisplayListHead++, curX << 2, curY << 2, (curX + 16) << 2,
                                (curY + 16) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        } else {
            s16 curX = 18+(i*17);
            s16 curY = 210;
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, alpha);
            gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, &star_radar_dream_catalyst_rgba16);
            gSPDisplayList(gDisplayListHead++, dl_rgba16_load_tex_block);
            gSPTextureRectangle(gDisplayListHead++, curX << 2, curY << 2, (curX + 16) << 2,
                                (curY + 16) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }
    }

    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
}

static struct ObjectHitbox sDreamCatalystHitbox = {
    /* interactType:      */ INTERACT_STAR_OR_KEY,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 80,
    /* height:            */ 50,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

void bhv_dream_catalyst(void) {
    switch(o->oAction) {
        case 0: //decide if i should become active
            if (level_in_dream_comet_mode()) {
                o->oAction = 1;
            } else {
                mark_obj_for_deletion(o);
            }
            break;
        case 1: //init
            if (have_dream_star(o->oBehParams2ndByte)) {
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_TRANSPARENT_STAR];
            } else {
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_DREAM_STAR];
            }
            obj_set_hitbox(o, &sDreamCatalystHitbox);
            o->oAction = 2;
            break;
        case 2: //loop
            o->oFaceAngleYaw += 0x800;
            if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                obj_mark_for_deletion(o);
                o->oInteractStatus = INT_STATUS_NONE;
            }
            break;
    }
}