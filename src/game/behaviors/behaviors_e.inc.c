//Warning: rushed & bad

#include "levels/e/header.h"
#include "game/e__c9_dobj.h"





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
#define oEEAttackedByMario   OBJECT_FIELD_S32(0x4A)
#define oEEDistToTarget      oHomeX
#define oEEAttackedByEnemy   oAnimState


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

static s32 e__enemy_raycast(void);

static s32 e__pistol_guy_attack(void) {
    cur_obj_init_animation(3);

    approach_s16_asymptotic(o->oFaceAngleYaw, obj_angle_to_object(o, o->oEETargetObj), 3);

    if (o->oTimer == 0) {
        s16 yaw = obj_angle_to_object(o, o->oEETargetObj);
        o->oFaceAngleYaw = yaw;

        Vec3f pos = { (o->oPosX + (sins(yaw) * 100.f)), (o->oPosY + 120.f), (o->oPosZ + (coss(yaw) * 100.f)) };
		e__spawn_c9_dobj(o, o->oEETargetObj, 0, pos, 120.f, 40.f, yaw);
        play_sound(SOUND_OBJ2_EYEROK_SOUND_LONG, o->header.gfx.cameraToObject);

        struct Object *flash = spawn_object(o, MODEL_ID_1D, bhvE_MuzzleFlash);
        vec3f_copy(&flash->oPosX, pos);

    } else if (o->oTimer == 9) {
        return TRUE; }

    return FALSE;
}

static s32 e__chaingun_guy_attack(void) {
    cur_obj_init_animation(3);

    o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw, obj_angle_to_object(o, o->oEETargetObj), 3);

    if ((o->oTimer % 4) == 0) {
        s16 yaw = obj_angle_to_object(o, o->oEETargetObj);
        Vec3f pos = { (o->oPosX + (sins(yaw) * 120.f)), (o->oPosY + 120.f), (o->oPosZ + (coss(yaw) * 120.f)) };
		e__spawn_c9_dobj(o, o->oEETargetObj, 0, pos, 120.f, 30.f, yaw);
        play_sound(SOUND_OBJ2_EYEROK_SOUND_LONG, o->header.gfx.cameraToObject);

        struct Object *flash = spawn_object(o, MODEL_ID_1D, bhvE_MuzzleFlash);
        flash->oPosY = (o->oPosY + 120.f);

        if ((!e__enemy_raycast()) || o->oTimer > (30 + (random_u16() / 2184))) {
            return TRUE; }
    }

    return FALSE;
}

static s32 e__caco_attack(void) {
    cur_obj_init_animation(3);

    o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw, obj_angle_to_object(o, o->oEETargetObj), 5);

    if (o->oTimer == 0) {//--**
        cur_obj_set_model(MODEL_ID_04);
    } else if (o->oTimer == 12) {
        cur_obj_set_model(MODEL_ID_03);
    }

    if (o->oTimer == 5) {
        //-if (dist_between_objects(o, o->oEETargetObj) < 400.f) {//close attack
        s16 yaw = calculate_yaw(&o->oPosX, &o->oEETargetObj->oPosX);
        o->oFaceAngleYaw = yaw;
        Vec3f pos = { (o->oPosX + (sins(yaw) * 100.f)), (o->oPosY + 120.f), (o->oPosZ + (coss(yaw) * 100.f)) };
		e__spawn_c9_dobj(o, o->oEETargetObj, 2, pos, 60.f, 40.f, o->oFaceAngleYaw);
        play_sound(SOUND_MITM_LEVEL_E_MISSILE_FIRE, o->header.gfx.cameraToObject);
    } else if (o->oTimer == 24) {
        return TRUE; }

    return FALSE;
}




static struct E_EnemyClass sE_EnemyClasses[E_ENEMY_TYPE_COUNT] = {
    //pistol
    { SOUND_MITM_LEVEL_E_GUN_GUY_ALERT,  SOUND_MITM_LEVEL_E_GUN_GUY_ALERT2,
    SOUND_MITM_LEVEL_E_GUN_GUY_ROAMING,  SOUND_MITM_LEVEL_E_GUN_GUY_ROAMING,
    SOUND_MITM_LEVEL_E_GUN_GUY_DAMAGE,   SOUND_MITM_LEVEL_E_GUN_GUY_DAMAGE,
    SOUND_MITM_LEVEL_E_GUN_GUY_DAMAGE,   SOUND_MITM_LEVEL_E_GUN_GUY_DEATH,
    &pistol_guy_anims, 140.f, 180.f, 10.f, &e__pistol_guy_attack,   2, 0, 1, 5,   0, 0, 1 },

    //chaingun
    { SOUND_MITM_LEVEL_E_GUN_GUY_ALERT,  SOUND_MITM_LEVEL_E_GUN_GUY_ALERT2,
    SOUND_MITM_LEVEL_E_GUN_GUY_ROAMING,  SOUND_MITM_LEVEL_E_GUN_GUY_ROAMING,
    SOUND_MITM_LEVEL_E_GUN_GUY_DAMAGE,   SOUND_MITM_LEVEL_E_GUN_GUY_DAMAGE,
    SOUND_MITM_LEVEL_E_GUN_GUY_DAMAGE,   SOUND_MITM_LEVEL_E_GUN_GUY_DEATH,
    &chaingun_guy_anims, 150.f, 210.f, 10.f, &e__chaingun_guy_attack,   3, 0, 1, 10,   0, 0, 1 },

    //lost soul
    { 0000000000000000,  0000000000000000,
    0000000000000000,    0000000000000000,
    0000000000000000,   0000000000000000,
    0000000000000000,    0000000000000000,
    &pistol_guy_anims, 60.f, 160.f, 10.f, &e__pistol_guy_attack,   2, 50, 1, 3,   0, 0, 1 },    

    //caco
    { SOUND_MITM_LEVEL_E_CACO_ALERT,  SOUND_MITM_LEVEL_E_CACO_ALERT2,
    SOUND_MITM_LEVEL_E_CACO_ALERT,    SOUND_MITM_LEVEL_E_CACO_ALERT2,//--**
    SOUND_MITM_LEVEL_E_CACO_DAMAGE,   SOUND_MITM_LEVEL_E_CACO_DAMAGE2,
    SOUND_MITM_LEVEL_E_CACO_DEATH,    SOUND_MITM_LEVEL_E_CACO_DEATH2,
    &caco_anims, 140.f, 280.f, 15.f, &e__caco_attack,   (3 * 4), 25, 4, 3,   1, 1, 1 },

    //revenant
    { 0000000000000000,  0000000000000000,
    0000000000000000,    0000000000000000,
    0000000000000000,   0000000000000000,
    0000000000000000,    0000000000000000,
    &pistol_guy_anims, 60.f, 160.f, 10.f, &e__pistol_guy_attack,   2, 50, 1, 3,   0, 0, 1 },

    //mancubus
    { 0000000000000000,  0000000000000000,
    0000000000000000,    0000000000000000,
    0000000000000000,   0000000000000000,
    0000000000000000,    0000000000000000,
    &pistol_guy_anims, 60.f, 160.f, 10.f, &e__pistol_guy_attack,   2, 50, 1, 3,   0, 0, 1 },

    //mastermind
    { 0000000000000000,  0000000000000000,
    0000000000000000,    0000000000000000,
    0000000000000000,   0000000000000000,
    0000000000000000,    0000000000000000,
    &pistol_guy_anims, 60.f, 160.f, 10.f, &e__pistol_guy_attack,   2, 50, 1, 3,   0, 0, 1 },
};



//--Process

static s32 e__enemy_raycast(void) {
    if (o->oEEDistToTarget < 3000.f) {//4000.f
        struct Surface *surf;
        Vec3f orig = { o->oPosX, (o->oPosY + (o->hitboxHeight * 0.5f)), o->oPosZ }; 
        Vec3f soundSource = { o->oEETargetObj->oPosX, (o->oEETargetObj->oPosY + 80.f), o->oEETargetObj->oPosZ };
        Vec3f hitPos, dir = { (soundSource[0] - orig[0]), (soundSource[1] - orig[1]), (soundSource[2] - orig[2]) };

        find_surface_on_ray(orig, dir, &surf, hitPos, (RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL | RAYCAST_FIND_WALL));
        if (!surf) {
            return TRUE; }
    }
    return FALSE;
}

static s32 e__alerted_sound(void) {
    if ((gE_ShotgunTimer == 25)) {//--**
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

static void e__attacked_common(s32 targetMario) {//--**
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

    if (targetMario) {
        o->oEETargetObj = gMarioObject;
    }
}
static void e__attacked_by_enemy(void) {
    e__attacked_common(0);

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

    //--**
   //wall
    struct Surface *surf;
    f32 collDist = (o->hitboxRadius + (sE_EnemyClasses[o->oBehParams2ndByte].speed * 3.f));
    f32 offsetY  = ((o->hitboxHeight * 0.5f) - o->hitboxDownOffset);

    Vec3f orig = { nextPos[0], (nextPos[1] + offsetY), nextPos[2] };
    Vec3f hitPos, dir = { (sins(o->oMoveAngleYaw) * collDist), 0.f, (coss(o->oMoveAngleYaw) * collDist) };
    find_surface_on_ray(orig, dir, &surf, hitPos, (RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL | RAYCAST_FIND_WALL | RAYCAST_FIND_WATER));//--**

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
        if ((behavior == segmented_to_virtual(bhvE_Caco))
         || (behavior == segmented_to_virtual(bhvE_PistolGuy))
         || (behavior == segmented_to_virtual(bhvE_ChaingunGuy))) {//--**
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
    if (o->oDistanceToMario > 5000.f) {
        return; }

    //attacked
    if (o->oShotByShotgun) {
        o->oEEAttackedByMario = TRUE;
        e__attacked_common(1);
        o->oShotByShotgun = 0;
    } else {
        if ((o->oIntangibleTimer == 0) && (o->oInteractStatus & INT_STATUS_WAS_ATTACKED)) {
            if (gMarioState->action == ACT_GROUND_POUND) {
                o->oHealth -= 2; }
            else {
                o->oHealth -= 1; }
            e__attacked_by_enemy();
            o->oIntangibleTimer = 18;

        } else if (o->oEEAttackedByEnemy) {
            o->oHealth -= o->oEEAttackedByEnemy;
            e__attacked_by_enemy();
        }
    }
    o->oEEAttackedByEnemy = FALSE;


    //reset target & check if target is defeated
    if (o->oEETargetObj != NULL) {
        if (o->oEETargetObj == gMarioObject) {
            if (gMarioState->health == 0) {
                o->oAction = EE_ACT_IDLE; }
        } else if (o->oEETargetObj->activeFlags == 0) {//--**
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
        o->oDrawingDistance = 5000.f;
        
      {
        struct E_EnemyClass *enemyClass = &sE_EnemyClasses[o->oBehParams2ndByte];

        E_SET_ROAMING_SOUND_DELAY()
        E_SET_ATTACK_DELAY(enemyClass->attackRate)   
        //-o->oDeathSound = E_RANDOM_SOUND(enemyClass->deathSound);//--**
        o->oAnimations       = enemyClass->anims;
        o->hitboxRadius      = enemyClass->hitboxRadius;
        o->hurtboxRadius     = enemyClass->hitboxRadius;
        o->hitboxHeight      = enemyClass->hitboxHeight;
        o->hurtboxHeight     = enemyClass->hitboxHeight;
        //-o->hitboxDownOffset  = enemyClass->offsetY;//--**
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



    case EE_ACT_ROAMING:;
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
                if (((random_u16() % 6) == 0) || ((o->oEETargetObj == gMarioObject) && (gMarioState->action == ACT_E_DOOM_DEATH))) {
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

        if (notFalling && (!((o->oEETargetObj == gMarioObject) && (gMarioState->action == ACT_E_DOOM_DEATH)))) {
            if (closeAttack) {
                o->oAction = EE_ACT_ATTACK; }
            else if (enemyClass->range) {
                if (o->oTimer > o->oEEAttackDelay) {
                    if (e__enemy_raycast()) {
                        o->oAction = EE_ACT_ATTACK; }
                    E_SET_ATTACK_DELAY(enemyClass->attackRate)//
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


    if (gMarioState->action != ACT_E_DOOM_DEATH) {
        o->oPosY -= o->hitboxDownOffset;
        cur_obj_push_mario_away_from_cylinder((o->hitboxRadius - 20.f), (o->hitboxHeight - 20.f));
        o->oPosY += o->hitboxDownOffset;
    }

    o->oInteractStatus = 0;
    o->collidedObjs[0] = NULL;
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








//-- door

enum {
    ED_ACT_INIT,
    ED_ACT_CLOSED,
    ED_ACT_OPENING,
    ED_ACT_OPEN,
};

#define oEDRequiredKey  OBJECT_FIELD_S32(0x1B)
#define oEDCloseDelay   OBJECT_FIELD_U32(0x1C)

extern u8 gE_KeyMessageTimer;
extern u8 gE_KeyMessageIndex;

static Collision *sE_DoorCollision[] = {
    e_door_collision,
};



static e__open_door(void) {
    play_sound(SOUND_MITM_LEVEL_E_DOOR_OPEN, o->header.gfx.cameraToObject);
    o->oAction = ED_ACT_OPENING;
}


void bhv_e__door(void) {
    switch (o->oAction) {
    case ED_ACT_INIT:
        o->oPosY = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
        obj_set_collision_data(o, sE_DoorCollision[0/*o->oBehParams >> 24*/]);
        o->oEDCloseDelay = 135;

        //if (o->oBehParams >> 24) {
        //    e__create_door_light(o); }

        vec3f_copy(&o->oHomeX, &o->oPosX);
        o->oDrawingDistance = 20000.f;
        o->oCollisionDistance = 20000.f;
        o->oAction = ED_ACT_CLOSED;
        o->oEDRequiredKey = (o->oBehParams & 0x000000FF);
        break;

        
    case ED_ACT_CLOSED:;
        s32 open = FALSE;
        
        switch (o->oBehParams2ndByte) {
        case 1://common
            if (o->oTimer > 15) {            
                f32 dX = (o->oHomeX - gMarioState->pos[0]);
                f32 dZ = (o->oHomeZ - gMarioState->pos[2]);
                s16 oNegYaw = -o->oFaceAngleYaw;
                f32 cY = coss(oNegYaw);
                f32 sY = sins(oNegYaw);
                f32 dXR = ((cY * dX) + (sY * dZ));
                f32 dZR = ((sY * dX) - (cY * dZ));

                if (absf(dX) < 750.f) {
                    f32 dY = (gMarioState->pos[1] - o->oHomeY);
                    if ((dY >= 0.f) && (dY < 600.f)) {
                        if (absf(dZ) < 750.f) {
                            if (o->oEDRequiredKey) {//key
                                if (gMarioState->numKeys & o->oEDRequiredKey) {
                                    e__open_door(); }
                                else {//key message
                                    if (o->oSubAction == 0) {
                                        o->oSubAction = 120;
                                        gE_KeyMessageTimer = 1;
                                        gE_KeyMessageIndex = (o->oEDRequiredKey - 1);
                                        if (gE_KeyMessageIndex > 2) {
                                            gE_KeyMessageIndex = 2; }
                                    }
                                }
                            } else {
                                e__open_door(); }
                        }
                    }
                }
            }

            //key message cool down
            if (o->oSubAction) {
                o->oSubAction--; }

            //close
            o->oPosY = approach_f32(o->oPosY, o->oHomeY, 20.f, 20.f);
            break;

        case 0:;//
            struct Object *coin = cur_obj_nearest_object_with_behavior(bhvRedCoin);
            if (coin && dist_between_objects(coin, gMarioObject) < 200.f) {
                o->oEDCloseDelay = 65535;
                e__open_door();
            }
            break;

        case 2:
            if (gMarioState->numKeys & 1) {
                o->oEDCloseDelay = 65535;
                e__open_door();
            }
            break;

        case 3:
            if (dist_between_objects(o, gMarioObject) < 380.f) {
                o->oEDCloseDelay = 65535;
                e__open_door();
            }
        }
        break;

        
    case ED_ACT_OPENING:
        if (!approach_f32_bool(&o->oPosY, (o->oHomeY + 700.f), 20.f, 20.f)) {
            o->oAction = ED_ACT_OPEN; }
        break;

        
    case ED_ACT_OPEN:
        if (o->oTimer > o->oEDCloseDelay) {
            play_sound(SOUND_MITM_LEVEL_E_DOOR_CLOSE, o->header.gfx.cameraToObject);
            o->oAction = ED_ACT_CLOSED;
        }
    }

    //-if (obj_has_model(o, MODEL_ID_14)) {\
        print_text_fmt_int(20, 80, "TIMER %d", (s32)(o->oTimer)); }

    load_object_collision_model();
}







//--key



void bhv_e__key(void) {
    enum { EK_ACT_INIT, EK_ACT_COLLECTABLE };

    switch (o->oAction) {
    case EK_ACT_INIT:
        o->oPosY = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
        o->oDrawingDistance = 20000.f;
        o->oAction = EK_ACT_COLLECTABLE;
        o->oIntangibleTimer = 0;
        o->hitboxRadius = 60.f;
        o->hitboxHeight = 100.f;
        break;

        
    case EK_ACT_COLLECTABLE:
        if (o->oShotByShotgun) {
            o->oShotByShotgun = 0;
            o->oMoveAngleYaw = DEGREES(33);
        }
        o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, DEGREES(3), DEGREES(1));
        o->oFaceAngleYaw += o->oMoveAngleYaw;

        if (o->oDistanceToMario < 110.f) {
            play_sound(SOUND_MITM_LEVEL_E_ITEM, o->header.gfx.cameraToObject);
            spawn_object(o, (obj_get_model_id(o) + 3), bhvE_KeyCollect);
            o->activeFlags = 0;
            gMarioState->numKeys |= o->oBehParams2ndByte;
        }
    }
}

void bhv_e__key_collect(void) {
    f32 scaleX = (o->header.gfx.scale[0] = approach_f32(o->header.gfx.scale[0], 0.f, 0.3f, 0.3f));
    o->header.gfx.scale[1] = scaleX;
    o->header.gfx.scale[2] = scaleX;

    if (scaleX == 0.f) {
        o->activeFlags = 0; }
}





//--elevator

void bhv_e__elevator(void) {
    enum {
        EEL_ACT_INIT,
        EEL_ACT_DOWN,
        EEL_ACT_RISE,
        EEL_ACT_UP,
        EEL_ACT_LOWER,
    };

    switch (o->oAction) {
    case EEL_ACT_INIT:
        spawn_object(o, MODEL_ID_0E, bhvE_ElevatorBase);

        o->oPosY -= (1400.f + 10.f);
        o->oHomeY = o->oPosY;

        if (o->oBehParams2ndByte) {
            o->oEDCloseDelay = 0x7FFFFFFF; }
        else {
            o->oEDCloseDelay = 105; }

        obj_set_collision_data(o, e_elevator_collision);
        o->oDrawingDistance = 20000.f;
        o->oAction = EEL_ACT_DOWN;
        break;

        
    case EEL_ACT_DOWN:
        if (!level_in_dream_comet_mode()) {
            if (o->oBehParams2ndByte) {
                struct Object *swltch = cur_obj_nearest_object_with_behavior(bhvE_Switch);
                if (swltch->oAction != 3) {
                    break; }
            } else {
                if (gMarioObject->platform != o) {
                    break; }
            }
            play_sound(SOUND_MITM_LEVEL_E_ELEVATOR, o->header.gfx.cameraToObject);
            o->oAction = EEL_ACT_RISE;
        }
        break;

        
    case EEL_ACT_RISE:
        if (!approach_f32_bool(&o->oPosY, (o->oHomeY + 1400.f), 40.f, 40.f)) {
            o->oAction = EEL_ACT_UP; }
        break;

        
    case EEL_ACT_UP:
        if (o->oTimer > o->oEDCloseDelay) {
            play_sound(SOUND_MITM_LEVEL_E_ELEVATOR, o->header.gfx.cameraToObject);
            o->oAction = EEL_ACT_LOWER;
        }
        break;
        

    case EEL_ACT_LOWER:
        if (!approach_f32_bool(&o->oPosY, o->oHomeY, 40.f, 40.f)) {
            o->oAction = EEL_ACT_DOWN; }
        break;
    }

    load_object_collision_model();
}





//--candelabra


void bhv_e__candelabra(void) {
    enum {
        EC_ACT_INIT,
        EC_ACT_STILL,
        EC_ACT_SHOT,
    };


    switch (o->oAction) {
    case EC_ACT_INIT:
        o->oPosY = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
        o->oInteractType = INTERACT_IGLOO_BARRIER;
        o->oIntangibleTimer = 0;
        o->hitboxRadius     = 100;
        o->hitboxHeight     = 500;
        o->oAction = EC_ACT_STILL;
        break;

        
    case EC_ACT_STILL:


        break;

        
    case EC_ACT_SHOT:;


    }
}





//--switch

void bhv_e__switch(void) {
    enum {
        ES_ACT_INIT,
        ES_ACT_NOT_USED,
        ES_ACT_USED_DELAY,
        ES_ACT_USED,
    };


    switch (o->oAction) {
    case ES_ACT_INIT:
        o->oPosY = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
        o->oEDRequiredKey = (o->oBehParams & 0x000000FF);
        o->oDrawingDistance = 20000.f;
        o->oAction = ES_ACT_NOT_USED;

        obj_set_collision_data(o, e_switch_collision);
        break;

        
    case ES_ACT_NOT_USED:
        if ((o->oDistanceToMario < 200.f) || o->oShotByShotgun) {
            if (o->oEDRequiredKey) {
                if (!(gMarioState->numKeys & o->oEDRequiredKey)) {
                    if (o->oSubAction == 0) {
                        o->oSubAction = 120;
                        gE_KeyMessageTimer = 1;
                        gE_KeyMessageIndex = (o->oEDRequiredKey - 1);
                        if (gE_KeyMessageIndex > 2) {
                            gE_KeyMessageIndex = 2; }
                    }
                    break;
                }
            }

            play_sound(SOUND_MITM_LEVEL_E_SWITCH, o->header.gfx.cameraToObject);
            cur_obj_set_model(MODEL_ID_11);
            o->oAction = ES_ACT_USED;
        }
        break;

        
    case ES_ACT_USED_DELAY:
        if (o->oTimer >= 10) {
            o->oAction = ES_ACT_USED; }
        break;

        
    case ES_ACT_USED:;
    }

    //key message cool down
    if (o->oSubAction) {
        o->oSubAction--; }

    //print_text_fmt_int(20, 20, "DIST %d", (s32)(o->oDistanceToMario));
    o->oShotByShotgun = 0;
    load_object_collision_model();
}





//--teleport

#define oETDestTeleport  OBJECT_FIELD_OBJ(0x1B)

void bhv_e__teleport(void) {
    enum {
        ET_ACT_INIT,
        ET_ACT_TELEPORT,
        ET_ACT_STOOD_ON,
    };

    switch (o->oAction) {
    case ET_ACT_INIT:
        o->oAction = ET_ACT_TELEPORT;
        if (o->oBehParams2ndByte) {
            o->oETDestTeleport = o->header.next; }
        else {
            o->oETDestTeleport = o->header.prev; }
        obj_set_collision_data(o, e_teleport_collision);
        load_object_static_model();
        break;

        
    case ET_ACT_TELEPORT:
        if (gMarioState->floor->object == o) {
            struct Object *next = (struct Object *)(o->oETDestTeleport);
            o->oETDestTeleport->oAction = ET_ACT_STOOD_ON;

            gMarioState->pos[0] += (o->oETDestTeleport->oPosX - o->oPosX);
            gMarioState->pos[1] += (o->oETDestTeleport->oPosY - o->oPosY);
            gMarioState->pos[2] += (o->oETDestTeleport->oPosZ - o->oPosZ);

            spawn_object_relative(0, 0, (gMarioState->pos[1] - o->oPosY) + 80.f,                  0, o,                  MODEL_ID_13, bhvE_TeleportEffect);//teleported from
            spawn_object_relative(0, 0, (gMarioState->pos[1] - o->oETDestTeleport->oPosY) + 80.f, 0, o->oETDestTeleport, MODEL_ID_13, bhvE_TeleportEffect);//teleported to

            gLakituState.focHSpeed = 1.f;
            gLakituState.focVSpeed = 1.f;
            gLakituState.posHSpeed = 1.f;
            gLakituState.posVSpeed = 1.f;

            play_sound(SOUND_MITM_LEVEL_E_TELEPORT, o->header.gfx.cameraToObject);
        }
        break;

        
    case ET_ACT_STOOD_ON:
        if (o->oTimer > 1) {
            if (gMarioState->floor->object != o) {
                o->oAction = ET_ACT_TELEPORT; }
        } else if (o->oTimer == 1) {
            gLakituState.focHSpeed = 0.8f;
            gLakituState.focVSpeed = 0.3f;
            gLakituState.posHSpeed = 0.3f;
            gLakituState.posVSpeed = 0.3f;
        }
    }

    o->oVelY = 0.f;
}


void bhv_e__teleport_effect(void) {
    enum {
        ETE_ACT_INIT,
        ETE_ACT_LOOP,
    };

    switch (o->oAction) {
    case ETE_ACT_INIT:
        o->header.gfx.scale[0] = 0.f;
        o->oAction = ETE_ACT_LOOP;
        break;

        
    case ETE_ACT_LOOP:;
        f32 scaleY = (1.f - (o->header.gfx.scale[0] = approach_f32(o->header.gfx.scale[0], 1.f, 0.1f, 0.1f)));
        o->header.gfx.scale[1] = scaleY;
        if (scaleY == 0.f) {
            o->activeFlags = 0; }
    }
}



//--medkit

extern u8 gE_C9MarioHealth;

void bhv_e__medkit(void) {
    enum { EM_ACT_INIT, EM_ACT_COLLECTABLE };

    switch (o->oAction) {
    case EM_ACT_INIT:
        o->oPosY = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
        o->oDrawingDistance = 20000.f;
        o->oAction = EM_ACT_COLLECTABLE;
        //o->oIntangibleTimer = 0;
        //o->hitboxRadius = 90.f;
        //o->hitboxHeight = 100.f;
        break;

        
    case EM_ACT_COLLECTABLE:
        if (o->oDistanceToMario < 110.f) {
            switch (o->oBehParams2ndByte) {
            case 0://medkit
                if (gE_C9MarioHealth < 100) {
                    gE_C9MarioHealth += 25;
                    if (gE_C9MarioHealth > 100) {
                        gE_C9MarioHealth = 100; }

                    play_sound(SOUND_MITM_LEVEL_E_ITEM, o->header.gfx.cameraToObject);
                    spawn_object(o, MODEL_ID_1B, bhvE_KeyCollect);
                    o->activeFlags = 0;
                }
                break;

            case 1://shells/coins
                play_sound(SOUND_MITM_LEVEL_E_ITEM, o->header.gfx.cameraToObject);
                spawn_object(o, MODEL_ID_1B, bhvE_KeyCollect);
                gMarioState->numGlobalCoins += 10;
                if (gMarioState->numGlobalCoins > 999) {gMarioState->numGlobalCoins = 999;} //CLAMP
                o->activeFlags = 0;
            }
        }
    }
}







//--tutorial


#define oTTarget1 OBJECT_FIELD_OBJ(0x1B)
#define oTTarget2 OBJECT_FIELD_OBJ(0x1C)
#define oTTarget3 OBJECT_FIELD_OBJ(0x1D)

static void spawn_target(s32 index, s32 model, f32 offsetY, f32 dist, s16 angle) {
	angle += DEGREES(180);

	o->OBJECT_FIELD_OBJ(index) = spawn_object(o, model, bhvE_Target);

	o->OBJECT_FIELD_OBJ(index)->oBehParams2ndByte = index;
	o->OBJECT_FIELD_OBJ(index)->oPosX += (sins(angle) * dist);
	o->OBJECT_FIELD_OBJ(index)->oPosY += offsetY;
	o->OBJECT_FIELD_OBJ(index)->oPosZ += (coss(angle) * dist);
	o->OBJECT_FIELD_OBJ(index)->oFaceAngleYaw = obj_angle_to_object(o->OBJECT_FIELD_OBJ(index), o);
}

void bhv_e__tutorial(void) {
    if (gCurrCreditsEntry != NULL) {
        // no tutorial during credits
        return;
    }

	if ((o->oTTarget1 != NULL) || (o->oTTarget2 != NULL) || (o->oTTarget3 != NULL)) {
		o->oTimer = 0; }

	if (o->oSubAction == 0) {
		play_sound(SOUND_OBJ_DEFAULT_DEATH, gGlobalSoundSource);
		o->oSubAction++;
	}

    //--
    if (gMarioState->numGlobalCoins <= 0) {
        gMarioState->numGlobalCoins = 1;
    }

	switch (o->oAction) {
	case 0:
        gMarioState->health = 0x880;
        //-gE_C9MarioHealth = 100;

		if ((save_file_get_flags() & SAVE_FLAG_SHOTGUN_TUTORIAL) || ((gPlayer1Controller->buttonDown & Z_TRIG) && (gPlayer1Controller->buttonDown & R_TRIG) && (gPlayer1Controller->buttonDown & B_BUTTON))) {//--T1
			o->oAction = 4;
			return;
		}
		if (cur_obj_update_dialog(MARIO_DIALOG_LOOK_UP, DIALOG_FLAG_TEXT_DEFAULT, DIALOG_C9_1, 0)) {
			spawn_target(0x1B, MODEL_ID_21, 100.f, 1400.f, DEGREES(45));
			spawn_target(0x1C, MODEL_ID_21, 100.f, 1400.f, DEGREES(-45));
			spawn_target(0x1D, MODEL_ID_21, 100.f, 1400.f, DEGREES(240));

			o->oAction = 1;
		}
		break;

		
	case 1:
		if (o->oTimer >= 35) {
			if (cur_obj_update_dialog(MARIO_DIALOG_LOOK_UP, DIALOG_FLAG_TEXT_DEFAULT, DIALOG_C9_2, 0)) {
				spawn_target(0x1B, MODEL_ID_24, -100.f, 500.f, DEGREES(78));
				spawn_target(0x1C, MODEL_ID_24, 750.f,  700.f, DEGREES(330));
				spawn_target(0x1D, MODEL_ID_24, 500.f,  800.f, DEGREES(240));
				o->oAction = 2;
			}
		}
		break;

		
	case 2:
		if (o->oTimer >= 35) {
			if (cur_obj_update_dialog(MARIO_DIALOG_LOOK_UP, DIALOG_FLAG_TEXT_DEFAULT, DIALOG_C9_3, 0)) {
				spawn_target(0x1B, MODEL_ID_22, 700.f,  1400.f, DEGREES(45));
				spawn_target(0x1C, MODEL_ID_22, 700.f,  1400.f, DEGREES(340));
				spawn_target(0x1D, MODEL_ID_23, 350.f,  1400.f, DEGREES(270));
				o->oAction = 3;
			}
		}
		break;

		
	case 3:
		if (o->oTimer >= 35) {
			if (o->oTimer == 35) {
				play_puzzle_jingle(); }

			if (cur_obj_update_dialog(MARIO_DIALOG_LOOK_UP, DIALOG_FLAG_TEXT_DEFAULT, DIALOG_C9_4, 0)) {
                save_file_set_flags(SAVE_FLAG_SHOTGUN_TUTORIAL);
				o->activeFlags = 0;
            }
		}
		break;


	case 4:
		//-if (cur_obj_update_dialog(MARIO_DIALOG_LOOK_UP, DIALOG_FLAG_TEXT_DEFAULT, DIALOG_005, 0)) {
		o->activeFlags = 0;
		//-}
	}

	f32 lateralDistToM = lateral_dist_between_objects(o, gMarioObject);
	if (lateralDistToM > 1340.f) {
		s16 angleToMario = obj_angle_to_object(o, gMarioObject);
		gMarioState->pos[0] = o->oPosX + (sins(angleToMario) * 1340.f);
		gMarioState->pos[2] = o->oPosZ + (coss(angleToMario) * 1340.f);
	}
}

void bhv_e__target(void) {
	switch (o->oAction) {
	case 0:
		if (cur_obj_has_model(MODEL_ID_24)) {
			o->oFlags |= OBJ_FLAG_E__SG_COLLISION_CUSTOM;
			o->oAction = 2;
		} else {
			o->oFlags |= OBJ_FLAG_E__SG_CUSTOM;
			o->oAction = 1;
		}

		o->hitboxRadius = 150.f;
		o->hitboxHeight = 300.f;
		o->oIntangibleTimer = 0;

		spawn_mist_particles_variable(0, 0, 92.f);
		break;

		
	case 1:
		if (o->oShotByShotgun) {
			o->activeFlags = 0;
			o->parentObj->OBJECT_FIELD_OBJ(o->oBehParams2ndByte) = NULL;
			e__sg_obj_explode(o, 12);
		}
		break;

		
	case 2:
		load_object_collision_model();
		if (o->oShotByShotgun) {
			if (mario_is_in_air_action()) {
				o->activeFlags = 0;
				o->parentObj->OBJECT_FIELD_OBJ(o->oBehParams2ndByte) = NULL;
				e__sg_obj_explode(o, 12);
				//-play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gGlobalSoundSource);
			}
		}		
		o->oShotByShotgun = 0;
	}
}











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
        o->header.gfx.node.flags |= GRAPH_RENDER_DONT_NORMALIZE_TRANS_LERP;
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
























Gfx *e__geo_caco_eye_color(s32 callContext, struct GraphNode *node, Mat4 *unused) {
    return NULL;
}


Gfx *e__0(s32 callContext, struct GraphNode *node, Mat4 *unused) {
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
            gE_UpperAimPitch = ((s16)(calculate_pitch(gLakituState.focus, gLakituState.pos)));
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
