#include <ultra64.h>
#include "types.h"
#include "game_init.h"
#include "engine/math_util.h"
#include "camera.h"
#include "lerp.h"

#define LERP_THRESHOLD 400.0f
#define LERP_THRESHOLD_ANGLE 0x3000

s32 absi_lerp(s32 x) {
    if (x >= 0) {
        return x;
    } else {
        return -x;
    }
}

u32 abs_angle_diff_lerp(s16 x0, s16 x1) {
    return absi_lerp((s16) (x1 - x0));
}

s32 approach_angle_lerp(s32 current, s32 target) {
    s32 diff1;
    s32 ret;
    if ((diff1 = abs_angle_diff_lerp(current, target)) >= LERP_THRESHOLD_ANGLE) {
        return target;
    }
    if (_60fps_midframe) {
        ret = (target + current) >> 1;
    } else {
        ret = current - (target - current) >> 1;
    }
    if ((diff1 < (absi_lerp(target - current + 0x10000))) && (diff1 < (absi_lerp(target - current - 0x10000)))) {
        return ret;
    } else {
        return ret + 0x8000;
    }
}

u8 lerp_overshot_flag = FALSE;
f32 approach_pos_lerp(f32 current, f32 target) {
    if (ABS(target - current) >= LERP_THRESHOLD) {
        lerp_overshot_flag = TRUE;
        return target;
    }
    if (_60fps_midframe) {
        return current + ((target - current) * 0.5f);
    } else {
        return current - ((target - current) * 0.5f);
    }
}

f32 approach_pos_lerp_lo(f32 current, f32 target) {
    if (ABS(target - current) >= 10.0f) {
        lerp_overshot_flag = TRUE;
        return target;
    }
    if (_60fps_midframe) {
        return current + ((target - current) * 0.5f);
    } else {
        return current - ((target - current) * 0.5f);
    }
}

void warp_node(struct Object *node) {
    vec3f_copy(node->header.gfx.posLerp, node->header.gfx.pos);
    vec3s_copy(node->header.gfx.angleLerp, node->header.gfx.angle);
    vec3f_copy(node->header.gfx.scaleLerp, node->header.gfx.scale);
    node->header.gfx.bothMats++;
}

void interpolate_node(struct Object *node) {
    for (u32  i = 0; i < 3; i++) {
        node->header.gfx.posLerp[i] = approach_pos_lerp(node->header.gfx.posLerp[i],node->header.gfx.pos[i]);
        node->header.gfx.scaleLerp[i] = approach_pos_lerp(node->header.gfx.scaleLerp[i], node->header.gfx.scale[i]);
        node->header.gfx.angleLerp[i] = approach_angle_lerp(node->header.gfx.angleLerp[i], node->header.gfx.angle[i]);
    }
}


f32 lerp_menu_stack[LMENU_COUNT];
f32 lerp_menu(f32 value,int stack_index) {
    if (!_60fps_midframe) {
        lerp_menu_stack[stack_index] = value;
    } else {
        lerp_menu_stack[stack_index] = approach_pos_lerp(lerp_menu_stack[stack_index],value);
    }
    return lerp_menu_stack[stack_index];
}

f32 lerp_menu_lotolerance(f32 value,int stack_index) {
    if (!_60fps_midframe) {
        lerp_menu_stack[stack_index] = value;
    } else {
        lerp_menu_stack[stack_index] = approach_pos_lerp_lo(lerp_menu_stack[stack_index],value);
    }
    return lerp_menu_stack[stack_index];
}