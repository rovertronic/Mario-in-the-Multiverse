//checkpoint flag

void bhv_checkpoint_flag(void) {
    if (o->oBehParams2ndByte!=gMarioState->numCheckpointFlag) {
        o->oAnimState = 0;
        if (o->oDistanceToMario < 100.0f) {
            gMarioState->numCheckpointFlag = o->oBehParams2ndByte;
            o->oAnimState = 1;
            o->oVelY = 4000.0f;
            o->oTimer = 0;

            play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gMarioState->marioObj->header.gfx.cameraToObject);

            //move the death warp to me
            struct Object *dw = cur_obj_nearest_object_with_behavior(bhvDeathWarp);
            if (dw) {
                dw->oPosX = o->oPosX;
                dw->oPosY = o->oPosY+150.0f;
                dw->oPosZ = o->oPosZ;
            }
        }
    }

    if (o->oVelY > 2000.0f) {
        struct Object *sparkleObj = spawn_object(o, MODEL_SPARKLES, bhvCoinSparkles);
        sparkleObj->oPosX += random_float() * 50.0f - 25.0f;
        sparkleObj->oPosY += random_float() * 100.0f;
        sparkleObj->oPosZ += random_float() * 50.0f - 25.0f;
    }

    o->oFaceAngleRoll = sins(o->oTimer*0x900)*o->oVelY;
    o->oVelY *= 0.97f;
}

//flip switch

#define oSwitchState oHealth

u8 tiles_active = 0;
u8 tiles_needed = 0;
u8 tiles_hasmodel_count = 0;
u8 tiles_star_spawned = FALSE;
void bhv_flipswitch(void) {
    if ((tiles_active == tiles_needed) && (o->oAction > 1)) {
        if (o->oSwitchState == TRUE) {
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_FLIPSWITCH_3];
            o->oSwitchState = FALSE;
            tiles_hasmodel_count --;
        }
        if ((tiles_hasmodel_count == 0)&&(!tiles_star_spawned)) {
            tiles_star_spawned = TRUE;
            spawn_default_star(o->oPosX,o->oPosY+400.0f,o->oPosZ);
        }
        return;
    }

    switch(o->oAction) {
        case 0://init
            o->oAction = 1;
            o->oSwitchState = FALSE;
            tiles_needed = 0;
            tiles_active = 0;
            tiles_hasmodel_count = 0;
            tiles_star_spawned = FALSE;
            cur_obj_scale(1.0f + (o->oBehParams2ndByte*0.5f));
        break;
        case 1:
            tiles_needed ++;
            o->oAction = 2;
        break;
        case 2: //mario off
            if (gMarioObject->platform == o) {
                cur_obj_play_sound_2(SOUND_GENERAL_BOWSER_KEY_LAND);
                o->oAction = 3;
                o->oSwitchState = !o->oSwitchState;

                if (o->oSwitchState) {
                    tiles_active++;
                    if (tiles_active != tiles_needed) { //prevent being the 2nd model for 1 frame
                        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_FLIPSWITCH_2];
                    }
                } else {
                    tiles_active--;
                    o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_FLIPSWITCH_1];
                }
                tiles_hasmodel_count = tiles_active;
            }
        break;
        case 3: //mario on
            if (gMarioObject->platform != o) {
                o->oAction = 2;
            }
        break;
    }
}

//noteblock (from orchestral keys & btcm)
void bhv_noteblock(void) {
    o->oPosY = o->oHomeY + (sins(o->oTimer*5000) * o->oVelY);
    o->oVelY *= 0.95f;

    if (cur_obj_is_mario_on_platform()) {
        mario_stop_riding_and_holding(gMarioState);
        o->oTimer = 0;
        o->oVelY = 50.0f;
        cur_obj_play_sound_2(SOUND_GENERAL_CRAZY_BOX_BOING_SLOW);
        set_mario_action(gMarioState, ACT_DOUBLE_JUMP, 0);
        gMarioStates[0].vel[1] = 95.0f;
    }
}