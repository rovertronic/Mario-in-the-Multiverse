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

enum {
    AIRLOCK_STATE_WET,
    AIRLOCK_STATE_DRY,
    AIRLOCK_STATE_CLOSED,
    AIRLOCK_STATE_CLOSED_FINISHED,
};

u8 airlockState;
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
    o->oFaceAngleYaw += 0x100;
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
        }
    }
}

void bhv_airlock_water_loop(){
    cur_obj_update_floor_and_walls();
    if (isWet == TRUE && airlockState == AIRLOCK_STATE_CLOSED_FINISHED){
        if (o->oPosY >= o->oHomeY - 846.0f){
            o->oPosY-= 10;
        } else {
            o->oPosY = o->oHomeY - 846.0f;
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
                o->oAction = 1;
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
                    o->oInteractStatus = INT_STATUS_NONE;
                    o->oAction = 4;
                }
            break;
        case 4:
            o->prevObj->oInteractionSubtype |= INT_SUBTYPE_DROP_IMMEDIATELY;
            spawn_object_relative(0, 400, 0, 0, o, MODEL_EXPLOSION, bhvExplosion);
            spawn_object_relative(ABILITY_BIG_DADDY, 400, 0, 0, o, MODEL_ABILITY, bhvAbilityUnlock);
            o->oAction = 5;
            break;
        case 5:
            if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP,
                    DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, DIALOG_059)) {
                    o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                    o->oInteractStatus = INT_STATUS_NONE;
                    o->oInteractionSubtype = 0;
                    o->oSubAction++;
                }
            }
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
        o->oHomeX = respawner->oPosX;
        o->oHomeY = respawner->oPosY;
        o->oHomeZ = respawner->oPosZ;
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
            DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG_NO_ZOOM, BIG_DADDY_STAR)) {
                o->oInteractStatus = INT_STATUS_NONE;
                o->oInteractType = INTERACT_GRABBABLE;
                o->oInteractionSubtype = INT_SUBTYPE_HOLDABLE_NPC;
                o->oAction = LS_CUTSCENE;
                
                
        }
    }
    if (o->oAction == LS_CUTSCENE){
        inCutscene = TRUE;
        switch (curCutsceneState) {
            case 0:
                curCutsceneState = 1;
                break;
            case 1:
                cutsceneFocus[0] = 2702;
                cutsceneFocus[1] = 595;
                cutsceneFocus[2] = -1389;
                cutscenePos[0] = 3000;
                cutscenePos[1] = 595;
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
                set_or_approach_f32_asymptotic(&gLakituState.goalFocus[1], 350, 0.05f);
                if (gLakituState.goalPos[0] > 3499.0f){
                    curCutsceneState = 4;
                }
                break;
            case 5:
                gLakituState.goalPos[0] = 4200;
                gLakituState.goalPos[1] = 800;
                gLakituState.goalPos[2] = -2194;
                gLakituState.goalFocus[0] = 5700;
                gLakituState.goalFocus[1] = 82;
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
        o->oHomeX = o->oPosX;
        o->oHomeY = o->oPosY;
        o->oHomeZ = o->oPosZ;
        cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x250);
        cur_obj_init_animation(0);
        if (o->oInteractStatus & INT_STATUS_INTERACTED) {
            if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP,
                DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, DIALOG_072)) {
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
                        cur_obj_init_animation(0);
                    }
                }
            }
            break;
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

    // Find the nearest object with the specified behavior and get the distance
    f32 dist;
    struct Object *turretPlatform = cur_obj_find_nearest_object_with_behavior(bhvTurretPlatform, &dist);

    // If the distance is less than 100.0f, set the parent object and behavior parameter accordingly
    if (dist < 100.0f){
        o->parentObj = turretPlatform;
        SET_BPARAM1(o->oBehParams, GET_BPARAM1(o->parentObj->oBehParams));
    }

    // Find the object with the specified behavior and parameter
    o->oObjF4 = find_object_with_behaviors_bparam(bhvTurretPanel, GET_BPARAM1(o->oBehParams), 1);
}


void bhv_turret_body_loop(void){
    //print_text_fmt_int(20, 120, "base yaw %d", (u16)o->oMoveAngleYaw);
    if (o->oDistanceToMario < 500){
        //print_text_fmt_int(20, 60, "bparam1 %d", GET_BPARAM1(o->oBehParams));
    }
    if (o->parentObj != NULL){
        if (o->parentObj->o10C == 1){
            if (o->prevObj != NULL) {
                mark_obj_for_deletion(o->prevObj);
            }
            mark_obj_for_deletion(o);
            return; // Exit the function since 'o' has been deleted
        }
        o->oPosY = o->parentObj->oPosY;
    }
    if (obj_hit_by_bullet(o, 750.0f) == 2){
        spawn_object_relative(0, 0, 0, 0, o, MODEL_EXPLOSION, bhvExplosion);
        if (o->prevObj != NULL) {
            mark_obj_for_deletion(o->prevObj);
        }
        mark_obj_for_deletion(o);
        return; // Exit the function since 'o' has been deleted
    }
    if (o->oObjF4 != NULL && o->oObjF4->oAction == 1){
        spawn_object_relative(0, 0, 0, 0, o, MODEL_EXPLOSION, bhvExplosion);
        if (o->prevObj != NULL) {
            mark_obj_for_deletion(o->prevObj);
        }
        mark_obj_for_deletion(o);
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
            mark_obj_for_deletion(o);
            return; // Exit the function since 'o' has been deleted
        } else {
            o->oInteractStatus = INT_STATUS_NONE;
        }
    }
    if (o->oShotByShotgun > 0){
        spawn_object_relative(0, 0, 0, 0, o, MODEL_EXPLOSION, bhvExplosion);
        if (o->prevObj != NULL) {
            mark_obj_for_deletion(o->prevObj);
        }
        mark_obj_for_deletion(o);
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

void bhv_cork(void){
    struct Surface *hitSurface;
    if (cur_obj_was_attacked_or_ground_pounded()) {
        obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
        create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
        if (GET_BPARAM1(o->oBehParams) == 1){
            gLakituState.goalPos[1] = gLakituState.goalPos[1] - 3000;
            gLakituState.goalFocus[1] = gLakituState.goalFocus[1] - 3000;
        }
    }
}