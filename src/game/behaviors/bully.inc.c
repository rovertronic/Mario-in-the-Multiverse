// bully.inc.c

static struct ObjectHitbox sSmallBullyHitbox = {
    /* interactType:      */ INTERACT_BULLY,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 73,
    /* height:            */ 123,
    /* hurtboxRadius:     */ 63,
    /* hurtboxHeight:     */ 113,
};

static struct ObjectHitbox sBigBullyHitbox = {
    /* interactType:      */ INTERACT_BULLY,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 115,
    /* height:            */ 235,
    /* hurtboxRadius:     */ 105,
    /* hurtboxHeight:     */ 225,
};

void bhv_small_bully_init(void) {
    cur_obj_init_animation(0);
    vec3f_copy(&o->oHomeVec, &o->oPosVec);
    o->oBehParams2ndByte = BULLY_BP_SIZE_SMALL;
    o->oGravity = 4.0f;
    o->oFriction = 0.91f;
    o->oBuoyancy = 1.3f;

    obj_set_hitbox(o, &sSmallBullyHitbox);
}

void bhv_big_bully_init(void) {
    cur_obj_init_animation(0);
    vec3f_copy(&o->oHomeVec, &o->oPosVec);
    o->oBehParams2ndByte = BULLY_BP_SIZE_BIG;
    o->oGravity = 5.0f;
    o->oFriction = 0.93f;
    o->oBuoyancy = 1.3f;

    obj_set_hitbox(o, &sBigBullyHitbox);

    obj_scale(o,2.5f);
    if (in_vanilla_painting_world()) {
        obj_scale(o,1.0f);
    }
}

void bully_check_mario_collision(void) {
    if (o->oAction != OBJ_ACT_LAVA_DEATH && o->oAction != OBJ_ACT_DEATH_PLANE_DEATH && ((o->oInteractStatus & INT_STATUS_INTERACTED) || o->oShotByShotgun)) {//--E
        o->oShotByShotgun = 0;
        if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) {
            cur_obj_play_sound_2(SOUND_OBJ2_SMALL_BULLY_ATTACKED);
        } else {
            cur_obj_play_sound_2(SOUND_OBJ2_LARGE_BULLY_ATTACKED);
        }

        o->oInteractStatus &= ~INT_STATUS_INTERACTED;
        o->oAction = BULLY_ACT_KNOCKBACK;
        o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
        cur_obj_init_animation(3);
        o->oBullyMarioCollisionAngle = o->oMoveAngleYaw;
    }
}

void bully_act_chase_mario(void) {
    f32 homeX = o->oHomeX;
    f32 posY = o->oPosY;
    f32 homeZ = o->oHomeZ;

    if (o->oTimer < 10) {
        o->oForwardVel = 3.0f;
        obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x1000);
    } else if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) {
        o->oForwardVel = 20.0f;
        if (o->oTimer > 30) {
            o->oTimer = 0;
        }
    } else {
        o->oForwardVel = 30.0f;
        if (o->oTimer > 35) {
            o->oTimer = 0;
        }
    }

    if (cur_obj_has_behavior(bhvNball)) {
        return;
    }

    if (!is_point_within_radius_of_mario(homeX, posY, homeZ, 1000)) {
        o->oAction = BULLY_ACT_PATROL;
        cur_obj_init_animation(0);
    }
}

void bully_act_knockback(void) {
    if (o->oForwardVel < 10.0f && (s32) o->oVelY == 0) {
        o->oForwardVel = 1.0f;
        o->oBullyKBTimerAndMinionKOCounter++;
        o->oFlags |= OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
        o->oMoveAngleYaw = o->oFaceAngleYaw;
        obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 1280);
    } else {
        o->header.gfx.animInfo.animFrame = 0;
    }

    if (o->oBullyKBTimerAndMinionKOCounter == 18) {
        o->oAction = BULLY_ACT_CHASE_MARIO;
        o->oBullyKBTimerAndMinionKOCounter = 0;
        cur_obj_init_animation(1);
    }
}

void bully_act_back_up(void) {
    if (o->oTimer == 0) {
        o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
        o->oMoveAngleYaw += 0x8000;
    }

    o->oForwardVel = 5.0f;

    //! bully_backup_check() happens after this function, and has the potential to reset
    //  the bully's action to BULLY_ACT_BACK_UP. Because the back up action is only
    //  set to end when the timer EQUALS 15, if this happens on that frame, the bully
    //  will be stuck in BULLY_ACT_BACK_UP forever until Mario hits it or its death
    //  conditions are activated. However because its angle is set to its facing angle,
    //  it will walk forward instead of backing up.

    if (o->oTimer == 15) {
        o->oMoveAngleYaw = o->oFaceAngleYaw;
        o->oFlags |= OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
        o->oAction = BULLY_ACT_PATROL;
    }
}

void bully_backup_check(s16 collisionFlags) {
    if (!(collisionFlags & OBJ_COL_FLAG_NO_Y_VEL) && o->oAction != BULLY_ACT_KNOCKBACK) {
        o->oPosX = o->oBullyPrevX;
        o->oPosZ = o->oBullyPrevZ;
        o->oAction = BULLY_ACT_BACK_UP;
    }
}

void bully_play_stomping_sound(void) {
    s16 animFrame = o->header.gfx.animInfo.animFrame;

    switch (o->oAction) {
        case BULLY_ACT_PATROL:
            if (animFrame == 0 || animFrame == 12) {
                if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) {
                    cur_obj_play_sound_2(SOUND_OBJ_BULLY_WALK_SMALL);
                } else {
                    cur_obj_play_sound_2(SOUND_OBJ_BULLY_WALK_LARGE);
                }
            }
            break;

        case BULLY_ACT_CHASE_MARIO:
        case BULLY_ACT_BACK_UP:
            if (animFrame == 0 || animFrame == 5) {
                if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) {
                    cur_obj_play_sound_2(SOUND_OBJ_BULLY_WALK_SMALL);
                } else {
                    cur_obj_play_sound_2(SOUND_OBJ_BULLY_WALK_LARGE);
                }
            }
            break;
    }
}

void bully_step(void) {
    s16 collisionFlags;
    u8 is_a_8_ball = cur_obj_has_behavior(bhvNball);

    if (!is_a_8_ball) {
        collisionFlags = object_step();
    } else {
        collisionFlags = object_step_without_floor_orient();
    }

    if (!is_a_8_ball) {
        bully_backup_check(collisionFlags);
        bully_play_stomping_sound();
    }
    obj_check_floor_death(collisionFlags, sObjFloor);

    if ((o->oBullySubtype & BULLY_STYPE_CHILL)||(is_a_8_ball)) {
        if (o->oPosY < -3030.0f) {
            o->oAction = OBJ_ACT_LAVA_DEATH;
        }
    }
}

void bully_spawn_coin(void) {
    struct Object *coin = spawn_object(o, MODEL_YELLOW_COIN, bhvMovingYellowCoin);

    cur_obj_play_sound_2(SOUND_GENERAL_COIN_SPURT);

    coin->oForwardVel = 10.0f;
    coin->oVelY = 100.0f;
    coin->oPosY = o->oPosY + 310.0f;
    coin->oMoveAngleYaw = (f32)(o->oBullyMarioCollisionAngle + 0x8000) + random_float() * 1024.0f;
}

void bully_act_level_death(void) {
    if (obj_lava_death() == TRUE) {
        if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) {
            if (o->oBullySubtype == BULLY_STYPE_MINION) {
                o->parentObj->oBullyKBTimerAndMinionKOCounter++;
            }
            bully_spawn_coin();
        } else {
            spawn_mist_particles();

            if (o->oBullySubtype == BULLY_STYPE_CHILL) {
                spawn_default_star(130.0f, 1600.0f, -4335.0f);
            } else {
                spawn_default_star(0, 950.0f, -6800.0f);
                spawn_object_abs_with_rot(o, 0, MODEL_NONE, bhvLllTumblingBridge,
                                          0, 154, -5631, 0, 0, 0);
            }
        }
    }
}

void bhv_bully_loop(void) {
    vec3f_copy(&o->oBullyPrevVec, &o->oPosVec);

    //! Because this function runs no matter what, Mario is able to interrupt the bully's
    //  death action by colliding with it. Since the bully hitbox is tall enough to collide
    //  with Mario even when it is under a lava floor, this can get the bully stuck OOB
    //  if there is nothing under the lava floor.
    bully_check_mario_collision();

    switch (o->oAction) {
        case BULLY_ACT_PATROL:
            o->oForwardVel = 5.0f;

            if (obj_return_home_if_safe(o, o->oHomeX, o->oPosY, o->oHomeZ, 800) == TRUE) {
                o->oAction = BULLY_ACT_CHASE_MARIO;
                cur_obj_init_animation(1);
            }

            bully_step();
            break;

        case BULLY_ACT_CHASE_MARIO:
            bully_act_chase_mario();
            bully_step();
            break;

        case BULLY_ACT_KNOCKBACK:
            bully_act_knockback();
            bully_step();
            break;

        case BULLY_ACT_BACK_UP:
            bully_act_back_up();
            bully_step();
            break;

        case OBJ_ACT_LAVA_DEATH:
            bully_act_level_death();
            break;

        case OBJ_ACT_DEATH_PLANE_DEATH:
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            break;
    }

    set_object_visibility(o, 3000);
}

void big_bully_spawn_minion(s32 x, s32 y, s32 z, s16 yaw) {
    struct Object *bully =
        spawn_object_abs_with_rot(o, 0, MODEL_BULLY, bhvSmallBully, x, y, z, 0, yaw, 0);
    bully->oBullySubtype = BULLY_STYPE_MINION;
    bully->oBehParams2ndByte = BULLY_BP_SIZE_SMALL;
}

void bhv_big_bully_with_minions_init(void) {
    big_bully_spawn_minion(o->oPosX+300.0f, o->oPosY, o->oPosZ-100.0f, 0);
    big_bully_spawn_minion(o->oPosX, o->oPosY, o->oPosZ+200.0f, 0);
    big_bully_spawn_minion(o->oPosX-300.0f, o->oPosY, o->oPosZ-100.0f, 0);

    o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;

    cur_obj_become_intangible();

    o->oAction = BULLY_ACT_INACTIVE;
}

void big_bully_spawn_star(void) {
    if (obj_lava_death() == TRUE) {
        spawn_mist_particles();
        //spawn_default_star(3700.0f, 600.0f, -5500.0f);
        spawn_default_star(o->oHomeX,o->oHomeY-1000.0f,o->oHomeZ);
    }
}

void bhv_big_bully_with_minions_loop(void) {
    s16 collisionFlags = 0;
    vec3f_copy(&o->oBullyPrevVec, &o->oPosVec);

    if (o->oShotByShotgun > 0) {
        // The big uka bully is too strong to be beat by the shotgun ツ
        cur_obj_play_sound_2(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL);
        o->oShotByShotgun = 0;
    }

    bully_check_mario_collision();

    switch (o->oAction) {
        case BULLY_ACT_PATROL:
            o->oForwardVel = 5.0f;

            if (obj_return_home_if_safe(o, o->oHomeX, o->oPosY, o->oHomeZ, 1000) == TRUE) {
                o->oAction = BULLY_ACT_CHASE_MARIO;
                cur_obj_init_animation(1);
            }

            bully_step();
            break;

        case BULLY_ACT_CHASE_MARIO:
            bully_act_chase_mario();
            bully_step();
            break;

        case BULLY_ACT_KNOCKBACK:
            bully_act_knockback();
            bully_step();
            break;

        case BULLY_ACT_BACK_UP:
            bully_act_back_up();
            bully_step();
            break;

        case BULLY_ACT_INACTIVE:
            //! The Big Bully that spawns from killing its 3 minions uses the knockback timer
            //  for counting the number of dead minions. This means that when it activates,
            //  the knockback timer is at 3 instead of 0. So the bully knockback time will
            //  be reduced by 3 frames (16.67%) on the first hit.
            if (o->oBullyKBTimerAndMinionKOCounter == 3) {
                play_puzzle_jingle();

                if (o->oTimer > 90) {
                    o->oAction = BULLY_ACT_ACTIVATE_AND_FALL;
                }
            }
            break;

        case BULLY_ACT_ACTIVATE_AND_FALL:
            collisionFlags = object_step();
            if ((collisionFlags & OBJ_COL_FLAGS_LANDED) == OBJ_COL_FLAGS_LANDED) {
                o->oAction = BULLY_ACT_PATROL;
            }

            if (collisionFlags == OBJ_COL_FLAG_GROUNDED) {
                cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
                set_camera_shake_from_point(SHAKE_POS_SMALL, o->oPosX, o->oPosY, o->oPosZ);
                spawn_mist_particles();
            }

            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            cur_obj_become_tangible();
            break;

        case OBJ_ACT_LAVA_DEATH:
            big_bully_spawn_star();
            break;

        case OBJ_ACT_DEATH_PLANE_DEATH:
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            break;
    }
}

static struct ObjectHitbox sNBallHitbox = {
    /* interactType:      */ INTERACT_BULLY,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 115,
    /* height:            */ 235,
    /* hurtboxRadius:     */ 105,
    /* hurtboxHeight:     */ 225,
};

void nball_spawn_star(void) {
    if (obj_lava_death() == TRUE) {
        spawn_mist_particles();
        spawn_default_star(gMarioState->pos[0],gMarioState->pos[1]+500.0f,gMarioState->pos[2]);
    }
}

void bhv_nball_init(void) {
    cur_obj_init_animation(0);
    vec3f_copy(&o->oHomeVec, gMarioState->pos);
    o->oBehParams2ndByte = BULLY_BP_SIZE_BIG;
    o->oGravity = 5.0f;
    o->oFriction = 0.93f;
    o->oBuoyancy = 1.3f;

    obj_set_hitbox(o, &sNBallHitbox);

    o->oAction = BULLY_ACT_PATROL;
}

void bhv_nball_loop(void) {
    u8 star_flags = save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_TTC));
    vec3f_copy(&o->oBullyPrevVec, &o->oPosVec);

    //! Because this function runs no matter what, Mario is able to interrupt the bully's
    //  death action by colliding with it. Since the bully hitbox is tall enough to collide
    //  with Mario even when it is under a lava floor, this can get the bully stuck OOB
    //  if there is nothing under the lava floor.
    bully_check_mario_collision();

    o->oFaceAnglePitch += (0x20*o->oForwardVel);
    o->oFaceAngleYaw = o->oMoveAngleYaw;

    vec3f_copy(&o->oHomeVec, gMarioState->pos);

    switch (o->oAction) {
        case BULLY_ACT_PATROL:
            //o->oForwardVel = 5.0f;

            //if (obj_return_home_if_safe(o, o->oHomeX, o->oPosY, o->oHomeZ, 800) == TRUE) {
                //o->oAction = BULLY_ACT_CHASE_MARIO;
                //cur_obj_init_animation(1);
            //}

            //bully_step();
            cur_obj_hide();
            if (star_flags == 0x7F) {
                o->oAction = BULLY_ACT_CHASE_MARIO;
                cur_obj_unhide();
            }

            break;

        case BULLY_ACT_CHASE_MARIO:
            vec3f_copy(&o->oHomeVec, gMarioState->pos);
            bully_act_chase_mario();

            if (gMarioState->pos[1] < o->oPosY-100.0f) {
                //don't chase mario off the edge
                o->oForwardVel = 0.0f;
            }

            bully_step();
            break;

        case BULLY_ACT_KNOCKBACK:
            bully_act_knockback();
            bully_step();
            break;

        case BULLY_ACT_BACK_UP:
            bully_act_back_up();
            bully_step();
            break;

        case OBJ_ACT_LAVA_DEATH:
            nball_spawn_star();
            break;

        case OBJ_ACT_DEATH_PLANE_DEATH:
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            break;
    }

    set_object_visibility(o, 3000);
}
