#include "sm64.h"
#include "game/game_init.h"
#include "game/geo_misc.h"
#include "engine/math_util.h"
#include "engine/colors.h"
#include "area.h"
#include "level_update.h"
#include "print.h"
#include "engine/surface_collision.h"
#include "engine/surface_load.h"
#include "object_list_processor.h"
#include "behavior_data.h"
#include "cutscene_manager.h"

// Quick, dirty, and simple cutscene system. Not the most sophisticated solution, but it gets the job done for what this project actually needs.

Vec3f cm_camera_pos = {0.0f,0.0f,0.0f};
Vec3f cm_camera_foc = {0.0f,0.0f,0.0f};
u32 cm_cutscene_timer = 0;
f32 cm_fov = 45.0f;
u8 cm_cutscene_on = FALSE;
u8 cm_target_camera_object = 0;

void cm_mario_anim(s32 animid) {
    set_mario_animation(gMarioState,animid);
}

void cm_intro_cutscene(void) {
    switch(cm_cutscene_timer) {
        case 0:
            cm_fov = 64.0f;
            gMarioObject->header.gfx.angle[1] += 0x8000;
            gMarioObject->header.gfx.pos[2] += 240.0f;
            set_mario_anim_with_accel(gMarioState, MARIO_ANIM_TIPTOE, 0x00028000);
            break;

        case 60:
            cm_mario_anim(MARIO_ANIM_FIRST_PERSON);
            break;
    }

    if (cm_cutscene_timer < 60) {
        gMarioObject->header.gfx.pos[2] -= 4.0f;
    }
}

void cm_manager_object_loop(void) {
    if (o->oAction == 0) {
        //init a cutscene
        o->oAction = 1;
        cm_cutscene_on = TRUE;
        cm_cutscene_timer = 0;
        cm_target_camera_object = 0;
        cm_fov = 45.0f;
        set_mario_action(gMarioState,ACT_CM_CUTSCENE,0);
        set_mario_animation(gMarioState,MARIO_ANIM_FIRST_PERSON);
    }
    switch(o->oBehParams2ndByte) {
        case 0:
            cm_intro_cutscene();
        break;
    }
    cm_cutscene_timer ++;
}

void cm_camera_object_loop(void) {
    if (o->oBehParams2ndByte == cm_target_camera_object) {
        vec3f_copy(cm_camera_pos,&o->oPosVec);
        cm_camera_foc[0] = o->oPosX + sins(o->oFaceAngleYaw) * coss(o->oFaceAnglePitch) * 5.0f;
        cm_camera_foc[1] = o->oPosY + sins(o->oFaceAnglePitch) * -5.0f;
        cm_camera_foc[2] = o->oPosZ + coss(o->oFaceAngleYaw) * coss(o->oFaceAnglePitch) * 5.0f;
    }

    switch(o->oBehParams2ndByte) {
        case 0:
            //slowly pan up
        break;
    }
}