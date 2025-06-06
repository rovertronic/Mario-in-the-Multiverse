// hidden_star.inc.c

void bhv_hidden_star_init(void) {
    s16 remainingTriggers = count_objects_with_behavior(bhvHiddenStarTrigger);
    if (gCurrLevelNum == LEVEL_F) {
        remainingTriggers = count_objects_with_behavior(bhvBriefcase);
    }
    if (gCurrLevelNum == LEVEL_O) {
        remainingTriggers = count_objects_with_behavior(bhvOuvstar);
    }

    if (remainingTriggers == 0) {
        struct Object *starObj = spawn_object_abs_with_rot(o, 0, MODEL_STAR, bhvStar, o->oPosX, o->oPosY, o->oPosZ, 0, 0, 0);
        starObj->oBehParams = o->oBehParams;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }

    o->oHiddenStarTriggerCounter = 5 - remainingTriggers;
}

void bhv_hidden_star_loop(void) {
    switch (o->oAction) {
        case 0:
            if (o->oHiddenStarTriggerCounter == 5) {
                o->oAction = 1;
            }
            break;

        case 1:
            if (o->oTimer > 2) {
                spawn_red_coin_cutscene_star(o->oPosX, o->oPosY, o->oPosZ);
                spawn_mist_particles();
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
    }
}

void bhv_gco_star_init(void) {
    f32 dist;
    o->parentObj = cur_obj_find_nearest_object_with_behavior(bhvRocketButtonGroup, &dist);
}

void bhv_gco_star_loop(void) {
    switch (o->oAction) {
        case 0:
            if (o->parentObj->oAction == 1) {
                o->oAction = 1;
            }
            break;

        case 1:
            if (o->oTimer > 2) {
                spawn_red_coin_cutscene_star(o->oPosX, o->oPosY, o->oPosZ);
                spawn_mist_particles();
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
    }
}

void bhv_hidden_star_trigger_loop(void) {
    u8 spongebob_condition = FALSE;
    if (gCurrLevelNum == LEVEL_A) {
        // this hardcoding is pretty awful, but it's the easiest course of action
        struct Object * nearest_conc = cur_obj_nearest_object_with_behavior(bhvConcreteBlock);
        spongebob_condition = TRUE;
        if (nearest_conc && dist_between_objects(o,nearest_conc) < 100.0f) {
            spongebob_condition = FALSE;
        }
    }

    if (obj_check_if_collided_with_object(o, gMarioObject)||spongebob_condition) {
        struct Object *hiddenStar = cur_obj_nearest_object_with_behavior(bhvHiddenStar);

        if (hiddenStar != NULL) {
            hiddenStar->oHiddenStarTriggerCounter++;

            if (hiddenStar->oHiddenStarTriggerCounter != 5) {
                spawn_orange_number(hiddenStar->oHiddenStarTriggerCounter, 0, 0, 0);
            }

            play_sound(SOUND_MENU_COLLECT_SECRET + (((u8) hiddenStar->oHiddenStarTriggerCounter - 1) << 16), gGlobalSoundSource);
        }

        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void bhv_bowser_course_red_coin_star_init(void) {
    if (o->oBehParams2ndByte != 0) {
        o->oHiddenStarTriggerTotal = o->oBehParams2ndByte;
        o->oHiddenStarTriggerCounter = gRedCoinsCollected;
    }
    else {
        s16 numRedCoinsRemaining = count_objects_with_behavior(bhvRedCoin);
        o->oHiddenStarTriggerTotal = numRedCoinsRemaining + gRedCoinsCollected;
        o->oHiddenStarTriggerCounter = o->oHiddenStarTriggerTotal - numRedCoinsRemaining;
    }
}

void bhv_bowser_course_red_coin_star_loop(void) {
    gRedCoinsCollected = o->oHiddenStarTriggerCounter;

    switch (o->oAction) {
        case 0:
            if (o->oHiddenStarTriggerCounter == o->oHiddenStarTriggerTotal) {
                o->oAction = 1;
            }
            break;

        case 1:
            if (o->oTimer > 2) {
                spawn_no_exit_star(o->oPosX, o->oPosY, o->oPosZ);
                spawn_mist_particles();
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
    }
}
