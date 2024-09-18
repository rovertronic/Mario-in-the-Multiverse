// recovery_heart.inc.c

struct ObjectHitbox sRecoveryHeartHitbox = {
    /* interactType:      */ 0,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 50,
    /* height:            */ 50,
    /* hurtboxRadius:     */ 50,
    /* hurtboxHeight:     */ 50,
};

void bhv_recovery_heart_loop(void) {
    obj_set_hitbox(o, &sRecoveryHeartHitbox);
    if (obj_check_if_collided_with_object(o, gMarioObject)) {
        if (o->oSpinningHeartPlayedSound == 0) {
            cur_obj_play_sound_2(SOUND_GENERAL_HEART_SPIN);
            o->oSpinningHeartPlayedSound++;
        }

        o->oAngleVelYaw = (s32)(200.0f * gMarioState->forwardVel) + 1000;
    } else {
        o->oSpinningHeartPlayedSound = 0;

        if ((o->oAngleVelYaw -= 50) < 400) {
            o->oAngleVelYaw = 400;
            o->oSpinningHeartTotalSpin = 0;
        }
    }

    if ((o->oSpinningHeartTotalSpin += o->oAngleVelYaw) >= 0x10000) {
        combo_meter = CLAMP(combo_meter+33,0,201);
        gMarioState->healCounter += 4;
#ifdef BREATH_METER
        gMarioState->breathCounter += 4;
#endif
        o->oSpinningHeartTotalSpin -= 0x10000;
    }

    o->oFaceAngleYaw += o->oAngleVelYaw;
}

void bhv_ability_heart_loop(void) {
    obj_set_hitbox(o, &sRecoveryHeartHitbox);
    f32 dist;
    struct Object *rocket = cur_obj_find_nearest_object_with_behavior(bhvShockRocket, &dist);
    if (rocket && dist < 100) {
        if (rocket->oAction == 1) rocket->oTimer = 0;
        if (o->oSpinningHeartPlayedSound == 0) {
            cur_obj_play_sound_2(SOUND_GENERAL_HEART_SPIN);
             o->oSpinningHeartPlayedSound++;
        }

        o->oAngleVelYaw = (s32)(200.0f * 10) + 1000;
    }
    else if (obj_check_if_collided_with_object(o, gMarioObject)) {
        if (o->oSpinningHeartPlayedSound == 0) {
            cur_obj_play_sound_2(SOUND_GENERAL_HEART_SPIN);
            ability_ready(gMarioState->abilityId);
            aku_recharge = 0;
            chronos_timer = 360;
            if (phasewalk_timer > 140) {
                phasewalk_timer = 240;
                phasewalk_state = 1;
            }
            else {
                phasewalk_timer = 0;
            }

            if (aku_invincibility > 0) {
                aku_invincibility = 360;
            }

            gMarioState->remainingDashes = 3;
            o->oSpinningHeartPlayedSound++;
        }

        o->oAngleVelYaw = (s32)(200.0f * gMarioState->forwardVel) + 1000;
    } else {
        o->oSpinningHeartPlayedSound = 0;

        if ((o->oAngleVelYaw -= 50) < 400) {
            o->oAngleVelYaw = 400;
            o->oSpinningHeartTotalSpin = 0;
        }
    }

    if ((o->oSpinningHeartTotalSpin += o->oAngleVelYaw) >= 0x10000) {
        o->oSpinningHeartTotalSpin -= 0x10000;
    }

    o->oFaceAngleYaw += o->oAngleVelYaw;
}
