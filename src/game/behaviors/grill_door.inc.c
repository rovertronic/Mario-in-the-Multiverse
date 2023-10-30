// grill_door.inc.c

#include "actors/common0.h"

struct OpenableGrill {
    s16 halfWidth;
    ModelID16 modelID;
    const Collision *collision;
};

struct OpenableGrill gOpenableGrills[] = {
    { 320, MODEL_BOB_BARS_GRILLS, bob_seg7_collision_gate },
    { 410, MODEL_HMC_RED_GRILLS,  hmc_seg7_collision_grill_door },
    { 480, MODEL_METAL_BOX/*MODEL_LEVEL_I_WOODEN_GATE*/, metal_box_seg8_collision_08024C28/*wooden_gate_collision*/}
};

void bhv_openable_cage_door_loop(void) {
    if (o->oAction == OPENABLE_GRILL_DOOR_ACT_CLOSED) {
        if (o->parentObj->oOpenableGrillIsOpen) {
            o->oAction++;
        }
    } else if (o->oAction == OPENABLE_GRILL_DOOR_ACT_OPENING) {
        if (o->oTimer < 64) {
            o->oMoveAngleYaw -= o->oBehParams2ndByte * 0x100;
        } else {
            o->oAction++;
        }
    }
}

void bhv_openable_grill_loop(void) {
    struct Object *grillObj;
    s32 grillIdx;

    switch (o->oAction) {
        case OEPNABLE_GRILL_ACT_SPAWN:
            grillIdx = o->oBehParams2ndByte;

            grillObj = spawn_object_relative(-1, gOpenableGrills[grillIdx].halfWidth, 0, 0, o,
                                             gOpenableGrills[grillIdx].modelID, bhvOpenableCageDoor);
            grillObj->oMoveAngleYaw += 0x8000;
            obj_set_collision_data(grillObj, gOpenableGrills[grillIdx].collision);

            grillObj = spawn_object_relative(1, -gOpenableGrills[grillIdx].halfWidth, 0, 0, o,
                                             gOpenableGrills[grillIdx].modelID, bhvOpenableCageDoor);
            obj_set_collision_data(grillObj, gOpenableGrills[grillIdx].collision);

            o->oAction++;
            break;

        case OEPNABLE_GRILL_IDLE_CLOSED:
            if (
                (o->oOpenableGrillFloorSwitchObj = cur_obj_nearest_object_with_behavior(bhvFloorSwitchGrills)) != NULL ||
                (o->oOpenableGrillFloorSwitchObj = cur_obj_nearest_object_with_behavior(bhvWoodenLever)) != NULL) {
                o->oAction++;
            }
            break;

        case OEPNABLE_GRILL_OPENING:
            grillObj = o->oOpenableGrillFloorSwitchObj;
    
            if ((obj_has_behavior(grillObj, bhvFloorSwitchGrills) && grillObj->oAction == OPENABLE_GRILL_DOOR_ACT_OPEN) 
            || (obj_has_behavior(grillObj, bhvWoodenLever) && grillObj->oAction == 1)) {
                o->oOpenableGrillIsOpen = TRUE;
                cur_obj_play_sound_2(SOUND_GENERAL_CAGE_OPEN);
                o->oAction++;

                // Only play the jingle once
                if (o->oBehParams2ndByte != 0) {
                    play_puzzle_jingle();
                }
            }
            break;

        case OEPNABLE_GRILL_IDLE_OPEN:
            break;
    }
}
