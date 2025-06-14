
s16 random_signed_value(f32 max) {
    return random_float() * random_sign() * max;
}

static void spawn_multiple_enemies(const BehaviorScript *behavior, ModelID32 modelId, u8 amount){
    u8 i;
    for (i = 0; i < amount; i++) {
        struct Object *obj = spawn_object_relative(0, random_signed_value(1500.0f), 0, random_signed_value(1500.0f), o, modelId, behavior);
        obj_scale(obj, 2.0f);
        obj->oGraphYOffset = 15;
        SET_BPARAM1(obj->oBehParams, 3);
        if(obj_has_behavior(obj, bhvOctoball)) {
            obj->oOctoballCantRespawn = TRUE;
        }
    }
}

void bhv_fight_waves_manager_loop(void) {
    struct Object *squidLoot;
    switch(o->oAction){
        case 0: //wait for mario
            if(o->oDistanceToMario < 2000){
                spawn_multiple_enemies(bhvGoomba, MODEL_OCTOBA, 5);
                play_sound(SOUND_MITM_LEVEL_C_BELL, gGlobalSoundSource);
                o->oAction++;
            }
            break;
        case 1: //wait for wave 1 to end
            if(count_objects_with_behavior(bhvGoomba) == 0){
                spawn_multiple_enemies(bhvOctoball, MODEL_OCTOBALL, 5);
                o->oAction++;
            }
            break;
        case 2: //wait for wave 2 to end
            if(count_objects_with_behavior_and_specific_s32_value(bhvOctoball, 0x1F, 1) == 0){ //count the octoball that can't respawn left
                spawn_multiple_enemies(bhvChuckya, MODEL_CHUCKYA, 5);
                o->oAction++;
            }
            break;
        case 3: //wait for wave 3 to end
            if(count_objects_with_behavior(bhvChuckya) == 0){
                create_sound_spawner(SOUND_GENERAL2_RIGHT_ANSWER);
                squidLoot = spawn_object(o, MODEL_ABILITY, bhvAbilityUnlock);
                squidLoot->oBehParams2ndByte = ABILITY_SQUID;
                o->oAction++;
            }
            break;
        case 4: //end fight
            if(o->oTimer > 20) {
                cur_obj_spawn_star_at_y_offset(6656.0f, 4172.0f, -3519.0f, 0.0f);
                o->oAction++;
            }
            break;
    }
}

//--------------------CRANE--------------------//

#define OFFSET 180
void bhv_crane_arrow_controller_init(void) {
    o->oObjF4 = spawn_object_relative_with_scale(0, OFFSET, 0, 0, 2.0f, o, MODEL_CRANE_ARROW, bhvCraneArrow);
    o->oObjF8 = spawn_object_relative_with_scale(1, -OFFSET, 0, 0, 2.0f, o, MODEL_CRANE_ARROW, bhvCraneArrow);
    o->oObjF4->oFaceAngleYaw += 0x8000;
    o->oObjFC = cur_obj_nearest_object_with_behavior(bhvCrane);
}

void bhv_crane_arrow_controller_loop(void) {
}

void bhv_crane_arrow_loop(void) {
    switch (o->oAction) {
        case PURPLE_SWITCH_ACT_IDLE:
            if (
                gMarioObject->platform == o
                && !(gMarioStates[0].action & MARIO_NO_PURPLE_SWITCH)
                && lateral_dist_between_objects(o, gMarioObject) < 150.5f
            ) {
                o->oAction = PURPLE_SWITCH_ACT_PRESSED;
            }
            break;

        case PURPLE_SWITCH_ACT_PRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 2.0f, 0.2f);
            if (o->oTimer == 3) {
                cur_obj_play_sound_2(SOUND_GENERAL2_PURPLE_SWITCH);
                o->oAction = PURPLE_SWITCH_ACT_TICKING;
                cur_obj_shake_screen(SHAKE_POS_SMALL);
#if ENABLE_RUMBLE
                queue_rumble_data(5, 80);
#endif
            }
            break;

        case PURPLE_SWITCH_ACT_TICKING:
            if (gMarioObject->platform != o) {
                    o->oAction++;
            }

            struct Object *crane = o->parentObj->oObjFC;
            if(crane != NULL){
                //if first arrow  : 30 * (1 - 0 *2) => 30 *  1 =>  30 ; so angle increment
                //if second arrow : 30 * (1 - 1 *2) => 30 * -1 => -30 ; so angle decrement
                //this calcul avoid to do one more if statement
                crane->oMoveAngleYaw += 110 * (1 - GET_BPARAM2(o->oBehParams) * 2);
                cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);
            }
            break;

        case PURPLE_SWITCH_ACT_UNPRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 0.2f, 2.0f);
            if (o->oTimer == 3) {
                o->oAction = PURPLE_SWITCH_ACT_IDLE;
            }
            break;
    }
}

void bhv_crane_init(void) {
    o->oObjF4 = spawn_object_relative_with_scale(0, 0, 800, 4000, 1.0f, o, MODEL_CRANE_HEAD, bhvCraneHead);
}

void bhv_crane_head_loop(void) {
    cur_obj_set_pos_relative(o->parentObj, 0, 900, 4200);
    o->oMoveAngleYaw = o->parentObj->oMoveAngleYaw;
    o->oFaceAnglePitch += 300;
}

void bhv_crane_rock_init(void) {
    o->oHomeY = o->oPosY;
    o->craneHeadObj = cur_obj_nearest_object_with_behavior(bhvCraneHead);
    o->oCarvingTimer = 0;
}

void bhv_crane_rock_loop(void) {
    switch(o->oAction){
        case 0: //wait
            o->craneHeadObj = cur_obj_nearest_object_with_behavior(bhvCraneHead);
            if(o->craneHeadObj != NULL) {
                if(dist_between_objects(o->craneHeadObj, o) < 1700) {
                    o->oAction++;
                }
            }
        break;

        case 1: //carve
            o->oCarvingTimer++;
            cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
            //rumble effect
            o->oPosY = o->oTimer % 2 ? o->oHomeY + 20.0f : o->oHomeY - 20.0f;
            //explode if carved enough
            if(o->oCarvingTimer > 150){
                o->oAction++;
            }
            //stop carving if the crane head is too far
            if(dist_between_objects(o->craneHeadObj, o) > 2000) {
                o->oCarvingTimer = 0;
                o->oAction = 0;
            }
        break;
        case 2: //explode
            create_sound_spawner(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION);
            spawn_mist_particles_variable(0, 0, 500.0f);
            spawn_triangle_break_particles(30, MODEL_DIRT_ANIMATION, 3.0f, 4);
            //if it was the last rock
            if(count_objects_with_behavior(bhvCraneRock) == 1){
                //play_puzzle_jingle();
                bhv_spawn_star_no_level_exit_at_object(4, gMarioObject);
            }
            obj_mark_for_deletion(o);
        break;
    }
}

//--------------------PAINT GUN--------------------//

struct ObjectHitbox sPaintGunHitbox = {
    .interactType      = INTERACT_GRABBABLE,
    .downOffset        = 50,
    .damageOrCoinValue = 0,
    .health            = 1,
    .numLootCoins      = 0,
    .radius            = 120,
    .height            = 200,
    .hurtboxRadius     = 130,
    .hurtboxHeight     = 210,
};

struct ObjectHitbox sPaintBulletHitbox = {
    .interactType      = INTERACT_DAMAGE,
    .downOffset        = 50,
    .damageOrCoinValue = 1,
    .health            = 1,
    .numLootCoins      = 0,
    .radius            = 45,
    .height            = 80,
    .hurtboxRadius     = 45,
    .hurtboxHeight     = 80,
};

void shoot(void) {
    struct Object *paintBullet = spawn_object_relative(0, 0, 0, 180, o, MODEL_PAINT_BULLET, bhvPaintBullet);
    paintBullet->oAnimState = o->oAnimState;
    cur_obj_play_sound_1(SOUND_OBJ_SNUFIT_SHOOT);
    obj_copy_angle(paintBullet, o);
}

void remove_mario_from_paint_gun(void) {
    set_mario_action(gMarioState,ACT_IDLE,0);
    gMarioState->usedObj = NULL;
    gLakituState.mode = CAMERA_MODE_8_DIRECTIONS;
    gMarioObject->header.gfx.sharedChild = gLoadedGraphNodes[ability_struct[gMarioState->abilityId].model_id];
}

void bhv_paint_gun_loop(void) {
    obj_set_hitbox(o, &sPaintGunHitbox);
    o->oInteractionSubtype = INT_SUBTYPE_NOT_GRABBABLE;

    switch(o->oAction) {
        case 0: //orange
            o->oMoveAngleYaw = o->oAngleToMario;
            obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_PITCH_INDEX, 0x1000);
            o->oFaceAnglePitch = o->oMoveAnglePitch;

            if(o->oDistanceToMario < 2500 && o->oTimer % 15 == 0) {
                shoot();
            }

            //if kicked by Mario or attacked
            if((o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED) 
            || o->oShotByShotgun == 2
            || o->oInteractStatus & INT_STATUS_MARIO_KNOCKBACK_DMG) {
                o->oAction++;
                o->oAnimState = 0;
            }
            break;

        case 1: //blue
            switch(o->oSubAction){
                case 0:
                    o->oAngleVelYaw = 0x2000;
                    o->oSubAction++;
                case 1: //pivot and slow down
                    o->oMoveAngleYaw += o->oAngleVelYaw;
                    o->oAngleVelYaw = approach_s32(o->oAngleVelYaw, 0, 0x50, 0x50);
                    if(o->oAngleVelYaw <= 0) o->oSubAction++;
                    break;
                case 2: //wait to be controlled
                    if(o->oDistanceToMario < 400) {
                        sprintf(&hud_information_string,"Press B to use");
                        if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                            o->oSubAction++;
                            obj_set_model(gMarioObject, MODEL_NONE);
                            o->oTimer = 0;
                        }
                    }
                    break;
                case 3: // Mario controls it
                    if (set_cam_angle(0) == CAM_ANGLE_AIM) {
                        set_cam_angle(CAM_ANGLE_LAKITU);
                    }

                    shock_rocket_stick_control();
                    set_mario_action(gMarioState, ACT_CUTSCENE_CONTROLLED, 0);
                    gMarioState->usedObj = o;
                    gLakituState.mode = CAMERA_MODE_PAINT_GUN;
                    if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                        shoot();
                    } else if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                        remove_mario_from_paint_gun();
                        o->oSubAction--;
                    }
                    break;
            }
            break;
    }

    //CAP PITCH TO AVOID CAMERA FLIPPING
    if (o->oMoveAnglePitch > 0x1600) o->oMoveAnglePitch = 0x1600;
    if (o->oMoveAnglePitch < -0x1800) o->oMoveAnglePitch = -0x1800;

    o->oInteractStatus = 0;
    o->oShotByShotgun = 0;
}

void bhv_paint_bullet_loop(void) {
    obj_set_hitbox(o, &sPaintBulletHitbox);
    struct Surface *surface;
    f32 ceilHeight;
    ceilHeight = find_ceil(o->oPosX, o->oPosY, o->oPosZ, &surface);
    cur_obj_update_floor_and_walls();
    obj_attack_collided_from_other_object(o);

    if(o->oTimer == 0){
        struct Object *smoke = spawn_object(o, MODEL_SMOKE, bhvSmoke);
        obj_scale(smoke, 3.0f);
    }
    if(obj_check_if_collided_with_object(o, gMarioObject) || o->oTimer > 70 || 
    o->oMoveFlags & OBJ_MOVE_HIT_WALL || (o->oPosY - o->oFloorHeight < 15) || (ceilHeight - o->oPosY < 20)){
        obj_mark_for_deletion(o);
    }

    cur_obj_move_xz_using_fvel_and_yaw();
    o->oPosY -= (sins(o->oMoveAnglePitch)) * o->oForwardVel;
}

//----------------------PAINT----------------------//

void bhv_paint_stain_init(void) {
    if(random_sign() == -1) {
        o->oAnimState = 0;
    } else {
        o->oAnimState = 1;
    }

    o->oFaceAngleYaw = random_u16();

    o->oFloatF4 = 1.0f; //scale
    cur_obj_scale(o->oFloatF4);
}

void bhv_paint_stain_loop(void) {
    struct Surface *sObjFloor;
    find_floor(o->oPosX, o->oPosY, o->oPosZ, &sObjFloor);
    Vec3f snormals = {sObjFloor->normal.x, sObjFloor->normal.y, sObjFloor->normal.z};

    mtxf_align_terrain_normal(o->transform, snormals, &o->oPosVec, o->oFaceAngleYaw);
    o->header.gfx.throwMatrix = o->transform;

    if(o->oTimer > 120) {
        o->oFloatF4 -= 0.02f;
        cur_obj_scale(o->oFloatF4);
        if(o->oFloatF4 <= 0) {
            obj_mark_for_deletion(o);
        }
    }

    //if this paint is the nearest to mario, do damage (it avoid that all the paint stains damage mario, leading to a huge life draining)
    struct Object *marioNearestPaintStain = mario_find_nearest_object_with_behavior(bhvPaintStain);
    if (marioNearestPaintStain == o && o->oDistanceToMario < 300.0f) {
        gMarioState->health -= 5;
        //render_textured_splatoon();
    }
}

//----------------------TARGET----------------------//

struct ObjectHitbox sTargetHitbox = {
    .interactType      = INTERACT_NONE,
    .downOffset        = 150,
    .damageOrCoinValue = 0,
    .health            = 1,
    .numLootCoins      = 0,
    .radius            = 200,
    .height            = 450,
    .hurtboxRadius     = 205,
    .hurtboxHeight     = 455,
};

void bhv_target_loop(void) {
    if(o->oTimer == 0) obj_set_hitbox(o, &sTargetHitbox);
    
    switch(o->oAction){
        case 0: //wait to be exploded
            if((o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED) || o->oShotByShotgun == 2){
                    spawn_triangle_break_particles(15, MODEL_DIRT_ANIMATION, 1.0f, 0);
                    if(count_objects_with_behavior(bhvLevelSplatoonTarget) == 1) { //if it was the last target
                        play_puzzle_jingle();
                        cur_obj_hide();
                        o->oAction++;
                    } else {
                        play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gGlobalSoundSource);
                        obj_mark_for_deletion(o);
                    }
            }
            break;
        case 1:
            if(o->oTimer > 50) {
                bhv_spawn_star_no_level_exit_at_object(5, gMarioObject);
                obj_mark_for_deletion(o);
            }
            break;
    }
    o->oShotByShotgun = 0;
}

void bhv_target_box_init(void) {
    o->oAnimState = GET_BPARAM4(o->oBehParams);
}

//----------------------INK WALL----------------------//

#define MOVING_TIME 203

void bhv_ink_moving_platform_loop(void) {
    if(o->oTimer <= MOVING_TIME) {
        o->oVelY = 10.0f * o->oF4;
        cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);
    } else if (o->oTimer <= MOVING_TIME + 60) {
        o->oVelY = 0.0f;
    } else {
        o->oTimer = 0;
        o->oF4 *= -1;
    }

    cur_obj_move_using_vel();
}

//----------------------OCTOZEPPLIN----------------------//

struct Object *spawn_big_explosion(f32 scale) {
    struct Object *explosion = spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
    obj_scale(explosion, scale);
    return explosion;
}

s32 oscillate_roll_with_factor(s32 factor) {
    return sins(o->oTimer * 0x1000) * DEGREES(1.0f) * (factor);
}

void bhv_octozepplin_loop(void) {
    switch(o->oAction) {
        case 0: //wandering around

            if(o->oF8 > 400) {
                o->oMoveAngleYaw += 0x8000;
                o->oF8 = 0;
            }

            struct Object *paintBullet = cur_obj_nearest_object_with_behavior(bhvPaintBullet);
            if(paintBullet != NULL && dist_between_objects(o, paintBullet) < 500) {
                obj_mark_for_deletion(paintBullet);
                o->oHealth--;
                o->oF4 = 30; //o->oF4 use as oscillation roll boost for visual animation
                if(o->oHealth < 25) spawn_big_explosion(50.0f);;
            }

            o->oFaceAngleRoll = oscillate_roll_with_factor(o->oF4);
            o->oF4 = approach_s32(o->oF4, 0, 1, 1);
            o->oPosY += 10.0f * coss(1000 * o->oTimer);

            if(o->oHealth <= 0) {
                spawn_big_explosion(50.0f);
                //remove_mario_from_paint_gun();
                cutscene_object(CUTSCENE_OCTOZEPPLIN_DEATH, o);
                o->oAction++;
            }
            break;
        case 1: //exploding
            if(o->oTimer < 120) {
                o->oFaceAngleRoll = oscillate_roll_with_factor(50);
                o->oPosY -= 10;
                o->oFaceAnglePitch -= 0x20;
                if(o->oTimer % 10 == 0) {
                    struct Object *explosion = spawn_big_explosion(80.0f);
                    s16 newX = explosion->oPosX + random_signed_value(1000.f);
                    s16 newY = explosion->oPosY + random_signed_value(1000.f);
                    s16 newZ = explosion->oPosZ + random_signed_value(1000.f);
                    obj_set_pos(explosion, newX, newY, newZ);
                }
            } else {
                cur_obj_hide();
                o->oAction++;
            }
            break;
        case 2: // dying
            if (o->oTimer == 0) spawn_big_explosion(500.0f);
            if (o->oTimer == 5) {
                obj_mark_for_deletion(o);
                spawn_default_star(-9270, 570, -2195);
                o->oAction++;
            }
            break;
    }

    o->oF8++;

}

#include "include/dialog_ids.h"

//----------------------JELLYFISH----------------------//

void jelly_fish_act_talk(void) {
    if (set_mario_npc_dialog(MARIO_DIALOG_LOOK_FRONT) == MARIO_DIALOG_STATUS_SPEAK) {
        o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;

        s32 dialogID = DIALOG_C_JELLY_GIBBERISH;
        if(using_ability(ABILITY_SQUID)) {
            switch(o->oBehParams2ndByte) {
                case 1 : dialogID = DIALOG_C_JELLY_PAINT_GUN; break;
                case 2 : dialogID = DIALOG_C_JELLY_CRANE; break;
                case 3 : dialogID = DIALOG_C_JELLY_TOWER; break;
                default : dialogID = DIALOG_C_JELLY_GIBBERISH;
            }
        }

        if (cutscene_object_with_dialog(CUTSCENE_DIALOG, o, dialogID)
            != BOBOMB_BUDDY_BP_STYPE_GENERIC) {
            set_mario_npc_dialog(MARIO_DIALOG_STOP);

            o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
            o->oBobombBuddyHasTalkedToMario = BOBOMB_BUDDY_HAS_TALKED;
            o->oInteractStatus = INT_STATUS_NONE;
            o->oAction = BOBOMB_BUDDY_ACT_IDLE;
        }
    }
}

void bhv_jelly_fish_loop(void) {
    switch (o->oAction) {
        case BOBOMB_BUDDY_ACT_IDLE:
            if (o->oDistanceToMario < 1000.0f) {
                o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x140);
            }

            if (o->oInteractStatus == INT_STATUS_INTERACTED) {
                o->oAction = BOBOMB_BUDDY_ACT_TURN_TO_TALK;
            }
            break;

        case BOBOMB_BUDDY_ACT_TURN_TO_TALK:
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x1000);

            if ((s16) o->oMoveAngleYaw == (s16) o->oAngleToMario) {
                o->oAction = BOBOMB_BUDDY_ACT_TALK;
            }

            cur_obj_play_sound_2(SOUND_ACTION_READ_SIGN);
            break;

        case BOBOMB_BUDDY_ACT_TALK:
            jelly_fish_act_talk();
            break;
    }

    set_object_visibility(o, 3000);

    o->oInteractStatus = INT_STATUS_NONE;
}

void bhv_floor_switch_teleporter(void) {
    // this convoluted setup calculates the nearest floor switch to mario and teleports it to it
    struct Object * old_o = o;
    o = gMarioObject;
    struct Object * closest_switch_location = cur_obj_nearest_object_with_behavior(bhvFloorSwitchTeleporter);
    o = old_o;

    struct Object * switcho = cur_obj_nearest_object_with_behavior(bhvFloorSwitchHiddenObjects);

    vec3f_copy(&switcho->oPosVec,&closest_switch_location->oPosVec);
}