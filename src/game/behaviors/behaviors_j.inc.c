#define DRAGONITE_ACT_ABILITY 0
#define DRAGONITE_ACT_RESTING 1
#define DRAGONITE_ACT_GETTING_UP 2
#define DRAGONITE_ACT_DESPAWNING 3
#define DRAGONITE_ACT_EXTREME_SPEED 4
#define DRAGONITE_ACT_CUTSCENE  5

static struct ObjectHitbox sDragoniteHitbox = {
    /* interactType:      */ INTERACT_IGLOO_BARRIER,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 200,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 200,
    /* hurtboxHeight:     */ 200,
};

static struct ObjectHitbox sDragoniteESHitbox = {
    /* interactType:      */ INTERACT_NONE,
    /* downOffset:        */ 100,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 150,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 150,
    /* hurtboxHeight:     */ 200,
};

struct ObjectHitbox sBerryHitbox = {
    /* interactType:      */ INTERACT_GRABBABLE,
    /* downOffset:        */ 20,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 1,
    /* numLootCoins:      */ 3,//--E
    /* radius:            */ 150,
    /* height:            */ 250,
    /* hurtboxRadius:     */ 150,
    /* hurtboxHeight:     */ 250,
};

void bhv_dragonite_init(void){
    if (o->oBehParams2ndByte == 0){
        obj_scale_xyz(o, 0.0f, 0.0f, 0.0f);
        spawn_mist_particles_variable(0, 0, 30.0f);
        cur_obj_init_animation(0);
    } else if (o->oBehParams2ndByte == 1){
        ///IF (1), DESPAWN IF YOU HAVE THE ABILITY UNLOCKED
        if (save_file_check_ability_unlocked(ABILITY_HM_FLY)) {
            obj_mark_for_deletion(o);
            return;
        }
        o->oAction = DRAGONITE_ACT_RESTING;
        obj_scale_xyz(o, 0.8f,0.8f,0.8f);
        obj_set_hitbox(o, &sDragoniteHitbox);
        cur_obj_init_animation(1);
        o->oGraphYOffset = 20.0f;
    } else {
        ///ALSO DESPAWN DRAGONITE HERE IF YOU HAVE THE ABILITY UNLOCKED, OTHERWISE RUN THE CUTSCENE
        if (save_file_check_ability_unlocked(ABILITY_HM_FLY)) {
            obj_mark_for_deletion(o);
            return;
        }

        cur_obj_init_animation(0);
        o->oAction = DRAGONITE_ACT_CUTSCENE;
        cutscene_object(CUTSCENE_DRAGONITE, o);
        set_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
        o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
    }
}

extern void spawn_no_exit_star(f32, f32, f32);

void bhv_dragonite_loop(void){
    f32 xScale = o->header.gfx.scale[0];
    f32 yScale = o->header.gfx.scale[1];
    f32 zScale = o->header.gfx.scale[2];
    f32 maxScale = 0.8f;
    f32 dist;
    struct Object *berryObj = cur_obj_find_nearest_object_with_behavior(bhvBerry, &dist);

    switch(o->oAction){
        case DRAGONITE_ACT_ABILITY:
            obj_set_pos(o, gMarioState->pos[0], gMarioState->pos[1] + 156.0f, gMarioState->pos[2]);
            o->oFaceAngleYaw = gMarioState->faceAngle[1];
            o->oFaceAnglePitch = 0.0f;

            if (ability_chronos_frame_can_progress()) {
                if (gMarioState->action != ACT_HM_FLY) {
                    if (yScale > 0.0f) {
                        yScale -= 0.15f;
                    }
                    if (xScale > 0.0f) {
                        xScale -= 0.15f;
                    }
                    if (zScale > 0.0f) {
                        zScale -= 0.15f;
                    }
                    if (yScale <= 0.0f) {
                        obj_mark_for_deletion(o);
                    }

                } else {
                    if (yScale < maxScale) {
                        yScale += 0.15f;
                        xScale += 0.15f;
                        zScale += 0.15f;
                    }
                    if (yScale > maxScale){
                        yScale = maxScale;
                        xScale = maxScale;
                        zScale = maxScale;
                    }
                }

                obj_scale_xyz(o, xScale, yScale, zScale);
            }

            break;

        case DRAGONITE_ACT_RESTING:
            o->oAnimState = DRAGONITE_ANIM_STATE_EYES_CLOSED;
            if (berryObj != NULL && dist < 300.0f && berryObj->oHeldState != HELD_FREE){
                o->oAction = DRAGONITE_ACT_GETTING_UP;
                cur_obj_init_animation(2);
            }
            break;

        case DRAGONITE_ACT_GETTING_UP:
            o->oAnimState = DRAGONITE_ANIM_STATE_EYES_OPEN;
            if (cur_obj_check_if_near_animation_end()){
                o->oAction = DRAGONITE_ACT_DESPAWNING;
                cur_obj_init_animation(3);
                o->oTimer = 0;
            }
            break;
        case DRAGONITE_ACT_DESPAWNING:
            if (o->oTimer == 10){
                spawn_no_exit_star(0.0f, 749.0f, -1762.0f);
            }

            if (o->oTimer > 30) {
                yScale -= 0.05f;
                xScale -= 0.05f;
                zScale -= 0.05f;

                obj_scale_xyz(o, xScale, yScale, zScale);

                if (yScale <= 0.0f){
                    spawn_mist_particles();
                    spawn_object_relative(ABILITY_HM_FLY, 0, 50, 0, o, MODEL_ABILITY, bhvAbilityUnlock);
                    o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                }
            }
            break;
        
        case DRAGONITE_ACT_EXTREME_SPEED:
            o->oForwardVel = 75.0f;
            gMarioState->canHMFly = FALSE;
            obj_set_hitbox(o, &sDragoniteESHitbox);
            cur_obj_init_animation(4);
            cur_obj_move_xz_using_fvel_and_yaw();
            
            if (o->oTimer >= 60 || o->oInteractStatus == INT_STATUS_INTERACTED){
                yScale -= 0.05f;
                xScale -= 0.05f;
                zScale -= 0.05f;

                obj_scale_xyz(o, xScale, yScale, zScale);

                if (yScale <= 0.0f){
                    spawn_mist_particles();
                    o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                }
            }
            break;
        
        case DRAGONITE_ACT_CUTSCENE:
            o->oPosY -= 10.0f;

            if (o->oPosY <= 1060.0f){
                gObjCutsceneDone = TRUE;
                clear_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
                o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                obj_mark_for_deletion(o);
            }

            break;
            
    }
}


void bhv_berry_loop(void){
    f32 dist;
    struct Object *DragoniteObj = cur_obj_find_nearest_object_with_behavior(bhvDragonite, &dist);
    if (!DragoniteObj) {
        cur_obj_hide();
        return;
    } else {
        cur_obj_unhide();
    }

    cur_obj_update_floor_and_walls();
    switch(o->oHeldState) {
        case HELD_FREE:
        object_step();
        break;
        case HELD_HELD:
        cur_obj_unrender_set_action_and_anim(0, 0);
        obj_copy_pos(o, gMarioObject);
        break;
        case HELD_THROWN:
        cur_obj_get_thrown_or_placed(10.0f, 10.0f, 0);
        object_step();
        break;
        case HELD_DROPPED:
        cur_obj_get_dropped();
        object_step();
        break;
    }

    if (DragoniteObj->oAction == DRAGONITE_ACT_DESPAWNING){
        gMarioState->action = ACT_IDLE;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void bhv_graveler_ramp_loop(void){
    if (gCamera->cutscene < 2) {
        if (gMarioState->pos[0] <= 4800 && gMarioState->pos[0] >= -200 && gMarioState->pos[2] >= -7236 && gMarioState->pos[2] <= -5425){
            //reset_camera(gMarioState->area->camera);
            gCamera->cutscene = 1;
            //set_camera_mode_fixed(gMarioState->area->camera, -4168, 5810, -6300);
            gMarioState->area->camera->yaw = o->oFaceAngleYaw;
            gLakituState.goalPos[0] = -4168;
            gLakituState.goalPos[1] = 5810;
            gLakituState.goalPos[2] = -6300;
            gLakituState.goalFocus[0] = 1142;
            gLakituState.goalFocus[1] = 5154;
            gLakituState.goalFocus[2] = -6300;
        
        } else {
            gCamera->cutscene = 0;
        }
    }
    
}

void bhv_snorlax_init(void){
    obj_scale_xyz(o, 1.5f,1.5f,1.5f);
    o->oGraphYOffset = -250.0f;
}

void bhv_snorlax_loop(void){
    ///I only did this bc he kept turning to face mario without a behavior script.
}