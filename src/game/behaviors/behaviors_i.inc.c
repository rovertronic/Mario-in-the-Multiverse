//behaviors_i.inc.c

#define DELAY 30

/******************************Shock Rocket**********************************/

struct ObjectHitbox sShockRocketHitbox = {
    .interactType      = INTERACT_NONE,
    .downOffset        = 50,
    .damageOrCoinValue = 0,
    .health            = 1,
    .numLootCoins      = 0,
    .radius            = 100,
    .height            = 100,
    .hurtboxRadius     = 100,
    .hurtboxHeight     = 100,
};

void shock_rocket_stick_control(void){
    s16 stickX = gPlayer1Controller->rawStickX;
    s16 stickY = gPlayer1Controller->rawStickY;
    if (stickX < 10 && stickX > -10) stickX = 0;
    if (stickY < 10 && stickY > -10) stickY = 0;
    if (find_water_level(o->oPosX, o->oPosZ) > o->oPosY) {
        o->oMoveAngleYaw -= 5 * stickX * ability_chronos_current_slow_factor();
        o->oMoveAnglePitch -= 5 * stickY * ability_chronos_current_slow_factor();
        o->oForwardVel = 20.0f;
    } else {
        o->oMoveAngleYaw -= 10 * stickX * ability_chronos_current_slow_factor();
        o->oMoveAnglePitch -= 10 * stickY * ability_chronos_current_slow_factor();
        o->oForwardVel = 30.0f;
    }
    //CAP PITCH TO AVOID CAMERA FLIPPING
    if (o->oMoveAnglePitch > 0x3FFC) o->oMoveAnglePitch = 0x3FFC;
    if (o->oMoveAnglePitch < -0x3FF0) o->oMoveAnglePitch = -0x3FF0;
}

void shock_rocket_quit(void){
    gMarioObject->header.gfx.sharedChild = gLoadedGraphNodes[ability_struct[gMarioState->abilityId].model_id];
    obj_mark_for_deletion(o);
    if(!(gMarioState->action & ACT_FLAG_INVULNERABLE)){
       gMarioState->actionState = 2;
    }

    gLakituState.mode = o->oPreviousLakituCamMode;
}

void shock_rocket_armed(void){
    shock_rocket_stick_control();
    obj_set_model(gMarioObject, MODEL_NONE);

    o->oPosX = gMarioObject->oPosX;
    o->oPosY = gMarioObject->oPosY + 100;
    o->oPosZ = gMarioObject->oPosZ;

    if (o->oTimer == 0) {
        o->oDrawingDistance = 32000.0f;
        gMarioState->usedObj = o;
        o->oPreviousLakituCamMode = gLakituState.mode;
        gLakituState.mode = CAMERA_MODE_SHOCK_ROCKET;
    }

    if (gPlayer1Controller->buttonPressed & B_BUTTON) {
        cur_obj_play_sound_2(SOUND_OBJ_POUNDING_CANNON);
        cur_obj_shake_screen(SHAKE_POS_SMALL);
        obj_set_hitbox(o, &sShockRocketHitbox);
        o->oAction++;
    }

    if((gMarioState->action & ACT_FLAG_INVULNERABLE)) {
        o->oAction = 2;
    }


    // if Mario interupted, Rocket dismiss
    if (o->oTimer > 5 && ((gMarioState->action != ACT_IDLE) || gPlayer1Controller->buttonPressed & L_TRIG)) {
        shock_rocket_quit();
    }
}

void shock_rocket_move(void){
    f32 ceilHeight;

    if (o->oTimer == 5) {
        gMarioObject->header.gfx.sharedChild = gLoadedGraphNodes[ability_struct[gMarioState->abilityId].model_id];
        o->oInteractType = INTERACT_DAMAGE; 
    }

    //collision
    obj_attack_collided_from_other_object(o);
    cur_obj_update_floor_and_walls();
    play_sound(SOUND_AIR_BOBOMB_LIT_FUSE, gGlobalSoundSource);

    //control and moving
    shock_rocket_stick_control();
    o->oPosX += (sins(o->oMoveAngleYaw) * coss(o->oMoveAnglePitch)) * o->oForwardVel * ability_chronos_current_slow_factor();
    o->oPosY -= (sins(o->oMoveAnglePitch)) * o->oForwardVel * ability_chronos_current_slow_factor();
    o->oPosZ += (coss(o->oMoveAngleYaw) * coss(o->oMoveAnglePitch)) * o->oForwardVel * ability_chronos_current_slow_factor();

    //visual animation
    o->oMoveAngleRoll =  sins(o->oTimer * 0x1000) * DEGREES(1.0f);
    if (find_water_level(o->oPosX, o->oPosZ) > o->oPosY) {
        spawn_object(o, MODEL_BUBBLE, bhvRocketSmoke);
    } else {
        spawn_object(o, MODEL_SMOKE, bhvRocketSmoke);
    }
    

    //Rocket Explose
    struct Surface *surface;
    ceilHeight = find_ceil(o->oPosX, o->oPosY, o->oPosZ, &surface);
    if (o->oTimer > 300 
        || o->oMoveFlags & OBJ_MOVE_HIT_WALL || (o->oPosY - o->oFloorHeight < 35) || (ceilHeight - o->oPosY < 25)
        || (o->oInteractStatus & INT_STATUS_INTERACTED) || (o->numCollidedObjs > 0 && o->oInteractType == INTERACT_DAMAGE)
        || (gPlayer1Controller->buttonPressed & B_BUTTON)) {
        o->oAction++;
    }

    //Mario interupted
    if(gMarioState->action != ACT_IDLE){
        spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
        shock_rocket_quit();
    }
}

void shock_rocket_wait_before_quitting(){
    if(o->oTimer == 0){
        spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
        cur_obj_disable();
        o->oForwardVel = 0;
    }

    if(o->oTimer == DELAY){
        shock_rocket_quit();
    }
}

void bhv_shock_rocket_loop(void) {
    switch(o->oAction){
        case SHOCK_ROCKET_ACT_ARMED:
        shock_rocket_armed();
        break;

        case SHOCK_ROCKET_ACT_MOVE:
        shock_rocket_move();
        break;

        case SHOCK_ROCKET_ACT_WAIT_BEFORE_QUITING:
        shock_rocket_wait_before_quitting();
        break;
    }
}

/*********************************Smoke*************************************/

void bhv_rocket_smoke_init(void) {
    cur_obj_scale((random_float() * 2 + 2.0) / 15);
}

/*********************************Button*************************************/

void rocket_button_off() {
    obj_set_model(o, o->oModelStateOFF);
    
    if((o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED) || o->oShotByShotgun == 2){
        o->oAction++;
    }
}

void rocket_button_on() {
    s32 buttonToggleGroupSucceded = 0;
    if(o->oTimer == 0){
        obj_set_model(o, o->oModelStateON);
        play_sound(SOUND_GENERAL2_PURPLE_SWITCH, gGlobalSoundSource);
    }

    if(o->oTimer > DELAY){
    //if Bparam 2 is set, represent a timer for the button to stay on, after what it goes off again
        if(o->oBehParams2ndByte != 0){
            buttonToggleGroupSucceded = count_objects_with_behavior_bparam1_action(bhvRocketButtonGroup, o->oBehParams >> 24, 1);
            if(!buttonToggleGroupSucceded){
                if ((o->oBehParams2ndByte * 5) - o->oTimer <  90) {
                    play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
                } else {
                    play_sound(SOUND_GENERAL2_SWITCH_TICK_FAST, gGlobalSoundSource);
                }
            }

            // time over
            if (o->oTimer > o->oBehParams2ndByte * 5 && !buttonToggleGroupSucceded){
                o->oAction--;
            }
        }
    }

}

void bhv_rocket_button_loop(void) {
    switch(o->oAction){
        case ROCKET_BUTTON_ACT_OFF:
        rocket_button_off();
        break;

        case ROCKET_BUTTON_ACT_ON:
        rocket_button_on();
        break;
    }

    o->oInteractStatus = INT_STATUS_NONE;
    o->oShotByShotgun = 0;
}

void bhv_rocket_button_init(void){
    //if Bparam 3 is set, change the model ID for the ON state
    o->oModelStateON = ((o->oBehParams >> 8) & 0xFF);
    if (o->oModelStateON == 0) o->oModelStateON = MODEL_ROCKET_BUTTON_ON;
    //if Bparam 4 is set, change the model ID for the OFF state
    o->oModelStateOFF = ((o->oBehParams) & 0xFF);
    if (o->oModelStateOFF == 0) o->oModelStateOFF = MODEL_ROCKET_BUTTON_OFF;
}

void bhv_rocket_button_group_loop(void){
    if(o->oAction == ROCKET_BUTTON_GROUP_WAITING && 
        count_objects_with_behavior_bparam1_action(bhvRocketButton, o->oBehParams >> 24, ROCKET_BUTTON_ACT_OFF) == 0){
        if(o->oBehParams2ndByte == 0)
            play_puzzle_jingle();
        o->oAction = ROCKET_BUTTON_GROUP_SUCCESSFUL;
    }
}

/*********************************hoodmonger*************************************/

void bhv_hoodmonger_init(void){
    o->oDeathSound = SOUND_MITM_LEVEL_I_HOODMONGER_DEATH1;
    o->oIsLootingRocket = (GET_BPARAM1(o->oBehParams) == 1);
    if(o->oIsLootingRocket) {
        o->oDollarDropObj = spawn_object_rel_with_rot(o, MODEL_KOOPA_SHELL, bhvPushableMetalBox, 0, 500, 0, 0, 0, 0);
    }
    //if first star get, delete all hoodmonger with Bparam 2 set to 1
    if (save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_CCM)) & STAR_FLAG_ACT_1 && 
        GET_BPARAM2(o->oBehParams) == 1
        ) {
        obj_mark_for_deletion(o);
    }
}

void bhv_hoodmonger_loop(void){
    o->oSubAction = o->oWantedSubAction;

    switch(o->oAction){
        case HOODMONGER_ACTION_WANDERING:

            switch(o->oSubAction){
                case HOODMONGER_WANDERING_SUBACTION_WAIT:
                    cur_obj_init_animation(HOODMONGER_ANIM_WANDERING);
                    if(o->oDistanceToMario < 2500){
                        if(o->oIsLootingRocket){  //special hoodmonger looting rocket
                            o->oAction = HOODMONGER_ACTION_ALERTED;
                            o->oWantedSubAction = HOODMONGER_ALERTED_SUBACTION_SHOOTING;
                            o->oShootingCooldown = 20;
                        } else {
                            o->oWantedSubAction = HOODMONGER_WANDERING_SUBACTION_START_ALERT;
                        }
                        cur_obj_play_sound_2(SOUND_MITM_LEVEL_I_HOODMONGER_ALERT);
                    }
                    break;

                case HOODMONGER_WANDERING_SUBACTION_START_ALERT:
                    obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x1000);
                    if(cur_obj_init_anim_check_frame(HOODMONGER_ANIM_ALERT, 24)){
                        o->oAction = HOODMONGER_ACTION_ALERTED;
                        o->oWantedSubAction = HOODMONGER_ALERTED_SUBACTION_END_ALERT;
                    }
                    break;
            }
            break;

        case HOODMONGER_ACTION_ALERTED:
            switch(o->oSubAction){
                case HOODMONGER_ALERTED_SUBACTION_END_ALERT:
                    if(cur_obj_init_animation_and_check_if_near_end(HOODMONGER_ANIM_ALERT)){
                        o->oWantedSubAction = HOODMONGER_ALERTED_SUBACTION_SHOOTING;
                        o->oShootingCooldown = 0;
                    }
                    break;

                case  HOODMONGER_ALERTED_SUBACTION_SHOOTING:
                    if(o->oShootingCooldown <= 0){
                        struct Object *bullet = spawn_object_relative(0, 0, 110, 200, o, MODEL_HOODMONGER_BULLET, bhvHoodmongerBullet);
                        bullet->oMoveAnglePitch = o->oMoveAnglePitch;
                        //spawn_object_rel_with_rot(o, MODEL_HOODMONGER_BULLET, bhvHoodmongerBullet, 0, 110, 200, o->parentObj->oMoveAnglePitch, o->parentObj->oMoveAngleYaw, 0);
                        create_sound_spawner(SOUND_MITM_LEVEL_I_HOODMONGER_SHOT);
                        cur_obj_init_animation_and_anim_frame(HOODMONGER_ANIM_SHOOT, 0);
                        o->oShootingCooldown = 50;
                    } else {
                        cur_obj_extend_animation_if_at_end();
                    }
                    if(o->oDistanceToMario < 300){
                        o->oWantedSubAction = HOODMONGER_ALERTED_SUBACTION_PARRY;
                        cur_obj_play_sound_2(SOUND_MITM_LEVEL_I_HOODMONGER_PARRY);
                    }
                    if(o->oShootingCooldown == 40 && o->oDistanceToMario < 1000){
                        create_sound_spawner(SOUND_MITM_LEVEL_I_HOODMONGER_RELOAD);
                    }
                    o->oShootingCooldown -= 1 * ability_chronos_current_slow_factor();
                    break;

                case HOODMONGER_ALERTED_SUBACTION_PARRY:
                    o->oShootingCooldown -= 1 * ability_chronos_current_slow_factor();
                    if(cur_obj_init_animation_and_check_if_near_end(3)){
                        o->oWantedSubAction = HOODMONGER_ALERTED_SUBACTION_SHOOTING;
                    }
                    break;
            }
            obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x1000);
            obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_PITCH_INDEX, 0x1000);
            if(o->oDistanceToMario > 3000){
                o->oLoosingTriggerCooldown += 1 * ability_chronos_current_slow_factor();
                if(o->oLoosingTriggerCooldown > 200){
                    o->oAction = HOODMONGER_ACTION_WANDERING;
                    o->oWantedSubAction = HOODMONGER_WANDERING_SUBACTION_WAIT;
                    o->oLoosingTriggerCooldown = 0;
                }
            } else {
                o->oLoosingTriggerCooldown = 0;
            }
            break;
    }
    
    if((o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED) || o->oShotByShotgun == 1){
        o->oHealth--;
        create_sound_spawner(o->oDeathSound);
        obj_die_if_health_non_positive();
        if(o->oIsLootingRocket){
            
        }
    }

    if(o->oIsLootingRocket && o->oDollarDropObj != NULL){
        obj_set_pos(o->oDollarDropObj, o->parentObj->oPosX, o->parentObj->oPosY + 500, o->parentObj->oPosZ);
    }

    o->oNearestHoodmongerWandering = cur_obj_nearest_object_with_behavior_and_action(bhvHoodmonger, HOODMONGER_ACTION_WANDERING); //find nearest hoodmonger not alerted

}

void bhv_hoodmonger_alert_manager_loop(void){
    struct Object *alertedhoodmonger = cur_obj_nearest_object_with_behavior_and_action(bhvHoodmonger, 1);
    struct Object *wanderinghoodmonger;
    if(alertedhoodmonger != NULL && GET_BPARAM1(alertedhoodmonger->oBehParams) == 0){ //if a hoodlum is alerted
        play_hoodlum_fight_music();
        wanderinghoodmonger = alertedhoodmonger->oNearestHoodmongerWandering;
        //and existing wandering hoodlum nearby AND not losing trigger on Mario
        if( wanderinghoodmonger != NULL && 
            dist_between_objects(wanderinghoodmonger, alertedhoodmonger) < 7000 &&
            GET_BPARAM1(wanderinghoodmonger->oBehParams) == 0 &&
            alertedhoodmonger->oLoosingTriggerCooldown == 0)
        {
            wanderinghoodmonger->oAction = HOODMONGER_ACTION_ALERTED; //alert the wandering hoodlum
            wanderinghoodmonger->oWantedSubAction = HOODMONGER_ALERTED_SUBACTION_SHOOTING; //directly shoot and skipping end-alerte phase
            wanderinghoodmonger->oShootingCooldown = 20;
        }
    } else {
        stop_hoodlum_fight_music();
    }
}

void bhv_hoodmonger_bullet_loop(void) {
    if(obj_check_if_collided_with_object(o, gMarioObject) || o->oTimer > 100){
        obj_mark_for_deletion(o);
    }

    cur_obj_move_xz_using_fvel_and_yaw();
    int maxAngle = degrees_to_angle(20);
    if(ABS(o->oMoveAnglePitch) > maxAngle){
        if(o->oMoveAnglePitch < 0) {
            o->oMoveAnglePitch = -maxAngle;
        } else { 
            o->oMoveAnglePitch = maxAngle;
        }
    }
    o->oVelY = sins(o->oMoveAnglePitch) * o->oForwardVel;
    o->oPosY -= o->oVelY;
}

/*********************************Hoodboomer*************************************/

void bhv_hoodboomer_loop(void){

    o->oDeathSound = SOUND_MITM_LEVEL_I_HOODBOOMER_DEATH;
    obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x800);

    switch(o->oAction){
        case 0: //laughing
            cur_obj_init_animation(0);

            if(dist_between_objects(o, gMarioObject) < 2500 && o->oLaunchingBombCooldown <= 0){
                if(cur_obj_init_animation_and_check_if_near_end(0)) {
                    o->oAction++;
                }
            }
            break;

        case 1: //throwing grenade
            if(cur_obj_init_anim_check_frame(1, 14)){
                struct Object *bomb = spawn_object_relative(0, 0, 200, 0, o, MODEL_HOODBOOMER_BOMB, bhvHoodboomerBomb);
                SET_BPARAM1(bomb->oBehParams, 200);
                SET_BPARAM2(bomb->oBehParams, 200);
                SET_BPARAM3(bomb->oBehParams, 200);
            }
            if(cur_obj_init_animation_and_check_if_near_end(1)){
                o->oLaunchingBombCooldown = 150;
                o->oAction--;
            }
            break;
    }

    if((o->oTimer % 15) == 0){
        spawn_object(o, MODEL_BURN_SMOKE, bhvBlackSmokeHoodboomer);
    }

    if((o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED) || o->oShotByShotgun == 2){
        o->oHealth--;
        create_sound_spawner(o->oDeathSound);
        obj_die_if_health_non_positive();
    }

    if(o->oLaunchingBombCooldown > 0){
        o->oLaunchingBombCooldown--;
    }

    if((o->oTimer % 300) == 0 && o->oDistanceToMario < 3000){
        if(random_sign() == 1) 
            cur_obj_play_sound_2(SOUND_MITM_LEVEL_I_HOODBOOMER_LAUGH);
        else
            cur_obj_play_sound_2(SOUND_MITM_LEVEL_I_HOODBOOMER_HAHA);
    }
}

void bhv_black_smoke_hoodboomer_loop(void){
    if (o->oTimer == 0) {
        o->oForwardVel = random_float() * 2 + 0.5f;
        o->oMoveAngleYaw = (o->parentObj->oMoveAngleYaw + 0x7000) + random_float() * 8192.0f;
        o->oVelY = 8.0f;
        o->oPosY += 200;
    }
    o->oMoveAngleYaw += o->oAngleVelYaw;
    o->oPosY += o->oVelY;
    cur_obj_scale(1.0f + (o->oTimer / 64.0f));
    o->oOpacity -= 4;
    if (o->oOpacity < 10) {
        obj_mark_for_deletion(o);
    }
}

/**
 * Hitbox for hoodboomer bomb.
 */
static struct ObjectHitbox sHoodboomerBombHitbox = {
    /* interactType:      */ INTERACT_MR_BLIZZARD,
    /* downOffset:        */ 15,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 99,
    /* numLootCoins:      */ 0,
    /* radius:            */ 30,
    /* height:            */ 15,
    /* hurtboxRadius:     */ 30,
    /* hurtboxHeight:     */ 15,
};

static void hoodboomer_bomb_act_move(void){
    s16 collisionFlags;
    f32 floorY;
    struct Surface *sObjFloor;

    cur_obj_compute_vel_xz();
    floorY = find_floor(o->oPosX + o->oVelX, o->oPosY, o->oPosZ + o->oVelZ, &sObjFloor);
    if ((s32) o->oPosY == (s32) floorY) {
        collisionFlags += OBJ_COL_FLAG_GROUNDED;
    }
    
    if (collisionFlags == OBJ_COL_FLAG_GROUNDED) {
        cur_obj_spawn_particles(&sMontyMoleRockBreakParticles);
        obj_mark_for_deletion(o);
    }
        

    cur_obj_move_standard(78);
}

extern s16 gArctanTable[];

void bhv_hoodboomer_bomb_loop(void){
    f32 x;
    f32 y;
    f32 g;
    f32 v;
    if(o->oTimer == 0){
        /*f32 x = o->oDistanceToMario;
        f32 y =  gMarioObject->oPosY - o->oPosY;
        o->oMoveAngleYaw = obj_angle_to_object(o, gMarioObject);
        o->oForwardVel = 10.0f;
        v = o->oForwardVel;
        o->oGravity = 2.0f;
        g = o->oGravity;

        o->oMoveAnglePitch = degrees_to_angle(atans((v*v + sqrtf(v*v*v*v - g*g*x*x + g*2*y*v*v))/ g*x));
        o->oVelY = o->oForwardVel * sins(o->oMoveAnglePitch);*/
        o->oMoveAngleYaw = obj_angle_to_object(o, gMarioObject);

        o->oForwardVel = 40.0f;
        o->oVelY = o->oDistanceToMario * 0.08f + 8.0f;
        
    }
    obj_check_attacks(&sHoodboomerBombHitbox, o->oAction);
    hoodboomer_bomb_act_move();
}

/*********************************PigPot*************************************/

void bhv_pigpot_loop(void){
    if((o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED) || o->oShotByShotgun == 1){
       obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
       play_sound(SOUND_MITM_LEVEL_I_PIGPOT_DEATH, gGlobalSoundSource);
    }
}

/*********************************Misc*************************************/

void bhv_rotating_gear_decorative_init(void){
    f32 scale = GET_BPARAM2(o->oBehParams);
    cur_obj_scale(1.0f + (scale / 20));
}

void bhv_rotating_gear_decorative_loop(void){
    o->oFaceAnglePitch += (o->oBehParams >> 24) * 5;
}

/*************************GATE OPEN BY BUTTONS*****************************/

void bhv_grill_openable_by_rocket_button_loop(void){
    //Handle if a gat can be open by 2 different way
    s32 firstButtonGroupToCheck;
    s32 secondButtonGroupToCheck;
    s32 openingSpeed = ((o->oBehParams >> 8) & 0xFF);
    if(openingSpeed < 1) openingSpeed = 1;
    s32 openingHeigh = (o->oBehParams & 0xFF) * 10;
    s32 openingTime = openingHeigh / openingSpeed;
    switch (o->oAction){
    //closed
    case 0:
        firstButtonGroupToCheck = count_objects_with_behavior_bparam1_action(bhvRocketButtonGroup, o->oBehParams >> 24, ROCKET_BUTTON_GROUP_SUCCESSFUL);
        secondButtonGroupToCheck = count_objects_with_behavior_bparam1_action(bhvRocketButtonGroup, o->oBehParams2ndByte, ROCKET_BUTTON_GROUP_SUCCESSFUL);
        if(firstButtonGroupToCheck != 0 || secondButtonGroupToCheck != 0){
            o->oTimer == 0;
            o->oAction++;
        }
        break;
    //opening
    case 1:
        if(o->oTimer < openingTime){
            o->oPosY += openingSpeed;
        }
        break;
    //open
    case 2:
        //Do nothing
        break;
    }
}

/*************************WOODEN LEVER*****************************/

void bhv_wooden_lever_loop(void){
    switch (o->oAction) {
            //wait
            case 0:
                break;
            //activated
            case 1:
                o->oAngleVelRoll = -0x100;
                if (o->oTimer > 63) {
                    o->oAction++;
                }
                cur_obj_play_sound_1(SOUND_ENV_ELEVATOR2);
                cur_obj_rotate_face_angle_using_vel();
                break;
            //wait but can't be activated anymore
            case 2:
                break;
        }
}

void bhv_opening_wall_loop(void) {
    o->oObjF4 = cur_obj_nearest_object_with_behavior(bhvWoodenLever);
    switch (o->oAction) {
            //wait
            case 0:
                if(o->oObjF4 != NULL && o->oObjF4->oAction == 1){
                    o->oAction++;
                }
                break;
            //activated
            case 1:
                o->oVelX = 10;
                if (o->oTimer > 63) {
                    o->oAction++;
                }
                cur_obj_play_sound_1(SOUND_ENV_ELEVATOR2);
                cur_obj_move_using_vel();
                break;
            //wait but can't be activated anymore
            case 2:
                obj_mark_for_deletion(o);
                break;
    }
}

/*************************PLUM*****************************/

void respawn_plum(void) {
    o->oVelX = 0;
    o->oVelY = 0;
    o->oVelZ = 0;
    o->oForwardVel = 0;
    o->oHeldState = HELD_FREE;
    o->oBreakableBoxSmallReleased = FALSE;
    cur_obj_unhide();
    cur_obj_set_pos_to_home();
    stop_plum_music();
    cur_obj_scale(0.0f);
}

void plum_released_loop(void) {
    o->oBreakableBoxSmallFramesSinceReleased++;

    // Begin flashing
    if (o->oBreakableBoxSmallFramesSinceReleased > 810) {
        COND_BIT((o->oBreakableBoxSmallFramesSinceReleased & 0x1), o->header.gfx.node.flags, GRAPH_RENDER_INVISIBLE);
    }

    // Despawn, and create a corkbox respawner
    if (o->oBreakableBoxSmallFramesSinceReleased > 900) {
        respawn_plum();
    }
}

void plum_idle_loop(void) {
    s16 collisionFlags;
    cur_obj_update_floor_and_walls();
    o->oVelY -= o->oGravity;

    switch (o->oAction) {
        case BREAKABLE_BOX_SMALL_ACT_MOVE:
            collisionFlags = object_step();
            if (collisionFlags == OBJ_COL_FLAG_GROUNDED) {
                o->oForwardVel = 0.0f;
                cur_obj_play_sound_2(SOUND_GENERAL_SMALL_BOX_LANDING);
            }
            if (collisionFlags == OBJ_COL_FLAG_UNDERWATER){
                spawn_mist_particles_with_sound(SOUND_OBJ_DEFAULT_DEATH);
                respawn_plum();
            }
            break;

        case OBJ_ACT_DEATH_PLANE_DEATH:
            respawn_plum();
            break;
    }

    if (o->oBreakableBoxSmallReleased == TRUE) {
        plum_released_loop();
    }
}

void bhv_plum_loop(void) {
    if(o->header.gfx.scale[0] >= 1.0f) {
        cur_obj_scale(1.0f);
        cur_obj_become_tangible();
        switch (o->oHeldState) {
            case HELD_FREE:
                plum_idle_loop();
                break;

            case HELD_HELD:
                cur_obj_disable_rendering();
                cur_obj_become_intangible();
                //if music not playing
                play_plum_music();
                break;

            case HELD_THROWN:
            case HELD_DROPPED:
                cur_obj_get_thrown_or_placed(18.0f, 46.0f, 0);
                o->oBreakableBoxSmallFramesSinceReleased = 0;
                o->oBreakableBoxSmallReleased = TRUE;
                break;
        }

        o->oInteractStatus = INT_STATUS_NONE;
    } else {
        cur_obj_scale(o->header.gfx.scale[0] + 0.05f);
        cur_obj_become_intangible();
        o->oPosY -= 6.5f; //make the plum go down as it grown on tree to align the stem with the branche since his origine is at his bottom
    }

}

void bhv_plum_bucket_loop(void) {
    f32 dist;
    struct Object *plum = cur_obj_find_nearest_object_with_behavior(bhvPlum, &dist);
    

    switch(o->oAction){
        //wait for plum
        case 0:
            if(plum != NULL && dist < 300.0f){
                stop_plum_music();
                obj_mark_for_deletion(plum);
                spawn_default_star(gMarioObject->oPosX, gMarioObject->oPosY + 280.0f, gMarioObject->oPosZ);
                o->oAction++;
            }
            break;
        //do nothing
        case 1:
            break;
    }
    o->oInteractStatus = INT_STATUS_NONE;
}

/*************************ROPE*****************************/

void bhv_plank_attached_to_rope_loop(void) {
    s16 collisionFlags = 0;

    switch (o->oAction){
    case 0:
        //rope cuted
        if(GET_BPARAM3(o->oBehParams) == 0){
            o->oAction++;
            }
        break;
    case 1:
        //fall
        o->oPosY -= o->oGravity;
        object_step();
        if(o->oTimer > 25){
            o->oAction++;
            cur_obj_play_sound_2(SOUND_GENERAL_SMALL_BOX_LANDING);
        }
        break;
    case 2:
        break;
    }
}

void bhv_barrier_attached_to_rope_loop(void) {
    s16 collisionFlags = 0;
    o->oVelY -= o->oGravity;

    switch (o->oAction){
    case 0:
        //rope cuted
        if(GET_BPARAM3(o->oBehParams) == 0){
            o->oF4 = o->oFaceAngleYaw;
            o->oAction++;
            }
        break;
    case 1:
        //fall
        o->oFaceAngleYaw = o->oF4;
        if(object_step() == OBJ_COL_FLAG_GROUNDED){
            cur_obj_play_sound_2(SOUND_GENERAL_SMALL_BOX_LANDING);
        }
        break;
    }
}

/*************************SAVING TOAD FROM CAGES*****************************/

void bhv_caged_toad_loop(){
    struct Object *freeToadObj = NULL;

    if((o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED) || o->oShotByShotgun == 2){
        spawn_mist_particles_variable(0, 0, 46.0f);
        spawn_triangle_break_particles(30, MODEL_DIRT_ANIMATION, 3.0f, TINY_DIRT_PARTICLE_ANIM_STATE_YELLOW);
        obj_mark_for_deletion(o);
        create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
        freeToadObj = spawn_object_abs_with_rot(o, 0, MODEL_TOAD, bhvFallingToad, o->oPosX, o->oPosY, o->oPosZ, 0, 0, 0);
        freeToadObj->oToadMessageDialogId = GET_BPARAM1(o->oBehParams);
        freeToadObj->oToadMessageRecentlyTalked = FALSE;
        freeToadObj->oToadMessageState = 0;
        freeToadObj->oOpacity = 81;
        gRedCoinsCollected++;
    }

    o->oPosY += 8.0f * coss(1000 * o->oTimer);

    if((o->oTimer % 400) == 0 && o->oDistanceToMario < 5000){
        cur_obj_play_sound_2(SOUND_MITM_LEVEL_I_TOAD_HELP);
    }

    o->oInteractStatus = INT_STATUS_NONE;
}

void bhv_caged_toad_star_init(void) {
    //Using red coin counter to count freed toad
    struct Object *starObj = NULL;

    spawn_object(o, MODEL_TRANSPARENT_STAR, bhvRedCoinStarMarker);
    
    s16 numCagedToadsRemaining = count_objects_with_behavior(bhvCagedToad);
    if (numCagedToadsRemaining == 0) {
        starObj = spawn_object_abs_with_rot(o, 0, MODEL_STAR, bhvStar, o->oPosX, o->oPosY, o->oPosZ, 0, 0, 0);
        starObj->oBehParams = o->oBehParams;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
    o->oHiddenStarTriggerTotal = numCagedToadsRemaining + gRedCoinsCollected;
    o->oHiddenStarTriggerCounter = o->oHiddenStarTriggerTotal - numCagedToadsRemaining;
    
}

void bhv_bhv_caged_toad_star_loop(void) {
    s16 numCagedToadsRemaining = count_objects_with_behavior(bhvCagedToad);
    o->oHiddenStarTriggerCounter = o->oHiddenStarTriggerTotal - numCagedToadsRemaining;
    gRedCoinsCollected = o->oHiddenStarTriggerCounter;

    switch (o->oAction) {
        case HIDDEN_STAR_ACT_INACTIVE:
            if (o->oHiddenStarTriggerCounter == o->oHiddenStarTriggerTotal) {
                o->oAction = HIDDEN_STAR_ACT_ACTIVE;
            }
            break;

        case HIDDEN_STAR_ACT_ACTIVE:
            if (o->oTimer > 50) {
                bhv_spawn_star_no_level_exit_at_object(GET_BPARAM1(o->oBehParams), gMarioObject);
                spawn_mist_particles();
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
    }
}

/*************************FUNKY SHELL*****************************/

struct ObjectHitbox sFunkyShellHitbox = {
    .interactType      = INTERACT_KOOPA_SHELL,
    .downOffset        = 0,
    .damageOrCoinValue = 4,
    .health            = 1,
    .numLootCoins      = 1,
    .radius            = 50,
    .height            = 50,
    .hurtboxRadius     = 50,
    .hurtboxHeight     = 50,
};

void bhv_funky_shell_loop(void) {
    struct Surface *floor;

    obj_set_hitbox(o, &sFunkyShellHitbox);
    cur_obj_scale(1.0f);

    switch (o->oAction) {
        case KOOPA_SHELL_ACT_MARIO_NOT_RIDING:
            cur_obj_update_floor_and_walls();
            cur_obj_if_hit_wall_bounce_away();

            if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                o->oPreviousLakituCamMode = gLakituState.mode;
                gLakituState.mode = CAMERA_MODE_FUNKY_BOARD;
                gMarioState->faceAngle[1] = 0x8000;
                o->oAction = KOOPA_SHELL_ACT_MARIO_RIDING;
            }

            o->oFaceAngleYaw += 0x1000;
            cur_obj_move_standard(-20);
            koopa_shell_spawn_sparkles(10.0f);
            check_shell_despawn();
            break;

        case KOOPA_SHELL_ACT_MARIO_RIDING:
            obj_copy_pos(o, gMarioObject);
            floor = cur_obj_update_floor_height_and_get_floor();
            koopa_shell_spawn_sparkles(10.0f);

            //align with mario
            o->oFaceAngleYaw = gMarioObject->oMoveAngleYaw;

            if (o->oInteractStatus & INT_STATUS_STOP_RIDING) {
                gLakituState.mode = o->oPreviousLakituCamMode;
                cur_obj_set_pos_to_home();
                spawn_mist_particles();
                o->oAction = KOOPA_SHELL_ACT_MARIO_NOT_RIDING;
            }
            break;
    }

    o->oInteractStatus = INT_STATUS_NONE;
}

#define OFFSET_FROM_CENTER 900

void bhv_skrinking_black_door_spawner(void) {
    switch(o->oAction){
        //spawn 4 panel
        case 0:
            spawn_object_relative(0, -OFFSET_FROM_CENTER, -OFFSET_FROM_CENTER, 0, o, MODEL_BLACK_PANEL, bhvSkrinkingBlackDoor);
            spawn_object_relative(0, OFFSET_FROM_CENTER, OFFSET_FROM_CENTER, 0, o, MODEL_BLACK_PANEL, bhvSkrinkingBlackDoor);
            spawn_object_relative(0, -OFFSET_FROM_CENTER, OFFSET_FROM_CENTER, 0, o, MODEL_BLACK_PANEL, bhvSkrinkingBlackDoor);
            spawn_object_relative(0, OFFSET_FROM_CENTER, -OFFSET_FROM_CENTER, 0, o, MODEL_BLACK_PANEL, bhvSkrinkingBlackDoor);
            o->oAction++;
            break;
        //wait for mario
        case 1:
            if(o->oDistanceToMario < 2000){
                o->oAction++;
            }
            break;
    } 
}

void bhv_skrinking_black_door(void) {
    if(o->parentObj->oAction == 2){
        o->oFloatF4 -= 0.05f;
        cur_obj_scale(o->oFloatF4);
        if(o->oFloatF4 <= 0.0f){
            obj_mark_for_deletion(o);
        }
    }
}

void bhv_rotating_funky_platform(void){
    if(o->oAction == 0){
        //store default Yaw
        o->oF4 = o->oFaceAngleYaw;
            if(o->oDistanceToMario < 1900){
                o->oAngleVelYaw = 0x800;
                o->oAction++;
            }
    }
    
    if(o->oAction == 1 && (o->oFaceAngleYaw - o->oF4 >= 0x4000)){
        o->oAngleVelYaw = 0;
        o->oFaceAngleYaw = 0x4000;
        o->oAction++;
    }

    cur_obj_rotate_face_angle_using_vel();

}

void bhv_moving_funky_platform(void){
    s8 reverse = 1;
    if(GET_BPARAM1(o->oBehParams) != 0) reverse = -1;
    o->oPosX += (10.0f * coss(1000 * o->oTimer)) * reverse;
}

void bhv_three_axis_rotative_object(void){
    o->oFaceAngleRoll += GET_BPARAM1(o->oBehParams) * 5;
    o->oFaceAngleYaw += GET_BPARAM2(o->oBehParams) * 5;
    o->oFaceAnglePitch += GET_BPARAM3(o->oBehParams) * 5;
    cur_obj_scale(1.0f + (GET_BPARAM4(o->oBehParams) / 20));
}

/*************************BOUNTY HUNTER TOAD*****************************/

#include "src/game/mario_misc.h"

#define TOAD_BOUNTY_HUNTER_BEFORE DIALOG_I_BOUNTY_HUNTER_TOAD_MISSION
#define TOAD_BOUNTY_HUNTER_THANKS DIALOG_I_BOUNTY_HUNTER_TOAD_THANKS
#define TOAD_BOUNTY_HUNTER_AFTER DIALOG_I_BOUNTY_HUNTER_TOAD_AFTER

void bhv_bounty_hunter_toad_init(void) {
    o->oToadMessageDialogId = TOAD_BOUNTY_HUNTER_BEFORE;
    o->oToadMessageRecentlyTalked = FALSE;
    o->oToadMessageState = 0;
    o->oOpacity = 81;
}

void bhv_bounty_hunter_toad_loop(void) {
    if (o->header.gfx.node.flags & GRAPH_RENDER_ACTIVE) {
        o->oInteractionSubtype = INT_STATUS_NONE;
        switch (o->oToadMessageState) {
            case 0:
                toad_message_faded();
                break;
            case 1:
                toad_message_opaque();
                if((count_objects_with_behavior(bhvHoodmonger) + count_objects_with_behavior(bhvHoodboomer)) == 0 && 
                o->oToadMessageDialogId == TOAD_BOUNTY_HUNTER_BEFORE ) {
                    o->oToadMessageDialogId = TOAD_BOUNTY_HUNTER_THANKS;
                }
                break;
            case 2:
                toad_message_opacifying();
                break;
            case 3:
                toad_message_fading();
                break;
            case 4:
                if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_DOWN, DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, o->oToadMessageDialogId)) {
                    o->oToadMessageRecentlyTalked = TRUE;
                    o->oToadMessageState = 3;
                    if(o->oToadMessageDialogId == TOAD_BOUNTY_HUNTER_THANKS){
                        o->oToadMessageDialogId = TOAD_BOUNTY_HUNTER_AFTER;
                        bhv_spawn_star_no_level_exit(GET_BPARAM1(o->oBehParams));
                    }
                }
                break;
        }
    }
}