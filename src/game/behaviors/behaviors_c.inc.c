
static void spawn_multiple_enemies(const BehaviorScript *behavior, ModelID32 modelId, u8 amount){
    u8 i;
    for (i = 0; i < amount; i++) {
        struct Object *obj = spawn_object_relative(0, random_float() * random_sign() * 1000.0f, 0, random_float() * random_sign() * 1000.0f, o, modelId, behavior);
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
                spawn_multiple_enemies(bhvOctoball, MODEL_OCTOBALL, 5);
                o->oAction++;
            }
            break;
        case 2: //wait for wave 2 to end
            if(count_objects_with_behavior(bhvOctoball) == 0){
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

#define OFFSET 180
void bhv_crane_arrow_controller_init(void) {
    o->oObjF4 = spawn_object_relative_with_scale(0, OFFSET, 0, 0, 2.0f, o, MODEL_CRANE_ARROW, bhvCraneArrow);
    o->oObjF8 = spawn_object_relative_with_scale(1, -OFFSET, 0, 0, 2.0f, o, MODEL_CRANE_ARROW, bhvCraneArrow);
    o->oObjF4->oFaceAngleYaw += 0x8000;
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
                gLakituState.mode = CAMERA_MODE_CRANE;
#if ENABLE_RUMBLE
                queue_rumble_data(5, 80);
#endif
            }
            break;

        case PURPLE_SWITCH_ACT_TICKING:
            if (gMarioObject->platform != o) {
                    o->oAction++;
            }

            struct Object *crane = o->parentObj->oObjFC;
            if(crane != NULL){
                //if first arrow  : 30 * (1 - 0 *2) => 30 *  1 =>  30 ; so angle increment
                //if second arrow : 30 * (1 - 1 *2) => 30 * -1 => -30 ; so angle decrement
                //this calcul avoid to do one more if statement
                crane->oMoveAngleYaw += 90 * (1 - GET_BPARAM2(o->oBehParams) * 2);
            }
            break;

        case PURPLE_SWITCH_ACT_UNPRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 0.2f, 2.0f);
            if (o->oTimer == 3) {
                o->oAction = PURPLE_SWITCH_ACT_IDLE;
                gLakituState.mode = CAMERA_MODE_8_DIRECTIONS;
            }
            break;
    }
    o->oShotByShotgun = 0;//--E
}

void bhv_crane_init(void) {
    o->oObjF4 = spawn_object_relative_with_scale(0, 0, 800, 4000, 1.0f, o, MODEL_CRANE_HEAD, bhvCraneHead);
}

void bhv_crane_head_loop(void) {
    cur_obj_set_pos_relative(o->parentObj, 0, 900, 4200);
    o->oMoveAngleYaw = o->parentObj->oMoveAngleYaw;
    o->oFaceAnglePitch += 300;
}

void bhv_crane_rock_init(void) {
    o->oHomeY = o->oPosY;
    o->craneHeadObj = cur_obj_nearest_object_with_behavior(bhvCraneHead);
    o->oCarvingTimer = 0;
}

void bhv_crane_rock_loop(void) {
    switch(o->oAction){
        case 0: //wait
            o->craneHeadObj = cur_obj_nearest_object_with_behavior(bhvCraneHead);
            if(o->craneHeadObj != NULL) {
                if(dist_between_objects(o->craneHeadObj, o) < 2000) {
                    o->oAction++;
                }
            }
        break;

        case 1: //carve
            o->oCarvingTimer++;
            //rumble effect
            o->oPosY = o->oTimer % 2 ? o->oHomeY + 20.0f : o->oHomeY - 20.0f;
            //explode if carved enough
            if(o->oCarvingTimer > 250){
                o->oAction++;
            }
            //stop carving if the crane head is too far
            if(dist_between_objects(o->craneHeadObj, o) > 2000) {
                o->oCarvingTimer = 0;
                o->oAction = 0;
            }
        break;
        case 2: //explode
            create_sound_spawner(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION);
            spawn_mist_particles_variable(0, 0, 80.0f);
            spawn_triangle_break_particles(30, MODEL_DIRT_ANIMATION, 3.0f, 4);
            //if it was the last rock
            if(count_objects_with_behavior(bhvCraneRock) == 1){
                //play_puzzle_jingle();
                bhv_spawn_star_no_level_exit_at_object(3, gMarioObject);
            }
            obj_mark_for_deletion(o);
        break;
    }
}

//--------------------PAINT GUN--------------------//

void bhv_paint_gun_loop(void) {
    o->oMoveAngleYaw = o->oAngleToMario;
    obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_PITCH_INDEX, 0x1000);
    o->oFaceAnglePitch = o->oMoveAnglePitch;
}