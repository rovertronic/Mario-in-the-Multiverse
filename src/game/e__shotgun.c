//Warning: rushed & bad

#include <PR/gbi.h>
#include "actors/group0.h"
#include "behavior_data.h"
#include "macros.h"
#include "object_fields.h"
#include "sm64.h"
#include "types.h"
#include "audio/external.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "ability.h"
#include "camera.h"
#include "e__shotgun_effects.h"
#include "game_init.h"
#include "hud.h"
#include "level_update.h"
#include "object_list_processor.h"
#include "mario.h"




//-- *** Upper animation ***


static s8 sE_ShotgunForearmState = 0;

static e__animate_sg_forearm() {//use matrix later
    if (sE_ShotgunForearmState) {
        Vtx *forearmVtx = segmented_to_virtual(e__mario_000_displaylist_004_mesh_layer_1_vtx_3);
        s32 i = 24;

        if (sE_ShotgunForearmState <= 5) {
            while (i--) {
                forearmVtx[i].v.ob[0] -= 21;
                forearmVtx[i].v.ob[1] -= 10;
            }
        } else if (sE_ShotgunForearmState <= 10) {
            while (i--) {
                forearmVtx[i].v.ob[0] += 21;
                forearmVtx[i].v.ob[1] += 10;
            }
        } else {
            sE_ShotgunForearmState = 0;
            return;
        }
        sE_ShotgunForearmState++;
    }
}

void e__set_upper_anim(struct MarioState *m, s32 animID) {
    struct AnimInfo *animInfo = &gE_UpperAnimInfo;
    struct Animation **animSegmented = segmented_to_virtual(&e__mario_anims[animID]);
    struct Animation *anim = segmented_to_virtual(*animSegmented);

    if (animInfo->curAnim != anim) {
        animInfo->animID = animID;
        animInfo->curAnim = anim;
        animInfo->animFrame = anim->startFrame + ((anim->flags & ANIM_FLAG_FORWARD) ? 1 : -1);
        animInfo->animAccel = 0;
        animInfo->animYTrans = 0;
    }
}

void e__animate_upper(void) {
    struct MarioState *m = gMarioState;
    struct AnimInfo *animInfo = &gMarioObject->header.gfx.animInfo;
    s32 animID = animInfo->animID;
    f32 accel  = 1.f;

    gE_ShotgunFlags &= ~E_SGF_LEFT_HAND;

    if (gE_ShotgunTimer == 15) {
        sE_ShotgunForearmState = TRUE; }
    e__animate_sg_forearm();

    //firing animation
    if (gE_ShotgunFlags & E_SGF_AIM_FIRE) {
        if (gE_ShotgunTimer) {
            gE_ShotgunTimer--;
            e__set_upper_anim(m, 28);
            return;
        } else {
            e__set_upper_anim(m, 29);
            gE_UpperAnimInfo.animFrame = (((u16)(gE_UpperAimYaw + DEGREES(180))) / 464);
        }
        return;

    } else if (gE_ShotgunTimer) {//SG overwrites all anims
        gE_UpperAimPitch = 0;
        gE_UpperAimYaw   = m->faceAngle[1];
        gE_ShotgunTimer--;
        e__set_upper_anim(m, 28);
        if ((m->action == ACT_IDLE) || (m->action == ACT_WALKING)) {
            gE_UpperAnimInfo.animFrame = (27 - gE_ShotgunTimer);
            return;
        }
    }


    switch (animID) {
    case MARIO_ANIM_SKID_ON_GROUND:
    case MARIO_ANIM_STOP_SKID:
        e__set_upper_anim(m, 27);
        gE_UpperAnimInfo.animYTrans = TRUE;//sync animFrame
        break;
    case MARIO_ANIM_GROUND_BONK:
        e__set_upper_anim(m, 26);
        break;


    case MARIO_ANIM_HEAVY_THROW:
        e__set_upper_anim(m, 25);
        break;
    case MARIO_ANIM_THROW_LIGHT_OBJECT:
        e__set_upper_anim(m, 24);
        break;
    case MARIO_ANIM_PLACE_LIGHT_OBJ:
        e__set_upper_anim(m, 23);
        break;
    case MARIO_ANIM_PICK_UP_LIGHT_OBJ:
        e__set_upper_anim(m, 22);
        break;

            
    case MARIO_ANIM_SLOW_LAND_FROM_DIVE:
        e__set_upper_anim(m, 21);
        break;


    case MARIO_ANIM_GRAB_HEAVY_OBJECT:
    case MARIO_ANIM_IDLE_HEAVY_OBJ:
    case MARIO_ANIM_WALK_WITH_HEAVY_OBJ:
        e__set_upper_anim(m, 20);
        break;

            
    case MARIO_ANIM_WALKING:
    case MARIO_ANIM_START_TIPTOE:
        e__set_upper_anim(m, 19);
        gE_UpperAnimInfo.animYTrans = TRUE;//sync animFrame
        break;
    case MARIO_ANIM_TIPTOE:
        e__set_upper_anim(m, 18);
        gE_UpperAnimInfo.animYTrans = TRUE;//sync animFrame
        break;


    case MARIO_ANIM_PUSHING:
    case MARIO_ANIM_STAND_AGAINST_WALL:
    case MARIO_ANIM_SIDESTEP_LEFT:
    case MARIO_ANIM_SIDESTEP_RIGHT:
        e__set_upper_anim(m, 17);
        break;
            

    case MARIO_ANIM_STAR_DANCE:
        e__set_upper_anim(m, 16);
        if (gE_UpperAnimInfo.animFrame == 41) {
            sE_ShotgunForearmState = TRUE;
            play_sound(SOUND_MITM_ABILITY_E_SHOTGUN_RACK, gGlobalSoundSource);//for some reason this doesn't play, don't know why. Gonna heep it here for now though in case we find a simple fix later
        }
        break;
            

    case MARIO_ANIM_BREAKDANCE:
        e__set_upper_anim(m, 15);
        break;


    case MARIO_ANIM_DROWNING_PART2:
    case MARIO_ANIM_WATER_DYING:
    case MARIO_ANIM_DYING_ON_BACK:
    case MARIO_ANIM_DYING_FALL_OVER:
        e__set_upper_anim(m, 14);
        break;


    case MARIO_ANIM_BACKWARD_KB:
    case MARIO_ANIM_FORWARD_KB:
        e__set_upper_anim(m, 13);
        gE_UpperAnimInfo.animYTrans = TRUE;//sync animFrame
        break;
    case MARIO_ANIM_GROUND_POUND_LANDING:
    case MARIO_ANIM_LAND_FROM_DOUBLE_JUMP:
    case MARIO_ANIM_LAND_FROM_SINGLE_JUMP:
    case MARIO_ANIM_SLIDEFLIP_LAND:
    case MARIO_ANIM_TRIPLE_JUMP_LAND:
    case MARIO_ANIM_GENERAL_LAND:
    case MARIO_ANIM_STOP_CROUCHING:
    case MARIO_ANIM_PUSH_DOOR_WALK_IN:
    case MARIO_ANIM_PULL_DOOR_WALK_IN:
        e__set_upper_anim(m, 12);
        break;
    case MARIO_ANIM_CROUCH_FROM_FAST_LONGJUMP:
    case MARIO_ANIM_CROUCH_FROM_SLOW_LONGJUMP:
        e__set_upper_anim(m, 11);
        gE_UpperAnimInfo.animFrame = 6;
        break;
    case MARIO_ANIM_START_CROUCHING:
    case MARIO_ANIM_START_CRAWLING:
    case MARIO_ANIM_CRAWLING:
    case MARIO_ANIM_STOP_CRAWLING:
        e__set_upper_anim(m, 11);
        break;
    case MARIO_ANIM_CROUCHING:
        e__set_upper_anim(m, 11);
        gE_UpperAnimInfo.animFrame = 8;
        break;


    case MARIO_ANIM_SECOND_PUNCH:
    case MARIO_ANIM_SECOND_PUNCH_FAST:
        e__set_upper_anim(m, 10);
        break;
    case MARIO_ANIM_FIRST_PUNCH:
    case MARIO_ANIM_FIRST_PUNCH_FAST:
        e__set_upper_anim(m, 9);
        break;


    case MARIO_ANIM_WALK_WITH_LIGHT_OBJ:
    case MARIO_ANIM_RUN_WITH_LIGHT_OBJ:
    case MARIO_ANIM_SLOW_WALK_WITH_LIGHT_OBJ:
    case MARIO_ANIM_STOP_SLIDE_LIGHT_OBJ:
    case MARIO_ANIM_IDLE_WITH_LIGHT_OBJ:
    case MARIO_ANIM_JUMP_LAND_WITH_LIGHT_OBJ:
    case MARIO_ANIM_JUMP_WITH_LIGHT_OBJ:
    case MARIO_ANIM_FALL_LAND_WITH_LIGHT_OBJ:
    case MARIO_ANIM_FALL_WITH_LIGHT_OBJ:
    case MARIO_ANIM_FALL_FROM_SLIDING_WITH_LIGHT_OBJ:
    case MARIO_ANIM_SLIDING_ON_BOTTOM_WITH_LIGHT_OBJ:
    case MARIO_ANIM_STAND_UP_FROM_SLIDING_WITH_LIGHT_OBJ:
        e__set_upper_anim(m, 8);
        break;

    case MARIO_ANIM_FAST_LEDGE_GRAB:
        e__set_upper_anim(m, 7);
        break;
    case MARIO_ANIM_IDLE_ON_LEDGE:
        e__set_upper_anim(m, 6);
        break;
    case MARIO_ANIM_CLIMB_DOWN_LEDGE:
    case MARIO_ANIM_SLOW_LEDGE_GRAB:
        e__set_upper_anim(m, 5);
        break;


    case MARIO_ANIM_TRIPLE_JUMP_GROUND_POUND:
    case MARIO_ANIM_START_GROUND_POUND:
    case MARIO_ANIM_GROUND_POUND:
        e__set_upper_anim(m, 4);
        break;
            

    case MARIO_ANIM_DYING_ON_STOMACH:
    case MARIO_ANIM_LAND_ON_STOMACH:
    case MARIO_ANIM_SLIDE_DIVE:
    case MARIO_ANIM_DIVE:
        e__set_upper_anim(m, 3);
        break;


    case MARIO_ANIM_FORWARD_SPINNING:
    case MARIO_ANIM_BACKWARD_SPINNING:
    case MARIO_ANIM_BACKFLIP:
    case MARIO_ANIM_TRIPLE_JUMP:
    case MARIO_ANIM_DOUBLE_JUMP_FALL:
    case MARIO_ANIM_DOUBLE_JUMP_RISE:
    case MARIO_ANIM_SLIDEJUMP:
        e__set_upper_anim(m, 2);
        gE_UpperAnimInfo.animFrame = 5;
        break;
    case MARIO_ANIM_FIRST_PERSON:
    case MARIO_ANIM_AIR_KICK:
    case MARIO_ANIM_GROUND_KICK:
    case MARIO_ANIM_FAST_LONGJUMP:
    case MARIO_ANIM_SLOW_LONGJUMP:
    case MARIO_ANIM_DROWNING_PART1:
    case MARIO_ANIM_WALK_PANTING:
    case MARIO_ANIM_FALL_OVER_BACKWARDS:
    case MARIO_ANIM_GENERAL_FALL:
    case MARIO_ANIM_FALL_FROM_SLIDE_KICK:
    case MARIO_ANIM_SLIDE_KICK:
    case MARIO_ANIM_CROUCH_FROM_SLIDE_KICK:
    case MARIO_ANIM_SLIDEFLIP:
    case MARIO_ANIM_SINGLE_JUMP:
        e__set_upper_anim(m, 2);
        break;


    case MARIO_ANIM_RUNNING:
    case MARIO_ANIM_TURNING_PART1:
    case MARIO_ANIM_TURNING_PART2:
        e__set_upper_anim(m, 1);
        gE_UpperAnimInfo.animYTrans = TRUE;//sync animFrame
        break;

    default:
        e__set_upper_anim(m, 0);//1 frame anim
    }
}








//-- *** Shotgun shot - level/object collision, object interaction, and gfx spawning ***


#define E_SHOTGUN_RANGE         5461.f
#define E_SHOTGUN_FLATTEN_RANGE 12286.f
#define E_SG_SHOT_Y_OFFSET  100.f
#define E_OUTER_RAYCAST_COUNT 4

#define E_SG_ANGLE(dist, dest, min)\
    f32 temp = (dist * 0.00375f);   \
    if (temp < min) {              \
        temp = min; }              \
    dest = temp;              

static s16 sE_ShotgunEffectFormation[E_OUTER_RAYCAST_COUNT][2] = {
    { DEGREES(27), DEGREES(15) },
    { DEGREES(27), DEGREES(-15) },
    { DEGREES(-7), DEGREES(30) },
    { DEGREES(-7), DEGREES(-30) },
};

//--Note: keep 'grate right above Mario' situation in mind
static s32 e__obj_shotgun_cast_tm(Vec3f shotOrig, Vec3f dirNorm, f32 collPointDist, s16 pitch, s16 yaw, struct Object *obj, struct Surface **flattenSurf, Vec3f flattenHitPos) {
    //returns 0: object is not shot
    //returns 1: object is shot.  returns 2
    //objects has been shot directly (crosshair within hitbox)

  //--
    Vec3f oCenter = { obj->oPosX, ((obj->oPosY + (obj->hitboxHeight * 0.5f)) - obj->hitboxDownOffset),  obj->oPosZ };
    f32 shotDistToObj = 0.f;
    vec3f_get_dist(shotOrig, oCenter, &shotDistToObj);
    //offset; where the shot points to
    Vec3f offsetPos = { (shotOrig[0] + (dirNorm[0] * shotDistToObj)),
                        (shotOrig[1] + (dirNorm[1] * shotDistToObj)),
                        (shotOrig[2] + (dirNorm[2] * shotDistToObj)), };
    f32 objDistToOffset = 0.f;
    vec3f_get_dist(oCenter, offsetPos, &objDistToOffset);//vec3f_get_dist_and_angle(oCenter, offsetPos, &objDistToOffset, &objPitchToOffset, &objYawToOffset);

    f32 div = (shotDistToObj * 0.012f);//--
    if (div < 1.f) {
        div = 1.f; }
    f32 distRange = (shotDistToObj / div);

    if (objDistToOffset < (distRange + 400.f)) {//--**
  //--
        if (shotDistToObj < E_SHOTGUN_RANGE) {

  //--
            //edgePos; edge position of approximate hitbox range
            s16 objPitchToOffset, objYawToOffset;
            vec3f_get_angle(oCenter, offsetPos, &objPitchToOffset, &objYawToOffset);

    //--
            f32 cX = coss(objPitchToOffset);
            Vec3f edgePos = { ((sins(objYawToOffset) * cX) * (obj->hitboxRadius * 0.99f)),
                              (sins(objPitchToOffset)      * (obj->hitboxHeight * 0.495f)),
                              ((coss(objYawToOffset) * cX) * (obj->hitboxRadius * 0.99f)) };
            if (objDistToOffset < sqrtf(sqr(edgePos[0]) + sqr(edgePos[1]) + sqr(edgePos[2]))) {
                struct Surface *surf;
                Vec3f hitPos, dir = { (dirNorm[0] * E_SHOTGUN_FLATTEN_RANGE),
                                      (dirNorm[1] * E_SHOTGUN_FLATTEN_RANGE),
                                      (dirNorm[2] * E_SHOTGUN_FLATTEN_RANGE) };
                find_surface_on_ray(shotOrig, dir, &surf, hitPos, (RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL | RAYCAST_FIND_WALL | RAYCAST_FIND_WATER));
                f32 shotDistToHitPos = 0.f;
                vec3f_get_dist(shotOrig, hitPos, &shotDistToHitPos);
                if (shotDistToHitPos > shotDistToObj) {
                    *flattenSurf = surf;
                    vec3f_copy(flattenHitPos, hitPos);
                    return 2;
                }
            }
            vec3f_add(edgePos, oCenter);//make edge obj-oriented

  //--
            f32 edgeDistToOffset = 0.f;
            vec3f_get_dist(edgePos, offsetPos, &edgeDistToOffset);

            if (edgeDistToOffset < distRange) {
                Vec3f dir = { (edgePos[0] - shotOrig[0]),
                              (edgePos[1] - shotOrig[1]),
                              (edgePos[2] - shotOrig[2]) };
                f32 shotDistToEdge = sqrtf(sqr(dir[0]) + sqr(dir[1]) + sqr(dir[2]));
                f32 dirMag = (E_SHOTGUN_FLATTEN_RANGE / shotDistToEdge);
                vec3f_set(dir, (dir[0] * dirMag), (dir[1] * dirMag), (dir[2] * dirMag));

  //--
                if (collPointDist < shotDistToObj) {
                    //reverse edge position
                    vec3f_sub(edgePos, oCenter);
                    vec3f_sub(oCenter, edgePos);//oCenter is now used instead of edgePos

                    s16 shotPitchToEdgeReverse, shotYawToEdgeReverse;
                    vec3f_get_angle(shotOrig, oCenter, &shotPitchToEdgeReverse, &shotYawToEdgeReverse);

                    f32 cX2 = coss(shotPitchToEdgeReverse);
                    dir[0] = ((sins(shotYawToEdgeReverse) * cX2) * E_SHOTGUN_FLATTEN_RANGE);
                    dir[1] = (sins(shotPitchToEdgeReverse)       * E_SHOTGUN_FLATTEN_RANGE);
                    dir[2] = ((coss(shotYawToEdgeReverse) * cX2) * E_SHOTGUN_FLATTEN_RANGE);
                }

  //--
                struct Surface *surf;
                Vec3f hitPos = { 0.f, 0.f, 0.f };
                find_surface_on_ray(shotOrig, dir, &surf, hitPos, (RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL | RAYCAST_FIND_WALL | RAYCAST_FIND_WATER));
                f32 shotDistToHitPos = 0.f;
                vec3f_get_dist(shotOrig, hitPos, &shotDistToHitPos);
                if (shotDistToHitPos > shotDistToObj) {
                    *flattenSurf = surf;
                    vec3f_copy(flattenHitPos, hitPos);
                    return 1;
                }
            }
        }
    }

    return 0;
}


static void e__push_obj(struct Object *obj, Vec3f dirNorm, f32 pushStrength) {
    s16 pushAngle = atan2s(dirNorm[2], dirNorm[0]);
    struct Object *push = spawn_object(obj, MODEL_NONE, bhvE_PushObj);
    push->oVelX = (sins(pushAngle) * pushStrength);
    push->oVelZ = (coss(pushAngle) * pushStrength);
}

static void e__shotgun_object_collision(Vec3f shotOrig, Vec3f dirNorm, f32 collPointDist, s16 pitch, s16 yaw) {
    s32 shotgunLists[6] = { OBJ_LIST_SURFACE, OBJ_LIST_PUSHABLE, OBJ_LIST_GENACTOR, OBJ_LIST_DESTRUCTIVE, OBJ_LIST_LEVEL, OBJ_LIST_DEFAULT };
    s32 listIndex = 6;
    s32 shotObjCount = 0;

    while (listIndex--) {
        struct ObjectNode *listHead = &gObjectLists[shotgunLists[listIndex]];
        struct ObjectNode *objNode = listHead->next;
        struct Object *obj;

        while (listHead != objNode) {
            obj = ((struct Object *) objNode);
            struct Surface *flattenSurf;
            Vec3f hitPos = { 0.f, 0.f, 0.f };
            s32 objIsShot = FALSE;

            //--**! This ordering leads to unecessary amounts of math being done every shot. For the sake of stability, I'm gonna focus on reformatting & optimizing when we need it
            if (objIsShot = e__obj_shotgun_cast_tm(shotOrig, dirNorm, collPointDist, pitch, yaw, obj, &flattenSurf, hitPos)) {
                if (shotObjCount >= gE_MaxObjsHitPerShot) {
                    return; }

                if (obj->oFlags & (OBJ_FLAG_E__SG_ENEMY | OBJ_FLAG_E__SG_BREAKABLE)) {
                    if (obj->oIntangibleTimer == 0) {//--**
                        shotObjCount++;
                        obj->oShotByShotgun += objIsShot;

                        e__sg_obj_shot_sparks(obj);//effect

                        if (gCurrLevelNum == LEVEL_E) {//maybe find a better method later
                            if (obj->oShotByShotgun == 2) {
                                obj->oHealth -= 3; }
                            else if (obj->oShotByShotgun == 1) {
                                obj->oHealth -= (3 - (((random_u16() % 3) == 0))); }
                        } else {
                            obj->oHealth--; }

                        if ((obj->oHealth <= 0) || (obj->oHealth == (2048 - 1))) {
                            obj_spawn_loot_yellow_coins(obj, obj->oNumLootCoins, 20.f);

                            if (obj->oFlags & OBJ_FLAG_E__SG_ENEMY) {
                                //flatten against wall
                                if (flattenSurf != NULL) {
                                    if (SURFACE_IS_NEW_WATER(flattenSurf)) {
                                        spawn_object(obj, MODEL_WATER_SPLASH, bhvWaterSplash);
                                    } else {
                                        combo_meter = 201;
                                        struct Object *flatObj = spawn_object(obj, obj_get_model_id(obj), bhvE_FlattenedObj);
                                        flatObj->oDeathSound = obj->oDeathSound;
                                        flatObj->oUpVel = 1.f;//oUpVel used as scale osc mag
                                        flatObj->oAnimState = obj->oAnimState;
                                        flatObj->oOpacity   = obj->oOpacity;
                                        *((struct AnimInfo *)(&flatObj->header.gfx.animInfo)) = *((struct AnimInfo *)(&obj->header.gfx.animInfo));
                                        vec3f_copy(&flatObj->oVelX, obj->header.gfx.scale);//oVelX used as base scale
                                        vec3f_set(&flatObj->oVelX, (flatObj->oVelX * 1.6f), (flatObj->oVelY * 1.6f), (flatObj->oVelZ * 1.6f));

                                        Vec3f hitPosOffset = { (dirNorm[0] * 40.f), (dirNorm[1] * 40.f), (dirNorm[2] * 40.f) };
                                        vec3f_sub(hitPos, hitPosOffset);
                                        vec3f_copy(&flatObj->oPosX, hitPos);

                                        flatObj->oFaceAnglePitch = 0;
                                        if (absf(flattenSurf->normal.y) < 0.01f) {//NORMAL_FLOOR_THRESHOLD
                                            flatObj->oFaceAngleYaw = SURFACE_YAW(flattenSurf); }
                                        else {
                                            flatObj->oFaceAngleYaw = (yaw + DEGREES(180));
                                            flatObj->oAction = 1;
                                        }
                                        flatObj->oFaceAngleRoll = 0;

                                        flatObj->OBJECT_FIELD_S16P(0x1B) = flattenSurf;
                                    }
                                } else {
                                    if (obj->oDeathSound) {
                                        create_sound_spawner(obj->oDeathSound); }
                                }


                            } else {
                            //--OBJ_FLAG_E__SG_BREAKABLE
                                e__sg_obj_explode(obj, 4);//effect
                                if (obj->oDeathSound) {
                                    create_sound_spawner(obj->oDeathSound); }
                            }

                            obj->activeFlags = 0;
                        } else if (gCurrLevelNum == LEVEL_E) {//maybe find a better method later
                            obj->oVelX = (dirNorm[0] * 50.f);
                            obj->oVelZ = (dirNorm[2] * 50.f);
                        } else {
                            e__push_obj(obj, dirNorm, 50.f); }
                    }


                } else if (obj->oFlags & OBJ_FLAG_E__SG_BOSS) {
                    if (obj->oIntangibleTimer == 0) {//--**
                        obj->oShotByShotgun += objIsShot;
                        shotObjCount++;

                        Vec3f pos       = { obj->oPosX, obj->oPosY, obj->oPosZ };
                        Vec3f offset = { (dirNorm[0] * 100.f), (dirNorm[1] * 100.f), (dirNorm[2] * 100.f) };                        
                        vec3f_add(pos, offset);
                        struct SGSmoke *smoke = e__sg_smoke(pos);
                        if (smoke != NULL) {
                            smoke->timer = 3;
                            smoke->scale = 5.f;
                        }
                        e__push_obj(obj, dirNorm, 100.f);
                    }


                } else if (obj->oFlags & OBJ_FLAG_E__SG_CUSTOM) {
                    if (obj->oIntangibleTimer == 0) {//--**
                        obj->oShotByShotgun += objIsShot;
                        shotObjCount++;

                        e__sg_obj_shot_sparks(obj);
                    }//effect
                }
            }

            objNode = objNode->next;
        }
    }
}


static struct Surface *e__shotgun_raycast(Vec3f orig, Vec3f dir, Vec3f dirNorm, Vec3f hitPos, struct Object **shotCollisionObjs) {
    struct Surface *surf;
    find_surface_on_ray(orig, dir, &surf, hitPos, (RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL | RAYCAST_FIND_WALL | RAYCAST_FIND_WATER));
    if (surf != NULL) {
        struct Object *obj = surf->object;

        if (SURFACE_IS_NEW_WATER(surf)) {
            spawn_object(gMarioObject, MODEL_WATER_SPLASH, bhvWaterSplash); }
        else {//effect
            //wall damage
            Vec3f pos = { hitPos[0], hitPos[1], hitPos[2] };
            f32 *surfNorm = ((f32 *)(&surf->normal));
            if (obj == NULL) {
                e__sg_wall_damage(pos, surf); }
            //smoke
            Vec3f offset = { (surfNorm[0] * 100.f), (surfNorm[1] * 100.f), (surfNorm[2] * 100.f) };
            vec3f_add(pos, offset);
            struct SGSmoke *newSmoke = e__sg_smoke(pos);
            if (obj != NULL) {
                if (newSmoke != NULL) {
                    newSmoke->timer = 3; }
            }
            //piece
            Vec3f random = { (random_float() * 100.f), (random_float() * 100.f), (random_float() * 100.f) };
            vec3f_add(pos, random);
            Vec3f vel = { (surfNorm[0] * 20.f), (surfNorm[1] * 35.f), (surfNorm[2] * 20.f) };
            e__sg_piece(pos, vel);
            e__sg_piece(pos, vel);
            //spark
            e__sg_spark(pos, (0.5f + (random_float() * 3.f)));
            e__sg_spark(pos, (0.5f + (random_float() * 3.f)));
        }

        //objects with collision
        if (obj != NULL) {
            if (obj->oFlags & OBJ_FLAG_E__SG_COLLISION_BREAKABLE) {
                //check if obj hasn't been shot yet
                s32 notShot = TRUE;
                s32 i = (E_OUTER_RAYCAST_COUNT + 1);
                while (i--) {
                    if (shotCollisionObjs[i] == obj) {
                        return FALSE; }
                }
                //shoot obj
                if (notShot) {
                    if ((obj->oHealth <= 1) || (obj->oHealth == 2048)) {
                        s32 size = ((s32)(sqrtf(sqr(obj->hitboxRadius) + sqr(obj->hitboxHeight))));
                        obj->oPosY += (obj->hitboxHeight * 0.5f);
                        e__sg_obj_explode(obj, (size / 30));//effect

                        set_camera_shake_from_point(SHAKE_POS_MEDIUM, obj->oPosX, obj->oPosY, obj->oPosZ);
                        play_sound(SOUND_GENERAL_WALL_EXPLOSION, obj->header.gfx.cameraToObject);
                        obj->activeFlags = 0;
                    } else {
                        obj->oHealth--;
                        obj_set_model(obj, (obj_get_model_id(obj) + 1));
                    }
                    //put obj in shot list, so no other raycasts can affect it this frame
                    struct Object **shotObjs = shotCollisionObjs;
                    while (*shotObjs != NULL) {
                        shotObjs++; }
                    *shotObjs = obj;
                }
            } else if (obj->oFlags & OBJ_FLAG_E__SG_COLLISION_CUSTOM) {
                obj->oShotByShotgun += 1; }
        }
    }
    return surf;//determines if collPointDist gets set
}


static void e__shotgun_shot(Vec3f shotOrig, Vec3f shotVisualPos, s16 pitch, s16 yaw) {
    set_camera_shake_from_hit(SHAKE_GROUND_POUND);
    if (random_u16() & 1) {
        play_sound(SOUND_MITM_ABILITY_E_SHOTGUN, gGlobalSoundSource); }
    else {
        if (random_u16() & 1) {
            play_sound(SOUND_MITM_ABILITY_E_SHOTGUN2, gGlobalSoundSource); }
        else {
            play_sound(SOUND_MITM_ABILITY_E_SHOTGUN3, gGlobalSoundSource); }
    }
    //Mario effects
    struct Object *muzzleFlash = spawn_object(gMarioObject, MODEL_E__MUZZLE_FLASH, bhvE_MuzzleFlash);
    vec3f_copy(&muzzleFlash->oPosX, shotVisualPos);
    muzzleFlash->oFaceAnglePitch = -pitch;
    muzzleFlash->oFaceAngleYaw   = yaw;
    //used for Mario's effects and shot direction math
    f32 cX = coss(pitch);
    Vec3f dir, hitPos, dirNorm = { (sins(yaw) * cX),
                                   (sins(pitch)),
                                   (coss(yaw) * cX) };
    struct SGSmoke *smoke = e__sg_smoke(shotVisualPos);
    if (smoke != NULL) {
        smoke->timer = 4;
        smoke->scale = 2.f;
        Vec3f smokeOffset = { (dirNorm[0] * 80.f), (dirNorm[1] * 80.f), (dirNorm[2] * 80.f) };
        vec3f_add(smoke->pos, smokeOffset);
    }


  //--Shot effects, level & object collision
    vec3f_set(dir, (dirNorm[0] * E_SHOTGUN_RANGE), (dirNorm[1] * E_SHOTGUN_RANGE), (dirNorm[2] * E_SHOTGUN_RANGE));
    //middle raycast; not only checks for objects, but determines collPointDist as well
    struct Object *shotCollisionObjs[E_OUTER_RAYCAST_COUNT + 1] = { NULL };
    f32 collPointDist = E_SHOTGUN_RANGE;
    if (e__shotgun_raycast(shotOrig, dir, dirNorm, hitPos, &shotCollisionObjs) != NULL) {
        vec3f_get_dist(shotOrig, hitPos, &collPointDist); }
    //outer raycasts
    s32 i = E_OUTER_RAYCAST_COUNT;
    while (i--) {
        s32 div;
        E_SG_ANGLE(collPointDist, div, 3.f)
        s16 fPitch = sE_ShotgunEffectFormation[i][0];
        s16 fYaw   = sE_ShotgunEffectFormation[i][1];
        s16 dirPitch = (pitch + (fPitch / div));
        s16 dirYaw   = (yaw   + (fYaw   / div));
        f32 cX2 = coss(dirPitch);
        Vec3f outerDir = { (sins(dirYaw) * cX2),
                           (sins(dirPitch)),
                           (coss(dirYaw) * cX2) };
        vec3f_set(outerDir, (outerDir[0] * E_SHOTGUN_RANGE), (outerDir[1] * E_SHOTGUN_RANGE), (outerDir[2] * E_SHOTGUN_RANGE));
        e__shotgun_raycast(shotOrig, outerDir, dirNorm, hitPos, &shotCollisionObjs);
    }


  //--Object interaction
    e__shotgun_object_collision(shotOrig, dirNorm, collPointDist, pitch, yaw);
}








//-- *** Actions ***

void e__fire_shotgun(void) {
    if (using_ability(ABILITY_E_SHOTGUN)) {
        if (gE_ShotgunFlags & E_SGF_AIM_MODE) {
            gE_ShotgunFlags |= E_SGF_AIM_FIRE; }

        if (gE_ShotgunTimer == 0) {
            if (gPlayer1Controller->buttonDown & L_TRIG) {
                struct MarioState *m = gMarioState;
                if (m->numGlobalCoins) {
                    m->numGlobalCoins--; }
                else {
                    gE_ShotgunTimer = 26;
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                    return;
                }

                gE_UpperAnimInfo.animFrame = 0;
                Vec3f shotVisualPos = { m->pos[0], (m->pos[1] + E_SG_SHOT_Y_OFFSET), m->pos[2] };

                if (gE_ShotgunFlags & E_SGF_AIM_MODE) {
                  //aim mode
                    struct LakituState *l = &gLakituState;
                    s16 rX = calculate_pitch(l->pos, l->focus);
                    s16 rY = (l->yaw + DEGREES(180));
                    e__shotgun_shot(l->focus, shotVisualPos, rX, rY);
                } else {
                  //lakitu mode
                    m->marioBodyState->torsoAngle[0] = -0x500;
                    e__shotgun_shot(shotVisualPos, shotVisualPos, 0, m->faceAngle[1]);
                }
                gE_ShotgunTimer = 26;
            }
        }
    }
}

void e__fire_shotgun_air(void) {//--**combine with e__fire_shotgun later
    if (using_ability(ABILITY_E_SHOTGUN)) {
        struct MarioState *m = gMarioState;
        if (mario_is_in_air_action()) {
            if (gPlayer1Controller->buttonPressed & L_TRIG) {            
                if (!(gE_ShotgunFlags & E_SGF_AIR_SHOT_USED)) {
                    gE_ShotgunFlags |= E_SGF_AIR_SHOT_USED;
                    if (m->numGlobalCoins) {
                        m->numGlobalCoins--; }
                    else {
                        gE_ShotgunTimer = 26;
                        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                        return;
                    }    

                    e__set_upper_anim(m, 2);
                    gE_UpperAnimInfo.animFrame = 0;

                    s32 action = m->action;
                    f32 vel = 0.f;
                    if ((action == ACT_LONG_JUMP) || (action == ACT_SLIDE_KICK)) {
                        vel = 36.f; }
                    else {
                        vel = 54.f; }
                    if (m->vel[1] < vel) {
                        m->vel[1] = vel; }
                    else {
                        m->vel[1] += 10.f; }
                    m->flags        &= ~MARIO_JUMPING;

                    //shot
                    Vec3f shotPos = { (m->pos[0] + (sins(m->faceAngle[1]) * E_SG_SHOT_Y_OFFSET)),
                                            (m->pos[1] + E_SG_SHOT_Y_OFFSET),
                                            (m->pos[2] + (coss(m->faceAngle[1]) * E_SG_SHOT_Y_OFFSET)) };
                    e__shotgun_shot(shotPos, shotPos, DEGREES(270), 0);
                    gE_ShotgunTimer = 26;
                }
            }
        }
    }
}
