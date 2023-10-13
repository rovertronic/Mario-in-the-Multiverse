#include "src/game/camera.h"
#include "src/game/area.h"
#include "src/game/ability.h"
#include "src/game/mario_actions_airborne.h"
#include "src/game/mario.h"

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
    o->oGravity = 0.0f;
    o->oFriction = 0.999f;
    
    obj_set_hitbox(o, &sJellyHitbox);
}

void jelly_loop(void) {
    object_step();
    
    switch (o->oAction) {
        case 0:
            o->oForwardVel = 0;
            if (o->oDistanceToMario < 1000.0f) {
                o->oAction = 1;
            }
            break;
        case 1:
            o->oGravity = 0;
            
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

            if (cur_obj_was_attacked_or_ground_pounded())
                {
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
    if (o->oTimer >= 22.5f) {
        obj_scale_xyz(o, 1.0f + ((0.2f - (0.2f * ((f32)o->oTimer) / 30.0f)) * sins(o->oTimer * 0x1000)),
                         1.0f + ((0.3f - (0.3f * ((f32)o->oTimer) / 30.0f)) * coss(o->oTimer * 0x1000 + 0x4000)),
                         1.0f + ((0.25f - (0.25f * ((f32)o->oTimer) / 30.0f)) * sins(o->oTimer * 0x1000)));
    }
    if (o->oTimer >= 45) {
        o->oTimer = 0;
    }
}

// Jellyfish Fields Platform

void jfplatform_loop(void) {
    o->oVelY = 5 * sins(o->oTimer * 0x222);
    o->oPosY += o->oVelY;
}

// Floating Checker Platform

enum checkerAnims
{
    ANIM_C_MAIN,
};

void fcp_loop(void)
{
    cur_obj_init_animation(ANIM_C_MAIN);
    o->oPosY += o->oVelY;

    switch (o->oBehParams2ndByte)
    {
        case 0:
            o->oVelY = 5 * sins(o->oTimer * 0x122);
            break;
        case 1:
            o->oVelY = 5 * sins(o->oTimer * 0x222);
            break;
        case 2:
            o->oVelY = 9 * sins(o->oTimer * 0x300);
            break;
    }
}


// Taxi stop

void taxistop_loop(void)
{
    s16 timer = 52;
    
    if (gMarioObject->platform == o)
    {
        o->oAction = 1;
        gLakituState.curPos[0] = 5181;
        gLakituState.curPos[1] = -3;
        gLakituState.curPos[2] = -7742;

        play_transition(WARP_TRANSITION_FADE_INTO_CIRCLE, timer, 0, 0, 0);
    }

    switch (o->oAction)
    {
        case 0:

            break;
        case 1:
            if (o->oTimer >= 50)
            {
                initiate_warp(LEVEL_A, 2, 0x0A, 0);
            }
            break;
    }   
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
    o->oGravity = 1;
    o->oOpacity = 150;
    obj_set_hitbox(o, &sTikiHitbox);
}

void tiki_box_loop(void)
{   
    if (cur_obj_was_attacked_or_ground_pounded())
    {
        obj_mark_for_deletion(o);
        obj_explode_and_spawn_coins(8, COIN_TYPE_YELLOW);
        obj_spawn_loot_yellow_coins(o, 4, 10);
    }
    
    
    switch (o->oBehParams2ndByte)
    {
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

// King Jellyfish

void king_jellyfish_loop(void)
{
    switch (o->oAction)
    {

    }
}

// Trampoline

struct ObjectHitbox sTrampHitbox = {
    /* interactType:      */ INTERACT_NONE,
    /* downOffset:        */  20,
    /* damageOrCoinValue: */   0,
    /* health:            */   1,
    /* numLootCoins:      */   0,
    /* radius:            */ 250,
    /* height:            */ 300,
    /* hurtboxRadius:     */ 250,
    /* hurtboxHeight:     */ 300,
};


void trampoline_loop(void)
{
    f32 yVel = 90.0f;
    f32 fVel = 50.0f;

    switch (o->oAction)
    {
        case 0:
            cur_obj_scale(1.0f);
            break;
        case 1:
            if (o->oTimer >= 0) {
                obj_scale_xyz(o, 1.0f + ((0.25f - (0.25f * ((f32)o->oTimer) / 20.0f)) * sins(o->oTimer * 0x1000)),
                         1.0f + ((0.4f - (0.4f * ((f32)o->oTimer) / 20.0f)) * coss(o->oTimer * 0x1000 + 0x4000)),
                         1.0f + ((0.25f - (0.25f * ((f32)o->oTimer) / 20.0f)) * sins(o->oTimer * 0x1000)));
            }
            if (o->oTimer >= 22.5f) {
                obj_scale_xyz(o, 1.0f + ((0.2f - (0.2f * ((f32)o->oTimer) / 30.0f)) * sins(o->oTimer * 0x1000)),
                         1.0f + ((0.3f - (0.3f * ((f32)o->oTimer) / 30.0f)) * coss(o->oTimer * 0x1000 + 0x4000)),
                         1.0f + ((0.25f - (0.25f * ((f32)o->oTimer) / 30.0f)) * sins(o->oTimer * 0x1000)));
            }
            if (o->oTimer >= 45) {
                
            }
            break;
    }

    if (gMarioObject->platform == o)
    {
        o->oAction = 1;
        gMarioState->vel[1] = yVel;
        gMarioState->faceAngle[1] = gMarioState->intendedYaw;
        gMarioState->forwardVel = fVel;
        return set_mario_action(gMarioState, ACT_SPECIAL_TRIPLE_JUMP, 0);
    } else if (o->oTimer >= 45)
    {
        o->oAction = 0;
    }
}