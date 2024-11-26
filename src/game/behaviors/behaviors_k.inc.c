void blood_cast(Vec3f * start, Vec3f * ray) {
    if (gSaveBuffer.menuData.config[SETTINGS_BLOOD] == 1) {
        return;
    }

    s16 blood_count = count_objects_with_behavior(bhvKblood);
    if (blood_count > 100) {
        return;
    }

    Vec3f hitpos;
    struct Surface * surf;
    find_surface_on_ray(start,ray,&surf,hitpos,RAYCAST_FIND_WALL | RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL);

    if (surf&&!surf->object) {
        u16 model = MODEL_K_BLOOD;
        if (surf->type == SURFACE_VANISH_FLOOR) {
            model = MODEL_K_BLOOD_2;
        }

        struct Object * blood = spawn_object(o,model,bhvKblood);
        vec3f_copy(&blood->oPosVec,hitpos);
        vec3f_copy(&blood->oHomeVec,&surf->normal);
        blood->oFloor = surf;
    }
}

void bhv_k_fan(void) {
    if (gMarioState->abilityChronosTimeSlowActive) {
        o->oFaceAnglePitch += 0x200;
        o->collisionData = segmented_to_virtual(k_fan_collision);
    } else {
        o->oFaceAnglePitch += 0x1000;
        o->collisionData = segmented_to_virtual(k_fan_2_collision);
    }

    if (o->oDistanceToMario < 4000.0f) {
        cur_obj_play_sound_1(SOUND_MITM_LEVEL_SPINNING_BLADE);
    }

    if (gMarioState->wall && gMarioState->wall->object && obj_has_behavior(gMarioState->wall->object,bhvKfan)) {
        play_sound(SOUND_MARIO_ATTACKED, gMarioState->marioObj->header.gfx.cameraToObject);
        gMarioState->hurtCounter+=8;
        set_mario_action(gMarioState,ACT_BACKWARD_AIR_KB,0);

        Vec3f blood_cast_ray = {sins(gMarioState->faceAngle[1])*-500.0f,-150.0f,coss(gMarioState->faceAngle[1])*-500.0f};
        blood_cast(gMarioState->pos,blood_cast_ray);
        for (int i = 0; i<3; i++) {
            Vec3f blood_cast_ray = {450.0f-random_float()*900.0f,-600.0f,450.0f-random_float()*900.0f};
            gMarioState->pos[1] += 5.0f;
            blood_cast(gMarioState->pos,blood_cast_ray);
            gMarioState->pos[1] -= 5.0f;
        }
    }
}

void bhv_k_blood(void) {
    Vec3f scale = {1.0f,1.0f,1.0f};
    if (o->oTimer == 0) {
        s16 roll = (random_u16()%4)*0x4000;
        mtxf_shadow(o->transform, &o->oHomeVec, &o->oPosVec, scale, roll);
        vec3f_copy(&o->transform[3][0],&o->oPosVec);

        if (o->oFloor->type == SURFACE_CONVEYOR) {
            o->oAction = 1;
        }
    }

    if (o->oAction == 1) {
        //roll over conveyor
        struct Surface * floor;
        find_floor(o->oPosX,o->oPosY+10.0f,o->oPosZ,&floor);
        if (floor && floor->type == SURFACE_CONVEYOR) {
            //0xAABB -> AA is speed, BB is angle
            s16 pushAngle = floor->force << 8;
            u8 pushSpeed = floor->force >> 8;

            // divide by 2 to be more precise
            o->oPosX += ((f32)(pushSpeed) / 2) * sins(pushAngle);
            o->oPosZ += ((f32)(pushSpeed) / 2) * coss(pushAngle);

            vec3f_copy(&o->transform[3][0],&o->oPosVec);
        } else {
            mark_obj_for_deletion(o);
        }
    }

    f32 dsqr;
    vec3f_get_dist_squared(&o->oPosVec,gMarioState->pos,&dsqr);

    if (dsqr > 7000.0f * 7000.0f) {
        mark_obj_for_deletion(o);
    }

    o->header.gfx.throwMatrix = o->transform;
}

void bhv_k_bartender(void) {
    o->oAnimState = 0;
    switch(o->oTimer) {
        case 30:
        case 31:
        case 32:
        case 37:
        case 38:
        case 39:
            o->oAnimState = 1;
            break;
    }
    if (o->oTimer > 40) {
        o->oTimer = 0;
    }
}

s16 k_kill_counter = 0;

static struct ObjectHitbox sKEnemyHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 3,
    /* radius:            */ 60,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 60,
    /* hurtboxHeight:     */ 160,
};

enum {
    K_ENEMY_INIT,
    K_ENEMY_IDLE,
    K_ENEMY_PATROL_RUN,
    K_ENEMY_PATROL_IDLE,
    K_ENEMY_CHASE,
    K_ENEMY_STAGGER,
    K_ENEMY_MELEE,
    K_ENEMY_SHOOT,
    K_ENEMY_BLOCKUP,
    K_ENEMY_DIE,
};

void k_kill_enemy(void) {
    if (o->oAction != K_ENEMY_DIE) {
        s16 kill_angle;
        Vec3f origin = {o->oPosX, o->oPosY + 70.0f, o->oPosZ};
        Vec3f cast = {0.0f,-100.0f,0.0f};
        blood_cast(origin,cast);

        kill_angle = gMarioState->faceAngle[1] + (750-(random_u16()%1500));
        vec3f_set(cast,sins(kill_angle)*200.0f,-100.0f,coss(kill_angle)*200.0f);
        blood_cast(origin,cast);

        kill_angle = gMarioState->faceAngle[1] + (750-(random_u16()%1500));
        vec3f_set(cast,sins(kill_angle)*400.0f,-100.0f,coss(kill_angle)*400.0f);
        blood_cast(origin,cast);

        kill_angle = gMarioState->faceAngle[1] + (750-(random_u16()%1500));
        vec3f_set(cast,sins(kill_angle)*600.0f,-100.0f,coss(kill_angle)*600.0f);
        blood_cast(origin,cast);

        kill_angle = gMarioState->faceAngle[1] + (750-(random_u16()%1500));
        vec3f_set(cast,sins(kill_angle)*1000.0f,0.0f,coss(kill_angle)*1000.0f);
        blood_cast(origin,cast);

        kill_angle = gMarioState->faceAngle[1] + (750-(random_u16()%1500));
        vec3f_set(cast,sins(kill_angle)*1000.0f,250.0f,coss(kill_angle)*1000.0f);
        blood_cast(origin,cast);

        kill_angle = gMarioState->faceAngle[1];

        o->oAction = K_ENEMY_DIE;
        o->oMoveAngleYaw = kill_angle;
        o->oForwardVel = 35.0f;
        o->oVelY = 15.0f;
        cur_obj_become_intangible();

        cur_obj_init_animation_with_sound(HUMANOID_ANIM_DIE);

        for (u8 i=0; i<4; i++) {
            osRecvMesg(&gGameVblankQueue, &gMainReceivedMesg, OS_MESG_BLOCK);
        }

        k_kill_counter++;
    }
}

void k_enemy_melee(void) {
    o->oInteractType = INTERACT_DAMAGE;
    o->oDamageOrCoinValue = 4;
    cur_obj_become_tangible();
}

void k_enemy_vulnerable(void) {
    o->oInteractType = INTERACT_BOUNCE_TOP;
    o->oDamageOrCoinValue = 0;
    if (o->oShotByShotgun > 0) {
        k_kill_enemy();
    }
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
            k_kill_enemy();
        }
    }
    if (obj_hit_by_deflected_bullet(o, 200.0f)) {
        k_kill_enemy();
    }
}

void k_enemy_staggerable(void) {
    o->oInteractType = INTERACT_BOUNCE_TOP;
    o->oDamageOrCoinValue = 0;
    if (o->oShotByShotgun > 0) {
        cur_obj_play_sound_2(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL);
        o->oAction = K_ENEMY_STAGGER;
        o->oTimer = 0;
    }
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
            cur_obj_play_sound_2(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL);
            o->oAction = K_ENEMY_STAGGER;
            o->oTimer = 0;

            if (using_ability(ABILITY_MARBLE)) {
                k_kill_enemy();
            }
        }
    }
    if (obj_hit_by_deflected_bullet(o, 200.0f)) {
        k_kill_enemy();
    }
}

void k_enemy_stagger_vulnerable(void) {
    o->oInteractType = INTERACT_BOUNCE_TOP;
    o->oDamageOrCoinValue = 0;
    if (o->oShotByShotgun > 0) {
        cur_obj_play_sound_2(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL);
        o->oAction = K_ENEMY_STAGGER;
        o->oTimer = 0;
        o->oMoveAngleYaw = obj_angle_to_object(o,gMarioObject);
    }
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oInteractStatus & INT_STATUS_CHRONOS_SLASHED) {
            k_kill_enemy();
        } else {
            if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
                cur_obj_play_sound_2(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL);
                o->oAction = K_ENEMY_STAGGER;
                o->oTimer = 0;
                o->oMoveAngleYaw = obj_angle_to_object(o,gMarioObject);

                if (using_ability(ABILITY_MARBLE)) {
                    k_kill_enemy();
                }
            }
        }
    }
    if (obj_hit_by_deflected_bullet(o, 200.0f)) {
        k_kill_enemy();
    }
}

void k_enemy_shielded(void) {
    o->oInteractType = INTERACT_BOUNCE_TOP;
    o->oDamageOrCoinValue = 0;
    if (o->oShotByShotgun > 0) {
        cur_obj_play_sound_2(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL);
    }
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
            cur_obj_play_sound_2(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL);

            if (using_ability(ABILITY_MARBLE)) {
                k_kill_enemy();
            }
        }
    }
}

void k_generic_enemy_search_for_mario(void) {
    //look for mario
    if (o->oMoveFlags & (OBJ_MOVE_HIT_EDGE|OBJ_MOVE_HIT_WALL)) {
        return;
    }
    Vec3f hitPos;
    struct Surface * surf = NULL;
    Vec3f ray_start = {o->oPosX,o->oPosY+100.0f,o->oPosZ};
    Vec3f ray_vector = {gMarioState->pos[0]-o->oPosX,(gMarioState->pos[1]-o->oPosY)+100.0f,gMarioState->pos[2]-o->oPosZ};
    if (o->oDistanceToMario < 2000.0f) {
        u16 view_angle = ABS(obj_angle_to_object(o,gMarioObject)-o->oMoveAngleYaw);
        find_surface_on_ray(ray_start, ray_vector, &surf, hitPos, (RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL | RAYCAST_FIND_WALL));
        if ((view_angle < 0x3000) && !surf) {
            o->oAction = K_ENEMY_CHASE;
        }
    }
}

void k_generic_enemy_init(void) {
    if (o->oAction == K_ENEMY_INIT) {
        obj_set_hitbox(o, &sKEnemyHitbox);
        o->oGravity = -2.0f;
        o->oAction = K_ENEMY_IDLE;
        o->oWallHitboxRadius = 40.0f;
    }
}

void k_generic_enemy_handler(void) {
    cur_obj_update_floor_and_walls();
    if (o->oAction == K_ENEMY_DIE) {
        cur_obj_move_standard(78);
    } else {
        cur_obj_move_standard(-78);
    }

    if (o->oFloor) {
        struct Surface * floor = o->oFloor;
        if (floor->type == SURFACE_CONVEYOR) {
            //0xAABB -> AA is speed, BB is angle
            s16 pushAngle = floor->force << 8;
            u8 pushSpeed = floor->force >> 8;

            // divide by 2 to be more precise
            o->oPosX += ((f32)(pushSpeed) / 2) * sins(pushAngle);
            o->oPosZ += ((f32)(pushSpeed) / 2) * coss(pushAngle);
        }
        cur_obj_update_floor_and_walls();
    }


    switch(o->oAction) {
        case K_ENEMY_DIE:
            o->oForwardVel *= .9f;

            if (o->oMoveFlags & OBJ_MOVE_LANDED) {
                Vec3f origin = {o->oPosX, o->oPosY + 70.0f, o->oPosZ};
                Vec3f cast = {0.0f,-100.0f,0.0f};
                blood_cast(origin,cast);
                o->oForwardVel = 17.0f;
                cur_obj_play_sound_2(SOUND_ACTION_BONK);
            }
            break;
        case K_ENEMY_PATROL_RUN:
            if (o->oTimer == 0) {
                cur_obj_init_animation_with_sound(0);
            }
            if (o->oMoveFlags & (OBJ_MOVE_HIT_WALL | OBJ_MOVE_HIT_EDGE)) {
                o->oAction = K_ENEMY_PATROL_IDLE;
            }
            o->oForwardVel = 25.0f;
            if (o->oTimer > 40) {
                o->oAction = K_ENEMY_PATROL_IDLE;
            }
            k_generic_enemy_search_for_mario();
            break;
        case K_ENEMY_PATROL_IDLE:
            o->oForwardVel = 0.f;
            if (o->oTimer == 0) {
                cur_obj_init_animation_with_sound(1);
                o->oAngleVelYaw = random_u16();
            }
            o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw,o->oAngleVelYaw,4);
            if (o->oTimer > 50) {
                o->oAction = K_ENEMY_PATROL_RUN;
            }
            k_generic_enemy_search_for_mario();
            break;
        case K_ENEMY_CHASE:
            if (o->oTimer == 0) {
                cur_obj_init_animation_with_sound(0);
            }
            o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw,obj_angle_to_object(o,gMarioObject),4);
            o->oForwardVel = 25.0f;

            if (o->oMoveFlags & (OBJ_MOVE_HIT_EDGE|OBJ_MOVE_HIT_WALL)) {
                o->oAction = K_ENEMY_PATROL_IDLE;
                cur_obj_init_animation_with_sound(1);
            }
            break;
        case K_ENEMY_MELEE:
            if (o->oTimer == 0) {
                cur_obj_play_sound_2(SOUND_ACTION_SIDE_FLIP_UNK);
                o->oForwardVel = 0.0f;
            }
            o->oForwardVel *= .95f;
            if (o->oTimer == 10) {
                cur_obj_play_sound_2(SOUND_ACTION_SIDE_FLIP_UNK);
                o->oForwardVel = 35.0f;
            }
            if (o->oTimer >= 60) {
                o->oAction = K_ENEMY_PATROL_IDLE;
            }
            break;
        case K_ENEMY_STAGGER:
            cur_obj_become_intangible();
            if (o->oTimer == 0) {
                o->oForwardVel = -60.0f;
            }
            o->oForwardVel *= .9f;
            if (o->oTimer >= 35) {
                o->oAction = K_ENEMY_PATROL_IDLE;
                cur_obj_become_tangible();
            }
            if (o->oTimer > 25) {
                cur_obj_become_tangible();
                k_enemy_stagger_vulnerable();
            }
            break;
    }

    cur_obj_die_if_on_death_floor();

    o->oInteractStatus = INTERACT_NONE;
    o->oShotByShotgun = 0;
}

void bhv_k_strong_terry(void) {
    k_generic_enemy_init();

    switch(o->oAction) {
        case K_ENEMY_IDLE:
            if (gCurrAreaIndex != 2) {
                o->oAction = K_ENEMY_PATROL_RUN;
            }
            k_generic_enemy_search_for_mario();
            k_enemy_vulnerable();
            break;
        case K_ENEMY_PATROL_IDLE:
        case K_ENEMY_PATROL_RUN:
            k_enemy_vulnerable();
            break;
        case K_ENEMY_CHASE:
            if (o->oDistanceToMario < 200.0f) {
                o->oAction = K_ENEMY_MELEE;
            }
            k_enemy_vulnerable();
            break;
        case K_ENEMY_MELEE:
            if (o->oTimer == 0) {
                //ensure the first frame is the slow cond
                cur_obj_init_animation_with_sound(HUMANOID_ANIM_TERRY_MASH);
                o->oForwardVel = 0.0f;
            }
            if (o->oForwardVel > 10.0f) {
                k_enemy_melee();
            } else {
                k_enemy_vulnerable();
            }
            break;
    }

    k_generic_enemy_handler();
}

void bhv_k_skinny_ricky(void) {
    k_generic_enemy_init();

    switch(o->oAction) {
        case K_ENEMY_IDLE:
            o->oAction = K_ENEMY_PATROL_RUN;
            break;
        case K_ENEMY_PATROL_IDLE:
        case K_ENEMY_PATROL_RUN:
            k_enemy_stagger_vulnerable();
            break;
        case K_ENEMY_CHASE:
            if (o->oDistanceToMario < 200.0f) {
                o->oAction = K_ENEMY_MELEE;
            }
            k_enemy_staggerable();
            break;
        case K_ENEMY_MELEE:
            if (o->oTimer == 0) {
                //ensure the first frame is the slow cond
                cur_obj_init_animation_with_sound(HUMANOID_ANIM_RICKY_WHACK);
                o->oForwardVel = 0.0f;
            }
            if (o->oForwardVel > 7.0f) {
                k_enemy_melee();
            } else {
                k_enemy_staggerable();
            }
            break;
        case K_ENEMY_STAGGER:
            if (o->oTimer == 0) {
                cur_obj_init_animation_with_sound(HUMANOID_ANIM_STAGGER);
            }
            break;
    }

    k_generic_enemy_handler();
}

void bhv_k_shieldo(void) {
    o->oAnimState = 1;
    k_generic_enemy_init();

    switch(o->oAction) {
        case K_ENEMY_IDLE:
            o->oAction = K_ENEMY_PATROL_RUN;
            break;
        case K_ENEMY_PATROL_IDLE:
        case K_ENEMY_PATROL_RUN:
            if (o->oTimer > 20 && o->oDistanceToMario < 1000.0f) {
                o->oAction = K_ENEMY_SHOOT;
            }
            k_enemy_stagger_vulnerable();
            break;
        case K_ENEMY_CHASE:
            if (o->oDistanceToMario < 1000.0f) {
                o->oAction = K_ENEMY_SHOOT;
            }
            k_enemy_staggerable();
            break;
        case K_ENEMY_SHOOT:
            {
                Vec3f bullet_origin = //where the bullet spawns relative to the enemy
                {o->oPosX+(sins(o->oFaceAngleYaw)*50.0f)+(sins(o->oFaceAngleYaw-0x4000)*-40.0f),
                o->oPosY+100.0f,
                o->oPosZ+(coss(o->oFaceAngleYaw)*50.0f)+(coss(o->oFaceAngleYaw-0x4000)*-40.0f)};

                o->oForwardVel = 0.0f;
                o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw,obj_angle_to_object(o,gMarioObject),4);

                if ((lateral_dist_between_objects(o,gMarioObject) < 250.0f)&&(gMarioState->pos[1] > o->oPosY+160.0f)) {
                    o->oAction = K_ENEMY_BLOCKUP;
                }

                if (o->oTimer == 0) {
                    //ensure the first frame is the slow cond
                    cur_obj_init_animation_with_sound(HUMANOID_ANIM_SHOOT);
                }
                if (o->header.gfx.animInfo.animFrame == 11) {
                    o->oAnimState = 0;
                    cur_obj_play_sound_2(SOUND_OBJ2_EYEROK_SOUND_LONG);

                    o->oFaceAnglePitch = -obj_turn_pitch_toward_mario(0.0f, 0x2000);
                    dobj_spawn_bullet(bullet_origin,o->oFaceAnglePitch,o->oFaceAngleYaw);
                    o->oFaceAnglePitch = 0;
                }

                if (o->oDistanceToMario > 1100.0f) {
                    o->oAction = K_ENEMY_CHASE;
                }

                if (obj_hit_by_deflected_bullet(o, 200.0f)) {
                    o->oAction = K_ENEMY_STAGGER;
                    o->oTimer = 0;
                    cur_obj_play_sound_2(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL);
                }

                o->oInteractType = INTERACT_DAMAGE;
                o->oDamageOrCoinValue = 0;

                k_enemy_shielded();
            }
            break;
        case K_ENEMY_BLOCKUP:

            o->oForwardVel = 0.0f;
            o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw,obj_angle_to_object(o,gMarioObject),4);
            cur_obj_init_animation_with_sound(HUMANOID_ANIM_BLOCKUP);

            o->oInteractType = INTERACT_BOUNCE_TOP;
            o->oDamageOrCoinValue = 0;

            if (gMarioState->pos[1] < o->oPosY + 20.0f) {
                o->oAction = K_ENEMY_SHOOT;
            }

            k_enemy_shielded();
            break;
        case K_ENEMY_STAGGER:
            if (o->oTimer == 0) {
                cur_obj_init_animation_with_sound(HUMANOID_ANIM_SHIELDBLOCK);
            }
            break;
    }

    k_generic_enemy_handler();
}

void bhv_k_electrohead(void) {
    k_generic_enemy_init();

    switch(o->oAction) {
        case K_ENEMY_IDLE:
            k_enemy_vulnerable();

            if ((o->oDistanceToMario < 1000.0f) && gMarioState->pos[1] < o->oPosY + 10.0f && gMarioState->pos[1] > o->oPosY - 10.0f && o->oHealth == 0) {
                if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP, DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, DIALOG_K_ELECTROHEAD)) {
                    o->oHealth = 1;
                }
            }
        break;
        case K_ENEMY_DIE:
            if (o->oTimer == 60) {
                spawn_default_star(o->oPosX,o->oPosY+100.0f,o->oPosZ);
            }
            if (o->oTimer > 70) {
                if (o->oHealth == 1) {
                    if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP, DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, DIALOG_K_ELECTROHEAD_DEAD)) {
                        o->oHealth = 2;
                    }
                }
            }
        break;
    }

    k_generic_enemy_handler();
}

void bhv_k_billionare(void) {
    k_generic_enemy_init();
    s16 home_angle = o->oMoveAngleYaw;

    switch(o->oAction) {
        case K_ENEMY_IDLE:
            k_enemy_vulnerable();
            o->oMoveAngleYaw = home_angle;
            if (o->oTimer % 30 == 0) {
                spawn_object_relative(0, 0.0f, 50.f, 100.0f, o, MODEL_BURN_SMOKE, bhvBlackSmokeHoodboomer);
            }
        break;
        case K_ENEMY_DIE:
            if (o->oTimer == 120) {
                spawn_default_star(1081, -3124, 430);
            }
        break;
    }

    k_generic_enemy_handler();
}

Vec3f k_tv_dumpspots[] = {
    {-984, 21, 2385},
    {-2133, 21, 1112},
    {-2133, 21, -1112},
    {-984, 21, -2385}
};

u8 tv_target_state = 0;
u8 tv_state = 0;
u8 tv_timer = 0;

u8 enemy_spawn_index = 0;
u8 enemy_spawn_table[] = {
    0,0,1,1,2,0,2,0,0,0
};

struct Object * tv_aimer;
void bhv_k_tv(void) {    
    switch(o->oAction) {
        case 0: //wait for mario
            tv_target_state = 0;
            tv_state = 0;
            tv_timer = 0;
            enemy_spawn_index = 0;
            if (o->oDistanceToMario < 1500.0f) {
                //talk to him
                tv_state = 1;
                tv_target_state = 1;
                if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP, DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, DIALOG_K_TV_START)) {
                    o->oAction = 1;
                    tv_aimer = spawn_object(o,MODEL_WATCH_AIM,bhvKtvAim);
                    k_kill_counter = 0;
                }
            }
            break;
        case 1: // phase 1: avoid the aimer only
            if (o->oTimer>120) {
                o->oAction = 2;
            }
            break;
        case 2: // phase 2: dodge
            if (o->oTimer % 90 == 0&&(o->oTimer <600)) {
                f32 ratio = 0.1f + (o->oTimer*.001f);
                int pounder_count = 0;
                for (int x = -6; x <= 6; x++) {
                    for (int z = 1; z <= 5; z++) {
                        if (pounder_count>80) {
                            break;
                        }
                        if (random_float() <= ratio) {
                            struct Object * pounder = spawn_object(o,MODEL_NONE,bhvKpounder);
                            pounder->oPosZ = x*400.0f;
                            pounder->oPosX = (z*-400.0f)+100.0f;
                            pounder_count++;
                        }
                    }
                }
            }
            if (gMarioState->pos[0] > -100.0f) {
                gMarioState->pos[0] = -100.0f; //keep mario in crush zone
            }
            if (o->oTimer>600&&(!cur_obj_nearest_object_with_behavior(bhvKpounder))) {
                o->oAction = 3;
            }
            break;
        case 3: // phase 3: fight
            if (o->oTimer < 600 &&(o->oTimer % 90 == 0)) {
                k_kill_counter --;
                struct Object * enemy;
                u16 random_enemy = enemy_spawn_table[enemy_spawn_index];
                switch(random_enemy) {
                    case 0:
                        enemy = spawn_object(o,MODEL_K_STRONG_TERRY,bhvStrongTerry);
                        break;
                    case 1:
                        enemy = spawn_object(o,MODEL_K_SKINNY_RICKY,bhvSkinnyRicky);
                        break;
                    case 2:
                        enemy = spawn_object(o,MODEL_K_SHIELDO,bhvShieldo);
                        break;
                }
                vec3f_copy(&enemy->oPosVec,k_tv_dumpspots[random_u16()%4]);
                enemy->oMoveAngleYaw = random_u16();
                enemy_spawn_index++;
            }

            if ((o->oTimer>610)&&(k_kill_counter == 0)) {
                o->oAction = 4;
            }
            break;
        case 4: //end of fight
            if (tv_aimer) {
                mark_obj_for_deletion(tv_aimer);
                tv_aimer = NULL;
            }
            if (o->oTimer > 30) {
                if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP, DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, DIALOG_K_TV_END)) {
                    o->oAction = 5;
                    spawn_default_star(o->oPosX+1000.0f,o->oPosY-300.0f,o->oPosZ);
                    tv_state = 0;
                    tv_target_state = 0;
                }
            }
            break;
    }

    o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_K_TV_1];
    if (tv_state != tv_target_state) {
        tv_timer++;
        if (tv_timer > 5) {
            tv_timer = 0;
            tv_state = tv_target_state;
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_K_TV_1+tv_state];
        }
    } else {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_K_TV_1+tv_state];
    }
}

void bhv_k_tv_aim(void) {
    f32 base_speed = 0.0f;

    switch(o->oAction) {
        case 0: //chase mario
            base_speed = 22.0f;
            if (o->oTimer > 90) {
                o->oAction=1;
                tv_target_state = 2;
            }
            break;
        case 1: //fire
            base_speed = 5.0f;
            cur_obj_hide();
            if ((o->oTimer/2)%2 == 0) {
                cur_obj_unhide();
            }
            if (o->oTimer > 10) {
                e__sg_smoke(&o->oPosVec);

                tv_state = 3;
                tv_target_state = 3;
                if (o->oDistanceToMario < 100.0f) {
                    Vec3f blood_cast_ray = {0.0f,-400.0f,0.0f};
                    gMarioState->pos[1] += 5.0f;
                    blood_cast(gMarioState->pos,blood_cast_ray);
                    gMarioState->pos[1] -= 5.0f;

                    set_mario_action(gMarioState,ACT_HARD_BACKWARD_GROUND_KB,0);
                    gMarioState->health = 0xFF; //die
                }
                cur_obj_play_sound_2(SOUND_OBJ2_EYEROK_SOUND_LONG);
                o->oAction = 2;
                cur_obj_hide();
            }
            break;
        case 2: //wait and refresh
            if (o->oTimer == 3) {
                tv_state = 2;
                tv_target_state = 2;
            }
            if (o->oTimer > 40) {
                tv_target_state = 1;
                o->oAction = 0;
                cur_obj_unhide();
                vec3f_copy(&o->oPosVec,gMarioState->pos);
            }
            break;
    }

    f32 speed = base_speed;
    if (o->oDistanceToMario < 100.0f) {
        speed = (o->oDistanceToMario/100.0f)*base_speed;
    }
    Vec3f govec;
    vec3f_diff(govec,&gMarioState->pos,&o->oPosVec);
    vec3f_normalize(govec);
    vec3_mul_val(govec,speed);
    vec3f_sum(&o->oPosVec,&o->oPosVec,govec);
}

void bhv_k_pounder(void) {
    switch(o->oAction) {
        case 0://init
            o->oPosY = 0.0f;
            o->prevObj = spawn_object(o,MODEL_K_LITE,bhvStaticObject);
            o->prevObj->oOpacity = 0;
            o->oPosY = 1500.0f;
            o->oAction = 1;
            break;
        case 1: //telegraph
            o->prevObj->oOpacity = approach_f32_asymptotic(o->prevObj->oOpacity,255.0f,.2f);
            if (o->oTimer > 30) {
                o->oAction = 2;
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_K_POUNDER];
            }
            break;
        case 2: //pound
            o->oPosY -= 50.0f;
            if (o->oPosY < 3.0f) {
                o->oPosY = 3.0f;
                o->oAction = 3;
                mark_obj_for_deletion(o->prevObj);
                cur_obj_play_sound_2(SOUND_OBJ_POUNDING_LOUD);
            }
            break;
        case 3: //wait and raise
            if (o->oTimer > 20) {
                o->oPosY += 20.0f;
                if (o->oPosY > 1500.0f) {
                    mark_obj_for_deletion(o);
                }
            }
        break;
    }
}

#define PERSONAL_SPACE_DIST 300.0f
void bhv_dancer(void) {
    int anim = GET_BPARAM1(o->oBehParams);
    if (o->oTimer == 0) {
        o->oFaceAngleYaw = random_u16();
        o->oGraphYOffset += o->oBehParams2ndByte * 2.0f;

        if (anim != 0) {
            cur_obj_init_animation_with_sound(anim);
        } else {
            cur_obj_init_animation_with_sound(random_u16()%2);
        }
    }
    o->oMoveAngleYaw = approach_s16_asymptotic(o->oAngleToMario + 0x8000,o->oAngleVelYaw,64);

    f32 backawayamount = 0.0f;
    if (o->oDistanceToMario <= PERSONAL_SPACE_DIST) {
        backawayamount = (PERSONAL_SPACE_DIST-o->oDistanceToMario)/PERSONAL_SPACE_DIST;
    }
    o->oPosX = o->oHomeX + sins(o->oMoveAngleYaw)*PERSONAL_SPACE_DIST*backawayamount;
    o->oPosZ = o->oHomeZ + coss(o->oMoveAngleYaw)*PERSONAL_SPACE_DIST*backawayamount;

    if (anim == 4) {
        cur_obj_scale(0.5f);
        o->oFaceAngleYaw += 0x400;
        if (o->header.gfx.animInfo.animFrame > 80) {
            o->oFaceAngleYaw += 0x400;
        }
    }
}