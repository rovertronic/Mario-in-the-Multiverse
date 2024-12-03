#include "src/game/interaction.h"
#include "src/game/ability.h"
#include "dialog_ids.h"
#include "src/game/bullet_system.h"
#include "src/game/camera.h"
#include "src/engine/surface_collision.h"
Bool8 inCutscene = FALSE;
Bool8 littleSisterCutscene = FALSE;
u8 curCutsceneState = 0;
Vec3f cutsceneFocus = {0, 0, 0};
Vec3f cutscenePos = {0, 0, 0};
Vec3f cutsceneNextFocus = {0, 0, 0};
Vec3f cutsceneNextPos = {0, 0, 0};
u16 cutsceneTimer = 0;

    struct ObjectHitbox sConcreteBlockHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */   0,
    /* damageOrCoinValue: */   0,
    /* health:            */   1,
    /* numLootCoins:      */   0,
    /* radius:            */ 150,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 150,
    /* hurtboxHeight:     */ 200,
    };

    static struct ObjectHitbox sGaugeHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 1,
    /* radius:            */ 120,
    /* height:            */ 260,
    /* hurtboxRadius:     */ 120,
    /* hurtboxHeight:     */ 260,
};

    static struct ObjectHitbox sAirlockButtonHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */ 45,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 1,
    /* radius:            */ 46,
    /* height:            */ 91,
    /* hurtboxRadius:     */ 46,
    /* hurtboxHeight:     */ 91,
};

    static struct ObjectHitbox sAirlockWater = {
    /* interactType:      */ INTERACT_NONE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 0,
    /* height:            */ 0,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

    static struct ObjectHitbox sCrusherHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 1,
    /* radius:            */ 250,
    /* height:            */ 706,
    /* hurtboxRadius:     */ 250,
    /* hurtboxHeight:     */ 706,
};

    static struct ObjectHitbox sTurretHitbox = {
    /* interactType:      */ INTERACT_SPINY_WALKING,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 1,
    /* radius:            */ 110,
    /* height:            */ 210,
    /* hurtboxRadius:     */ 110,
    /* hurtboxHeight:     */ 210,
};

    static struct ObjectHitbox sCeilingTurretHitbox = {
    /* interactType:      */ INTERACT_SPINY_WALKING,
    /* downOffset:        */ 210,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 1,
    /* radius:            */ 110,
    /* height:            */ 210,
    /* hurtboxRadius:     */ 110,
    /* hurtboxHeight:     */ 210,
};

    static struct ObjectHitbox sTurretPanelHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */ 90,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 1,
    /* radius:            */ 46,
    /* height:            */ 179,
    /* hurtboxRadius:     */ 46,
    /* hurtboxHeight:     */ 179,
};

struct ObjectHitbox sBigDaddyHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */   0,
    /* damageOrCoinValue: */   1,
    /* health:            */   3,
    /* numLootCoins:      */   0,
    /* radius:            */ 170,
    /* height:            */ 420,
    /* hurtboxRadius:     */ 170,
    /* hurtboxHeight:     */ 420,
};
    
static u8 sBossDaddyAttackHandlers[] = {
    /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_SPECIAL_HUGE_GOOMBA_WEAKLY_ATTACKED,
    /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_SPECIAL_HUGE_GOOMBA_WEAKLY_ATTACKED,
    /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_SQUISHED,
    /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_SQUISHED,
    /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_SPECIAL_HUGE_GOOMBA_WEAKLY_ATTACKED,
    /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_SPECIAL_HUGE_GOOMBA_WEAKLY_ATTACKED,
};

enum {
    AIRLOCK_STATE_WET,
    AIRLOCK_STATE_DRY,
    AIRLOCK_STATE_CLOSED,
    AIRLOCK_STATE_CLOSED_FINISHED,
};

u8 airlockState = 0;
Bool8 isWet = TRUE;
Bool8 waterMoving = FALSE;
Bool8 activeGauge[15];


void bhv_concrete_block_init(void){
    f32 Scale = GET_BPARAM2(o->oBehParams);
    sConcreteBlockHitbox.radius = 150 + (Scale/100.0);
    sConcreteBlockHitbox.height = 200 + (Scale/100.0) - 3;
    sConcreteBlockHitbox.hurtboxHeight = 200 + (Scale/100.0) - 3;
    cur_obj_scale(1.0 + Scale/100.0);
    obj_set_hitbox(o, &sConcreteBlockHitbox);
    if (GET_BPARAM1(o->oBehParams) >= 3){
        o->oHealth = 2;
    } else {
        o->oHealth = GET_BPARAM1(o->oBehParams);
    }
}

void bhv_concrete_block_loop(void) {
    if (o->oHealth == 2){
        cur_obj_set_model(MODEL_CONCRETE_BLOCK);
    }else if (o->oHealth == 1){
        cur_obj_set_model(MODEL_CONCRETE_BLOCK_CRACK1);
    }else if (o->oHealth == 0){
        cur_obj_set_model(MODEL_CONCRETE_BLOCK_CRACK2);
    }
    if (using_ability(ABILITY_BIG_DADDY)){
        if (gMarioState->action == ACT_PUNCHING || gMarioState->action == ACT_MOVE_PUNCHING || gMarioState->action == ACT_JUMP_KICK){
            if ((o->oInteractStatus & INT_STATUS_INTERACTED) && (o->oInteractStatus & INT_STATUS_WAS_ATTACKED)) {
                if (o->oTimer >= 10){
                    o->oTimer = 0;
                    if (o->oHealth > 0){
                        o->oHealth -= 1;
                    } else {
                        obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
                        create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
                    }
                }
            }
        }
    }
    if (o->oShotByShotgun > 0) {
        o->oShotByShotgun = 0;

        if (o->oHealth > 0){
            o->oHealth -= 1;
        } else {
            obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
            create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
        }
    }
    o->oInteractStatus = INT_STATUS_NONE;
}

void bhv_gauge_init(void){
    obj_set_hitbox(o, &sGaugeHitbox);
    o->header.gfx.animInfo.animFrame = (random_u16()%21);
}

void bhv_gauge_loop(void){
    if(o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED){
        activeGauge[GET_BPARAM1(o->oBehParams)] = TRUE;
        spawn_triangle_break_particles(20, 138, 0.3f, 3);
        create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
        mark_obj_for_deletion(o);
    }
}


void bhv_waterfall_hidden_loop(void){
    cur_obj_move_using_fvel_and_gravity();
    cur_obj_update_floor_and_walls();
    if (activeGauge[GET_BPARAM1(o->oBehParams)] == TRUE){
        spawn_object(o, MODEL_WATERFALL, bhvWaterfall);
        mark_obj_for_deletion(o);
    }
}

void bhv_waterfall_loop(void){
    cur_obj_move_using_fvel_and_gravity();
    cur_obj_update_floor_and_walls();
    if (o->oPosY < (o->oHomeY + 1052.0f)){
        o->oPosY += 25;
    } else {
        o->oPosY = (o->oHomeY + 1052.0f);
    }
}

void bhv_debris_init(void){
    o->oAction = 0;
}

void bhv_debris_loop(void){
    o->oFaceAngleYaw += 0x80;
    o->oMoveAngleYaw = o->oFaceAngleYaw;
}

void bhv_airlock_init(){
    if (GET_BPARAM1(o->oBehParams) == 1){
        o->oPosY = o->oHomeY + 455.0;
    }
}

void bhv_airlock_loop(){
    if (GET_BPARAM1(o->oBehParams) == airlockState){
        if (o->oPosY > o->oHomeY){
            o->oPosY-= 10;
        } else {
            o->oPosY = o->oHomeY;
        }
    }
    if (airlockState == AIRLOCK_STATE_CLOSED){
        if (o->oPosY < o->oHomeY + 455.0){
            o->oPosY+= 10;
        } else {
            o->oPosY = o->oHomeY + 455.0;
            if (GET_BPARAM1(o->oBehParams) != isWet && o->oPosY == o->oHomeY + 455.0){
                airlockState = AIRLOCK_STATE_CLOSED_FINISHED;
            }
        }
    }
}

void bhv_airlock_button_init(void){
    obj_set_hitbox(o, &sAirlockButtonHitbox);
}

void bhv_airlock_button_loop(){
    //print_text_fmt_int(20, 20, "Airlock State: %d", airlockState);
    if (airlockState != AIRLOCK_STATE_CLOSED || airlockState != AIRLOCK_STATE_CLOSED_FINISHED){
        if(o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED){
            //print_text(20, 40, "Button Pressed");
            o->oInteractStatus = INT_STATUS_NONE;
            airlockState = AIRLOCK_STATE_CLOSED;
            cur_obj_play_sound_2(SOUND_GENERAL_WATER_LEVEL_TRIG);
        }
    }
}

void bhv_airlock_water_loop(){
    cur_obj_update_floor_and_walls();
    if (isWet == TRUE && airlockState == AIRLOCK_STATE_CLOSED_FINISHED){
        if (o->oPosY >= o->oHomeY - 860.0f){
            o->oPosY-= 10;
        } else {
            o->oPosY = o->oHomeY - 860.0f;
            isWet = FALSE;
            airlockState = AIRLOCK_STATE_DRY;

        }
    } else if (isWet == FALSE && airlockState == AIRLOCK_STATE_CLOSED_FINISHED){
        if (o->oPosY <= o->oHomeY){
            o->oPosY+= 10;
        } else {
            o->oPosY = o->oHomeY;
            isWet = TRUE;
            airlockState = AIRLOCK_STATE_WET;
        }
    }
}

// penguin stuff

void bhv_big_daddy_init(void){
    inCutscene = FALSE;
    o->oInteractionSubtype = INT_SUBTYPE_NPC;
}

void bhv_big_daddy_loop(void) {
    //print_text_fmt_int(20, 40, "oSubAction: %d", o->oSubAction);
    //print_text_fmt_int(20, 60, "oAction: %d", o->oAction);
    f32 dist;
    struct Object *littleSisterObj = cur_obj_find_nearest_object_with_behavior(bhvLittleSister, &dist);
    o->prevObj = littleSisterObj;
    o->activeFlags |= ACTIVE_FLAG_IGNORE_ENV_BOXES;
    cur_obj_update_floor_and_walls();
    cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x100);
    switch (o->oAction){
        case 0:
            if (dist < 500.0f && gMarioState->floor->type == SURFACE_BDADDY){
                if (o->prevObj->oPosX <= 2478){
                    o->oAction = 1;
                }
            }
            break;
        case 1:
            if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP,
                DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, BIG_DADDY_STAR)) {
                    o->oInteractStatus = INT_STATUS_NONE;
                    o->oAction = 2;
                }
            break;
        case 2:
            cur_obj_spawn_star_at_y_offset(gMarioState->pos[0], gMarioState->pos[1] + 300, gMarioState->pos[2], 0.0f);
            o->oAction = 3;
            break;
        case 3:
            if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP,
                DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, BIG_DADDY_ABILITY_TEXT)) {

                    o->oAction = 4;
                }
            break;
        case 4:
            o->prevObj->oInteractionSubtype |= INT_SUBTYPE_DROP_IMMEDIATELY;
            spawn_object_relative(0, 400, 0, 0, o, MODEL_EXPLOSION, bhvSafeExplosion);
            spawn_object_relative(ABILITY_BIG_DADDY, 400, 0, 0, o, MODEL_ABILITY, bhvAbilityUnlock);
            o->oAction = 5;
            o->oInteractStatus = INT_STATUS_INTERACTED;;
            break;
    }
    switch (o->oSubAction) {
        case 0:
            if (!(dist < 500.0f) && cur_obj_can_mario_activate_textbox_2(499.0f, 100.0f) && o->oAction == 0) {
                    o->oSubAction++; 
                }
            break;
        case 1:
            if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP,
                    DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, BIG_DADDY_HELP)) {
                    o->oInteractStatus = INT_STATUS_NONE;
                o->oSubAction++; 
                }
            break;
        case 2:
            if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP,
                    DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, BIG_DADDY_HELP_REPEAT)) {
                    o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                    o->oInteractStatus = INT_STATUS_NONE;
                }
            }
            break;
    }
    cur_obj_move_standard(-78);
}

enum sister_states {
    LS_NPC_START,
    LS_IDLE,
    LS_CUTSCENE,
    LS_SIT,
    LS_NPC_END,
    LS_CRUSHED,
};

void bhv_little_sister_loop(void) {
    o->parentObj = cur_obj_nearest_object_with_behavior(bhvBigDaddy);
    static u8 sisterTimer;
    if (sisterTimer <= 10){
        sisterTimer++;
    }
    //print_text_fmt_int(20, 40, "oAction: %d", o->oAction);
    //print_text_fmt_int(20, 60, "oF4: %d", o->oF4);
    //print_text_fmt_int(20, 80, "oTimer: %d", sisterTimer);
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(-78);
    if (obj_hit_by_bullet(o, 144.0f) == 1 && sisterTimer > 10){
        o->oF4 = 1;
        o->oHeldState = HELD_DROPPED;
        gMarioState->action = ACT_IDLE;
        gMarioState->heldObj = NULL;
        sisterTimer = 0;
        spawn_mist_particles_with_sound(SOUND_ACTION_TELEPORT);
        o->oPosX = o->oHomeX;
        o->oPosY = o->oHomeY;
        o->oPosZ = o->oHomeZ;
        o->oAction = LS_IDLE;
        cur_obj_init_animation(0);
    }
    if (o->oFloorType == SURFACE_INSTANT_QUICKSAND && o->oFloorHeight == o->oPosY){
        sisterTimer = 0;
        o->oPosX = o->oHomeX;
        o->oPosY = o->oHomeY;
        o->oPosZ = o->oHomeZ;
        play_sound(SOUND_ACTION_TELEPORT, gGlobalSoundSource);
    }
    //print_text_fmt_int(20, 20, "oAction: %d", o->oAction);
    /*
        if (inCutscene == FALSE){
        inCutscene = TRUE;
        gCamera->mode = CAMERA_MODE_FIXED;
        gMarioState->action = ACT_IDLE;
        gMarioState->controller = &gControllers[5];
        gCamera->cutscene = 1;
        reset_camera(gCamera);
    }
    if (inCutscene == TRUE){
        gLakituState.goalPos[0] = 0;
        gLakituState.goalPos[1] = 0;
        gLakituState.goalPos[2] = 0;
        gLakituState.goalFocus[0] = 50;
        gLakituState.goalFocus[1] = 50;
        gLakituState.goalFocus[2] = 50;   
    }
    */
    f32 distRespawn;
    struct Object *respawner = cur_obj_find_nearest_object_with_behavior(bhvCheckpointFlag, &distRespawn);
    if (distRespawn < 100.0f){
        vec3f_copy(&o->oHomeVec,gMarioState->vecCheckpointFlag);
    }
    f32 dist;
    struct Object *crusher = cur_obj_find_nearest_object_with_behavior(bhvCrusher, &dist);
    if (dist < 250.0f){
        o->header.gfx.scale[1] = .2f;
        o->oInteractType = INTERACT_NONE;
        //print_text(20, 20, "Too Close!");
        sisterTimer = 0;
        o->oAction = LS_CRUSHED;
    } if (o->oAction == LS_CRUSHED){
    if (sisterTimer > 10){
            spawn_mist_particles_with_sound(SOUND_ACTION_TELEPORT);
            o->oPosX = o->oHomeX;
            o->oPosY = o->oHomeY;
            o->oPosZ = o->oHomeZ;
            o->oInteractType = INTERACT_GRABBABLE;
            o->oAction = LS_IDLE;
            o->header.gfx.scale[1] = 1.0f;
            cur_obj_init_animation(0);
        }
    }
    if (o->oDistanceToMario < 500.0f && o->oAction == LS_NPC_START && gMarioState->floorHeight == gMarioState->pos[1]){
        if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP,
            DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG_NO_ZOOM, LITTLE_SISTER_TEXT_1)) {
                o->oInteractStatus = INT_STATUS_NONE;
                o->oInteractType = INTERACT_GRABBABLE;
                o->oInteractionSubtype = INT_SUBTYPE_HOLDABLE_NPC;
                o->oAction = LS_CUTSCENE;
                
                
        }
    }
    if (o->oAction == LS_CUTSCENE){
        inCutscene = TRUE;
        magic_mirror_disable = TRUE;
        switch (curCutsceneState) {
            case 0:
                curCutsceneState = 1;
                break;
            case 1:
                cutsceneFocus[0] = 2702;
                cutsceneFocus[1] = 895;
                cutsceneFocus[2] = -1389;
                cutscenePos[0] = 3000;
                cutscenePos[1] = 895;
                cutscenePos[2] = -1389;
                gLakituState.mode = CAMERA_MODE_NONE;
                gMarioState->controller = &gControllers[5];
                curCutsceneState = 2;
                break;
            case 2:
                gLakituState.goalPos[0] = cutscenePos[0];
                gLakituState.goalPos[1] = cutscenePos[1];
                gLakituState.goalPos[2] = cutscenePos[2];
                gLakituState.goalFocus[0] = cutsceneFocus[0];
                gLakituState.goalFocus[1] = cutsceneFocus[1];
                gLakituState.goalFocus[2] = cutsceneFocus[2];
                cutsceneTimer++;
                if (cutsceneTimer > 15){
                curCutsceneState = 3;
                cutsceneTimer = 0;
                }
                break;
            case 3:
                cutsceneTimer++;
                if (cutsceneTimer > 15){
                curCutsceneState = 4;
                cutsceneTimer = 0;
                }
                break;
            case 4:
                set_or_approach_f32_asymptotic(&gLakituState.goalPos[0], 3500, 0.05f);
                set_or_approach_f32_asymptotic(&gLakituState.goalFocus[1], 650, 0.05f);
                if (gLakituState.goalPos[0] > 3499.0f){
                    curCutsceneState = 4;
                }
                break;
            case 5:
                gLakituState.goalPos[0] = 4200;
                gLakituState.goalPos[1] = 1100;
                gLakituState.goalPos[2] = -2194;
                gLakituState.goalFocus[0] = 5700;
                gLakituState.goalFocus[1] = 382;
                gLakituState.goalFocus[2] = -1389;
                cutsceneTimer++;
                if (cutsceneTimer > 60){
                curCutsceneState = 6;
                }
                break;
            case 6:
                gLakituState.mode = CAMERA_MODE_8_DIRECTIONS;
                gMarioState->controller = &gControllers[0];
                inCutscene = FALSE;
                o->oAction = LS_IDLE;
                curCutsceneState = 0;
                break;

        }
    }
    if (o->oAction == LS_NPC_END){
        magic_mirror_disable = FALSE;
        o->oHomeX = o->oPosX;
        o->oHomeY = o->oPosY;
        o->oHomeZ = o->oPosZ;
        cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x250);
        cur_obj_init_animation(0);
        if (o->oInteractStatus & INT_STATUS_INTERACTED) {
            if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP,
                DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, LITTLE_SISTER_TEXT_2)) {
                o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                o->oInteractStatus = INT_STATUS_NONE;
            }
        }
    }
    switch (o->oHeldState) {  
        case HELD_HELD:
            o->header.gfx.scale[1] = 1.0f;
            if (phasewalk_state != 0){
                gMarioState->action = ACT_PLACING_DOWN;
            }
            cur_obj_unrender_set_action_and_anim(1, LS_SIT);
            if (cur_obj_check_if_at_animation_end() && o->oAction == LS_IDLE) {
                o->oAction = LS_SIT;
            }
            obj_copy_pos(o, gMarioObject);
            break;
        case HELD_THROWN:
            cur_obj_get_thrown_or_placed(0.0f, 0.0f, 0);
            break;
        case HELD_DROPPED:
            cur_obj_get_dropped();
            break;
        case HELD_FREE:
            if (o->oAction == LS_SIT) {
                cur_obj_init_animation(2);
                if (cur_obj_check_if_at_animation_end()){
                    if (o->parentObj->oAction == 5) {
                        o->oInteractionSubtype = INT_SUBTYPE_NPC;
                        o->oInteractType = INTERACT_TEXT;
                        o->oAction = LS_NPC_END;
                    } else {
                        o->oAction = LS_IDLE;
                        o->oInteractStatus = 0;
                        cur_obj_init_animation(0);
                    }
                }
            }
            break;
    }

    if (o->oAction != LS_NPC_END) {
        o->oInteractStatus = 0;
    }
}

enum CrusherStates {
    CRUSHER_STATE_IDLE,
    CRUSHER_STATE_DOWN,
    CRUSHER_STATE_UP,
    CRUSHER_STATE_BOTTOM,
};
void bhv_crusher_init(void){
    obj_set_hitbox(o, &sCrusherHitbox);
}
void bhv_crusher_loop(void){
    cur_obj_update_floor_and_walls();
    cur_obj_move_using_fvel_and_gravity();
    //print_text_fmt_int(20, 20, "oAction: %d", o->oAction);
    switch (o->oAction){
        case CRUSHER_STATE_IDLE: 
            o->oAction = CRUSHER_STATE_DOWN;
            o->oTimer = 0;
            break;
        case CRUSHER_STATE_DOWN:
            if (o->oPosY > o->oFloorHeight){
                o->oGravity = -4;
            } else {
                o->oPosY = o->oFloorHeight;
                o->oVelY = 0;
                cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
                o->oAction = CRUSHER_STATE_BOTTOM;
            }
            break;
        case CRUSHER_STATE_BOTTOM:
                o->oAction = CRUSHER_STATE_UP;
                o->oTimer = 0;
            
            break;
        case CRUSHER_STATE_UP:
            o->oGravity = 0;
            if (o->oPosY < o->oHomeY){
                if (GET_BPARAM1(o->oBehParams) == 0){
                    o->oVelY = 10;
                } else {
                    o->oVelY = GET_BPARAM1(o->oBehParams);
                }
            } else {
                o->oPosY = o->oHomeY;
                o->oVelY = 0;
                o->oTimer = 0;
                o->oAction = CRUSHER_STATE_IDLE;
            }
            break;
        }
    }

void bhv_turret_body_init(void){
    // Spawn the appropriate object based on the behavior parameter
    spawn_object_relative(GET_BPARAM2(o->oBehParams), 0, 0, 0, o, 
                          GET_BPARAM2(o->oBehParams) == 0 ? MODEL_TURRET_HEAD : MODEL_TURRET_HEAVY, 
                          bhvTurretHead);

    // Set the previous object to the nearest object with the specified behavior
    o->prevObj = cur_obj_nearest_object_with_behavior(bhvTurretHead);

    // Set the hitbox based on the parent object's face angle pitch
    obj_set_hitbox(o, o->parentObj->oFaceAnglePitch == 0x08000 || o->parentObj->oFaceAnglePitch == -0x08000 ? 
                   &sCeilingTurretHitbox : &sTurretHitbox);

    if (o->parentObj->oFaceAnglePitch != 0x08000 || o->parentObj->oFaceAnglePitch != -0x08000){
        o->oGravity = -4;
    }
    // Find the nearest object with the specified behavior and get the distance
    f32 dist;
    struct Object *turretPlatform = cur_obj_find_nearest_object_with_behavior(bhvTurretPlatform, &dist);

    // If the distance is less than 100.0f, set the parent object and behavior parameter accordingly
    if (dist < 100.0f){
        o->parentObj = turretPlatform;
        SET_BPARAM1(o->oBehParams, GET_BPARAM1(o->parentObj->oBehParams));
    } else {
        o->parentObj = NULL;
    }

    // Find the object with the specified behavior and parameter
    o->oObjF4 = find_object_with_behaviors_bparam(bhvTurretPanel, GET_BPARAM1(o->oBehParams), 1);
}


void bhv_turret_body_loop(void){
    cur_obj_move_standard(78);
    cur_obj_update_floor_and_walls();
    //print_text_fmt_int(20, 120, "base yaw %d", (u16)o->oMoveAngleYaw);
    //if (o->oDistanceToMario < 500){
        //print_text_fmt_int(20, 60, "bparam1 %d", GET_BPARAM1(o->oBehParams));
    //}
    if (o->parentObj == NULL){
        if  (o->oMoveFlags & OBJ_MOVE_LANDED){
            cur_obj_play_sound_1(SOUND_GENERAL_BOX_LANDING_UNUSED);
        }
    }
    if (o->parentObj != NULL){
        if (o->parentObj->o10C == 1){
            if (o->prevObj != NULL) {
                mark_obj_for_deletion(o->prevObj);
            }
            //mark_obj_for_deletion(o);
            obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
            return; // Exit the function since 'o' has been deleted
        }
        o->oPosY = o->parentObj->oPosY;
    }
    if (obj_hit_by_deflected_bullet(o, 750.0f) == 1){
        spawn_object_relative(0, 0, 0, 0, o, MODEL_EXPLOSION, bhvSafeExplosion);
        if (o->prevObj != NULL) {
            mark_obj_for_deletion(o->prevObj);
        }
        //mark_obj_for_deletion(o);
        obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
        return; // Exit the function since 'o' has been deleted
    }
    if (o->oObjF4 != NULL && o->oObjF4->oAction == 1){
        spawn_object_relative(0, 0, 0, 0, o, MODEL_EXPLOSION, bhvSafeExplosion);
        if (o->prevObj != NULL) {
            mark_obj_for_deletion(o->prevObj);
        }
        //mark_obj_for_deletion(o);
        obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
        return; // Exit the function since 'o' has been deleted
    }
    if (o->oInteractStatus & INT_STATUS_INTERACTED){
        if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED){
            if (o->oObjF4 != NULL) {
                o->oObjF4->oF4 -= 1;
            }
            spawn_mist_particles_with_sound(SOUND_GENERAL_EXPLOSION6);
            if (o->prevObj != NULL) {
                mark_obj_for_deletion(o->prevObj);
            }
            //mark_obj_for_deletion(o);
            obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
            return; // Exit the function since 'o' has been deleted
        } else {
            o->oInteractStatus = INT_STATUS_NONE;
        }
    }
    if (o->oShotByShotgun > 0){
        spawn_object_relative(0, 0, 0, 0, o, MODEL_EXPLOSION, bhvSafeExplosion);
        if (o->prevObj != NULL) {
            mark_obj_for_deletion(o->prevObj);
        }
        //mark_obj_for_deletion(o);
        obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
        return; // Exit the function since 'o' has been deleted
    }
}

enum turretAnim{
    ANIM_NONE,
    ANIM_SPINNING,
    ANIM_SPINUP,
    ANIM_SPINDOWN,
};

enum turretTurn{
    STATE_NONE,
    STATE_LEFT,
    STATE_RIGHT,
};
enum turretSpin{
    STATE_NOSPIN,
    STATE_SPINUP,
    STATE_SPINNING,
    STATE_SPINDOWN,
};

void bhv_turret_head_init(void){
    
    struct Object *turretBody = cur_obj_nearest_object_with_behavior(bhvTurretBody);

    o->parentObj = turretBody;
    if (o->parentObj->oFaceAnglePitch == 0x8000 || o->parentObj->oFaceAnglePitch == -0x8000){

        o->oFaceAnglePitch = o->oMoveAnglePitch;
        
    } else {
        o->oMoveAngleYaw = o->parentObj->oMoveAngleYaw;
        
    }
    o->oMoveAnglePitch = 0;
    o->oFaceAnglePitch = o->oMoveAnglePitch;
    o->oF8 = (u16)(o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw + 0x8000);
}

void bhv_turret_head_loop(void){
    o->oMoveAngleYaw = (u16)o->oMoveAngleYaw;
    //print_text_fmt_int(20, 80, "Relative Yaw: %d", (u16)(o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw));
    //print_text_fmt_int(20, 100, "Raw Yaw: %d", (o->oMoveAngleYaw));
    //print_text_fmt_int(200, 120, "%d", (u16)(o->parentObj->oMoveAngleYaw));
    //print_text_fmt_int(20, 140, "Relative 180yaw: %d", (o->oF8));
    //print_text_fmt_int(20, 160, "180yaw: %d", (o->parentObj->oMoveAngleYaw + 0x8000));
    Vec3f d;
    d[0] = gMarioState->pos[0] - o->oPosX;
    d[1] = -gMarioState->pos[1] + o->oPosY;
    d[2] = gMarioState->pos[2] - o->oPosZ;
    o->oF4 = atan2s(sqrtf(sqr(d[0]) + sqr(d[2])), d[1]);
    o->oPosX = o->parentObj->oPosX;
    if (o->parentObj->oFaceAnglePitch == 0x08000 || o->parentObj->oFaceAnglePitch == -0x08000){
        o->oPosY = o->parentObj->oPosY - 181;
    } else {
        o->oPosY = o->parentObj->oPosY + 181;
    }
    o->oPosZ = o->parentObj->oPosZ;
    o->oFaceAnglePitch = o->oMoveAnglePitch;
    //o->oMoveAngleYaw = o->parentObj->oMoveAngleYaw;
    
    /*
    if (o->oMoveAngleYaw < -32768){
    o->oMoveAngleYaw = o->oMoveAngleYaw + 65536;
} else if (o->oMoveAngleYaw >= 32768){
    o->oMoveAngleYaw = o->oMoveAngleYaw - 65536;
    
}
*/
/*
if (abs_angle_diff(o->oFaceAngleYaw, (o->parentObj->oMoveAngleYaw)) <= DEGREES(135)){
    print_text(20, 20, "should go right");
} else {
    print_text(20, 20, "should go left");
}
*/
/*
print_text_fmt_int(20, 180, "diff: %d", abs_angle_diff((o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw), (o->oF8)));
print_text_fmt_int(20, 200, "diff2: %d", abs_angle_diff((o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw), (o->oF8 - 0x8000 + 0x2000)));
print_text_fmt_int(20, 220, "diff3: %d", abs_angle_diff(((u16)o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw), ((u16)o->oF8 - 0x8000 + 0xE000)));

    if ((abs_angle_diff(o->oF8 + DEGREES(45) , o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw)) >= (abs_angle_diff(o->oF8 + DEGREES(315) , o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw))){
        print_text(20, 20, "should go right");
    } else {
        print_text(20, 20, "should go left");
    }
    */

    struct Surface *surf;
    /*
    if (gPlayer1Controller->buttonPressed & D_CBUTTONS){
            dobj_spawn_bullet((&o->oPosVec), -o->oFaceAnglePitch, o->oMoveAngleYaw);
            play_sound(SOUND_OBJ_SNUFIT_SHOOT, gGlobalSoundSource);
        }
        */
    Vec3f orig = { o->oPosX, o->oPosY, o->oPosZ }; 
    Vec3f marioPos = { gMarioState->pos[0], gMarioState->pos[1], gMarioState->pos[2] };
    Vec3f hitPos, dir = { (marioPos[0] - orig[0]), (marioPos[1]+10 - orig[1]), (marioPos[2] - orig[2]) };
    find_surface_on_ray(orig, dir, &surf, hitPos, (RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL | RAYCAST_FIND_WALL));
    if (o->oDistanceToMario < 3000.0f && !surf && gMarioState->health != 0xFF && phasewalk_state == 0 && o->oF4 < 0x1800){
        obj_turn_pitch_toward_mario(120.0f, 0x200);
        if (o->oMoveAnglePitch < -0x1200){
            o->oMoveAnglePitch = -0x1200;
        } else if (o->oMoveAnglePitch > 0x1200){
            o->oMoveAnglePitch = 0x1200;
        }
        cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x200);
        if (GET_BPARAM2(o->oBehParams) == 1){
            switch (o->oAction){
                case STATE_NOSPIN:
                    o->oAction = STATE_SPINUP;
                    break;
                case STATE_SPINDOWN:
                    o->oAction = STATE_SPINUP;
                    break;
                case STATE_SPINUP:
                    cur_obj_init_animation(ANIM_SPINUP);
                    if (cur_obj_check_if_at_animation_end()){
                        o->oAction = STATE_SPINNING;
                    }
                    break;
                case STATE_SPINNING:
                    cur_obj_init_animation(ANIM_SPINNING);
                    if (cur_obj_check_anim_frame(1)){
                        o->oTimer = 1;
                    }
                    
                    if (o->oTimer == 1){
                        if (abs_angle_diff(o->oFaceAngleYaw, o->oAngleToMario) < 0x500 ){
                            dobj_spawn_bullet((&o->oPosVec), -o->oFaceAnglePitch, o->oFaceAngleYaw);
                            play_sound(SOUND_OBJ_SNUFIT_SHOOT, gGlobalSoundSource);
                        }
                    }
                    break;
                } 
                
        } else if (o->oTimer > 40 && abs_angle_diff(o->oFaceAngleYaw, o->oAngleToMario) < 0x500){
            dobj_spawn_bullet((&o->oPosVec), -o->oFaceAnglePitch, o->oFaceAngleYaw);
            play_sound(SOUND_OBJ_SNUFIT_SHOOT, gGlobalSoundSource);
            o->oTimer = 0;
            
        }
        
        o->oSubAction = STATE_NONE;
    } else {
        o->oTimer = 20;
        if (GET_BPARAM2(o->oBehParams) == 1){
            switch (o->oAction){
                case STATE_SPINUP:
                    o->oAction = STATE_SPINDOWN;
                    break;
                case STATE_SPINNING:
                    o->oAction = STATE_SPINDOWN;
                    break;
                case STATE_SPINDOWN:
                    cur_obj_init_animation(ANIM_SPINDOWN);
                    if (cur_obj_check_if_at_animation_end()){
                        o->oAction = STATE_NOSPIN;
                    }
                    break;
                case STATE_NOSPIN:
                    cur_obj_init_animation(ANIM_NONE);
                    break;
            }
        }
        //char hex_str[10];
        //sprintf(hex_str, "%08X", o->oMoveAngleYaw);
        //print_text(20, 80, hex_str);
        
        switch (o->oSubAction){
            case STATE_NONE:
            
    //print_text(20, 20, "STATE_NONE");
    //if (o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw < o->oF8){
    //if (o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw > o->parentObj->oMoveAngleYaw + 0x12000){
        //print_text(20, 40, "should go right");
        //o->oSubAction = STATE_LEFT;
        //o->oMoveAngleYaw += 75;
        
    //} //else if (o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw > o->parentObj->oMoveAngleYaw - 0x8000){
        //print_text(20, 40, "should go left");
        //o->oSubAction = STATE_RIGHT;
    //}

            // Normalize the difference to be between -32768 and 32767
            // o->o100: state_right ending yaw, o->o104: state_left ending yaw
/*
                if ((u16)(o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw) >= o->oF8 ||
    (u16)(o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw + 0x8000) >= (o->oF8 + 0x8000)) {
    // Check if the current angle is greater than or equal to 180 degrees
    o->oSubAction = STATE_RIGHT; // Turn right
} else {
    // The current angle is less than 180 degrees
    o->oSubAction = STATE_LEFT; // Turn left
}
*/

    if ((abs_angle_diff(o->oF8 + DEGREES(45) , o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw)) >= (abs_angle_diff(o->oF8 + DEGREES(315) , o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw))){
        o->oSubAction = STATE_LEFT;
    } else {
        o->oSubAction = STATE_RIGHT;
    }


            
    break;
            case STATE_LEFT:
                //print_text(20, 40, "STATE_LEFT");
                o->oMoveAngleYaw-= 75;
                //o->oMoveAngleYaw = approach_s32_symmetric(o->oMoveAngleYaw, o->parentObj->oMoveAngleYaw - 0x2000, 0x75);
                //print_text_fmt_int(20, 20, "goal yaw: %d", (u16)(o->parentObj->oMoveAngleYaw - 0x2000));
                //if ((o->oMoveAngleYaw - (o->parentObj->oMoveAngleYaw - 0x2000)) & 0x8000){
                    //if (abs(o->oMoveAngleYaw - (o->parentObj->oMoveAngleYaw - 0x2000) & 0x8000) <= 0x75) {
                    //if (o->oMoveAngleYaw <= o->parentObj->oMoveAngleYaw - 0x2000 || o->oMoveAngleYaw >= o->parentObj->oMoveAngleYaw + 0xE000){
                        //if ((o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw >= (u16)(o->parentObj->oMoveAngleYaw - 0x2000 - 0x75)) && (o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw <= (u16)(o->parentObj->oMoveAngleYaw - 0x2000 + 0x75))) {
                        if (abs_angle_diff((o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw), (o->oF8 - 0x8000 + 0xE000)) <= 0x75) {
                        //print_text(20, 0, "within range");
                        o->oSubAction = STATE_RIGHT;
                        }
                    //o->oSubAction = STATE_RIGHT;
                //}
                break;
            case STATE_RIGHT:
                //print_text(20, 60, "STATE_RIGHT");
                o->oMoveAngleYaw+= 75;
                //o->oMoveAngleYaw = approach_s32_symmetric(o->oMoveAngleYaw, o->parentObj->oMoveAngleYaw + 0x2000, 0x75);
                //print_text_fmt_int(20, 20, "goal yaw: %d", (u16)(o->parentObj->oMoveAngleYaw + 0x2000));
                //if ((o->oMoveAngleYaw - (o->parentObj->oMoveAngleYaw + 0x2000)) & 0x8000){
                    //if (abs(o->oMoveAngleYaw - (o->parentObj->oMoveAngleYaw + 0x2000) & 0x8000) <= 0x75) {
                    //if (o->oMoveAngleYaw >= o->parentObj->oMoveAngleYaw + 0x2000 || o->oMoveAngleYaw <= o->parentObj->oMoveAngleYaw - 0xE000){
                    //o->oSubAction = STATE_LEFT;
                //}
                //if ((o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw >= (u16)(o->parentObj->oMoveAngleYaw + 0x2000 - 0x76)) && (o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw <= (u16)(o->parentObj->oMoveAngleYaw + 0x2000 + 0x76))) {
                    if (abs_angle_diff((o->parentObj->oMoveAngleYaw + o->oMoveAngleYaw), (o->oF8 - 0x8000 + 0x2000)) <= 0x75) {
                        //print_text(20, 0, "within range");
                        o->oSubAction = STATE_LEFT;
                        }
                break;
        }
        
        if (o->oMoveAnglePitch != 0){
            o->oMoveAnglePitch = approach_s32_symmetric(o->oMoveAnglePitch, 0, 0x100);
        }
        if (o->oTimer > 100){
            o->oTimer = 0;
        }
    }
    //dobj_spawn_bullet(o->oPosVec, o->oMoveAnglePitch, o->oMoveAngleYaw);
}
/*
* bparams:
* 1: control panel number
* 2: 0 = normal, 1 = heavy
* 3: floor number
*/
void bhv_turret_platform_init(void){
    if (GET_BPARAM1(o->oBehParams) != 0){
        o->oObj100 = find_object_with_behaviors_bparam(bhvTurretPanel, GET_BPARAM1(o->oBehParams), 1);
    }
    if (o->oObj100 == NULL){
        SET_BPARAM1(o->oBehParams, 0);
    }
    o->oHomeY = o->oPosY;
    struct Object *coverLeft = spawn_object_abs_with_rot(o, 0, MODEL_TURRET_COVER, bhvTurretCover, -107*sins(o->oMoveAngleYaw-0x4000)+o->oPosX, o->oPosY+235, -107*coss(o->oMoveAngleYaw-0x4000)+o->oPosZ, 0, o->oMoveAngleYaw-0x4000, 0);
    struct Object *coverRight = spawn_object_abs_with_rot(o, 0, MODEL_TURRET_COVER, bhvTurretCover, -107*sins(o->oMoveAngleYaw+0x4000)+o->oPosX, o->oPosY+235, -107*coss(o->oMoveAngleYaw+0x4000)+o->oPosZ, 0, o->oMoveAngleYaw+0x4000, 0);
    o->oObjF4 = coverLeft;
    o->oObjF8 = coverRight;
    o->o110 = 0;
    //o110 states:
    // 0: not activated
    // 1: spawns turret, oAction handles movement
}

void bhv_turret_platform(void){
    if (GET_BPARAM1(o->oBehParams) == 1){
        if (curCutsceneState == 5 && o->o110 == 0){
            o->oAction = 1;
            o->o110 = 1;
            o->oObjF4->oAction = 1;
            o->oObjF8->oAction = 1;
        }
    } if (GET_BPARAM3(o->oBehParams) == 0){
        if (o->oDistanceToMario < 750 && o->o110 == 0){
            o->oAction = 1;
            o->o110 = 1;
            o->oObjF4->oAction = 1;
            o->oObjF8->oAction = 1;
        }
    } else if (gMarioState->floor->type == SURFACE_TURRET_ACTIVATOR){
        if (GET_BPARAM3(o->oBehParams) == gMarioState->floor->force && o->o110 == 0){
            o->oAction = 1;
            o->o110 = 1;
            o->oObjF4->oAction = 1;
            o->oObjF8->oAction = 1;
        }
        //print_text_fmt_int(20,20, "floor force: %d", gMarioState->floor->force);
    } if (GET_BPARAM1(o->oBehParams) != 0){
        if (o->oObj100->oAction == 1){
            if (o->o110 == 0){
                mark_obj_for_deletion(o);
            } else {
                o->o10C = 1;
            }
        }
    }
    /*
    if (o->oDistanceToMario < 750 && o->oAction == 0){
        o->oAction = 1;
        o->o110 = 1;
        o->oObjF4->oAction = 1;
        o->oObjF8->oAction = 1;
    }
    */
    if (o->o110 == 1){
        struct Object *turret = spawn_object_relative(GET_BPARAM2(o->oBehParams), 0, 0, 0, o, MODEL_TURRET_BODY, bhvTurretBody);
        o->oObjFC = turret;
        o->oObjFC->oMoveAngleYaw = o->oMoveAngleYaw;
        o->oObjFC->oMoveAnglePitch = o->oMoveAnglePitch;
        o->o110 = 2;
    }
    switch (o->oAction){
        case 0:
            o->oTimer = 0;
            break;
        case 1:
            if (o->oTimer >= 10){
                o->oAction = 2;
            }
            break;
        case 2:
            if (o->oFaceAnglePitch == 0x08000 || o->oFaceAnglePitch == -0x08000){
                if (o->oPosY > o->oHomeY - 262.617f){
                    play_sound(SOUND_ENV_ELEVATOR4, &o->oPosVec);
                    o->oPosY -= 7.5;
                } else {
                    o->oPosY = o->oHomeY - 262.617f;
                    o->oAction = 3;
                    play_sound(SOUND_ENV_METAL_BOX_PUSH, &o->oPosVec);
                }
            } else {
                if (o->oPosY < o->oHomeY + 262.617f){
                    play_sound(SOUND_ENV_ELEVATOR4, &o->oPosVec);
                    o->oPosY += 7.5;
                } else {
                    o->oPosY = o->oHomeY + 262.617f;
                    o->oAction = 3;
                    play_sound(SOUND_ENV_METAL_BOX_PUSH, &o->oPosVec);
                    
                }
            }
        break;
    }
}

void bhv_turret_cover_init(void){
    o->parentObj = cur_obj_nearest_object_with_behavior(bhvTurretPlatform);
    if (o->parentObj->oFaceAnglePitch == 0x08000 || o->parentObj->oFaceAnglePitch == -0x08000){
        o->oMoveAnglePitch = 0x08000;
        o->oFaceAnglePitch = o->oMoveAnglePitch;
        o->oFaceAngleYaw = o->oFaceAngleYaw+0x8000;
        o->oPosY = o->parentObj->oPosY - 262.617f;
    }
}

void bhv_turret_cover(void){
    //print_text_fmt_int(20, 20, "oTimer: %d", o->oTimer);
    cur_obj_move_standard(-78);
    if (o->oAction == 1){
        o->oPosX -= 7.5*sins(o->oMoveAngleYaw);
        o->oPosZ -= 7.5*coss(o->oMoveAngleYaw); 
    } else {
        o->oTimer = 0;
    }
    if (o->oTimer == 23){
        mark_obj_for_deletion(o);
    }
}


void bhv_turret_panel_init(void){
    o->oF4 = GET_BPARAM2(o->oBehParams);
    obj_set_hitbox(o, &sTurretPanelHitbox);
}

void bhv_turret_panel(void){
    //print_text_fmt_int(20, 60 + (20*GET_BPARAM2(o->oBehParams)), "oF4: %d", o->oF4);
    if(o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED){
        //print_text(20, 40, "Button Pressed");
        //o->oInteractStatus = INT_STATUS_NONE;
        o->oAction = 1;
        obj_mark_for_deletion(o);
    }
    if (o->oF4 == 0){
        o->oAction = 1;
        obj_mark_for_deletion(o);
    }
}

void bhv_gate_init(void){
    if (GET_BPARAM1(o->oBehParams) != 0){
        o->oObjF4 = find_object_with_behaviors_bparam(bhvTurretPanel, GET_BPARAM1(o->oBehParams), 1);
    }
}
void bhv_gate(void){
    if (GET_BPARAM1(o->oBehParams) == 0){
        if (curCutsceneState == 4){
            cutsceneFocus[1] = o->oPosY;
            if (o->oPosY > o->oHomeY - 455.9f){
                o->oPosY -= 7.5;
                play_sound(SOUND_ENV_ELEVATOR2, &o->oPosVec);
            } else {
                o->oPosY = o->oHomeY - 455.9f;
                play_sound(SOUND_OBJ_BOWSER_WALK, &o->oPosVec);
                curCutsceneState = 5;
            }
        }
    } else if (GET_BPARAM1(o->oBehParams) != 0){
        if (o->oObjF4->oAction == 1){
            o->oAction = 1;
        }
        //print_text_fmt_int(20, 20, "oAction: %d", o->oAction);
    }
    if (o->oAction == 1){
        if (o->oPosY < o->oHomeY + 455.9f){
            o->oPosY += 7.5;
            play_sound(SOUND_ENV_ELEVATOR2, &o->oPosVec);
        } else {
            o->oPosY = o->oHomeY + 455.9f;
            o->oAction = 2;
        }
    }
}

void bhv_alarm(void){
    if (curCutsceneState == 3){
        cur_obj_set_model(MODEL_ALARM_LIT);
        o->oAction = 1;
    } else if (curCutsceneState == 0){
        o->oAction = 0;
    }
    if (o->oAction == 1){
        if (o->oTimer > 15){
            cur_obj_play_sound_2(SOUND_GENERAL_COIN_DROP);
            o->oTimer = 0;
        }
    }

}

/*
void b_cutscene_handler(){
    if (inCutscene == TRUE){
        gMarioState->controller = &gControllers[5];
        print_text_fmt_int(20, 20, "Cutscene State: %d", curCutsceneState);
        if (curCutsceneState == 0){
            curCutsceneState = 1;
        }
    } else {
        gMarioState->controller = &gControllers[0];
    }
    
    if (frames > 0){
        if (o->oTimer >= frames){
            o->oTimer = 0;
            curCutsceneState = nextState;
        }
    } else {
        curCutsceneState = nextState;
    }
    
}
*/


/*
void bhv_turret_heavy_loop(void){
o->oFaceAnglePitch = o->oMoveAnglePitch;
    o->oFaceAngleYaw = o->oMoveAngleYaw;
    struct Surface *surf;
    Vec3f orig = { o->oPosX, o->oPosY, o->oPosZ }; 
    Vec3f marioPos = { gMarioState->pos[0], gMarioState->pos[1], gMarioState->pos[2] };
    Vec3f hitPos, dir = { (marioPos[0] - orig[0]), (marioPos[1]+100 - orig[1]), (marioPos[2] - orig[2]) };
    find_surface_on_ray(orig, dir, &surf, hitPos, (RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL | RAYCAST_FIND_WALL));
    if (o->oDistanceToMario < 3000.0f && !surf){
        o->oSubAction = STATE_NONE;
        obj_turn_pitch_toward_mario(120.0f, 0x200);
        cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x200);
        if (o->oTimer > 40 && abs_angle_diff(o->oFaceAngleYaw, o->oAngleToMario) < 0x500){
            cur_obj_init_animation(0);
        dobj_spawn_bullet((&o->oPosVec), -o->oFaceAnglePitch, o->oFaceAngleYaw);
        play_sound(SOUND_OBJ_SNUFIT_SHOOT, gGlobalSoundSource);
        o->oTimer = 0;
        }
    } else {
        cur_obj_init_animation(1);
        o->oTimer = 20;
        switch (o->oSubAction){
            case STATE_NONE:
                if (o->oSubAction == STATE_NONE){
                    if (o->oMoveAngleYaw > 0){
                        o->oSubAction = STATE_RIGHT;
                    } else {
                        o->oSubAction = STATE_LEFT;
                    }
                }
            case STATE_LEFT:
                o->oMoveAngleYaw = approach_s32_symmetric(o->oMoveAngleYaw, -0x2000 + o->parentObj->oMoveAngleYaw, 0x75);
                if (o->oMoveAngleYaw == -0x2000 + o->parentObj->oMoveAngleYaw){
                    o->oSubAction = STATE_RIGHT;
                }
                break;
            case STATE_RIGHT:
                o->oMoveAngleYaw = approach_s32_symmetric(o->oMoveAngleYaw, 0x2000 + o->parentObj->oMoveAngleYaw, 0x75);
                if (o->oMoveAngleYaw == 0x2000 + o->parentObj->oMoveAngleYaw){
                    o->oSubAction = STATE_LEFT;
                }
                break;
        }
        
        if (o->oMoveAnglePitch != 0){
        o->oMoveAnglePitch = approach_s32_symmetric(o->oMoveAnglePitch, 0, 0x100);
        }
        
        if (o->oTimer > 100){
            o->oTimer = 0;
        }
        
    }
}
*/

u8 waterTempleState = 0;
void bhv_cork_init(void){
    o->parentObj = cur_obj_nearest_object_with_behavior(bhvWaterTemple);
    o->oHomeY = o->oPosY;
}

void bhv_cork(void){
    if (cur_obj_was_attacked_or_ground_pounded()) {
        waterTempleState = GET_BPARAM2(o->oBehParams);
        obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
        create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
        if (GET_BPARAM1(o->oBehParams) == 1){
            gLakituState.goalPos[1] = gLakituState.goalPos[1] - 3000;
            gLakituState.goalFocus[1] = gLakituState.goalFocus[1] - 3000;
        }

        
    }
}

void bhv_watertemple_init(void){
    waterTempleState = 0;
    airlockState = AIRLOCK_STATE_WET;
}

void bhv_watertemple(void){
    //cur_obj_update_floor_and_walls();
    //print_text_fmt_int(20, 20, "waterTempleState: %d", waterTempleState);
    switch (waterTempleState) {
        case 0:
            o->oHomeY = 152;
            break;
        case 1:
            o->oHomeY = -641; //placeholder
            break;
        case 2:
            o->oHomeY = -2731; //placeholder
            break;
        case 3:
            o->oHomeY = -6900; //placeholder
            break;
    }
    if (o->oHomeY != o->oPosY){
        approach_f32_symmetric_bool(&o->oPosY, o->oHomeY, 10);
        cur_obj_play_sound_1(SOUND_ENV_WATERFALL2);
    } else if (o->oHomeY > o->oPosY){
        o->oPosY = o->oHomeY;
    }
    if (gMarioState->floor->type == SURFACE_SQUID_INK){ 
        gLakituState.goalPos[1] = gMarioState->pos[1] + 300;
        gLakituState.goalFocus[1] = gMarioState->pos[1] + 300;
    }
}
void bhv_boss_daddy_init(void){
    o->oHomeX = -10130;
    o->oHomeY = 746;
    o->oHomeZ = -927;
    o->oFaceAngleYaw = 0x4000;
    o->oMoveAngleYaw = o->oFaceAngleYaw;
    obj_set_hitbox(o, &sBigDaddyHitbox);
    o->oHealth = 3;
    o->oInteractType = INTERACT_TEXT;
    o->oInteractionSubtype = INT_SUBTYPE_NPC;
    cur_obj_boss_shimmer_reset();
}

// for use with o->oF4
enum bigDaddyBossStates{
    STATE_INTRO,
    STATE_IDLE,
    STATE_JUMP_UP,
    STATE_JUMP_DOWN,
    STATE_JUMP_AROUND,
    STATE_KNOCKED_BACK,
    STATE_RUNNING,
    STATE_ATTACK,
    STATE_VULNERABLE,
    STATE_DEATH_DIALOG,
    STATE_SPAWN_STAR,
    STATE_LAUGH,
    STATE_SQUISHED,
    STATE_GETUP,
    STATE_SKID,
    STATE_STOMP,
    STATE_RESTART,
    STATE_SPAWN_TURRETS,
};
// o->oF8 is what quadrant mario was last in
    s32 TruncForwardVel;
u8 course_6_boss_reset = FALSE;
void bhv_boss_daddy(void){
    //if (cur_obj_is_mario_in_room() == MARIO_OUTSIDE_ROOM || gMarioState->action == ACT_DEATH_EXIT_LAND){
    //    print_text(20, 80, "Mario pls come back");
    //    o->oF4 = STATE_RESTART;
    //}
    f32 dist;
    //print_text_fmt_int(20, 60, "oHealth: %d", o->oHealth);
    //print_text_fmt_int(20, 20, "oAction: %d", o->oAction);
    //print_text_fmt_int(20, 40, "oF4: %d", o->oF4);
    s32 TruncForwardVel = o->oForwardVel;
    //print_text_fmt_int(20, 40, "oForwardVel: %d", TruncForwardVel);
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(-78);
    if (gMarioState->floor->type == SURFACE_B_BOSS_QUADRANT){
        o->oF8 = gMarioState->floor->force;
    }
    //cur_obj_move_using_fvel_and_gravity();
    //if (gPlayer1Controller->buttonPressed & L_TRIG){
        //gMarioState->health = 0xFF;
        //o->oF4 = STATE_STOMP;
        //spawn_object_abs_with_rot(o, 0, MODEL_TURRET_BODY, bhvTurretBody, -10130, 500, -2072, 0, 0, 0);
        //o->oPosX = o->oHomeX;
        //o->oPosY = o->oHomeY;
        //o->oPosZ = o->oHomeZ;
        //o->oAction = 1;
        //o->oTimer = 0;
    //}
    if (course_6_boss_reset) {
        course_6_boss_reset = FALSE;
        o->oF4 = STATE_RESTART;
    }

    switch (o->oF4) {
        case STATE_KNOCKED_BACK:
            o->oInteractType = INTERACT_NONE;
            o->oInteractStatus = 0;
            switch (o->oAction){
                case 1:
                    cur_obj_init_animation(1);
                    o->oVelY = 40;
                    o->oForwardVel -= 50;
                    o->oAction = 2;
                    break;
                case 2:
                    if  (o->oMoveFlags & OBJ_MOVE_LANDED){
                    spawn_mist_particles_with_sound(SOUND_OBJ_POUNDING_LOUD);
                    cur_obj_shake_screen(SHAKE_POS_SMALL);
                    o->oVelY = 20;
                    o->oForwardVel = -15;
                    o->oAction = 3;
                    }
                    break;
                case 3:
                    if  (o->oMoveFlags & OBJ_MOVE_LANDED){
                    cur_obj_shake_screen(SHAKE_POS_SMALL);
                    spawn_mist_particles_with_sound(SOUND_OBJ_POUNDING_LOUD);
                    o->oForwardVel = 0;
                    o->oAction = 1;
                    o->oF4 = STATE_VULNERABLE;
                    }
                    break;
            }
            break;
        case STATE_VULNERABLE:
            if (o->oTimer >= 120){
                o->oF4 = STATE_GETUP;
            }
            sBigDaddyHitbox.radius = 250;
            sBigDaddyHitbox.height = 261;
            obj_set_hitbox(o, &sBigDaddyHitbox);
            o->oInteractType = INTERACT_BOUNCE_TOP;
            o->oDamageOrCoinValue = 0;
            cur_obj_init_animation(3);
            if (o->oInteractStatus & INT_STATUS_TOUCHED_MARIO && (gMarioState->action & ACT_GROUP_MASK) == ACT_GROUP_AIRBORNE){
                o->oF4 = STATE_SQUISHED;
                o->oAction = 1;
            } else if (o->oInteractStatus & INT_STATUS_INTERACTED){
                o->oInteractStatus = 0;
            }
            break;
        case STATE_GETUP:
            o->oInteractType = INTERACT_NONE;
            o->oDamageOrCoinValue = 1;
            sBigDaddyHitbox.radius = 170;
            sBigDaddyHitbox.height = 420;
            obj_set_hitbox(o, &sBigDaddyHitbox);
            cur_obj_init_animation(7);
            if (cur_obj_check_if_at_animation_end()){
                o->oF4 = STATE_STOMP;
                o->oAction = 1;
            }
            break;
        case STATE_SQUISHED:
            switch (o->oAction){
                case 1:
                    o->oHealth -= 1;
                    o->oTimer = 0;
                    o->oAction = 2;
                    break;
                case 2:
                    obj_scale_xyz(o, 1.0, (1-(.16*o->oTimer)), 1.0);
                    if (o->oTimer >= 5){
                        o->oAction = 3;
                        o->oTimer = 0;
                    }
                    break;
                case 3:
                    obj_scale_xyz(o, 1.0, (.2+(.16*o->oTimer)), 1.0);
                    if (o->oTimer >= 5){
                        o->oAction = 4;
                        o->oTimer = 0;
                    }
                    break;
                case 4:
                    obj_scale_xyz(o, 1.0, 1.0, 1.0);
                    o->oInteractStatus = 0;
                    //o->oF4 = STATE_VULNERABLE;
                    if (o->oHealth != 0){
                    o->oF4 = STATE_GETUP;
                    } else {
                        o->oF4 = STATE_DEATH_DIALOG;
                    }
            }
            break;
        case STATE_RUNNING:
            o->oInteractType = INTERACT_DAMAGE;
            //print_text_fmt_int(20, 60, "oDistanceToMario: %d", o->oDistanceToMario);
            cur_obj_init_animation(4);
            cur_obj_unused_play_footstep_sound(1, 15, SOUND_OBJ_POUNDING_LOUD);
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 1792 / (o->oForwardVel / 8));
            if (o->oForwardVel < 64){
                o->oForwardVel += 2;
            }
            if (o->oInteractStatus & INT_STATUS_ATTACKED_MARIO){
                o->oF4 = STATE_SKID;
                o->oFC = 0;
                o->oAction = 1;
                o->oTimer = 0;
            }
            
            if (cur_obj_find_nearest_object_with_behavior(bhvTurretBody, &dist)){
                if (dist < 250){
                    o->oObjFC = cur_obj_find_nearest_object_with_behavior(bhvTurretBody, &dist);
                    mark_obj_for_deletion(o->oObjFC->prevObj);
                    mark_obj_for_deletion(o->oObjFC);
                    spawn_object_relative(0, 0, 0, 0, o, MODEL_EXPLOSION, bhvSafeExplosion);
                    obj_spawn_loot_yellow_coins(o, o->oNumLootCoins, 20.0f);
                    o->oObjFC = NULL;
                }
            }
            if (o->oHealth < 3){
                if (cur_obj_find_nearest_object_with_behavior(bhvTurretBody, &dist) == NULL || dist > 3000){
                    o->oF4 = STATE_SKID;
                    o->oAction = 1;
                    o->o104 = 1; //o100 being used to show STATE_SKID to spawn turrets
                
                }
            }
            
            //obj_spawn_loot_yellow_coins(o, o->oNumLootCoins, 20.0f);
            if ((abs_angle_diff(o->oWallAngle, o->oFaceAngleYaw) >= 24576) && (o->oMoveFlags & OBJ_MOVE_HIT_WALL)){
                if (o->oHealth == 1){
                    o->oFC += 1;
                    if (o->oFC < 5){
                    cur_obj_if_hit_wall_bounce_away();
                    cur_obj_play_sound_1(SOUND_OBJ_WATER_BOMB_BOUNCING);
                    } else if (o->oFC >= 5 ){
                        o->oF4 = STATE_KNOCKED_BACK;
                        o->oAction = 1;
                    }
                } else if (o->oHealth > 1){
                o->oF4 = STATE_KNOCKED_BACK;
                o->oAction = 1;
                }
            }
            o->oInteractStatus = 0;
                break;
        case STATE_IDLE:
            cur_obj_init_animation(0);
            o->oInteractStatus = 0;
            if (cur_obj_find_nearest_object_with_behavior(bhvTurretBody, &dist) == NULL || dist > 3000){
                o->oF4 = STATE_JUMP_DOWN;
            }
            break;
        case STATE_SKID:
            o->oInteractType = INTERACT_NONE;
            o->oInteractStatus = 0;
            cur_obj_init_animation(9);
            if (o->oForwardVel > 0){
                cur_obj_play_sound_1(SOUND_MOVING_TERRAIN_SLIDE);
                if (o->oTimer % 2){
                    spawn_object_relative(0, 0, 0, 0, o, MODEL_SMOKE, bhvSmoke);
                }
                o->oForwardVel -= .20;
            } else {
                if (o->o104 == 0){
                    o->oForwardVel = 0;
                    o->oF4 = STATE_LAUGH;
                } else {
                    o->oF4 = STATE_STOMP;
                    o->oForwardVel = 0;
                }
            }
            break;
        case STATE_LAUGH:
            switch (o->oAction){
                case 1:
                    o->oInteractStatus = 0;
                    cur_obj_init_animation(5);
                    play_sound(SOUND_OBJ_BOWSER_LAUGH, gGlobalSoundSource);
                    o->oAction = 2;
                        break;
                case 2:
                    cur_obj_rotate_yaw_toward(o->oAngleToMario, 1000);
                    if (cur_obj_check_anim_frame(38)){
                    stop_sound(SOUND_OBJ_BOWSER_LAUGH, gGlobalSoundSource);
                    }
                    if (cur_obj_check_if_at_animation_end()){
                        o->oF4 = STATE_RUNNING;
                        o->oAction = 1;
                    }
                    break;
                }
            break;
        case STATE_SPAWN_TURRETS:
            switch (o->oAction){
                case 1:
                    cur_obj_init_animation(0);
                    if (cur_obj_find_nearest_object_with_behavior(bhvTurretBody, &dist) == NULL || dist > 3000){
                        spawn_object_abs_with_rot(o, 0, MODEL_TURRET_BODY, bhvTurretBody, -8978, 1000, -927, 0, 0x4000, 0);
                        spawn_object_abs_with_rot(o, 0, MODEL_TURRET_BODY, bhvTurretBody, -10130, 1000, -2072, 0, 0x8000, 0);
                        spawn_object_abs_with_rot(o, 0, MODEL_TURRET_BODY, bhvTurretBody, -11281, 1000, -927, 0, 0xC000, 0); 
                        spawn_object_abs_with_rot(o, 0, MODEL_TURRET_BODY, bhvTurretBody, -10130, 1000, 223, 0, 0, 0);
                    }
                    o->oAction = 2;
                    o->oTimer = 0;
                    break;
                case 2:
                    cur_obj_rotate_yaw_toward(o->oAngleToMario, 1000);
                    if (o->oTimer >= 90){
                        o->oObjF8 = NULL; 
                        if (o->oHealth == 3){
                            if (o->oPosY >= 740){
                                o->oF4 = STATE_IDLE;
                                o->oAction = 1;
                            } else {
                                o->oF4 = STATE_JUMP_UP;
                                o->oAction = 1;
                            }
                        } else if (o->oHealth == 2){
                            o->oAction = 1;
                            o->oF4 = STATE_RUNNING;
                        } else if (o->oHealth == 1){
                            if (find_object_with_behaviors_bparam(bhvTurretPlatform, 10, 3) != NULL){
                                o->oObjF8 = find_object_with_behaviors_bparam(bhvTurretPlatform, 10, 3);
                                SET_BPARAM2(o->oObjF8->oBehParams, 1);
                                SET_BPARAM3(o->oObjF8->oBehParams, 0);
                                o->oObjF8->oDistanceToMario = 0;
                                o->oObjF8 = NULL;
                            }
                            o->oAction = 1;
                            if (o->o104 == 0){
                            o->oF4 = STATE_JUMP_AROUND;
                            } else {
                                o->oF4 = STATE_RUNNING;
                            
                            }
                        }
                    }
                    break;
            }
            break;
        case STATE_JUMP_UP:
            o->oHomeX = -10130;
            o->oHomeY = 746;
            o->oHomeZ = -927;
            switch (o->oAction){
                case 1:
                    o->oAngleToHome = cur_obj_angle_to_home();
                    cur_obj_rotate_yaw_toward(o->oAngleToHome, 1792);
                    //o->oMoveAngleYaw = o->oFaceAngleYaw;
                    if (o->oFaceAngleYaw == o->oAngleToHome){
                        o->oAction = 2;
                    }
                    break;
                case 2:
                    cur_obj_init_animation(6);
                    if (cur_obj_check_anim_frame(13)){
                        cur_obj_play_sound_1(SOUND_OBJ_KING_BOBOMB_JUMP);
                        o->oAction = 3;
                        o->oVelY = 70;
                    }
                    break;
                case 3:
                    if (o->oAction == 3){
                        approach_vec3f_asymptotic(&o->oPosVec, &o->oHomeVec, 0.08, 0.1, 0.08);
                        if (o->oMoveFlags & OBJ_MOVE_LANDED){
                            o->oAction = 4;
                        }
                    }
                    break;
                case 4:
                    cur_obj_init_animation(8);
                    cur_obj_play_sound_1(SOUND_OBJ_POUNDING_LOUD);
                    cur_obj_shake_screen(SHAKE_POS_SMALL);
                    play_sound(SOUND_OBJ_MONTY_MOLE_ATTACK, gGlobalSoundSource);
                    o->oTimer = 0;
                    o->oAction = 5;
                    break;
                case 5:
                    if (cur_obj_check_if_at_animation_end()){
                        o->oF4 = STATE_SPAWN_TURRETS;
                        o->oAction = 1;
                    }
                    break;
            }
            break;
        case STATE_JUMP_DOWN:
            o->oInteractStatus = 0;
            switch (o->oAction){
                case 1:
                    switch (o->oF8){
                        case 1: 
                            o->oHomeX = -8881;
                            o->oHomeY = 20;
                            o->oHomeZ = 322;
                            o->oAction = 2;
                            break;
                        case 2:
                            o->oHomeX = -8881;
                            o->oHomeY = 20;
                            o->oHomeZ = -2219;
                            o->oAction = 2;
                            break;
                        case 3:
                            o->oHomeX = -11380;
                            o->oHomeY = 20;
                            o->oHomeZ = -2219;
                            o->oAction = 2;
                            break;
                        case 4:
                            o->oHomeX = -11380;
                            o->oHomeY = 20;
                            o->oHomeZ = 322;
                            o->oAction = 2;
                            break;
                    }
                    break;
                case 2:
                    o->oAngleToHome = cur_obj_angle_to_home();
                    cur_obj_rotate_yaw_toward(o->oAngleToHome, 1792);
                    if (o->oFaceAngleYaw == o->oAngleToHome){
                        o->oAction = 3;
                    }
                    break;
                case 3:
                    cur_obj_init_animation(6);
                    if (cur_obj_check_anim_frame(13)){
                        cur_obj_play_sound_1(SOUND_OBJ_KING_BOBOMB_JUMP);
                        o->oAction = 4;
                        o->oVelY = 60;
                    }
                    break;
                case 4:
                    approach_vec3f_asymptotic(&o->oPosVec, &o->oHomeVec, 0.08, 0.1, 0.08);
                    if (o->oMoveFlags & OBJ_MOVE_LANDED){
                        cur_obj_play_sound_1(SOUND_OBJ_POUNDING_LOUD);
                        cur_obj_shake_screen(SHAKE_POS_SMALL);
                        o->oAction = 5;
                    }
                    break;
                case 5:
                    o->oF4 = STATE_RUNNING;
                    o->oTimer = 0;
                    break;
            }
            break;
        case STATE_JUMP_AROUND:
            o->oInteractStatus = 0;
            //print_text_fmt_int(20, 80, "o100: %d", o->o100);
            switch (o->oAction){
                case 1:
                    o->o100 = (o->oF8 + 1) % 4;
                    if (o->o100 < 1){
                            o->o100 = 1;
                        } else if (o->o100 > 4){
                            o->o100 = 1;
                        }
                    o->oAction = 2;
                    break;
                case 2:
                    switch (o->o100){
                        case 1: 
                            o->oHomeX = -8881;
                            o->oHomeY = 20;
                            o->oHomeZ = 322;
                            o->oAction = 3;
                            break;
                        case 2:
                            o->oHomeX = -8881;
                            o->oHomeY = 20;
                            o->oHomeZ = -2219;
                            o->oAction = 3;
                            break;
                        case 3:
                            o->oHomeX = -11380;
                            o->oHomeY = 20;
                            o->oHomeZ = -2219;
                            o->oAction = 3;
                            break;
                        case 4:
                            o->oHomeX = -11380;
                            o->oHomeY = 20;
                            o->oHomeZ = 322;
                            o->oAction = 3;
                            break;
                        o->oTimer = 0;
                    }
                    break;
                case 3:
                    cur_obj_init_animation(0);
                    o->oAngleToHome = cur_obj_angle_to_home();
                    cur_obj_rotate_yaw_toward(o->oAngleToHome, 1792);
                    if (o->oFaceAngleYaw == o->oAngleToHome){
                        if (o->oTimer > 30){
                        o->oAction = 4;
                        }
                    }
                    break;
                case 4:
                    cur_obj_init_animation(6);
                    if (cur_obj_check_anim_frame(13)){
                        cur_obj_play_sound_1(SOUND_OBJ_KING_BOBOMB_JUMP);
                        o->oAction = 5;
                        o->oVelY = 60;
                    }
                    break;
                case 5:
                    approach_vec3f_asymptotic(&o->oPosVec, &o->oHomeVec, 0.08, 0.1, 0.08);
                    if (o->oMoveFlags & OBJ_MOVE_LANDED){
                        cur_obj_init_animation(8);
                        spawn_object_abs_with_rot(o, 0, MODEL_B_SHOCKWAVE, bhvBowserShockWave, o->oPosX, o->oFloorHeight, o->oPosZ, 0, 0, 0);
                        o->o104 += 1;
                        cur_obj_play_sound_1(SOUND_OBJ_POUNDING_LOUD);
                        cur_obj_shake_screen(SHAKE_POS_SMALL);
                        o->o100 = (o->o100 + 1) % 4;
                        if (o->o100 < 1){
                            o->o100 = 1;
                        } else if (o->o100 > 4){
                            o->o100 = 1;
                        }
                        if (o->o104 >= 4){
                            o->oAction = 6;
                        } else {
                            o->oAction = 2;
                        }
                        
                    }
                    break;
                case 6:
                    o->o104 = 0;
                    o->oF4 = STATE_RUNNING;
                    o->oTimer = 0;
                    break;
            }
            break;
        case STATE_STOMP:
            o->oInteractType = INTERACT_DAMAGE;
            switch (o->oAction){
                case 1:
                    switch (o->oHealth){
                        case 3:
                            o->oAction = 4;
                            break;
                        case 2:
                            o->oAction = 4;
                            break;
                        case 1:
                            o->oAction = 4;
                            break;
                        }
                        break;
                case 2: // jump to 2, adds three stomps
                    cur_obj_init_animation(11);
                    if (cur_obj_check_if_at_animation_end()){
                        cur_obj_play_sound_1(SOUND_OBJ_POUNDING_LOUD);
                        spawn_object_abs_with_rot(o, 0, MODEL_B_SHOCKWAVE, bhvBowserShockWave, o->oPosX, o->oFloorHeight, o->oPosZ, 0, 0, 0);
                        o->header.gfx.animInfo.animFrame = 0;
                        o->oAction = 3;
                    }
                    break;
                case 3: // jump to 3, adds two stomps
                    cur_obj_init_animation(11);
                    if (cur_obj_check_if_at_animation_end()){
                        cur_obj_play_sound_1(SOUND_OBJ_POUNDING_LOUD);
                        spawn_object_abs_with_rot(o, 0, MODEL_B_SHOCKWAVE, bhvBowserShockWave, o->oPosX, o->oFloorHeight, o->oPosZ, 0, 0, 0);
                        o->header.gfx.animInfo.animFrame = 0;
                        o->oAction = 4;
                    }
                    break;
                case 4: // jump to 4, adds one stomp
                    cur_obj_init_animation(11);
                    if (cur_obj_check_if_at_animation_end()){
                        cur_obj_play_sound_1(SOUND_OBJ_POUNDING_LOUD);
                        spawn_object_abs_with_rot(o, 0, MODEL_B_SHOCKWAVE, bhvBowserShockWave, o->oPosX, o->oFloorHeight, o->oPosZ, 0, 0, 0);
                        o->header.gfx.animInfo.animFrame = 0;
                        o->oAction = 5;
                    }
                    break;
                    //spawn_object_abs_with_rot(o, 0, MODEL_B_SHOCKWAVE, bhvBowserShockWave, o->oPosX, o->oPosY+20, o->oPosZ, 0, 0, 0);
                    //o->oAction = 2;
                case 5:
                    o->oAction = 1;
                    if (o->oHealth == 3 && o->o104 == 0){
                    o->oF4 = STATE_JUMP_UP;
                    } else {
                        o->oF4 = STATE_SPAWN_TURRETS;
                    }
                    break;
            }
            break;
        case STATE_INTRO:
            cur_obj_init_animation(12);
            o->oInteractType = INTERACT_TEXT;
            o->oInteractionSubtype = INT_SUBTYPE_NPC;
            switch (o->oAction){
                case 0:
                    if (o->oDistanceToMario < 500.0f && gMarioState->floorHeight == gMarioState->pos[1]){
                        o->oAction = 1;
                    }
                    break;
                case 1:
                    if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP,
                        DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, BIG_DADDY_FIGHT_INTRO)) {
                            o->oInteractStatus = INT_STATUS_NONE;
                            o->oAction = 1;
                            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
                            o->oF4 = STATE_JUMP_UP;
                        }
                    break;
            }
            break;
        case STATE_DEATH_DIALOG:
            cur_obj_init_animation(3);
            if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP,
                DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, BIG_DADDY_DEATH)) {
                    o->oInteractStatus = INT_STATUS_NONE;
                    o->oF4 = STATE_SPAWN_STAR;
                }
            break;
        case STATE_SPAWN_STAR:
            if (cur_obj_boss_shimmer_death(200.0f,1.0f)) {
                stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
                //spawn_object_relative(0, 0, 100, 0, o, MODEL_EXPLOSION, bhvSafeExplosion);
                //struct Object * star = spawn_object(o, MODEL_STAR, bhvStar);
                //star->oPosY += 100.0f;
                //star->oBehParams = 0x07000007;
                o->oBehParams = 0x07000007;
                spawn_default_star(o->oHomeX,o->oHomeY+300.f,o->oHomeZ);
                mark_obj_for_deletion(o);
            }
            break;
        case STATE_RESTART:
            cur_obj_init_animation(12);
            while (cur_obj_find_nearest_object_with_behavior(bhvTurretBody, &dist) != NULL && dist < 3000){
                o->oObjF8 = cur_obj_find_nearest_object_with_behavior(bhvTurretBody, &dist);
                mark_obj_for_deletion(o->oObjF8->prevObj);
                mark_obj_for_deletion(o->oObjF8);
                o->oObjF8 = NULL;
            }
            o->oObjF8 = cur_obj_find_nearest_object_with_behavior(bhvTurretPlatform, &dist);
            if (o->oObjF8->oAction >= 1){
                o->oObjFC = spawn_object_relative(0, 0, 0, 0, o->oObjF8, MODEL_TURRET_PLATFORM, bhvTurretPlatform);
                SET_BPARAM3(o->oObjFC->oBehParams, 10);
                o->oObjFC->oPosY = -243;
                mark_obj_for_deletion(o->oObjF8);
                o->oObjF8 = NULL;
                o->oObjFC = NULL;
            }
            o->oInteractStatus = 0;
            o->oFaceAngleYaw = 0x4000;
            o->oMoveAngleYaw = o->oFaceAngleYaw;
            //o->oDistanceToMario = 1000;
            stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
            o->oPosX = -10130;
            o->oPosY = 19;
            o->oPosZ = -927;
            o->oForwardVel = 0;
            o->oHealth = 3;
            o->oAction = 0;
            o->oF4 = STATE_INTRO;
            break;

    }
}

void bhv_floating_platform_b_loop(void) {

    // o->oAction = o->oFloatingPlatformIsOnFloor;
    if (o->oFloatingPlatformIsOnFloor) {
        o->oPosY = o->oHomeY;
    } else {
        floating_platform_act_move_to_home();
    }
}