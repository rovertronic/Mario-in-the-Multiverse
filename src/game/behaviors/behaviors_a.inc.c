#include "src/game/camera.h"
#include "src/game/area.h"
#include "src/game/ability.h"

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
    /*s16 eventTimer = 62;

    if (o->oAction >= 1) {
        gCamera->cutscene = 1;
    } else {
        gCamera->cutscene = 0;
    }
    
    if (gMarioObject->platform) {
        gLakituState.curPos[0] = -1021;
        gLakituState.curPos[1] = 9;
        gLakituState.curPos[2] = -8046;
        set_mario_animation(gMarioState, MARIO_ANIM_TRIPLE_JUMP_FLY);
        approach_f32_asymptotic_bool(&gMarioState->pos[0], o->oPosX, 0.0f);
        approach_f32_asymptotic_bool(&gMarioState->pos[2], o->oPosZ - (o->oTimer * 2), 0.0f);
        play_transition(WARP_TRANSITION_FADE_INTO_CIRCLE, eventTimer, 255, 255, 255);
        set_mario_action(gMarioState, TAXI_STOP_CUTSCENE, 0);
        o->oAction = 1;
        if (o->oTimer == 60) {
            initiate_warp(LEVEL_G, 1, 0x0A, 0);
        }
    }*/
}

// Boat for Taxi Stop

void tsboat_loop(void) {
    
}

// Tiki Box

struct ObjectHitbox sTikiHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */  20,
    /* damageOrCoinValue: */   0,
    /* health:            */   1,
    /* numLootCoins:      */   0,
    /* radius:            */ 150,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 150,
    /* hurtboxHeight:     */ 200,
};

void tiki_box_init(void) {
    o->oGravity = 1.2f;
    o->oFriction = 0.999f;
    o->oBuoyancy = 0.9f;
    o->oOpacity = 150;
}

void tiki_box_loop(void) {
    f32 floorY;
    s32 speed;
    s16 yaw = o->oMoveAngleYaw;
    s16 pitch = o->oMoveAnglePitch;
    
    obj_set_hitbox(o, &sTikiHitbox);

    floorY = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);

    if (using_ability(ABILITY_BUBBLE_HAT)) {
        if (cur_obj_was_attacked_or_ground_pounded()) {
            obj_mark_for_deletion(o);
            cur_obj_disable_rendering();
            cur_obj_become_intangible();
            spawn_mist_particles();
            create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
        }
    }

    o->oVelX = sins(yaw) * (f32) speed;
    o->oVelY = sins(pitch) * (f32) speed;
    o->oVelZ = coss(yaw) * (f32) speed;

    switch (o->oBehParams2ndByte) {
        case 0:
            obj_set_model(o, MODEL_TIKI_WOOD);
            break;
        case 1:
            obj_set_model(o, MODEL_TIKI_STONE);
            break;
        case 2:
            obj_set_model(o, MODEL_TIKI_FLOAT);
            break;
    }
}