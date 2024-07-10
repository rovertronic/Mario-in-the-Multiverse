#ifndef MARIO_H
#define MARIO_H

#include <PR/ultratypes.h>

#include "macros.h"
#include "types.h"
//--E SG
#include "e__shotgun.h"

s32 is_2d_area(void);
s32 is_anim_at_end(struct MarioState *m);
s32 is_anim_past_end(struct MarioState *m);
s16 set_mario_animation(struct MarioState *m, s32 targetAnimID);
s16 set_mario_anim_with_accel(struct MarioState *m, s32 targetAnimID, s32 accel);
void set_anim_to_frame(struct MarioState *m, s16 animFrame);
s32 is_anim_past_frame(struct MarioState *m, s16 animFrame);
s16 find_mario_anim_flags_and_translation(struct Object *obj, s32 yaw, Vec3s translation);
void update_mario_pos_for_anim(struct MarioState *m);
s16 return_mario_anim_y_translation(struct MarioState *m);
void play_sound_if_no_flag(struct MarioState *m, u32 soundBits, u32 flags);
void play_mario_jump_sound(struct MarioState *m);
void adjust_sound_for_speed(struct MarioState *m);
void play_sound_and_spawn_particles(struct MarioState *m, u32 soundBits, u32 waveParticleType);
void play_mario_action_sound(struct MarioState *m, u32 soundBits, u32 waveParticleType);
void play_mario_landing_sound(struct MarioState *m, u32 soundBits);
void play_mario_landing_sound_once(struct MarioState *m, u32 soundBits);
void play_mario_heavy_landing_sound(struct MarioState *m, u32 soundBits);
void play_mario_heavy_landing_sound_once(struct MarioState *m, u32 soundBits);
void play_mario_sound(struct MarioState *m, s32 primarySoundBits, s32 scondarySoundBits);
void mario_set_forward_vel(struct MarioState *m, f32 speed);
s32 mario_get_floor_class(struct MarioState *m);
u32 mario_get_terrain_sound_addend(struct MarioState *m);
s32 mario_facing_downhill(struct MarioState *m, s32 turnYaw);
u32 mario_floor_is_slippery(struct MarioState *m);
s32 mario_floor_is_slope(struct MarioState *m);
s32 mario_floor_is_steep(struct MarioState *m);
f32 find_floor_height_relative_polar(struct MarioState *m, s16 angleFromMario, f32 distFromMario);
s16 find_floor_slope(struct MarioState *m, s16 yawOffset);
Bool32 set_mario_wall(struct MarioState *m, struct Surface *wall);
Bool32 set_mario_ceil(struct MarioState *m, struct Surface *ceil,  f32 ceilHeight);
Bool32 set_mario_floor(struct MarioState *m, struct Surface *floor, f32 floorHeight);
void update_mario_sound_and_camera(struct MarioState *m);
void set_steep_jump_action(struct MarioState *m);
u32 set_mario_action(struct MarioState *m, u32 action, u32 actionArg);
s32 set_jump_from_landing(struct MarioState *m);
s32 set_jumping_action(struct MarioState *m, u32 action, u32 actionArg);
s32 drop_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg);
s32 hurt_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg, s16 hurtCounter);
s32 check_common_action_exits(struct MarioState *m);
s32 check_common_hold_action_exits(struct MarioState *m);
s32 transition_submerged_to_walking(struct MarioState *m);
s32 transition_submerged_to_airborne(struct MarioState *m);
s32 set_water_plunge_action(struct MarioState *m);
s32 execute_mario_action(UNUSED struct Object *obj);
s16 set_custom_mario_animation(struct MarioState *m, s32 targetAnimID);
s16 set_custom_mario_animation_with_accel(struct MarioState *m, s32 targetAnimID, s32 accel);
void init_mario(void);
void init_mario_from_save_file(void);
s32 ground_check_knight(struct MarioState *m);
s32 check_dashboost_inputs(struct MarioState *m);

u16 update_mario_action_timer_pre(struct MarioState *m);
u16 update_mario_action_timer_post(struct MarioState *m);

extern u8 pizza_time;
extern u16 pizza_timer;
extern u8 combo_meter;
extern u8 p_rank_challenge_enabled;
extern u8 p_rank_challenge_prepare;
extern u8 p_rank_stars;
extern u8 p_rank_lap_2;
extern u8 p_rank_success;
extern u8 p_rank_true;
extern u8 magic_mirror_disable;

extern s8 esa_hp;
extern s8 esa_mhp;
extern char * esa_str;

#endif // MARIO_H
