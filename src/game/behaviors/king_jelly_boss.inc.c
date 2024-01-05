
struct ObjectHitbox sKingJellyBossHitbox = {
    /* interactType:      */ INTERACT_SHOCK,
    /* downOffset:        */ 50,
    /* damageOrCoinValue: */ 3,
    /* health:            */ 3,
    /* numLootCoins:      */ 0,
    /* radius:            */ 75,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 110,
    /* hurtboxHeight:     */ 100,
};

enum {
    KING_JELLY_ACT_INIT,
    KING_JELLY_ACT_WAIT,
    KING_JELLY_ACT_WANDER,
    KING_JELLY_ACT_SUMMON,
    KING_JELLY_GO_ABOVE_MARIO,
    KING_JELLY_ACT_SHAKE,
    KING_JELLY_ACT_STUNNED,
    KING_JELLY_ACT_SLAM,
    KING_JELLY_ACT_HURT,
    KING_JELLY_ACT_DIE,
    KING_JELLY_ACT_KILL_CHEATER,
};

enum kingJellyBossAnims {
    A_KINGJELLY_ANIM_IDLE,
    A_KINGJELLY_ANIM_SHOOT,
    KINGJELLY_ANIM_SPIN,
    KINGJELLY_ANIM_SLAM,
};

extern s32 big_boo_update_during_nonlethal_hit(f32 a0);

void king_jelly_boss_loop(void) {
    obj_set_hitbox(o, &sKingJellyBossHitbox);
    o->oAnimState = 0;

    switch(o->oAction) {
        case KING_JELLY_ACT_INIT:
            o->oPosY += 300.0f;
            o->prevObj = spawn_object(o, MODEL_ZAP, bhvKingJellyZap);
            cur_obj_init_animation(A_KINGJELLY_ANIM_IDLE);
            o->oAction = KING_JELLY_ACT_WAIT;
            o->oBehParams2ndByte = 0;
            break;

        case KING_JELLY_ACT_WAIT:
            o->oFaceAngleYaw = o->oAngleToMario;
            if (o->oDistanceToMario < 1500.0f) {
                o->oAction = KING_JELLY_ACT_WANDER;
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_CUSTOM_KIRBY_BOSS), 0);
            }
            break;

        case KING_JELLY_ACT_WANDER:
            o->prevObj->oAnimState = 1;
            o->oInteractType = INTERACT_SHOCK;
            o->oDamageOrCoinValue = 3;
            cur_obj_play_sound_1(SOUND_AIR_AMP_BUZZ);

            o->oPosY = approach_f32_asymptotic(o->oPosY,o->oHomeY + 300.0f, 0.1f);

            o->oPosX += sins(o->oFaceAngleYaw)*20.0f;
            o->oPosZ += coss(o->oFaceAngleYaw)*20.0f;
            if (cur_obj_lateral_dist_to_home() > 600.0f) {
                o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, cur_obj_angle_to_home(), 0x250);
                o->oMoveAngleYaw = o->oFaceAngleYaw;
            }
            //o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, o->oAngleToMario, 0x140);

            vec3f_copy(&o->prevObj->oPosVec,&o->oPosVec);

            if (o->oTimer > 160) {
                if (o->oBehParams2ndByte == 0) {
                    o->oAction = KING_JELLY_ACT_SUMMON;
                } else {
                    o->oAction = KING_JELLY_GO_ABOVE_MARIO;
                }
            }
            break;

        case KING_JELLY_ACT_SUMMON:
            if (o->oTimer == 0) {
                cur_obj_init_animation(KINGJELLY_ANIM_SPIN);
                cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_JUMP);
            }

            if (o->oTimer == 15) {
                for (u8 i = 0; i < 6; i++) {
                    struct Object *j = spawn_object(o, MODEL_JELLY, bhvJelly);
                    j->oMoveAngleYaw = i*0x2AAA;       
                    j->oFaceAngleYaw = i*0x2AAA;
                    j->oForwardVel = 40.0f;
                    j->oAction = 3;
                    j->oPosY -= 290.0f;
                }
            }

            if (o->oTimer > 29) {
                cur_obj_init_animation(A_KINGJELLY_ANIM_IDLE);
                o->oBehParams2ndByte = 1;
                o->oAction = KING_JELLY_ACT_WANDER;
            }
            break;

        case KING_JELLY_GO_ABOVE_MARIO:
            o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, o->oAngleToMario, 0x600);
            o->oMoveAngleYaw = o->oAngleToMario;

            o->oPosY = approach_f32_asymptotic(o->oPosY,o->oHomeY + 700.0f, 0.2f);
            o->oPosX += sins(o->oMoveAngleYaw)*60.0f;
            o->oPosZ += coss(o->oMoveAngleYaw)*60.0f;
            cur_obj_play_sound_1(SOUND_AIR_AMP_BUZZ);
            vec3f_copy(&o->prevObj->oPosVec,&o->oPosVec);

            if (lateral_dist_between_objects(o,gMarioObject) < 40.0f) {
                o->oAction = KING_JELLY_ACT_SHAKE;
            }
            break;

        case KING_JELLY_ACT_SHAKE:
            if (o->oTimer % 2 == 0) {
                o->oPosX += 20.0f;
                o->oPosZ += 20.0f;
            } else {
                o->oPosX -= 20.0f;
                o->oPosZ -= 20.0f;
            }
            if (o->oTimer > 30) {
                o->oAction = KING_JELLY_ACT_SLAM;
                o->oVelY = 0.0f;
                o->oSubAction = 0;
            }
            vec3f_copy(&o->prevObj->oPosVec,&o->oPosVec);
            break;

        case KING_JELLY_ACT_SLAM:
            if (o->oSubAction == 0) {
                o->oPosY += o->oVelY;
                o->oVelY -= 3.0f;
                if (o->oPosY < o->oHomeY+280.0f) {
                    o->oPosY = o->oHomeY+280.0f;
                    o->oVelY = 0.0f;
                    o->oSubAction = 1;
                    cur_obj_play_sound_2(SOUND_OBJ_POUNDING1);
                    o->oTimer = 0;
                    cur_obj_init_animation(KINGJELLY_ANIM_SLAM);

                    struct Object *wave = spawn_object(o, MODEL_PISSWAVE, bhvBowserShockWave);
                    wave->oPosY = o->oHomeY + 20.0f;
                }
            } else {
                if (o->oTimer > 60) {
                    o->oAction = KING_JELLY_ACT_STUNNED;
                }
            }
            vec3f_copy(&o->prevObj->oPosVec,&o->oPosVec);
            break;

        case KING_JELLY_ACT_STUNNED:
            o->prevObj->oAnimState = 0;
            o->oInteractType = INTERACT_BOUNCE_TOP;
            o->oDamageOrCoinValue = 0;
            if ((o->oTimer % 15 == 0)||(o->oTimer % 15 == 3)) {
                o->oAnimState = 1;
                cur_obj_play_sound_2(SOUND_GENERAL_BOWSER_KEY_LAND);
            }
            if ((o->oTimer % 15 == 1)||(o->oTimer % 15 == 4)) {
                o->oAnimState = 1;
            }
            if ((o->oInteractStatus & INT_STATUS_WAS_ATTACKED)||(o->oShotByShotgun > 0)) {
                cur_obj_init_animation(A_KINGJELLY_ANIM_IDLE);
                cur_obj_play_sound_2(SOUND_OBJ_EEL_EXIT_CAVE);
                o->oAction = KING_JELLY_ACT_HURT;
                o->oHealth--;
            }
            break;

        case KING_JELLY_ACT_HURT:
            cur_obj_become_intangible();
            if (big_boo_update_during_nonlethal_hit(40.0f)) {
                if (o->oHealth < 1) {

                    //delete every jellyfish from the arena when dead
                    struct Object * nearest_jelly = cur_obj_nearest_object_with_behavior(bhvJelly);
                    while(nearest_jelly) {
                        obj_mark_for_deletion(nearest_jelly);
                        nearest_jelly = cur_obj_nearest_object_with_behavior(bhvJelly);
                    }

                    o->oAction = KING_JELLY_ACT_DIE;
                } else {
                    o->oBehParams2ndByte = 0;
                    o->oAction = KING_JELLY_ACT_WANDER;
                    o->oFaceAnglePitch = 0;
                    o->oFaceAngleRoll = 0;
                }
            }
            break;
            
        case KING_JELLY_ACT_DIE:
            if (o->oTimer==0) {
                stop_background_music(SEQUENCE_ARGS(4, SEQ_CUSTOM_KIRBY_BOSS));
                cur_obj_play_sound_2(SOUND_OBJ_ENEMY_DEFEAT_SHRINK);
            }
            cur_obj_scale(4.0 * ((30.0f-o->oTimer)/30.0f));

            if (o->oTimer > 30) {
                spawn_default_star(o->oHomeX,o->oHomeY+400.0f,o->oHomeZ);
                obj_mark_for_deletion(o->prevObj);
                obj_mark_for_deletion(o);
            }
            break;

        case KING_JELLY_ACT_KILL_CHEATER:
            if (o->oTimer % 15 == 0) {
                cur_obj_play_sound_2(SOUND_OBJ_EEL_EXIT_CAVE);
            }

            o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, o->oAngleToMario, 0x600);
            o->oMoveAngleYaw = o->oAngleToMario;
            o->oDamageOrCoinValue = 8; // he must  die

            o->oPosY = approach_f32_asymptotic(o->oPosY,gMarioState->pos[1]+120.0f, 0.2f);
            if (lateral_dist_between_objects(o,gMarioObject) > 100.0f) {
                o->oPosX += sins(o->oMoveAngleYaw)*100.0f;
                o->oPosZ += coss(o->oMoveAngleYaw)*100.0f;
            }
            cur_obj_play_sound_1(SOUND_AIR_AMP_BUZZ);
            vec3f_copy(&o->prevObj->oPosVec,&o->oPosVec);
            break;

    }

    //hold mario in the arena unless king jelly has the following states:
    switch(o->oAction) {
        case KING_JELLY_ACT_INIT:
        case KING_JELLY_ACT_WAIT:
        case KING_JELLY_ACT_DIE:
        case KING_JELLY_ACT_KILL_CHEATER:
            break;
        default:
            while(cur_obj_lateral_dist_from_mario_to_home() > 1800.0f) {
                s16 mario_angle_to_obj_home = cur_obj_mario_angle_to_home();
                gMarioState->pos[0] += sins(mario_angle_to_obj_home);
                gMarioState->pos[2] += coss(mario_angle_to_obj_home);
                gMarioObject->oPosX = gMarioState->pos[0];
                gMarioObject->oPosZ = gMarioState->pos[2];
            }
            /*
            if (cur_obj_lateral_dist_from_mario_to_home() > 2100.0f) {
                cur_obj_init_animation(A_KINGJELLY_ANIM_IDLE);
                o->oAction = KING_JELLY_ACT_KILL_CHEATER;
            }
            */
            break;
    }

    o->oShotByShotgun = 0;
    o->oInteractStatus = 0;
}

//struct ObjectHitbox sKingJellyBossShockHitbox = {
//    /* interactType:      */ INTERACT_SHOCK,
//    /* downOffset:        */  20,
//    /* damageOrCoinValue: */   0,
//    /* health:            */   1,
//    /* numLootCoins:      */   0,
//    /* radius:            */ 90,
//    /* height:            */ 200,
//    /* hurtboxRadius:     */ 100,
//    /* hurtboxHeight:     */ 200,
//};
//
//struct ObjectHitbox sKingJellyBossButtonHitbox = {
//    /* interactType:      */ INTERACT_BREAKABLE,
//    /* downOffset:        */  20,
//    /* damageOrCoinValue: */   0,
//    /* health:            */   1,
//    /* numLootCoins:      */   0,
//    /* radius:            */ 150,
//    /* height:            */ 200,
//    /* hurtboxRadius:     */ 150,
//    /* hurtboxHeight:     */ 200,
//};

/*
enum kingJellyBossActions {
    A_KINGJELLY_IDLE_TURN,
    A_KINGJELLY_THROW_SHOCK,
    A_KINGJELLY_JELLY_LAUNCH,
    A_KINGJELLY_ATTACKED,
    A_KINGJELLY_DEATH,
    A_KINGJELLY_IDLE_TURN_2,
    A_KINGJELLY_THROW_MULTIPLE_SHOCK,
    A_KINGJELLY_JELLY_LAUNCH_2,
    A_KINGJELLY_JELLY_LAUNCH_3,
    A_KINGJELLY_ANIM_IDLE_3
};

u8 isKingJellyAttacked = 0;
u8 switchAttack = 0;
u8 hitButton = 0;

void king_jelly_boss_turn_towards_player(void) {
    s16 targetYaw = 0x600;
    cur_obj_rotate_yaw_toward(o->oAngleToMario, targetYaw);
}

void king_jelly_boss_shock(void) {
    f32 fVel = 30.0f;
    s16 targetYaw = 0x500;
    obj_set_hitbox(o, &sKingJellyBossShockHitbox);
    switch (o->oAction) {
        case 0:
            o->oForwardVel = fVel;
            cur_obj_rotate_yaw_toward(o->oAngleToMario, targetYaw);
            if ((o->oInteractStatus & INT_STATUS_INTERACTED)) {
                o->oAction = 1;
            }
            if (o->oTimer == 120) {
                o->oAction = 1;
            }
            break;
        case 1:
            o->oForwardVel = 0;
            obj_mark_for_deletion(o);
            cur_obj_disable_rendering();
            cur_obj_become_intangible();
            if (o->oTimer == 1) {
                cur_obj_play_sound_2(SOUND_OBJ_ENEMY_DEATH_HIGH);
            }
            spawn_mist_particles();
            break;
    }
    cur_obj_move_xz_using_fvel_and_yaw();
}

void king_jelly_boss_throw_shock(void) {
    if (o->oTimer == 1) {
        struct Object *s = spawn_object(o, MODEL_KING_JELLY_SHOCK, bhvKingJellyShock);
    }
}

void king_jelly_boss_jelly(void) {
    f32 fVel = 36.0f;
    s16 yaw = 0x900;
    switch (o->oAction) {
        case 0:
            o->oForwardVel = fVel;
            o->oAngleVelYaw = yaw;
            if (o->oTimer == 60) {
                o->oAction = 1;
            }
            break;
        case 1:
            o->oForwardVel = 0;
            o->oAngleVelYaw = 0;
            obj_mark_for_deletion(o);
            cur_obj_disable_rendering();
            cur_obj_become_intangible();
            spawn_mist_particles();
            break;
    }
    cur_obj_rotate_face_angle_using_vel();
    cur_obj_move_xz_using_fvel_and_yaw();
}

void king_jelly_boss_jelly_spawn(void) {
    if (o->oTimer == 1) {
        cur_obj_play_sound_2(SOUND_GENERAL_PAINTING_EJECT);
        s16 yaw = 0x4000;
        struct Object *j = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        j->oPosX = 564;
        j->oPosY = 210;
        j->oPosZ = -50;
        j->oMoveAngleYaw = yaw;       
        j->oFaceAngleYaw = yaw;
    }
    if (o->oTimer == 2) {
        s16 yaw = 0x8000;
        struct Object *j2 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        j2->oPosX = -56;
        j2->oPosY = 210;
        j2->oPosZ = -693;
        j2->oMoveAngleYaw = yaw;       
        j2->oFaceAngleYaw = yaw;
    }
    if (o->oTimer == 3) {
        s16 yaw = 0xC000;
        struct Object *j3 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        j3->oPosX = -627;
        j3->oPosY = 210;
        j3->oPosZ = -8;  
        j3->oMoveAngleYaw = yaw;
        j3->oFaceAngleYaw = yaw;   
    }
    if (o->oTimer == 4) {
        s16 yaw = 0x0000;
        struct Object *j4 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        j4->oPosX = 27;
        j4->oPosY = 210;
        j4->oPosZ = 693;
        j4->oMoveAngleYaw = yaw;       
        j4->oFaceAngleYaw = yaw;     
    }
}

void king_jelly_boss_goo_switch(void) {
    f32 yVel = 30.0f;
    s16 yaw = 0x1000;
    switch (o->oAction) {
        case 0:
            break;
        case 1:
            obj_scale_xyz(o, 1.4f * sins(o->oTimer * 0x555), 1.9f * sins(o->oTimer * 555), 1.0f);
            if (o->oTimer >= 10) {
                o->oAction = 2;
            }
            break;
        case 2:
            o->oVelY = yVel;
            o->oAngleVelYaw = yaw;
            if (o->oTimer >= 20) {
                hitButton++;
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
    obj_set_hitbox(o, &sKingJellyBossButtonHitbox);
    if (using_ability(ABILITY_BUBBLE_HAT)) {
        if (gMarioState->action == ACT_PUNCHING || gMarioState->action == ACT_MOVE_PUNCHING || gMarioState->action == ACT_JUMP_KICK) {
             if ((o->oInteractStatus & INT_STATUS_INTERACTED) && (o->oInteractStatus & INT_STATUS_WAS_ATTACKED)) {
                o->oAction = 1;
             }
        }
    }
    vec3i_add(&o->oFaceAngleVec, &o->oAngleVelVec);
}

void king_jelly_boss_throw_multiple_shock(void) {
        if (o->oTimer == 1) {
            struct Object *sh = spawn_object(o, MODEL_KING_JELLY_SHOCK, bhvKingJellyShock);
            sh->oPosX = 53;
            sh->oPosY = 214;
            sh->oPosZ = -100;
        }
        if (o->oTimer == 10) {
            struct Object *sh2 = spawn_object(o, MODEL_KING_JELLY_SHOCK, bhvKingJellyShock);
            sh2->oPosX = 275;
            sh2->oPosY = 310;
            sh2->oPosZ = -132;
        }
        if (o->oTimer == 20) {
            struct Object *sh3 = spawn_object(o, MODEL_KING_JELLY_SHOCK, bhvKingJellyShock);
            sh3->oPosX = 50;
            sh3->oPosY = 278;
            sh3->oPosZ = -396;
        }
        if (o->oTimer == 30) {
            struct Object *sh4 = spawn_object(o, MODEL_KING_JELLY_SHOCK, bhvKingJellyShock);
            sh4->oPosX = 117;
            sh4->oPosY = 294;
            sh4->oPosZ = -336;
        }
}

void king_jelly_boss_spawn_jelly_2(void) {
    if (o->oTimer == 1) {
        cur_obj_play_sound_2(SOUND_GENERAL_PAINTING_EJECT);
        s16 yaw = 0x4000;
        struct Object *j = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        j->oPosX = 564;
        j->oPosY = 210;
        j->oPosZ = -50;
        j->oMoveAngleYaw = yaw;       
        j->oFaceAngleYaw = yaw;
    }
    if (o->oTimer == 2) {
        s16 yaw = 0x8000;
        struct Object *j2 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        j2->oPosX = -56;
        j2->oPosY = 210;
        j2->oPosZ = -693;
        j2->oMoveAngleYaw = yaw;       
        j2->oFaceAngleYaw = yaw;
    }
    if (o->oTimer == 3) {
        s16 yaw = 0xC000;
        struct Object *j3 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        j3->oPosX = -627;
        j3->oPosY = 210;
        j3->oPosZ = -8;  
        j3->oMoveAngleYaw = yaw;
        j3->oFaceAngleYaw = yaw;   
    }
    if (o->oTimer == 4) {
        s16 yaw = 0x0000;
        struct Object *j4 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        j4->oPosX = 27;
        j4->oPosY = 210;
        j4->oPosZ = 693;
        j4->oMoveAngleYaw = yaw;       
        j4->oFaceAngleYaw = yaw;     
    }
    if (o->oTimer == 11) {
        cur_obj_play_sound_2(SOUND_GENERAL_PAINTING_EJECT);
        s16 yaw = 0x4000;
        struct Object *j = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        j->oPosX = 564;
        j->oPosY = 210;
        j->oPosZ = -50;
        j->oMoveAngleYaw = yaw;       
        j->oFaceAngleYaw = yaw;
    }
    if (o->oTimer == 12) {
        s16 yaw = 0x8000;
        struct Object *j2 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        j2->oPosX = -56;
        j2->oPosY = 210;
        j2->oPosZ = -693;
        j2->oMoveAngleYaw = yaw;       
        j2->oFaceAngleYaw = yaw;
    }
    if (o->oTimer == 13) {
        s16 yaw = 0xC000;
        struct Object *j3 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        j3->oPosX = -627;
        j3->oPosY = 210;
        j3->oPosZ = -8;  
        j3->oMoveAngleYaw = yaw;
        j3->oFaceAngleYaw = yaw;   
    }
    if (o->oTimer == 14) {
        s16 yaw = 0x0000;
        struct Object *j4 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        j4->oPosX = 27;
        j4->oPosY = 210;
        j4->oPosZ = 693;
        j4->oMoveAngleYaw = yaw;       
        j4->oFaceAngleYaw = yaw;     
    }
    if (o->oTimer == 21) {
        cur_obj_play_sound_2(SOUND_GENERAL_PAINTING_EJECT);
        s16 yaw = 0x4000;
        struct Object *j = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        j->oPosX = 564;
        j->oPosY = 210;
        j->oPosZ = -50;
        j->oMoveAngleYaw = yaw;       
        j->oFaceAngleYaw = yaw;
    }
    if (o->oTimer == 22) {
        s16 yaw = 0x8000;
        struct Object *j2 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        j2->oPosX = -56;
        j2->oPosY = 210;
        j2->oPosZ = -693;
        j2->oMoveAngleYaw = yaw;       
        j2->oFaceAngleYaw = yaw;
    }
    if (o->oTimer == 23) {
        s16 yaw = 0xC000;
        struct Object *j3 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        j3->oPosX = -627;
        j3->oPosY = 210;
        j3->oPosZ = -8;  
        j3->oMoveAngleYaw = yaw;
        j3->oFaceAngleYaw = yaw;   
    }
    if (o->oTimer == 24) {
        s16 yaw = 0x0000;
        struct Object *j4 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        j4->oPosX = 27;
        j4->oPosY = 210;
        j4->oPosZ = 693;
        j4->oMoveAngleYaw = yaw;       
        j4->oFaceAngleYaw = yaw;     
    }
}

void king_jelly_boss_spawn_jelly_3(void) {
    if (o->oTimer == 1) {
        struct Object *jelly = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        jelly->oPosX = 419;
        jelly->oPosY = 265;
        jelly->oPosZ = -98;
    }
    if (o->oTimer == 5) {
        struct Object *jelly2 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        jelly2->oPosX = -39;
        jelly2->oPosY = 185;
        jelly2->oPosZ = -364;
    }
    if (o->oTimer == 10) {
        struct Object *jelly3 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        jelly3->oPosX = 265;
        jelly3->oPosY = 329;
        jelly3->oPosZ = 368;
    }
    if (o->oTimer == 15) {
        struct Object *jelly4 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        jelly4->oPosX = 419;
        jelly4->oPosY = 265;
        jelly4->oPosZ = -98;
    }
    if (o->oTimer == 20) {
        struct Object *jelly3 = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        jelly3->oPosX = 265;
        jelly3->oPosY = 329;
        jelly3->oPosZ = 368;
    }
    if (o->oTimer == 25) {
        struct Object *jelly = spawn_object(o, MODEL_JELLY, bhvSpawnJellyKJ);
        jelly->oPosX = 419;
        jelly->oPosY = 265;
        jelly->oPosZ = -98;
    }
}

void king_jelly_boss_loop(void) {
    obj_set_hitbox(o, &sKingJellyBossHitbox);
    switch (o->oAction) {
        case A_KINGJELLY_IDLE_TURN:
            //spawn_platform_1();
            king_jelly_boss_turn_towards_player();
            cur_obj_init_animation(A_KINGJELLY_ANIM_IDLE);
            if (hitButton == 1) {
                o->oAction = A_KINGJELLY_ATTACKED;
            }
            if (o->oTimer == 100) {
                o->oAction = A_KINGJELLY_THROW_SHOCK;
                if (switchAttack == 1) {
                    o->oAction = A_KINGJELLY_JELLY_LAUNCH;
                }
            }
            break;
        case A_KINGJELLY_THROW_SHOCK:
            king_jelly_boss_throw_shock();
            cur_obj_init_animation(A_KINGJELLY_ANIM_SHOOT);
            if (o->oTimer == 1) {
                switchAttack = 1;
            }
            if (cur_obj_check_if_near_animation_end()) {
                o->oAction = A_KINGJELLY_IDLE_TURN;
            }
            break;
        case A_KINGJELLY_JELLY_LAUNCH:
            if (o->oTimer == 1) {
                switchAttack = 0;
            }
            cur_obj_init_animation(A_KINGJELLY_ANIM_SHOOT);
            if (cur_obj_check_if_near_animation_end()) {
                o->oAction = A_KINGJELLY_IDLE_TURN;
            }
            break;
        case A_KINGJELLY_ATTACKED:
            if (o->oTimer == 60) {
                o->oAction = A_KINGJELLY_IDLE_TURN_2;
            }
            break;
        case A_KINGJELLY_DEATH:
            if (o->oTimer == 1) {
                obj_mark_for_deletion(o);
                cur_obj_disable_rendering();
            }
            break;
        case A_KINGJELLY_IDLE_TURN_2:
            king_jelly_boss_turn_towards_player();
            cur_obj_init_animation(A_KINGJELLY_ANIM_IDLE);
            if (hitButton == 2) {
                o->oAction = A_KINGJELLY_ANIM_IDLE_3;
            }
            if (o->oTimer == 100) {
                o->oAction = A_KINGJELLY_THROW_MULTIPLE_SHOCK;
                if (switchAttack == 2) {
                    o->oAction = A_KINGJELLY_JELLY_LAUNCH_2;
                }
                if (switchAttack == 3) {
                    o->oAction = A_KINGJELLY_JELLY_LAUNCH_3;
                }
            }
            break;
        case A_KINGJELLY_THROW_MULTIPLE_SHOCK:
            cur_obj_init_animation(A_KINGJELLY_ANIM_SHOOT);
            if (o->oTimer == 40) {
                switchAttack = 2;
                o->oAction = A_KINGJELLY_IDLE_TURN_2;
            }
            break;
        case A_KINGJELLY_JELLY_LAUNCH_2:
            king_jelly_boss_spawn_jelly_2();
            cur_obj_init_animation(A_KINGJELLY_ANIM_SHOOT);
            switchAttack = 3;
            if (o->oTimer == 30) {
                o->oAction = A_KINGJELLY_IDLE_TURN_2;
            }
            break;
        case A_KINGJELLY_JELLY_LAUNCH_3:
            cur_obj_init_animation(A_KINGJELLY_ANIM_SHOOT);
            if (o->oTimer == 60) {
                switchAttack = 0;
                o->oAction = A_KINGJELLY_IDLE_TURN_2;
            }
            break;
    }

    if (o->oAction == A_KINGJELLY_JELLY_LAUNCH) {
        king_jelly_boss_jelly_spawn();
    }
    if (o->oAction == A_KINGJELLY_THROW_MULTIPLE_SHOCK) {
        king_jelly_boss_throw_multiple_shock();
    }
    if (o->oAction == A_KINGJELLY_JELLY_LAUNCH_3) {
        king_jelly_boss_spawn_jelly_3();
    }
    cur_obj_rotate_face_angle_using_vel();
}
*/