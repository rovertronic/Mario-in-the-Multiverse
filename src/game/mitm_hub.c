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
#include "buffers/buffers.h"

#include "mitm_hub.h"
#include "ability.h"
#include "hints.h"
#include "dream_comet.h"
#include "lerp.h"

u8 pipe_string_not_enough[] = {TEXT_PIPE_NOT_ENOUGH};
u8 pipe_string_enter[] = {TEXT_PIPE_ENTER};
u8 pipe_string_a[] = {TEXT_PIPE_A};
u8 pipe_string_b[] = {TEXT_PIPE_B};
u8 pipe_string_z[] = {TEXT_PIPE_Z};

u8 hub_star_string[] = {0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,DIALOG_CHAR_TERMINATOR};

mitm_dream_data mitmdd_a = {{ABILITY_DEFAULT,ABILITY_MARBLE,ABILITY_NONE,ABILITY_NONE},5};
mitm_dream_data mitmdd_b = {{ABILITY_DEFAULT,ABILITY_UTIL_MIRROR,ABILITY_BIG_DADDY,ABILITY_NONE},6};
mitm_dream_data mitmdd_c = {{ABILITY_DEFAULT,ABILITY_PHASEWALK,ABILITY_NONE,ABILITY_NONE},5};
mitm_dream_data mitmdd_d = {{ABILITY_DEFAULT,ABILITY_UTIL_MIRROR,ABILITY_AKU,ABILITY_NONE},7};
mitm_dream_data mitmdd_e = {{ABILITY_DEFAULT,ABILITY_UTIL_MIRROR,ABILITY_E_SHOTGUN,ABILITY_NONE},8};
mitm_dream_data mitmdd_f = {{ABILITY_DEFAULT,ABILITY_GADGET_WATCH,ABILITY_PHASEWALK,ABILITY_NONE},6};
mitm_dream_data mitmdd_g = {{ABILITY_DEFAULT,ABILITY_UTIL_MIRROR,ABILITY_NONE,ABILITY_NONE},7};
mitm_dream_data mitmdd_h = {{ABILITY_DEFAULT,ABILITY_UTIL_MIRROR,ABILITY_PHASEWALK,ABILITY_NONE},7};
mitm_dream_data mitmdd_i = {{ABILITY_DEFAULT,ABILITY_CUTTER,ABILITY_NONE,ABILITY_NONE},7};
mitm_dream_data mitmdd_j = {{ABILITY_DEFAULT,ABILITY_BUBBLE_HAT,ABILITY_SQUID,ABILITY_NONE},8};
mitm_dream_data mitmdd_k = {{ABILITY_DEFAULT,ABILITY_UTIL_MIRROR,ABILITY_CHRONOS,ABILITY_NONE},7};
mitm_dream_data mitmdd_l = {{ABILITY_DEFAULT,ABILITY_KNIGHT,ABILITY_NONE,ABILITY_NONE},4};
mitm_dream_data mitmdd_m = {{ABILITY_DEFAULT,ABILITY_UTIL_MIRROR,ABILITY_PHASEWALK,ABILITY_KNIGHT},8};
mitm_dream_data mitmdd_n = {{ABILITY_DEFAULT,ABILITY_E_SHOTGUN,ABILITY_BUBBLE_HAT,ABILITY_NONE},7};
mitm_dream_data mitmdd_o = {{ABILITY_DEFAULT,ABILITY_UTIL_MIRROR,ABILITY_HM_FLY,ABILITY_GADGET_WATCH},8};

//In course order, not alphabetical!
//Only mess with /* Level */ entry, everything else is pre-configured
struct mitm_level_data mitm_levels[] = {
          /* Name, Author(s)*/
          /*Level     StarFlags     StarReq  StartArea  ReturnWarp  StarCt DreamData*/
    /*G*/ {"MARIO SUPER STAR ULTRA", "CowQuack", "CowQuack",
            LEVEL_G,  COURSE_BOB,   0,       3,         20,         8,     &mitmdd_g},
    /*A*/ {"MARIO IN BIKINI BOTTOM", "JoshTheBosh", "JoshTheBosh",
            LEVEL_A,  COURSE_WF,    2,       1,         21,         8,     &mitmdd_a},
    /*C*/ {"PIRANHA PIT", "Drahnokks, Idea by: Woissil", "Drahnokks & Co.",
            LEVEL_C,  COURSE_JRB,   2,       1,         22,         8,     &mitmdd_c},
    /*I*/ {"MUSHROOM HAVOC", "Drahnokks", "Drahnokks",
            LEVEL_I,  COURSE_CCM,   5,       1,         23,         8,     &mitmdd_i},
    /*H*/ {"OPPORTUNITY", "joopii", "joopii",
            LEVEL_H,  COURSE_BBH,   10,       1,         24,         8,     &mitmdd_h },
    /*B*/ {"BIOSHOCK RAPTURE", "furyiousfight", "furyiousfight",
            LEVEL_B,  COURSE_HMC,   15,      1,         25,         8,     &mitmdd_b },
    /*L*/ {"BEYOND THE CURSED PIZZA", "luigiman0640", "luigiman0640",
            LEVEL_L,  COURSE_LLL,   20,      6,         26,         8,     &mitmdd_l },
    /*K*/ {"KATANA MARIO NEW MECCA", "KeyBlader, Ability by: axollyon", "KeyBlader & Co.",
            LEVEL_K,  COURSE_SSL,   20,      2,         27,         8,     &mitmdd_k },
    /*E*/ {"DOOM", "Dorrieal", "Dorrieal",
            LEVEL_E,  COURSE_DDD,   30,      1,         28,         8,     &mitmdd_e },
    /*F*/ {"FROM RUSSIA WITH LOVE", "Aeza", "Aeza",
            LEVEL_F,  COURSE_SL,    30,      1,         29,         8,     &mitmdd_f},
    /*J*/ {"ECRUTEAK CITY", "SpK", "SpK",
            LEVEL_J,  COURSE_WDW,   40,      1,         30,         8,     &mitmdd_j},
    /*D*/ {"NEW N-SANITY ISLAND", "JakeDower", "JakeDower",
            LEVEL_D,  COURSE_TTM,   50,      1,         31,         8,     &mitmdd_d},
    /*O*/ {"SAINTS, SINNERS, & MARIO", "Rovertronic", "Rovertronic",
            LEVEL_O,  COURSE_THI,   50,      1,         32,         8,     &mitmdd_o},
    /*N*/ {"MARIO IN HAMSTERBALL", "LinCrash", "LinCrash",
            LEVEL_N,  COURSE_TTC,   60,      1,         33,         8,     &mitmdd_n},
    /*M*/ {"ENVIRONMENTAL STATION M", "Mel", "Mel",
            LEVEL_M,  COURSE_RR,    60,      1,         34,         8,     &mitmdd_m},
    /*BC*/{"CENTRUM OMNIUM", NULL, NULL,
            LEVEL_BOWSER_COURSE,  COURSE_BITDW, 80, 0,   37,         1,     NULL},
   /*HUB*/{"METAXY ISLES", NULL, NULL,
            NULL,     COURSE_BITFS, 0,       0,         34,         2,     NULL},
    /*PW*/{"PAINTING WORLD", NULL, NULL,
            NULL,     COURSE_NONE,  0,       0,         36,         0,     NULL},
    /*SB*/{"GAPS AND HANDS", NULL, NULL,
            NULL,     COURSE_NONE,  0,       0,         36,         0,     NULL},
    /*MC*/{"Mute City", "BroDute", "BroDute",
            NULL,     COURSE_PSS,  0,        0,         36,         1,     NULL},
    /*BB*/{"Big Blue", "BroDute", "BroDute",
            NULL,     COURSE_WMOTR,  0,        0,       36,         1,     NULL},
};

s8 hub_level_index = -1;
s8 hub_dma_index = -1;
s8 hub_level_current_index = HUBLEVEL_HUB;
f32 hub_titlecard_alpha = 0.0f;

void update_hub_star_string(s8 index_of_hublevel) {
    u8 star_flags = star_flags = save_file_get_star_flags(gCurrSaveFileNum-1,COURSE_NUM_TO_INDEX(mitm_levels[index_of_hublevel].course));
    u8 star_count = mitm_levels[index_of_hublevel].star_count;

    if (dream_comet_enabled && mitm_levels[index_of_hublevel].dream_data) {
        star_flags = get_dream_star_flags(index_of_hublevel);
        star_count = mitm_levels[index_of_hublevel].dream_data->dream_star_ct;
    }

    for (u8 i=0;i<star_count;i++) {
        if (star_flags & (1<<i)) {
            hub_star_string[i] = 0xFA;
        } else {
            hub_star_string[i] = 0xFD;
        }
    }
    hub_star_string[star_count] = DIALOG_CHAR_TERMINATOR;
}

void level_pipe_in_level_loop(void) {
    switch(o->oAction) {
        case 0:
            if ((lateral_dist_between_objects(o, gMarioObject) < 120.0f)&&(gMarioState->pos[1] < o->oPosY+500.0f)&&(gMarioState->pos[1] > o->oPosY)) {
                gMarioState->interactObj = o;

                if (gMarioState->action != ACT_ENTER_HUB_PIPE) {
                    set_mario_action(gMarioState,ACT_ENTER_HUB_PIPE,0);
                    o->oAction = 3;
                }
            }

            load_object_collision_model();
            break;
        case 3: // Choose
        case 2: //Cancel
            if (lateral_dist_between_objects(o, gMarioObject) > 120.0f) {
                o->oAction = 0;
            }
            load_object_collision_model();
            break;
        case 4: // Level being entered
            break;
    }
}

u8 queued_pipe_cutscene = FALSE;

void level_pipe_init(void) {
    queued_pipe_cutscene = FALSE;
    o->oUnk94 = random_u16();

    if (gCurrLevelNum != LEVEL_CASTLE) {
        o->oOpacity = 250;
        return;
    }

    o->oOpacity = 0;
    if (gSaveBuffer.files[gCurrSaveFileNum - 1][0].levels_unlocked & (1 << o->oBehParams2ndByte)) {
        o->oOpacity = 250.0f;
    }
}

void level_pipe_loop(void) {
    o->oUnk94++;
    if (gCurrLevelNum != LEVEL_CASTLE) {
        level_pipe_in_level_loop();
        return;
    }

    if ((gMarioState->numStars >= mitm_levels[o->oBehParams2ndByte].star_requirement)&&(!queued_pipe_cutscene)&&
        !(gSaveBuffer.files[gCurrSaveFileNum - 1][0].levels_unlocked & (1 << o->oBehParams2ndByte))) {
        if (o->oTimer > 30) {
            queued_pipe_cutscene = TRUE;
            o->oAction = 5;
            o->oOpacity = 0;
            gSaveBuffer.files[gCurrSaveFileNum - 1][0].levels_unlocked |= (1 << o->oBehParams2ndByte);
            gSaveFileModified = TRUE;
        }
        return;
    }

    if ((!queued_pipe_cutscene)&&(o->oAction == 5)) {
        //free mario if there is no longer any queued cutscenes
        //and every pipe is satisfied
        o->oAction = 0;
        if (gCamera->cutscene == 1) {
            gCamera->cutscene = 0;
            set_mario_action(gMarioState, ACT_IDLE, 0);
            save_file_do_save(gCurrSaveFileNum - 1);
        }
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
                    #ifdef UNLOCK_ABILITIES_DEBUG
                        mitm_levels[o->oBehParams2ndByte].star_requirement = 0;
                    #endif
                    if (gMarioState->numStars >= mitm_levels[o->oBehParams2ndByte].star_requirement) {
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
            hub_level_current_index = o->oBehParams2ndByte;
            break;

        case 5: // Unlock cutscene
            switch(o->oTimer) {
                case 0:
                    gCamera->cutscene = 1;
                    o->oHomeX = 0.0f;
                    o->oHomeZ = 0.0f;
                    o->oMoveAngleYaw = cur_obj_angle_to_home();
                    //gCamera->cutscene = 1;
                    set_mario_action(gMarioState, ACT_CUTSCENE_CONTROLLED, 0);
                    vec3f_copy(&gLakituState.goalFocus, &o->oPosVec);
                    vec3f_copy(&gLakituState.goalPos, &o->oPosVec);
                    gLakituState.goalPos[0] += sins(o->oMoveAngleYaw)*2000.0f;
                    gLakituState.goalPos[2] += coss(o->oMoveAngleYaw)*2000.0f;

                    gLakituState.goalFocus[1] += 200.0f;
                    gLakituState.goalPos[1] += 2000.0f;
                    break;

                case 15:
                    spawn_object(o, MODEL_STAR, bhvUnlockDoorStar);
                    break;

                case 140:
                    queued_pipe_cutscene = FALSE;
                    break;
            }
            if ((o->oTimer > 30)&&(o->oOpacity < 240)) {
                o->oOpacity+=3;
            }
            break;
    }
}

extern const u8 title_card_data[];
void render_mitm_hub_hud(void) {
    u8 *texture = segmented_to_virtual(&title_card_placeholder_title_card_rgba16);
    u8 star_flags = 0;
    s16 i;

    char sprintf_buffer[50];

    if (!_60fps_midframe) {
        if (hub_level_index > -1) {
            hub_titlecard_alpha = approach_f32_asymptotic(hub_titlecard_alpha,255.0f,0.1f);
        } else {
            hub_titlecard_alpha = approach_f32_asymptotic(hub_titlecard_alpha,0.0f,0.15f);
        }
    }
    hub_titlecard_alpha = lerp_menu(hub_titlecard_alpha,LMENU_TITLE_CARD);

    if ((hub_level_index != hub_dma_index)&&(hub_level_index > -1)) {
        hub_dma_index = hub_level_index;

        void * rom_location = (hub_dma_index*65536) + ((uintptr_t)title_card_data) ;

        dma_read(texture,rom_location,rom_location+65536);
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

        sprintf(sprintf_buffer,"By: %s", mitm_levels[hub_dma_index].author_abridged);
        print_generic_string_ascii(110,56, sprintf_buffer);

        s16 line_2_y = 40;
        s16 line_3_y = 25;
        if (dream_comet_unlocked()) {
            line_2_y = 43;
            line_3_y = 31;
        }

        if (mitm_levels[hub_dma_index].star_requirement <= gMarioState->numStars) {
            //Display Collected Stars
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, (u8)hub_titlecard_alpha);
            if (dream_comet_enabled) {
                gDPSetEnvColor(gDisplayListHead++, 255, 0, 255, (u8)hub_titlecard_alpha);
            }
            update_hub_star_string(hub_dma_index);
            print_generic_string(110,line_2_y,hub_star_string);
        } else {
            //Not Enough Stars to Enter
            gDPSetEnvColor(gDisplayListHead++, 255, 0, 0, (u8)hub_titlecard_alpha);
            int_to_str(mitm_levels[hub_dma_index].star_requirement, &pipe_string_not_enough[10]);
            print_generic_string(110,line_2_y,pipe_string_not_enough);
        }

        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, (u8)hub_titlecard_alpha);
        print_generic_string(113,line_3_y,pipe_string_enter);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 255, (u8)hub_titlecard_alpha);
        print_generic_string(110,line_3_y,pipe_string_a);
        gDPSetEnvColor(gDisplayListHead++, 0, 150, 0, (u8)hub_titlecard_alpha);
        print_generic_string(109,line_3_y,pipe_string_b);

        if (dream_comet_unlocked()) {
            gDPSetEnvColor(gDisplayListHead++, 255, 0, 255, (u8)hub_titlecard_alpha);
            if (dream_comet_enabled) {
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, (u8)hub_titlecard_alpha);
            }
            print_generic_string(120,18,pipe_string_z);

            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, (u8)hub_titlecard_alpha);
            if (dream_comet_enabled) {
                print_generic_string_ascii(120,18,"  :Standard");
            } else {
                print_generic_string_ascii(120,18,"  :Dream");
            }
        }

        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    }

    if (!_60fps_midframe) {
        hub_level_index = -1;
    }
}

void render_mitm_return_to_hub_hud(void) {
    if (gMarioState->action == ACT_ENTER_HUB_PIPE) {
        hub_titlecard_alpha = approach_f32_asymptotic(hub_titlecard_alpha,255.0f,0.1f);
    } else {
        hub_titlecard_alpha = approach_f32_asymptotic(hub_titlecard_alpha,0.0f,0.15f);
    }
    if (hub_titlecard_alpha > 1.0f) {
        create_dl_ortho_matrix();

        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, (u8)hub_titlecard_alpha);

        create_dl_translation_matrix(MENU_MTX_PUSH, 160, 45, 0);
        gSPDisplayList(gDisplayListHead++, round_box_roundbox_mesh);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);

        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, (u8)hub_titlecard_alpha);
        print_generic_string_ascii(113,49,"Return To Hub?");
        print_generic_string(113,33,pipe_string_enter);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 255, (u8)hub_titlecard_alpha);
        print_generic_string(110,33,pipe_string_a);
        gDPSetEnvColor(gDisplayListHead++, 0, 150, 0, (u8)hub_titlecard_alpha);
        print_generic_string(109,33,pipe_string_b);

        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    }
}

u8 get_hub_level(u8 id) {
    return mitm_levels[id].level ;
}

u8 get_hub_area(u8 id) {
    return mitm_levels[id].start_area ;
}

u8 get_hub_return_id(u8 id) {
    return mitm_levels[id].return_id;
}

void hub_reset_variables(void) {
    hub_dma_index = -1;
    hub_level_index = -1;
}

// Shop code in here, rendering in hud.c
s8 shop_target_item = -1;
extern u8 shop_show_ui;
extern u8 shop_cant_afford;
extern u8 shop_sold_out;
struct Object * shop_item_objects[5];

s32 try_to_buy(s32 price) {
    if (gMarioState->numGlobalCoins >= price) {
        gMarioState->numGlobalCoins -= price;
        shop_sold_out = TRUE;
        return TRUE;
    } else {
        shop_cant_afford = TRUE;
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
    }
    return FALSE;
}

void bhv_shop_controller(void) {
    u8 sold_out[5];
    sold_out[0] = (save_file_check_ability_unlocked(ABILITY_UTIL_COMPASS) != 0);
    sold_out[1] = (save_file_check_ability_unlocked(ABILITY_UTIL_MIRROR) != 0);
    sold_out[2] = (save_file_check_ability_unlocked(ABILITY_UTIL_MILK) != 0);
    sold_out[3] = (save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_BITFS)) & 1);
    sold_out[4] = ((save_file_get_flags() & SAVE_FLAG_ARTREUS_ARTIFACT) != 0);

    Vec3f camera_target;
    switch(o->oAction) {
        case 0: // Init
            o->oAction = 1;
            shop_target_item = -1;
            shop_cant_afford = FALSE;
            shop_show_ui = FALSE;
            shop_sold_out = FALSE;
            break;

        case 1: // Wait for mario
            if ((lateral_dist_between_objects(gMarioObject,o) < 800.0f)&&(gMarioState->pos[1] > o->oPosY-50.0f)&&(gMarioState->pos[1] < o->oPosY+50.0f)) {
                o->oAction = 2;
                gCamera->cutscene = 1;
                set_mario_action(gMarioState, ACT_CUTSCENE_CONTROLLED, 0);
                shop_show_ui = TRUE;
                shop_cant_afford = FALSE;
                shop_sold_out = FALSE;
            }
            for (s32 i = 0; i < 5; i++) {
                shop_item_objects[i]->oFaceAngleYaw += 0x100;
                if (sold_out[i]) {
                    shop_item_objects[i]->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
                }
            }
            break;

        case 2: // In-Shop

            // Pos
            o->oFaceAngleYaw = obj_angle_to_object(o,gMarioObject);
            gLakituState.goalPos[0] = o->oPosX + sins(o->oFaceAngleYaw) * 800.0f;
            gLakituState.goalPos[2] = o->oPosZ + coss(o->oFaceAngleYaw) * 800.0f;
            gLakituState.goalPos[1] = o->oPosY + 200.0f;

            // Foc
            vec3f_copy(&camera_target,&o->oPosVec);
            camera_target[1] += 100.0f;
            if (shop_target_item != -1) {
                vec3f_copy(&camera_target,&shop_item_objects[shop_target_item]->oPosVec);
            }
            if (o->oTimer == 0) {
                vec3f_copy(&gLakituState.goalFocus,&camera_target);
            }
            for (s32 i = 0; i < 3; i++) {
                gLakituState.goalFocus[i] = approach_f32_asymptotic(gLakituState.goalFocus[i],camera_target[i],0.1f);
            }

            // Control
            if (o->oTimer > 30) {
                s8 old_shop_target_item = shop_target_item;
                handle_menu_scrolling(MENU_SCROLL_INVERTICAL, &shop_target_item, -1, 4);
                if (old_shop_target_item != shop_target_item) {
                    shop_cant_afford = FALSE;
                }
                if (shop_target_item != -1) {
                    shop_sold_out = sold_out[shop_target_item];
                }
            }
            if ((gPlayer1Controller->buttonPressed & (A_BUTTON | START_BUTTON)) && !shop_sold_out) {
                switch(shop_target_item) {
                    case 0:
                        if (try_to_buy(250)) {
                            save_file_unlock_ability(ABILITY_UTIL_COMPASS);
                            save_file_set_coins();
                            play_sound(SOUND_MENU_STAR_SOUND, gMarioState->marioObj->header.gfx.cameraToObject);
                            save_file_do_save(gCurrSaveFileNum - 1);
                        }
                        break;
                    case 1:
                        if (try_to_buy(200)) {
                            save_file_unlock_ability(ABILITY_UTIL_MIRROR);
                            save_file_set_coins();
                            play_sound(SOUND_MENU_STAR_SOUND, gMarioState->marioObj->header.gfx.cameraToObject);
                            save_file_do_save(gCurrSaveFileNum - 1);
                        }
                        break;
                    case 2:
                        if (try_to_buy(350)) {
                            save_file_unlock_ability(ABILITY_UTIL_MILK);
                            save_file_set_coins();
                            play_sound(SOUND_MENU_STAR_SOUND, gMarioState->marioObj->header.gfx.cameraToObject);
                            save_file_do_save(gCurrSaveFileNum - 1);
                        }
                        break;
                    case 3:
                        if (try_to_buy(200)) { // Star
                            save_file_set_coins();

                            shop_target_item = -1;
                            o->oAction = 3;
                            gCamera->cutscene = 0;
                            shop_show_ui = FALSE;

                            gMarioState->interactObj = shop_item_objects[4];
                            gMarioState->usedObj = shop_item_objects[4];
                            set_mario_action(gMarioState, ACT_STAR_DANCE_NO_EXIT, 3);
                            save_file_collect_star_or_key(gMarioState->numCoins, 0);
                            gMarioState->numStars = save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1);
                        }
                        break;
                    case 4:
                        if (try_to_buy(500)) {
                            save_file_set_coins();
                            save_file_set_flags(SAVE_FLAG_ARTREUS_ARTIFACT);
                            play_sound(SOUND_MENU_STAR_SOUND, gMarioState->marioObj->header.gfx.cameraToObject);
                            save_file_do_save(gCurrSaveFileNum - 1);
                        }
                        break;
                }
            } else if (gPlayer1Controller->buttonPressed & (B_BUTTON)) {
                shop_target_item = -1;
                o->oAction = 3;
                gCamera->cutscene = 0;
                set_mario_action(gMarioState, ACT_IDLE, 0);
                shop_show_ui = FALSE;
            }

            // Item Objects
            for (s32 i = 0; i < 5; i++) {
                shop_item_objects[i]->oFaceAngleYaw += 0x200;
                if (i != shop_target_item) {
                    shop_item_objects[i]->oFaceAngleYaw = obj_angle_to_object(o,gMarioObject);
                }
                if (sold_out[i]) {
                    shop_item_objects[i]->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
                }
            }
            break;
        
        case 3: // Wait for mario to move away
            if ((lateral_dist_between_objects(gMarioObject,o) > 900.0f)&&(gMarioState->pos[1] > o->oPosY-50.0f)) {
                o->oAction = 1;
            }
            break;
            
    }
}

void bhv_shopitem_loop(void) {
    switch(o->oAction) {
        case 0:
            switch(o->oBehParams2ndByte) {
                case 0: // Compass
                    o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_SHOPITEM_1];
                    cur_obj_scale(.5f);
                    break;
                case 1: // Magic Mirror
                    o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_SHOPITEM_2];
                    cur_obj_scale(.5f);
                    break;
                case 2: // Lon Lon Milk
                    cur_obj_scale(.75f);
                    o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_SHOPITEM_3];
                    break;
                //case 3: // 121st Star

                //    break;
                case 4: // Atreus' Artifact
                    o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_SHOPITEM_4];
                    break;
            }
            shop_item_objects[o->oBehParams2ndByte] = o;
            o->oAction = 1;
            break;
    }
}

extern u8 hint_show_ui;

u8 hint_index = 0;
u8 hint_level = 0;
u8 hint_ix = 0;
u8 hint_iy = 0;
u8 hint_layer = 0;

extern u16 hud_display_coins;
extern u8 hudbar_coin[];
void render_hint_ui(u8 hud_alpha) {
    char stringBuf[20];

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-hud_alpha);
    create_dl_translation_matrix(MENU_MTX_PUSH, 160, 120, 0);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gSPDisplayList(gDisplayListHead++, hint_menu_roundbox_002_mesh);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);  

    if (hint_layer == 0) {
        create_dl_translation_matrix(MENU_MTX_PUSH, 40+(33*hint_ix), 197-(18*hint_iy), 0);
        gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-hud_alpha);
        print_generic_string_ascii(45, 95, "Need help finding a\npower star?");

        if (gSaveBuffer.files[gCurrSaveFileNum - 1][0].levels_unlocked & (1<<hint_index)) {
            print_generic_string_ascii(45, 56, mitm_levels[hint_index].name);
        }

        for (s32 i = 0; i < 15; i++) {
            u16 unlocked = (gSaveBuffer.files[gCurrSaveFileNum - 1][0].levels_unlocked & (1<<i));
            u8 star_flags = save_file_get_star_flags(gCurrSaveFileNum-1,COURSE_NUM_TO_INDEX(mitm_levels[i].course));
            sprintf(stringBuf,"C%02d",i+1);

            if (star_flags == 0xFF) {
                // level has been filled
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255.0f-hud_alpha);
            } else {
                // level has remaining stars
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-hud_alpha);
            }
            if (!unlocked) {
                // level is locked and undiscovered
                gDPSetEnvColor(gDisplayListHead++, 100, 100, 100, 255.0f-hud_alpha);
            }

            print_generic_string_ascii(50+(33*(i%3)), 197-(18*(i/3)), stringBuf);
        }
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    } else {
        // Hint Abilities
        s32 ability_amount = 0;
        s32 ability_x_offset = 0;
        u32 hint_ability_flags = hintlist[hint_level][hint_index].dependancies;
        u8 star_flags = save_file_get_star_flags(gCurrSaveFileNum-1,COURSE_NUM_TO_INDEX(hint_level+1));

        lerp_ability_icons = FALSE;
        for (s32 i = 0; i < 19; i++) {
            if (hint_ability_flags & (1 << i)) {
                render_ability_icon(59+ability_x_offset, 95, 255, i);
                ability_x_offset += 34;
            }
        }

        // Selection Triangle
        create_dl_translation_matrix(MENU_MTX_PUSH, 40+(50*hint_ix), 197-(18*hint_iy), 0);
        gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

        // Hint Text
        char * hint_text = hintlist[hint_level][hint_index].hint_text;

        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);

        for (s32 i = 0; i < 8; i++) {
            if (star_flags & (1<<i)) {
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255.0f-hud_alpha);
            } else {
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-hud_alpha);
            }
            sprintf(stringBuf,"Star %d",i+1);
            print_generic_string_ascii(50+(50*(i%2)), 197-(18*(i/2)), stringBuf);
        }

        if (star_flags & (1<<hint_index)) {
            gSaveBuffer.files[gCurrSaveFileNum - 1][0].hints_unlocked[hint_level] |= (1<<hint_index);
            if (hint_index == 0 && hint_level == 0) {
                hint_text = "You've got this one!";
            }
        }
        if (!(gSaveBuffer.files[gCurrSaveFileNum - 1][0].hints_unlocked[hint_level] & (1<<hint_index))) {
            hint_text = "Reveal Solution - 20 Coins";
        }

        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-hud_alpha);
        print_generic_string_ascii(43, 58, hint_text);
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

        gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
        int_to_str_000(hud_display_coins, &hudbar_coin[2]);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-hud_alpha);
        if (shop_cant_afford) {
            gDPSetEnvColor(gDisplayListHead++, 255, 126.0f+sins(gGlobalTimer*0x1000)*126.0f, 126.0f+sins(gGlobalTimer*0x1000)*126.0f, 255.0f-hud_alpha);
        }
        print_hud_lut_string(HUD_LUT_GLOBAL, 160, 143, hudbar_coin);
        gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
    }

}

void bhv_morshu_loop(void) {
    o->oFaceAngleYaw = o->oAngleToMario;
}

void bhv_layton_hint_loop(void) {
    s8 old_hint_index;

    o->oAnimState = 0;
    if (o->oTimer%90 < 4) {
        o->oAnimState = 1;
    }
    switch(o->oAction) {
        case 0: // wait
            if (o->oInteractStatus == INT_STATUS_INTERACTED) {
                hint_show_ui = TRUE;
                hint_index = 0;
                hint_layer = 0;
                hint_ix = 0;
                hint_iy = 0;
                hint_level = 0;
                shop_cant_afford = 0;
                o->oAction = 1;
                gCamera->cutscene = 1;

                vec3f_copy(&gLakituState.goalFocus, &o->oPosVec);
                vec3f_copy(&gLakituState.goalPos, &o->oPosVec);
                gLakituState.goalPos[0] += sins(o->oMoveAngleYaw)*800.0f + sins(o->oMoveAngleYaw - 0x4000)*150.0f;
                gLakituState.goalPos[2] += coss(o->oMoveAngleYaw)*800.0f + coss(o->oMoveAngleYaw - 0x4000)*150.0f;

                gLakituState.goalFocus[0] += sins(o->oMoveAngleYaw - 0x4000)*150.0f;
                gLakituState.goalFocus[2] += coss(o->oMoveAngleYaw - 0x4000)*150.0f;

                gLakituState.goalFocus[1] += 140.0f;
                gLakituState.goalPos[1] += 190.0f;

                cur_obj_init_animation_with_sound(1);
            }
            o->oInteractStatus = 0;
        break;
        case 1: // select course
            //handle_menu_scrolling(MENU_SCROLL_INVERTICAL, &shop_target_item, -1, 4);
            handle_menu_scrolling_2way(&hint_ix, &hint_iy, 0, 4, 2);
            hint_index = (hint_iy *3)+(hint_ix%3);
            if (gPlayer1Controller->buttonPressed & (A_BUTTON | START_BUTTON)) {
                if (gSaveBuffer.files[gCurrSaveFileNum - 1][0].levels_unlocked & (1<<hint_index)) {
                    o->oAction = 2;
                    hint_level = hint_index;
                    hint_layer = 1;
                    hint_index = 0;
                    hint_ix = 0;
                    hint_iy = 0;
                    cur_obj_init_animation_with_sound(2);
                } else {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            } else if (gPlayer1Controller->buttonPressed & (B_BUTTON)) {
                set_mario_action(gMarioState, ACT_IDLE, 0);
                gCamera->cutscene = 0;
                hint_show_ui = FALSE;
                o->oAction = 0;
                cur_obj_init_animation_with_sound(0);
            }
        break;
        case 2:
            old_hint_index = hint_index;
            handle_menu_scrolling_2way(&hint_ix, &hint_iy, 0, 3, 1);
            hint_index = (hint_iy*2)+(hint_ix%4);
            if (old_hint_index != hint_index) {
                shop_cant_afford = FALSE;
            }

            if (gPlayer1Controller->buttonPressed & (A_BUTTON | START_BUTTON)) {
                if (!(gSaveBuffer.files[gCurrSaveFileNum - 1][0].hints_unlocked[hint_level] & (1<<hint_index))) {
                    if (gMarioState->numGlobalCoins >= 20) {
                        gSaveBuffer.files[gCurrSaveFileNum - 1][0].hints_unlocked[hint_level] |= (1<<hint_index);
                        gMarioState->numGlobalCoins-=20;
                        save_file_set_coins();
                        play_sound(SOUND_MENU_STAR_SOUND, gMarioState->marioObj->header.gfx.cameraToObject);
                        gSaveFileModified = TRUE;
                        save_file_do_save(gCurrSaveFileNum - 1);
                    } else {
                        shop_cant_afford = TRUE;
                        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                    }
                }
            } else if (gPlayer1Controller->buttonPressed & (B_BUTTON)) {
                o->oAction = 1;
                hint_layer = 0;
                hint_index = 0;
                hint_ix = 0;
                hint_iy = 0;
                shop_cant_afford = 0;

                cur_obj_init_animation_with_sound(1);
            }
        break; // select hint
    }
}

u8 show_mitm_credits = FALSE;
u8 mitm_credits_object_state = 0;
s32 credits_y_offset = 0;

void bhv_credits_slab_loob(void) {
    switch(o->oAction) {
        case 0:
            mitm_credits_object_state = 1;
            o->oAction++;
            break;
    }

    switch(mitm_credits_object_state) {
        case 1: // wait for mario interaction
            if ((o->oDistanceToMario < 250.0f) && (gMarioState->pos[1] < o->oPosY+5.0f)) {
                mitm_credits_object_state = 2;
                show_mitm_credits = TRUE;
                credits_y_offset = 0;
                set_mario_action(gMarioState, ACT_WAITING_FOR_DIALOG, 0);
            }
            break;
        case 2:
            if (gPlayer1Controller->buttonPressed & (B_BUTTON | A_BUTTON | START_BUTTON)) {
                set_mario_action(gMarioState, ACT_IDLE, 0);
                mitm_credits_object_state = 3;
                show_mitm_credits = FALSE;
            }
            break;
        case 3:
            if (o->oDistanceToMario > 1000.0f ) {
                mitm_credits_object_state = 1;
            }
            break;
    }
}

struct mitm_credits_entry {
    char * text;
    u32 color;
};

struct mitm_credits_entry mitm_credits[] = {
    {"Mario in the Multiverse",1},
    {"",0},

    {"Collaboration Host",1},
    {"Rovertronic",2},
    {"",0},

    {"Super Contributors",1},
    {"Super Contributors are collab members",0},
    {"who went above and beyond to contribute",0},
    {"extra on top of initial obligations.",0},
    {"",0},
    {"Drahnokks:",2},
    {"Two Levels",0},
    {"Morshu Model",0},
    {"Mumbo Model",0},
    {"Redd Model",0},
    {"Layton Model",0},
    {"",0},
    {"Aeza:",2},
    {"Hub Model",0},
    {"Castle Model",0},
    {"",0},
    {"CowQuack:",2},
    {"Rope System",0},
    {"Ability Heart Object",0},
    {"",0},
    {"furyiousfight:",2},
    {"Bowser Model",0},
    {"Title Screen Model",0},
    {"MitM Concept",0},
    {"",0},
    {"Dorrieal:",2},
    {"Bullet System",0},
    {"",0},
    {"Abilities",1},
    {"CowQuack",2},
    {"JoshTheBosh",2},
    {"Drahnokks",2},
    {"Joopii",2},
    {"furyiousfight",2},
    {"luigiman0640",2},
    {"axollyon",2},
    {"Dorrieal",2},
    {"Aeza",2},
    {"SpK",2},
    {"JakeDower",2},
    {"lincrash",2},
    {"Mel",2},
    {"",0},

    {"Levels",1},
    {"CowQuack",2},
    {"JoshTheBosh",2},
    {"Drahnokks",2},
    {"Woissil",2},
    {"Joopii",2},
    {"furyiousfight",2},
    {"luigiman0640",2},
    {"KeyBlader",2},
    {"Dorrieal",2},
    {"Aeza",2},
    {"SpK",2},
    {"JakeDower",2},
    {"lincrash",2},
    {"Mel",2},
    //{"BroDute",2},
    {"",0},

    {"Music",1},
    {"Teraok",2},
    {"SpK",2},
    {"sm64pie",2},
    //{"Asbeth",2},
    {"Leonitz",2},
    {"",0},

    {"Title Card Artwork",1},
    {"Leonitz",2},
    {"Erableto",2},
    {"Biobak",2},
    {"",0},

    {"Additional Help",1},
    {"",0},
    {"axollyon",2},
    {"Cover Artwork",0},
    {"Meter System",0},
    {"Humanoid Model & Rig",0},
    {"",0},
    {"MrComit:",2},
    {"MP64 Star Switch Model",0},
    {"",0},
    {"MrComit & Cheezepin:",2},
    {"E.Gadd Model & Animations",0},
    {"",0},
    {"theCozies:",2},
    {"Screen Shaders",0},
    {"",0},
    {"Arthurtilly:",2},
    {"Rigid Body Physics",0},
    {"",0},
    {"Alex-GPTV:",2},
    {"Shotgun Detection Math",0},
    {"",0},
    {"Indigo Dindigo:",2},
    {"Funky Shell Camera Mode",0},
    {"",0},
    {"Biobak:",2},
    {"Bowser's Castle Model",0},
    {"Splatoon Squid Model",0},
    {"Model RAM Optimizations",0},
    {"",0},
    {"Erableto:",2},
    {"Aku Ability Art",0},
    {"",0},
    {"ArcticJaguar725:",2},
    {"Audio Technical Support",0},
    {"",0},
    {"RationaLess:",2},
    {"Atreus Design & Lore",0},
    {"",0},
    {"HackerN64 Team:",2},
    {"HackerSM64",0},

    {"",0},
    {"Club Multiverse Models",1},
    {"",0},
    {"Rovertronic",2},
    {"Kaguya (Angels & Demons)",0},
    {"Ford Early Exit (BONEWORKS)",0},
    {"",0},
    {"CowQuack",2},
    {"Raquna (Etrian Odyssey)",0},
    {"Steve (Minecraft)",0},
    {"",0},
    {"Drahnokks",2},
    {"Mara (Crow Country)",0},
    {"Dixie Kong (Donkey Kong)",0},
    {"",0},
    {"Biobak",2},
    {"Isaac (The Binding of Isaac)",0},
    {"",0},
    {"JakeDower:",2},
    {"Ratchet (Ratchet & Clank)",0},
    {"",0},
    {"furyiousfight",2},
    {"Vincent (Catherine: Full Body)",0},
    {"",0},
    {"RationaLess:",2},
    {"Alex (YIIK: A Post-Modern RPG)",0},
    {"",0},
    {"Thank you for playing!",1},
    {"-The MitM Team",2},
};

f32 clamp2(f32 x) {
  f32 lowerlimit = 0.0f;
  f32 upperlimit = 1.0f;
  if (x < lowerlimit) return lowerlimit;
  if (x > upperlimit) return upperlimit;
  return x;
}

f32 smoothstep2(f32 edge0, f32 edge1, f32 x) {
   // Scale, and clamp x to 0..1 range
   x = clamp2((x - edge0) / (edge1 - edge0));

   return x * x * (3.0f - 2.0f * x);
}

u8 mitm_text_colors[][3] = {
    {255, 255, 255},
    {220, 0, 240},
    {0, 255, 255},
};

void print_string_ascii_alpha(s32 x, s32 y, char *str, s32 color, s32 alpha) {
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, mitm_text_colors[color][0], mitm_text_colors[color][1], mitm_text_colors[color][2], alpha);
    print_generic_string_ascii(x, y, (u8 *)str);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

void print_string_ascii_centered_alpha(s32 x, s32 y, char *str, s32 color, s32 alpha) {
    s32 x1 = get_string_width_ascii(str);
    print_string_ascii_alpha(x - x1/2, y, str, color, alpha);
}

void print_mitm_credits(u8 hud_alpha) {
    s32 credits_entries = (sizeof(mitm_credits)/8);
    s32 lower_limit = (credits_entries*16) - 160;

    u8 base_alpha = 255;

    shade_screen();

    if (_60fps_on) {
        credits_y_offset -= (gPlayer1Controller->rawStickY/20.0f);
    } else {
        credits_y_offset -= (gPlayer1Controller->rawStickY/10.0f);
    }
    if (credits_y_offset <= 0) {
        credits_y_offset = 0;
    }
    if (credits_y_offset >= lower_limit) {
        credits_y_offset = lower_limit;
    }
    if (credits_y_offset != lower_limit) {
        print_string_ascii_centered_alpha(300,20 + sins(gGlobalTimer*0x300)*2.5f ,"|",0,base_alpha);
    }
    if (credits_y_offset != 0) {
        print_string_ascii_centered_alpha(300,40 - sins(gGlobalTimer*0x300)*2.5f,"^",0,base_alpha);
    }

    for (int i=0; i<credits_entries; i++) {
        u8 alpha = base_alpha;
        s32 ypos = credits_y_offset+200-(16*i);
        if ((ypos < 220)&&(ypos >10)) {
            if (ypos > 200) {
                alpha = ((base_alpha/255.0f)*smoothstep2(220.0f,200.0f,ypos))*255.0f;
            }
            if (ypos < 30) {
                alpha = ((base_alpha/255.0f)*smoothstep2(10.0f,30.0f,ypos))*255.0f;
            }

            print_string_ascii_centered_alpha(160,ypos, mitm_credits[i].text, mitm_credits[i].color, alpha);
        }
    }
}

struct painting_world painting_world_list[] = {
    {"Bob-omb Battlefield", LEVEL_BOB},
    {"Whomp's Fortress", LEVEL_WF},
    {"Jolly Roger Bay", LEVEL_JRB},
    {"Cool Cool Mountain", LEVEL_CCM},
    {"Big Boo's Haunt", LEVEL_BBH},
    {"Hazy Maze Cave", LEVEL_HMC},
    {"Lethal Lava Land", LEVEL_LLL},
    {"Shifting Sand Land", LEVEL_SSL},
    {"Dire Dire Docks", LEVEL_DDD},
    {"Snowman's Land", LEVEL_SL},
    {"Wet Dry World", LEVEL_WDW},
    {"Tall Tall Mountain", LEVEL_TTM},
    {"Tiny Huge Island", LEVEL_THI},
    {"Tick Tock Clock", LEVEL_TTC},
    {"Rainbow Ride", LEVEL_RR},
    {"Secret Slide", LEVEL_PSS}
};

s32 in_vanilla_painting_world(void) {
    return hub_level_current_index == HUBLEVEL_PWORLD;
}

u8 redd_painting_show_ui = FALSE;
u8 redd_painting_state = 0;
s8 redd_painting_ix = 0;
s8 redd_painting_iy = 0;
void bhv_redd_paintings_loop(void) {
    s8 old_hint_index;

    o->oAnimState = 0;
    if (o->oTimer%90 < 4) {
        o->oAnimState = 1;
    }
    switch(o->oAction) {
        case 0: // wait
            if (o->oInteractStatus == INT_STATUS_INTERACTED) {
                redd_painting_show_ui = TRUE;
                redd_painting_ix = 0;
                redd_painting_iy = 0;
                shop_cant_afford = 0;

                redd_painting_state = 0;
                o->oAction = 1;

                gCamera->cutscene = 1;

                vec3f_copy(&gLakituState.goalFocus, &o->oPosVec);
                vec3f_copy(&gLakituState.goalPos, &o->oPosVec);
                gLakituState.goalPos[0] += sins(o->oMoveAngleYaw)*800.0f + sins(o->oMoveAngleYaw - 0x4000)*150.0f;
                gLakituState.goalPos[2] += coss(o->oMoveAngleYaw)*800.0f + coss(o->oMoveAngleYaw - 0x4000)*150.0f;

                gLakituState.goalFocus[0] += sins(o->oMoveAngleYaw - 0x4000)*150.0f;
                gLakituState.goalFocus[2] += coss(o->oMoveAngleYaw - 0x4000)*150.0f;

                gLakituState.goalFocus[1] += 140.0f;
                gLakituState.goalPos[1] += 190.0f;
            }
            o->oInteractStatus = 0;
        break;
        case 1: // select course
            handle_menu_scrolling_2way(&redd_painting_ix, &redd_painting_iy, 0, 3, 3);
            u8 redd_painting_index = (redd_painting_iy *4)+(redd_painting_ix%4);
            if (gPlayer1Controller->buttonPressed & (A_BUTTON | START_BUTTON)) {
                if (gSaveBuffer.files[gCurrSaveFileNum - 1][0].paintings_unlocked & (1<<redd_painting_index)) {
                    redd_painting_show_ui = FALSE;
                    gCurrActNum = 1;
                    hub_level_current_index = HUBLEVEL_PWORLD;
                    initiate_warp(painting_world_list[redd_painting_index].level, 1, 0x0A, WARP_FLAGS_NONE);
                    fade_into_special_warp(WARP_SPECIAL_NONE, 0);
                    gSavedCourseNum = COURSE_NONE;
                } else {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            } else if (gPlayer1Controller->buttonPressed & (B_BUTTON)) {
                set_mario_action(gMarioState, ACT_IDLE, 0);
                gCamera->cutscene = 0;
                redd_painting_show_ui = FALSE;
                o->oAction = 0;
            }
        break;
        case 2: //mario buy paintings
            if (gPlayer1Controller->buttonPressed & (A_BUTTON | START_BUTTON)) {
                if (gMarioState->numGlobalCoins >= 200) {
                    save_file_set_flags(SAVE_FLAG_BOUGHT_PAINTINGS);
                    gMarioState->numGlobalCoins -= 200.0f;
                    redd_painting_state = 0;
                    o->oAction = 1;
                    save_file_set_coins();
                    save_file_do_save(gCurrSaveFileNum - 1);
                    play_sound(SOUND_MENU_STAR_SOUND, gMarioState->marioObj->header.gfx.cameraToObject);
                } else {
                    shop_cant_afford = TRUE;
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            } else if (gPlayer1Controller->buttonPressed & (B_BUTTON)) {
                set_mario_action(gMarioState, ACT_IDLE, 0);
                gCamera->cutscene = 0;
                redd_painting_show_ui = FALSE;
                o->oAction = 0;
            }
            break;
    }
}

void render_painting_ui(f32 alpha) {
    char stringBuf[200];

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-alpha);
    create_dl_translation_matrix(MENU_MTX_PUSH, 160, 120, 0);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gSPDisplayList(gDisplayListHead++, painting_menu_roundbox_003_mesh);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f);
    for (int i = 0; i<16; i++) {
        int x = i%4;
        int y = i/4;
        if (!(gSaveBuffer.files[gCurrSaveFileNum - 1][0].paintings_unlocked & (1<<i))) {
            create_dl_translation_matrix(MENU_MTX_PUSH, 57+x*32, 194-y*32, 0);
            gSPDisplayList(gDisplayListHead++, painting_mystery_mysp_mesh);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
        }
    }

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-alpha);
    u8 redd_painting_index = (redd_painting_iy *4)+(redd_painting_ix%4);
    if (redd_painting_state == 0) {
        create_dl_translation_matrix(MENU_MTX_PUSH, 57+redd_painting_ix*32, 195-redd_painting_iy*32, 0);
        gSPDisplayList(gDisplayListHead++, selector_selector_mesh);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    }

    if (gSaveBuffer.files[gCurrSaveFileNum - 1][0].paintings_unlocked & (1<<redd_painting_index)) {
        sprintf(stringBuf,"Enter: %s\nThese are sandbox levels intended for play,\nso there are no power stars to collect.",painting_world_list[redd_painting_index].name);
    } else {
        if (mitm_levels[redd_painting_index].star_requirement <= gMarioState->numStars) {
            sprintf(stringBuf,"Enter: ???\nFind this painting in %s.",mitm_levels[redd_painting_index].name);
        } else {
            sprintf(stringBuf,"Enter: ???\nFind this painting in ???.");
        }
    }
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-alpha);
    print_generic_string_ascii(43, 58, stringBuf);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

}

struct music_data music_list[] = {
    {SEQ_MITM_FILE_SELECT,0,"File Select","Original composition by: SpK"},
    {SEQ_MITM_HUB,0,"Fracture","Original composition by: SpK"},
    
    {SEQ_PEACHS_BIRTHDAY,0,"Peach's Birthday Cake","From: Mario Party\nPorted by: Teraok"},
    {SEQ_BOWSER_TIME,0,"Bowser Time!","From: Mario Party DS\nPorted by: Teraok"},

    {SEQ_MITM_GET_ABILITY,0,"Get Ability","Original composition by: Leonitz\nPorted by: sm64pie"},

    {SEQ_CUSTOM_SAVE_HUT,0,"Save Hut","From: Kirby Super Star Ultra\nPorted by: CowQuack"},
    {SEQ_CUSTOM_KIRBY_BOSS,0,"Boss Battle","From: Kirby Super Star Ultra\nPorted by: CowQuack"},
    {SEQ_CUSTOM_PEANUT_PLAINS,0,"Peanut Plains","From: Kirby Super Star Ultra\nPorted by: CowQuack"},
    {SEQ_CUSTOM_CRYSTAL_FIELD,0,"Crystal Field","From: Kirby Super Star Ultra\nPorted by: CowQuack"},
    {SEQ_CUSTOM_TREES_IN_THE_DEPTHS,0,"Trees in the Depths of the Earth","From: Kirby Super Star Ultra\nPorted by: CowQuack"},
    {SEQ_MINECART_RIDING,0,"Mine Cart Riding","From: Kirby Super Star Ultra\nPorted by: CowQuack"},
    {SEQ_CUSTOM_MARX,0,"V.S. Marx","From: Kirby Super Star Ultra\nPorted by: CowQuack"},

    {SEQ_JELLYFISH_FIELDS,0,"Jellyfish Fields","From: Battle for Bikini Bottom\nPorted by: JoshTheBosh"},
    {SEQ_JELLYFISH_SECRET,0,"Jellyfish Secret","From: Battle for Bikini Bottom\nPorted by: JoshTheBosh"},
    {SEQ_DOWNTOWN_BB,0,"Downtown Bikini Bottom","From: Battle for Bikini Bottom\nPorted by: JoshTheBosh"},
    {SEQ_JELLYFISH_BOSS,0,"Jellyfish Jam","From: Battle for Bikini Bottom\nPorted by: sm64pie"},

    {SEQ_C_SEA_ME_NOW,0,"Sea Me Now","From: Splatoon 3\nPorted by: Teraok"},

    {SEQ_LEVEL_I_INSIDE,0,"Cave Dungeon Rayman Remix","Original composition by: Teraok"},
    {SEQ_CLEARLEAF_FOREST,0,"Clearleaf Forest","From: Rayman 3\nPorted by: Teraok"},
    {SEQ_LEVEL_I_AMBUSH,0,"Hoodlum Ambush","From: Rayman 3\nPorted by: Teraok"},
    {SEQ_LEVEL_I_CARRYING_THE_PLUM,0,"Carrying the Plum","From: Rayman 3\nPorted by: Teraok"},
    {SEQ_FUNKY_SHELL,0,"Funky Board","From: Rayman 3\nPorted by: Teraok"},
    {SEQ_MASTER_KAAG_BOSS,0,"Master Kaag","From: Rayman 3\nPorted by: Teraok"},
    
    {SEQ_H_GEOTHERMAL,0,"Geothermal","From: Cave Story\nPorted by: Teraok"},
    {SEQ_C6,0,"Step Into My Gardens","From: Bioshock"},

    {SEQ_L_MONDAYS,0,"Mondays","From: Pizza Tower\nPorted by: sm64pie"},
    {SEQ_L_HOT_SPAGHETTI,0,"Hot Spaghetti","From: Pizza Tower\nPorted by: sm64pie"},
    {SEQ_L_PIZZA_TIME,0,"Pizza Time","From: Pizza Tower\nPorted by: Teraok"},
    {SEQ_PEPPERMAN_STRIKES,0,"Pepperman Strikes!","From: Pizza Tower\nPorted by: sm64pie"},

    {SEQ_K_CHINATOWN,0,"Chinatown","From: Katana Zero\nPorted by: Teraok"},
    {SEQ_ROCKSOLID,0,"Rock Solid","From: Conker's Bad Fur Day"},

    {SEQ_C9,0,"Hangar","From: DOOM PSX"},

    {SEQ_F_FRWL,0,"From Russia with Love","From: From Russia with Love\nPorted by: Teraok"},
    {SEQ_F_BOND,0,"James Bond Theme Song","From: 007 Series\nPorted by: Teraok"},

    {SEQ_CUSTOM_ECRUTEAK,0,"Ecruteak City","From: Pokemon\nPorted by: SpK"},
    {SEQ_CUSTOM_AZALEA,0,"Azalea","From: Pokemon\nPorted by: SpK"},
    {SEQ_CUSTOM_DARK_CAVE,0,"Dark Cave","From: Pokemon\nPorted by: SpK"},
    {SEQ_CUSTOM_GYM,0,"Gym","From: Pokemon\nPorted by: SpK"},
    {SEQ_CUSTOM_VS_HOOH,0,"V.S. Hooh","From: Pokemon"},

    {SEQ_D_OVER,0,"N. Sanity Island","From: Crash Twinsanity\nPorted by: Teraok"},
    {SEQ_D_UNDER,0,"Underwater","From: Crash Bandicoot 3: Warped\nPorted by: Teraok"},

    {SEQ_O_MAINTRACK,0,"Via Corolla","From: The Walking Dead: Saints & Sinners"},
    {SEQ_O_EASYSTREET,0,"Easy Street","From: The Walking Dead"},
    {SEQ_O_STH,0,"Stir The Herd","From: The Walking Dead: Saints & Sinners"},

    {SEQ_HAMSTERBALL,0,"Beginner Race","From: Hamsterball\nPorted by: sm64pie"},

    {SEQ_CUSTOM_ESA_VALIANT,0,"Valiant","From: Environmental Station Alpha\nPorted by: Teraok"},
    {SEQ_CUSTOM_ESA_SUBMERGED,0,"Submerged","From: Environmental Station Alpha\nPorted by: Teraok"},
    {SEQ_CUSTOM_ESA_AMMOINEN,0,"Ammoinen","From: Environmental Station Alpha\nPorted by: Teraok"},
    {SEQ_CUSTOM_ESA_MECHA,0,"Swift Mecha","From: Environmental Station Alpha\nPorted by: Teraok"},

    //{SEQ_BIGBLUE,"Big Blue","From: F-ZERO\nPorted by: Asbeth"},
    //{SEQ_MUTECITY,"Mute City","From: F-ZERO\nPorted by: Asbeth"},

    {SEQ_MITM_BOWSER_COURSE,0,"Centrum Omnium","Original composition by: SpK"},

    {SEQ_FINAL_BOSS,2,"Final Bowser Phase 1 - Eggman","Original composition by: SpK\nBased on: Boss (Sonic the Hedgehog 2)"},
    {SEQ_FINAL_BOSS,3,"Final Bowser Phase 2 - Gaster","Original composition by: SpK\nBased on: CORE (Undertale)"},
    {SEQ_FINAL_BOSS,4,"Final Bowser Phase 3 - Yukari","Original composition by: SpK\nBased on: Necrofantasia (Touhou 7)"},
    {SEQ_FINAL_BOSS,5,"Final Bowser Phase 4 - Sephiroth","Original composition by: SpK\nBased on: One Winged Angel (Final Fantasy 7)"},
    {SEQ_FINAL_BOSS,6,"Final Bowser Phase 5 - Hector","Original composition by: SpK\nBased on: Hekalis (Blade and Sorcery)"},

    {SEQ_MITM_CREDITS,0,"Multiversal Dream","Original composition by: Teraok"},

    {SEQ_COUNT,0,NULL,NULL},
};

u8 music_menu_show_ui = FALSE;
s8 music_menu_index = 0;
s8 music_menu_isplaying = -1;

void bhv_music_menu_loop(void) {
    s8 old_hint_index;

    o->oAnimState = 0;
    if (o->oTimer%90 < 4) {
        o->oAnimState = 1;
    }
    switch(o->oAction) {
        case 0: //init
            o->oAction = 1;
            music_menu_isplaying = -1;
            break;
        case 1: // wait
            if (o->oInteractStatus == INT_STATUS_INTERACTED) {
                music_menu_show_ui = TRUE;
                music_menu_index = 0;
                o->oAction = 2;
                gCamera->cutscene = 1;

                vec3f_copy(&gLakituState.goalFocus, &o->oPosVec);
                vec3f_copy(&gLakituState.goalPos, &o->oPosVec);
                gLakituState.goalPos[0] += sins(o->oMoveAngleYaw)*800.0f + sins(o->oMoveAngleYaw - 0x4000)*150.0f;
                gLakituState.goalPos[2] += coss(o->oMoveAngleYaw)*800.0f + coss(o->oMoveAngleYaw - 0x4000)*150.0f;

                gLakituState.goalFocus[0] += sins(o->oMoveAngleYaw - 0x4000)*150.0f;
                gLakituState.goalFocus[2] += coss(o->oMoveAngleYaw - 0x4000)*150.0f;

                gLakituState.goalFocus[1] += 140.0f;
                gLakituState.goalPos[1] += 190.0f;
            }
            o->oInteractStatus = 0;
        break;
        case 2: // select course
            handle_menu_scrolling(MENU_SCROLL_VERTICAL, &music_menu_index, 0, ARRAY_COUNT(music_list)-2);
            if (gPlayer1Controller->buttonPressed & (A_BUTTON | START_BUTTON)) {
                if (save_file_check_song_unlocked(music_menu_index)) {
                    if (music_menu_isplaying == music_menu_index) {
                        stop_background_music(SEQUENCE_ARGS(4, music_list[music_menu_index].seq ));
                        music_menu_isplaying = -1;
                    } else {
                        stop_background_music(SEQUENCE_ARGS(4, music_list[music_menu_isplaying].seq ));
                        set_background_music(0, music_list[music_menu_index].seq, 0);
                        gDynamicPhase = music_list[music_menu_index].dynPhase;
                        music_menu_isplaying = music_menu_index;
                    }
                } else {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            } else if (gPlayer1Controller->buttonPressed & (B_BUTTON)) {
                set_mario_action(gMarioState, ACT_IDLE, 0);
                gCamera->cutscene = 0;
                music_menu_show_ui = FALSE;
                o->oAction = 1;
            }
        break;
    }
}

#define MUSIC_MENU_PAGE_LENGTH 7
void render_music_menu_ui(f32 alpha) {
    u8 page = music_menu_index/MUSIC_MENU_PAGE_LENGTH;
    u8 page_index = music_menu_index%MUSIC_MENU_PAGE_LENGTH;

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-alpha);
    create_dl_translation_matrix(MENU_MTX_PUSH, 160, 120, 0);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gSPDisplayList(gDisplayListHead++, bigtext_menu_roundbox_004_mesh);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    // Selection Triangle
    create_dl_translation_matrix(MENU_MTX_PUSH, 43, 190-(page_index*16), 0);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);

    for (int i = 0; i < MUSIC_MENU_PAGE_LENGTH; i++) {
        int trueindex = (page*MUSIC_MENU_PAGE_LENGTH)+i;
        if (trueindex >= ARRAY_COUNT(music_list)-1) {
            continue;
        }

        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-alpha);

        if (save_file_check_song_unlocked(trueindex)) {
            if (trueindex == music_menu_isplaying) {
                gDPSetEnvColor(gDisplayListHead++, 0, 240, 0, 255.0f-alpha);
                print_generic_string_ascii(55, 190-(i*16), ">");
                print_generic_string_ascii(65, 190-(i*16), music_list[trueindex].name);
            } else {
                print_generic_string_ascii(55, 190-(i*16), music_list[trueindex].name);
            }
        } else {
            gDPSetEnvColor(gDisplayListHead++, 200, 200, 200, 255.0f-alpha);
            print_generic_string_ascii(55, 190-(i*16), "???");
        }
    }

    char stringBuf[10];
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-alpha);
    sprintf( stringBuf, "(%d/%d)", page, 7/*(ARRAY_COUNT(music_list)-1)/MUSIC_MENU_PAGE_LENGTH*/ );
    print_generic_string_ascii(240, 78, stringBuf);
    if (save_file_check_song_unlocked(music_menu_index)) {
        print_generic_string_ascii(43, 58, music_list[music_menu_index].desc);
    }
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}