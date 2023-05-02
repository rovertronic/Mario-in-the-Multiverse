#pragma once

void render_fb_effects(void);
void run_motion_blur(s32 goalAmount);
void set_fb_effect_type(u32 type);
void set_motion_blur(s32 goalAmount);
void set_fb_effect_col(u8 r, u8 g, u8 b);
s32 render_fbe_warning(void);
s32 script_check_fbe_warning(UNUSED s16 arg);

enum FBETypes {
    /* blur effects */
    // weird additive-like effect - fb_effect_col should be very low
    FBE_EFFECT_BRIGHTEN   = (1 << 0),
    // multiplies last framebuffer with fb_effect_col,
    // good choice for basic blur if the colors pure white
    FBE_EFFECT_MULT       = (1 << 1),
    
    /* screen effects */
    // monotone, current fb * fb_effect_col
    FBE_EFFECT_MONO       = (1 << 2),
    // monotone, using black and white version of current fb, lerp between white and fb_effect_col
    FBE_EFFECT_MONO_LIGHT = (1 << 3),
    // inverted * fb_effect_col
    FBE_EFFECT_INVERT     = (1 << 4),
};

typedef struct FBEffects {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 type; // FBETypes
} FBEffects;

void render_pause_vibe(void);
