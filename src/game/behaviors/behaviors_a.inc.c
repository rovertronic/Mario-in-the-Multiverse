#include "src/game/camera.h"
#include "src/game/area.h"
#include "src/game/ability.h"
#include "src/game/mario_actions_airborne.h"
#include "src/game/mario.h"
#include "src/game/hud.h"
#include "src/game/print.h"
#include "src/game/game_init.h"
#include "src/game/puppyprint.h"
#include "src/audio/external.h"
#include "levels/a/a_ham_robot/geo_header.h"

// Jelly
s32 jelly_check_dmg(void) {
    u8 punchstate = ((gMarioState->action == ACT_MOVE_PUNCHING)||(gMarioState->action == ACT_PUNCHING));
    o->oInteractType = INTERACT_SHOCK;

    //mario states where he can kill well
    if ((gMarioState->action == ACT_KNIGHT_SLIDE)||(aku_invincibility>0)) {
        //since the saw-axe is made out of metal, mario gets electrocuted
        o->oInteractType = INTERACT_BOUNCE_TOP;
    }
    //same with chrono's katana.
    //same with big daddy drill

    o->oNumLootCoins = 1;
    o->hitboxRadius = 80;
    if ((gMarioState->vel[1]>=0.0f)&&(punchstate)&&(using_ability(ABILITY_BUBBLE_HAT))) {
        o->oInteractType = INTERACT_BOUNCE_TOP;
        o->oNumLootCoins = 3;
        o->hitboxRadius = 150;
        // You get awarded more loot coins for safely handling jellyfish
    }

    struct Object * cutter = cur_obj_nearest_object_with_behavior(bhvCutterBlade);
    if (cutter && dist_between_objects(o,cutter) < 150.0f) {
        o->oInteractType = INTERACT_BOUNCE_TOP;
        o->oNumLootCoins = 1;
    }

    if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
        return TRUE;
    }

    return FALSE;
}

static struct ObjectHitbox sJellyHitbox = {
    /* interactType:      */ INTERACT_SHOCK,
    /* downOffset:        */ 50,
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
    
    o->header.gfx.pos[1] = 5;

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

            if (jelly_check_dmg())
            {
                o->oAction = 2;
            }

            if (o->oTimer >= 2)
            {
                o->oInteractStatus = 0;
            }
            break;
        case 2:
            if (o->oTimer >= 1) {
                obj_mark_for_deletion(o);
                if (o->oNumLootCoins == 3) {
                    cur_obj_play_sound_2(SOUND_ACTION_SPIN);
                } else {
                    cur_obj_play_sound_2(SOUND_OBJ_ENEMY_DEATH_HIGH);
                }
                spawn_mist_particles();
                if (o->oBehParams2ndByte != 5) {
                    obj_spawn_loot_yellow_coins(o, o->oNumLootCoins, 10);
                }
            }
            break;

        case 3:
            //summoned by king jelly
            if (o->oTimer > 15) {
                o->oBehParams2ndByte = 5;
                o->oAction = 1;
            }
    }

    if (o->oTimer >= 0) {
        obj_scale_xyz(o, 1.0f + ((0.25f - (0.25f * ((f32)o->oTimer) / 20.0f)) * sins(o->oTimer * 0x1000)),
                         1.0f + ((0.4f - (0.4f * ((f32)o->oTimer) / 20.0f)) * coss(o->oTimer * 0x1000 + 0x4000)),
                         1.0f + ((0.25f - (0.25f * ((f32)o->oTimer) / 20.0f)) * sins(o->oTimer * 0x1000)));
    }
    if (o->oTimer >= 22.5f) { // ?
        obj_scale_xyz(o, 1.0f + ((0.2f - (0.2f * ((f32)o->oTimer) / 30.0f)) * sins(o->oTimer * 0x1000)),
                         1.0f + ((0.3f - (0.3f * ((f32)o->oTimer) / 30.0f)) * coss(o->oTimer * 0x1000 + 0x4000)),
                         1.0f + ((0.25f - (0.25f * ((f32)o->oTimer) / 30.0f)) * sins(o->oTimer * 0x1000)));
    }
    if (o->oTimer >= 45) {
        o->oTimer = 0;
    }


    cur_obj_set_model(MODEL_JELLY);
    /*
    switch (o->oBehParams2ndByte)
    {
        case 0:
            cur_obj_set_model(MODEL_JELLY);
            break;
        case 1:
            cur_obj_set_model(MODEL_JELLYS);
            break;
    }*/
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

u16 time;

void taxi_stop_text(void) {
    Color red = 255;
    Color green = 255;
    Color blue = 255;
    time++;
    if (time >= 128) {
        time = 0;
    }
    print_set_envcolour(red, green, blue * sins(time * 0x100), 255);
    print_small_text_buffered(SCREEN_CENTER_X, 200, "Press L To Travel", PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, FONT_VANILLA);
}

void taxistop_loop(void) {
    s16 transitionTimer = 52;
    u8 behparams = GET_BPARAM1(o->oBehParams);
    u8 behparams2 = o->oBehParams2ndByte;
    if ((gMarioObject->platform == o) && (gPlayer1Controller->buttonPressed == L_TRIG)) {
        o->oAction = 1;
    }
    if (gMarioObject->platform == o) {
        taxi_stop_text();
    }
    switch (o->oAction) {
        case 0:
            break;
        case 1:
            if (o->oTimer == 1) {
                set_mario_action(gMarioState, ACT_WAITING_FOR_DIALOG, 0);
                struct Object * boat = spawn_object(o, MODEL_TSBOAT, bhvtsBoat);
                if (behparams == 4) {
                    boat->oPosZ -= 500;
                } else if (behparams == 3) {
                    boat->oPosX -= 500;
                } else if (behparams == 1) {
                    boat->oPosX += 500;
                }
            }
            if (o->oTimer == 14) {
                gMarioObject->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_NONE];
            }
            if (o->oTimer == 30) {
                play_transition(WARP_TRANSITION_FADE_INTO_STAR, transitionTimer - 29, 0, 0, 0);
            }
            if (o->oTimer == 52) {
                initiate_warp(LEVEL_A, behparams, behparams2, 0);
            }
            switch (behparams) {
                case 1:
                    gCamera->cutscene = 1;
                    gLakituState.goalPos[0] = o->oPosX + 1000;
                    gLakituState.goalPos[1] = o->oPosY + 200;
                    gLakituState.goalPos[2] = o->oPosZ;
    
                    gLakituState.goalFocus[0] = o->oPosX;
                    gLakituState.goalFocus[1] = o->oPosY + 100;
                    gLakituState.goalFocus[2] = o->oPosZ;
                    break;
                case 3:
                    gCamera->cutscene = 1;
                    gLakituState.goalPos[0] = o->oPosX - 1000;
                    gLakituState.goalPos[1] = o->oPosY + 200;
                    gLakituState.goalPos[2] = o->oPosZ;
    
                    gLakituState.goalFocus[0] = o->oPosX;
                    gLakituState.goalFocus[1] = o->oPosY + 100;
                    gLakituState.goalFocus[2] = o->oPosZ;
                    break;
                case 4:
                    gCamera->cutscene = 1;
                    gLakituState.goalPos[0] = o->oPosX;
                    gLakituState.goalPos[1] = o->oPosY + 200;
                    gLakituState.goalPos[2] = o->oPosZ - 1000;
    
                    gLakituState.goalFocus[0] = o->oPosX;
                    gLakituState.goalFocus[1] = o->oPosY + 100;
                    gLakituState.goalFocus[2] = o->oPosZ;
                    break;
            }
            break;
    }
}

// Boat for Taxi Stop

void tsboat_loop(void) {
    switch (o->oAction)
    {
        case 0:
            obj_scale_xyz(o, 1.9f * sins(o->oTimer * 0x300), 1.9f * sins(o->oTimer * 0x300), 1.2f);
            break;
    }
}

// Tiki Box

struct ObjectHitbox sTikiHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */  20,
    /* damageOrCoinValue: */   0,
    /* health:            */   1,
    /* numLootCoins:      */   2,
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
    if (using_ability(ABILITY_BUBBLE_HAT))
    {
        if (cur_obj_was_attacked_or_ground_pounded())
        {
            obj_mark_for_deletion(o);
            obj_explode_and_spawn_coins(8, COIN_TYPE_YELLOW);
            obj_spawn_loot_yellow_coins(o, 4, 10);
        }
    }

    if (o->oTimer >= 2)
    {
        o->oInteractStatus = 0;
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
        cur_obj_play_sound_2(SOUND_OBJ_WATER_BOMB_BOUNCING);
        o->oAction = 1;
        gMarioState->vel[1] = yVel;
        gMarioState->faceAngle[1] = gMarioState->intendedYaw;
        gMarioState->forwardVel = fVel;
        return set_mario_action(gMarioState, ACT_TWIRLING, 0);
    } else if (o->oTimer >= 45)
    {
        o->oAction = 0;
    }
}

// Squidward

#define /*0x0F8*/ oNPCHasTalkedToMario OBJECT_FIELD_S32(0x1C)

#define NPC_HAS_TALKED 0x2

static struct ObjectHitbox sSquidwardHitbox = {
    /* interactType:      */ INTERACT_TEXT,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 300,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 200,
    /* hurtboxHeight:     */ 200,
};

enum squidwardActions
{
    SQUIDWARD_IDLE,
    SQUIDWARD_TALK,
    SQUIDWARD_GOBACKIDLE
};

void squidward_init(void)
{
    o->oGravity  = 2.5f;
    o->oFriction = 0.8f;
    o->oBuoyancy = 1.3f;
    o->oInteractionSubtype = INT_SUBTYPE_NPC;
    o->header.gfx.scale[0] = 1.0f;
    o->header.gfx.scale[1] = 1.0f;
    o->header.gfx.scale[2] = 1.0f;
    o->oGraphYOffset = 0.0f;
    obj_set_hitbox(o, &sSquidwardHitbox);
}

void squidward_loop(void)
{
    u16 squidward_dialog = DIALOG_SQ;
    if (!cur_obj_nearest_object_with_behavior(bhvConcreteBlock)) {
        squidward_dialog = DIALOG_SQ2;
    }

    switch (o->oAction)
    {
        case SQUIDWARD_IDLE:
            cur_obj_init_animation(0);
            if (o->oInteractStatus == INT_STATUS_INTERACTED)
            {
                o->oAction = SQUIDWARD_TALK;
            }
            break;
        case SQUIDWARD_TALK:
            cur_obj_init_animation(0);
            if (set_mario_npc_dialog(MARIO_DIALOG_LOOK_FRONT) == MARIO_DIALOG_STATUS_SPEAK) {
                 o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
                if (cutscene_object_with_dialog(CUTSCENE_DIALOG, o, squidward_dialog)) {
                    set_mario_npc_dialog(MARIO_DIALOG_STOP);

                    o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                    o->oInteractStatus = 0;
                    o->oAction = SQUIDWARD_IDLE;
                }
            }
            break;
        case SQUIDWARD_GOBACKIDLE:

            break;
    }
}

// KK Platform - ok last platform i swear

void kktable_loop(void)
{
    load_object_collision_model();
}

// Bridge rotate

u16 ifPushed = 0;
u16 ifPushedAgain = 0;

struct ObjectHitbox sBHButtonHitbox = {
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

void button_for_bridge_loop(void)
{
    f32 yVel = 30.0f;
    s16 yaw = 0x1000;

    switch (o->oAction)
    {
        case 0:
            if ((o->oInteractStatus & INT_STATUS_INTERACTED) && (o->oInteractStatus & INT_STATUS_WAS_ATTACKED))
            {
                ifPushed = 1;
                o->oAction = 1;
            }
            break;
        case 1:
            obj_scale_xyz(o, 1.4f * sins(o->oTimer * 0x555), 1.9f * sins(o->oTimer * 555), 1.0f);
            if (o->oTimer >= 10)
            {
                o->oAction = 2;
            }
            break;
        case 2:
            o->oVelY = yVel;
            o->oAngleVelYaw = yaw;
            gLakituState.focus[0] = 1134;
            gLakituState.focus[1] = 28;
            gLakituState.focus[2] = 1775;
            if (o->oTimer >= 20)
            {
                o->oAction = 3;
            }
            break;
        case 3:
            o->oVelY = 0;
            obj_mark_for_deletion(o);
            cur_obj_disable_rendering();
            cur_obj_become_intangible();
            break;
    }
    o->oPosY += o->oVelY;
    obj_set_hitbox(o, &sBHButtonHitbox);

    o->oInteractStatus = INT_STATUS_NONE;

    vec3i_add(&o->oFaceAngleVec, &o->oAngleVelVec);
}

// I know this is very bad but this is the only way i can prevent a bug with 2 days left!
void button_for_bridge_loop_2(void)
{
    f32 yVel = 30.0f;
    s16 yaw = 0x1000;

    switch (o->oAction)
    {
        case 0:
             if ((o->oInteractStatus & INT_STATUS_INTERACTED) && (o->oInteractStatus & INT_STATUS_WAS_ATTACKED))
             {
                ifPushedAgain = 1;
                o->oAction = 1;
             }
            break;
        case 1:
            obj_scale_xyz(o, 1.4f * sins(o->oTimer * 0x555), 1.9f * sins(o->oTimer * 555), 1.0f);
            if (o->oTimer >= 10)
            {
                o->oAction = 2;
            }
            break;
        case 2:
            o->oVelY = yVel;
            o->oAngleVelYaw = yaw;
            if (o->oTimer >= 20)
            {
                o->oAction = 3;
            }
            break;
        case 3:
            o->oVelY = 0;
            obj_mark_for_deletion(o);
            cur_obj_disable_rendering();
            cur_obj_become_intangible();
            break;
    }
    o->oPosY += o->oVelY;
    obj_set_hitbox(o, &sBHButtonHitbox);

    vec3i_add(&o->oFaceAngleVec, &o->oAngleVelVec);
}

void bridge_loop(void)
{   
    switch (o->oAction)
    {
        case 0:
            cur_obj_init_animation(0);
            cur_obj_become_intangible();
            if (ifPushed == 1)
            {
                o->oAction = 1;
            }
            break;
        case 1:
            cur_obj_init_animation(1);
            cur_obj_become_tangible();
            if (o->oTimer >= 21)
            {
                o->oAction = 2;
            }
            break;
        case 2:
            cur_obj_init_animation(2);
            load_object_collision_model();
            break;
    }
}

// The second
void bridge2_loop(void)
{
    switch (o->oAction)
    {
        case 0:
            cur_obj_init_animation(0);
            cur_obj_become_intangible();
            if (ifPushedAgain == 1)
            {
                o->oAction = 1;
            }
            break;
        case 1:
            cur_obj_init_animation(1);
            cur_obj_become_tangible();
            if (o->oTimer >= 21)
            {
                o->oAction = 2;
            }
            break;
        case 2:
            cur_obj_init_animation(2);
            load_object_collision_model();
            break;
    }
}

// King Jelly

u16 getHit = 0; // After button pushed
u16 pushGooButton = 0; // Push button

enum kingJellyActions
{
    KINGJELLY_TURN,
    KINGJELLY_SHOOT,
    KINGJELLY_ATTACKED,
    KINGJELLY_DEATH
};

enum kingJellyAnims
{
    KINGJELLY_ANIM_TURN,
    KINGJELLY_ANIM_SHOOT,
    KINGJELLY_ANIM_ATTACKED
};

struct ObjectHitbox sGooButtonHitbox = {
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

static struct ObjectHitbox sKingJellyHitbox = {
    /* interactType:      */ INTERACT_SHOCK,
    /* downOffset:        */ 0,-
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 90,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 90,
    /* hurtboxHeight:     */ 40,
};

struct ObjectHitbox sShockJHitbox = {
    /* interactType:      */ INTERACT_SHOCK,
    /* downOffset:        */  20,
    /* damageOrCoinValue: */   0,
    /* health:            */   1,
    /* numLootCoins:      */   0,
    /* radius:            */ 150,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 150,
    /* hurtboxHeight:     */ 200,
};

static struct ObjectHitbox sJellyKJHitbox = {
    /* interactType:      */ INTERACT_SHOCK,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 1,
    /* numLootCoins:      */ 0,
    /* radius:            */ 80,
    /* height:            */ 90,
    /* hurtboxRadius:     */ 70,
    /* hurtboxHeight:     */ 80,
};

void king_jellyfish_init(void)
{
    obj_set_hitbox(o, &sKingJellyHitbox);
    play_secondary_music(SEQ_CUSTOM_CRYSTAL_FIELD, 0, 127, 5);
}

void king_jellyfish_turn_to_player(void)
{
    s16 yaw = 0x600;
    cur_obj_rotate_yaw_toward(o->oAngleToMario, yaw);
    cur_obj_rotate_face_angle_using_vel();
}

void king_jelly_spawn_shockwave(void)
{

}

// Different than the jellyfish you find in game these are thrown at that player and from 6 different directions

void king_jelly_spawn_jellyfish_init(void)
{
    o->oGravity  = 2.5f;
    o->oFriction = 0.8f;
    o->oBuoyancy = 1.3f;
    o->oGraphYOffset = 0.0f;
    obj_set_hitbox(o, &sJellyKJHitbox);
}

void king_jelly_spawn_jellyfish(void)
{
    f32 fVel = 40.0f;
    f32 fVel2 = 50.0f;
    
    switch (o->oAction)
    {
        case 0:
            o->oForwardVel = 0;
            if (o->oTimer == 20)
            {
                o->oAction = 1;
            }
            break;
        case 1:
            cur_obj_init_animation(0);
            o->oAngleVelYaw = 0x1000;
            o->oForwardVel = fVel2;
            if (o->oTimer == 60)
            {
                o->oAction = 2;
            }
            break;
        case 2:
            obj_mark_for_deletion(o);
            cur_obj_disable_rendering();
            spawn_mist_from_global();
            cur_obj_become_intangible();
            break;
    }

    vec3i_add(&o->oFaceAngleVec, &o->oAngleVelVec);
    cur_obj_move_xz_using_fvel_and_yaw();
}

void king_jelly_triple_shock(void)
{
    if (o->oTimer == 1)
    {
        struct Object *shock = spawn_object(o, MODEL_KING_JELLY_SHOCK, bhvKingJellyShock);
        shock->oPosX = 594;
        shock->oPosY = 200;
        shock->oPosZ = -55;
    }
    if (o->oTimer == 2)
    {
        struct Object *shock2 = spawn_object(o, MODEL_KING_JELLY_SHOCK, bhvKingJellyShock);
        shock2->oPosX = 606;
        shock2->oPosY = 312;
        shock2->oPosZ = 26;        
    }
    if (o->oTimer == 3)
    {
        struct Object *shock3 = spawn_object(o, MODEL_KING_JELLY_SHOCK, bhvKingJellyShock);
        shock3->oPosX = 606;
        shock3->oPosY = 312;
        shock3->oPosZ = -86; 
    }
}

void king_jelly_raindrop_action(void)
{
    if (o->oTimer == 1)
    {
        struct Object *rain = spawn_object(o, MODEL_GOO_DROP, bhvGooDrop);
        rain->oPosX = 100;
        rain->oPosY = 100;
        rain->oPosZ = 100;
    }
    if (o->oTimer == 2)
    {
        struct Object *rain2 = spawn_object(o, MODEL_GOO_DROP, bhvGooDrop);
        rain2->oPosX = 200;
        rain2->oPosY = 200;
        rain2->oPosZ = 200;
    }
    if (o->oTimer == 3)
    {
        struct Object *rain3 = spawn_object(o, MODEL_GOO_DROP, bhvGooDrop);
        rain3->oPosX = 300;
        rain3->oPosY = 300;
        rain3->oPosZ = 300;
    }
}

u16 shockthrowCount;

void king_jellyfish_loop(void)
{   
    switch (o->oAction)
    {
        case 0:
            king_jellyfish_turn_to_player();
            cur_obj_init_animation(0);
            if (o->oTimer == 120)
            {
                shockthrowCount++;
                if (o->oTimer >= 1)
                {
                    o->oAction = 1;
                }
                o->oTimer = 0;
                if (shockthrowCount == 3)
                {
                    o->oAction = 2;
                }
                if (shockthrowCount == 6)
                {
                    o->oAction = 3;
                }
                if (pushGooButton == 1)
                {
                    o->oAction = 5;
                }
                if (pushGooButton == 2)
                {
                    o->oAction = 5;
                }
                if (getHit == 3)
                {
                    o->oAction = 4;
                }
            }
            break;
        case 1:
            cur_obj_init_animation(1);
            if (o->oTimer == 5)
            {
                spawn_object(o, MODEL_KING_JELLY_SHOCK, bhvKingJellyShock);
            }
            if (cur_obj_check_if_near_animation_end())
            {
                o->oAction = 0;
            }
            break;
        case 2:
            cur_obj_init_animation(1);
            if (cur_obj_check_if_near_animation_end())
            {
                o->oAction = 0;
            }
            break;
        case 3:
            cur_obj_init_animation(1);
            king_jelly_triple_shock();
            shockthrowCount = 0;
            if (cur_obj_check_if_near_animation_end())
            {
                o->oAction = 0;
            }
            break;
        case 4:
            obj_mark_for_deletion(o);
            cur_obj_disable_rendering();
            cur_obj_become_intangible();
            spawn_mist_particles();
            break;
        case 5:
            king_jelly_raindrop_action();
            if (o->oTimer == 130)
            {
                o->oAction = 0;
            }
            break;
        case 6:
            cur_obj_init_animation(1);
            if (o->oTimer == 130)
            {
                o->oAction = 0;
            }
            break;
    }

    if (o->oAction == 2)
    {
        if (o->oTimer == 1)
        {
            struct Object *j = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
            s16 yaw = 0x4000;
            j->oPosX = 564;
            j->oPosY = 210;
            j->oPosZ = -50;
            j->oMoveAngleYaw = yaw;       
            j->oFaceAngleYaw = yaw;
        }
        if (o->oTimer == 2)
        {
            struct Object *j2 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
            s16 yaw = 0x8000;
            j2->oPosX = -56;
            j2->oPosY = 210;
            j2->oPosZ = -693;  
            j2->oMoveAngleYaw = yaw;
            j2->oFaceAngleYaw = yaw;   
        }
        if (o->oTimer == 3)
        {
            struct Object *j3 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
            s16 yaw = 0xC000;
            j3->oPosX = -627;
            j3->oPosY = 210;
            j3->oPosZ = -8;  
            j3->oMoveAngleYaw = yaw;
            j3->oFaceAngleYaw = yaw;   
        }
       if (o->oTimer == 4)
        {
            struct Object *j4 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
            s16 yaw = 0x0000;
            j4->oPosX = 27;
            j4->oPosY = 210;
            j4->oPosZ = 693;
            j4->oMoveAngleYaw = yaw;       
            j4->oFaceAngleYaw = yaw;     
        }
    }
}

void king_jellyfish_goo_switch(void)
{   
    obj_set_hitbox(o, &sGooButtonHitbox);

    f32 yVel = 30.0f;
    s16 yaw = 0x1000;

    switch (o->oAction)
    {
        case 0:
            break;
        case 1:
            obj_scale_xyz(o, 1.4f * sins(o->oTimer * 0x555), 1.9f * sins(o->oTimer * 555), 1.0f);
            if (o->oTimer >= 10)
            {
                o->oAction = 2;
                pushGooButton++;
                o->oTimer = 0;
            }
            break;
        case 2:
            o->oVelY = yVel;
            o->oAngleVelYaw = yaw;
            if (o->oTimer == 1)
            {
                
            }
            if (o->oTimer >= 20)
            {
                o->oAction = 3;
            }
            break;
        case 3:
            o->oVelY = 0;
            obj_mark_for_deletion(o);
            cur_obj_disable_rendering();
            cur_obj_become_intangible();
            break;
    }
    o->oPosY += o->oVelY;
    if (using_ability(ABILITY_BUBBLE_HAT))
    {
        if (gMarioState->action == ACT_PUNCHING || gMarioState->action == ACT_MOVE_PUNCHING || gMarioState->action == ACT_JUMP_KICK) 
        {
             if ((o->oInteractStatus & INT_STATUS_INTERACTED) && (o->oInteractStatus & INT_STATUS_WAS_ATTACKED))
             {
                o->oAction = 1;
             }
        }
    }

    vec3i_add(&o->oFaceAngleVec, &o->oAngleVelVec);
}

void king_jellyfish_goo_loop(void)
{
    f32 yVel = 30.0f;

    switch (o->oAction)
    {
        case 0:
            o->oVelY = yVel;
            if (o->oTimer == 40)
            {
                o->oAction = 1;
                getHit++;
            }
            break;
        case 1:
            obj_mark_for_deletion(o);
            cur_obj_disable_rendering();
            break;
    }

    o->oVelY += o->oPosY;
}

void king_jellyfish_shock_throw(void)
{
    f32 fVel = 30.0f;
    s16 yaw = 0x500;

    obj_set_hitbox(o, &sShockJHitbox);
    
    switch (o->oAction)
    {
        case 0:
            o->oForwardVel = fVel;
            o->oAngleVelYaw = yaw;
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x400);
            if ((o->oInteractStatus & INT_STATUS_INTERACTED))
            {
                o->oAction = 1;
            }
            if (o->oTimer == 100)
            {
                o->oAction = 1;
            }
            break;
        case 1:
            obj_mark_for_deletion(o);
            cur_obj_disable_rendering();
            cur_obj_become_intangible();
            cur_obj_play_sound_2(SOUND_OBJ_ENEMY_DEATH_HIGH);
            spawn_mist_particles();
            break;
    }

    vec3i_add(&o->oFaceAngleVec, &o->oAngleVelVec);
    cur_obj_move_xz_using_fvel_and_yaw();
}

void a_cage_loop(void) {
    struct Object * ability_object = cur_obj_nearest_object_with_behavior(bhvAbilityUnlock);

    switch(o->oAction) {
        case 0: // set home y
            o->oHomeY = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
            o->oAction ++;
            break;
        case 1:
            if (ability_object) {
                vec3f_copy(&ability_object->oPosVec,&o->oPosVec);
                ability_object->oPosY -= 300.0f;
            }

            o->oPosY += o->oVelY;
            o->oVelY -= 2.0f;

            if (o->oPosY < o->oHomeY+400.0f) {
                o->oPosY = o->oHomeY;
                obj_mark_for_deletion(o);
                spawn_mist_particles();
                spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 0.7f, 3);
                cur_obj_play_sound_2(SOUND_GENERAL_BREAK_BOX);
            }
            break;
    }
}
// Robots

u8 robotsKilled;
u8 robotCount;
u8 starCutsceneActive;

// UFO robot

static struct ObjectHitbox sAUFOHitbox = {
    /* interactType:      */ INTERACT_SHOCK,
    /* downOffset:        */ 50,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 1,
    /* numLootCoins:      */ 1,
    /* radius:            */ 80,
    /* height:            */ 90,
    /* hurtboxRadius:     */ 70,
    /* hurtboxHeight:     */ 80,
};

void a_ufo_robot_init(void) {
    o->oGravity = 0.0f;
    o->oFriction = 0.999f;
    o->header.gfx.pos[1] = 5;
    obj_set_hitbox(o, &sAUFOHitbox);
}

void a_ufo_robot_loop(void) {
    object_step();

    o->oInteractStatus = 0;

    // random chance that the ufo robot will spawn a coin when it dies.
    sAUFOHitbox.numLootCoins = (random_u16() % 2);
    
    if (gMarioObject->platform == o) {
        if (gMarioState->action == ACT_GROUND_POUND_LAND) {
            o->oAction = 2;
            robotsKilled++;
            cur_obj_play_sound_2(SOUND_GENERAL_BREAK_BOX);
        }
    }
    
    switch (o->oAction) {
        case 0:
            cur_obj_init_animation(0);
            load_object_collision_model();
            if (o->oDistanceToMario < 1000.0f) {
                o->oAction = 1;
                o->oF8 = 100;
            }
            o->oForwardVel = 0;
            break;
        case 1:
            cur_obj_init_animation(0);
            o->oForwardVel = 10;
            load_object_collision_model();
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x400);
            if (o->oDistanceToMario > 1000.0f) {
                o->oAction = 0;
            }
            break;
        case 2:
            o->oF8++;
            o->oForwardVel = 0;
            if (o->oTimer == 12) {
                o->oAction = 3;
            }
            break;
        case 3:
            cur_obj_disable_rendering();
            cur_obj_become_intangible();
            if (o->oTimer == 1) {
                spawn_mist_particles();
            }
            if (o->oTimer == 12) {
                obj_mark_for_deletion(o);
                obj_explode_and_spawn_coins(1.0f, COIN_TYPE_YELLOW);
            }
            break;
    }

    if (o->oAction == 2) {
        o->header.gfx.scale[1] = 5 * sins(o->oF8 * 0x122);
    }
}

// Chum bucket cutscene

void chum_bucket_cutscene_vel_xyz(f32 x, f32 y, f32 z) {
    gLakituState.goalPos[0] += x;
    gLakituState.goalPos[1] += y;
    gLakituState.goalPos[2] += z;
}

void chum_bucket_cutscene_vel_xyz_foc(f32 x, f32 y, f32 z) {
    gLakituState.goalFocus[0] += x;
    gLakituState.goalFocus[1] += y;
    gLakituState.goalFocus[2] += z;
}

void chum_bucket_cutscene_loop(void) {
    switch (o->oAction) {
        case 0:
            if (o->oTimer == 56) {
                o->oAction = 1;
            }
            break;
        case 1:
            gCamera->cutscene = 1;
            o->oF8++;
            if (o->oTimer == 1) {
                set_mario_action(gMarioState, ACT_WAITING_FOR_DIALOG, 0);
                o->oF8 = 91;
                gLakituState.goalPos[0] = 3373;
                gLakituState.goalPos[1] = 1972;
                gLakituState.goalPos[2] = 2075;

                gLakituState.goalFocus[0] = 2653;
                gLakituState.goalFocus[1] = 1972;
                gLakituState.goalFocus[2] = 635;
            }
            if (o->oF8 < 129) {
                chum_bucket_cutscene_vel_xyz(0, 10 * sins(o->oF8 * 0x200), 0);
            }
            if (o->oF8 == 255) {
                o->oAction = 2;
                spawn_object_abs_with_rot(o, 0, MODEL_NONE, bhvBeatEmUpObject, -2123, 0, 103, 0, 0, 0);
            }
            break;
        case 2:
            if (o->oTimer == 1) {
                gCamera->cutscene = 0;   
                o->oF8 = 0;
            }
            
            if (starCutsceneActive == TRUE) {
                o->oAction = 3;
            }
            break;
        case 3:
            gCamera->cutscene = 1;
            o->oF8++;
            gMarioState->pos[0] = 2858;
            gMarioState->pos[1] = 0;
            gMarioState->pos[2] = -636;
            gMarioState->faceAngle[1] = 0x0000;
            if (o->oTimer == 1) {
                set_mario_action(gMarioState, ACT_WAITING_FOR_DIALOG, 0);
                gLakituState.goalPos[0] = 3373;
                gLakituState.goalPos[1] = 1713;
                gLakituState.goalPos[2] = 2075;

                gLakituState.goalFocus[0] = 2653;
                gLakituState.goalFocus[1] = 1972;
                gLakituState.goalFocus[2] = 635;
            }
            chum_bucket_cutscene_vel_xyz(-20 * sins(o->oF8 * 0x200), 20 * sins(o->oF8 * 0x200), 0);
            if (o->oTimer == 60) {
                o->oAction = 4;
                o->oF8 = 0;
            }
            break;
        case 4:
            o->oF8++;
            chum_bucket_cutscene_vel_xyz(20 * sins(o->oF8 * 0x200), -90 * sins(o->oF8 * 0x312), 7 * sins(o->oF8 * 0x200));
            chum_bucket_cutscene_vel_xyz_foc(0, -60 * sins(o->oF8 * 0x312), 0);
            if (o->oTimer == 40) {
                o->oAction = 5;
                o->oF8 = 0;
            }
            break;
        case 5:
            break;
    }
}

// Beat em up object

void beat_em_up_object(void) {
    char* robotText[] = {
        "DESTROY 10 ROBOTS", 
        "DESTROY 15 ROBOTS", 
        "DESTROY 20 ROBOTS"
    };
    switch (o->oAction) {
        case 0:
            if (o->oTimer == 1) {
                o->oAction = 1;
            }
            break;
        case 1:
            robotsKilled = 0;
            robotCount = 0;
            print_text_centered(SCREEN_CENTER_X, SCREEN_CENTER_Y, robotText[0]);
            set_mario_action(gMarioState, ACT_WAITING_FOR_DIALOG, 0);
            if (o->oTimer == 90) {
                o->oAction = 2;
            }
            break;
        case 2:
            print_text_fmt_int(20, 20, "%d OUT OF 10", robotsKilled);
            if (o->oTimer == 1) {
                set_mario_action(gMarioState, ACT_IDLE, 0);
                sound_init();
                play_music(SEQ_PLAYER_LEVEL, 69 /* lol */, 0);
            }
            if (o->oTimer == 2) {
                play_sound(SOUND_GENERAL_RACE_GUN_SHOT, gMarioState->marioObj->header.gfx.cameraToObject);
            }
            if (o->oTimer == 20) {
                struct Object * spawner = spawn_object_abs_with_rot(o, 0, MODEL_A_ROBOT_LAUNCHER, bhvARobotLauncher, 1456, 258, 1660, 0, 180, 0);
                spawner->oBehParams2ndByte = 0;
            }
            if (robotsKilled >= 10) {
                o->oAction = 3;
            }
            break;
        case 3:
            robotsKilled = 0;
            robotCount = 0;
            print_text_centered(SCREEN_CENTER_X, SCREEN_CENTER_Y, robotText[1]);
            if (o->oTimer == 130) {
                o->oAction = 4;
            }
            break;
        case 4:
            print_text_fmt_int(20, 20, "%d OUT OF 15", robotsKilled);
            if (o->oTimer == 2) {
                play_sound(SOUND_GENERAL_RACE_GUN_SHOT, gMarioState->marioObj->header.gfx.cameraToObject);
            }
            if (o->oTimer == 20) {
                struct Object * spawner1 = spawn_object_abs_with_rot(o, 0, MODEL_A_ROBOT_LAUNCHER, bhvARobotLauncher, 1456, 258, 1660, 0, 180, 0);
                spawner1->oBehParams2ndByte = 1;
            }
            if (o->oTimer == 100) {
                struct Object * spawner2 = spawn_object_abs_with_rot(o, 0, MODEL_A_ROBOT_LAUNCHER, bhvARobotLauncher, 1350, 258, -516, 0, 180, 0);
                spawner2->oBehParams2ndByte = 1;
            }
            if (robotsKilled >= 15) {
                o->oAction = 5;
            }
            break;
        case 5:
            robotsKilled = 0;
            robotCount = 0;
            print_text_centered(SCREEN_CENTER_X, SCREEN_CENTER_Y, robotText[2]);
            if (o->oTimer == 130) {
                o->oAction = 6;
            }
            break;
        case 6:
            print_text_fmt_int(20, 20, "%d OUT OF 20", robotsKilled);
            if (o->oTimer == 2) {
                play_sound(SOUND_GENERAL_RACE_GUN_SHOT, gMarioState->marioObj->header.gfx.cameraToObject);
            }
            if (o->oTimer == 20) {
                struct Object * spawner1 = spawn_object_abs_with_rot(o, 0, MODEL_A_ROBOT_LAUNCHER, bhvARobotLauncher, 1456, 258, 1660, 0, 180, 0);
                spawner1->oBehParams2ndByte = 2;
            }
            if (o->oTimer == 100) {
                struct Object * spawner2 = spawn_object_abs_with_rot(o, 0, MODEL_A_ROBOT_LAUNCHER, bhvARobotLauncher, 1350, 258, -516, 0, 180, 0);
                spawner2->oBehParams2ndByte = 2;
            }
            if (o->oTimer == 160) {
                struct Object * spawner3 = spawn_object_abs_with_rot(o, 0, MODEL_A_ROBOT_LAUNCHER, bhvARobotLauncher, 1350, 258, 623, 0, 180, 0);
                spawner3->oBehParams2ndByte = 2;
            }
            if (robotsKilled >= 20) {
                o->oAction = 7;
            }
            break;
        case 7:
            if (o->oTimer == 1) {
                play_puzzle_jingle();
                stop_background_music(69);
            }
            if (o->oTimer == 80) {
                starCutsceneActive = TRUE;
                o->oAction = 8;
            }
            break;
        case 8:
            if (o->oTimer == 102) {
                play_sound(SOUND_GENERAL_BREAK_BOX, gMarioState->marioObj->header.gfx.cameraToObject);
            }
            if (o->oTimer == 103) {
                play_sound(SOUND_GENERAL_STAR_APPEARS, gGlobalSoundSource);
                play_music(SEQ_PLAYER_LEVEL, 21, 0);
                starCutsceneActive = FALSE;
            }
            if (o->oTimer == 184) {
                gCamera->cutscene = 0;
                set_mario_action(gMarioState, ACT_IDLE, 0);
            }
            break;
    }
}

// Ham robot

enum aHamRobotAnims {
    ANIM_A_HAM_ROBOT_WALK, ANIM_A_HAM_ROBOT_IDLE, ANIM_A_HAM_ROBOT_FIND, 
    ANIM_A_HAM_ROBOT_SWING_HAMMER, ANIM_A_HAM_ROBOT_GET_UP, ANIM_A_HAM_ROBOT_DESTROYED
};

static struct ObjectHitbox sAHamRobotHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 50,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 1,
    /* numLootCoins:      */ 1,
    /* radius:            */ 180,
    /* height:            */ 290,
    /* hurtboxRadius:     */ 10,
    /* hurtboxHeight:     */ 10,
};

void ham_robot_init(void) {
    o->header.gfx.scale[0] = 0.4f;
    o->header.gfx.scale[1] = 0.4f;
    o->header.gfx.scale[2] = 0.4f;
    o->oPosY += 46;
}

void ham_robot_loop(void) {
    obj_set_hitbox(o, &sAHamRobotHitbox);
    object_step();
    
    // random chance that the ufo robot will spawn a coin when it dies.
    sAHamRobotHitbox.numLootCoins = (random_u16() % 2);
    
    switch (o->oAction) {
        case 0 /* IDLE */:
            if (o->oDistanceToMario < 1000.0f) {
                o->oAction = 1;
            }
            cur_obj_init_animation(ANIM_A_HAM_ROBOT_IDLE);
            break;
        case 1 /* FOUND MARIO*/:
            if (cur_obj_was_attacked_or_ground_pounded()) {
                o->oAction = 5;
            }
            cur_obj_init_animation(ANIM_A_HAM_ROBOT_FIND);
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x1000);
            if (o->oTimer == 1) {
                cur_obj_play_sound_2(SOUND_OBJ_GOOMBA_ALERT);
            }
            if (o->oTimer == 14) {
                o->oAction = 2;
            }
            break;
        case 2 /* FOLLOW MARIO */:
            if (cur_obj_was_attacked_or_ground_pounded()) {
                o->oAction = 5;
            }
            cur_obj_init_animation(ANIM_A_HAM_ROBOT_WALK);
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x400);
            if (lateral_dist_between_objects(gMarioObject, o) < 300.0f) {
                o->oAction = 3;
                o->oInteractStatus = 0;
            }
            o->oForwardVel = 14;
            break;
        case 3 /* WACK HAMMER */:
            o->oForwardVel = 0;
            if (cur_obj_was_attacked_or_ground_pounded()) {
                o->oAction = 5;
            }
            if (o->header.gfx.animInfo.animFrame < 22) {
                if (cur_obj_was_attacked_or_ground_pounded()) {
                    o->oAction = 5;
                }
            }
            if (o->header.gfx.animInfo.animFrame == 22) {
                spawn_object(o, MODEL_PISSWAVE, bhvBowserShockWave);
            }
            cur_obj_init_animation(ANIM_A_HAM_ROBOT_SWING_HAMMER);
            if (o->oTimer == 29) {
                o->oAction = 4;
            }
            break;
        case 4 /* GET BACK UP */:
            cur_obj_init_animation(ANIM_A_HAM_ROBOT_GET_UP);
            if (cur_obj_was_attacked_or_ground_pounded()) {
                o->oAction = 5;
            }
            if (o->oTimer == 29) {
                o->oAction = 0;
                o->oInteractStatus = 0;
            }
            break;
        case 5 /* DESTROYED */:
            o->oForwardVel = -24;
            cur_obj_become_intangible();
            cur_obj_init_animation(ANIM_A_HAM_ROBOT_DESTROYED);
            if (o->oTimer == 17) {
                obj_mark_for_deletion(o);
                obj_explode_and_spawn_coins(3.0f, COIN_TYPE_YELLOW);
                cur_obj_disable_rendering();
                spawn_mist_particles();    
                robotsKilled++;
            }
            break;
        case 6 /* INSTANT DESTROY */:
            obj_mark_for_deletion(o);
            cur_obj_become_intangible();
            cur_obj_disable_rendering();
            spawn_mist_particles();    
            break;
    }
}

// Launched box

void a_launched_box(void) {
    ModelID32 model;
    BehaviorScript behavior;
    //print_text_fmt_int(100, 100, "BOT %d", o->oBehParams2ndByte);
    cur_obj_update_floor_and_walls();

    switch (o->oAction) {
        case 0:
            o->oHomeY = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
            o->oAction = 1;
            break;
        case 1:
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x2000);
            if (o->oTimer < 7) {
                o->oVelY = 37;
                o->oForwardVel = 21;
            }
            if (o->oTimer >= 7) {
                o->oVelY-=2;
            }
            cur_obj_move_xz_using_fvel_and_yaw();
            o->oPosY += o->oVelY;
            if (o->oPosY < o->oHomeY - 241) {
                o->oAction = 2;
                if (o->oBehParams2ndByte == 2) {
                    struct Object *ham = spawn_object(o, MODEL_A_HAM_ROBOT, bhvAHamRobot);
                    ham->oPosY = -5;
                } 
                if (o->oBehParams2ndByte == 1){
                    struct Object *ufo = spawn_object(o, MODEL_A_UFO_ROBOT, bhvAUFORobot);
                    ufo->oPosY += 190;
                }
                if (o->oBehParams2ndByte == 0) {
                    struct Object *dog = spawn_object(o, MODEL_A_DOG_ROBOT, bhvADogRobot);
                    dog->oPosY += 100;
                }
                spawn_mist_particles();
                cur_obj_play_sound_2(SOUND_GENERAL_BREAK_BOX);
            }
            break;
        case 2:
            if (o->oTimer == 27) {
                obj_mark_for_deletion(o);
            }
            cur_obj_disable_rendering();
            cur_obj_become_intangible();
            break;
    }
}

// Robot launcher

void a_robot_launcher_loop(void) {
    switch (o->oAction) {
        case 0:
            o->header.gfx.scale[1] = 1.0f;
            o->oF8 = 0;
            if (o->oTimer == 180) {
                o->oAction = 1;
                robotCount++;
                struct Object *box = spawn_object(o, MODEL_A_LAUNCHED_BOX, bhvALaunchedBox);
                box->oPosY += 200;
                box->oBehParams2ndByte = (random_u16() % 3);
                cur_obj_play_sound_2(SOUND_OBJ_WATER_BOMB_CANNON);
            }
            switch (o->oBehParams2ndByte) {
                case 0:
                    if (robotCount >= 10) {
                        o->oAction = 2;
                    }
                    break;
                case 1:
                    if (robotCount >= 15) {
                        o->oAction = 2;
                    }
                    break;
                case 2:
                    if (robotCount >= 20) {
                        o->oAction = 2;
                    }
                    break;
            }
            break;
        case 1:
            o->oF8++;
            o->header.gfx.scale[1] = 2 * coss(o->oF8 * 0x433);
            if (o->oTimer == 9) {
                o->oAction = 0;
            }
            break;
        case 2:
            obj_mark_for_deletion(o);
            spawn_mist_particles();
            cur_obj_disable_rendering();
            break;
    }
}

// Dog robot

enum dogRobotAnims { 
    ANIM_DOG_ROBOT_IDLE, ANIM_DOG_ROBOT_JUMP, 
    ANIM_DOG_ROBOT_BURP, ANIM_DOG_ROBOT_DESTROYED
};

static struct ObjectHitbox sADogRobotHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 50,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 1,
    /* numLootCoins:      */ 1,
    /* radius:            */ 60,
    /* height:            */ 180,
    /* hurtboxRadius:     */ 40,
    /* hurtboxHeight:     */ 160,
};

void a_dog_robot_init(void) {
    
}

void a_dog_robot_loop(void) {
    obj_set_hitbox(o, &sADogRobotHitbox);
    object_step();
    
    sADogRobotHitbox.numLootCoins = (random_u16() % 2);

    switch (o->oAction) {
        case 0 /* IDLE */:
            cur_obj_init_animation(ANIM_DOG_ROBOT_IDLE);
            o->oForwardVel = 0;
            if (o->oDistanceToMario < 1000.f) {
                o->oAction = 1;
            }
            break;
        case 1 /* FIND PLAYER */:
            cur_obj_init_animation(ANIM_DOG_ROBOT_JUMP);
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x600);
            if (cur_obj_check_anim_frame(10)) {
                cur_obj_play_sound_2(SOUND_GENERAL_CRAZY_BOX_BOING_FAST);
                o->oForwardVel = 20;
            }
            if (cur_obj_check_anim_frame(24)) {
                o->oForwardVel = 0;
            }
            if (lateral_dist_between_objects(gMarioObject, o) < 250.f) {
                o->oAction = 2;
            }
            if ((o->oDistanceToMario > 1000.f) && (cur_obj_check_if_near_animation_end())) {
                o->oAction = 0;
            }
            if (cur_obj_was_attacked_or_ground_pounded()) {
                o->oAction = 3;
            }
            break;
        case 2 /* ATTACK */:
            o->oForwardVel = 0;
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x600);
            if (cur_obj_was_attacked_or_ground_pounded()) {
                o->oAction = 3;
            }
            if (cur_obj_check_anim_frame(39)) {
                o->oAction = 0;
            }
            cur_obj_init_animation(ANIM_DOG_ROBOT_BURP);
            if (cur_obj_check_anim_frame(15)) {
                cur_obj_play_sound_2(SOUND_OBJ_MRI_SHOOT);
                spawn_object(o, MODEL_A_GAS_CLOUD, bhvAGasCloud);
            }
            break;
        case 3:
            o->oForwardVel = -27;
            cur_obj_init_animation(ANIM_DOG_ROBOT_DESTROYED);
            if (o->oTimer == 15) {
                obj_mark_for_deletion(o);
                obj_explode_and_spawn_coins(3.0f, COIN_TYPE_YELLOW);
                cur_obj_become_intangible();
                cur_obj_disable_rendering();
                spawn_mist_particles();    
                robotsKilled++;
            }
            break;
    }
}

// Gas cloud

static struct ObjectHitbox sAGasCloudHitBox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 50,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 1,
    /* numLootCoins:      */ 1,
    /* radius:            */ 60,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 10,
    /* hurtboxHeight:     */ 10,
};

void a_gas_cloud_loop(void) {
    obj_set_hitbox(o, &sAGasCloudHitBox);
    object_step();
    switch (o->oAction) {
        case 0:
            if (o->oTimer == 1) {
                cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x2000);
            }
            o->oF8++;
            o->oForwardVel = 15;
            if (o->oTimer == 75) {
                o->oAction = 1;
                o->oFC = 14;
            }
            break;
        case 1:
            o->oFC++;
            o->oForwardVel = 15;
            if (o->oTimer == 10) {
                o->oAction = 2;
            }
            break;
        case 2:
            obj_mark_for_deletion(o);
            break;
    }

    if (o->oAction == 0) {
        obj_scale_xyz(o,
        1.0f - 0.2f * sins(o->oF8 * 0x222),
        1.0f - 0.2f * coss(o->oF8 * 0x222),
        1.0f - 0.2f * sins(o->oF8 * 0x222));
    }
    if (o->oAction == 1) {
        obj_scale_xyz(o,
        1.0f * sins(o->oFC * 0x500),
        1.0f * sins(o->oFC * 0x500),
        1.0f * sins(o->oFC * 0x500));
    }
}

// Chained cage

void a_chained_cage_loop(void) {
    struct Object * star = cur_obj_nearest_object_with_behavior(bhvStar);
    switch (o->oAction) {
        case 0:
            if (o->oTimer == 56) {
                o->oAction = 1;
            }
            break;
        case 1:
            if (star) {
                star->oPosY -= 9 * sins(o->oF8 * 0x100);
            }
            cur_obj_play_sound_2(SOUND_ENV_ELEVATOR1);
            o->oVelY = -9 * sins(o->oF8 * 0x100);
            o->oF8++;
            if (o->oTimer == 127) {
                o->oAction = 2;
            }
            break;
        case 2:
            if (o->oTimer == 2) {
                cur_obj_play_sound_2(SOUND_GENERAL_ELEVATOR_LAND);
            }
            o->oVelY = 0;
            if (starCutsceneActive == TRUE) {
                o->oAction = 3;
            }
            break;
        case 3:
            if (o->oTimer < 60) {
                o->oVelY = 0;
            } else {
                if (star) {
                    star->oPosY += star->oVelY;
                    star->oVelY-=2;
                }
                o->oVelY-=2;
            }
            if (o->oTimer == 61) {
                cur_obj_play_sound_2(SOUND_GENERAL_BIG_POUND);
            }
            if (o->oTimer == 103) {
                o->oAction = 4;
                o->oF8 = 0;
            }
            break;
        case 4:
            o->oF8++;
            if (star) {
                if (o->oF8 < 75) {
                    star->oPosY += 10 * sins(o->oF8 * 0x300);
                    star->oPosX += -15 * sins(o->oF8 * 0x80);
                }
            }
            if (o->oF8 == 85) {
                o->oAction = 5;
            }
            cur_obj_disable_rendering();
            spawn_mist_particles();
            spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 0.7f, 3);
            cur_obj_play_sound_2(SOUND_GENERAL_BREAK_BOX);
            break;
        case 5:
            obj_mark_for_deletion(o);
            break;
    }

    o->oPosY += o->oVelY;
    o->oPosZ += o->oVelZ;
}