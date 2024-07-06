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

//only for fangame marathon, some levels are skipped
u8 hint_fake_index_list[] = {
0,
1,
2,
3,
6,
8,
9,
10,
11,
14,
};

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

u8 hub_star_string[] = {0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,DIALOG_CHAR_TERMINATOR};

//In course order, not alphabetical!
//Only mess with /* Level */ entry, everything else is pre-configured
struct mitm_hub_level hub_levels[] = {
          /* Author          Level      StarFlags     StarReq  StartArea  ReturnWarp  StarCt DreamCt  Name */
    /*G*/ {&author_string_g, LEVEL_G,   COURSE_BOB,   0 ,      3,         20,         8,     0,       "MARIO SUPER STAR ULTRA"},
    /*A*/ {&author_string_a, LEVEL_A,   COURSE_WF,    1 ,      1,         21,         8,     0,       "MARIO IN BIKINI BOTTOM"},
    /*C*/ {&author_string_c, LEVEL_C,   COURSE_JRB,   1 ,      1,         22,         8,     0,       "PIRANHA PIT"},
    /*I*/ {&author_string_i, LEVEL_I,   COURSE_CCM,   3 ,      1,         23,         8,     0,       "MUSHROOM HAVOC"},
    /*H*/ {&author_string_h, LEVEL_H,   COURSE_BBH,   5 ,      1,         24,         8,     0,       "OPPORTUNITY"},
    /*B*/ {&author_string_b, LEVEL_B,   COURSE_HMC,   10,      1,         25,         8,     0,       "-"},
    /*L*/ {&author_string_l, LEVEL_L,   COURSE_LLL,   15,      6,         26,         8,     0,       "BEYOND THE CURSED PIZZA"},
    /*K*/ {&author_string_k, LEVEL_BOB, COURSE_SSL,   15,      1,         27,         8,     0,       "-"},
    /*E*/ {&author_string_e, LEVEL_E,   COURSE_DDD,   20,      1,         28,         8,     0,       "DOOM"},
    /*F*/ {&author_string_f, LEVEL_F,   COURSE_SL,    20,      1,         29,         8,     0,       "FROM RUSSIA WITH LOVE"},
    /*J*/ {&author_string_j, LEVEL_J,   COURSE_WDW,   25,      1,         30,         8,     0,       "ECRUTEAK CITY"},
    /*D*/ {&author_string_d, LEVEL_D,   COURSE_TTM,   25,      1,         31,         8,     0,       "NEW N-SANITY ISLAND"},
    /*O*/ {&author_string_o, LEVEL_O,   COURSE_THI,   30,      1,         32,         8,     0,       "SAINTS, SINNERS, & MARIO"},
    /*N*/ {&author_string_n, LEVEL_N,   COURSE_TTC,   45,      1,         33,         8,     0,       "MARIO IN HAMSTERBALL"},
    /*M*/ {&author_string_m, LEVEL_M,   COURSE_RR,    45,      1,         34,         8,     0,       "ENVIRONMENTAL STATION M"},
    /*BC*/{NULL, LEVEL_BOWSER_COURSE,   COURSE_BITDW, 0,       1,         34,         1,     0,       "CENTRUM OMNIUM"},
   /*HUB*/{NULL,             NULL,      COURSE_BITFS, 0,       1,         34,         1,     0,       "HUB"},
};

s8 hub_level_index = -1;
s8 hub_dma_index = -1;
s8 hub_level_current_index = HUBLEVEL_HUB;
f32 hub_titlecard_alpha = 0.0f;

void update_hub_star_string(s8 index_of_hublevel) {
    u8 star_flags = star_flags = save_file_get_star_flags(gCurrSaveFileNum-1,COURSE_NUM_TO_INDEX(hub_levels[index_of_hublevel].course));
    u8 star_count = hub_levels[index_of_hublevel].star_count;

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

    o->oOpacity = 0;
    if (gCurrLevelNum != LEVEL_CASTLE) {
        o->oOpacity = 250;
        return;
    }
    if (gMarioState->numStars >= hub_levels[o->oBehParams2ndByte].star_requirement) {
        o->oOpacity = 250;
    }
}

void level_pipe_loop(void) {
    o->oUnk94++;
    if (gCurrLevelNum != LEVEL_CASTLE) {
        level_pipe_in_level_loop();
        return;
    }

    if ((gMarioState->numStars >= hub_levels[o->oBehParams2ndByte].star_requirement)&&(!queued_pipe_cutscene)&&
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
            update_hub_star_string(hub_dma_index);
            print_generic_string(110,40,hub_star_string);
        } else {
            //Not Enough Stars to Enter
            gDPSetEnvColor(gDisplayListHead++, 255, 0, 0, (u8)hub_titlecard_alpha);
            int_to_str(hub_levels[hub_dma_index].star_requirement, &pipe_string_not_enough[10]);
            print_generic_string(110,40,pipe_string_not_enough);
        }

        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, (u8)hub_titlecard_alpha);
        print_generic_string(113,25,pipe_string_enter);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 255, (u8)hub_titlecard_alpha);
        print_generic_string(110,25,pipe_string_a);
        gDPSetEnvColor(gDisplayListHead++, 0, 150, 0, (u8)hub_titlecard_alpha);
        print_generic_string(109,25,pipe_string_b);

        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    }

    hub_level_index = -1;
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
    return hub_levels[id].level ;
}

u8 get_hub_area(u8 id) {
    return hub_levels[id].start_area ;
}

u8 get_hub_return_id(u8 id) {
    return hub_levels[id].return_id;
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
                        if (try_to_buy(150)) {
                            save_file_unlock_ability(ABILITY_UTIL_COMPASS);
                            save_file_set_coins();
                            play_sound(SOUND_MENU_STAR_SOUND, gMarioState->marioObj->header.gfx.cameraToObject);
                            save_file_do_save(gCurrSaveFileNum - 1);
                        }
                        break;
                    case 1:
                        if (try_to_buy(100)) {
                            save_file_unlock_ability(ABILITY_UTIL_MIRROR);
                            save_file_set_coins();
                            play_sound(SOUND_MENU_STAR_SOUND, gMarioState->marioObj->header.gfx.cameraToObject);
                            save_file_do_save(gCurrSaveFileNum - 1);
                        }
                        break;
                    case 2:
                        if (try_to_buy(250)) {
                            save_file_unlock_ability(ABILITY_UTIL_MILK);
                            save_file_set_coins();
                            play_sound(SOUND_MENU_STAR_SOUND, gMarioState->marioObj->header.gfx.cameraToObject);
                            save_file_do_save(gCurrSaveFileNum - 1);
                        }
                        break;
                    case 3:
                        if (try_to_buy(100)) { // Star
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
                        if (try_to_buy(400)) {
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

        print_generic_string_ascii(45, 56, hub_levels[hint_fake_index_list[hint_index]].name);

        for (s32 i = 0; i < 10; i++) {
            u8 star_flags = save_file_get_star_flags(gCurrSaveFileNum-1,COURSE_NUM_TO_INDEX(hub_levels[hint_fake_index_list[i]].course));
            sprintf(stringBuf,"C%02d",i+1);

            if (star_flags == 0xFF) {
                // level has been filled
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255.0f-hud_alpha);
            } else {
                // level has remaining stars
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-hud_alpha);
            }

            print_generic_string_ascii(50+(33*(i%2)), 197-(18*(i/2)), stringBuf);
        }
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    } else {
        // Hint Abilities
        s32 ability_amount = 0;
        s32 ability_x_offset = 0;
        u32 hint_ability_flags = hintlist[hint_level][hint_index].dependancies;
        u8 star_flags = save_file_get_star_flags(gCurrSaveFileNum-1,COURSE_NUM_TO_INDEX(hint_level+1));

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
            hint_text = "You've got this one!";
            gSaveBuffer.files[gCurrSaveFileNum - 1][0].hints_unlocked[hint_level] |= (1<<hint_index);
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
            handle_menu_scrolling_2way(&hint_ix, &hint_iy, 0, 4, 1);
            hint_index = (hint_iy *2)+(hint_ix%3);
            if (gPlayer1Controller->buttonPressed & (A_BUTTON | START_BUTTON)) {
                o->oAction = 2;
                hint_level = hint_fake_index_list[hint_index];
                hint_layer = 1;
                hint_index = 0;
                hint_ix = 0;
                hint_iy = 0;
                cur_obj_init_animation_with_sound(2);
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