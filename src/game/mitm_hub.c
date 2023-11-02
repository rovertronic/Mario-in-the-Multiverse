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
#include "text_strings.h"
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
#include "engine/surface_load.h"

#include "mitm_hub.h"
#include "ability.h"

u8 author_string_a[] = {AUTHOR_A};
u8 author_string_b[] = {AUTHOR_B};
u8 author_string_c[] = {AUTHOR_C};
u8 author_string_d[] = {AUTHOR_D};
u8 author_string_e[] = {AUTHOR_E};
u8 author_string_f[] = {AUTHOR_F};
u8 author_string_g[] = {AUTHOR_G};
u8 author_string_h[] = {AUTHOR_H};
u8 author_string_i[] = {AUTHOR_I};
u8 author_string_j[] = {AUTHOR_J};
u8 author_string_k[] = {AUTHOR_K};
u8 author_string_l[] = {AUTHOR_L};
u8 author_string_m[] = {AUTHOR_M};
u8 author_string_n[] = {AUTHOR_N};
u8 author_string_o[] = {AUTHOR_O};

u8 pipe_string_not_enough[] = {TEXT_PIPE_NOT_ENOUGH};
u8 pipe_string_enter[] = {TEXT_PIPE_ENTER};
u8 pipe_string_a[] = {TEXT_PIPE_A};
u8 pipe_string_b[] = {TEXT_PIPE_B};

u8 hub_star_string[] = {0xFA,0xFA,0xFA,0xFA,0xFA,0xFA,0xFA,0xFA,DIALOG_CHAR_TERMINATOR};

//In course order, not alphabetical!
//Only mess with /* Level */ entry, everything else is pre-configured
struct mitm_hub_level hub_levels[] = {
          /* Author */      /* Level */  /*Star Flags*/   /*Star Req*/
    /*G*/ {&author_string_g, LEVEL_G,     COURSE_BOB,      0/*0 */ },
    /*A*/ {&author_string_a, LEVEL_BOB,   COURSE_WF ,      0/*1 */ },
    /*C*/ {&author_string_c, LEVEL_CCM,   COURSE_JRB,      0/*1 */ },
    /*I*/ {&author_string_i, LEVEL_BOB,   COURSE_CCM,      0/*3 */ },
    /*H*/ {&author_string_h, LEVEL_BOB,   COURSE_BBH,      0/*5 */ },
    /*B*/ {&author_string_b, LEVEL_B,     COURSE_HMC,      0/*10*/ },
    /*L*/ {&author_string_l, LEVEL_BOB,   COURSE_LLL,      0/*15*/ },
    /*K*/ {&author_string_k, LEVEL_BOB,   COURSE_SSL,      0/*15*/ },
    /*E*/ {&author_string_e, LEVEL_E,     COURSE_DDD,      0/*20*/ },
    /*F*/ {&author_string_f, LEVEL_F  ,   COURSE_SL ,      0/*20*/ },
    /*J*/ {&author_string_j, LEVEL_J,   COURSE_WDW,      0/*25*/ },
    /*D*/ {&author_string_d, LEVEL_SSL,   COURSE_TTM,      0/*30*/ },
    /*O*/ {&author_string_o, LEVEL_O,     COURSE_THI,      0/*30*/ },
    /*N*/ {&author_string_n, LEVEL_X,     COURSE_TTC,      0/*50*/ },
    /*M*/ {&author_string_m, LEVEL_BOB,   COURSE_RR ,      0/*50*/ },
};

s8 hub_level_index = -1;
s8 hub_dma_index = -1;
f32 hub_titlecard_alpha = 0.0f;

void level_pipe_loop(void) {
    if (gCurrLevelNum != LEVEL_CASTLE) {
        return;
    }

    switch(o->oAction) {
        case 0:
            if ((lateral_dist_between_objects(o, gMarioObject) < 120.0f)&&(gMarioState->pos[1] < o->oPosY+500.0f)&&(gMarioState->pos[1] > o->oPosY)) {
                hub_level_index = o->oBehParams2ndByte;
                gMarioState->interactObj = o;

                if (gMarioState->action != ACT_ENTER_HUB_PIPE) {
                    set_mario_action(gMarioState,ACT_ENTER_HUB_PIPE,0);
                    o->oAction = 1;
                    if (gMarioState->numStars >= hub_levels[o->oBehParams2ndByte].star_requirement) {
                        o->oAction = 3;
                    }
                }
            }

            load_object_collision_model();
        break;
        case 1: // Choose
        case 3: // 
            hub_level_index = o->oBehParams2ndByte;
        case 2: //Cancel

            if (lateral_dist_between_objects(o, gMarioObject) > 120.0f) {
                o->oAction = 0;
            }
            load_object_collision_model();
        break;
        case 4: // Level being entered
            hub_level_index = -1;
        break;
    }
}

void render_mitm_hub_hud(void) {
    u8 *texture = segmented_to_virtual(&title_card_placeholder_title_card_rgba16);
    u8 star_flags = 0;
    s16 i;

    if (hub_level_index > -1) {
        hub_titlecard_alpha = approach_f32_asymptotic(hub_titlecard_alpha,255.0f,0.1f);
    } else {
        hub_titlecard_alpha = approach_f32_asymptotic(hub_titlecard_alpha,0.0f,0.15f);
    }

    if ((hub_level_index != hub_dma_index)&&(hub_level_index > -1)) {
        hub_dma_index = hub_level_index;
        dma_read(texture,(hub_dma_index*65536)+_title_cardSegmentRomStart,(hub_dma_index*65536)+_title_cardSegmentRomStart+65536);
        }

    if (hub_dma_index > -1) {
        create_dl_ortho_matrix();

        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, (u8)hub_titlecard_alpha);

        create_dl_translation_matrix(MENU_MTX_PUSH, 32, 215, 0);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
        gSPDisplayList(gDisplayListHead++, title_card_TitleCardMesh_mesh);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

        create_dl_translation_matrix(MENU_MTX_PUSH, 160, 45, 0);
        gSPDisplayList(gDisplayListHead++, round_box_roundbox_mesh);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, (u8)hub_titlecard_alpha);
        print_generic_string(110,55,hub_levels[hub_dma_index].author);

        if (hub_levels[hub_dma_index].star_requirement <= gMarioState->numStars) {
            //Display Collected Stars
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, (u8)hub_titlecard_alpha);
            star_flags = save_file_get_star_flags(gCurrSaveFileNum-1,COURSE_NUM_TO_INDEX(hub_levels[hub_dma_index].course));

            for (i=0;i<8;i++) {
                if (star_flags & (1<<i)) {
                    hub_star_string[i] = 0xFA;
                } else {
                    hub_star_string[i] = 0xFD;
                }
            }

            print_generic_string(110,40,hub_star_string);
        } else {
            //Not Enough Stars to Enter
            gDPSetEnvColor(gDisplayListHead++, 255, 0, 0, (u8)hub_titlecard_alpha);
            int_to_str(hub_levels[hub_dma_index].star_requirement, &pipe_string_not_enough[10]);
            print_generic_string(110,40,pipe_string_not_enough);
        }

        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, (u8)hub_titlecard_alpha);
        print_generic_string(110,25,pipe_string_enter);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 255, (u8)hub_titlecard_alpha);
        print_generic_string(110,25,pipe_string_a);
        gDPSetEnvColor(gDisplayListHead++, 0, 150, 0, (u8)hub_titlecard_alpha);
        print_generic_string(110,25,pipe_string_b);

        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    }

    hub_level_index = -1;
}

u8 get_hub_level(u8 id) {
    return hub_levels[id].level ;
}