#include "src/game/area.h"

void bhv_g_star_door_init(void) {
   
}

void bhv_g_star_door_loop(void) {
    if (o->oAction == 1) {

        if (o->oTimer == 1) {
            cur_obj_play_sound_2(SOUND_MITM_LEVEL_G_0_STAR_DOOR);
            set_mario_action(gMarioState, ACT_CUTSCENE_CONTROLLED, 0);
        }
        set_mario_anim_with_accel(gMarioState, MARIO_ANIM_RUNNING, 0x00040000);
        gMarioState->faceAngle[1] = o->oFaceAngleYaw;
        approach_f32_asymptotic_bool(&gMarioState->pos[0], o->oPosX, 0.8f);
        approach_f32_asymptotic_bool(&gMarioState->pos[2], o->oPosZ - (o->oTimer * 2), 0.8f);

        if (o->oTimer == 60) {
            play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 60, 255, 255, 255);
        }

        gCamera->cutscene = 1;
        gLakituState.goalPos[0] = o->oPosX;
        gLakituState.goalPos[1] = o->oPosY + 200;
        gLakituState.goalPos[2] = o->oPosZ + 800;

        gLakituState.goalFocus[0] = o->oPosX;
        gLakituState.goalFocus[1] = o->oPosY + 100;
        gLakituState.goalFocus[2] = o->oPosZ;
    }
}

