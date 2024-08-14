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

u8 pipe_string_not_enough[] = {TEXT_PIPE_NOT_ENOUGH};
u8 pipe_string_enter[] = {TEXT_PIPE_ENTER};
u8 pipe_string_a[] = {TEXT_PIPE_A};
u8 pipe_string_b[] = {TEXT_PIPE_B};

u8 hub_star_string[] = {0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,DIALOG_CHAR_TERMINATOR};

mitm_dream_data mitmdd_b = {{ABILITY_DEFAULT,ABILITY_UTIL_MIRROR,ABILITY_BIG_DADDY,ABILITY_NONE},6};
mitm_dream_data mitmdd_c = {{ABILITY_DEFAULT,ABILITY_PHASEWALK,ABILITY_NONE,ABILITY_NONE},5};
mitm_dream_data mitmdd_e = {{ABILITY_DEFAULT,ABILITY_UTIL_MIRROR,ABILITY_E_SHOTGUN,ABILITY_NONE},8};
mitm_dream_data mitmdd_g = {{ABILITY_DEFAULT,ABILITY_UTIL_MIRROR,ABILITY_NONE,ABILITY_NONE},7};
mitm_dream_data mitmdd_k = {{ABILITY_DEFAULT,ABILITY_UTIL_MIRROR,ABILITY_CHRONOS,ABILITY_NONE},7};
mitm_dream_data mitmdd_l = {{ABILITY_DEFAULT,ABILITY_KNIGHT,ABILITY_NONE,ABILITY_NONE},4};
mitm_dream_data mitmdd_n = {{ABILITY_DEFAULT,ABILITY_E_SHOTGUN,ABILITY_BUBBLE_HAT,ABILITY_NONE},7};
mitm_dream_data mitmdd_o = {{ABILITY_DEFAULT,ABILITY_UTIL_MIRROR,ABILITY_HM_FLY,ABILITY_GADGET_WATCH},8};

//In course order, not alphabetical!
//Only mess with /* Level */ entry, everything else is pre-configured
struct mitm_level_data mitm_levels[] = {
          /* Name, Author(s)*/
          /*Level     StarFlags     StarReq  StartArea  ReturnWarp  StarCt DreamData*/
    /*G*/ {"MARIO SUPER STAR ULTRA", "CowQuack",
            LEVEL_G,  COURSE_BOB,   0,       3,         20,         8,     &mitmdd_g},
    /*A*/ {"MARIO IN BIKINI BOTTOM", "JoshTheBosh",
            LEVEL_A,  COURSE_WF,    1,       1,         21,         8,     NULL},
    /*C*/ {"PIRANHA PIT", "Drahnokks & Woissil",
            LEVEL_C,  COURSE_JRB,   1,       1,         22,         8,     &mitmdd_c},
    /*I*/ {"MUSHROOM HAVOC", "Drahnokks",
            LEVEL_I,  COURSE_CCM,   3,       1,         23,         8,     NULL},
    /*H*/ {"OPPORTUNITY", "joopii",
            LEVEL_H,  COURSE_BBH,   5,       1,         24,         8,     NULL},
    /*B*/ {"BIOSHOCK RAPTURE", "furyiousfight",
            LEVEL_B,  COURSE_HMC,   10,      1,         25,         8,     &mitmdd_b },
    /*L*/ {"BEYOND THE CURSED PIZZA", "luigiman0640",
            LEVEL_L,  COURSE_LLL,   15,      6,         26,         8,     &mitmdd_l },
    /*K*/ {"KATANA MARIO NEW MECCA", "KeyBlader & axollyon",
            LEVEL_K,  COURSE_SSL,   15,      2,         27,         8,     &mitmdd_k },
    /*E*/ {"DOOM", "Dorrieal",
            LEVEL_E,  COURSE_DDD,   20,      1,         28,         8,     &mitmdd_e },
    /*F*/ {"FROM RUSSIA WITH LOVE", "Aesy (Aeza)",
            LEVEL_F,  COURSE_SL,    20,      1,         29,         8,     NULL},
    /*J*/ {"ECRUTEAK CITY", "SpK",
            LEVEL_J,  COURSE_WDW,   25,      1,         30,         8,     NULL},
    /*D*/ {"NEW N-SANITY ISLAND", "JakeDower",
            LEVEL_D,  COURSE_TTM,   30,      1,         31,         8,     NULL},
    /*O*/ {"SAINTS, SINNERS, & MARIO", "Rovertronic",
            LEVEL_O,  COURSE_THI,   30,      1,         32,         8,     &mitmdd_o},
    /*N*/ {"MARIO IN HAMSTERBALL", "LinCrash",
            LEVEL_N,  COURSE_TTC,   50,      1,         33,         8,     &mitmdd_n},
    /*M*/ {"ENVIRONMENTAL STATION M", "Mel",
            LEVEL_M,  COURSE_RR,    50,      1,         34,         8,     NULL},
    /*BC*/{"CENTRUM OMNIUM", NULL,
            LEVEL_BOWSER_COURSE,  COURSE_BITDW, 0, 0,   34,         1,     NULL},
   /*HUB*/{"FRACTURE", NULL,
   NULL,     COURSE_BITFS, 0,       0,         34,         2,     NULL},
};

s8 hub_level_index = -1;
s8 hub_dma_index = -1;
s8 hub_level_current_index = HUBLEVEL_HUB;
f32 hub_titlecard_alpha = 0.0f;

void update_hub_star_string(s8 index_of_hublevel) {
    u8 star_flags = star_flags = save_file_get_star_flags(gCurrSaveFileNum-1,COURSE_NUM_TO_INDEX(mitm_levels[index_of_hublevel].course));
    u8 star_count = mitm_levels[index_of_hublevel].star_count;

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
            o->oOpacity = 250;
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

        if (mitm_levels[hub_dma_index].star_requirement <= gMarioState->numStars) {
            //Display Collected Stars
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, (u8)hub_titlecard_alpha);
            update_hub_star_string(hub_dma_index);
            print_generic_string(110,40,hub_star_string);
        } else {
            //Not Enough Stars to Enter
            gDPSetEnvColor(gDisplayListHead++, 255, 0, 0, (u8)hub_titlecard_alpha);
            int_to_str(mitm_levels[hub_dma_index].star_requirement, &pipe_string_not_enough[10]);
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

        print_generic_string_ascii(45, 56, mitm_levels[hint_index].name);

        for (s32 i = 0; i < 15; i++) {
            u8 star_flags = save_file_get_star_flags(gCurrSaveFileNum-1,COURSE_NUM_TO_INDEX(mitm_levels[hint_index].course));
            sprintf(stringBuf,"C%02d",i+1);

            if (star_flags == 0xFF) {
                // level has been filled
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255.0f-hud_alpha);
            } else {
                // level has remaining stars
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-hud_alpha);
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
            handle_menu_scrolling_2way(&hint_ix, &hint_iy, 0, 4, 2);
            hint_index = (hint_iy *3)+(hint_ix%3);
            if (gPlayer1Controller->buttonPressed & (A_BUTTON | START_BUTTON)) {
                o->oAction = 2;
                hint_level = hint_index;
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
    {"Rovertronic",0},
    {"",0},

    {"Abilities",1},
    {"CowQuack",0},
    {"JoshTheBosh",0},
    {"Drahnokks",0},
    {"Joopii",0},
    {"furyiousfight",0},
    {"luigiman0640",0},
    {"axollyon",0},
    {"Dorrieal",0},
    {"Aeza",0},
    {"SpK",0},
    {"JakeDower",0},
    {"lincrash",0},
    {"Mel",0},
    {"",0},

    {"Levels",1},
    {"CowQuack",0},
    {"JoshTheBosh",0},
    {"Drahnokks",0},
    {"Woissil",0},
    {"Joopii",0},
    {"furyiousfight",0},
    {"luigiman0640",0},
    {"KeyBlader",0},
    {"Dorrieal",0},
    {"Aeza",0},
    {"SpK",0},
    {"JakeDower",0},
    {"lincrash",0},
    {"Mel",0},
    {"",0},

    {"Music",1},
    {"Teraok",0},
    {"sm64pie",0},
    {"SpK",0},
    {"",0},

    {"Title Card Artwork",1},
    {"Leonitz",0},
    {"Erableto",0},
    {"Biobak",0},
    {"",0},

    {"Additional Help",1},
    {"",0},
    {"MrComit:",0},
    {"MP64 Star Switch Model",0},
    {"",0},
    {"theCozies:",0},
    {"Screen Shaders",0},
    {"",0},
    {"Arthurtilly:",0},
    {"Rigid Body Physics",0},
    {"",0},
    {"Alex-GPTV:",0},
    {"Shotgun Detection Math",0},
    {"",0},
    {"Indigo Dindigo:",0},
    {"Funky Shell Camera Mode",0},
    {"",0},
    {"Biobak:",0},
    {"Squid Model, Optimizations",0},
    {"",0},
    {"Erableto:",0},
    {"Aku Ability Art",0},
    {"",0},
    {"MrComit & Cheezepin:",0},
    {"E.Gadd Model",0},
    {"",0},
    {"HackerN64 Team:",0},
    {"HackerSM64",0},
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
    {255, 255, 0},
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

    credits_y_offset -= (gPlayer1Controller->rawStickY/10.0f);
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