#ifndef LERP_H
#define LERP_H

s32 approach_angle_lerp(s32 current, s32 target);
f32 approach_pos_lerp(f32 current, f32 target);
void warp_node(struct Object *node);
void interpolate_node(struct Object *node);
f32 lerp_menu(f32 value,int stack_index);
f32 lerp_menu_lotolerance(f32 value,int stack_index);

extern u8 lerp_overshot_flag;

enum {
    LMENU_ABILITY_HUD,
    LMENU_HUD_ALPHA=20,
    LMENU_TITLE_CARD,
    LMENU_DIALOG_OPEN,
    LMENU_DIALOG_SCALE,
    LMENU_TRANSITION,
    LMENU_PAUSE,
    LERPM_FOV,
    LMENU_COUNT,
};

#endif // LERP_H
