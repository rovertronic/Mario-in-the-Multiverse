#ifndef CUTSCENE_MANAGER_H
#define CUTSCENE_MANAGER_H

#include "types.h"

extern Vec3f cm_camera_pos;
extern Vec3f cm_camera_foc;
extern u8 cm_cutscene_on;
extern f32 cm_fov;
extern f32 cm_textbox_alpha;
extern f32 cm_textbox_text_alpha;
extern char * cm_textbox_text;
extern u8 cm_textbox_speaker;
extern u8 cm_textbox_a_signal;
extern u8 cm_crack_signal;
extern s16 cm_roll;

extern void cm_manager_object_loop(void);
extern void cm_camera_object_loop(void);

enum {
    CM_SPEAKER_NEUTRAL,
    CM_SPEAKER_PEACH,
    CM_SPEAKER_EGADD,
    CM_SPEAKER_BOWSER,
    CM_SPEAKER_YUKARI,
    CM_SPEAKER_GASTER,
    CM_SPEAKER_ATREUS,
};

#endif