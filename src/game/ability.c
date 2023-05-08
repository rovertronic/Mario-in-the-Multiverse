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

#include "text_strings.h" //IGNORE THIS ERROR, make -j AGAIN

#include "mitm_hub.h"
#include "ability.h"

Gfx gfx_ability_hand[2] = {gsSPDisplayList(mario_right_hand_closed),gsSPEndDisplayList()};
Gfx gfx_ability_hat[2] = {gsSPEndDisplayList()};

//Graphics data for abilities
ALIGNED8 u8 ability_images[][2048] = {
    { /*Default*/
    #include "actors/ability_images/custom_ability_default.rgba16.inc.c"
    },
    { /*Ability A*/
    #include "actors/ability_images/custom_ability_a.rgba16.inc.c"
    },
    { /*Ability B*/
    #include "actors/ability_images/custom_ability_b.rgba16.inc.c"
    },
    { /*Ability C*/
    #include "actors/ability_images/custom_ability_c.rgba16.inc.c"
    },
    { /*Ability D*/
    #include "actors/ability_images/custom_ability_d.rgba16.inc.c"
    },
    { /*Ability E*/
    #include "actors/ability_images/custom_ability_e.rgba16.inc.c"
    },
    { /*Ability F*/
    #include "actors/ability_images/custom_ability_f.rgba16.inc.c"
    },
    { /*Ability G*/
    #include "actors/ability_images/custom_ability_g.rgba16.inc.c"
    },
    { /*Ability H*/
    #include "actors/ability_images/custom_ability_h.rgba16.inc.c"
    },
    { /*Ability I*/
    #include "actors/ability_images/custom_ability_i.rgba16.inc.c"
    },
    { /*Ability J*/
    #include "actors/ability_images/custom_ability_j.rgba16.inc.c"
    },
    { /*Ability K*/
    #include "actors/ability_images/custom_ability_k.rgba16.inc.c"
    },
    { /*Ability L*/
    #include "actors/ability_images/custom_ability_l.rgba16.inc.c"
    },
    { /*Ability M*/
    #include "actors/ability_images/custom_ability_m.rgba16.inc.c"
    },
    { /*Ability N*/
    #include "actors/ability_images/custom_ability_n.rgba16.inc.c"
    },
    { /*Ability O*/
    #include "actors/ability_images/custom_ability_o.rgba16.inc.c"
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
    /*A*/      {&mario_right_hand_closed  , NULL               ,MODEL_MARIO       ,&abstr_a  },
    /*B*/      {&mario_right_hand_closed  , NULL               ,MODEL_MARIO       ,&abstr_b  },
    /*C*/      {&mario_right_hand_closed  , NULL               ,MODEL_MARIO       ,&abstr_c  },
    /*D*/      {&mario_right_hand_closed  , NULL               ,MODEL_MARIO       ,&abstr_d  },
    /*E*/      {&mario_right_hand_closed  , NULL               ,MODEL_MARIO       ,&abstr_e  },
    /*F*/      {&mario_right_hand_closed  , NULL               ,MODEL_MARIO       ,&abstr_f  },
    /*G*/      {&mario_right_hand_closed  , &cutter_hat_Circle_mesh_layer_1               ,MODEL_MARIO       ,&abstr_g  },
    /*H*/      {&mario_right_hand_closed  , NULL               ,MODEL_MARIO       ,&abstr_h  },
    /*I*/      {&mario_right_hand_closed  , NULL               ,MODEL_MARIO       ,&abstr_i  },
    /*J*/      {&mario_right_hand_closed  , NULL               ,MODEL_MARIO       ,&abstr_j  },
    /*K*/      {&mario_right_hand_closed  , NULL               ,MODEL_MARIO       ,&abstr_k  },
    /*L*/      {&mario_right_hand_closed  , NULL               ,MODEL_MARIO       ,&abstr_l  },
    /*M*/      {&mario_right_hand_closed  , NULL               ,MODEL_MARIO       ,&abstr_m  },
    /*N*/      {&mario_right_hand_closed  , NULL               ,MODEL_MARIO       ,&abstr_n  },
    /*O*/      {&saw_hand_skinned_016_mesh, NULL               ,MODEL_MARIO       ,&abstr_o  },
};

void render_ability_icon(u16 x, u16 y, u8 alpha, u8 index) {
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, alpha);
    create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);

	gDPPipeSync(gDisplayListHead++);
	gDPSetTextureImage(gDisplayListHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, &ability_images[index]);
	gDPSetTile(gDisplayListHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0);
	gDPLoadBlock(gDisplayListHead++,7, 0, 0, 1023, 256);

    gSPDisplayList(gDisplayListHead++,ability_ability_mesh);
    
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
        gDPSetCombineLERP(dlHead++,0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0);
        gSPTexture(dlHead++,65535, 65535, 0, 0, 1);
        gDPSetTextureImage(dlHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, ability_images[obj->oBehParams2ndByte]);
        gDPSetTile(dlHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0);
        gDPLoadBlock(dlHead++,7, 0, 0, 1023, 256);
        gDPSetTile(dlHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0);
        gDPSetTileSize(dlHead++,0, 0, 0, 124, 124);
        gSPEndDisplayList(dlHead++);

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

    if (picked_ability > -1) {
        // Set Mario's Ability Variable
        gMarioState->abilityId = ability_slot[picked_ability];

        // Animate image on DPad HUD
        ability_y_offset[picked_ability] = 5;
        ability_gravity[picked_ability] = 2;

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
    }
}

u8 using_ability(u8 ability_id) {
    return (gMarioState->abilityId == ability_id);
}

u8* ability_string(u8 ability_id) {
    return (ability_struct[ability_id].string);
}