#include "src/game/camera.h"

// Jelly

static struct ObjectHitbox sJellyHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 1,
    /* numLootCoins:      */ 1,
    /* radius:            */ 80,
    /* height:            */ 90,
    /* hurtboxRadius:     */ 70,
    /* hurtboxHeight:     */ 80,
};

void jelly_init(void) {
    obj_set_hitbox(o, &sJellyHitbox);
}

void jelly_loop(void) {
    switch (o->oAction) {
        case 0:
            o->oForwardVel = 0;
            if (o->oDistanceToMario < 1000.0f) {
                o->oAction = 1;
            }
            break;
        case 1:
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x250);
            
            if (cur_obj_check_anim_frame(1)) {
                o->oForwardVel = 5.2f;
            }
            if (cur_obj_check_anim_frame(30)) {
                o->oForwardVel = 0;
            }
            if (cur_obj_check_anim_frame(32)) {
                o->oForwardVel = 4.8;
            }
            if (cur_obj_check_anim_frame(35)) {
                o->oForwardVel = 3.9;
            }
            if (o->oDistanceToMario > 1000.0f) {
                o->oAction = 0;
            }

            if (cur_obj_was_attacked_or_ground_pounded()) {
                o->oAction = 2;
            }
            break;
        case 2:
            if (o->oTimer >= 1) {
                obj_mark_for_deletion(o);
                cur_obj_disable_rendering();
                cur_obj_become_intangible();
                spawn_mist_particles();
                cur_obj_play_sound_2(SOUND_OBJ_ENEMY_DEATH_HIGH);
                obj_spawn_loot_yellow_coins(o, 1, 10);
            }
            break;
    }

    if (o->oTimer >= 0) {
        obj_scale_xyz(o, 1.0f + ((0.25f - (0.25f * ((f32)o->oTimer) / 20.0f)) * sins(o->oTimer * 0x1000)),
                         1.0f + ((0.4f - (0.4f * ((f32)o->oTimer) / 20.0f)) * coss(o->oTimer * 0x1000 + 0x4000)),
                         1.0f + ((0.25f - (0.25f * ((f32)o->oTimer) / 20.0f)) * sins(o->oTimer * 0x1000)));
    }
    if (o->oTimer >= 30) {
        obj_scale_xyz(o, 1.0f + ((0.2f - (0.2f * ((f32)o->oTimer) / 30.0f)) * sins(o->oTimer * 0x1000)),
                         1.0f + ((0.3f - (0.3f * ((f32)o->oTimer) / 30.0f)) * coss(o->oTimer * 0x1000 + 0x4000)),
                         1.0f + ((0.25f - (0.25f * ((f32)o->oTimer) / 30.0f)) * sins(o->oTimer * 0x1000)));
    }
    if (o->oTimer >= 45) {
        o->oTimer = 0;
    }

    o->oVelX = o->oForwardVel * sins(o->oMoveAngleYaw);
    o->oVelZ = o->oForwardVel * coss(o->oMoveAngleYaw);
    o->oPosX += o->oVelX;
    o->oPosZ += o->oVelZ;
}

// Jellyfish Fields Platform

void jfplatform_loop(void) {
    o->oVelY = 5 * sins(o->oTimer * 0x222);
    o->oPosY += o->oVelY;
}

// Taxi stop

void taxistop_loop(void) {
    if (gMarioObject->platform) {
        o->oAction = 0;
    } else {
        o->oAction = 1;
    }
    
    switch (o->oAction) {
        case 0:
            gLakituState.curPos[0] = 0;
            gLakituState.curPos[1] = 0;
            gLakituState.curPos[2] = 0;

            gCamera->cutscene = 1;
            
            if (o->oTimer >= 13) {

            }
            break;
        case 1:

            break;
    }
}