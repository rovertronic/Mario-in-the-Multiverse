void blood_cast(Vec3f * start, Vec3f * ray) {
    s16 blood_count = count_objects_with_behavior(bhvKblood);
    if (blood_count > 100) {
        return;
    }

    Vec3f hitpos;
    struct Surface * surf;
    find_surface_on_ray(start,ray,&surf,hitpos,RAYCAST_FIND_WALL | RAYCAST_FIND_FLOOR);

    if (surf&&!surf->object) {
        struct Object * blood = spawn_object(o,MODEL_K_BLOOD,bhvKblood);
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
        cur_obj_play_sound_1(SOUND_AIR_AMP_BUZZ);
    }

    if (gMarioState->wall && gMarioState->wall->object) {
        play_sound(SOUND_MARIO_ATTACKED, gMarioState->marioObj->header.gfx.cameraToObject);
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
        s16 roll = (random_u16()%4);
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