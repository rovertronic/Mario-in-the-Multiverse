#include "levels/f/header.h"
#include "src/game/save_file.h"
#include "src/buffers/buffers.h"
#define WATCH_DISTANCE 1300.0f

u8 trinkets_shot_f = 0;

u32 targetable_behavior_list[] = {
    bhvFloorSwitchAnimatesObject,
    bhvFloorSwitchGrills,
    bhvFloorSwitchHardcodedModel,
    bhvFloorSwitchHiddenObjects,
    bhvBlueCoinSwitch,
    bhvExclamationBox,
    bhvBreakableBox,
    bhvBreakableBoxSmall,
    bhvMessagePanel,
    bhvStarPieceSwitch,
    bhvKeypad,
    bhvGMarxDoor,
    bhvWoodenLever,
    bhvFTrinket,
    bhvFblastwall,
    bhvSignOnWall,
};

struct Object *find_nearest_watch_target(void) {
    //stupid ass function
    struct Object *result;
    struct Object *closest = NULL;
    struct Object *myself = o;
    f32 closest_dist = WATCH_DISTANCE;

    for (u8 i=0; i < sizeof(targetable_behavior_list)/4; i++) {
        //shitty hack, make this function run from mario instead of the aimer itself
        o = gMarioObject;
        result = cur_obj_nearest_object_with_behavior(targetable_behavior_list[i]);
        o = myself;
        if (result) {
            f32 this_dist = dist_between_objects(gMarioObject,result);
            if (this_dist < closest_dist) {
                closest_dist = this_dist;
                closest = result;
            }
        }
    }

    return closest;
}

f32 bruh_scale = 1.0f;
struct Object *last_target = NULL;
extern u8 star_pieces_got;

void bhv_gadget_aim(void) {
    struct Object *target = find_nearest_watch_target();

    if (last_target != target) {
        last_target = target;
        bruh_scale = 1.0f;
        play_sound(SOUND_GENERAL_BOWSER_KEY_LAND, gGlobalSoundSource);
    }

    if (target) {
        vec3f_copy(&o->oPosVec,&target->oPosVec);
        cur_obj_unhide();
        cur_obj_scale(bruh_scale+1.0f);
        bruh_scale *= 0.9f;

        if (gPlayer1Controller->buttonPressed & L_TRIG) {

            struct Object * laser = spawn_object(gMarioObject,MODEL_F_LASER,bhvFLaser);
            vec3f_copy(&laser->oPosVec, mario_hand_position);
            vec3f_copy(&laser->oHomeVec,&target->oPosVec);

            //no switch cases for ptrs : (
            if (target->behavior == segmented_to_virtual(bhvBreakableBox)) {
                spawn_object(target,MODEL_EXPLOSION,bhvExplosion);
                target->oAction = BREAKABLE_BOX_ACT_BROKEN;
                spawn_mist_particles();
                spawn_triangle_break_particles(30, MODEL_DIRT_ANIMATION, 3.0f, TINY_DIRT_PARTICLE_ANIM_STATE_YELLOW);
                mark_obj_for_deletion(target);
            } else if (target->behavior == segmented_to_virtual(bhvBreakableBoxSmall)) {
                spawn_object(target,MODEL_EXPLOSION,bhvExplosion);
                target->oForwardVel = 30.0f;
                target->oMoveAngleYaw = gMarioState->faceAngle[1];
            } else if (target->behavior == segmented_to_virtual(bhvFloorSwitchGrills)) {
                target->oAction = PURPLE_SWITCH_ACT_PRESSED;
            } else if (target->behavior == segmented_to_virtual(bhvFloorSwitchAnimatesObject)) {
                target->oAction = PURPLE_SWITCH_ACT_PRESSED;
            } else if (target->behavior == segmented_to_virtual(bhvFloorSwitchHardcodedModel)) {
                target->oAction = PURPLE_SWITCH_ACT_PRESSED;
            } else if (target->behavior == segmented_to_virtual(bhvFloorSwitchHiddenObjects)) {
                target->oAction = PURPLE_SWITCH_ACT_PRESSED;
            }  else if (target->behavior == segmented_to_virtual(bhvExclamationBox)) {
                if (target->oAction == EXCLAMATION_BOX_ACT_ACTIVE) {
                    target->oAction = EXCLAMATION_BOX_ACT_EXPLODE;
                }
            } else if (target->behavior == segmented_to_virtual(bhvBlueCoinSwitch)) {
                if (target->oAction == BLUE_COIN_SWITCH_ACT_IDLE) {
                    target->oAction = BLUE_COIN_SWITCH_ACT_RECEDING;
                    // Recede at a rate of 20 units/frame.
                    target->oVelY = -20.0f;
                    // Set gravity to 0 so it doesn't accelerate when receding.
                    target->oGravity = 0.0f;
                    cur_obj_play_sound_2(SOUND_GENERAL_SWITCH_DOOR_OPEN);
                }
            } else if (target->behavior == segmented_to_virtual(bhvMessagePanel)) {
                gMarioState->usedObj = target;
                set_mario_action(gMarioState, ACT_READING_SIGN, 0);
            } else if (target->behavior == segmented_to_virtual(bhvStarPieceSwitch)) {
                if (target->oAction == BLUE_COIN_SWITCH_ACT_IDLE) {
                    target->oAction = BLUE_COIN_SWITCH_ACT_RECEDING;
                    // Recede at a rate of 20 units/frame.
                    target->oVelY = -20.0f;
                    // Set gravity to 0 so it doesn't accelerate when receding.
                    target->oGravity = 0.0f;
                    star_pieces_got = 0;
                    cur_obj_play_sound_2(SOUND_GENERAL_SWITCH_DOOR_OPEN);
                }
            } else if (target->behavior == segmented_to_virtual(bhvKeypad)) {
                gMarioState->keypad_id = target->oBehParams2ndByte;
                spawn_object(target,MODEL_EXPLOSION,bhvExplosion);
                mark_obj_for_deletion(target);
            } else if (target->behavior == segmented_to_virtual(bhvGMarxDoor)) {
                spawn_object(target,MODEL_EXPLOSION,bhvExplosionVisual);
                mark_obj_for_deletion(target);
            } else if (target->behavior == segmented_to_virtual(bhvWoodenLever)) {
                if(target->oAction == 0){
                    target->oAction = 1;
                }
            } else if (target->behavior == segmented_to_virtual(bhvFTrinket)) {
                trinkets_shot_f++;
                cur_obj_play_sound_2(SOUND_GENERAL_BOWSER_KEY_LAND);
                spawn_object(target,MODEL_EXPLOSION,bhvExplosionVisual);
                mark_obj_for_deletion(target);

                if (trinkets_shot_f == 3) {
                    spawn_default_star(-1832, 484, 2022);
                }
            } else if (target->behavior == segmented_to_virtual(bhvFblastwall)) {
                if (target->oAction == 0) {
                    target->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_BLASTWALL_2];
                    target->collisionData = segmented_to_virtual(blastwall2_collision);
                    target->oAction=1;
                }
            } else if (target->behavior == segmented_to_virtual(bhvSignOnWall)) {
                gMarioState->usedObj = target;
                set_mario_action(gMarioState, ACT_READING_SIGN, 0);
            }
        }

    } else {
        cur_obj_hide();
        bruh_scale = 1.0f;
    }
}

void bhv_fdoor_loop(void) {
    switch(o->oAction) {
        case 0:
            load_object_collision_model();
            if (gMarioState->keypad_id == o->oBehParams2ndByte) {
                o->oAction ++;
            }
        break;
        case 1:
            o->oFaceAngleYaw += 0x222;
            if (o->oTimer >= 30) {
                o->oAction++;
            }
        break;
    }
}

void bhv_ffence_loop(void) {
    switch(o->oAction) {
        case 0:
            load_object_collision_model();
            if (gMarioState->keypad_id == o->oBehParams2ndByte) {
                o->oAction ++;
            }
        break;
        case 1:
            o->oPosY += 15.0f;
            if (o->oTimer >= 30) {
                o->oAction++;
            }
        break;
    }
}

void bhv_ftrinket_loop(void) {
    switch(o->oAction) {
        case 0:
            trinkets_shot_f = 0;
            o->oAction++;
        break;
    }
    switch(o->oBehParams2ndByte) {
        case 0:
            o->oPosY = o->oHomeY + sins(o->oTimer*0x200)*20.0f;
        break;
        case 1:
            o->oFaceAnglePitch = sins(o->oTimer*0x200)*0x400;
        break;
    }
}

void bhv_fblastwall_loop(void) {
    switch(o->oAction) {
        case 1:
            for (u8 i=0; i<3; i++) {
                struct Object * boom = spawn_object(o,MODEL_EXPLOSION,bhvExplosionVisual);
                boom->oPosX += 50.0f-random_float()*100.0f;
                boom->oPosY += 50.0f-random_float()*100.0f;
                boom->oPosZ += 50.0f-random_float()*100.0f;
            }
            if (o->oTimer > 30) {
                o->oAction++;
            }
        break;
    }
}

struct ObjectHitbox sDynamiteHitbox = {
    /* interactType:      */ INTERACT_GRABBABLE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 1,
    /* numLootCoins:      */ 0,//--E
    /* radius:            */ 100,
    /* height:            */ 190,
    /* hurtboxRadius:     */ 100,
    /* hurtboxHeight:     */ 190,
};

void bhv_fdynamite_loop(void) {    
    switch (o->oHeldState) {
        case HELD_FREE:
            cur_obj_unhide();
            cur_obj_become_tangible();
            object_step();
            break;

        case HELD_HELD:
            cur_obj_hide();
            cur_obj_become_intangible();
            vec3f_copy(&o->oPosVec,gMarioState->pos);
            break;

        case HELD_THROWN:
            cur_obj_unhide();
            cur_obj_become_tangible();
            object_step();
            break;

        case HELD_DROPPED:
            cur_obj_unhide();
            cur_obj_become_tangible();
            object_step();
            break;
    }

    switch(o->oAction) {
        case 0:
            obj_set_hitbox(o, &sDynamiteHitbox);
            o->oGravity = 2.5f;
            o->oFriction = 0.8f;
            o->oBuoyancy = 1.3f;
            if (o->oHeldState == HELD_HELD) {
                o->oAction = 1;
                level_control_timer(TIMER_CONTROL_SHOW);
                gHudDisplay.timer = 450;
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_F_BOND), 0);
            }
        break;
        case 1:
            cur_obj_play_sound_1(SOUND_AIR_BOBOMB_LIT_FUSE);
            if (gHudDisplay.timer > 0) {
                gHudDisplay.timer --;
            } else {
                stop_background_music(SEQUENCE_ARGS(4, SEQ_F_BOND));

                struct Object * dynamite_waypoint = cur_obj_nearest_object_with_behavior(bhvStaticObject);
                if (dynamite_waypoint && (lateral_dist_between_objects(o,dynamite_waypoint) < 400.0f)) {
                    o->oAction = 2;
                    spawn_default_star(o->oPosX,o->oPosY+200.0f,o->oPosZ);
                } else {
                    //reset
                    if (gMarioState->heldObj != NULL) {
                        mario_drop_held_object(gMarioState);
                        set_mario_action(gMarioState, ACT_BACKWARD_AIR_KB, 0);
                    }
                    o->oAction = 0;
                    o->oHeldState = HELD_FREE;
                    spawn_object(o,MODEL_EXPLOSION,bhvExplosion);
                    vec3f_copy(&o->oPosVec,&o->oHomeVec);
                    level_control_timer(TIMER_CONTROL_HIDE);
                }
            }
        break;
        case 2:
            o->oInteractType = INT_NONE;
            cur_obj_become_intangible();
        break;
    }

    o->oInteractStatus = INT_STATUS_NONE;
}

struct ObjectHitbox sFSGkeypad = {
    /* interactType:      */ INTERACT_NONE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,//--E
    /* radius:            */ 100,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 100,
    /* hurtboxHeight:     */ 100,
};

void bhv_fsg_keypad_loop(void) {
    obj_set_hitbox(o, &sFSGkeypad);
    if (o->oShotByShotgun > 0) {
        play_sound(SOUND_GENERAL_BOWSER_KEY_LAND, gGlobalSoundSource);
        gMarioState->keypad_id = o->oBehParams2ndByte;
        mark_obj_for_deletion(o);
    }
    o->oInteractStatus = INT_STATUS_NONE;
}

void bhv_poof_on_watch(void) {
    u8 has_watch = using_ability(ABILITY_GADGET_WATCH);

    if (o->oBehParams2ndByte != has_watch) {
        o->oBehParams2ndByte = has_watch;
        spawn_mist_particles();
    }
}

void bhv_sch_board_loop(void) {
    switch(o->oAction) {
        case 0:
            o->oAction++;
            o->oHealth = 2;
        break;
        case 1:
            if (o->oHealth == 1) {
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_F_SCH_BOARD_2];
            }
            if (o->oHealth < 1) {
                spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 3.0f, 4);
                create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
                obj_mark_for_deletion(o);
            }
        break;
    }
}

void bhv_f_trapdoor(void) {
    struct Object *rocketbutton = cur_obj_nearest_object_with_behavior(bhvFRocketButtonGold);
    switch(o->oAction) {
        case 0: //wait for button press
            if (gSaveBuffer.files[gCurrSaveFileNum - 1][0].level_f_flags & (1<<LEVEL_F_FLAG_TRAPDOOR)) {
                o->oAction = 2;
            }
            if ((rocketbutton) && (rocketbutton->oAction > 0)) {
                gSaveBuffer.files[gCurrSaveFileNum - 1][0].level_f_flags |= (1<<LEVEL_F_FLAG_TRAPDOOR);
                o->oAction = 1;
            }
        break;
        case 1://wait a second
            if (o->oTimer > 30) {
                play_puzzle_jingle();
                o->oAction ++;
            }
        break;
        case 2: //lower for 5 frames
            o->oPosY -= 2.0f;
            if (o->oTimer > 5) {
                o->oAction++;
            }
        break;
        case 3://go to side
            if (o->oTimer < 30) {
                o->oPosX += 7.0f;
            }
        break;
    }
}

void bhv_f_key(void) {
    switch(o->oAction) {
        case 0:
            o->oFaceAngleYaw += 0x200;
            if (o->oDistanceToMario < 150.0f) {
                o->oAction = 1;
                o->oHomeY = 1.0f;
                gSaveBuffer.files[gCurrSaveFileNum - 1][0].level_f_flags |= (1<<LEVEL_F_FLAG_KEY);
                save_file_do_save(gCurrSaveFileNum - 1);
                cur_obj_play_sound_2(SOUND_GENERAL_BOWSER_KEY_LAND);
            }
        break;
        case 1:
            o->oAngleVelYaw += 0x70;
            o->oFaceAngleYaw += o->oAngleVelYaw;
            cur_obj_scale(o->oHomeY);
            o->oHomeY = o->oHomeY *.98f;
            if (o->oHomeY < .2f) {
                obj_mark_for_deletion(o);
            }
        break;
    }
}

static struct ObjectHitbox sFshooterHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 1,
    /* numLootCoins:      */ 3,
    /* radius:            */ 60,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 60,
    /* hurtboxHeight:     */ 160,
};

void bhv_f_shooter(void) {
    u16 view_angle = ABS(o->oAngleToMario-o->oFaceAngleYaw);
    
    Vec3f hitPos;
    struct Surface * surf = NULL;

    Vec3f bullet_origin = //where the bullet spawns relative to the enemy
    {o->oPosX+(sins(o->oFaceAngleYaw)*50.0f)+(sins(o->oFaceAngleYaw-0x4000)*30.0f),
    o->oPosY+155.0f,
    o->oPosZ+(coss(o->oFaceAngleYaw)*50.0f)+(coss(o->oFaceAngleYaw-0x4000)*30.0f)};

    Vec3f ray_start = {o->oPosX,o->oPosY+100.0f,o->oPosZ};
    Vec3f ray_vector = {gMarioState->pos[0]-o->oPosX,(gMarioState->pos[1]-o->oPosY)+100.0f,gMarioState->pos[2]-o->oPosZ};
    if (o->oDistanceToMario < 2500.0f) {
        find_surface_on_ray(ray_start, ray_vector, &surf, hitPos, (RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL | RAYCAST_FIND_WALL));
    }

    switch(o->oAction) {
        case 0:
            o->oAction=1;
            obj_set_hitbox(o, &sFshooterHitbox);
            cur_obj_scale(1.5f);
            o->oGravity = -2.0f;
        break;
        case 1: //patrol
            o->oAnimState = 1; //no muzzle flash
            if ((view_angle < 0x3000)&&(o->oDistanceToMario < 1500.0f)&&(!surf)) {
                o->oAction = 2;
            }
            if (o->oShotByShotgun > 0) {
                o->oShotByShotgun = 0;
                o->oAction = 2;
            }
        break;
        case 2: //attack
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x500);
            o->oFaceAngleYaw = o->oMoveAngleYaw;

            //fire every 5 frames and if mario's in sightlines
            o->oAnimState = 1;
            if ((o->oTimer % 5 == 0)&&(view_angle < 0x1500)&&(!surf)) {
                o->oAnimState = 0;
                cur_obj_play_sound_2(SOUND_OBJ2_EYEROK_SOUND_LONG);
                o->oFaceAnglePitch = -obj_turn_pitch_toward_mario(0.0f, 0x2000);
                dobj_spawn_bullet(bullet_origin,o->oFaceAnglePitch,o->oFaceAngleYaw);
                o->oFaceAnglePitch = 0;
            }

            if (o->oDistanceToMario > 2500.0f) {
                o->oAction = 1; //patrol
            }
        break;
    }

    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
            spawn_mist_particles();
            obj_spawn_loot_yellow_coins(o, o->oNumLootCoins, 20.0f);
            obj_mark_for_deletion(o);
        }
    }

    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(78);

    o->oInteractStatus = INTERACT_NONE;
}

void bhv_f_shooter_star(void) {
    switch(o->oAction) {
        case 0:
            if (!cur_obj_nearest_object_with_behavior(bhvFshooter)) {
                spawn_default_star(o->oPosX,o->oPosY,o->oPosZ);
                o->oAction++;
            }
        break;
    }
}

void bhv_f_keydoor(void) {
    switch(o->oAction) {
        case 0:
            load_object_collision_model();
            if (gSaveBuffer.files[gCurrSaveFileNum - 1][0].level_f_flags & (1<<LEVEL_F_FLAG_KEY)) {
                cur_obj_init_animation_with_sound(0);
                o->oAction++;
            }
        break;
    }
}

void bhv_f_curtainplatform(void) {
    switch(o->oAction) {
        case 0:
            if (gSaveBuffer.files[gCurrSaveFileNum - 1][0].level_f_flags & (1<<LEVEL_F_FLAG_MISSILE)) {
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_CURTAINPLATFORM2];
                o->oAction = 2;
                struct Object * missiles = spawn_object(o,MODEL_F_MISSILES,bhvFMissiles);
                missiles->oAction = 2;
            }
            if (gMarioState->keypad_id == o->oBehParams2ndByte) {
                gSaveBuffer.files[gCurrSaveFileNum - 1][0].level_f_flags |= (1<<LEVEL_F_FLAG_MISSILE);
                o->oAction = 1;
                struct Object * missiles = spawn_object(o,MODEL_F_MISSILES,bhvFMissiles);
                missiles->oPosZ += 6000.0f;
                missiles->oAction = 0;
                gCamera->cutscene = 1;
            }
            break;
        case 1:
            if (o->oTimer >= 60) {
                create_sound_spawner(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION);
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_CURTAINPLATFORM2];
                o->oAction++;
            }
            break;
        case 2:
            load_object_static_model();
            o->oAction ++;
            break;
    }
}

void bhv_f_missiles(void) {
    switch(o->oAction) {
        case 0:
            vec3f_copy(&gLakituState.goalFocus,&o->oPosVec);
            gLakituState.goalPos[0] = -23953;
            gLakituState.goalPos[1] = 1000;
            gLakituState.goalPos[2] = -7278;

            if (o->parentObj->oAction != 2) {
                o->oPosZ -= 100.0f;
            } else {
                o->oAction++;
            }
        break;
        case 1:
            vec3f_copy(&gLakituState.goalFocus,&o->oPosVec);
            gLakituState.goalPos[0] = -23953;
            gLakituState.goalPos[1] = 1000;
            gLakituState.goalPos[2] = -7278;

            if (o->oTimer > 30) {
                o->oAction++;
                gCamera->cutscene = 0;
            }
        break;
    }
}

void bhv_f_blowvent(void) {
    struct Object * curtain_platform = cur_obj_nearest_object_with_behavior(bhvFCurtainPlatform);
    if ((curtain_platform)&&(curtain_platform->oAction == 3)) {
        cur_obj_spawn_strong_wind_particles(12, 3.0f, 0.0f, -50.0f, 120.0f);
    }
}

struct ObjectHitbox sFBoatHitbox = {
    .interactType      = INTERACT_KOOPA_SHELL,
    .downOffset        = 0,
    .damageOrCoinValue = 4,
    .health            = 1,
    .numLootCoins      = 1,
    .radius            = 50,
    .height            = 200,
    .hurtboxRadius     = 50,
    .hurtboxHeight     = 50,
};

void bhv_f_boat(void) {
    struct Surface *floor;

    obj_set_hitbox(o, &sFBoatHitbox);
    cur_obj_scale(1.0f);

    switch (o->oAction) {
        case KOOPA_SHELL_ACT_MARIO_NOT_RIDING:
            if (o->oTimer > 30) {
                cur_obj_become_tangible();
            }

            load_object_collision_model();

            cur_obj_update_floor_and_walls();
            cur_obj_if_hit_wall_bounce_away();

            if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                o->oAction = KOOPA_SHELL_ACT_MARIO_RIDING;
                gMarioState->pos[1] = o->oPosY;
                gMarioState->faceAngle[1] = o->oFaceAngleYaw;
            }

            cur_obj_move_standard(-20);
            koopa_shell_spawn_sparkles(10.0f);
            o->oForwardVel *= 0.98f;
            o->oFaceAngleRoll *= 0.9f;
            break;

        case KOOPA_SHELL_ACT_MARIO_RIDING:
            obj_copy_pos(o, gMarioObject);
            o->oPosX += sins(gMarioState->faceAngle[1])*gMarioState->forwardVel;
            o->oPosZ += coss(gMarioState->faceAngle[1])*gMarioState->forwardVel;
            //^ this code is needed to accomodate for the 1 frame of delay
            floor = cur_obj_update_floor_height_and_get_floor();

            if (absf(find_water_level(o->oPosX, o->oPosZ) - o->oPosY) < 10.0f) {
                koopa_shell_spawn_water_drop();
            } else if (absf(o->oPosY - o->oFloorHeight) < 5.0f) {
                if (floor != NULL && floor->type == SURFACE_BURNING) {
                    bhv_koopa_shell_flame_spawn();
                } else {
                    koopa_shell_spawn_sparkles(10.0f);
                }
            } else {
                koopa_shell_spawn_sparkles(10.0f);
            }

            o->oFaceAngleYaw = gMarioObject->oMoveAngleYaw;
            o->oFaceAngleRoll = gMarioState->angleVel[1]*-3;
            o->oForwardVel = gMarioState->forwardVel;

            if (o->oInteractStatus & INT_STATUS_STOP_RIDING) {
                gMarioState->pos[1] += 150.0f;
                o->oMoveAngleYaw = gMarioState->faceAngle[1];
                o->oAction = KOOPA_SHELL_ACT_MARIO_NOT_RIDING;
                cur_obj_become_intangible();
            }
            break;
    }

    o->oOpacity = o->oForwardVel*5;
    if (o->oForwardVel*5 < 0.0f) {
        o->oOpacity = 0;
    }
    if (o->oForwardVel*5 > 255.0f) {
        o->oOpacity = 255;
    }

    o->oInteractStatus = INT_STATUS_NONE;
}

struct ObjectHitbox sHelicopterHitbox = {
    .interactType      = INTERACT_DAMAGE,
    .downOffset        = 200,
    .damageOrCoinValue = 4,
    .health            = 3,
    .numLootCoins      = 0,
    .radius            = 400,
    .height            = 400,
    .hurtboxRadius     = 400,
    .hurtboxHeight     = 400,
};

void bhv_f_heli(void) {
    Vec3f bullet_origin = //where the bullet spawns relative to the helicopter
    {o->oPosX+(sins(o->oFaceAngleYaw)*150.0f), o->oPosY-155.0f, o->oPosZ+(coss(o->oFaceAngleYaw)*150.0f)};

    switch(o->oAction) {
        case 0: //Hidden. Wait until proper conditions are met for the battle to start.
            o->oAnimState = 1;
            cur_obj_hide();
            obj_set_hitbox(o, &sHelicopterHitbox);
            if (!cur_obj_nearest_object_with_behavior(bhvFshooter) && save_file_check_ability_unlocked(ABILITY_GADGET_WATCH)) {
                if (o->oTimer > 30) {
                    cur_obj_unhide();
                    o->oAction = 1;
                    play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_F_BOND), 0);
                    gCamera->cutscene = 1;
                    o->prevObj = spawn_object(o,MODEL_F_HELISHADOW,bhvStaticObject);
                    o->prevObj->oPosY = 600.0f;
                }
            } else {
                o->oTimer = 0;
            }
            break;
        case 1: //Drop in cutscene.
            o->oPosY = approach_f32_asymptotic(o->oPosY,o->oHomeY-800.0f,0.02f);
            vec3f_copy(&gLakituState.goalFocus,&o->oPosVec);
            vec3f_copy(&gLakituState.goalPos,&o->oHomeVec);
            gLakituState.goalPos[0] -= 4000.0f;
            gLakituState.goalPos[2] += 2000.0f;
            if (o->oTimer > 90) {
                o->oAction = 2;
                gCamera->cutscene = 0;
            }
            break;

        case 2: //Patrol and fire
            switch(o->oSubAction) {
                case 0: //patrol forward
                    if (o->oVelX > -45.0f) {
                        o->oVelX -= 0.4f;
                    }
                    if (o->oPosX < o->oHomeX-8000.0f) {
                        o->oSubAction = 1;
                    }
                    break;
                case 1: //patrol backward
                    if (o->oVelX < 45.0f) {
                        o->oVelX += 0.4f;
                    }
                    if (o->oPosX > o->oHomeX-2500.0f) {
                        o->oSubAction = 0;
                    }
                    break;
            }

            if (o->oShotByShotgun > 0) {
                // The helicopter is too strong to be beat by the shotgun ツ
                cur_obj_play_sound_2(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL);
            }

            if ((o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED)) {
                gCamera->cutscene = 1;
                o->oAction = 3;
                o->oHealth --;
            }

            // Fire at the player every 100 frames for 100 frames (200 frame cycle)
            o->oAnimState = 1;
            if (o->oTimer%200>99) {
                if (o->oTimer%3==0) {
                    o->oAnimState = 0;
                    cur_obj_play_sound_2(SOUND_OBJ2_EYEROK_SOUND_LONG);
                    o->oFaceAnglePitch = obj_turn_pitch_toward_mario(0.0f, 0x4000);
                    struct Object * bullet = spawn_object(o,MODEL_BOWLING_BALL,bhvHeliBalls);
                    bullet->oMoveAnglePitch = o->oFaceAnglePitch-0x280+(random_u16()%0x500);
                    bullet->oMoveAngleYaw = o->oFaceAngleYaw-0x280+(random_u16()%0x500);
                    vec3f_copy(&bullet->oPosVec,bullet_origin);
                    o->oFaceAnglePitch = 0;
                }
            }

            o->oPosX += o->oVelX;
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x500);
            o->oFaceAngleYaw = o->oMoveAngleYaw;

            o->prevObj->oPosX = o->oPosX;
            o->prevObj->oPosZ = o->oPosZ;
            o->prevObj->oFaceAngleYaw = o->oFaceAngleYaw;
            break;

        case 3: // Damaged
            vec3f_copy(&gLakituState.goalFocus,&o->oPosVec);
            vec3f_copy(&gLakituState.goalPos,&o->oPosVec);
            gLakituState.goalPos[0] -= 3000.0f;
            gLakituState.goalPos[1] += 3000.0f;
            gLakituState.goalPos[2] += 3000.0f;

            cur_obj_become_intangible();
            if (big_boo_update_during_nonlethal_hit(40.0f)) {
                if (o->oHealth < 1) {
                    //die
                    o->oAction = 4;
                    o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_F_HELIDEAD];
                    stop_background_music(SEQUENCE_ARGS(4, SEQ_F_BOND));
                } else {
                    //return to patrol
                    o->oAction = 2;
                    gCamera->cutscene = 0;
                    o->oFaceAnglePitch = 0;
                    o->oFaceAngleRoll = 0;
                }
            }
            break;

        case 4: // Defeated P1
            cur_obj_become_intangible();
            o->oPosY -= 15.0f;
            o->oMoveAngleYaw += 0x800;
            o->oFaceAngleYaw = o->oMoveAngleYaw;

            o->prevObj->oPosX = o->oPosX;
            o->prevObj->oPosZ = o->oPosZ;
            o->prevObj->oFaceAngleYaw = o->oFaceAngleYaw;

            if (o->oPosY < 700.0f) {
                create_sound_spawner(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION);
                o->oAction = 5;
            }
            break;

        case 5: // Defeated P2
            if (o->oTimer == 60) {
                gCamera->cutscene = 0;
            }
            if (o->oTimer > 60) {
                spawn_mist_particles_variable(0, 0, 100.0f);
                spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 3.0f, 4);
                cur_obj_shake_screen(SHAKE_POS_SMALL);
                create_sound_spawner(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION);
                spawn_default_star(o->oHomeX,o->oHomeY-1300.0f,o->oHomeZ);
                mark_obj_for_deletion(o->prevObj);
                mark_obj_for_deletion(o);
            }
            break;
    }

    if (o->oTimer % 8 == 0) {
        for (u8 i = o->oHealth; i<3; i++) {
            spawn_object_relative(0, 100.0f-(random_float()*200.0f), 200, 100.0f-(random_float()*200.0f), o, MODEL_BURN_SMOKE, bhvBlackSmokeHoodboomer);
        }
    }

    if ((o->oAction != 0)&&(gMarioState->pos[2] > -6288.0f)) {
        // Keep mario in boss area
        gMarioState->pos[2] = -6288.0f;
        gMarioObject->oPosZ = gMarioState->pos[2];
    }

    o->oInteractStatus = INT_STATUS_NONE;
    o->oShotByShotgun = 0;
}

void bhv_f_laser(void) {
    Vec3f origin;
    Vec3f dir;
    Vec3f hitpos;
    f32 a, b;

    vec3f_copy(origin, mario_hand_position); // Source
    vec3f_copy(hitpos,&o->oHomeVec); // Target

    dir[0] = hitpos[0] - origin[0];
    dir[1] = hitpos[1] - origin[1];
    dir[2] = hitpos[2] - origin[2];

    o->header.gfx.scale[2] = (sqrtf(dir[0]*dir[0] + dir[1]*dir[1] + dir[2]*dir[2])/100.0f);

    a=hitpos[0] - o->oPosX;
    b=hitpos[2] - o->oPosZ;

    o->oFaceAngleYaw = atan2s(b,a);
    o->oFaceAnglePitch = atan2s( sqrtf((a*a) + (b*b)) ,origin[1]-hitpos[1]);

    if (o->oTimer > 1) {
        mark_obj_for_deletion(o);
    }
}