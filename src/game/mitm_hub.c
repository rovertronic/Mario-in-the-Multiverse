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
          /* Author */      /* Level */  /*Star Flags*/   /*Star Req*/  /*Start Area*/  /*Return Hub Warp ID*/
    /*G*/ {&author_string_g, LEVEL_G,     COURSE_BOB,      0/*0 */,      3,             20},
    /*A*/ {&author_string_a, LEVEL_A,     COURSE_WF,       0/*1 */,      1,             21},
    /*C*/ {&author_string_c, LEVEL_CCM,   COURSE_JRB,      0/*1 */,      1,             22},
    /*I*/ {&author_string_i, LEVEL_I,     COURSE_CCM,      0/*3 */,      1,             23},
    /*H*/ {&author_string_h, LEVEL_H,     COURSE_BBH,      0/*5 */,      1,             24},
    /*B*/ {&author_string_b, LEVEL_B,     COURSE_HMC,      0/*10*/,      1,             25},
    /*L*/ {&author_string_l, LEVEL_BOB,   COURSE_LLL,      0/*15*/,      1,             26},
    /*K*/ {&author_string_k, LEVEL_BOB,   COURSE_SSL,      0/*15*/,      1,             27},
    /*E*/ {&author_string_e, LEVEL_E,     COURSE_DDD,      0/*20*/,      1,             28},
    /*F*/ {&author_string_f, LEVEL_F,     COURSE_SL ,      0/*20*/,      1,             29},
    /*J*/ {&author_string_j, LEVEL_J,     COURSE_WDW,      0/*25*/,      1,             30},
    /*D*/ {&author_string_d, LEVEL_D,     COURSE_TTM,      0/*30*/,      1,             31},
    /*O*/ {&author_string_o, LEVEL_O,     COURSE_THI,      0/*30*/,      1,             32},
    /*N*/ {&author_string_n, LEVEL_N,     COURSE_TTC,      0/*50*/,      1,             33},
    /*M*/ {&author_string_m, LEVEL_BOB,   COURSE_RR ,      0/*50*/,      1,             34},
};

s8 hub_level_index = -1;
s8 hub_dma_index = -1;
s8 hub_level_current_index = 0; // temp val
f32 hub_titlecard_alpha = 0.0f;

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
            o->oOpacity = 250;
            if ((lateral_dist_between_objects(o, gMarioObject) < 120.0f)&&(gMarioState->pos[1] < o->oPosY+500.0f)&&(gMarioState->pos[1] > o->oPosY)) {
                hub_level_index = o->oBehParams2ndByte;
                hub_level_current_index = o->oBehParams2ndByte;
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
    sold_out[3] = (save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_NONE)) & 1);
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