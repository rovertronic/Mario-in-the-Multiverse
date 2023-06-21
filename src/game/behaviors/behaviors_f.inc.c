#define WATCH_DISTANCE 1300.0f

u32 targetable_behavior_list[] = {
    bhvFloorSwitchAnimatesObject,
    bhvFloorSwitchGrills,
    bhvFloorSwitchHardcodedModel,
    bhvFloorSwitchHiddenObjects,
    bhvBlueCoinSwitch,
    bhvExclamationBox,
    bhvBreakableBox,
    bhvBreakableBoxSmall,
};

struct Object *find_nearest_watch_target(void) {
    //stupid ass function
    struct Object *result;

    for (u8 i=0; i < sizeof(targetable_behavior_list)/4; i++) {
        result = cur_obj_nearest_object_with_behavior(targetable_behavior_list[i]);
        if (result) {
            if (dist_between_objects(gMarioObject,result) < WATCH_DISTANCE) {
                return result;
            }
        }
    }

    return NULL;
}

f32 bruh_scale = 1.0f;
struct Object *last_target = NULL;

void bhv_gadget_aim(void) {
    struct Object *target = find_nearest_watch_target();

    if (last_target != target) {
        last_target = target;
        bruh_scale = 1.0f;
        play_sound(SOUND_GENERAL_BOWSER_KEY_LAND, gGlobalSoundSource);
    }

    if (target) {
        vec3f_copy(&o->oPosVec,&target->oPosVec);
        cur_obj_unhide();
        cur_obj_scale(bruh_scale+1.0f);
        bruh_scale *= 0.9f;

        if (gPlayer1Controller->buttonPressed & L_TRIG) {

            //no switch cases for ptrs : (
            if (target->behavior == segmented_to_virtual(bhvBreakableBox)) {
                spawn_object(target,MODEL_EXPLOSION,bhvExplosion);
                target->oAction = BREAKABLE_BOX_ACT_BROKEN;
            } else if (target->behavior == segmented_to_virtual(bhvBreakableBoxSmall)) {
                spawn_object(target,MODEL_EXPLOSION,bhvExplosion);
                target->oForwardVel = 30.0f;
                target->oMoveAngleYaw = target->oAngleToMario;
            } else if (target->behavior == segmented_to_virtual(bhvFloorSwitchGrills)) {
                target->oAction = PURPLE_SWITCH_ACT_PRESSED;
            } else if (target->behavior == segmented_to_virtual(bhvFloorSwitchAnimatesObject)) {
                target->oAction = PURPLE_SWITCH_ACT_PRESSED;
            } else if (target->behavior == segmented_to_virtual(bhvFloorSwitchHardcodedModel)) {
                target->oAction = PURPLE_SWITCH_ACT_PRESSED;
            } else if (target->behavior == segmented_to_virtual(bhvFloorSwitchHiddenObjects)) {
                target->oAction = PURPLE_SWITCH_ACT_PRESSED;
            }  else if (target->behavior == segmented_to_virtual(bhvExclamationBox)) {
                if (target->oAction == EXCLAMATION_BOX_ACT_ACTIVE) {
                    target->oAction = EXCLAMATION_BOX_ACT_EXPLODE;
                }
            } else if (target->behavior == segmented_to_virtual(bhvBlueCoinSwitch)) {
                if (target->oAction == BLUE_COIN_SWITCH_ACT_IDLE) {
                    target->oAction = BLUE_COIN_SWITCH_ACT_RECEDING;
                    // Recede at a rate of 20 units/frame.
                    target->oVelY = -20.0f;
                    // Set gravity to 0 so it doesn't accelerate when receding.
                    target->oGravity = 0.0f;
                    cur_obj_play_sound_2(SOUND_GENERAL_SWITCH_DOOR_OPEN);
                }
            }
        }

    } else {
        cur_obj_hide();
        bruh_scale = 1.0f;
    }
}