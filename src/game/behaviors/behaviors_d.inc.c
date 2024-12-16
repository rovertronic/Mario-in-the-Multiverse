void bhv_nitro_box_loop(void) {

    if (gPlayer1Controller->buttonPressed & L_TRIG) {
        o->oAction=1;
        o->oTimer = 0;
    }

    if (o->oAction == 1) {
        o->oAngleVelRoll -= 0x10;
        o->oFaceAnglePitch += o->oAngleVelRoll;

        if (o->oTimer > 60) {
            o->oAction ++;
        }
    }



    return;
    o->oPosY += o->oVelY;
    o->oVelY -= 2.0f;
    if (o->oPosY < o->oHomeY) {
        o->oPosY = o->oHomeY;
        o->oVelY = 0;
    }
    if (o->oTimer%20 == 0) {
        o->oVelY = 10.0f;
    }

    if (obj_check_if_collided_with_object(o, gMarioObject) == TRUE) {
        o->oInteractStatus &= ~INT_STATUS_INTERACTED;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;

        if (aku_invincibility == 0) {
            spawn_object(o, MODEL_NITRO_BOOM, bhvNitroBoom);
            set_mario_action(gMarioState,ACT_HARD_BACKWARD_GROUND_KB,0);
            gMarioState->faceAngle[1] = o->oAngleToMario+0x8000;
            gMarioState->health = 0xFF; //die
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        } else {
            spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
        }
    }

    set_object_visibility(o, 7000);

    if (o->oShotByShotgun > 0) {
        spawn_object(o, MODEL_NITRO_BOOM, bhvNitroBoom);
        set_mario_action(gMarioState,ACT_HARD_BACKWARD_GROUND_KB,0);
        gMarioState->faceAngle[1] = o->oAngleToMario+0x8000;
        gMarioState->health = 0xFF; //die
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void bhv_nitro_boom_loop(void) {
    cur_obj_scale(1.0f+(o->oTimer*2.0f));
    if (o->oTimer == 0) {
        o->oOpacity = 150;
    }
    if (o->oOpacity > 0) {
        o->oOpacity -= 2;
    } else {
        mark_obj_for_deletion(o);
    }
}

void bhv_d_elevator(void) {
    struct Surface * dummy_surf;

    switch(o->oAction) {
        case 0: //init
            o->oHomeX = find_floor(o->oPosX,o->oPosY,o->oPosZ,&dummy_surf); //actually ohomey2
            o->oHomeY = o->oPosY;
            o->oAction++;
        break;
        case 1: //wait for mario (top)
            if ((gMarioObject->platform == o)||((gMarioState->pos[1]<o->oPosY)&&(lateral_dist_between_objects(o,gMarioObject)<1500.0f)) ) {
                o->oAction ++;
            }
        break;
        case 2: // go down
            o->oPosY -= 25.0f;
            cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);

            if (o->oPosY < o->oHomeX) {
                o->oPosY = o->oHomeX;
                o->oAction++;
                cur_obj_play_sound_2(SOUND_GENERAL_QUIET_POUND1);
                cur_obj_shake_screen(SHAKE_POS_SMALL);
            }
        break;
        case 3: //wait for mario to get off (bottom)
            if (gMarioObject->platform != o) {
                o->oAction ++;
            }
        break;
        case 4: //wait for mario (bottom)
            if (gMarioObject->platform == o) {
                o->oAction ++;
            }
        break;
        case 5: // go up
            o->oPosY += 25.0f;
            cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);

            if (o->oPosY > o->oHomeY) {
                o->oPosY = o->oHomeY;
                o->oAction++;
                cur_obj_play_sound_2(SOUND_GENERAL_QUIET_POUND1);
                cur_obj_shake_screen(SHAKE_POS_SMALL);
            }
        break;
        case 6: //wait for mario to get off (top)
            if (gMarioObject->platform != o) {
                o->oAction = 1;
            }
        break;
    }
}