Vec3f miltank_ball_Size = {100.0f,100.0f,100.0f};

struct MeshInfo Miltank_Ball_Mesh = {
    NULL,
    NULL,
    NULL,
    NULL,
    0, // Number of vertices
    0,
    0,
    0
};

static struct ObjectHitbox sMiltankHitbox = {
    /* interactType:      */ INTERACT_J_MILTANK,
    /* downOffset:        */ 50,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 100,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 100,
    /* hurtboxHeight:     */ 100,
};

static struct SpawnParticlesInfo sMiltankParticlesInfo = {
    /* behParam:        */ 0,
    /* count:           */ 6,
    /* model:           */ MODEL_WHITE_PARTICLE,
    /* offsetY:         */ 0,
    /* forwardVelBase:  */ 5,
    /* forwardVelRange: */ 5,
    /* velYBase:        */ 10,
    /* velYRange:       */ 10,
    /* gravity:         */ -3,
    /* dragStrength:    */ 0,
    /* sizeBase:        */ 3.0f,
    /* sizeRange:       */ 5.0f,
};

// Mr. Blizzard particle spawner.
static void miltank_spawn_milk_particles(s8 count, s8 offsetY, s8 forwardVelBase, s8 velYBase, s8 sizeBase) {
    sMiltankParticlesInfo.count = count;
    sMiltankParticlesInfo.offsetY = offsetY;
    sMiltankParticlesInfo.forwardVelBase = forwardVelBase;
    sMiltankParticlesInfo.velYBase = velYBase;
    sMiltankParticlesInfo.sizeBase = sizeBase;
    cur_obj_spawn_particles(&sMiltankParticlesInfo);
}

void bhv_miltank_init(void) {
    struct RigidBody *body = allocate_rigid_body_from_object(o, &Miltank_Ball_Mesh, 1.0f, miltank_ball_Size, FALSE);
    if (o->oFloor->normal.y > 0.99f) body->asleep = TRUE;
    obj_set_hitbox(o, &sMiltankHitbox);

    struct Object *miltankStar = cur_obj_nearest_object_with_behavior(bhvMiltankStar);

    if (miltankStar != NULL){
        o->parentObj = miltankStar;
    }
}

void bhv_miltank_loop(void) {    
    /*Vec3f move_force = {
        (sins(gMarioState->intendedYaw) * gMarioState->intendedMag)/10.0f,
        0.0f,
        (coss(gMarioState->intendedYaw) * gMarioState->intendedMag)/10.0f,
    };
    Vec3f push_position = {
        o->oPosX + (sins(gMarioState->intendedYaw+0x8000) * 50.0f),
        0.0f,
        o->oPosZ + (coss(gMarioState->intendedYaw+0x8000) * 50.0f),
    };*/



    //if ( vec3_mag(o->rigidBody->linearVel) < 20.0f) {
        //rigid_body_add_force(o->rigidBody, push_position, move_force, TRUE);
    //}

    if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED && o->oTimer > 5 && o->oTimer > 5){
        Vec3f force;
        force[0] = (sins(gMarioState->faceAngle[1]) * 125.0f);
        force[2] = (coss(gMarioState->faceAngle[1]) * 125.0f);
        force[1] = 150.0f;
        rigid_body_add_force(o->rigidBody, &gMarioState->pos, force, TRUE);
        miltank_spawn_milk_particles(8, -10, 15, 20, 10);
        cur_obj_play_sound_2(SOUND_OBJ_DIVING_IN_WATER);
        cur_obj_play_sound_2(SOUND_MITM_LEVEL_J_MILTANK);
        o->oTimer = 0;
    }

    if (o->oFloor->normal.y < 0.99f) {
        o->rigidBody->asleep = FALSE;
        o->rigidBody->motion = 10.f;
    }

    struct Surface *floor;

    //break upon contact with lava / quicksand
    /*f32 fheight = find_floor(o->oPosX,o->oPosY,o->oPosZ, &floor);
    if (floor && fheight+120.0f > o->oPosY && (floor->type == SURFACE_BURNING || floor->type == SURFACE_INSTANT_QUICKSAND || floor->type == SURFACE_DEATH_PLANE)) {
        gMarioState->abilityId = ABILITY_DEFAULT;
    }*/

    


    obj_set_hitbox(o, &sMiltankHitbox);
    o->oInteractStatus = 0;
    o->oIntangibleTimer = 0;

    if (o->oPosX <= -6630 && o->oPosX >= -9930 && o->oPosZ >= -550 && o->oPosZ <= 2150 && o->oPosY <= 400 && o->oInPen == 0){
        o->parentObj->oMiltankInPen += 1;
        o->oInPen = 1;
        //o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    } else if ((o->oPosX > -6630 || o->oPosX < -9930 || o->oPosZ < -550 || o->oPosZ > 2150 || o->oPosY > 400 || o->oPosY < 200) && o->oInPen == 1){
        o->oInPen = 0;
        o->parentObj->oMiltankInPen--;
        //o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}



void bhv_miltank_star_loop(void) {
    if (o->oMiltankInPen == 5){
        spawn_no_exit_star(o->oPosX, o->oPosY, o->oPosZ);
        spawn_mist_particles();
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
    //print_text_fmt_int(20,50, "PEN %d", o->oMiltankInPen);
}