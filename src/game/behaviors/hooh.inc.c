#define HOOH_ACT_FOLLOW 0
#define HOOH_ACT_ATTACK_1 1
#define HOOH_ACT_ATTACK_2 2
#define HOOH_ACT_PHASE2_INIT 3
#define HOOH_ACT_PHASE2_CIRCLE 4
#define HOOH_ACT_PHASE2_ATTACK_1 5
#define HOOH_ACT_PHASE2_ATTACK_2 6
#define HOOH_ACT_PHASE2_ATTACK_3 7
#define HOOH_ACT_PHASE2_HIT 8
#define HOOH_ACT_PHASE2_RISE 9

static struct ObjectHitbox sHoohHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 5,
    /* numLootCoins:      */ 0,
    /* radius:            */ 400,
    /* height:            */ 800,
    /* hurtboxRadius:     */ 400,
    /* hurtboxHeight:     */ 800,
};

s16 get_angle_yaw_from_home_to_mario(void){
    s16 ang;

    ang = atan2s(o->oHomeZ - gMarioState->pos[2], o->oHomeX - gMarioState->pos[0]);
    return ang;
}

s32 hooh_check_hit_dragonite(void) {
    f32 dist;
    struct Object *dragonite = cur_obj_find_nearest_object_with_behavior(bhvDragonite, &dist);
    
    if (dragonite != NULL && obj_check_if_collided_with_object(o, dragonite)) {
        if (dragonite->oAction == 4){
            dragonite->oInteractStatus |= INT_STATUS_INTERACTED;
            return TRUE;
        }
        
    }

    return FALSE;
}

void bhv_hooh_init(void){
    s16 angleHomeToMario;
    switch(o->oBehParams2ndByte){
        case 0:
            if (gMarioState->pos[1] > o->oPosY){
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            } else {
                o->oPosY = gMarioState->pos[1];
                o->oHomeY = o->oPosY;
                obj_set_hitbox(o, &sHoohHitbox);
                cur_obj_init_animation(0);
                o->oAction = HOOH_ACT_FOLLOW;
                angleHomeToMario = get_angle_yaw_from_home_to_mario();
                o->oPosX = -sins(o->oHomeAngleToMario) * 1300.0f;
                o->oPosZ = -coss(o->oHomeAngleToMario) * 1300.0f;
                o->oHomeAngleToMario = angleHomeToMario;
            }
            break;

        case 1:
            o->oPosY = 10150.0f;
            o->oPosZ = 950.0f;
            o->oMoveAngleYaw = 0;
            o->oHomeAngleToMario = o->oMoveAngleYaw;
            o->oAction = HOOH_ACT_PHASE2_INIT;
            obj_set_hitbox(o, &sHoohHitbox);
            cur_obj_init_animation(1);
            break;

    }
}

extern void spawn_no_exit_star(f32, f32, f32);

void bhv_hooh_loop(void){
    s16 angleHomeToMario;
    f32 targetY;
    f32 rotationSpeed;
    s16 animFrame = o->header.gfx.animInfo.animFrame;


    switch(o->oAction){
        /* Phase 1: In Bell Tower*/
        case HOOH_ACT_FOLLOW:
            targetY = gMarioState->pos[1];
            o->oPosY = approach_f32(o->oPosY, targetY, 25.0f, 50.0f);
            if (o->oPosY > 15347.0f){
                o->oPosY = 15347.0f;
                o->oTimer = 0;
            }
            if (animFrame == 15){
                cur_obj_play_sound_2(SOUND_GENERAL_WING_FLAP);
            }

            o->oHomeY = o->oPosY;
            angleHomeToMario = get_angle_yaw_from_home_to_mario();
            o->oHomeAngleToMario = approach_angle(o->oHomeAngleToMario, angleHomeToMario, 0xA0);
            o->oPosX = -sins(o->oHomeAngleToMario) * 1300.0f;
            o->oPosZ = -coss(o->oHomeAngleToMario) * 1300.0f;
            obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x200);
            if (o->oTimer >= 150 && o->oDistanceToMario < 2000.0f){
                o->oTimer = 0;
                //if (random_u16() % 2 == 0){
                    o->oAction = HOOH_ACT_ATTACK_1;
                    cur_obj_init_animation(1);
                //} else {
                //    o->oAction = HOOH_ACT_ATTACK_2;
                //    cur_obj_init_animation(2);
                //}
            }

            o->oInteractStatus = INT_STATUS_NONE;

            break;
        
        case HOOH_ACT_ATTACK_1:
            targetY = gMarioState->pos[1];
            o->oPosY = approach_f32(o->oPosY, targetY, 15.0f, 15.0f);
            if (o->oPosY > 15347.0f){
                o->oPosY = 15347.0f;
            }
            o->oHomeY = o->oPosY;
            angleHomeToMario = get_angle_yaw_from_home_to_mario();
            o->oHomeAngleToMario = approach_angle(o->oHomeAngleToMario, angleHomeToMario, 0x10);
            o->oPosX = -sins(o->oHomeAngleToMario) * 1300.0f;
            o->oPosZ = -coss(o->oHomeAngleToMario) * 1300.0f;
            obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x200);

            if (o->oTimer == 18){
                cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
            }
            if (o->oTimer >= 18 && o->oTimer <= 30 && (o->oTimer % 2) == 0){
                spawn_object_relative(0, 0, 460, 250, o, MODEL_RED_FLAME, bhvHoohFlame);
            }

            if (cur_obj_check_if_near_animation_end()){
                o->oTimer = 0;
                o->oAction = HOOH_ACT_FOLLOW;
                cur_obj_init_animation(0);

            }
            break;

            case HOOH_ACT_PHASE2_INIT:
                if (cur_obj_check_if_near_animation_end()){
                    cur_obj_init_animation(0);
                    o->oVelY = 50.0f;
                    cur_obj_play_sound_2(SOUND_GENERAL_WING_FLAP);
                }

                o->oPosY += o->oVelY;

                if (o->oTimer == 18){
                    cur_obj_play_sound_2(SOUND_MITM_LEVEL_J_HOOH);
                }

                if (o->oPosY >= 15000.0f){
                    o->oAction = HOOH_ACT_PHASE2_CIRCLE;
                    o->oTimer = 0;
                }

                o->oInteractStatus = INT_STATUS_NONE;

                break;
            
            case HOOH_ACT_PHASE2_CIRCLE:
                targetY = 10050.0f;
                o->oPosY = approach_f32(o->oPosY, targetY, 25.0f, 50.0f);
                switch(o->oHealth){
                    case 5:
                        o->oHomeAngleToMario += 64;
                        break;
                    case 4:
                        o->oHomeAngleToMario += 80;
                        break;
                    case 3:
                    case 2:
                    case 1:
                        o->oHomeAngleToMario += 96;
                        break;

                }
                
                o->oPosX = -sins(o->oHomeAngleToMario) * 5000.0f;
                o->oPosZ = -coss(o->oHomeAngleToMario) * 5000.0f;
                obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x200);

                if (animFrame == 15){
                    cur_obj_play_sound_2(SOUND_GENERAL_WING_FLAP);
                }

                //if (o->oTimer >= 150 && o->oDistanceToMario < 2000.0f){
                //    o->oTimer = 0;
                    //if (random_u16() % 2 == 0){
                //        o->oAction = HOOH_ACT_ATTACK_1;
                //        cur_obj_init_animation(1);
                    //} else {
                    //    o->oAction = HOOH_ACT_ATTACK_2;
                    //    cur_obj_init_animation(2);
                    //}
                //}

                if (o->oTimer == 120 && o->oHealth < 5){
                    cur_obj_init_animation(1);
                }
                
                if (o->oTimer == 138){
                    cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
                }

                if (o->oTimer >= 138 && o->oTimer <= 150 && (o->oTimer % 2) == 0 && o->oHealth < 5){
                    spawn_object_relative(1, 0, 460, 250, o, MODEL_RED_FLAME, bhvHoohFlame);
                }

                if (o->oTimer == 180){
                    o->oTimer = 0;
                    cur_obj_init_animation(0);
                }

                if (hooh_check_hit_dragonite()){
                    o->oAction = HOOH_ACT_PHASE2_HIT;
                    o->oTimer = 0;
                    o->oHealth--;
                    cur_obj_init_animation(3);
                    if (o->oHealth <= 0){
                        cur_obj_play_sound_2(SOUND_MITM_LEVEL_J_HOOH);
                        spawn_no_exit_star(0.0f, 10300.0f, 657.0f);
                    }
                    o->oVelY = 20;
                }

                o->oInteractStatus = INT_STATUS_NONE;

                break;
            
            case HOOH_ACT_PHASE2_HIT:
                targetY = 5000.0f;
                o->oVelY -= 4.0f;
                o->oPosY += o->oVelY;

                if (o->oPosY <= targetY){
                    if (o->oHealth <= 0){
                        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                    } else {
                        o->oAction = HOOH_ACT_PHASE2_RISE;
                        cur_obj_init_animation(4);
                        o->oTimer = 0;
                    }
                }

                break;
            
            case HOOH_ACT_PHASE2_RISE:
                o->oVelY = 100.0f;
                o->oPosY += o->oVelY;

                if (o->oPosY >= 15000.0f){
                    switch(o->oHealth){
                        case 4:
                        case 2: o->oAction = HOOH_ACT_PHASE2_ATTACK_1; break;
                        case 1:
                        case 3: o->oAction = HOOH_ACT_PHASE2_ATTACK_2; break;
                    }
                    o->oTimer = 0;
                }

                break;
            
            case HOOH_ACT_PHASE2_ATTACK_1:
                cur_obj_set_model(MODEL_NONE);
                if (o->oTimer % 15 == 0){
                    spawn_object(o, MODEL_J_HOOH_ROCK, bhvHoohRock);
                }

                if (o->oTimer >= 450){
                    o->oAction = HOOH_ACT_PHASE2_CIRCLE;
                    o->oTimer = 0;
                    cur_obj_set_model(MODEL_J_HOOH);
                    cur_obj_init_animation(0);
                }

                break;

            case HOOH_ACT_PHASE2_ATTACK_2:
                cur_obj_set_model(MODEL_NONE);
                if (o->oTimer % 60 == 0 || o->oTimer == 0){
                    spawn_object_relative(2, 0, 0, 0, o, MODEL_RED_FLAME, bhvHoohFlame);
                }

                if (o->oTimer >= 450){
                    o->oAction = HOOH_ACT_PHASE2_CIRCLE;
                    o->oTimer = 0;
                    cur_obj_set_model(MODEL_J_HOOH);
                    cur_obj_init_animation(0);
                }

                break;


    }

}

void bhv_hooh_flame_init(void){
    if (o->oBehParams2ndByte == 2){
        o->oPosY = 12000.0f;
        o->oPosX = gMarioState->pos[0];
        o->oPosZ = gMarioState->pos[2];
        o->oGravity = 1.6f;
    } else {
        f32 dx = gMarioObject->header.gfx.pos[0] - o->oPosX;
        f32 dy = gMarioObject->header.gfx.pos[1] - o->oPosY + 120.0f;
        f32 dz = gMarioObject->header.gfx.pos[2] - o->oPosZ;
        s16 targetPitch = atan2s(sqrtf(sqr(dx) + sqr(dz)), dy);
        o->oMoveAnglePitch = targetPitch;
        o->oMoveAngleYaw = atan2s( gMarioState->pos[2] - o->oHomeZ, gMarioState->pos[0] - o->oHomeX);
    }
}

void bhv_hooh_flame_loop(void){
    f32 dx = gMarioObject->header.gfx.pos[0] - o->oPosX;
    f32 dy = gMarioObject->header.gfx.pos[1] - o->oPosY + 120.0f;
    f32 dz = gMarioObject->header.gfx.pos[2] - o->oPosZ;
    s16 targetPitch = atan2s(sqrtf(sqr(dx) + sqr(dz)), dy);
    f32 floorY;
    int i = 0;

    switch (o->oBehParams2ndByte){

        case 0:
            obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x150);

            o->oMoveAnglePitch = approach_s16_symmetric(o->oMoveAnglePitch, targetPitch, 0xA0);
            o->oVelY = sins(o->oMoveAnglePitch) * 30.0f;
            o->oPosY += o->oVelY;
            o->oForwardVel = coss(o->oMoveAnglePitch) * 50.0f;
            cur_obj_move_xz_using_fvel_and_yaw();
            if (o->oTimer > 60 || o->oInteractStatus == INT_STATUS_INTERACTED){
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                obj_mark_for_deletion(o);
            }
            break;
        case 1:
            obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x150);

            o->oMoveAnglePitch = approach_s16_symmetric(o->oMoveAnglePitch, targetPitch, 0xA0);
            o->oVelY = sins(o->oMoveAnglePitch) * 30.0f;
            o->oPosY += o->oVelY;
            o->oForwardVel = coss(o->oMoveAnglePitch) * 50.0f;
            cur_obj_move_xz_using_fvel_and_yaw();
            if (o->oTimer > 120 || o->oInteractStatus == INT_STATUS_INTERACTED){
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                obj_mark_for_deletion(o);
            }
            break;
        
        case 2:
            o->oVelY -= o->oGravity;
            o->oPosY += o->oVelY;
            o->oFaceAngleYaw = 0x8000;
            floorY = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
            if (floorY >= o->oPosY){
                for (i = 0; i < 36; i++){
                    spawn_object_relative((i * 3276), 0, 150, 0, o, MODEL_BLUE_FLAME, bhvHoohFlame2);
                }

                if (random_u16() % 2 == 0){
                    spawn_object_relative(0, 0, 50, 0, o, MODEL_YELLOW_COIN, bhvMovingYellowCoin);
                }

                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                obj_mark_for_deletion(o);

            }
    }
}

void bhv_hooh_flame2_loop(void){
    o->oForwardVel = 20.0f;
    o->oMoveAngleYaw = o->oBehParams2ndByte;
    cur_obj_move_xz_using_fvel_and_yaw();

    if (o->oTimer > 90){
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        obj_mark_for_deletion(o);
    }
}

void bhv_hooh_rock_init(void){
    o->header.gfx.scale[0] = 2.0f;
    o->header.gfx.scale[1] = 2.0f;
    o->header.gfx.scale[2] = 2.0f;
    o->oPosY = 11500.0f;
    o->oGravity = 0.8f;
    if (random_u16() % 2 == 0){
        o->oPosX = gMarioState->pos[0];
        o->oPosZ = gMarioState->pos[2];
    } else {
        o->oPosX = gMarioState->pos[0] + (coss(gMarioState->faceAngle[1]) * 1000.0f);
        o->oPosZ = gMarioState->pos[2] + (sins(gMarioState->faceAngle[1]) * 1000.0f);
    }
}

void bhv_hooh_rock_loop(void){
    f32 floorY;
    o->oFaceAnglePitch += 0x200;
    o->oFaceAngleYaw += 0x200;

    o->oVelY -= o->oGravity;
    o->oPosY += o->oVelY;

    floorY = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
    if (floorY >= o->oPosY){
        spawn_mist_particles();
        cur_obj_play_sound_2(SOUND_GENERAL_GRINDEL_ROLL);
        set_camera_shake_from_point(SHAKE_POS_SMALL, o->oPosX, o->oPosY, o->oPosZ);
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        obj_mark_for_deletion(o);
    }
}