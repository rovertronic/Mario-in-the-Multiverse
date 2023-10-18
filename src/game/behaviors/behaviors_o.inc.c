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

//star piece switch

u8 star_pieces_got = 0;
void bhv_star_piece_switch_loop(void) {
    // The switch's model is 1/3 size.
    cur_obj_scale(3.0f);

    switch (o->oAction) {
        case BLUE_COIN_SWITCH_ACT_IDLE:
            // If Mario is on the switch and has ground-pounded,
            // recede and get ready to start ticking.
            if (((gMarioObject->platform == o) && (gMarioStates[0].action == ACT_GROUND_POUND_LAND))
                || (o->oShotByShotgun == 2)) {//--E
                //set star pieces got to 0
                star_pieces_got = 0;
                // Set to BLUE_COIN_SWITCH_ACT_RECEDING
                o->oAction = BLUE_COIN_SWITCH_ACT_RECEDING;
                // Recede at a rate of 16 units/frame.
                o->oVelY = -16.0f;

                // Set gravity to 0 so it doesn't accelerate when receding.
                o->oGravity = 0.0f;

                cur_obj_play_sound_2(SOUND_GENERAL_SWITCH_DOOR_OPEN);
            }
            o->oShotByShotgun = 0;//--E

            // Have collision
            load_object_collision_model();

            break;

        case BLUE_COIN_SWITCH_ACT_RECEDING:
            // Recede for 6 frames before going invisible and ticking.
            // This is probably an off-by-one error, since the switch is 100 units tall
            // and recedes at 20 units/frame, which means it will fully recede after 5 frames.

            if (o->oTimer > 3) {

                // Set to BLUE_COIN_SWITCH_ACT_TICKING
                o->oAction = BLUE_COIN_SWITCH_ACT_TICKING;

                // ???
                o->oVelY    = 0.0f;
                o->oGravity = 0.0f;

                // Spawn particles. There's a function that calls this same function
                // with the same arguments, spawn_mist_particles, why didn't they just call that?
                spawn_mist_particles_variable(0, 0, 46.0f);
            } else {
                // Have collision while receding
                load_object_collision_model();
                // Recede
                cur_obj_move_using_fvel_and_gravity();
            }

            break;

        case BLUE_COIN_SWITCH_ACT_TICKING:
            // Tick faster when the blue coins start blinking
            if (o->oTimer < (o->oBehParams2ndByte == 0 ? 200 : (o->oBehParams2ndByte * 10) - 40)) {
                play_sound(SOUND_GENERAL2_SWITCH_TICK_FAST, gGlobalSoundSource);
            } else {
                play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
            }

            if (star_pieces_got > 4) {//if (cur_obj_nearest_object_with_behavior(bhvHiddenBlueCoin) == NULL) {
                spawn_default_star(o->oPosX,o->oPosY+400.0f,o->oPosZ);
                spawn_mist_particles_variable(0, 0, 46.0f);
                obj_mark_for_deletion(o);
            // Set to BLUE_COIN_SWITCH_ACT_EXTENDING after the coins unload after the 240-frame timer expires.
            } else if (o->oTimer > (o->oBehParams2ndByte == 0 ? 240 : o->oBehParams2ndByte * 10)) {
                o->oAction  = BLUE_COIN_SWITCH_ACT_EXTENDING;
                o->oVelY    = 16.0f;
                o->oGravity =  0.0f;
            }
            load_object_collision_model();
            break;
        case BLUE_COIN_SWITCH_ACT_EXTENDING:
            if (o->oTimer > 3) {
                // Set to BLUE_COIN_SWITCH_ACT_IDLE
                o->oAction = BLUE_COIN_SWITCH_ACT_IDLE;
                o->oPosY = o->oHomeY; //thy be no evil shenanigans
            } else {
                // Have collision while extending
                load_object_collision_model();
                // Extend
                cur_obj_move_using_fvel_and_gravity();
            }
            break;
    }
}

//star piece.
void bhv_star_piece_loop(void) {
    struct Object *sps;

    o->oFaceAngleYaw += 0x400;
    o->oPosY = o->oHomeY + 20.0f + (sins(o->oTimer*0x500)*20.0f);

    sps = cur_obj_nearest_object_with_behavior(bhvStarPieceSwitch);

    switch(o->oAction) {
        case 0: // init
            cur_obj_hide();
            o->oAction = 1;
        break;
        case 1: //waiting
            if (sps && sps->oAction == BLUE_COIN_SWITCH_ACT_TICKING) {
                o->oAction = 2;
                cur_obj_unhide();
            }
        break;
        case 2: //active
            if (o->oDistanceToMario < 160.0f) {
                cur_obj_hide();
                cur_obj_play_sound_2(SOUND_MENU_COLLECT_SECRET+star_pieces_got);
                star_pieces_got++;
                o->oAction = 3;
            }

        case 3: //collected
            if (sps && (sps->oAction == BLUE_COIN_SWITCH_ACT_EXTENDING || sps->oAction == BLUE_COIN_SWITCH_ACT_IDLE)) {
                cur_obj_hide();
                o->oAction = 1;
            }
        break;
    }
}