#include "levels/g/header.h"

#define SIR_KIBBLE_ACT_CUTSCENE 0
#define SIR_KIBBLE_ACT_IDLE 1
#define SIR_KIBBLE_ACT_THROWING 2
#define SIR_KIBBLE_ACT_HURT 3

static struct ObjectHitbox sSirKibbleHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 3,
    /* radius:            */ 80,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 70,
    /* hurtboxHeight:     */ 30,
};

static struct ObjectHitbox sBossSirKibbleHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 80,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 70,
    /* hurtboxHeight:     */ 30,
};

static u8 sSirKibbleAttackHandlers[] = {
    /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_SET_SPEED_TO_ZERO,
    /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_SET_SPEED_TO_ZERO,
    /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_KNOCKBACK,
};

void bhv_sir_kibble_init(void) {
    o->oAction = SIR_KIBBLE_ACT_CUTSCENE;
    if (o->oBehParams2ndByte == 1) {
        obj_set_hitbox(o, &sBossSirKibbleHitbox);
        play_secondary_music(SEQ_CUSTOM_KIRBY_BOSS, 0, 127, 5);
    }
    else {
        //obj_set_hitbox(o, &sSirKibbleHitbox);
        o->oAction = SIR_KIBBLE_ACT_IDLE;
    }
    cur_obj_init_animation(0);
    o->oGravity = -4.0f;
    
}

void bhv_sir_kibble_loop(void) {
    if (obj_update_standard_actions(1.0f)) {
    obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x400);
    if (o->oBehParams2ndByte == 1) o->oInteractStatus = 0;
    switch (o->oAction) {
        case SIR_KIBBLE_ACT_CUTSCENE:
            if (o->oTimer > 10) {
                cur_obj_init_animation(1);
                o->oAction = SIR_KIBBLE_ACT_THROWING;
            }
        break;
        case SIR_KIBBLE_ACT_IDLE:
            if (o->oTimer >= 90 && cur_obj_check_if_near_animation_end()) {
                o->oAction = SIR_KIBBLE_ACT_THROWING;
                cur_obj_init_animation(1);
            }
        break;
        case SIR_KIBBLE_ACT_THROWING:
            if (o->oTimer == 17) {
                struct Object * cutterblade = spawn_object_relative(0, 0, 100, 0, o, MODEL_CUTTER_BLADE, bhvCutterBlade);
                cutterblade->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
            }

            if (cur_obj_check_if_near_animation_end()) {
                o->oAction = SIR_KIBBLE_ACT_IDLE;
                cur_obj_init_animation(0);
            }
        break;
    }

    if (o->oBehParams2ndByte == 1) {
        f32 dist;
        struct Object *star = cur_obj_find_nearest_object_with_behavior(bhvStarProjectile, &dist);
        if (star && dist < 200 && o->oAction < 5) {
            o->oAction = OBJ_ACT_HORIZONTAL_KNOCKBACK;
            o->oForwardVel = -50.0f;
            o->oVelY = 30.0f;
            o->oHealth = 0;
        } 
    }
    else {
        obj_handle_attacks(&sSirKibbleHitbox, o->oAction, sSirKibbleAttackHandlers);
    }
    }
    if (o->oShotByShotgun > 0) {
        // The pingas plane is too strong to be beat by the shotgun ツ
        cur_obj_play_sound_2(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL);
        o->oShotByShotgun = 0;
    }
}

