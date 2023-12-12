
static void spawn_multiple_enemies(const BehaviorScript *behavior, ModelID32 modelId, u8 amount){
    u8 i;
    for (i = 0; i < amount; i++) {
        struct Object *obj = spawn_object_relative(0, 0, 0, 0, o, modelId, behavior);
        SET_BPARAM1(obj->oBehParams, 3);
    }
}

void bhv_fight_waves_manager_loop(void) {
    switch(o->oAction){
        case 0: //wait for mario
            if(o->oDistanceToMario < 2000){
                spawn_multiple_enemies(bhvGoomba, MODEL_GOOMBA, 5);
                o->oAction++;
            }
            break;
        case 1: //wait for wave 1 to end
            if(count_objects_with_behavior(bhvGoomba) == 0){
                spawn_multiple_enemies(bhvBobomb, MODEL_BLACK_BOBOMB, 5);
                o->oAction++;
            }
            break;
        case 2: //wait for wave 2 to end
            if(count_objects_with_behavior(bhvBobomb) == 0){
                spawn_multiple_enemies(bhvChuckya, MODEL_CHUCKYA, 5);
                o->oAction++;
            }
            break;
        case 3: //wait for wave 3 to end
            if(count_objects_with_behavior(bhvChuckya) == 0){
                bhv_spawn_star_no_level_exit_at_object(0, gMarioObject);
                o->oAction++;
            }
            break;
        case 4: //end fight
            break;
    }
}

//--------------------CRANE--------------------//

#define OFFSET 210
void bhv_crane_arrow_controller_init(void) {
    o->oObjF4 = spawn_object_relative_with_scale(1, OFFSET, 0, 0, 2.0f, o, MODEL_PURPLE_SWITCH, bhvCraneArrow);
    o->oObjF8 = spawn_object_relative_with_scale(2, -OFFSET, 0, 0, 2.0f, o, MODEL_PURPLE_SWITCH, bhvCraneArrow);
    o->oObjFC = cur_obj_nearest_object_with_behavior(bhvCrane);
}

void bhv_crane_arrow_controller_loop(void) {
    
}

void bhv_crane_arrow_loop(void) {
    switch (o->oAction) {
        case PURPLE_SWITCH_ACT_IDLE:
            if ((
                gMarioObject->platform == o
                && !(gMarioStates[0].action & MARIO_NO_PURPLE_SWITCH)
                && lateral_dist_between_objects(o, gMarioObject) < 150.5f
            ) || (o->oShotByShotgun == 2)) {//--E
                o->oAction = PURPLE_SWITCH_ACT_PRESSED;
            }
            break;

        case PURPLE_SWITCH_ACT_PRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 2.0f, 0.2f);
            if (o->oTimer == 3) {
                cur_obj_play_sound_2(SOUND_GENERAL2_PURPLE_SWITCH);
                o->oAction = PURPLE_SWITCH_ACT_TICKING;
                cur_obj_shake_screen(SHAKE_POS_SMALL);
#if ENABLE_RUMBLE
                queue_rumble_data(5, 80);
#endif
            }
            break;

        case PURPLE_SWITCH_ACT_TICKING:
            if (gMarioObject->platform != o) {
                    o->oAction++;
            }
            break;

        case PURPLE_SWITCH_ACT_UNPRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 0.2f, 2.0f);
            if (o->oTimer == 3) {
                o->oAction = PURPLE_SWITCH_ACT_IDLE;
            }
            break;
    }
    o->oShotByShotgun = 0;//--E
}