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

    if (o->oDistanceToMario < 2000.0f) {
        //cur_obj_play_sound_1(SOUND_AIR_BLOW_FIRE);
    }

    if (gMarioState->wall && gMarioState->wall->object) {
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

static struct ObjectHitbox sKEnemyHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 1,
    /* numLootCoins:      */ 3,
    /* radius:            */ 60,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 60,
    /* hurtboxHeight:     */ 160,
};

enum {
    K_ENEMY_INIT,
    K_ENEMY_IDLE,
    K_ENEMY_DIE
};

void k_kill_enemy(void) {
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

    cur_obj_init_animation_with_sound(2);

    for (u8 i=0; i<4; i++) {
        osRecvMesg(&gGameVblankQueue, &gMainReceivedMesg, OS_MESG_BLOCK);
    }
}

void k_enemy_vulnerable(void) {
    if (o->oShotByShotgun > 0) {
        k_kill_enemy();
    }
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
            k_kill_enemy();
        } else {

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
    cur_obj_move_standard(78);

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
    }

    o->oInteractStatus = INTERACT_NONE;
    o->oShotByShotgun = 0;
}

void bhv_k_strong_terry(void) {
    k_generic_enemy_init();

    switch(o->oAction) {
        case K_ENEMY_IDLE:
            k_enemy_vulnerable();
        break;
    }

    k_generic_enemy_handler();
}

void bhv_k_electrohead(void) {
    k_generic_enemy_init();

    switch(o->oAction) {
        case K_ENEMY_IDLE:
            k_enemy_vulnerable();
        break;
        case K_ENEMY_DIE:
            if (o->oTimer == 60) {
                spawn_default_star(o->oPosX,o->oPosY+100.0f,o->oPosZ);
            }
        break;
    }

    k_generic_enemy_handler();
}