void bhv_g_cannon_init(void) {
    o->oNumSwitchesLeft = 3;
    o->oFaceAnglePitch = 0x8000;
    o->oMoveAnglePitch = 0x8000;
}

void bhv_g_cannon_loop(void) {
    switch (o->oAction) {
        case 0:
            if (o->oNumSwitchesLeft <= 0) {
                o->oAction = 1;
                cur_obj_play_sound_2(SOUND_OBJ_CANNON_RISE);
            }
        break;
        case 1:
            o->oFaceAnglePitch = approach_s32_symmetric(o->oFaceAnglePitch, 0, 0x200);
            o->oMoveAnglePitch = approach_s32_symmetric(o->oMoveAnglePitch, 0, 0x200);

            if (o->oFaceAnglePitch == 0 || o->oTimer >= 120) {
                o->oAction = 2;
            }
        break;
        case 2:
            if (o->oDistanceToMario < 100 && gMarioState->pos[1] - o->oPosY < 50) {
                o->oAction = 3;
                gCamera->cutscene = 1;
                gMarioState->pos[0] = o->oPosX;
                gMarioState->pos[1] = o->oPosY;
                gMarioState->pos[2] = o->oPosZ;
                set_mario_action(gMarioState, ACT_CUTSCENE_CONTROLLED, 0);
                gMarioState->marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
                play_sound(SOUND_GENERAL_ELEVATOR_LAND, gMarioState->marioObj->header.gfx.cameraToObject);
                cur_obj_play_sound_2(SOUND_OBJ_CANNON_TURN);
            }
        break;
        case 3:
            o->oFaceAnglePitch += 0x800;
            o->oMoveAnglePitch += 0x800;
            if (o->oTimer == 35) {
                o->oAction = 4;
            }
        break;
        case 4:
            obj_scale_xyz(o, 1.0f + (0.5*sins(o->oTimer*0x444)), 
            1.0f - (0.5*sins(o->oTimer*0x444)), 1.0f + (0.5*sins(o->oTimer*0x444)));
            if (o->oTimer == 30) {
                o->oAction = 5;
                gMarioState->faceAngle[1] = o->oFaceAngleYaw;
                gMarioState->pos[1] += 110.0f;
                gMarioState->vel[1] = 80.0f;
                gMarioState->forwardVel = 70.0f;
                gCamera->cutscene = 0;
                gMarioState->marioObj->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;
                play_sound(SOUND_ACTION_FLYING_FAST, gMarioState->marioObj->header.gfx.cameraToObject);
                play_sound(SOUND_OBJ_POUNDING_CANNON, gMarioState->marioObj->header.gfx.cameraToObject);
                set_mario_action(gMarioState, ACT_SHOT_FROM_CANNON, 0);
            }
        break;
        case 5:
            o->oFaceAnglePitch = approach_s32_symmetric(o->oFaceAnglePitch, 0, 0x400);
            o->oMoveAnglePitch = approach_s32_symmetric(o->oMoveAnglePitch, 0, 0x400);
            cur_obj_scale(1.0f);

            if (o->oFaceAnglePitch == 0 || o->oTimer >= 120) {
                o->oAction = 1;
            }
        break;
    }
}

