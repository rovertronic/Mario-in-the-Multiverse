#ifndef CUTSCENE_MANAGER_H
#define CUTSCENE_MANAGER_H

#include "types.h"

extern Vec3f cm_camera_pos;
extern Vec3f cm_camera_foc;
extern u8 cm_cutscene_on;
extern f32 cm_fov;

extern void cm_manager_object_loop(void);
extern void cm_camera_object_loop(void);

#endif