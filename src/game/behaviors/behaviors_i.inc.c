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
    s16 stickX = gPlayer3Controller->rawStickX;
    s16 stickY = gPlayer3Controller->rawStickY;
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

void bhv_rocket_button_group_init(void){
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

/*********************************Hoodboomer*************************************/

void bhv_hoodboomer_loop(void){

    o->oDeathSound = SOUND_MITM_LEVEL_I_HOODBOOMER_DEATH;
    obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x800);

    if(o->prevObj == NULL){
        struct Object *bomb = spawn_object(o, MODEL_HOODBOOMER_BOMB, bhvHoodboomerBomb);
        o->prevObj = bomb;
    }

    if(dist_between_objects(o, gMarioObject) < 1500 && o->oLaunchingBombCooldown <= 0){
        print_text(180, 180, "OUI");
        //if (cur_obj_init_anim_and_check_if_end(2)) {
        o->prevObj = NULL;
        o->oLaunchingBombCooldown = 200;
        //}
    }

    if(o->oLaunchingBombCooldown > 0){
        o->oLaunchingBombCooldown--;
    }

    if((o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED) || o->oShotByShotgun == 2){
        o->oHealth--;
        create_sound_spawner(o->oDeathSound);
        obj_die_if_health_non_positive();
    }

    if((o->oTimer % 300) == 0){
        create_sound_spawner(SOUND_MITM_LEVEL_I_HOODBOOMER_LAUGH);
    }

    if((o->oTimer % 15) == 0){
        spawn_object(o, MODEL_BURN_SMOKE, bhvBlackSmokeHoodboomer);
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

static void hoodboomer_bomb_act_held(void){
    // The position is offset since the monty mole is throwing it with its hand
    o->oParentRelativePosX = 500.0f;
    o->oParentRelativePosY = 400.0f;
    o->oParentRelativePosZ = 0.0f;

    if (o->parentObj->prevObj == NULL) {
        f32 distToMario = o->oDistanceToMario;

        o->oBombIsLaunched = TRUE;
        arc_to_goal_pos(&gMarioObject->oPosVec, &o->oPosVec, 60.0f, -4.0f);
        o->oAction++;
        o->oMoveFlags = OBJ_MOVE_NONE;
    }
}

static void hoodboomer_bomb_act_move(void){
    cur_obj_update_floor_and_walls();

    if (o->oMoveFlags & (OBJ_MOVE_MASK_ON_GROUND | OBJ_MOVE_ENTERED_WATER)) {
        cur_obj_spawn_particles(&sMontyMoleRockBreakParticles);
        obj_mark_for_deletion(o);
    }

    if (!o->oBombIsLaunched) {
        cur_obj_move_standard(78);
    } else {
        cur_obj_move_using_fvel_and_gravity();
    }
}

void bhv_hoodboomer_bomb_loop(void){
    obj_check_attacks(&sHoodboomerBombHitbox, o->oAction);

    switch (o->oAction) {
        case 0:
            hoodboomer_bomb_act_held();
            break;
        case 1:
            hoodboomer_bomb_act_move();
            break;
    }
}

/*********************************PigPot*************************************/

void bhv_pigpot_loop(void){
    if((o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED) || o->oShotByShotgun == 1){
       obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
       create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
    }
}

/*********************************Misc*************************************/

void bhv_rotating_gear_decorative(void){
    o->oFaceAnglePitch += (o->oBehParams >> 24) * 5;
}

/*************************GATE OPEN BY BUTTONS*****************************/

void bhv_grill_openable_by_rocket_button_loop(void){
    //Handle if a gat can be open by 2 different way
    s32 firstButtonGroupToCheck;
    s32 secondButtonGroupToCheck;
    s32 openingSpeed = ((o->oBehParams >> 8) & 0xFF);
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


