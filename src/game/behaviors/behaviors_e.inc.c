
#include "levels/e/header.h"





//-- *** Level ***

extern const struct Animation *const ukiki_seg5_anims_05015784[];


/* Animation order *
idle, roaming, attacked, range_or_close, close, death
*/

#define E_ENEMY_TYPE_COUNT 8

#define E_SET_ROAMING_SOUND_DELAY() \
    o->oEERoamingSoundDelay = (60 + (random_u16() / 250));

#define E_SET_ATTACK_DELAY(attackRate) \
    o->oEEAttackDelay = (attackRate * (random_u16() / 4000));

#define E_SET_MOVE_DIR()               \
    o->oEEGoalVelX = (sins(o->oMoveAngleYaw) * enemyClass->speed);\
    o->oEEGoalVelZ = (coss(o->oMoveAngleYaw) * enemyClass->speed);

#define E_RANDOM_SOUND(sound) (*(((u32 *)(&sound)) + (random_u16() & 1)))


#define oEEMovementTimer     OBJECT_FIELD_S32(0x1B)
#define oEEGoalVelX          OBJECT_FIELD_F32(0x1C)
#define oEEGoalVelZ          OBJECT_FIELD_F32(0x1D)
#define oEEAttackDelay       OBJECT_FIELD_S32(0x1E)
#define oEERoamingSoundDelay OBJECT_FIELD_S32(0x1F)
#define oEERoamingSoundTimer OBJECT_FIELD_S32(0x20)
#define oEETurnedFromWall    OBJECT_FIELD_S32(0x21)
#define oEETargetObj         OBJECT_FIELD_OBJ(0x22)
#define oEEDistToTarget      oHomeX


enum {
    EE_ACT_INIT,
    EE_ACT_IDLE,
    EE_ACT_ROAMING,
    EE_ACT_ATTACK,
    EE_ACT_ATTACKED
};

enum {
    E_MOVE_STEP_NONE,
    E_MOVE_STEP_WALL,
    E_MOVE_STEP_EDGE,
    E_MOVE_STEP_ENEMY
};

static struct E_EnemyClass {
    u32 alertSound,   alertSound2,
        roamingSound, roamingSound2,
        damageSound,  damageSound2,
        deathSound,   deathSound2;
    struct Animation **anims;
    f32 hitboxRadius, hitboxHeight;
    f32 speed;
    s32 (*attackAction)(void);
    u8 health;
    u8 stunChance;
    u8 lootCoins;
    u8 attackRate : 5;
    u8 fly   : 1;
    u8 close : 1;
    u8 range : 1;
};




//--Enemy-specific

//caco
static s32 e__caco_attack(void) {
    cur_obj_init_animation(3);

    o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw, obj_angle_to_object(o, o->oEETargetObj), 5);

    if (o->oTimer == 0) {//--**temp
        cur_obj_set_model(MODEL_ID_04);
    } else if (o->oTimer == 12) {
        cur_obj_set_model(MODEL_ID_03);
    }

    if (o->oTimer == 5) {
        //--**bullet
        //-if (dist_between_objects(o, o->oEETargetObj) < 400.f) {//close attack
        o->oFaceAngleYaw   = calculate_yaw(&o->oPosX, gMarioState->pos);
        o->oFaceAnglePitch = calculate_pitch(&o->oPosX, gMarioState->pos);
        spawn_object_relative(0, 0, 140, 140, o, MODEL_ID_05, bhvSnufitBalls);
        o->oFaceAnglePitch = 0;
    } else if (o->oTimer == 24) {
        return TRUE; }

    return FALSE;
}




static struct E_EnemyClass sE_EnemyClasses[E_ENEMY_TYPE_COUNT] = {
    //pistol

    //chaingun

    //lost soul

    //caco
    { SOUND_MITM_LEVEL_E_CACO_ALERT,  SOUND_MITM_LEVEL_E_CACO_ALERT2,
    SOUND_MITM_LEVEL_E_CACO_ALERT,    SOUND_MITM_LEVEL_E_CACO_ALERT2,//--**
    SOUND_MITM_LEVEL_E_CACO_DAMAGE,   SOUND_MITM_LEVEL_E_CACO_DAMAGE2,
    SOUND_MITM_LEVEL_E_CACO_DEATH,    SOUND_MITM_LEVEL_E_CACO_DEATH2,
    &caco_anims, 140.f, 280.f, 15.f, &e__caco_attack,   (3 * 4), 50, 4, 3,   1, 1, 1 },

    //revenant

    //mancubus

    //mastermind

};



//--Process

static s32 e__enemy_raycast(void) {
    if (o->oEEDistToTarget < 4000.f) {
        struct Surface *surf;
        Vec3f orig = { o->oPosX, (o->oPosY + (o->hitboxHeight * 0.5f)), o->oPosZ }; 
        Vec3f soundSource = { o->oEETargetObj->oPosX, (o->oEETargetObj->oPosY + 80.f), o->oEETargetObj->oPosZ };
        Vec3f hitPos, dir = { (soundSource[0] - orig[0]), (soundSource[1] - orig[1]), (soundSource[2] - orig[2]) };

        find_surface_on_ray(orig, dir, &surf, hitPos, (RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL | RAYCAST_FIND_WALL));//--**no water (keep depending on level)
        if (!surf) {
            return TRUE; }
    }
    return FALSE;
}

static s32 e__alerted_sound(void) {
    if ((gE_ShotgunTimer == 25)) {//--**|| mario makes a sound
        return e__enemy_raycast(); }
    return FALSE;
}

static s32 e__alerted_sight(void) {
    if ((random_u16() / 6553) == 0) {
        if (abs_angle_diff(obj_angle_to_object(o, gMarioObject), o->oFaceAngleYaw) < DEGREES(90)) {
            return e__enemy_raycast(); }
    }
    return FALSE;
}

static void e__attacked_common(void) {
    struct E_EnemyClass *enemyClass = &sE_EnemyClasses[o->oBehParams2ndByte];
    if (o->oHealth <= 0) {
        play_sound(E_RANDOM_SOUND(enemyClass->deathSound), o->header.gfx.cameraToObject); }
    else {
        play_sound(E_RANDOM_SOUND(enemyClass->damageSound), o->header.gfx.cameraToObject); }

    //stun
    if ((o->oAction == EE_ACT_IDLE) || ((random_u16() / 655) > enemyClass->stunChance)) {
        cur_obj_init_animation(2);
        o->oAction = EE_ACT_ATTACKED;
    }

    o->oEETargetObj = gMarioObject;
}
static void e__attacked_by_enemy(void) {
    e__attacked_common();

    //non-shotgun death
    if (o->oHealth <= 0) {
        obj_spawn_loot_yellow_coins(o, o->oNumLootCoins, 12.f);
        spawn_mist_particles();
        create_sound_spawner(o->oDeathSound);
        o->activeFlags = 0;
        return;
    }
}



static s32 e__movement_step(void) {
    s32 stepResult = E_MOVE_STEP_NONE;
    Vec3f nextPos = { o->oPosX, o->oPosY, o->oPosZ };
    vec3f_add(nextPos, &o->oVelX);

    //--**maybe 2nd cast at obj top
   //wall
    struct Surface *surf;
    f32 collDist = (o->hitboxRadius + (sE_EnemyClasses[o->oBehParams2ndByte].speed * 3.f));
    f32 offsetY  = ((o->hitboxHeight * 0.5f) - o->hitboxDownOffset);

    Vec3f orig = { nextPos[0], (nextPos[1] + offsetY), nextPos[2] };
    Vec3f hitPos, dir = { (sins(o->oMoveAngleYaw) * collDist), 0.f, (coss(o->oMoveAngleYaw) * collDist) };
    find_surface_on_ray(orig, dir, &surf, hitPos, (RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL | RAYCAST_FIND_WALL | RAYCAST_FIND_WATER));//--**?water

    if (surf != NULL) {
        o->oWallAngle = atan2s(surf->normal.z, surf->normal.x);
        return E_MOVE_STEP_WALL;
    }

   //edge
    struct Surface *nextFloor;
    f32 nextFloorHeight = find_floor(nextPos[0], (nextPos[1] + offsetY), nextPos[2], &nextFloor);
    if (nextFloor == NULL) {
        return E_MOVE_STEP_EDGE; }
    else if (sE_EnemyClasses[o->oBehParams2ndByte].fly == FALSE) {
        if (((o->oFloorHeight - nextFloorHeight) > 150.f) || (nextFloor->normal.y < 0.7071067f)) {
            return E_MOVE_STEP_EDGE; }
    }

    f32 objTop     = ((nextPos[1] + o->hitboxHeight) - o->hitboxDownOffset);
    f32 ceilHeight = find_ceil(nextPos[0], objTop, nextPos[2], &surf);
    if (objTop > ceilHeight) {
        nextPos[1] = (ceilHeight - o->hitboxHeight); }

    if (nextPos[1] < (nextFloorHeight + o->hitboxDownOffset)) {
        nextPos[1] = (nextFloorHeight + o->hitboxDownOffset); }

   //enemy collision
    if (o->collidedObjs[0] != NULL) {
        BehaviorScript behavior = o->collidedObjs[0]->behavior;
        if ((behavior == segmented_to_virtual(bhvE_Caco))) {//--**add other enemy behaviors later
            stepResult = E_MOVE_STEP_ENEMY; }
    }


    vec3f_copy(&o->oPosX, nextPos);
    o->oFloorHeight = nextFloorHeight;
    o->oFloor       = nextFloor;
    return stepResult;
}

static void e__flying_movement(void) {
    o->oVelY = ((o->oEETargetObj->oPosY - (o->oPosY - o->hitboxDownOffset)));
    if (o->oVelY > 12.f) {
        o->oVelY = 12.f; }
    else if (o->oVelY < -12.f) {
        o->oVelY = -12.f; }
}



void bhv_e__enemy(void) {
    s32 hitByEnemyProjectile = ((o->oDistanceToMario < 500.f) && (gE_ShotgunTimer == 25));//--**shot by enemy bullet | Note: temp activation is source of '1HP at a time' glitch

    //attacked
    if (o->oShotByShotgun) {
        e__attacked_common();
        o->oShotByShotgun = 0;
    } else {
        if ((o->oIntangibleTimer == 0) && (o->oInteractStatus & INT_STATUS_WAS_ATTACKED)) {
            if (gMarioState->action == ACT_GROUND_POUND) {
                o->oHealth -= 2; }
            else {
                o->oHealth -= 1; }
            e__attacked_by_enemy();
            o->oIntangibleTimer = 18;

        } else if (hitByEnemyProjectile) {
            o->oHealth -= 1;//--**enemyBullet->damage
            e__attacked_by_enemy();
            if (o->oHealth == sE_EnemyClasses[o->oBehParams2ndByte].health) {
                o->oEETargetObj = cur_obj_nearest_object_with_behavior(bhvE_Caco); }//--**enemyBullet->enemy
        }
    }


    //reset target & check if target is defeated
    if (o->oEETargetObj != NULL) {
        if (o->oEETargetObj == gMarioObject) {
            if (gMarioState->health == 0) {
                o->oAction = EE_ACT_IDLE; }
        } else if (o->oEETargetObj->activeFlags == 0) {//--**make sure it works
            if (gMarioState->health == 0) {
                o->oAction = EE_ACT_IDLE; }
            else {
                o->oEETargetObj = gMarioObject; }
        }
    }


    switch (o->oAction) {
    case EE_ACT_INIT:
        o->oInteractType = INTERACT_E__DOOM_ENEMY;
        o->oIntangibleTimer = 0;
        o->oEEMovementTimer = 255;
        
      {
        struct E_EnemyClass *enemyClass = &sE_EnemyClasses[o->oBehParams2ndByte];

        E_SET_ROAMING_SOUND_DELAY()
        E_SET_ATTACK_DELAY(enemyClass->attackRate)   
        //-o->oDeathSound = E_RANDOM_SOUND(enemyClass->deathSound);//--**Maybe play death sound when shot, then have default obj death sound when disappearing
        o->oAnimations       = enemyClass->anims;
        o->hitboxRadius      = enemyClass->hitboxRadius;
        o->hurtboxRadius     = enemyClass->hitboxRadius;
        o->hitboxHeight      = enemyClass->hitboxHeight;
        o->hurtboxHeight     = enemyClass->hitboxHeight;
        //-o->hitboxDownOffset  = enemyClass->offsetY;//--**remove hitboxDownOffset implementation
        o->oHealth           = enemyClass->health;
        o->oNumLootCoins     = enemyClass->lootCoins;
        o->oEETargetObj = gMarioObject;
      }
        cur_obj_init_animation(0);
        o->oAction = EE_ACT_IDLE;
        break;



    case EE_ACT_IDLE:
        cur_obj_init_animation(0);

        if ((o->oDistanceToMario < (o->hitboxRadius * 1.5f))
            || e__alerted_sight() || e__alerted_sound()) {
            play_sound(E_RANDOM_SOUND(sE_EnemyClasses[o->oBehParams2ndByte].alertSound), o->header.gfx.cameraToObject);
            cur_obj_init_animation(1);
            o->oAction = EE_ACT_ROAMING;
        }
        break;



    case EE_ACT_ROAMING:
        ;
        struct E_EnemyClass *enemyClass = &sE_EnemyClasses[o->oBehParams2ndByte];

        //movement
        f32 approach = (enemyClass->speed * 0.2f);
        o->oVelX = approach_f32(o->oVelX, o->oEEGoalVelX, approach, approach);
        o->oVelZ = approach_f32(o->oVelZ, o->oEEGoalVelZ, approach, approach);

        switch (e__movement_step()) {
        case E_MOVE_STEP_EDGE:
            o->oMoveAngleYaw += (DEGREES(180) + (random_u16() / 4));
            o->oVelX = (o->oVelZ = 0.f);
            goto move_dir;

        case E_MOVE_STEP_WALL:
            if (enemyClass->fly) {
                o->oEETurnedFromWall = TRUE; }
            o->oMoveAngleYaw = (o->oWallAngle + (random_u16() / 4));
            goto move_dir;

        case E_MOVE_STEP_ENEMY:
            o->oMoveAngleYaw = ((obj_angle_to_object(o, o->collidedObjs[0]) + DEGREES(180)) + (random_u16() / 4));
            move_dir:
            E_SET_MOVE_DIR()
            break;

        case E_MOVE_STEP_NONE:
          {
            //XZ
            s16 angleToTarget = obj_angle_to_object(o, o->oEETargetObj);
            if (((abs_angle_diff(angleToTarget, o->oFaceAngleYaw) > DEGREES(120)) && (o->oEEMovementTimer > 10))
                || (o->oEEMovementTimer++ > ((random_u16() / 200) + 20))) {
                o->oEEMovementTimer      = 0;
                o->oEETurnedFromWall = FALSE;
                if ((random_u16() % 6) == 0) {
                    o->oMoveAngleYaw = random_u16(); }
                else {
                    o->oMoveAngleYaw = angleToTarget; }
                E_SET_MOVE_DIR()
            }
            //Y
            if (enemyClass->fly) {
                //flying movement
                if ((lateral_dist_between_objects(o, o->oEETargetObj) < 1000.f) || o->oEETurnedFromWall) {
                    e__flying_movement(); }
                else {
                    o->oVelY = approach_f32_asymptotic(o->oVelY, 0.f, 0.25f); }
            } else {
                //falling
                if (o->oPosY == o->oFloorHeight) {
                    o->oVelY = 0.f; }
                else if (o->oVelY > -40.f) {
                    o->oVelY += -4.f; }
            }
          }
        }
        o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw, o->oMoveAngleYaw, 8);

        o->oEEDistToTarget = dist_between_objects(o, o->oEETargetObj);


        //sounds & attacks
        if (++o->oEERoamingSoundTimer == o->oEERoamingSoundDelay) {
            play_sound(E_RANDOM_SOUND(enemyClass->roamingSound), o->header.gfx.cameraToObject);
            o->oEERoamingSoundTimer = 0;
            E_SET_ROAMING_SOUND_DELAY()
        }

        s32 notFalling = TRUE;
        if (enemyClass->fly == FALSE) {
            if (o->oPosY != o->oFloorHeight) {
                notFalling = FALSE; }
        }
        s32 closeAttack = FALSE;
        if (enemyClass->close) {
            if (o->oEEDistToTarget < (o->hitboxRadius * 3.f)) {
                closeAttack = TRUE; }
        }

        if (notFalling) {
            if (closeAttack) {
                o->oAction = EE_ACT_ATTACK; }
            else if (enemyClass->range) {
                if (o->oTimer > o->oEEAttackDelay) {
                    if (e__enemy_raycast()) {
                        o->oAction = EE_ACT_ATTACK;
                        E_SET_ATTACK_DELAY(enemyClass->attackRate)
                    }
                }
            }
        }
        break;



    case EE_ACT_ATTACK:
        if ((*sE_EnemyClasses[o->oBehParams2ndByte].attackAction)()) {
            cur_obj_init_animation(1);
            o->oMoveAngleYaw = o->oFaceAngleYaw;
            o->oEEGoalVelX = (sins(o->oMoveAngleYaw) * sE_EnemyClasses[o->oBehParams2ndByte].speed);
            o->oEEGoalVelZ = (coss(o->oMoveAngleYaw) * sE_EnemyClasses[o->oBehParams2ndByte].speed);
            o->oVelX = 0.f;
            o->oVelZ = 0.f;
            o->oAction = EE_ACT_ROAMING;
        }
        break;



    case EE_ACT_ATTACKED:
        if (cur_obj_check_if_at_animation_end()) {
            cur_obj_init_animation(1);
            if (random_u16() & 1) {
                o->oEEAttackDelay = 0; }
            o->oAction = EE_ACT_ROAMING;
        }
    }

    o->oPosY -= o->hitboxDownOffset;
    cur_obj_push_mario_away_from_cylinder((o->hitboxRadius - 20.f), (o->hitboxHeight - 20.f));
    o->oPosY += o->hitboxDownOffset;

    o->oInteractStatus = 0;
    o->collidedObjs[0] = NULL;

    print_text_fmt_int(20, 40, "HEALTH %d", o->oHealth);
    print_text_fmt_int(20, 20, "ACTION %d", o->oAction);
}

#undef oEEMovementTimer
#undef oEEGoalVelX
#undef oEEGoalVelZ
#undef oEEAttackDelay
#undef oEERoamingSoundDelay
#undef oEERoamingSoundTimer
#undef oEETurnedFromWall
#undef oEETargetObj
#undef oEEDistToTarget






//-- *** Ablilty ***

void bhv_e__rocket_blast(void) {
    if (o->oTimer == 0) {
        o->oOpacity = 255;
        o->header.gfx.scale[0] = 0.45f;
        o->header.gfx.scale[2] = 0.45f;
        o->header.gfx.scale[1] = 1.f;
    }

    o->header.gfx.scale[0] += 0.08f;
    o->header.gfx.scale[2] += 0.08f;
    o->header.gfx.scale[1] = approach_f32_asymptotic(o->header.gfx.scale[1], 0.f, 0.15f);
    o->oPosY += 10.f;
    o->oFaceAngleYaw += DEGREES(1);

    o->oOpacity = approach_s32(o->oOpacity, 0, 26, 26);
    if (o->oOpacity == 0) {
        o->activeFlags = 0; }
}

void bhv_e__flattened_obj(void) {
    if (o->oAction) {
        Vec3f norm, lateralDir, leftDir, forwardDir;
        surface_normal_to_vec3f(norm, o->OBJECT_FIELD_S16P(0x1B));
        s16 yaw = o->oFaceAngleYaw;

        vec3f_set(lateralDir, sins(yaw), 0.0f, coss(yaw));
        vec3f_normalize(norm);
        vec3f_cross(leftDir, norm, lateralDir);
        vec3f_normalize(leftDir);
        vec3f_cross(forwardDir, leftDir, norm);
        vec3f_normalize(forwardDir);
        f32 negX = -forwardDir[0];
        f32 negY = -forwardDir[1];
        f32 negZ = -forwardDir[2];
        forwardDir[0] = negX;
        forwardDir[1] = negY;
        forwardDir[2] = negZ;
        vec3f_copy(o->transform[0], leftDir);
        vec3f_copy(o->transform[1], forwardDir);
        vec3f_copy(o->transform[2], norm);
        vec3f_copy(o->transform[3], &o->oPosX);
        MTXF_END(o->transform);
        o->header.gfx.throwMatrix = o->transform;
    }

    o->oUnk94 += 7000;
    o->oUpVel = approach_f32(o->oUpVel, 0.f, 0.0357142f, 0.0357142f);
    f32 bounce = (coss(o->oUnk94) * o->oUpVel);
    f32 x = (o->oVelX + bounce);
    f32 y = (o->oVelY + bounce);
    f32 z = 0.18f;
    o->header.gfx.scale[0] = x;
    o->header.gfx.scale[1] = y;
    o->header.gfx.scale[2] = z;

    o->oFloor = cur_obj_update_floor_height_and_get_floor();

    if (o->oFloor == NULL) {
        o->activeFlags = 0; }
    if (o->oTimer == 30) {
        spawn_mist_particles();
        if (o->oDeathSound) {
            create_sound_spawner(o->oDeathSound); }
        else {
            create_sound_spawner(SOUND_OBJ_DEFAULT_DEATH); }
        o->activeFlags = 0;
    }
}

void bhv_e__push_obj(void) {
    struct Object *obj = o->parentObj;
    //--**
    if (obj->oFloor != NULL) {
        o->oVelX = approach_f32_asymptotic(o->oVelX, 0.f, 0.1f);
        o->oVelZ = approach_f32_asymptotic(o->oVelZ, 0.f, 0.1f);

        f32 normY = obj->oFloor->normal.y;
        obj->oPosX += (o->oVelX * normY);
        obj->oPosZ += (o->oVelZ * normY);

        f32_find_wall_collision(&obj->oPosX, &obj->oPosY, &obj->oPosZ, 0.f, obj->hitboxRadius);

        f32 floorHeight = find_floor_height(obj->oPosX, (obj->oPosY + 100.f), obj->oPosZ);
        if (obj->oPosY < obj->oFloorHeight) {
            obj->oPosY = obj->oFloorHeight; }
    }

    if (o->oTimer > 40) {
        o->activeFlags = 0; }
}

//static s16 eq = DEGREES(35);//good: 45

void bhv_e__d(void) {
    //--D
    if (o->oTimer > 233) {
        o->activeFlags = 0;
    }


    f32 dist;
    vec3f_get_dist(&o->oPosX, &o->oHomeX, &dist);

    f32 div = (dist * 0.005f);
    if (div < 1.f) {
        div = 1.f;
    }
    s16 eq = (dist / div);
    o->header.gfx.scale[0] = eq;
    o->header.gfx.scale[1] = eq;
    o->header.gfx.scale[2] = eq;

    print_text_fmt_int(20, 50, "EQ %d", eq);

    o->oPosX += (sins(o->oFaceAngleYaw) * coss(o->oFaceAnglePitch)) * 70.f;
    o->oPosY += (sins(o->oFaceAnglePitch))                          * 70.f;
    o->oPosZ += (coss(o->oFaceAngleYaw) * coss(o->oFaceAnglePitch)) * 70.f;
    return;



#ifdef NEVER_DEFINED
    if (o->oTimer > 233) {
        o->activeFlags = 0;
    }
    

    f32 origDist = (f32)(o->oTimer * 70);
    s16 pitch = o->oFaceAnglePitch;
    s16 yaw = o->oFaceAngleYaw;


    s32 base = 8;
    f32 mul  = 6.f;
    /*if (origDist < 300.f) {//--D
        base = 45;
        mul  = 4.f;
    }*/

    //-f32 eq = ((DEGREES(base)) - ((s32)(sins(origDist + 1200.f) * (DEGREES(mul)))));


//    eq = approach_s16_asymptotic(eq, DEGREES(2), 75);//good: (eq, DEGREES(3), 60);
//    eq = ();
    f32 div = (origDist * 0.005f);
    if (div < 1.f) {
        div = 1.f; }
    s16 eq = (origDist * 0.7f/* + (sins((origDist) + 12000.f) * 546.f)*/);//((546.f / (origDist * 0.00025f)) + (sins((origDist) + 12000.f) * 546.f));//another good: (DEGREES(5) / (origDist * 0.0005f));
    print_text_fmt_int(20, 50, "EQ %d", eq);

    switch (o->oBehParams2ndByte) {
    case 1:
        yaw += eq;
        break;
    case 2:
        pitch -= eq;
        break;
    case 3:
        yaw -= eq;
        break;
    default:
        pitch += eq;
    }

    f32 dist = origDist + (origDist * sins(eq * 2));

    o->oPosX = o->oHomeX + (sins(yaw) * coss(pitch)) * dist;
    o->oPosY = o->oHomeY + (sins(pitch)) * dist;
    o->oPosZ = o->oHomeZ + (coss(yaw) * coss(pitch)) * dist;
#endif


    //--D
    /*
    o->header.gfx.scale[0] = 0.2f;
    o->header.gfx.scale[2] = 20.f;

    f32 div = (cur_obj_lateral_dist_to_home() * 0.0025f);
    if (div < 1.f) {
        div = 1.f; }
    o->oFaceAngleYaw = o->oMoveAngleYaw + ((7280.f / div)/* + (sins((origDist) + 12000.f) * 546.f)*R/);
    vec3f_copy(&o->oPosX, gMarioState->pos);*/



}









//--Geo


//obj

Gfx *e__geo_caco_eye_color(s32 callContext, struct GraphNode *node, Mat4 *context) {
    if (callContext == GEO_CONTEXT_RENDER) {
        Gfx *dlS = alloc_display_list(sizeof(Gfx) * 2);
        Gfx *dlH = dlS;
        
        if (dlS == NULL) {
            return; }

        print_text_fmt_int(20, 100, "GEO %d", 1);

        struct Object *obj = (struct Object *) gCurGraphNodeObject;
        s32 color = 0;
        if (obj->oAction == EE_ACT_ATTACK) {
            color = ((s32)(sins(o->oTimer * 6553) * 255.f)); }
        gDPSetEnvColor(dlH++, 0, 0, 0, 0xFF);//**
        gSPEndDisplayList(dlH);

        return dlS;
    }

    return NULL;
}


Gfx *e__0(s32 callContext, struct GraphNode *node, Mat4 *context) {
    /*if (callContext == GEO_CONTEXT_RENDER) {
        Gfx *dlS = alloc_display_list(sizeof(Gfx) * 3);
        Gfx *dlH = dlS
        
        if (dlS == NULL) {
            return; }

        struct Object *obj = (struct Object *) gCurGraphNodeObject;
        if (obj->oShotByShotgun) {
            

            gDPSetLights1(dlHead++, 255, 255, 255, objectOpacity);
            gSPEndDisplayList(dlHead);
        }

        return dlStart;
    }

    return NULL;*/
}




//Mario



static void e__mario_aim_rotation(s16 *rn0, s16 *rn1, s16 *rn2, s32 div, s32 shootAnimDiv) {
    s16 pitch = (gE_UpperAimPitch / div);
    s16 yaw   = (gE_UpperAimYaw   / div);
    if (shootAnimDiv) {
        yaw /= shootAnimDiv; }
    if (gMarioObject->header.gfx.animInfo.animID == MARIO_ANIM_RIDING_SHELL) {//shell offset
        yaw += DEGREES(30); }
    *rn0 = approach_s16_asymptotic(*rn0, yaw, 4);
    *rn1 = 0;
    *rn2 = approach_s16_asymptotic(*rn2, pitch, 4);
}


Gfx *geo_e__mario_torso_rotation(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        struct GraphNodeRotation *rotNode = (struct GraphNodeRotation *) node->next;

        if (gE_ShotgunFlags & E_SGF_AIM_FIRE) {
            //first in geo
            gE_UpperAimPitch = ((s16)((calculate_pitch(gLakituState.focus, gLakituState.pos)) - gMarioState->faceAngle[0]));
            gE_UpperAimYaw   = ((s16)((gCamera->yaw + DEGREES(180)) - gMarioState->faceAngle[1]));//approach toward middle when racking the gun
            e__mario_aim_rotation(&rotNode->rotation[0], &rotNode->rotation[1], &rotNode->rotation[2], 3, 1);
        } else {
            s32 action = gMarioState->action;
            s16 *torsoAngle = &gMarioState->marioBodyState->torsoAngle;

            if ((action != ACT_BUTT_SLIDE) && (action != ACT_HOLD_BUTT_SLIDE) && (action != ACT_WALKING) && (action != ACT_RIDING_SHELL_GROUND)) {
                vec3_zero(torsoAngle); }

            rotNode->rotation[0] = torsoAngle[1];
            rotNode->rotation[1] = torsoAngle[2];
            rotNode->rotation[2] = torsoAngle[0];
        }
    }
    return NULL;
}

Gfx *geo_e__mario_head_rotation(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        struct GraphNodeRotation *rotNode = (struct GraphNodeRotation *) node->next;

        if (gE_ShotgunFlags & E_SGF_AIM_FIRE) {
            e__mario_aim_rotation(&rotNode->rotation[0], &rotNode->rotation[1], &rotNode->rotation[2], 2, 1); }
        else if (gCamera->mode == CAMERA_MODE_C_UP) {
            rotNode->rotation[0] = gPlayerCameraState->headRotation[1];
            rotNode->rotation[2] = gPlayerCameraState->headRotation[0];
        } else if (gMarioState->action & ACT_FLAG_WATER_OR_TEXT) {
            struct MarioBodyState *bodyState = &gBodyStates;
            rotNode->rotation[0] = bodyState->headAngle[1];
            rotNode->rotation[1] = bodyState->headAngle[2];
            rotNode->rotation[2] = bodyState->headAngle[0];
        } else {
            approach_vec3s_asymptotic(&rotNode->rotation, gVec3sZero, 4, 4, 4); }
    }
    return NULL;
}

Gfx *geo_e__mario_arm_rotation(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        struct GraphNodeRotation *rotNode = (struct GraphNodeRotation *) node->next;

        if (gE_ShotgunFlags & E_SGF_AIM_FIRE) {//aim mode
            s32 shootAnimDiv = (13 - ABS((gE_ShotgunTimer - 13)));
            e__mario_aim_rotation(&rotNode->rotation[1], &rotNode->rotation[2], &rotNode->rotation[0], 2, shootAnimDiv); }
        else {
            approach_vec3s_asymptotic(&rotNode->rotation, gVec3sZero, 4, 4, 4); }
    }
    return NULL;
}

Gfx *geo_e__mario_shotgun_scale(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        struct MarioState *m = gMarioState;
        struct GraphNodeScale *scaleNode = (struct GraphNodeScale *) node->next;
        s32 sgTimer = gE_ShotgunTimer;

        if (gE_UpperAnimInfo.animID == 28) {
            s32 timer = (32767 - (sgTimer * 1424));
            f32 scale = (1.f + (sins(timer) * 0.3f));
            scaleNode->scale = scale;
        } else {
            scaleNode->scale = 1.f; }
    }
    return NULL;
}

Gfx *geo_e__switch_mario_shotgun_hand(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        struct GraphNodeSwitchCase *switchCase = (struct GraphNodeSwitchCase *) node;
        switchCase->selectedCase = (gE_ShotgunFlags & E_SGF_LEFT_HAND);
    }
    return NULL;
}
