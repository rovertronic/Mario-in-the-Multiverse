struct ObjectHitbox sKingJellyBossHitbox = {
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

struct ObjectHitbox sKingJellyBossShockHitbox = {
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

struct ObjectHitbox sKingJellyBossButtonHitbox = {
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

enum kingJellyBossAnims {
    A_KINGJELLY_ANIM_IDLE,
    A_KINGJELLY_ANIM_SHOOT
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