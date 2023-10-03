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



