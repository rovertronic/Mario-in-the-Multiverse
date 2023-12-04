static struct ObjectHitbox sCutterBladeHitbox = {
    /* interactType:      */ INTERACT_NONE,
    /* downOffset:        */ 50,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 80,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 20,
    /* hurtboxHeight:     */ 20,
};

static struct ObjectHitbox sEnemyCutterBladeHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 50,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 80,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 70,
    /* hurtboxHeight:     */ 30,
};

void bhv_cutter_blade_init(void) {
    o->oForwardVel = 70.0f;
    o->oGravity = 0.0f;

    play_sound(SOUND_ABILITY_CUTTER_THROW, o->header.gfx.cameraToObject);
    if (o->parentObj == gMarioObject) {
        obj_set_hitbox(o, &sCutterBladeHitbox);
    } else {
        obj_set_hitbox(o, &sEnemyCutterBladeHitbox);
    }
}

void bhv_cutter_blade_loop(void) {

    switch (o->oAction) {
        case 0:
            o->oFaceAngleYaw += 0x2000;
            o->oForwardVel -= 3.0f;
            if (o->oForwardVel <= 0) {
                o->oForwardVel = 0.0f;
                o->oAction++;
            }
            break;
        case 1:
            o->oFaceAngleYaw += 0x2000;
            if (o->oTimer >= 15) {
                o->oAction++;
            }
            break;
        case 2:
            o->oFaceAngleYaw += 0x2000;
            o->oForwardVel -= 2.0f;
            if (o->oTimer >= 50 || o->oDistanceToMario > 2000) {
                o->oAngleVelYaw = 0x800;
                o->oAngleVelPitch = random_u16() / 64;
                o->oAngleVelRoll = random_u16() / 64;
                o->oAction++;
            }
            break;
        case 3:
            o->oGravity = 1.0f;
            o->oForwardVel *= 0.8f;

            o->oFaceAngleYaw += o->oAngleVelYaw;
            o->oFaceAngleRoll += o->oAngleVelRoll;
            o->oFaceAnglePitch += o->oAngleVelPitch;

            o->oAngleVelYaw *= 0.9f;
            o->oAngleVelRoll *= 0.9f;
            o->oAngleVelPitch *= 0.9f;

            if (o->oTimer == 30) {

                spawn_mist_particles_variable(8, 10, 5.0f);
                obj_mark_for_deletion(o);
            }
            break;
    }

    struct Surface *surf;
    Vec3f originPos;
    Vec3f hitpos;
    Vec3f raydir;
    u8 rayResult = 0;

    raydir[0] = sins(o->oMoveAngleYaw) * o->oForwardVel;
    raydir[1] = 0.0f;
    raydir[2] = coss(o->oMoveAngleYaw) * o->oForwardVel;

    vec3f_set(hitpos, 0.0f, 0.0f, 0.0f);

    vec3f_set(originPos, o->oPosX, o->oPosY, o->oPosZ);
    // wall check
    find_surface_on_ray(originPos, raydir, &surf, hitpos, 2U);
    if (surf != NULL)
        rayResult = 1;
    // floor check
    raydir[1] -= 20.0f;
    find_surface_on_ray(originPos, raydir, &surf, hitpos, 1U);
    if (surf != NULL)
        rayResult = 2;
    // ceil check
    raydir[1] += 40.0f;
    find_surface_on_ray(originPos, raydir, &surf, hitpos, 4U);
    if (surf != NULL)
        rayResult = 3;

    if (rayResult > 0) {
        if (o->oAction == 0) {
            o->oForwardVel = 0.0f;
            o->oAction = 1;
        } else if (o->oAction == 2) {
            o->oAction = 3;
            if (rayResult == 2)
                o->oVelY = 10.0f;
            if (rayResult == 3)
                o->oVelY = -10.0f;
            o->oAngleVelYaw = 0x800;
            o->oAngleVelPitch = random_u16() / 64;
            o->oAngleVelRoll = random_u16() / 64;
            o->oForwardVel *= -0.05f;
        }
    }

    if (object_step() & OBJ_COL_FLAG_HIT_WALL) {
        o->oForwardVel *= -0.05f;
        o->oAngleVelYaw = 0x800;
        o->oAngleVelPitch = random_u16() / 64;
        o->oAngleVelRoll = random_u16() / 64;
        o->oAction = 3;
    }

    o->oInteractStatus = 0;
    for (int i = 0; i < o->numCollidedObjs; i++) {
        struct Object *other = o->collidedObjs[i];
        if (other != o->parentObj) {
            if (other != gMarioObject) attack_object(other, 2);
        } else if (o->oAction >= 2) {
            play_sound(SOUND_ABILITY_CUTTER_CATCH, o->header.gfx.cameraToObject);
            spawn_object_relative(0, 0, 100, 0, o->parentObj, MODEL_NONE, bhvSparkleSpawn);
            obj_mark_for_deletion(o);
        }
    }
}
