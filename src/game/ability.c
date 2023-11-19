#include <ultra64.h>
#include "geo_commands.h"

//Menu stuff
#include "actors/common1.h"
#include "area.h"
#include "audio/external.h"
#include "camera.h"
#include "course_table.h"
#include "dialog_ids.h"
#include "engine/math_util.h"
#include "eu_translation.h"
#include "segment_symbols.h"
#include "game_init.h"
#include "gfx_dimensions.h"
#include "ingame_menu.h"
#include "level_update.h"
#include "levels/castle_grounds/header.h"
#include "memory.h"
#include "print.h"
#include "save_file.h"
#include "segment2.h"
#include "segment7.h"
#include "seq_ids.h"
#include "sm64.h"
#include "types.h"
#include "config.h"
#include "puppycam2.h"
#include "main.h"
#include "levels/castle_inside/header.h"
//Object stuff
#include "behavior_actions.h"
#include "behavior_data.h"
#include "engine/behavior_script.h"
#include "engine/surface_collision.h"
#include "envfx_bubbles.h"
#include "interaction.h"
#include "level_misc_macros.h"
#include "level_table.h"
#include "mario.h"
#include "mario_actions_cutscene.h"
#include "mario_misc.h"
#include "obj_behaviors.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "rendering_graph_node.h"
#include "spawn_object.h"
#include "spawn_sound.h"
#include "rumble_init.h"
#include "puppylights.h"
#include "actors/group0.h"

#include "text_strings.h"

#include "mitm_hub.h"
#include "ability.h"

// Ability specific variables
u16 aku_invincibility = 0;
u8 phasewalk_state = 0;
u16 phasewalk_timer = 0;
u16 chronos_timer = 0;
u8 chronos_expended = FALSE;
//

Gfx gfx_ability_hand[2] = {gsSPDisplayList(mario_right_hand_closed),gsSPEndDisplayList()};
Gfx gfx_ability_hat[2] = {gsSPEndDisplayList()};

//Graphics data for abilities
ALIGNED8 u8 ability_images[][2048] = {
    { /*Default*/
    #include "actors/ability_images/custom_ability_default.rgba16.inc.c"
    },
    { /*Ability G*/
    #include "actors/ability_images/custom_ability_g.rgba16.inc.c"
    },
    { /*Ability A*/
    #include "actors/ability_images/custom_ability_a.rgba16.inc.c"
    },
    { /*Ability C*/
    #include "actors/ability_images/custom_ability_c.rgba16.inc.c"
    },
    { /*Ability I*/
    #include "actors/ability_images/custom_ability_i.rgba16.inc.c"
    },
    { /*Ability H*/
    #include "actors/ability_images/custom_ability_h.rgba16.inc.c"
    },
    { /*Ability B*/
    #include "actors/ability_images/custom_ability_b.rgba16.inc.c"
    },
    { /*Ability L*/
    #include "actors/ability_images/custom_ability_l.rgba16.inc.c"
    },
    { /*Ability K*/
    #include "actors/ability_images/custom_ability_k.rgba16.inc.c"
    },
    { /*Ability E*/
    #include "actors/ability_images/custom_ability_e.rgba16.inc.c"
    },
    { /*Ability F*/
    #include "actors/ability_images/custom_ability_f.rgba16.inc.c"
    },
    { /*Ability J*/
    #include "actors/ability_images/custom_ability_j.rgba16.inc.c"
    },
    { /*Ability D*/
    #include "actors/ability_images/custom_ability_d.rgba16.inc.c"
    },
    { /*Ability O*/
    #include "actors/ability_images/custom_ability_o.rgba16.inc.c"
    },
    { /*Ability N*/
    #include "actors/ability_images/custom_ability_n.rgba16.inc.c"
    },
    { /*Ability M*/
    #include "actors/ability_images/custom_ability_m.rgba16.inc.c"
    },
    {/*Locked*/
    #include "actors/ability_images/custom_ability_locked.rgba16.inc.c"
    }
};

u8 abstr_def[] = {TEXT_ABILITY_DEFAULT};
u8 abstr_a[] = {TEXT_ABILITY_A};
u8 abstr_b[] = {TEXT_ABILITY_B};
u8 abstr_c[] = {TEXT_ABILITY_C};
u8 abstr_d[] = {TEXT_ABILITY_D};
u8 abstr_e[] = {TEXT_ABILITY_E};
u8 abstr_f[] = {TEXT_ABILITY_F};
u8 abstr_g[] = {TEXT_ABILITY_G};
u8 abstr_h[] = {TEXT_ABILITY_H};
u8 abstr_i[] = {TEXT_ABILITY_I};
u8 abstr_j[] = {TEXT_ABILITY_J};
u8 abstr_k[] = {TEXT_ABILITY_K};
u8 abstr_l[] = {TEXT_ABILITY_L};
u8 abstr_m[] = {TEXT_ABILITY_M};
u8 abstr_n[] = {TEXT_ABILITY_N};
u8 abstr_o[] = {TEXT_ABILITY_O};

struct ability ability_struct[] = {
    /*           HAND DISPLAY LIST        HAT DISPLAY LIST     MARIO MODEL ID     STRING */
    /*Default*/{&mario_right_hand_closed  , NULL               ,MODEL_MARIO       ,&abstr_def},
    /*G*/      {&mario_right_hand_closed  , &cutter_hat_Circle_mesh_layer_1               ,MODEL_MARIO       ,&abstr_g  },
    /*A*/      {&net_hand_2_hand_mesh     , &bubble_hat_bhat_mesh               ,MODEL_MARIO       ,&abstr_a  },
    /*C*/      {&mario_right_hand_closed  , &squid_hat_lunette_mesh               ,MODEL_MARIO       ,&abstr_c  },
    /*I*/      {&rocket_hand_RaymanMissile_mesh_layer_1, NULL  ,MODEL_MARIO       ,&abstr_i  },
    /*H*/      {&phasewalk_hand_hand_mesh , NULL               ,MODEL_MARIO       ,&abstr_h  },
    /*B*/      {&bigdaddyhand_Plane_mesh  , bigdaddyhat_bigdaddy_mesh               ,MODEL_MARIO       ,&abstr_b  },
    /*L*/      {&mario_right_hand_closed  , NULL               ,MODEL_KNIGHT_MARIO,&abstr_l  },
    /*K*/      {&mario_right_hand_closed  , NULL               ,MODEL_MARIO_K     ,&abstr_k  },
    /*E*/      {&mario_right_hand_closed  , NULL               ,MODEL_E__MARIO    ,&abstr_e  },
    /*F*/      {&hand_f_hand_mesh         , &hat_f_hat_mesh    ,MODEL_MARIO       ,&abstr_f  },
    /*J*/      {&pokeball_hand_hand_mesh  , NULL               ,MODEL_MARIO       ,&abstr_j  },
    /*D*/      {&mario_right_hand_closed  , ability_d_mask_hat_mesh ,MODEL_MARIO       ,&abstr_d  },
    /*O*/      {&saw_hand_skinned_016_mesh, NULL               ,MODEL_MARIO       ,&abstr_o  },
    /*N*/      {&mario_right_hand_closed  , NULL               ,MODEL_MARIO       ,&abstr_n  },
    /*M*/      {&hand_m_hand_mesh         , NULL               ,MODEL_MARIO       ,&abstr_m  },
};

u16 ability_cooldown_flags = 0; //Flags that determine if their ability icon is "greyed out" or not; 0 = normal, 1 = cooling down

void render_ability_icon(u16 x, u16 y, u8 alpha, u8 index) {
    if (ability_is_cooling_down(index)) {
        alpha = 100+(sins(gGlobalTimer*0x600)*30);
    }

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, alpha);
    create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);

	gDPPipeSync(gDisplayListHead++);
    gDPSetTextureFilter(gDisplayListHead++,G_TF_POINT);
	gDPSetTextureImage(gDisplayListHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, &ability_images[index]);
	gDPSetTile(gDisplayListHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0);
	gDPLoadBlock(gDisplayListHead++,7, 0, 0, 1023, 256);

    gSPDisplayList(gDisplayListHead++,ability_ability_mesh);
    
    gDPSetTextureFilter(gDisplayListHead++,G_TF_BILERP);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

Gfx *geo_ability_material(s32 callContext, struct GraphNode *node, void *context) {
    Gfx *dlStart, *dlHead;
    struct Object *obj;
    struct GraphNodeGenerated *currentGraphNode;

    currentGraphNode = node;

    if (callContext == GEO_CONTEXT_RENDER) {
        obj = (struct Object *) gCurGraphNodeObject;
        currentGraphNode->fnNode.node.flags = (currentGraphNode->fnNode.node.flags & 0xFF) | (LAYER_ALPHA << 8);

        dlHead = alloc_display_list(sizeof(Gfx) * (11));
        dlStart = dlHead;

        gDPPipeSync(dlHead++);
        gDPSetTextureFilter(dlHead++,G_TF_POINT);
        gDPSetCombineLERP(dlHead++,0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0);
        gSPTexture(dlHead++,65535, 65535, 0, 0, 1);
        gDPSetTextureImage(dlHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, ability_images[obj->oBehParams2ndByte]);
        gDPSetTile(dlHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0);
        gDPLoadBlock(dlHead++,7, 0, 0, 1023, 256);
        gDPSetTile(dlHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0);
        gDPSetTileSize(dlHead++,0, 0, 0, 124, 124);
        gSPEndDisplayList(dlHead++);
    }
    return dlStart;
}

//DPAD ORDER: UP, RIGHT, DOWN, LEFT
s8 ability_y_offset[4] = {0,0,0,0};
s8 ability_gravity[4] = {0,0,0,0};
u8 ability_slot[4] = {ABILITY_DEFAULT,ABILITY_DEFAULT,ABILITY_DEFAULT,ABILITY_DEFAULT};

void render_ability_dpad(s16 x, s16 y, u8 alpha) {
    u8 i;

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, alpha);
    create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gSPDisplayList(gDisplayListHead++, dpad_dpad_mesh);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    render_ability_icon(x,y+30+ability_y_offset[0],alpha,ability_slot[0]);
    render_ability_icon(x+30,y+ability_y_offset[1],alpha,ability_slot[1]);
    render_ability_icon(x,y-30+ability_y_offset[2],alpha,ability_slot[2]);
    render_ability_icon(x-30,y+ability_y_offset[3],alpha,ability_slot[3]);

    for (i=0;i<4;i++){
        if (ability_y_offset[i] > 0) {
            ability_y_offset[i] += ability_gravity[i];
            ability_gravity[i] -= 1;
        }
        //Not an else to prevent sinking into the ground
        if (ability_y_offset[i] <= 0) {
            ability_gravity[i] = 0;
            ability_y_offset[i] = 0;
        }
    }
}

void change_ability(s8 picked_ability) {
    // Set Mario's Ability Variable
    gMarioState->abilityId = picked_ability;

    // Hand Display List
    gSPDisplayList(&gfx_ability_hand[0], ability_struct[gMarioState->abilityId].hand);
    gSPEndDisplayList(&gfx_ability_hand[1]);

    //Hat Display List
    if (ability_struct[gMarioState->abilityId].hat == NULL) {
        gSPEndDisplayList(&gfx_ability_hat[0]);
    } else {
        gSPDisplayList(&gfx_ability_hat[0], ability_struct[gMarioState->abilityId].hat);
        gSPEndDisplayList(&gfx_ability_hat[1]);
    }

    // Mario Model
    gMarioObject->header.gfx.sharedChild = gLoadedGraphNodes[ability_struct[gMarioState->abilityId].model_id];

    // Equip Sound Effect
    switch(gMarioState->abilityId) {
        case ABILITY_AKU:
            play_sound(SOUND_ABILITY_AKU_AKU, gGlobalSoundSource);
        break;
        case ABILITY_KNIGHT:
            play_sound(SOUND_ABILITY_KNIGHT_EQUIP, gGlobalSoundSource);
        break;
    }
}

void control_ability_dpad(void) {
    s8 picked_ability = -1;

    if (gPlayer1Controller->buttonPressed & U_JPAD) {
        picked_ability = 0;
    }
    if (gPlayer1Controller->buttonPressed & R_JPAD) {
        picked_ability = 1;
    }
    if (gPlayer1Controller->buttonPressed & D_JPAD) {
        picked_ability = 2;
    }
    if (gPlayer1Controller->buttonPressed & L_JPAD) {
        picked_ability = 3;
    }
    if ((picked_ability > -1)&&((gMarioState->action & ACT_GROUP_MASK) != ACT_GROUP_CUTSCENE)) {
        // Animate image on DPad HUD
        ability_y_offset[picked_ability] = 5;
        ability_gravity[picked_ability] = 2;

        change_ability(ability_slot[picked_ability]);
    }
}

u8 using_ability(u8 ability_id) {
    return (gMarioState->abilityId == ability_id);
}

u8* ability_string(u8 ability_id) {
    return (ability_struct[ability_id].string);
}

u16 ability_is_cooling_down(u8 ability_id) {
    return (ability_cooldown_flags & (1<<ability_id));
}

u8 cool_down_ability(u8 ability_id) {
    ability_cooldown_flags |= (1<<ability_id);
}

u8 ability_ready(u8 ability_id) {
    ability_cooldown_flags &= ~(1<<ability_id);
}


//--E

//graph
struct AnimInfo gE_UpperAnimInfo = { 0 };//Some of this might not be necessary, but optimization isn't the goal. Might polish this later on after MitM
u8   gE_UpperAnimType      = 0;
s16  gE_UpperAnimFrame     = 0;
u16 *gE_UpperAnimAttribute = NULL;
s16 *gE_UpperAnimData      = NULL;

s16 gE_UpperAimPitch = 0;
s16 gE_UpperAimYaw   = 0;

//behavior
s8 gE_ShotgunTimer = 0;
u8 gE_ShotgunFlags = 0x00;
u8 gE_MaxObjsHitPerShot = 8;


/**
 * Returns whether the current frame can unfreeze itself, for Axo's Chronos
 * ability's time slow mechanic. Always true if time slow is not active.
 * Otherwise, it will only unfreeze every ABILITY_CHRONOS_SLOW_SPLIT frames.
 * This uses static variables for optimization, so that the modulo operation
 * is not run more than once per frame.
 */
u8 ability_chronos_frame_can_progress(void) {
    static u8 frameCounter = 0;
    static u8 curFrame = 0;

    if (!gMarioState->abilityChronosTimeSlowActive) {
        return TRUE;
    }
    else if (curFrame != gGlobalTimer) {
        curFrame = gGlobalTimer;
        frameCounter = curFrame % ABILITY_CHRONOS_SLOW_SPLIT;
    }

    return frameCounter == 0;
}

/**
 * Returns the current factor by which to slow time at, if at all.
 */
f32 ability_chronos_current_slow_factor(void) {
    return gMarioState->abilityChronosTimeSlowActive ? ABILITY_CHRONOS_SLOW_FACTOR : 1.0f;
}
