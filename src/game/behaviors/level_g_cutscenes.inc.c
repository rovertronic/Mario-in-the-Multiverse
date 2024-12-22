#include "levels/g/header.h"
#include "src/game/camera.h"

void bhv_level_g_cutscenes_init(void) {
}

void bhv_level_g_cutscenes_loop(void) {
    switch (o->oBehParams2ndByte) {
        case 0:
            set_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
            o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
            f32 dist;
            struct Object *sirKibble = cur_obj_find_nearest_object_with_behavior(bhvSirKibble, &dist);
            sirKibble->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;


            gCamera->cutscene = 1;
            gLakituState.goalPos[0] = 749;
            gLakituState.goalPos[1] = 800;
            gLakituState.goalPos[2] = 446;
            if (move_point_along_spline(gLakituState.goalFocus, segmented_to_virtual(g_area_2_spline_KibbleFocus), &sCutsceneSplineSegment, &sCutsceneSplineSegmentProgress)) {
                gCamera->cutscene = 0;
                clear_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
                obj_mark_for_deletion(o);
            }
            break;
        case 1:
            if (o->oAction == 0) {
                f32 dist;
                struct Object *sirKibble = cur_obj_find_nearest_object_with_behavior(bhvSirKibble, &dist);

                if (!sirKibble || (sirKibble && sirKibble->activeFlags & ACTIVE_FLAG_DEACTIVATED)) {
                    spawn_object_abs_with_rot(o, 0, MODEL_G_STAR_PROJECTILE, bhvStarDrop, o->oF4, o->oF8 + 100, o->oFC, 0, 0, 0);
                    o->oAction = 1;
                }
                else {
                    o->oF4 = sirKibble->oPosX;
                    o->oF8 = sirKibble->oPosY;
                    o->oFC = sirKibble->oPosZ;
                }
                break;
            }
    }
}
