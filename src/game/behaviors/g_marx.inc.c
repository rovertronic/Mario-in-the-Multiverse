#include "src/game/area.h"
#include "include/sounds.h"

enum MarxActions {
    MARX_ACT_CUTSCENE,
    MARX_ACT_IDLE_FLIGHT,
    MARX_ACT_FLY_ACROSS,
    MARX_ACT_TELEPORT,
    MARX_ACT_CUTTER,
    MARX_ACT_THORNS,
    MARX_ACT_BLACK_HOLE,
    MARX_ACT_ARROWS,
    MARX_ACT_LASER,
    MARX_ACT_ICE_BOMB,
    MARX_ACT_SHADOW_BURST,
    MARX_ACT_DEAD
};

static struct ObjectHitbox sMarxHitbox = {
    /* interactType:      */ INTERACT_NONE,
    /* downOffset:        */ 50,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 130,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 120,
    /* hurtboxHeight:     */ 110,
};

static struct ObjectHitbox sMarxCutterHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 50,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 110,
    /* height:            */ 110,
    /* hurtboxRadius:     */ 100,
    /* hurtboxHeight:     */ 100,
};
static struct ObjectHitbox sMarxThornsHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 150,
    /* height:            */ 300,
    /* hurtboxRadius:     */ 140,
    /* hurtboxHeight:     */ 290,
};
static struct ObjectHitbox sMarxArrowHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 60,
    /* height:            */ 120,
    /* hurtboxRadius:     */ 40,
    /* hurtboxHeight:     */ 80,
};

void marx_act_cutscene(void) {
    if (o->oTimer == 0) {
        gMarxArenaScroll = 0.0f;
        cur_obj_boss_shimmer_reset();
    }
    if (o->oTimer == 120) {
        cur_obj_play_sound_2(SOUND_MITM_LEVEL_G_MARX_TELEPORT);
        o->oAction = MARX_ACT_IDLE_FLIGHT;
        o->oMarxTeleportTimer = 7;
                        o->oMarxTeleportX = o->oPosX;
                        o->oMarxTeleportY = o->oPosY;
                        o->oMarxTeleportZ = o->oPosZ;
                        cur_obj_unhide();
                        cur_obj_become_tangible();
                        gMarxArenaScroll = 1.0f;

        
    }
    else {
        cur_obj_hide();
        cur_obj_become_intangible();
        gMarxArenaScroll = (f32)o->oTimer / 120.0f;
    }

    if (_60fps_on) {
        gMarxArenaScroll *= .5f;
    }
}

s32 marx_is_above_floor(void) {
    struct Surface * dummyfloor;
    find_floor(o->oPosX,o->oPosY,o->oPosZ,&dummyfloor);
    return (dummyfloor != NULL);
}

void marx_act_idle_flight(void) {
    if (o->oTimer == 0) {
        cur_obj_init_animation(0);
    }
    obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x400);
    if (o->oTimer == 30) {
        u8 newAttack = 0;
        while (newAttack == 0) {
            switch (random_u16() % 11) {
                case 0: 
                case 1: o->oAction = MARX_ACT_CUTTER;
                break;
                case 2: o->oAction = MARX_ACT_THORNS;
                break;
                case 3:
                case 4: o->oAction = MARX_ACT_BLACK_HOLE;
                if (!marx_is_above_floor()) {
                    //black hole is useless if marx is off the arena
                    o->oAction = MARX_ACT_ARROWS;
                    if (o->oMarxLastAttack != MARX_ACT_ARROWS) o->oMarxLastAttack = MARX_ACT_IDLE_FLIGHT;
                }
                break;
                case 5: o->oAction = MARX_ACT_ICE_BOMB;
                break;
                case 6:
                case 7: o->oAction = MARX_ACT_FLY_ACROSS;
                break;
                case 8:
                case 9: o->oAction = MARX_ACT_CUTTER;
                break;
                case 10: o->oAction = MARX_ACT_ARROWS;
                    if (o->oMarxLastAttack != MARX_ACT_ARROWS) o->oMarxLastAttack = MARX_ACT_IDLE_FLIGHT;
                break;
            }

            if (o->oAction != o->oMarxLastAttack) {
                newAttack = 1;
            }
        }

        if (o->oMarxLastAttack != MARX_ACT_IDLE_FLIGHT) o->oMarxLastAttack = o->oAction;
        
    }
}


void marx_act_fly_across(void) {
    switch (o->oSubAction) {
        case 0:
            o->oSubAction++;
            cur_obj_play_sound_1(SOUND_MITM_LEVEL_G_MARX_LAUGH_1);
        break;
        case 1:
            if (cur_obj_check_if_at_animation_end()) {
                cur_obj_init_animation(1);
                o->oTimer = 0;
                o->oSubAction++;
                cur_obj_play_sound_1(SOUND_MITM_LEVEL_G_MARX_LAUGH_3);
            }
        break;
        case 2:
            if (o->oTimer >= 10 && o->oTimer < 50) {
                o->oForwardVel = approach_s16_asymptotic(o->oForwardVel, 40.0f, 4);
            }
            if (o->oTimer >= 50) {
                o->oForwardVel = approach_s16_asymptotic(o->oForwardVel, 0.0f, 4);
            }

            if (o->oTimer == 60) {
                cur_obj_init_animation(0);
                o->oForwardVel = 0;
                o->oAction = MARX_ACT_IDLE_FLIGHT;
            }
        break;
    }

    cur_obj_move_xz_using_fvel_and_yaw();
}

void marx_act_teleport(void) {
    if (o->oTimer % 20 == 0) {
        cur_obj_init_animation(2);
        o->header.gfx.animInfo.animFrame = 0;
        o->oSubAction++;
        if (o->oSubAction < 6) {
            o->oMarxTeleportTimer = 0;
            o->oMarxTeleportX = (random_u16() % 1000) - 500;
            o->oMarxTeleportY = (random_u16() % 300) + gMarioState->pos[1] + 100;
            o->oMarxTeleportZ = (random_u16() % 1000) - 500;
            cur_obj_play_sound_1(SOUND_MITM_LEVEL_G_MARX_TELEPORT);
        }
        else {
            o->oAction = MARX_ACT_IDLE_FLIGHT;
            cur_obj_init_animation(0);
        }
        
    }
}

void marx_act_cutter(void) {
    switch (o->oSubAction) {
        case 0:
            cur_obj_init_animation(2);
            
            o->oSubAction++;
        break;
        case 1:
            if (o->oTimer < 20) {
                obj_scale_xyz(o, 1.0f - 0.5f*sins(o->oTimer * 0x666), 1.0f - 0.25f*sins(o->oTimer * 0x666), 1.0f);
            }
            else {
                cur_obj_scale(1.0f);
            }
            if (o->oTimer == 15) {
                for (int i = 0; i < 4; i++) {
                    spawn_object_relative(i, 0, 0, 10, o, MODEL_G_MARX_CUTTER, bhvGMarxCutter);
                }
                cur_obj_play_sound_1(SOUND_MITM_LEVEL_G_MARX_CUTTER);
            }
            if (cur_obj_check_if_at_animation_end()) {
                cur_obj_init_animation(0);
                o->oAction = MARX_ACT_IDLE_FLIGHT;
            }
        break;
    }
}

void find_valid_seed_position(Vec3f pos) {
    u8 posIterations = 0;
    f32 posX = 0;
    f32 posZ = 0;

    while (posIterations < 10) {
        posX = gMarioState->pos[0] + ((random_u16() % 1200) - 600);
        posZ = gMarioState->pos[2] + ((random_u16() % 1200) - 600);

        if (find_floor_height(posX, gMarioState->pos[1] + 200, posZ) > -10000) {
            posIterations = 10;
        }
        posIterations++;
    }

    vec3f_set(pos, posX, 0, posZ);
    pos[0] = posX;
    pos[2] = posZ;
}

void marx_act_thorns(void) {
    switch (o->oSubAction) {
        case 0:
            o->oSubAction++;
            cur_obj_init_animation(3);
            if (gCamera->mode != CAMERA_MODE_SHOCK_ROCKET && !(gE_ShotgunFlags & E_SGF_AIM_MODE)) gLakituState.mode = CAMERA_MODE_8_DIRECTIONS;
            cur_obj_play_sound_1(SOUND_MITM_LEVEL_G_MARX_LAUGH_2);
        break;
        case 1:
            if (o->oTimer == 18) {
                o->oVelY = 30;
            }
            if (o->oTimer >= 18) {
                o->oVelY += 3;
            }

            if (o->oTimer == 90) {
                o->oSubAction++;
                o->oTimer = 0;
            }
        break;
        case 2:
            o->oVelY = 0;

            if (o->oTimer % 18 == 1) {
                Vec3f spawnPos;
                find_valid_seed_position(spawnPos);
                spawn_object_abs_with_rot(o, 0, MODEL_G_MARX_SEED, bhvGMarxSeed, spawnPos[0], gMarioState->pos[1] + 1000, spawnPos[2], 0, 0, 0);
            }

            if (o->oTimer == 91) {
                o->oSubAction++;
                o->oTimer = 0;
            }
        break;
        case 3:
        if (o->oTimer == 150) {
            switch (random_u16() % 3) {
                case 0: o->oAction = MARX_ACT_ARROWS;
                        o->oHomeY = gMarioState->pos[1] + 200;
                break;
                case 1:
                    o->oAction = MARX_ACT_LASER;
                break;
                case 2:
                    o->oAction = MARX_ACT_TELEPORT;
                break;
            }
        }
        break;
    }
    o->oPosY += o->oVelY;
}

void marx_act_black_hole(void) {
    switch (o->oSubAction) {
        case 0:
            if (o->oTimer == 0) {
                cur_obj_play_sound_1(SOUND_MITM_LEVEL_G_MARX_LAUGH_4);
            }
            if (cur_obj_check_if_at_animation_end()) {
                o->oSubAction++;
                gSecondCameraFocus = o;
            if (gCamera->mode != CAMERA_MODE_SHOCK_ROCKET && !(gE_ShotgunFlags & E_SGF_AIM_MODE)) gLakituState.mode = CAMERA_MODE_MARX_FIGHT;
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_NONE];
                spawn_object_relative(0, 0, 0, 0, o, MODEL_G_MARX_HALF_LEFT, bhvGMarxHalf);
                spawn_object_relative(1, 0, 0, 0, o, MODEL_G_MARX_HALF_RIGHT, bhvGMarxHalf);
                o->oTimer = 0;
            }
            
        break;
        case 1:

            if (o->oTimer == 20) {
                spawn_object_relative(0, 0, 0, 0, o, MODEL_G_MARX_BLACK_HOLE, bhvGMarxBlackHole);
                cur_obj_play_sound_1(SOUND_MITM_LEVEL_G_MARX_BLACK_HOLE);
            }

            if (o->oTimer == 150 && gMarioState->action != ACT_CUTSCENE_CONTROLLED && gMarioState->action != ACT_HARD_BACKWARD_AIR_KB) {
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MARX];
                switch (random_u16() % 3) {
                    case 0:
                        o->oAction = MARX_ACT_IDLE_FLIGHT;
                        o->oMarxTeleportTimer = 7;
                        o->oMarxTeleportX = o->oPosX;
                        o->oMarxTeleportY = o->oPosY;
                        o->oMarxTeleportZ = o->oPosZ;
                        cur_obj_play_sound_1(SOUND_MITM_LEVEL_G_MARX_TELEPORT);
                    break;
                    case 1:
                        o->oAction = MARX_ACT_LASER;
                        o->oMarxTeleportTimer = 7;
                    break;
                    case 2:
                        o->oAction = MARX_ACT_ARROWS;
                        o->oHomeY = gMarioState->pos[1] + 200;
                        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_NONE];
                    break;
                }
            }

            if (gMarioState->action == ACT_CUTSCENE_CONTROLLED) {
                o->oPosX = 500;
                o->oPosY = 700;
                o->oPosZ = 0;
                o->oSubAction++;
                o->oTimer = 0;
            }
        break;
        case 2:
            if (o->oTimer == 80) {
                o->oMarxTeleportTimer = 7;
                o->oMarxTeleportX = 500;
                o->oMarxTeleportY = 700;
                o->oMarxTeleportZ = 0;
                cur_obj_init_animation(0);
                o->oAction = MARX_ACT_IDLE_FLIGHT;
                cur_obj_play_sound_1(SOUND_MITM_LEVEL_G_MARX_TELEPORT);
            }
        break;
    }
}

void marx_act_arrows(void) {
    switch (o->oSubAction) {
        case 0:;
            if (o->oMarxLastAttack != MARX_ACT_IDLE_FLIGHT) {
            u16 randomAngle = random_u16();
            o->oPosX = 1500*sins(randomAngle);
            o->oPosZ = 1500*coss(randomAngle);
            o->oPosY = 0;
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MARX];
            o->oSubAction++;
            obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x800);
            }
            else {
                o->oSubAction = 5;
                o->oForwardVel = 20;
                o->oVelY = 4;
                cur_obj_init_animation(1);
                o->oTimer = 0;
            }
        break;
        case 1:
            o->oPosY = approach_f32_asymptotic(o->oPosY, o->oHomeY, 0.08f);
            gSecondCameraFocus = o;
            if (gCamera->mode != CAMERA_MODE_SHOCK_ROCKET && !(gE_ShotgunFlags & E_SGF_AIM_MODE)) gLakituState.mode = CAMERA_MODE_MARX_FIGHT;
            cur_obj_init_animation(4);
            if (o->oTimer == 30) {
                o->oSubAction++;
                o->oTimer = 0;
            }
        break;
        case 2:
            if (o->oTimer < 20) {
                obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x600);
            }
            if (o->oTimer == 30) {
                o->oSubAction++;
                o->oTimer = 0;
                cur_obj_play_sound_1(SOUND_MITM_LEVEL_G_MARX_ARROWS);
            }
        break;
        case 3:;
            f32 arrowX = 50 * sins(o->oFaceAngleYaw);
            f32 arrowZ = 50 * coss(o->oFaceAngleYaw);
            f32 offset = random_u16() % 400 - 200;
            arrowX += offset * coss(o->oFaceAngleYaw);
            arrowZ += offset * sins(o->oFaceAngleYaw);
            struct Object *arrow = spawn_object_relative(0, arrowX, random_u16() % 400 - 200, arrowZ, o, MODEL_G_MARX_ARROW, bhvGMarxArrow);
            obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x50);

            if (o->oTimer == 90) {
                o->oSubAction++;
                o->oForwardVel = 20;
                o->oVelY = 4;
                cur_obj_init_animation(1);
                o->oTimer = 0;
            }
        break;
        case 4:
            if (gCamera->mode != CAMERA_MODE_SHOCK_ROCKET && !(gE_ShotgunFlags & E_SGF_AIM_MODE)) gLakituState.mode = CAMERA_MODE_8_DIRECTIONS;
            o->oVelY += 1;
            o->oForwardVel += 2;

            o->oPosY += o->oVelY;
            cur_obj_move_xz_using_fvel_and_yaw();

            if (o->oTimer == 60) {
                o->oAction = MARX_ACT_IDLE_FLIGHT;
                o->oMarxTeleportTimer = 7;
                o->oMarxTeleportX = 0;
                o->oMarxTeleportY = 700;
                o->oMarxTeleportZ = 0;
                o->oForwardVel = 0;
                o->oVelY = 0;
                cur_obj_play_sound_1(SOUND_MITM_LEVEL_G_MARX_TELEPORT);
            }
        break;
        case 5:
            if (gCamera->mode != CAMERA_MODE_SHOCK_ROCKET && !(gE_ShotgunFlags & E_SGF_AIM_MODE)) gLakituState.mode = CAMERA_MODE_8_DIRECTIONS;
            o->oVelY += 1;
            o->oForwardVel += 2;

            o->oPosY += o->oVelY;
            cur_obj_move_xz_using_fvel_and_yaw();

            if (o->oTimer == 60) {
                switch (random_u16() % 2) {
                    case 0:
                        o->oAction = MARX_ACT_LASER;
                        o->oMarxTeleportTimer = 7;
                    break;
                    case 1:
                        o->oAction = MARX_ACT_ARROWS;
                        o->oHomeY = gMarioState->pos[1] + 200;
                        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_NONE];
                        o->oSubAction = 0;
                        o->oTimer = 0;
                    break;
                }
            }
        break;
    }
}

void marx_act_laser(void) {
    switch (o->oSubAction) {
        case 0:;
            gSecondCameraFocus = o;
            if (gCamera->mode != CAMERA_MODE_SHOCK_ROCKET && !(gE_ShotgunFlags & E_SGF_AIM_MODE)) gLakituState.mode = CAMERA_MODE_MARX_FIGHT;
            u16 randomAngle = random_u16();
            o->oMarxTeleportX = 1200*sins(randomAngle);
            o->oMarxTeleportZ = 1200*coss(randomAngle);
            o->oMarxTeleportY = gMarioState->pos[1] + 200;
            o->oMarxTeleportTimer = 7;
            o->oSubAction++;
            cur_obj_play_sound_1(SOUND_MITM_LEVEL_G_MARX_TELEPORT);
        break;
        case 1:
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_G_MARX_MOUTH_FULL];
            obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x400);
            //o->oMarxLaserBody->oFaceAngleYaw = o->oFaceAngleYaw;
            o->oPosX += (random_u16() % 3) - 1.5f;
            o->oPosY += (random_u16() % 3) - 1.5f;
            o->oPosZ += (random_u16() % 3) - 1.5f;
            cur_obj_scale(1 + ((f32)o->oTimer)/90.0f + (0.1f * sins(random_u16())));
            if (o->oTimer == 45) {
                o->oSubAction++;
                o->oTimer = 0;
            }
        break;
        case 2:
        cur_obj_scale(1.5f);
        o->oPosX += (random_u16() % 6) - 3;
            o->oPosY += (random_u16() % 6) - 3;
            o->oPosZ += (random_u16() % 6) - 3;
            if (o->oTimer == 18) {
                cur_obj_play_sound_1(SOUND_MITM_LEVEL_G_MARX_LASER);
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_G_MARX_MOUTH_OPEN];
                o->oForwardVel = -150;
                spawn_object_relative(0, 0, 0, 0, o, MODEL_G_MARX_LASER, bhvGMarxLaser);
                o->oSubAction++;
                o->oTimer = 0;
            }
        break;
        case 3:
            cur_obj_move_xz_using_fvel_and_yaw();
            if (o->oTimer < 5) {
                cur_obj_scale(1.5f - ((f32)(o->oTimer) / 10.0f));
            }
            else {
                cur_obj_scale(1.0f);
            }
            if (o->oTimer == 30) {
                //obj_mark_for_deletion(o->oMarxLaserBody);
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_NONE];
                if (gCamera->mode != CAMERA_MODE_SHOCK_ROCKET && !(gE_ShotgunFlags & E_SGF_AIM_MODE)) gLakituState.mode = CAMERA_MODE_8_DIRECTIONS;
            }

            if (o->oTimer == 120) {
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MARX];
                o->oAction = MARX_ACT_IDLE_FLIGHT;
                o->oMarxTeleportTimer = 7;
                o->oMarxTeleportX = 0;
                o->oMarxTeleportY = 700;
                o->oMarxTeleportZ = 0;
                o->oForwardVel = 0;
                o->oVelY = 0;
                cur_obj_play_sound_2(SOUND_MITM_LEVEL_G_MARX_TELEPORT);
            }
        break;
    }
}

void marx_act_ice_bomb(void) {
    switch (o->oSubAction) {
        case 0:
            //o->oMarxLaserBody = spawn_object(o, MODEL_G_MARX_MOUTH_FULL, bhvGMarxBodyLaser);
            //o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_NONE];
            cur_obj_play_sound_1(SOUND_MITM_LEVEL_G_MARX_LAUGH_3);
            o->oSubAction++;
        break;
        case 1:
            o->oPosY += 8;
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_G_MARX_MOUTH_FULL];
            if (o->oTimer == 45) {
                o->oSubAction++;
                o->oTimer = 0;
                spawn_object_relative(0, 0, -40, 0, o, MODEL_G_MARX_ICE_BOMB, bhvGMarxIceBomb);
            }
        break;
        case 2:
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_G_MARX_MOUTH_OPEN];
            o->oFaceAnglePitch = 0x1000;
            if (o->oTimer == 18) {
                o->oSubAction++;
                o->oTimer = 0;
            }
        break;
        case 3:
            if (o->oTimer == 3) {
                o->oMarxTeleportTimer = 0;
                cur_obj_play_sound_1(SOUND_MITM_LEVEL_G_MARX_TELEPORT);
                o->oMarxTeleportX = 0;
                o->oMarxTeleportY = 700;
                o->oMarxTeleportZ = 0;
            }
            o->oFaceAnglePitch = 0;
            if (o->oTimer == 10) {
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MARX];
                o->oAction = MARX_ACT_IDLE_FLIGHT;
                o->oForwardVel = 0;
                o->oVelY = 0;
            }
        break;
    }
}

void marx_act_dead(void) {

    switch (o->oSubAction) {
        case 0:
            if (o->oTimer == 0) {
            cur_obj_init_animation(5);
            cur_obj_play_sound_1(SOUND_MITM_G_MARX_FINAL_HIT);
            }
            if (o->oTimer == 30) {
            o->oSubAction++;
            o->oTimer = 0;
            }
        break;
        case 1:
            /*
            if (o->oTimer % 3 == 0) {
                spawn_object_relative(0, (random_u16() % 400 - 200), (random_u16() % 400 - 200), (random_u16() % 400 - 200), o, MODEL_EXPLOSION, bhvExplosionVisual);
            }
            if (o->oTimer == 60) {
                for (int i = 0; i < 10; i++) {
                    spawn_object_relative(0, (random_u16() % 400 - 200), (random_u16() % 400 - 200), (random_u16() % 400 - 200), o, MODEL_EXPLOSION, bhvExplosionVisual);
                }
                cur_obj_play_sound_1(SOUND_MITM_LEVEL_G_MARX_SCREAM);
                cur_obj_play_sound_2(SOUND_MITM_G_MARX_EXPLODE);
                cur_obj_hide();
                o->oTimer = 0;
                o->oSubAction++;
            }
            */
            if (cur_obj_boss_shimmer_death(0.0f,1.0f)) {
                cur_obj_hide();
                o->oTimer = 0;
                o->oSubAction++;
            }
        break;
        case 2:
            gMarxArenaScroll *= .9f;
            if (o->oTimer == 20) {
                SET_BPARAM1(o->oBehParams, 7);
                spawn_default_star(0, 700, 0);
                obj_mark_for_deletion(o);
            }
        break;
    }
}

void marx_generic_teleport(void) {
    o->oMarxTeleportTimer++;
    if (o->oMarxTeleportTimer < 8) {
    obj_scale_xyz(o, (f32)(8 - (o->oMarxTeleportTimer)) / 8.0f, 
        (f32)((o->oMarxTeleportTimer) + 8) / 8.0f, 
        (f32)(8 - (o->oMarxTeleportTimer)) / 8.0f);
    }

    if (o->oMarxTeleportTimer == 8) {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_NONE];
        o->oPosX = o->oMarxTeleportX;
        o->oPosY = o->oMarxTeleportY;
        o->oPosZ = o->oMarxTeleportZ;
    }

    if (o->oMarxTeleportTimer > 10) {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_MARX];
    obj_scale_xyz(o, (f32)((o->oMarxTeleportTimer - 10)) / 8.0f, 
        (f32)(16 - (o->oMarxTeleportTimer - 10)) / 8.0f, 
        (f32)((o->oMarxTeleportTimer - 10)) / 8.0f);
    }

    if (o->oMarxTeleportTimer == 18) {
       o->oMarxTeleportTimer = -1;
       cur_obj_scale(1.0f);
    }
}



s16 get_marx_damage_from_mario_attack(void) {
    switch (gMarioState->abilityId) {
        case ABILITY_CUTTER:;
            if (gMarioState->action == ACT_CUTTER_DASH) {
                return 8;
            }
            if (gMarioState->action == ACT_DIVE) {
                return 5;
            }
            if (gMarioState->action == ACT_FINAL_CUTTER_SEQUENCE) {
                if (gMarioState->actionArg == 0 && gMarioState->actionTimer == 0) {
                    return 4;
                }
                if (gMarioState->actionArg == 1 && gMarioState->actionTimer == 1) {
                    return 4;
                }
                if (gMarioState->actionArg == 2 && gMarioState->actionTimer == 4) {
                    return 10;
                }
            }
        break;
        case ABILITY_BUBBLE_HAT:;
            if (gMarioState->action == ACT_BUBBLE_HAT_ATTACK) {
                return 5;
            }
            if (gMarioState->action == ACT_BUBBLE_HAT_JUMP) {
                return 4;
            }
        break;
        case ABILITY_KNIGHT:;
            if (gMarioState->action == ACT_KNIGHT_JUMP || gMarioState->action == ACT_KNIGHT_SLIDE) {
                return 8;
            }
        break;
        case ABILITY_CHRONOS:;
            if (gMarioState->action == ACT_MOVE_PUNCHING || gMarioState->action == ACT_PUNCHING) {
                return 6;
            }
        break;
        case ABILITY_ESTEEMED_MORTAL:;
            if (gMarioState->action == ACT_ABILITY_AXE_JUMP) {
                return 4;
            }
        break;
        case ABILITY_MARBLE:;
            return 2;
        break;
        default:
            if (gMarioState->action & ACT_FLAG_ATTACKING) {
                return 3;
            }
        break;
    }
    return 0;
}

s16 get_marx_damage_from_object(struct Object *obj) {
    if (obj_has_behavior(obj, bhvCutterBlade)) {
        return 4;
    }
    else if (obj_has_behavior(obj, bhvShockRocket)) {
        obj->oAction = 2;
        return 16;
    }
    return 0;
}

extern s16 gMarxHudHealth;

void bhv_g_marx_init(void) {
    gSecondCameraFocus = NULL;
    gCamera->cutscene = 0;
    
    o->oMarxTeleportTimer = -1;
    obj_set_hitbox(o, &sMarxHitbox);
    o->oMarxInvincibilityTimer = 0;
    o->oInteractStatus = 0;
    o->oMarxHealth = 80;
    gMarxHudHealth = 0;
}

void bhv_g_marx_loop(void) {
    switch (o->oAction) {
        case MARX_ACT_CUTSCENE:
            marx_act_cutscene();
        break;
        case MARX_ACT_IDLE_FLIGHT:
            marx_act_idle_flight();
        break;
        case MARX_ACT_FLY_ACROSS:
            marx_act_fly_across();
        break;
        case MARX_ACT_TELEPORT:
            marx_act_teleport();
        break;
        case MARX_ACT_CUTTER:
            marx_act_cutter();
        break;
        case MARX_ACT_THORNS:
            marx_act_thorns();
        break;
        case MARX_ACT_BLACK_HOLE:
            marx_act_black_hole();
        break;
        case MARX_ACT_ARROWS:
            marx_act_arrows();
        break;
        case MARX_ACT_LASER:
            marx_act_laser();
        break;
        case MARX_ACT_ICE_BOMB:
            marx_act_ice_bomb();
        break;
        case MARX_ACT_DEAD:
            marx_act_dead();
        break;
    }

    //print_text_fmt_int(100, 100, "%d", o->oMarxHealth);

    if (o->oMarxTeleportTimer > -1) {
        marx_generic_teleport();
    }

    if (gMarxHudHealth < o->oMarxHealth) {
        if (o->oAction != MARX_ACT_CUTSCENE) {
            gMarxHudHealth += 2;
            cur_obj_play_sound_2(SOUND_MITM_G_MARX_HP);
        }
    }
    else {
        gMarxHudHealth = o->oMarxHealth;
    }

    if (o->oMarxInvincibilityTimer == 0) {
        o->oInteractStatus = 0;
    }
    else {
        o->oMarxInvincibilityTimer--;
    }

    if (o->oInteractStatus == 0) {
        if (o->oShotByShotgun > 0) {
            o->oMarxHealth -= 2;
            if (o->oShotByShotgun == 2) {
                o->oMarxHealth -= 1;
            }
            o->oShotByShotgun = 0;
            o->oMarxInvincibilityTimer = 20;
        }

        for (int i = 0; i < o->numCollidedObjs; i++) {
            struct Object *other = o->collidedObjs[i];
            if (other->parentObj && other->parentObj != o) {
                if (other == gMarioObject) {
                    s16 damageValue = get_marx_damage_from_mario_attack();
                    if (damageValue > 0) {
                        o->oMarxInvincibilityTimer = 20;
                        o->oMarxHealth -= damageValue;
                        o->oInteractStatus = INT_STATUS_WAS_ATTACKED;
                    }
                    push_mario_out_of_object(gMarioState, o, 5.0f);
                }
                else {
                    s16 damageValue = get_marx_damage_from_object(other);
                    if (damageValue > 0) {
                        o->oMarxInvincibilityTimer = 20;
                        o->oMarxHealth -= damageValue;
                        o->oInteractStatus = INT_STATUS_WAS_ATTACKED;
                    }
                }
            }
        }
    }

    Vec3f marxVisualPos;
    vec3f_copy(marxVisualPos, &o->oPosVec);

    if (o->oMarxInvincibilityTimer > 10) {
        marxVisualPos[0] += (random_u16() % 20) - 10;
        marxVisualPos[1] += (random_u16() % 20) - 10;
        marxVisualPos[2] += (random_u16() % 20) - 10;
    }

    vec3_copy_y_off(o->header.gfx.pos, marxVisualPos, o->oGraphYOffset);
    o->header.gfx.angle[0] = (o->oFaceAnglePitch & 0xFFFF);
    o->header.gfx.angle[1] = (o->oFaceAngleYaw   & 0xFFFF);
    o->header.gfx.angle[2] = (o->oFaceAngleRoll  & 0xFFFF);

    if (o->oMarxHealth <= 0) {
        o->oAction = MARX_ACT_DEAD;
        gMarxHudHealth = 0;
    }

    //this is so the shotgun doesnt annihilate marx lol
    o->oHealth = 20;

    //this is so that the shotgun doesn't push him very much
    struct Object * pushobj = cur_obj_nearest_object_with_behavior(bhvE_PushObj);
    if (pushobj) {
        pushobj->oVelX *= 0.85f;
        pushobj->oVelZ *= 0.85f;
    }
}

void bhv_g_marx_cutter_init(void) {
    o->oMoveAngleYaw = o->parentObj->oFaceAngleYaw + (o->oBehParams2ndByte % 2 == 0 ? 0x2000 : -0x2000);
    o->oVelY = (o->oBehParams2ndByte / 2 == 0 ? 15 : -15);
    o->oForwardVel = 60;
    obj_set_hitbox(o, &sMarxCutterHitbox);
}

void bhv_g_marx_cutter_loop(void) {
    cur_obj_move_xz_using_fvel_and_yaw();
    o->oPosY += o->oVelY;
    o->oFaceAngleYaw += 0x2000;
    o->oForwardVel -= 2;
    o->oInteractStatus = 0;
    o->oVelY += (o->oBehParams2ndByte / 2 == 0 ? -0.5f : 0.5f);
    if (o->oTimer == 60) {
        obj_mark_for_deletion(o);
    }
}

void bhv_g_marx_seed_init(void) {
    o->oVelY = -60.0f;
}

void bhv_g_marx_seed_loop(void) {
    f32 floorHeight = find_floor_height(o->oPosX, o->oPosY + 100, o->oPosZ);

    if (o->oPosY < floorHeight) {
        o->oPosY = floorHeight;
        spawn_object_relative(0, 0, 0, 0, o, MODEL_NONE, bhvGMarxVine);
        spawn_object_relative(0, 0, 0, 0, o, MODEL_NONE, bhvSparkleSpawn);
        obj_mark_for_deletion(o);
    }
    o->oPosY += o->oVelY;
}

void bhv_g_marx_vine_init(void) {
}

void bhv_g_marx_vine_loop(void) {
    switch (o->oAction) {
        case 0:
            if (o->oTimer == 100) {
                o->oAction++;
                o->oTimer = 0;
            }
        break;
        case 1:
            if (o->oTimer % 2 == 0) {
                spawn_object_relative(0, (random_u16() % 60 - 30), o->oF4, (random_u16() % 60 - 30), o, MODEL_G_MARX_THORNS, bhvGMarxThornSegment);
                o->oF4 += 160;
            }

            if (o->oTimer == 30) {
                obj_mark_for_deletion(o);
            }
        break;
    }
}

void bhv_g_marx_thorn_segment_init(void) {
    obj_set_hitbox(o, &sMarxThornsHitbox);
    cur_obj_play_sound_1(SOUND_ACTION_CLIMB_UP_TREE);
}

void bhv_g_marx_thorn_segment_loop(void) {
    if (o->oTimer == 20) {
        if (random_u16() % 40 == 2) {
            spawn_object_relative(0, 0, 0, 0, o, MODEL_YELLOW_COIN, bhvSingleCoinGetsSpawned);
        }
        obj_mark_for_deletion(o);
    }
    o->oInteractStatus = 0;
}

void bhv_g_marx_half_init(void) {

}

void bhv_g_marx_half_loop(void) {
    if (o->oTimer < 10 && o->oBehParams2ndByte == 1) {
        o->oPosY -= 4;
    }

    if (o->oTimer > 12 && o->oTimer <= 25) {
        o->oPosX += (o->oBehParams2ndByte == 0 ? 20 : -20)*coss(o->oFaceAngleYaw);
        o->oPosZ += (o->oBehParams2ndByte == 0 ? -20 : 20)*sins(o->oFaceAngleYaw);
    }

    if (o->oTimer >= 35) {
        obj_scale_xyz(o, (f32)(45 - (o->oTimer)) / 10.0f, (f32)((o->oTimer) - 25) / 10.0f, (f32)(45 - (o->oTimer)) / 10.0f);
    }

    if (o->oTimer == 44) {
        obj_mark_for_deletion(o);
    }
}

void bhv_g_marx_black_hole_init(void) {
    spawn_object_relative(0, 0, 0, 0, o, MODEL_G_MARX_BLACK_HOLE_EFFECT, bhvGMarxBlackHoleEffect);
}

void bhv_g_marx_black_hole_loop(void) {
    switch (o->oSubAction) {
        case 0:
            cur_obj_scale((f32)(o->oTimer + 1) / 16);
            if (o->oTimer == 16) {
                o->oSubAction++;
                o->oTimer = 0;
            }
        break;
        case 1:
            gMarioState->pos[0] = (o->oPosX - gMarioState->pos[0] > 0 ? CLAMP(gMarioState->pos[0] + (12000.0f / o->oDistanceToMario), -32000, o->oPosX) : CLAMP(gMarioState->pos[0] + -(12000.0f / o->oDistanceToMario), o->oPosX, 32000));
            gMarioState->pos[2] = (o->oPosZ - gMarioState->pos[2] > 0 ? CLAMP(gMarioState->pos[2] + (12000.0f / o->oDistanceToMario), -32000, o->oPosZ) : CLAMP(gMarioState->pos[2] + -(12000.0f / o->oDistanceToMario), o->oPosZ, 32000));

            if (o->oDistanceToMario < 500.0f) {
                o->oSubAction++;
                gMarioState->action = ACT_HARD_BACKWARD_AIR_KB;
                gMarioState->faceAngle[1] = 0x8000 + obj_angle_to_object(gMarioObject, o);
                play_sound(SOUND_MARIO_WAAAOOOW, gMarioObject->header.gfx.cameraToObject);
                o->oTimer = 0;
                gCamera->cutscene = 1;
            }


            if (o->oTimer == 90) {
                obj_mark_for_deletion(o);
            }
        break;
        case 2:
            gMarioState->action = ACT_HARD_BACKWARD_AIR_KB;
            gMarioState->pos[0] = approach_s16_symmetric(gMarioState->pos[0], o->oPosX, 10);
            gMarioState->pos[1] = approach_s16_symmetric(gMarioState->pos[1], o->oPosY, 10);
            gMarioState->pos[2] = approach_s16_symmetric(gMarioState->pos[2], o->oPosZ, 10);
            gMarioState->vel[1] = 0;

            gLakituState.goalPos[0] = approach_s16_symmetric(gLakituState.goalPos[0], o->oPosX, 20);
            gLakituState.goalPos[1] = approach_s16_symmetric(gLakituState.goalPos[1], o->oPosY, 20);
            gLakituState.goalPos[2] = approach_s16_symmetric(gLakituState.goalPos[2], o->oPosZ, 20);

            if (o->oTimer == 5) {
                play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 20, 0x00, 0x00, 0x00);
            }

            if (o->oTimer == 30) {
                gMarioState->pos[0] = 0;
                gMarioState->pos[1] = -1200;
                gMarioState->pos[2] = 0;
                gLakituState.goalPos[0] = 500;
                gLakituState.goalPos[1] = -1190;
                gLakituState.goalPos[2] = 500;
                gLakituState.goalFocus[0] = 0;
                gLakituState.goalFocus[1] = -1240;
                gLakituState.goalFocus[2] = 0;
                o->oSubAction++;
                gMarioState->action = ACT_CUTSCENE_CONTROLLED;
                play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 2, 0x00, 0x00, 0x00);
                o->oTimer = 0;
            }


        break;
        case 3:

            gMarioState->health -= 0x10;

            if (o->oTimer % 3 == 0) {
                spawn_object_abs_with_rot(o, 0, MODEL_EXPLOSION, bhvExplosion, (random_u16() % 600 - 300), -1200 + (random_u16() % 600 - 300), (random_u16() % 600 - 300), 0, 0, 0);
            }

            switch (o->oTimer % 30) {
                case 0: set_mario_animation(gMarioState, MARIO_ANIM_FORWARD_KB);
                break;
                case 8: set_mario_animation(gMarioState, MARIO_ANIM_BACKWARD_AIR_KB);
                break;
                case 16: set_mario_animation(gMarioState, MARIO_ANIM_SHOCKED);
                break;
                case 24: set_mario_animation(gMarioState, MARIO_ANIM_FALL_OVER_BACKWARDS);
                break;
            }

            if (o->oTimer > 50) {
                cur_obj_scale((f32)(61.0f - o->oTimer) / 11.0f);
            }

            if (o->oTimer == 60) {
                gMarioState->pos[0] = 0;
                gMarioState->pos[1] = 500;
                gMarioState->pos[2] = 0;
                gMarioState->action = ACT_HARD_BACKWARD_AIR_KB;
                gLakituState.goalPos[0] = 500;
                gLakituState.goalPos[1] = 590;
                gLakituState.goalPos[2] = 500;
                gLakituState.goalFocus[0] = 0;
                gLakituState.goalFocus[1] = 740;
                gLakituState.goalFocus[2] = 0;
                
                
                if (gCamera->mode != CAMERA_MODE_SHOCK_ROCKET && !(gE_ShotgunFlags & E_SGF_AIM_MODE)) set_camera_mode(gMarioState->area->camera, CAMERA_MODE_8_DIRECTIONS, 1);
                gCamera->cutscene = 0;
                obj_mark_for_deletion(o);
            }
        break;
    }
}

void bhv_g_marx_arrow_init(void) {
    o->oForwardVel = 120.0f;
    obj_set_hitbox(o, &sMarxArrowHitbox);
}

void bhv_g_marx_arrow_loop(void) {
    if (o->oTimer == 30) {
        obj_mark_for_deletion(o);
    }
}

void bhv_g_marx_body_laser_init(void) {
   
}

void bhv_g_marx_body_laser_loop(void) {
    o->oPosX = o->parentObj->oPosX;
    o->oPosY = o->parentObj->oPosY;
    o->oPosZ = o->parentObj->oPosZ;
}

s8 point_inside_xz_tri(Vec3f marioPos, Vec3f a, Vec3f b, Vec3f c) {
    int aMarioX = marioPos[0] - a[0];
    int aMarioZ = marioPos[2] - a[2];

    s8 mario_a_b = (b[0] - a[0]) * aMarioZ - (b[2] - a[2]) * aMarioX > 0;

    if ((c[0] - a[0]) * aMarioZ - (c[2] - a[2]) * aMarioX > 0 == mario_a_b)
        return FALSE;

    if ((c[0] - b[0]) * (marioPos[2] - b[2]) - (c[2] - b[2]) * (marioPos[0] - b[0]) > 0 != mario_a_b)
        return FALSE;

    return TRUE;
}

void bhv_g_marx_laser_init(void) {
   
}

void bhv_g_marx_laser_loop(void) {
    o->oPosX = o->parentObj->oPosX;
    o->oPosY = o->parentObj->oPosY;
    o->oPosZ = o->parentObj->oPosZ;

    if (o->oTimer < 10) {
        obj_scale_xyz(o, 1.5f, 1.5f, 4.0f);
    }
    else {
        obj_scale_xyz(o, 1.5f - (((f32)o->oTimer - 10.0f) / 40.0f), 1.5f - (((f32)o->oTimer - 10.0f) / 45.0f), 4.0f);
    }

    if (o->oTimer == 69) {
        obj_mark_for_deletion(o);
    }

    Vec3f pointA;
    Vec3f pointB;
    Vec3f pointC;
    Vec3f pointD;

    s16 laserWidth = 120 - (o->oTimer >= 10 ? 2*(o->oTimer - 10) : 0);
    s16 laserLength = 10000 + 20*o->oTimer;

    vec3f_set(pointA, o->oPosX + laserWidth * coss(o->oFaceAngleYaw), o->oPosY, o->oPosZ + laserWidth * sins(o->oFaceAngleYaw + 0x50));
    vec3f_set(pointB, o->oPosX + laserWidth * -coss(o->oFaceAngleYaw), o->oPosY, o->oPosZ + laserWidth * -sins(o->oFaceAngleYaw + 0x50));

    //vec3f_set(pointA, o->oPosX + 300 * coss(o->oFaceAngleYaw + 0x50), o->oPosY, o->oPosZ + 300 * sins(o->oFaceAngleYaw + 0x50));
    //vec3f_set(pointB, o->oPosX + 300 * coss(o->oFaceAngleYaw - 0x50), o->oPosY, o->oPosZ + 300 * sins(o->oFaceAngleYaw - 0x50));
    vec3f_set(pointC, pointA[0] + laserLength * sins(o->oFaceAngleYaw), o->oPosY, pointA[2] + laserLength * coss(o->oFaceAngleYaw));
    vec3f_set(pointD, pointB[0] + laserLength * sins(o->oFaceAngleYaw), o->oPosY, pointB[2] + laserLength * coss(o->oFaceAngleYaw));


    if (point_inside_xz_tri(gMarioState->pos, pointA, pointB, pointC) || point_inside_xz_tri(gMarioState->pos, pointA, pointC, pointD)) {
        if (absf(o->oPosY - gMarioState->pos[1] + 60) < 400 && gMarioState->action != ACT_BACKWARD_AIR_KB) {
            gMarioState->action = ACT_BACKWARD_AIR_KB;
            o->oDamageOrCoinValue = 4;
            take_damage_and_knock_back(gMarioState, o);
            gMarioState->vel[1] = 5;
            gMarioState->forwardVel = 0.0f;
            gMarioState->faceAngle[1] = o->oFaceAngleYaw + 0x8000;
        }
    }

    if (gMarioState->action == ACT_BACKWARD_AIR_KB) {
        gMarioState->pos[1] = o->oPosY - 60;
    }
}

void bhv_g_marx_ice_bomb_init(void) {
    o->oVelY = -10;
}

void bhv_g_marx_ice_bomb_loop(void) {
    if (o->oAction == 0) {
    o->oVelY -= 1;
    o->oPosY += o->oVelY;

    if (o->oPosY <= gMarioState->pos[1]) {
        o->oAction++;
        cur_obj_set_model(MODEL_G_MARX_ICE_RING);
        obj_scale_xyz(o, 0.2f, 1.0f, 0.2f);
        o->header.gfx.node.flags &= ~(GRAPH_RENDER_BILLBOARD);
    }
    }
    else {
        o->oVelY = 0;
        obj_scale_xyz(o, 0.2f + ((f32)o->oTimer / 10), 1.0f, 0.2f + ((f32)o->oTimer / 10));

        // Scale shockwave as the timer goes on
    o->oBowserShockWaveScale = (f32)o->oTimer;

    if (absf(o->oPosY - gMarioState->pos[1] + 60) < 100) {
        // ..define distance values depending of the scale multiplied by hit points
        f32 distMin1 = o->oBowserShockWaveScale * 101.0f;
        f32 distMax1 = o->oBowserShockWaveScale * 141.0f;
        // If Mario is in between distMin and distMax values, shock him
        if ((distMin1 < o->oDistanceToMario && o->oDistanceToMario < distMax1)) {
            gMarioState->action = ACT_BACKWARD_GROUND_KB;
            o->oDamageOrCoinValue = 3;
            take_damage_and_knock_back(gMarioState, o);
        }
    }

        if (o->oTimer == 30) {
            obj_mark_for_deletion(o);
        }
    }
}

void bhv_g_marx_black_hole_effect_init(void) {
    cur_obj_scale(30.0f);
}

void bhv_g_marx_black_hole_effect_loop(void) {
    cur_obj_scale(30.0f / (1.0f + ((f32)o->oTimer / 12.0f)));
    if (o->oTimer == 90) {
        obj_mark_for_deletion(o);
    }
}

