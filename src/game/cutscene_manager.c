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
#include "audio/external.h"
#include "seq_ids.h"

// Quick, dirty, and simple cutscene system. Not the most sophisticated solution, but it gets the job done for what this project actually needs.

Vec3f cm_camera_pos = {0.0f,0.0f,0.0f};
Vec3f cm_camera_foc = {0.0f,0.0f,0.0f};
u32 cm_cutscene_timer = 0;
f32 cm_fov = 45.0f;
u8 cm_cutscene_on = FALSE;
s8 cm_camera_object = 0;
s8 cm_target_camera_object = 0;
u8 cm_textbox_speaker = CM_SPEAKER_NEUTRAL;
u8 cm_textbox_target_speaker = CM_SPEAKER_NEUTRAL;
u8 cm_textbox_a_signal = FALSE;
f32 cm_textbox_alpha = 0.0f;
f32 cm_textbox_text_alpha = 0.0f;
char * cm_textbox_text = NULL;
char * cm_textbox_text_target = NULL;

s32 cm_wait_for_transition(void) {
    if (cm_textbox_text == cm_textbox_text_target) {
        return TRUE;
    } else {
        cm_cutscene_timer--;
    }
    return FALSE;
}

s32 cm_press_a_or_b(void) {
    if ((cm_textbox_text_alpha >= 254.0f)&&(gPlayer1Controller->buttonPressed & (A_BUTTON | B_BUTTON))) {
        play_sound(SOUND_MENU_YOSHI_GAIN_LIVES, gGlobalSoundSource);
        cm_textbox_a_signal = FALSE;
        return TRUE;
    } else {
        cm_textbox_a_signal = TRUE;
        cm_cutscene_timer--;
    }
    return FALSE;
}


void cm_mario_anim(s32 animid) {
    set_mario_animation(gMarioState,animid);
}


char ascii_peach1[] = {"Thank you all for coming to my birthday party."};
char ascii_peach2[] = {
"Give a warm welcome to our guest, Mario, who\n\
protects the Mushroom Kingdom every day."};
char ascii_peach3[] = {
"With that being said, it's time to unveil the gift\n\
that's being given to me."};
char ascii_peach4[] = {"Professor E.Gadd, you have the floor."};
char ascii_egadd1[] = {
"Today, I'm honored to present to you a marvel\n\
of scientific ingenuity:"};
char ascii_egadd_mm[] = {
"The Multiverse Machine!"
};
char ascii_egadd2[] = {
"Ho, this device has the capability to traverse\n\
various dimensions and alternate realities!"};
char ascii_egadd3[] = {
"Yes, you heard correctly, we're talking about\n\
the very fabric of space-time itself!"};
char ascii_egadd4[] = {
"By the power of the stars, we shall embark\n\
on journeys beyond our wildest imaginations."};
char ascii_egadd5[] = {
"We will unravel the secrets of the cosmos\n\
one dimension at a time!"};
char ascii_peach5[] = {
"Incredible! We should start up the machine and\n\
take a trip as soon as possible."};
char ascii_peach6[] = {"Wh- What's all that shaking about?"};
char ascii_bowser1[] = {"Gwahaha! It's me, Bowser!"};
char ascii_bowser2[] = {
"Happy birthday, Peaches. I am here to... well..."};
char ascii_bowser3[] = {
"...Confess my undying love to you!!"
};
char ascii_peach7[] = {
"After everything you've put me through...?\n\
Not a chance. Nor will you ever get one."};
char ascii_peach8[] = {"Get out of my sight."};
char ascii_bowser4[] = {
"Well-! If you won't love me, then surely I\n\
can find an alternate universe where you will!"};
char ascii_bowser5[] = {
"Outta my way! I need to use that machine!"
};
struct Object * intro_breakdoor;
struct Object * intro_cloth;
struct Object * intro_peach;

void cm_intro_cutscene(void) {
    switch(cm_cutscene_timer) {
        case 0:
            intro_breakdoor = cur_obj_nearest_object_with_behavior(bhvIntroBreakdoor);
            intro_cloth = cur_obj_nearest_object_with_behavior(bhvIntroCloth);
            intro_peach = cur_obj_nearest_object_with_behavior(bhvIntroPeach);

            //play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_LEVEL_INSIDE_CASTLE), 0);
            cm_fov = 64.0f;
            gMarioObject->header.gfx.angle[1] += 0x8000;
            gMarioObject->header.gfx.pos[2] += 240.0f;
            set_mario_anim_with_accel(gMarioState, MARIO_ANIM_TIPTOE, 0x00028000);
            break;
        case 60:
            cm_mario_anim(MARIO_ANIM_FIRST_PERSON);
            break;
        case 80:
            cm_camera_object = 1;
            cm_target_camera_object = 1;
            cm_textbox_target_speaker = CM_SPEAKER_PEACH;
            cm_textbox_text_target = &ascii_peach1;
            break;
        case 81:
            cm_fov = 45.0f;
            break;
        case 90:
            if (cm_press_a_or_b()) {
                cm_target_camera_object = 2;
                cm_textbox_text_target = &ascii_peach2;
            }
            break;
        case 130:
            cm_mario_anim(MARIO_ANIM_CREDITS_WAVING);
            play_sound(SOUND_MARIO_HELLO, gGlobalSoundSource);
            break;
        case 140:
            if (cm_press_a_or_b()) {
                cm_target_camera_object = 1;
                cm_textbox_text_target = &ascii_peach3;
            }
            break;
        case 141:
            if (cm_wait_for_transition()) {
                obj_init_animation(intro_peach,PEACH_ANIM_0);
            }
        break;
        case 150:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_peach4;
            }
            break;
        case 160:
            if (cm_press_a_or_b()) {
                cm_textbox_target_speaker = CM_SPEAKER_EGADD;
                cm_textbox_text_target = &ascii_egadd1;
                cm_target_camera_object = 3;
            }
            break;
        case 165:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_egadd_mm;
            }
            break;
        case 166:
            if (cm_wait_for_transition()) {
                //reveal thingy
                play_sound(SOUND_GENERAL_WING_FLAP, gGlobalSoundSource);
            }
            break;
        case 170:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_egadd2;
            }
            break;
        case 180:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_egadd3;
            }
            break;
        case 190:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_egadd4;
            }
            break;
        case 200:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_egadd5;
            }
            break;
        case 210:
            if (cm_press_a_or_b()) {
                cm_target_camera_object = 1;
                cm_textbox_target_speaker = CM_SPEAKER_PEACH;
                cm_textbox_text_target = &ascii_peach5;
            }
            break;
        case 220:
            if (cm_press_a_or_b()) {
                cm_target_camera_object = 0;
                cm_textbox_text_target = &ascii_peach6;
            }
            break;
        case 221:
            if (cm_wait_for_transition()) {
                cur_obj_play_sound_2(SOUND_GENERAL2_PYRAMID_TOP_SPIN);
                cm_mario_anim(MARIO_ANIM_MISSING_CAP);
                stop_background_music(SEQUENCE_ARGS(4, SEQ_LEVEL_INSIDE_CASTLE));
            }
            break;
        case 300:
            if (cm_press_a_or_b()) {
                cm_target_camera_object = 4;
                cm_textbox_target_speaker = CM_SPEAKER_BOWSER;
                cm_textbox_text_target = &ascii_bowser1;
            }
            break;
        case 301:
            if (cm_wait_for_transition()) {
                //play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_LEVEL_BOSS_KOOPA), 0);
            }
            break;

        case 325:
            //blow open door
            play_sound(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION, gGlobalSoundSource);
            obj_mark_for_deletion(intro_breakdoor);
            break;

        case 350:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_bowser2;
            }
            break;
        case 360:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_bowser3;
            }
            break;
        case 370:
            if (cm_press_a_or_b()) {
                cm_target_camera_object = 1;
                cm_textbox_target_speaker = CM_SPEAKER_PEACH;
                cm_textbox_text_target = &ascii_peach7;
            }
            break;
        case 380:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_peach8;
            }
            break;
        case 390:
            if (cm_press_a_or_b()) {
                cm_target_camera_object = 4;
                cm_textbox_target_speaker = CM_SPEAKER_BOWSER;
                cm_textbox_text_target = &ascii_bowser4;
            }
            break;
        case 400:
            if (cm_press_a_or_b()) {
                cm_target_camera_object = 5;
                cm_textbox_target_speaker = CM_SPEAKER_BOWSER;
                cm_textbox_text_target = &ascii_bowser5;
            }
            break;
        case 410:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = NULL;
            }
            break;

        case 420:
            // don't forget- do a dolly zoom
            stop_background_music(SEQUENCE_ARGS(4, SEQ_LEVEL_BOSS_KOOPA));
            cm_camera_object = 3;
            break;

        case 430: //CRACK!
            play_sound(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION, gGlobalSoundSource);
            break;

        case 440:
            cm_camera_object = 6;
            break;

        case 450:
            initiate_warp(LEVEL_G, 0x01, 0x0A, WARP_FLAGS_NONE);
            fade_into_special_warp(WARP_SPECIAL_NONE, 0);
            break;
    }

    if (cm_cutscene_timer < 60) {
        gMarioObject->header.gfx.pos[2] -= 4.0f;
    }
    if (cm_cutscene_timer > 449) {
        cur_obj_play_sound_1(SOUND_ENV_WIND1);
    }
    if (cm_cutscene_timer > 166) {
        if (intro_cloth) {
            intro_cloth->header.gfx.scale[1] = approach_f32_asymptotic(intro_cloth->header.gfx.scale[1],0.05f,0.1f);

            intro_cloth->header.gfx.scale[0] = approach_f32_asymptotic(intro_cloth->header.gfx.scale[0],1.2f,0.1f);
            intro_cloth->header.gfx.scale[2] = approach_f32_asymptotic(intro_cloth->header.gfx.scale[2],1.2f,0.1f);
        }
    }
}

void cm_manager_object_loop(void) {
    if (o->oAction == 0) {
        //init a cutscene
        o->oAction = 1;
        cm_cutscene_on = TRUE;
        cm_cutscene_timer = 0;
        cm_camera_object = 0;
        cm_target_camera_object = 0;
        cm_fov = 45.0f;
        cm_textbox_alpha = 0.0f;
        cm_textbox_text = NULL;
        cm_textbox_speaker = CM_SPEAKER_NEUTRAL;
        set_mario_action(gMarioState,ACT_CM_CUTSCENE,0);
        set_mario_animation(gMarioState,MARIO_ANIM_FIRST_PERSON);
    }
    switch(o->oBehParams2ndByte) {
        case 0:
            cm_intro_cutscene();
        break;
    }

    // Junky alpha transitions
    if (cm_textbox_text != NULL) {
        cm_textbox_alpha += 20.0f;
        if (cm_textbox_alpha > 255.0f) {
            cm_textbox_alpha = 255.0f;
        }
    } else {
        cm_textbox_alpha -= 20.0f;
        if (cm_textbox_alpha < 0.0f) {
            cm_textbox_alpha = 0.0f;
        }
    }

    if (cm_textbox_text_target != cm_textbox_text) {
        cm_textbox_text_alpha -= 20.0f;
        if (cm_textbox_text_alpha < 0.0f) {
            cm_textbox_text_alpha = 0.0f;
            cm_textbox_text = cm_textbox_text_target;
            cm_textbox_speaker = cm_textbox_target_speaker;
            cm_camera_object = cm_target_camera_object;
        }
    } else {
        cm_textbox_text_alpha += 20.0f;
        if (cm_textbox_text_alpha > 255.0f) {
            cm_textbox_text_alpha = 255.0f;
        }
    }

    if (cm_textbox_text_alpha > cm_textbox_alpha) {
        cm_textbox_text_alpha = cm_textbox_alpha;
    }

    cm_cutscene_timer ++;
}

void cm_camera_object_loop(void) {
    //print_text_fmt_int(210, 72, "CAM %d", cm_camera_object);
    //print_text_fmt_int(210, 92, "TIME %d", cm_cutscene_timer);

    if ((o->oBehParams2ndByte==0)&&(cm_cutscene_timer > 221)&&(cm_cutscene_timer<300)) {
        o->oPosX = o->oHomeX + random_float()*20.0f;
        o->oPosY = o->oHomeY + random_float()*20.0f;
        o->oPosZ = o->oHomeZ + random_float()*20.0f;
    }

    if (o->oBehParams2ndByte == cm_camera_object) {
        vec3f_copy(cm_camera_pos,&o->oPosVec);
        cm_camera_foc[0] = o->oPosX + sins(o->oFaceAngleYaw) * coss(o->oFaceAnglePitch) * 5.0f;
        cm_camera_foc[1] = o->oPosY + sins(o->oFaceAnglePitch) * -5.0f;
        cm_camera_foc[2] = o->oPosZ + coss(o->oFaceAngleYaw) * coss(o->oFaceAnglePitch) * 5.0f;
    }
}