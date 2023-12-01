Vec3f ball_Size = {100.0f,100.0f,100.0f};

struct MeshInfo Ball_Mesh = {
    NULL,
    NULL,
    NULL,
    NULL,
    0, // Number of vertices
    0,
    0,
    0
};

static struct ObjectHitbox sMarbleHitbox = {
    /* interactType:      */ INTERACT_NONE,
    /* downOffset:        */ 50,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 60,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 100,
    /* hurtboxHeight:     */ 100,
};

void bhv_marble_init(void) {
    struct RigidBody *body = allocate_rigid_body_from_object(o, &Ball_Mesh, 1.f, ball_Size, FALSE);
    vec3f_copy(body->linearVel,gMarioState->vel);
    if ((gMarioState->floor->normal.y > 0.99f) && (!cur_obj_has_model(MODEL_MARBLE))) body->asleep = TRUE;
}

u8 underwater = FALSE;
void bhv_marble_loop(void) {    
    Vec3f move_force = {
        (sins(gMarioState->intendedYaw) * gMarioState->intendedMag)/10.0f,
        0.0f,
        (coss(gMarioState->intendedYaw) * gMarioState->intendedMag)/10.0f,
    };
    Vec3f push_position = {
        o->oPosX + (sins(gMarioState->intendedYaw+0x8000) * 50.0f),
        0.0f,
        o->oPosZ + (coss(gMarioState->intendedYaw+0x8000) * 50.0f),
    };

    //this code is so that the camera is responsive and looks slightly ahead of the hamsterball
    Vec3f marble_go_vec = { o->oPosX + o->rigidBody->linearVel[0],0.0f, o->oPosZ + o->rigidBody->linearVel[2]};
    s16 marble_go_angle;
    vec3f_get_yaw(&o->oPosVec, marble_go_vec, &marble_go_angle);
    gMarioState->faceAngle[1] = marble_go_angle;

    //if ( vec3_mag(o->rigidBody->linearVel) < 20.0f) {
        //rigid_body_add_force(o->rigidBody, push_position, move_force, TRUE);
    //}

    if (gMarioState->intendedMag > 2.f || gMarioState->floor->normal.y < 0.99f) {
        o->rigidBody->asleep = FALSE;
        o->rigidBody->motion = 10.f;
        vec3f_add(o->rigidBody->linearVel, move_force);
    }

    struct Surface *floor;
    f32 water_level = find_water_level_and_floor(o->oPosX,o->oPosY,o->oPosZ, &floor);

    if (water_level > o->oPosY) {
        o->rigidBody->linearVel[1] += 5.0f;//buoyancy
        vec3_mul_val(o->rigidBody->linearVel,0.94f);//drag
        vec3_mul_val(o->rigidBody->angularVel,0.94f);
        if (!underwater) {
            underwater = TRUE;
            if (o->rigidBody->linearVel[1] < -4.0f) {
                cur_obj_play_sound_2(SOUND_ACTION_WATER_PLUNGE);
            }
        }
    } else {
        underwater = FALSE;
    }

    //break upon contact with lava / quicksand
    f32 fheight = find_floor(o->oPosX,o->oPosY,o->oPosZ, &floor);
    if (floor && fheight+120.0f > o->oPosY && (floor->type == SURFACE_BURNING || floor->type == SURFACE_INSTANT_QUICKSAND || floor->type == SURFACE_DEATH_PLANE)) {
        change_ability(ABILITY_DEFAULT);
    }


    vec3f_copy(&gMarioObject->oPosVec,&o->oPosVec);
    vec3f_copy(gMarioState->pos,&o->oPosVec);
    vec3f_copy(gMarioState->vel,&o->rigidBody->linearVel);

    //obj_set_hitbox(o, &sMarbleHitbox);
    //o->oInteractStatus = 0;
    //o->oIntangibleTimer = 0;

    /*
    for (int i = 0; i < o->numCollidedObjs; i++) {
        struct Object *other = o->collidedObjs[i];
        if (other != gMarioObject) {
            cur_obj_play_sound_2(SOUND_GENERAL_EXPLOSION7);
            attack_object(other, 2);
        }
    }
    */
}

void bhv_marble_cannon_loop(void) {
    struct Object * marble = cur_obj_nearest_object_with_behavior(bhvPhysicsMarble);

    if ((marble)&&(dist_between_objects(o,marble) < 10.0f)&&(vec3_mag(marble->rigidBody->linearVel)<1.0f)) {
        if (o->oTimer < 90) {
            cur_obj_play_sound_2(SOUND_OBJ_POUNDING_CANNON);
            marble->rigidBody->asleep = FALSE;
            marble->rigidBody->linearVel[1] = 300.0f;
            o->oTimer = 0;
        }
    } else {
        o->oTimer = 0;
    }
}