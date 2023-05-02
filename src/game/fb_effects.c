#include <ultra64.h>
#include <PR/gs2dex.h>

#include "types.h"
#include "main.h"
#include "game_init.h"
#include "fb_effects.h"
#include "buffers/framebuffers.h"
#include "buffers/zbuffer.h"
#include "puppyprint.h"
#include "engine/math_util.h"
#include "segment2.h"
#include "print.h"
#include "levels/intro/header.h"


extern u16 sRenderedFramebuffer;
extern u8 gFBE;

s32 sCurBlur = 255;
s32 sGoalBlur = 0;

FBEffects sFBEffects = {
    .r = 255,
    .g = 255,
    .b = 255,
    .a = 255,
    .type = FBE_EFFECT_MULT,
};

#define FUNNY_FBE_COLOR 0xFF00
#define MOTION_BLUR_APP_RATE 8

static u8 checkingFBE = 0;
static u8 checkedFBE = FALSE;
s32 check_fbe(void) {

    if (checkedFBE) return gFBE;
    else if (!checkedFBE && (gIsConsole || gCacheEmulated)) {
        checkedFBE = gFBE = TRUE;
        return TRUE;
    }

    if (checkingFBE == 0) {
        checkingFBE = TRUE;
        gFramebuffers[0][12] = FUNNY_FBE_COLOR;
    } else if (checkingFBE < 3) {
        checkingFBE++;
    } else {
        checkedFBE = TRUE;
        gFBE = gFramebuffers[0][12] != FUNNY_FBE_COLOR;
    }

    return gFBE;
}

void run_motion_blur(s32 goalAmount) {
    sGoalBlur = goalAmount;
}

void set_motion_blur(s32 goalAmount) {
    sGoalBlur = goalAmount;
    sFBEffects.a = CLAMP_U8(goalAmount);
}

void set_fb_effect_type(u32 type) {
    sFBEffects.type = type;
}

void set_fb_effect_col(u8 r, u8 g, u8 b) {
    sFBEffects.r = r;
    sFBEffects.g = g;
    sFBEffects.b = b;
}

void render_tiled_screen_effect(Texture *image, s32 mode, u32 fmt) {
    gDPSetCycleType( gDisplayListHead++, mode);
    if (mode == G_CYC_2CYCLE) {
        gDPSetRenderMode(gDisplayListHead++, G_RM_PASS, G_RM_XLU_SURF2);
    } else {
        gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    const s32 maxTMEM = 32 * 64; // texels
    const s32 tileHeight = maxTMEM / SCREEN_WIDTH;
    const s32 numRows = (SCREEN_HEIGHT / tileHeight);

    for (s32 i = 0; i < numRows; i++) {
        s32 yPos = (i * tileHeight);

        gDPLoadSync(gDisplayListHead++);

        gDPLoadTextureTile(gDisplayListHead++, // pkt
            image, // timg
            fmt, // fmt
            G_IM_SIZ_16b, // siz
            SCREEN_WIDTH, // width
            SCREEN_HEIGHT, // height
            0, // uls
            yPos, // ult
            SCREEN_WIDTH - 1, // lrs
            yPos + tileHeight - 1, // lrt
            0, // pal
            (G_TX_NOMIRROR | G_TX_CLAMP), // cms
            (G_TX_NOMIRROR | G_TX_CLAMP), // cmt
            0, // masks
            0, // maskt
            0, // shifts
            0 // shiftt
        );
        gSPScisTextureRectangle(gDisplayListHead++,
            qs102(0),
            qs102(yPos),
            qs102(SCREEN_WIDTH),
            qs102((yPos + tileHeight)),
            G_TX_RENDERTILE,
            qs105(0),
            qs105(yPos),
            qs510(1),
            qs510(1)
        );
    }
}

void render_motion_blur(void) {
    gDPPipeSync(gDisplayListHead++);
    u16 srcFB = sRenderedFramebuffer; // blur
    u32 fmt = G_IM_FMT_RGBA;
    s32 mode = G_CYC_1CYCLE;

    switch (sFBEffects.type) {
        case FBE_EFFECT_BRIGHTEN:
            gDPSetCombineLERP(gDisplayListHead++,
                1, TEXEL0, ENVIRONMENT, TEXEL0,
                0, 0, 0, ENVIRONMENT,
                1, TEXEL0, ENVIRONMENT, TEXEL0,
                0, 0, 0, ENVIRONMENT
            );
            gDPSetEnvColor(gDisplayListHead++, sFBEffects.r, sFBEffects.g, sFBEffects.b, sFBEffects.a);
            break;
        case FBE_EFFECT_MULT:
            gDPSetCombineLERP(gDisplayListHead++,
                TEXEL0, 0, ENVIRONMENT, 0,
                0, 0, 0, ENVIRONMENT,
                TEXEL0, 0, ENVIRONMENT, 0,
                0, 0, 0, ENVIRONMENT
            );
            gDPSetEnvColor(gDisplayListHead++, sFBEffects.r, sFBEffects.g, sFBEffects.b, sFBEffects.a);
            break;
        case FBE_EFFECT_MONO:
            gDPSetCombineLERP(gDisplayListHead++,
                ENVIRONMENT, 0, TEXEL0, 0,
                0, 0, 0, ENVIRONMENT,
                ENVIRONMENT, 0, TEXEL0, 0,
                0, 0, 0, ENVIRONMENT
            );
            gDPSetEnvColor(gDisplayListHead++, sFBEffects.r, sFBEffects.g, sFBEffects.b, sFBEffects.a);
            srcFB = sRenderingFramebuffer;
            fmt = G_IM_FMT_IA;
            break;
        case FBE_EFFECT_MONO_LIGHT:
            gDPSetCombineLERP(gDisplayListHead++,
                1, ENVIRONMENT, TEXEL0, ENVIRONMENT,
                0, 0, 0, ENVIRONMENT,
                1, ENVIRONMENT, TEXEL0, ENVIRONMENT,
                0, 0, 0, ENVIRONMENT
            );

            gDPSetEnvColor(gDisplayListHead++, sFBEffects.r, sFBEffects.g, sFBEffects.b, sFBEffects.a);
            srcFB = sRenderingFramebuffer;
            fmt = G_IM_FMT_IA;
            break;
        case FBE_EFFECT_INVERT:
            gDPSetCombineLERP(gDisplayListHead++,
                1, TEXEL0, ENVIRONMENT, 0,
                0, 0, 0, ENVIRONMENT,
                1, TEXEL0, ENVIRONMENT, 0,
                0, 0, 0, ENVIRONMENT
            );

            gDPSetEnvColor(gDisplayListHead++, sFBEffects.r, sFBEffects.g, sFBEffects.b, sFBEffects.a);
            srcFB = sRenderingFramebuffer;
            fmt = G_IM_FMT_RGBA;
            break;
        default: // lmao broken weird something have fun
            gDPSetCombineLERP(gDisplayListHead++,
                ENVIRONMENT, 0, TEXEL0_ALPHA, 0,
                ENVIRONMENT, 0, TEXEL0, TEXEL0,
                TEXEL1, 0, COMBINED_ALPHA, COMBINED,
                0, 0, 0, ENVIRONMENT
            );

            gDPSetEnvColor(gDisplayListHead++, sFBEffects.r, sFBEffects.g, sFBEffects.b, sFBEffects.a);
            srcFB = sRenderingFramebuffer;
            mode = G_CYC_2CYCLE;
            fmt = G_IM_FMT_IA;
            break;
    }

    gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
    gDPSetColorDither(gDisplayListHead++, G_CD_NOISE);
    gDPSetAlphaDither(gDisplayListHead++, G_AD_NOISE);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);

    if (gFBE) {
        render_tiled_screen_effect((u8 *)gFramebuffers[srcFB], mode, fmt);
    } /* else { // MITM potential later use
        u8 *emu_tex = segmented_to_virtual(youre_emu);
        render_tiled_screen_effect(emu_tex, G_CYC_1CYCLE, G_IM_FMT_RGBA);
    } */

    gDPSetColorDither(gDisplayListHead++, G_CD_MAGICSQ);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
}

static s32 sVerifiedFBE = FALSE; 

void render_fb_effects(void) {
    check_fbe();
    if (!checkedFBE) return;

    if (sGoalBlur > 200) {
        sFBEffects.a = approach_s16_asymptotic(sFBEffects.a, sGoalBlur, 18);
    } else {
        sFBEffects.a = approach_s32_symmetric(sFBEffects.a, sGoalBlur, MOTION_BLUR_APP_RATE);
    }
    
    if (sFBEffects.a > 0) {
        render_motion_blur();
    }
    sGoalBlur = 0;
    if (!sVerifiedFBE) {
        render_fbe_warning();
    }
}

s32 render_fbe_warning(void) {
    if (gFBE || !checkedFBE) return FALSE;

    f32 s = sins(gGlobalTimer*DEGREES(4));
    s = 1.0f - sqr(sqr(s));
    s32 bloob = roundf(120 - ((s / 2.0f) * 120.0f));

    gDPSetEnvColor(gDisplayListHead++, bloob, 0, 0, 255);

    gDPSetCombineLERP(gDisplayListHead++,
        NOISE, 0, ENVIRONMENT, TEXEL0,
        0, 0, 0, 1,
        NOISE, 0, ENVIRONMENT, TEXEL0,
        0, 0, 0, 1
    );

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
    gDPSetColorDither(gDisplayListHead++, G_CD_NOISE);
    gDPSetAlphaDither(gDisplayListHead++, G_AD_NOISE);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    /* // MITM potential later use
    u8 *emu_tex = segmented_to_virtual(fbe_warning);
    render_tiled_screen_effect(emu_tex, G_CYC_1CYCLE, G_IM_FMT_RGBA);
    */

    gDPSetColorDither(gDisplayListHead++, G_CD_MAGICSQ);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    return FALSE;
}

void render_pause_vibe(void) {
    f32 s = remap(sins(gGlobalTimer*DEGREES(4)), -1, 1, 5, 15);
    s32 bloob = roundf(s);

    gDPSetEnvColor(gDisplayListHead++, bloob, bloob, bloob, 255);

    gDPSetCombineLERP(gDisplayListHead++,
        NOISE, 0, ENVIRONMENT, TEXEL0,
        0, 0, 0, 1,
        NOISE, 0, ENVIRONMENT, TEXEL0,
        0, 0, 0, 1
    );

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
    gDPSetColorDither(gDisplayListHead++, G_CD_NOISE);
    gDPSetAlphaDither(gDisplayListHead++, G_AD_NOISE);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    /* // MITM probably no use
    u8 *pause_tex = segmented_to_virtual(pause_screen_img);
    render_tiled_screen_effect(pause_tex, G_CYC_1CYCLE, G_IM_FMT_RGBA);
    */

    gDPSetColorDither(gDisplayListHead++, G_CD_MAGICSQ);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);

    print_set_envcolour(0xFF, 0xFF, 0xFF, 0xFF);
    print_small_text(10, 10, gConfig.widescreen ? "L: toggle aspect ratio (16:9)" : "L: toggle aspect ratio (4:3)", PRINT_TEXT_ALIGN_LEFT, PRINT_ALL, FONT_DEFAULT);
    print_small_text(10, 36, 
    "Controls:\n"
    "R: recenter camera\n"
    "B (while groundponding): groundpound dive\n"
    "A (while diving): air rollout\n"
    "A (after groundpound): groundpound jump"
    "",
    PRINT_TEXT_ALIGN_LEFT, PRINT_ALL, FONT_DEFAULT);
}

s32 script_check_fbe_warning(UNUSED s16 arg) {
    if (!checkedFBE) return FALSE;
    if (gFBE) {
        sVerifiedFBE = TRUE;
        return TRUE;
    }
    if (
        (gPlayer1Controller->buttonDown & (Z_TRIG | A_BUTTON | START_BUTTON)) == (Z_TRIG | A_BUTTON | START_BUTTON) &&
        (gPlayer1Controller->buttonPressed & (Z_TRIG | A_BUTTON | START_BUTTON))
    ) {
        sVerifiedFBE = TRUE;
        return TRUE;
    }

    return FALSE;
}
