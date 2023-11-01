#define GEODUDE_ACT_ROAM 0
#define GEODUDE_ACT_CHASE 1
#define GEODUDE_ACT_PUNCH 2


static struct ObjectHitbox sGeodudeHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 100,
    /* height:            */ 50,
    /* hurtboxRadius:     */ 100,
    /* hurtboxHeight:     */ 50,
};

static struct ObjectHitbox sGeodudePunchHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 4,
    /* health:            */ 0,
    /* numLootCoins:      */ 1,
    /* radius:            */ 200,
    /* height:            */ 50,
    /* hurtboxRadius:     */ 200,
    /* hurtboxHeight:     */ 50,
};

void bhv_geodude_init(void){
    o->oGravity = -4.0f;
    o->oAction = GEODUDE_ACT_ROAM;
    o->header.gfx.scale[0] = 0.5f;
    o->header.gfx.scale[1] = 0.5f;
    o->header.gfx.scale[2] = 0.5f;
    obj_set_hitbox(o, &sGeodudeHitbox);
    cur_obj_init_animation(1);
}

static void geodude_act_walk(void){

    treat_far_home_as_mario(1000.0f);

    cur_obj_forward_vel_approach_upward(15.0f, 0.5f);

    if (o->oGeodudeTurningAwayFromWall) {
        o->oGeodudeTurningAwayFromWall = obj_resolve_collisions_and_turn(o->oGeodudeTargetYaw, 0x200);
    } else {
        // If far from home, walk toward home.
        if (o->oDistanceToMario >= 25000.0f) {
            o->oGeodudeTargetYaw = o->oAngleToMario;
            o->oGeodudeWalkTimer = random_linear_offset(20, 30);
        }

        if (!(o->oGeodudeTurningAwayFromWall = 
                obj_bounce_off_walls_edges_objects(&o->oGeodudeTargetYaw))) {
            if (o->oDistanceToMario < 2000.0f) {
                o->oAction = GEODUDE_ACT_CHASE;
            } else {
                if (o->oGeodudeWalkTimer != 0) {
                    o->oGeodudeWalkTimer--;
                } else {
                    o->oGeodudeTargetYaw = obj_random_fixed_turn(0x2000);
                    o->oGeodudeWalkTimer = random_linear_offset(100, 100);
                }
            }
        }

        cur_obj_rotate_yaw_toward(o->oGeodudeTargetYaw, 0x200);
    }
}

void bhv_geodude_loop(void){

    if (obj_update_standard_actions(0.5f)){
        cur_obj_update_floor_and_walls();

        switch (o->oAction){
            
            case GEODUDE_ACT_ROAM:
                geodude_act_walk();
                break;
            case GEODUDE_ACT_CHASE:
                o->oForwardVel = 15.0f;
                obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x400);
                if (o->oDistanceToMario < 200.0f){
                    o->oAction = GEODUDE_ACT_PUNCH;
                    o->oTimer = 0;
                    cur_obj_init_animation(0);
                }

                if (o->oDistanceToMario > 2000.0f){
                    o->oAction = GEODUDE_ACT_ROAM;
                    cur_obj_init_animation(1);
                }
                break;
            case GEODUDE_ACT_PUNCH:
                o->oForwardVel = 0.0f;
                if (o->oTimer == 24) {
                    spawn_object_relative(0, 0, 50, 100, o, MODEL_NONE, bhvGeodudePunchHitbox);
                    cur_obj_play_sound_2(SOUND_MITM_LEVEL_J_GEODUDE);
                }
                if (cur_obj_check_if_near_animation_end()) {
                    o->oAction = GEODUDE_ACT_ROAM;
                    cur_obj_init_animation(1);
                }
                break;

        }

        cur_obj_move_standard(-78);

        if((o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED) || o->oShotByShotgun == 2){
            spawn_mist_particles();
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }

        o->oInteractStatus = INT_STATUS_NONE;
        o->oShotByShotgun = 0;
    }

}

void bhv_geodude_punch_hitbox_init(void){
    obj_set_hitbox(o, &sGeodudePunchHitbox);
}

void bhv_geodude_punch_hitbox_loop(void){
    if (o->oTimer == 4){
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}