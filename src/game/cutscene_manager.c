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
#include "main.h"

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
u8 cm_crack_signal = FALSE;
s16 cm_roll = 0;
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
struct Object * intro_egadd;
struct Object * intro_machine;
struct Object * intro_bowser;
static struct SpawnParticlesInfo sIntroDoorParticles = {
    /* behParam:        */ 0,
    /* count:           */ 8,
    /* model:           */ MODEL_INTRO_ROCK,
    /* offsetY:         */ 0,
    /* forwardVelBase:  */ 16,
    /* forwardVelRange: */ 8,
    /* velYBase:        */ 20,
    /* velYRange:       */ 40,
    /* gravity:         */ -4,
    /* dragStrength:    */ 0,
    /* sizeBase:        */ 10.0f,
    /* sizeRange:       */ 20.0f,
};


void cm_intro_cutscene(void) {
    struct Object * normal_o;

    switch(cm_cutscene_timer) {
        case 0:
            intro_breakdoor = cur_obj_nearest_object_with_behavior(bhvIntroBreakdoor);
            intro_cloth = cur_obj_nearest_object_with_behavior(bhvIntroCloth);
            intro_peach = cur_obj_nearest_object_with_behavior(bhvIntroPeach);
            intro_egadd = cur_obj_nearest_object_with_behavior(bhvIntroEgadd);
            intro_machine = cur_obj_nearest_object_with_behavior(bhvIntroMachine);

            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_PEACHS_BIRTHDAY), 0);
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
        case 170:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_egadd_mm;
            }
            break;
        case 190:
            if (cm_wait_for_transition()) {
                //reveal thingy
                play_sound(SOUND_GENERAL_WING_FLAP, gGlobalSoundSource);
            }
            break;
        case 200:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_egadd2;
            }
            break;
        case 210:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_egadd3;
            }
            break;
        case 220:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_egadd4;
            }
            break;
        case 230:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_egadd5;
            }
            break;
        case 240:
            if (cm_press_a_or_b()) {
                cm_target_camera_object = 1;
                cm_textbox_target_speaker = CM_SPEAKER_PEACH;
                cm_textbox_text_target = &ascii_peach5;
            }
            break;
        case 250:
            if (cm_press_a_or_b()) {
                cm_target_camera_object = 7;
                cm_textbox_text_target = &ascii_peach6;
            }
            break;
        case 251:
            if (cm_wait_for_transition()) {
                cm_roll = 0x500; // dutch angle
                cur_obj_play_sound_2(SOUND_GENERAL2_PYRAMID_TOP_SPIN);
                cm_mario_anim(MARIO_ANIM_MISSING_CAP);
                stop_background_music(SEQUENCE_ARGS(4, SEQ_PEACHS_BIRTHDAY));
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
                cm_roll = 0;
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_BOWSER_TIME), 0);
            }
            break;

        case 325:
            //blow open door
            normal_o = o;
            o = intro_breakdoor;
            cur_obj_spawn_particles(&sIntroDoorParticles);
            spawn_mist_particles_variable(0, 0, 200.0f);
            play_sound(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION, gGlobalSoundSource);
            intro_bowser = spawn_object(o,MODEL_WEDSER,bhvIntroBowser);
            intro_bowser->oFaceAngleYaw -= 0x2000;
            intro_bowser->oForwardVel = 20.0f;
            obj_mark_for_deletion(intro_breakdoor);
            o = normal_o;
            //so fucking zeevil
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
        case 391:
            if (cm_wait_for_transition()) {
                obj_init_animation(intro_bowser,2);
            }
            break;
        case 400:
            if (cm_press_a_or_b()) {
                cm_target_camera_object = 5;
                cm_textbox_target_speaker = CM_SPEAKER_BOWSER;
                cm_textbox_text_target = &ascii_bowser5;
            }
            break;
        case 401:
            if (cm_wait_for_transition()) {
                vec3f_copy(&intro_bowser->oPosVec,&intro_egadd->oPosVec);
                intro_bowser->oPosZ += 400.0f;
                intro_bowser->oFaceAngleYaw = 0x8000;
                intro_bowser->oMoveAngleYaw = 0x8000;
                obj_init_animation(intro_bowser,0);
            }
            break;
        case 410:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = NULL;
                cm_target_camera_object = 3;
            }
            break;
        case 411:
            cm_wait_for_transition();
            break;
        case 412:
            obj_init_animation(intro_bowser,3);
            break;

        // Bowser blows fire on the machine, it overheats and explodes
        case 450:
            // don't forget- do a dolly zoom
            stop_background_music(SEQUENCE_ARGS(4, SEQ_BOWSER_TIME));
            cm_camera_object = 8;
            cm_target_camera_object = 8;
            play_sound(SOUND_ABILITY_MULTIVERSE_CRACK, gGlobalSoundSource);
            break;

        case 459:
            cm_crack_signal = TRUE;
        break;
        case 460: //CRACK!
            for (u8 i=0; i<250; i++) {
                osRecvMesg(&gGameVblankQueue, &gMainReceivedMesg, OS_MESG_BLOCK);
            }
            cm_camera_object = 6;
            cm_target_camera_object = 6;
            cm_fov = 45;
            break;

        case 461:
            cm_crack_signal = FALSE;
            play_sound(SOUND_MARIO_WAAAOOOW, gGlobalSoundSource);
            break;

        case 600:
            initiate_warp(LEVEL_G, 0x01, 0x0A, WARP_FLAGS_NONE);
            fade_into_special_warp(WARP_SPECIAL_NONE, 0);
            break;
    }

    if (cm_cutscene_timer < 60) {
        gMarioObject->header.gfx.pos[2] -= 4.0f;
    }
    if ((cm_cutscene_timer > 170)&&(cm_cutscene_timer < 250)) {
        obj_turn_toward_object(intro_egadd, intro_cloth, O_FACE_ANGLE_YAW_INDEX, 0x800);
    }
    if (cm_cutscene_timer > 190) {
        intro_cloth->header.gfx.scale[1] = approach_f32_asymptotic(intro_cloth->header.gfx.scale[1],0.05f,0.1f);
        intro_cloth->header.gfx.scale[0] = approach_f32_asymptotic(intro_cloth->header.gfx.scale[0],1.2f,0.1f);
        intro_cloth->header.gfx.scale[2] = approach_f32_asymptotic(intro_cloth->header.gfx.scale[2],1.2f,0.1f);
    }
    if (cm_cutscene_timer > 251) {
        obj_turn_toward_object(intro_egadd, gMarioObject, O_FACE_ANGLE_YAW_INDEX, 0x800);
    }
    if ((cm_cutscene_timer > 325)&&(cm_cutscene_timer < 391)) {
        intro_bowser->oPosX += sins(intro_bowser->oFaceAngleYaw) * intro_bowser->oForwardVel;
        intro_bowser->oPosZ += coss(intro_bowser->oFaceAngleYaw) * intro_bowser->oForwardVel;
        if (intro_bowser->oForwardVel < 1.0f) {
            obj_init_animation(intro_bowser,0);
            intro_bowser->oForwardVel = 0.0f;
        } else {
            intro_bowser->oForwardVel *= 0.93f;
        }
    }
    if (cm_cutscene_timer > 411 && cm_cutscene_timer < 420) {
        intro_egadd->oPosX-=23.0f;
    }
    if (cm_cutscene_timer > 420) {
        intro_egadd->header.gfx.animInfo.animFrame = 0;
        if (gGlobalTimer % 2 == 0) {
            intro_egadd->oPosZ += 4.0f;
        } else {
            intro_egadd->oPosZ -= 4.0f;
        }
        obj_turn_toward_object(intro_egadd, intro_machine, O_FACE_ANGLE_YAW_INDEX, 0x800);
        if (intro_machine->oOpacity < 187) {
            if (intro_bowser->header.gfx.animInfo.animFrame > 10) {
                intro_machine->oOpacity++;
                cur_obj_play_sound_1(SOUND_AIR_BOWSER_SPIT_FIRE);
                struct Object * flame = spawn_object(intro_bowser, MODEL_RED_FLAME, bhvFlameMovingForwardGrowing);
                flame->oPosY += 180.0f;
                flame->oPosZ -= 120.0f;
            }
            if (cm_cutscene_timer > 450) {
                cm_cutscene_timer = 451;
            }
        }
    }
    if (cm_cutscene_timer > 460) {
        cur_obj_play_sound_1(SOUND_ENV_WIND1);
        cm_roll += 0x100;
        cm_fov += 0.6f;

        //suck everyone
        // this implementation utterly fucking sucks. too bad!
        struct ObjectNode *listHead = &gObjectLists[OBJ_LIST_DEFAULT];
        struct Object *obj = (struct Object *) listHead->next;

        while (obj != (struct Object *) listHead) {
            f32 dx = intro_machine->header.gfx.pos[0] - obj->oPosX;
            f32 dy = intro_machine->header.gfx.pos[1] - obj->oPosY + 120.0f;
            f32 dz = intro_machine->header.gfx.pos[2] - obj->oPosZ;
            s16 targetPitch = atan2s(sqrtf(sqr(dx) + sqr(dz)), dy);

            obj_turn_toward_object(obj, intro_machine, O_MOVE_ANGLE_YAW_INDEX, 0x1000);

            obj->oMoveAnglePitch = approach_s16_symmetric(obj->oMoveAnglePitch, targetPitch, 0x1000);
            obj->oPosY += sins(obj->oMoveAnglePitch) * 30.0f;

            obj->oPosX += sins(obj->oMoveAngleYaw) * 30.0f;
            obj->oPosZ += coss(obj->oMoveAngleYaw) * 30.0f;

            obj->oFaceAngleRoll += 0x600;

            obj = (struct Object *) obj->header.next;
        }

        obj = gMarioObject;
        cm_mario_anim(MARIO_ANIM_FLY_FROM_CANNON);

        obj->header.gfx.pos[1] += 15.0f;
        obj->header.gfx.pos[0] += sins(0x8000) * 30.0f;
        obj->header.gfx.pos[2] += coss(0x8000) * 30.0f;
    }
}

void cm_kirby_cutscene(void) {
    switch(cm_cutscene_timer) {
        case 0:
            set_mario_action(gMarioState,ACT_SLEEPING,0);
            cm_target_camera_object = 0;
            cm_camera_object = 0;
        break;
        case 90:
            cm_cutscene_on = FALSE;
        break;
    }
}

char ascii_gaster1[] = {
"It appears...\n\
We have an unexpected visitor."};
char ascii_yukari1[] = {
"It wasn't enough for you to beat Bowser\n\
and have your happily ever after?"};
char ascii_yukari2[] = {
"You took it upon yourself to snoop around\n\
the dream realm..."};
char ascii_yukari2_1[] = {
"...and stick your big nose\n\
where it does not belong."};

char ascii_gaster2[] = {
"Indeed."};
char ascii_gaster3[] = {
"At this point, we haven't much choice\n\
but to have you dealt with."};

void cm_secretboss_intro(void) {
    switch(cm_cutscene_timer) {
        case 0:
            cm_camera_object = 0;
            cm_target_camera_object = 0;
            cm_textbox_target_speaker = CM_SPEAKER_GASTER;
            cm_textbox_text_target = &ascii_gaster1;
            break;
        case 1:
            if (cm_press_a_or_b()) {
                cm_camera_object = 1;
                cm_target_camera_object = 1;
                cm_textbox_target_speaker = CM_SPEAKER_YUKARI;
                cm_textbox_text_target = &ascii_yukari1;
            }
            break;
        case 2:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_yukari2;
            }
            break;
        case 3:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_yukari2_1;
            }
            break;
        case 4:
            if (cm_press_a_or_b()) {
                cm_target_camera_object = 0;
                cm_textbox_target_speaker = CM_SPEAKER_GASTER;
                cm_textbox_text_target = &ascii_gaster3;
            }
            break;
        case 5:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = NULL;
            }
            break;
        case 60:
            set_mario_action(gMarioState,ACT_IDLE,0);
            cm_cutscene_on = FALSE;
            break;
    }
}

void cm_secretboss_end(void) {
    switch(cm_cutscene_timer) {
        case 0:
            cm_camera_object = 0;
            cm_target_camera_object = 0;
            cm_textbox_target_speaker = CM_SPEAKER_ATREUS;
            cm_textbox_text_target = &ascii_gaster1;
            break;
        case 1:
            if (cm_press_a_or_b()) {
                cm_textbox_target_speaker = CM_SPEAKER_YUKARI;
                cm_textbox_text_target = &ascii_yukari1;
            }
            break;
        case 2:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_yukari2;
            }
            break;
        case 3:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_yukari2_1;
            }
            break;
        case 4:
            if (cm_press_a_or_b()) {
                cm_target_camera_object = 0;
                cm_textbox_target_speaker = CM_SPEAKER_GASTER;
                cm_textbox_text_target = &ascii_gaster3;
            }
            break;
        case 5:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = NULL;
            }
            break;
        case 60:
            set_mario_action(gMarioState,ACT_IDLE,0);
            cm_cutscene_on = FALSE;
            break;
    }
}

char ascii_atreus_1[] = "IT APPEARS\nA VISITOR HAS ARRIVED.";
char ascii_atreus_2[] = "PASS THROUGH MY EYE\nAND I WILL LEND YOU MY POWER.";

char ascii_fb_bowser_1[] = "I have come all this way.";
char ascii_fb_bowser_2[] = "And yet... not a one.";
char ascii_fb_bowser_3[] = "Not a single universe where Peach loves me.";
char ascii_fb_bowser_4[] = "I've been to THOUSANDS.";
char ascii_fb_bowser_5[] = "Yet, against all odds, they're all the same.";
char ascii_fb_bowser_6[] = "Well, that does it.";
char ascii_fb_bowser_7[] = "If not one shred of the observable universe\nwill indulge my needs,";
char ascii_fb_bowser_8[] = "Then I see it fit that it has no right to exist.";
char ascii_fb_bowser_9[] = "I will vanquish you, and use ATREUS's power\nto destroy EVERYTHING.";
char ascii_fb_bowser_10[] = "My wish will be to wipe every molecule, atom,\nand soul from this plane of existence.";

char ascii_atreus_3[] = "IT APPEARS\nWE HAVE A DISPUTE.";
char ascii_atreus_4[] = "THIS IS HOW IT WILL BE:";
char ascii_atreus_5[] = "ONE ON ONE COMBAT\nTHE VICTOR WILL EARN AN AUDIENCE WITH I";
char ascii_atreus_6[] = "WELL, THAT IS THAT.\nHAVE AT IT!";

struct Object * fb_bowser;

void cm_finalboss_1(void) {
    switch(cm_cutscene_timer) {
        case 0:
            cm_camera_object = 0;
            cm_target_camera_object = 0;
            break;
        case 60:
            cm_textbox_target_speaker = CM_SPEAKER_ATREUS;
            cm_textbox_text_target = &ascii_atreus_1;
            break;
        case 61:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_atreus_2;
            }
            break;
        case 62:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = NULL;
            }
            break;
        case 120:
                set_mario_action(gMarioState,ACT_IDLE,0);
                cm_cutscene_on = FALSE;
                obj_mark_for_deletion(o);
            break;
    }
}

void cm_finalboss_2(void) {
    switch(cm_cutscene_timer) {
        case 0:
            fb_bowser = cur_obj_nearest_object_with_behavior(bhvBcBowser);

            cm_camera_object = 1;
            cm_target_camera_object = 1;
            break;
        case 16:
            play_sound(SOUND_MARIO_OOOF, gGlobalSoundSource);
            cm_mario_anim(MARIO_ANIM_BACKWARD_KB);
            break;
        case 45:
            cm_target_camera_object = 2;

            cm_textbox_target_speaker = CM_SPEAKER_BOWSER;
            cm_textbox_text_target = &ascii_fb_bowser_1;

            obj_init_animation(fb_bowser,1);
            break;
        case 46:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_fb_bowser_2;
            }
            break;
        case 47:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_fb_bowser_3;
            }
            break;
        case 48:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_fb_bowser_4;
            }
            break;
        case 49:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_fb_bowser_5;
            }
            break;
        case 50:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_fb_bowser_6;
                cm_target_camera_object = 3;
            }
            break;
        case 51:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_fb_bowser_7;
            }
            break;
        case 52:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_fb_bowser_8;
            }
            break;
        case 53:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_fb_bowser_9;
            }
            break;
        case 54:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_fb_bowser_10;
            }
            break;
        case 55:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_atreus_3;
                cm_textbox_target_speaker = CM_SPEAKER_ATREUS;
                cm_target_camera_object = 0;
            }
            break;
        case 56:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_atreus_4;
            }
            break;
        case 57:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_atreus_5;
            }
            break;
        case 58:
            if (cm_press_a_or_b()) {
                cm_textbox_text_target = &ascii_atreus_6;
            }
            break;
    }

    if ((cm_cutscene_timer > 15)&&(cm_cutscene_timer < 35)) {
        gMarioObject->header.gfx.pos[2] += 15.0f;
    }
}

void cm_finalboss_3(void) {

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
        cm_crack_signal = FALSE;
        cm_roll = 0;
        set_mario_action(gMarioState,ACT_CM_CUTSCENE,0);
        set_mario_animation(gMarioState,MARIO_ANIM_FIRST_PERSON);
    }
    switch(o->oBehParams2ndByte) {
        case 0:
            cm_intro_cutscene();
            break;
        case 1:
            cm_kirby_cutscene();
            break;
        case 2:
            cm_secretboss_intro();
            break;
        case 3:
            cm_secretboss_end();
            break;
        case 4:
            cm_finalboss_1();
            break;
        case 5:
            cm_finalboss_2();
            break;
        case 6:

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

    if ((o->oBehParams2ndByte==7)&&(cm_cutscene_timer > 251)&&(cm_cutscene_timer<300)) {
        o->oPosX = o->oHomeX + random_float()*20.0f;
        o->oPosY = o->oHomeY + random_float()*20.0f;
        o->oPosZ = o->oHomeZ + random_float()*20.0f;
    }

    if (o->oBehParams2ndByte==8 &&(cm_cutscene_timer > 450)&&(cm_cutscene_timer < 460)) {
        // dolly zoom
        o->oPosX-=2.0f;
        cm_fov +=0.3f;
    }

    if (o->oBehParams2ndByte == cm_camera_object) {
        vec3f_copy(cm_camera_pos,&o->oPosVec);
        cm_camera_foc[0] = o->oPosX + sins(o->oFaceAngleYaw) * coss(o->oFaceAnglePitch) * 5.0f;
        cm_camera_foc[1] = o->oPosY + sins(o->oFaceAnglePitch) * -5.0f;
        cm_camera_foc[2] = o->oPosZ + coss(o->oFaceAngleYaw) * coss(o->oFaceAnglePitch) * 5.0f;
    }
}