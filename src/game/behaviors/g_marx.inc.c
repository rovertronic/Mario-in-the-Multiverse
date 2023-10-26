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
};

void marx_act_cutscene(void) {
    o->oAction = 1;
}

void marx_act_idle_flight(void) {
    if (o->oTimer == 0) {
        cur_obj_init_animation(0);
    }
    obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x400);
    if (o->oTimer == 60) {
        switch (random_u16() % 5) {
            case 0: o->oAction = MARX_ACT_CUTTER;
            break;
            case 1: o->oAction = MARX_ACT_THORNS;
            break;
            case 2: o->oAction = MARX_ACT_BLACK_HOLE;
            break;
            case 3: o->oAction = MARX_ACT_ICE_BOMB;
            break;
            case 4: o->oAction = MARX_ACT_FLY_ACROSS;
            break;
        }
        
    }
}


void marx_act_fly_across(void) {
    switch (o->oSubAction) {
        case 0:
            if (o->oTimer == 30) {
                o->oSubAction++;
            }
        break;
        case 1:
            if (cur_obj_check_if_at_animation_end()) {
                cur_obj_init_animation(1);
                o->oTimer = 0;
                o->oSubAction++;
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
            }
            if (cur_obj_check_if_at_animation_end()) {
                cur_obj_init_animation(0);
                o->oAction = MARX_ACT_IDLE_FLIGHT;
            }
        break;
    }
}

void marx_act_thorns(void) {
    switch (o->oSubAction) {
        case 0:
            o->oSubAction++;
            cur_obj_init_animation(3);
            set_camera_mode(gMarioState->area->camera, CAMERA_MODE_8_DIRECTIONS, 1);
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
                spawn_object_abs_with_rot(o, 0, MODEL_G_MARX_SEED, bhvGMarxSeed, gMarioState->pos[0], gMarioState->pos[1] + 1000, gMarioState->pos[2], 0, 0, 0);
            }

            if (o->oTimer == 91) {
                o->oSubAction++;
                o->oTimer = 0;
            }
        break;
        case 3:
        if (o->oTimer == 90) {
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
            if (cur_obj_check_if_at_animation_end()) {
                o->oSubAction++;
                gSecondCameraFocus = o;
            set_camera_mode(gMarioState->area->camera, CAMERA_MODE_BOSS_FIGHT, 1);
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_NONE];
                spawn_object_relative(0, 0, 0, 0, o, MODEL_G_MARX_HALF_LEFT, bhvGMarxHalf);
                spawn_object_relative(1, 0, 0, 0, o, MODEL_G_MARX_HALF_RIGHT, bhvGMarxHalf);
                o->oTimer = 0;
            }
            
        break;
        case 1:

            if (o->oTimer == 20) {
                spawn_object_relative(0, 0, 0, 0, o, MODEL_G_MARX_BLACK_HOLE, bhvGMarxBlackHole);
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
                    break;
                    case 1:
                        o->oAction = MARX_ACT_LASER;
                    break;
                    case 2:
                        o->oAction = MARX_ACT_ARROWS;
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
            if (o->oTimer == 30) {
                o->oMarxTeleportTimer = 7;
                o->oMarxTeleportX = 500;
                o->oMarxTeleportY = 700;
                o->oMarxTeleportZ = 0;
                o->oAction = MARX_ACT_IDLE_FLIGHT;
            }
        break;
    }
}

void marx_act_arrows(void) {
    switch (o->oSubAction) {
        case 0:;
            u16 randomAngle = random_u16();
            o->oPosX = 1200*sins(randomAngle);
            o->oPosZ = 1200*coss(randomAngle);
            o->oPosY = 0;
            o->oSubAction++;
        break;
        case 1:
            o->oPosY = approach_f32_asymptotic(o->oPosY, o->oHomeY, 0.08f);
            gSecondCameraFocus = o;
            set_camera_mode(gMarioState->area->camera, CAMERA_MODE_BOSS_FIGHT, 1);
            cur_obj_init_animation(4);
            if (o->oTimer == 30) {
                o->oSubAction++;
                o->oTimer = 0;
            }
        break;
        case 2:
            if (o->oTimer < 20) {
                obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x400);
            }
            if (o->oTimer == 30) {
                o->oSubAction++;
                o->oTimer = 0;
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
            set_camera_mode(gMarioState->area->camera, CAMERA_MODE_8_DIRECTIONS, 1);
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
            }
        break;
    }
}

void marx_act_laser(void) {
    switch (o->oSubAction) {
        case 0:;
            //set_camera_mode(gMarioState->area->camera, CAMERA_MODE_BOSS_FIGHT, 1);
            u16 randomAngle = random_u16();
            o->oMarxTeleportX = 1200*sins(randomAngle);
            o->oMarxTeleportZ = 1200*coss(randomAngle);
            o->oMarxTeleportY = gMarioState->pos[1] + 200;
            o->oMarxTeleportTimer = 7;
            o->oSubAction++;
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
                set_camera_mode(gMarioState->area->camera, CAMERA_MODE_8_DIRECTIONS, 1);
            }
        break;
        case 2:
        cur_obj_scale(1.5f);
        o->oPosX += (random_u16() % 6) - 3;
            o->oPosY += (random_u16() % 6) - 3;
            o->oPosZ += (random_u16() % 6) - 3;
            if (o->oTimer == 18) {

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
            }
        break;
    }
}

void marx_act_ice_bomb(void) {
    switch (o->oSubAction) {
        case 0:
            //o->oMarxLaserBody = spawn_object(o, MODEL_G_MARX_MOUTH_FULL, bhvGMarxBodyLaser);
            //o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_NONE];
            
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

void bhv_g_marx_init(void) {
    o->oMarxTeleportTimer = -1;
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
    }

    if (o->oMarxTeleportTimer > -1) {
        marx_generic_teleport();
    }
}

void bhv_g_marx_cutter_init(void) {
    o->oMoveAngleYaw = o->parentObj->oFaceAngleYaw + (o->oBehParams2ndByte % 2 == 0 ? 0x2000 : -0x2000);
    o->oVelY = (o->oBehParams2ndByte / 2 == 0 ? 15 : -15);
    o->oForwardVel = 60;
}

void bhv_g_marx_cutter_loop(void) {
    cur_obj_move_xz_using_fvel_and_yaw();
    o->oPosY += o->oVelY;
    o->oFaceAngleYaw += 0x2000;
    o->oForwardVel -= 2;
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

}

void bhv_g_marx_thorn_segment_loop(void) {
    if (o->oTimer == 20) {
        obj_mark_for_deletion(o);
    }
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
                set_camera_mode(gMarioState->area->camera, CAMERA_MODE_8_DIRECTIONS, 1);
                gCamera->cutscene = 0;
                obj_mark_for_deletion(o);
            }
        break;
    }
}

void bhv_g_marx_arrow_init(void) {
    o->oForwardVel = 120.0f;
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

        if (o->oTimer == 30) {
            obj_mark_for_deletion(o);
        }
    }
}

