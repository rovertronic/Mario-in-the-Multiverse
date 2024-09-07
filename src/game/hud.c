#include <PR/ultratypes.h>

#include "sm64.h"
#include "actors/common1.h"
#include "gfx_dimensions.h"
#include "game_init.h"
#include "level_update.h"
#include "camera.h"
#include "print.h"
#include "ingame_menu.h"
#include "hud.h"
#include "segment2.h"
#include "area.h"
#include "save_file.h"
#include "print.h"
#include "engine/surface_load.h"
#include "engine/math_util.h"
#include "puppycam2.h"
#include "puppyprint.h"
#include "actors/group0.h"
#include "cutscene_manager.h"
#include "mario.h"
#include "dream_comet.h"
//--E
#include "levels/e/header.h"

#include "config.h"
#include "ability.h"

/* @file hud.c
 * This file implements HUD rendering and power meter animations.
 * That includes stars, lives, coins, camera status, power meter, timer
 * cannon reticle, and the unused keys.
 **/

#ifdef BREATH_METER
#define HUD_BREATH_METER_X         40
#define HUD_BREATH_METER_Y         255 // This is used for alpha instead of y position.
#define HUD_BREATH_METER_HIDDEN_Y  0
#endif

// ------------- FPS COUNTER ---------------
// To use it, call print_fps(x,y); every frame.
#define FRAMETIME_COUNT 30

OSTime frameTimes[FRAMETIME_COUNT];
u8 curFrameTimeIndex = 0;

#include "PR/os_convert.h"

#ifdef USE_PROFILER
float profiler_get_fps();
#else
// Call once per frame
f32 calculate_and_update_fps() {
    OSTime newTime = osGetTime();
    OSTime oldTime = frameTimes[curFrameTimeIndex];
    frameTimes[curFrameTimeIndex] = newTime;

    curFrameTimeIndex++;
    if (curFrameTimeIndex >= FRAMETIME_COUNT) {
        curFrameTimeIndex = 0;
    }
    return ((f32)FRAMETIME_COUNT * 1000000.0f) / (s32)OS_CYCLES_TO_USEC(newTime - oldTime);
}
#endif

void print_fps(s32 x, s32 y) {
#ifdef USE_PROFILER
    f32 fps = profiler_get_fps();
#else
    f32 fps = calculate_and_update_fps();
#endif
    char text[14];

    sprintf(text, "FPS %2.2f", fps);
#ifdef PUPPYPRINT
    print_small_text(x, y, text, PRINT_TEXT_ALIGN_LEFT, PRINT_ALL, FONT_OUTLINE);
#else
    print_text(x, y, text);
#endif
}

// ------------ END OF FPS COUNER -----------------

struct PowerMeterHUD {
    s8 animation;
    s16 x;
    s16 y;
};

struct CameraHUD {
    s16 status;
};

// Stores health segmented value defined by numHealthWedges
// When the HUD is rendered this value is 8, full health.
static s16 sPowerMeterStoredHealth;

static struct PowerMeterHUD sPowerMeterHUD = {
    POWER_METER_HIDDEN,
    HUD_POWER_METER_X,
    HUD_POWER_METER_HIDDEN_Y,
};

// Power Meter timer that keeps counting when it's visible.
// Gets reset when the health is filled and stops counting
// when the power meter is hidden.
s32 sPowerMeterVisibleTimer = 0;

#ifdef BREATH_METER
static s16 sBreathMeterStoredValue;
static struct PowerMeterHUD sBreathMeterHUD = {
    BREATH_METER_HIDDEN,
    HUD_BREATH_METER_X,
    HUD_BREATH_METER_HIDDEN_Y, // Alpha
};
s32 sBreathMeterVisibleTimer = 0;
#endif

static s16 sAbilityMeterStoredValue;
static struct PowerMeterHUD sAbilityMeterHUD = {
    ABILITY_METER_HIDDEN,
    METER_STYLE_GENERIC, // Meter style
    0, // Alpha
};
s32 sAbilityMeterVisibleTimer = 0;

s16 gMarxHudHealth = 0;

static struct CameraHUD sCameraHUD = { CAM_STATUS_NONE };

/**
 * Renders a rgba16 16x16 glyph texture from a table list.
 */
void render_hud_tex_lut(s32 x, s32 y, Texture *texture) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture);
    gSPDisplayList(gDisplayListHead++, &dl_hud_img_load_tex_block);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + 15) << 2, (y + 15) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
}

/**
 * Renders a rgba16 8x8 glyph texture from a table list.
 */
void render_hud_small_tex_lut(s32 x, s32 y, Texture *texture) {
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0,
                G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);
    gDPTileSync(gDisplayListHead++);
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 0, G_TX_RENDERTILE, 0,
                G_TX_CLAMP, 3, G_TX_NOLOD, G_TX_CLAMP, 3, G_TX_NOLOD);
    gDPSetTileSize(gDisplayListHead++, G_TX_RENDERTILE, 0, 0, (8 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC);
    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture);
    gDPLoadSync(gDisplayListHead++);
    gDPLoadBlock(gDisplayListHead++, G_TX_LOADTILE, 0, 0, 8 * 8 - 1, CALC_DXT(8, G_IM_SIZ_16b_BYTES));
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + 7) << 2, (y + 7) << 2, G_TX_RENDERTILE,
                        0, 0, 4 << 10, 1 << 10);
}

/**
 * Renders power meter health segment texture using a table list.
 */
void render_power_meter_health_segment(s16 numHealthWedges) {
    Texture *(*healthLUT)[] = segmented_to_virtual(&power_meter_health_segments_lut);

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1,
                       (*healthLUT)[numHealthWedges - 1]);
    gDPLoadSync(gDisplayListHead++);
    gDPLoadBlock(gDisplayListHead++, G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES));
    gSP1Triangle(gDisplayListHead++, 0, 1, 2, 0);
    gSP1Triangle(gDisplayListHead++, 0, 2, 3, 0);
}

/**
 * Renders power meter display lists.
 * That includes the "POWER" base and the colored health segment textures.
 */
void render_dl_power_meter(s16 numHealthWedges) {
    Mtx *mtx = alloc_display_list(sizeof(Mtx));

    if (mtx == NULL) {
        return;
    }

    guTranslate(mtx, (f32) sPowerMeterHUD.x, (f32) sPowerMeterHUD.y, 0);

    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx++),
              G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList(gDisplayListHead++, &dl_power_meter_base);

    if (numHealthWedges != 0) {
        gSPDisplayList(gDisplayListHead++, &dl_power_meter_health_segments_begin);
        render_power_meter_health_segment(numHealthWedges);
        gSPDisplayList(gDisplayListHead++, &dl_power_meter_health_segments_end);
    }

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

/**
 * Power meter animation called when there's less than 8 health segments
 * Checks its timer to later change into deemphasizing mode.
 */
void animate_power_meter_emphasized(void) {
    s16 hudDisplayFlags = gHudDisplay.flags;

    if (!(hudDisplayFlags & HUD_DISPLAY_FLAG_EMPHASIZE_POWER)) {
        if (sPowerMeterVisibleTimer == 45.0f) {
            sPowerMeterHUD.animation = POWER_METER_DEEMPHASIZING;
        }
    } else {
        sPowerMeterVisibleTimer = 0;
    }
}

/**
 * Power meter animation called after emphasized mode.
 * Moves power meter y pos speed until it's at 200 to be visible.
 */
static void animate_power_meter_deemphasizing(void) {
    s16 speed = 5;

    if (sPowerMeterHUD.y > HUD_POWER_METER_Y - 20) speed = 3;
    if (sPowerMeterHUD.y > HUD_POWER_METER_Y - 10) speed = 2;
    if (sPowerMeterHUD.y > HUD_POWER_METER_Y -  5) speed = 1;

    sPowerMeterHUD.y += speed;

    if (sPowerMeterHUD.y > HUD_POWER_METER_Y) {
        sPowerMeterHUD.y = HUD_POWER_METER_Y;
        sPowerMeterHUD.animation = POWER_METER_VISIBLE;
    }
}

/**
 * Power meter animation called when there's 8 health segments.
 * Moves power meter y pos quickly until it's at 301 to be hidden.
 */
static void animate_power_meter_hiding(void) {
    sPowerMeterHUD.y += 20;
    if (sPowerMeterHUD.y > HUD_POWER_METER_HIDDEN_Y) {
        sPowerMeterHUD.animation = POWER_METER_HIDDEN;
        sPowerMeterVisibleTimer = 0;
    }
}

/**
 * Handles power meter actions depending of the health segments values.
 */
void handle_power_meter_actions(s16 numHealthWedges) {
    // Show power meter if health is not full, less than 8
    if (numHealthWedges < 8 && sPowerMeterStoredHealth == 8
        && sPowerMeterHUD.animation == POWER_METER_HIDDEN) {
        sPowerMeterHUD.animation = POWER_METER_EMPHASIZED;
        sPowerMeterHUD.y = HUD_POWER_METER_EMPHASIZED_Y;
    }

    // Show power meter if health is full, has 8
    if (numHealthWedges == 8 && sPowerMeterStoredHealth == 7) {
        sPowerMeterVisibleTimer = 0;
    }

    // After health is full, hide power meter
    if (numHealthWedges == 8 && sPowerMeterVisibleTimer > 45.0f) {
        sPowerMeterHUD.animation = POWER_METER_HIDING;
    }

    // Update to match health value
    sPowerMeterStoredHealth = numHealthWedges;

#ifndef BREATH_METER
    // If Mario is swimming, keep power meter visible
    if (gPlayerCameraState->action & ACT_FLAG_SWIMMING) {
        if (sPowerMeterHUD.animation == POWER_METER_HIDDEN
            || sPowerMeterHUD.animation == POWER_METER_EMPHASIZED) {
            sPowerMeterHUD.animation = POWER_METER_DEEMPHASIZING;
            sPowerMeterHUD.y = HUD_POWER_METER_EMPHASIZED_Y;
        }
        sPowerMeterVisibleTimer = 0;
    }
#endif
}

/**
 * Renders the power meter that shows when Mario is in underwater
 * or has taken damage and has less than 8 health segments.
 * And calls a power meter animation function depending of the value defined.
 */
void render_hud_power_meter(void) {
    s16 shownHealthWedges = gHudDisplay.wedges;
    if (sPowerMeterHUD.animation != POWER_METER_HIDING) handle_power_meter_actions(shownHealthWedges);
    if (sPowerMeterHUD.animation == POWER_METER_HIDDEN) return;
    switch (sPowerMeterHUD.animation) {
        case POWER_METER_EMPHASIZED:    animate_power_meter_emphasized();    break;
        case POWER_METER_DEEMPHASIZING: animate_power_meter_deemphasizing(); break;
        case POWER_METER_HIDING:        animate_power_meter_hiding();        break;
        default:                                                             break;
    }
    render_dl_power_meter(shownHealthWedges);
    sPowerMeterVisibleTimer++;
}

#ifdef BREATH_METER
/**
 * Renders breath meter health segment texture using a table list.
 */
void render_breath_meter_segment(s16 numBreathWedges) {
    Texture *(*breathLUT)[];
    breathLUT = segmented_to_virtual(&breath_meter_segments_lut);
    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, (*breathLUT)[numBreathWedges - 1]);
    gDPLoadSync(gDisplayListHead++);
    gDPLoadBlock(gDisplayListHead++, G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES));
    gSP1Triangle(gDisplayListHead++, 0, 1, 2, 0);
    gSP1Triangle(gDisplayListHead++, 0, 2, 3, 0);
}

/**
 * Renders breath meter display lists.
 * That includes the base and the colored segment textures.
 */
void render_dl_breath_meter(s16 numBreathWedges) {
    Mtx *mtx = alloc_display_list(sizeof(Mtx));

    if (mtx == NULL) {
        return;
    }

    guTranslate(mtx, (f32) sBreathMeterHUD.x, (f32) sBreathMeterHUD.y, 0);
    gSPMatrix(      gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx++),
                    G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList( gDisplayListHead++, &dl_breath_meter_base);
    if (numBreathWedges != 0) {
        gSPDisplayList(gDisplayListHead++, &dl_breath_meter_health_segments_begin);
        render_breath_meter_segment(numBreathWedges);
        gSPDisplayList(gDisplayListHead++, &dl_breath_meter_health_segments_end);
    }
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

/**
 * Breath meter animation called after emphasized mode.
 * Moves breath meter y pos speed until it's visible.
 */
static void animate_breath_meter_sliding_in(void) {
    approach_s16_symmetric_bool(&sBreathMeterHUD.y, HUD_BREATH_METER_Y, 20);
    if (sBreathMeterHUD.y         == HUD_BREATH_METER_Y) {
        sBreathMeterHUD.animation = BREATH_METER_VISIBLE;
    }
}

/**
 * Breath meter animation called when there's 8 health segments.
 * Moves breath meter y pos quickly until it's hidden.
 */
static void animate_breath_meter_sliding_out(void) {
    approach_s16_symmetric_bool(&sBreathMeterHUD.y, HUD_BREATH_METER_HIDDEN_Y, 20);
    if (sBreathMeterHUD.y         == HUD_BREATH_METER_HIDDEN_Y) {
        sBreathMeterHUD.animation = BREATH_METER_HIDDEN;
    }
}

/**
 * Handles breath meter actions depending of the health segments values.
 */
void handle_breath_meter_actions(s16 numBreathWedges) {
    // Show breath meter if health is not full, less than 8
    if ((numBreathWedges < 8) && (sBreathMeterStoredValue == 8) && sBreathMeterHUD.animation == BREATH_METER_HIDDEN) {
        sBreathMeterHUD.animation = BREATH_METER_SHOWING;
        // sBreathMeterHUD.y         = HUD_BREATH_METER_Y;
    }
    // Show breath meter if breath is full, has 8
    if ((numBreathWedges == 8) && (sBreathMeterStoredValue  == 7)) sBreathMeterVisibleTimer  = 0;
    // After breath is full, hide breath meter
    if ((numBreathWedges == 8) && (sBreathMeterVisibleTimer > 45)) sBreathMeterHUD.animation = BREATH_METER_HIDING;
    // Update to match breath value
    sBreathMeterStoredValue = numBreathWedges;
    // If Mario is swimming, keep breath meter visible
    if (gPlayerCameraState->action & ACT_FLAG_SWIMMING) {
        if (sBreathMeterHUD.animation == BREATH_METER_HIDDEN) {
            sBreathMeterHUD.animation = BREATH_METER_SHOWING;
        }
        sBreathMeterVisibleTimer = 0;
    }
}

void render_hud_breath_meter(void) {
    s16 shownBreathAmount = gHudDisplay.breath;
    if (sBreathMeterHUD.animation != BREATH_METER_HIDING) handle_breath_meter_actions(shownBreathAmount);
    if (sBreathMeterHUD.animation == BREATH_METER_HIDDEN) return;
    switch (sBreathMeterHUD.animation) {
        case BREATH_METER_SHOWING:       animate_breath_meter_sliding_in();  break;
        case BREATH_METER_HIDING:        animate_breath_meter_sliding_out(); break;
        default:                                                             break;
    }
    sBreathMeterVisibleTimer++;
}
#endif

static void animate_ability_meter_sliding_in(void) {
    approach_s16_symmetric_bool(&sAbilityMeterHUD.y, 255, 20);
    if (sAbilityMeterHUD.y         == 255) {
        sAbilityMeterHUD.animation = ABILITY_METER_VISIBLE;
    }
}

static void animate_ability_meter_sliding_out(void) {
    approach_s16_symmetric_bool(&sAbilityMeterHUD.y, 0, 20);
    if (sAbilityMeterHUD.y         == 0) {
        sAbilityMeterHUD.animation = ABILITY_METER_HIDDEN;
    }
}

void handle_ability_meter_actions(s16 numAbilityWedges, s16 style) {
    if (numAbilityWedges > -1 && sAbilityMeterHUD.animation == ABILITY_METER_HIDDEN) {
        sAbilityMeterHUD.animation = ABILITY_METER_SHOWING;
    }
    if (numAbilityWedges < 0) {
        sAbilityMeterHUD.animation = ABILITY_METER_HIDING;
    }
    if (sAbilityMeterHUD.animation != ABILITY_METER_HIDDEN && sAbilityMeterHUD.animation != ABILITY_METER_HIDING) {
        
        sAbilityMeterStoredValue = numAbilityWedges;
        sAbilityMeterHUD.x = style;
    }
}

void render_hud_ability_meter(void) {
    s16 shownAbilityAmount = gHudDisplay.abilityMeter;
    s16 shownAbilityStyle = gHudDisplay.abilityMeterStyle;
    if (sAbilityMeterHUD.animation != ABILITY_METER_HIDING) handle_ability_meter_actions(shownAbilityAmount, shownAbilityStyle);
    if (sAbilityMeterHUD.animation == ABILITY_METER_HIDDEN) return;
    switch (sAbilityMeterHUD.animation) {
        case ABILITY_METER_SHOWING:       animate_ability_meter_sliding_in();  break;
        case ABILITY_METER_HIDING:        animate_ability_meter_sliding_out(); break;
        default:                                                             break;
    }
    sAbilityMeterVisibleTimer++;
}


/**
 * Renders the amount of lives Mario has.
 */
void render_hud_mario_lives(void) {
    print_text(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(22), HUD_TOP_Y, ","); // 'Mario Head' glyph
    print_text(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(38), HUD_TOP_Y, "*"); // 'X' glyph
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(54), HUD_TOP_Y, "%d", gHudDisplay.lives);
}

#ifdef VANILLA_STYLE_CUSTOM_DEBUG
void render_debug_mode(void) {
    print_text(180, 40, "DEBUG MODE");
    print_text_fmt_int(5, 20, "Z %d", gMarioState->pos[2]);
    print_text_fmt_int(5, 40, "Y %d", gMarioState->pos[1]);
    print_text_fmt_int(5, 60, "X %d", gMarioState->pos[0]);
    print_text_fmt_int(10, 100, "SPD %d", (s32) gMarioState->forwardVel);
    print_text_fmt_int(10, 120, "ANG 0*%04x", (u16) gMarioState->faceAngle[1]);
    print_fps(10,80);
}
#endif

/**
 * Renders the amount of coins collected.
 */
void render_hud_coins(void) {
    print_text(HUD_COINS_X, HUD_TOP_Y, "$"); // 'Coin' glyph
    print_text((HUD_COINS_X + 16), HUD_TOP_Y, "*"); // 'X' glyph
    print_text_fmt_int((HUD_COINS_X + 30), HUD_TOP_Y, "%d", gHudDisplay.coins);
}

/**
 * Renders the amount of stars collected.
 * Disables "X" glyph when Mario has 100 stars or more.
 */
void render_hud_stars(void) {
    if (gHudFlash == HUD_FLASH_STARS && gGlobalTimer & 0x8) return;
    s8 showX = (gHudDisplay.stars < 100);
    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_STARS_X), HUD_TOP_Y, "^"); // 'Star' glyph
    if (showX) print_text((GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_STARS_X) + 16), HUD_TOP_Y, "*"); // 'X' glyph
    print_text_fmt_int((showX * 14) + GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_STARS_X - 16),
                       HUD_TOP_Y, "%d", gHudDisplay.stars);
}

/**
 * Unused function that renders the amount of keys collected.
 * Leftover function from the beta version of the game.
 */
void render_hud_keys(void) {
    s16 i;

    for (i = 0; i < gHudDisplay.keys; i++) {
        print_text((i * 16) + 220, 142, "|"); // unused glyph - beta key
    }
}

/**
 * Renders the timer when Mario start sliding in PSS.
 */
void render_hud_timer(void) {
    Texture *(*hudLUT)[58] = segmented_to_virtual(&main_hud_lut);
    u16 timerValFrames = gHudDisplay.timer;
    u16 timerMins = timerValFrames / (30 * 60);
    u16 timerSecs = (timerValFrames - (timerMins * 1800)) / 30;
    u16 timerFracSecs = ((timerValFrames - (timerMins * 1800) - (timerSecs * 30)) & 0xFFFF) / 3;

#if MULTILANG
    switch (eu_get_language()) {
        case LANGUAGE_ENGLISH: print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(150), 185,  "TIME"); break;
        case LANGUAGE_FRENCH:  print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(155), 185, "TEMPS"); break;
        case LANGUAGE_GERMAN:  print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(150), 185,  "ZEIT"); break;
    }
#else
    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(150), 185, "TIME");
#endif

    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(91), 185, "%0d", timerMins);
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(71), 185, "%02d", timerSecs);
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(37), 185, "%d", timerFracSecs);

    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    render_hud_tex_lut(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(81), 32, (*hudLUT)[GLYPH_APOSTROPHE]);
    render_hud_tex_lut(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(46), 32, (*hudLUT)[GLYPH_DOUBLE_QUOTE]);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}

/**
 * Sets HUD status camera value depending of the actions
 * defined in update_camera_status.
 */
void set_hud_camera_status(s16 status) {
    sCameraHUD.status = status;
}

/**
 * Renders camera HUD glyphs using a table list, depending of
 * the camera status called, a defined glyph is rendered.
 */
void render_hud_camera_status(s32 x, s32 y) {//--E
    Texture *(*cameraLUT)[6] = segmented_to_virtual(&main_hud_camera_lut);

    if (sCameraHUD.status == CAM_STATUS_NONE) {
        return;
    }

    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    render_hud_tex_lut(x, y, (*cameraLUT)[GLYPH_CAM_CAMERA]);

    switch (sCameraHUD.status & CAM_STATUS_MODE_GROUP) {
        case CAM_STATUS_MARIO:
            render_hud_tex_lut(x + 16, y, (*cameraLUT)[GLYPH_CAM_MARIO_HEAD]);
            break;
        case CAM_STATUS_LAKITU:
            render_hud_tex_lut(x + 16, y, (*cameraLUT)[GLYPH_CAM_LAKITU_HEAD]);
            break;
        case CAM_STATUS_FIXED:
            render_hud_tex_lut(x + 16, y, (*cameraLUT)[GLYPH_CAM_FIXED]);
            break;
            //--E C
        case CAM_STATUS_AIM:
            render_hud_tex_lut(x + 16, y, (*cameraLUT)[6]);
            if (using_ability(ABILITY_E_SHOTGUN)&&(gE_ShotgunFlags & E_SGF_AIM_FIRE)) {
                gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
                gSPDisplayList(gDisplayListHead++, dl_e__crosshair);
                gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
            }
            break;
    }

    switch (sCameraHUD.status & CAM_STATUS_C_MODE_GROUP) {
        case CAM_STATUS_C_DOWN:
            render_hud_small_tex_lut(x + 4, y + 16, (*cameraLUT)[GLYPH_CAM_ARROW_DOWN]);
            break;
        case CAM_STATUS_C_UP:
            render_hud_small_tex_lut(x + 4, y - 8, (*cameraLUT)[GLYPH_CAM_ARROW_UP]);
            break;
    }

    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}

u8 hudbar_star[] = {GLYPH_STAR, DIALOG_CHAR_SPACE, 0, 0, 0, DIALOG_CHAR_TERMINATOR};
u8 hudbar_coin[] = {GLYPH_COIN, DIALOG_CHAR_SPACE, 0, 0, 0, DIALOG_CHAR_TERMINATOR};
u8 hudbar_dc[] = {GLYPH_DC, DIALOG_CHAR_SPACE, 0, 0, 0, DIALOG_CHAR_TERMINATOR};

//Warning: no automatic terminator
void int_to_str_000(s32 num, u8 *dst) {
    s32 digit[3];

    s8 pos = 0;

    if (num > 999) {
        dst[0] = 0x00;
        dst[1] = DIALOG_CHAR_TERMINATOR;
        return;
    }

    digit[0] = (num / 100);
    digit[1] = ((num - (digit[0] * 100)) / 10);
    digit[2] = ((num - (digit[0] * 100)) - (digit[1] * 10));

    if (num < 10) {
        dst[0] = 0;
        dst[1] = 0;
        dst[2] = digit[2];
    } else if (num < 100) {
        dst[0] = 0;
        dst[1] = digit[1];
        dst[2] = digit[2];
    } else {
        dst[0] = digit[0];
        dst[1] = digit[1];
        dst[2] = digit[2];
    }
    return;
}

Gfx *meter_wedges_dl_table[] = {
    &meter_1_meter_1_mesh,
    &meter_1_meter_1_mesh,
    &meter_2_meter_2_mesh,
    &meter_3_meter_3_mesh,
    &meter_4_meter_4_mesh,
    &meter_5_meter_5_mesh,
    &meter_6_meter_6_mesh,
    &meter_7_meter_7_mesh,
    &meter_8_meter_8_mesh,
};

u8 meter_style_color_table[METER_STYLE_COUNT][9][3] = {
    {   // Generic
        {255, 0, 0},     // 1
        {255, 0, 0},     // 2
        {255, 50, 0},    // 3
        {255, 255, 0},   // 4
        {255, 255, 0},   // 5
        {0, 255, 0},     // 6
        {0, 255, 0},     // 7
        {0, 200, 255},   // 8
    },
    {   // HP
        {255, 0, 0},     // 1
        {255, 0, 0},     // 2
        {255, 50, 0},    // 3
        {255, 255, 0},   // 4
        {255, 255, 0},   // 5
        {0, 255, 0},     // 6
        {0, 255, 0},     // 7
        {0, 200, 255},   // 8
    },
    {   // Breath
        {255, 0, 0},     // 1
        {255, 0, 0},     // 2
        {255, 50, 0},    // 3
        {255, 255, 0},   // 4
        {255, 255, 0},   // 5
        {0, 255, 0},     // 6
        {0, 255, 0},     // 7
        {0, 200, 255},   // 8
    },
    {   // Aku Aku Mask
        {255, 255, 0},   // 1
        {255, 255, 0},   // 2
        {255, 255, 0},   // 3
        {255, 255, 0},   // 4
        {255, 255, 0},   // 5
        {255, 255, 0},   // 6
        {255, 255, 0},   // 7
        {255, 255, 0},   // 8
    },
    {   // Phasewalk
        {0, 200, 255},   // 1
        {0, 200, 255},   // 2
        {0, 200, 255},   // 3
        {0, 200, 255},   // 4
        {0, 200, 255},   // 5
        {0, 200, 255},   // 6
        {0, 200, 255},   // 7
        {0, 200, 255},   // 8
    },
    {   // Phasewalk (Superjump)
        {255, 255, 0},   // 1
        {255, 255, 0},   // 2
        {255, 255, 0},   // 3
        {255, 255, 0},   // 4
        {255, 255, 0},   // 5
        {255, 255, 0},   // 6
        {255, 255, 0},   // 7
        {255, 255, 0},   // 8
    },
    {   // Phasewalk (Recharge)
        {0, 100, 127},   // 1
        {0, 100, 127},   // 2
        {0, 100, 127},   // 3
        {0, 100, 127},   // 4
        {0, 100, 127},   // 5
        {0, 100, 127},   // 6
        {0, 100, 127},   // 7
        {0, 100, 127},   // 8
    },
    {   // Rocket
        {255, 156, 0},   // 1
        {255, 156, 0},   // 2
        {255, 156, 0},   // 3
        {255, 156, 0},   // 4
        {255, 156, 0},   // 5
        {255, 156, 0},   // 6
        {255, 156, 0},   // 7
        {255, 156, 0},   // 8
    },
    {   // Chronos
        {240, 19, 226},  // 1
        {208, 47, 230},  // 2
        {176, 74, 234},  // 3
        {144, 102, 237}, // 4
        {111, 130, 241}, // 5
        {80, 158, 245},  // 6
        {48, 185, 249},  // 7
        {0, 200, 255},   // 8
    },
    {   // Dash Booster
        {255, 74,  32},    // 1
        {255, 74,  32},    // 2
        {255, 74,  32},    // 3
        {255, 159, 76},    // 4
        {255, 159, 76},    // 5
        {255, 255, 255},   // 6
        {255, 255, 255},   // 7
        {255, 255, 255},   // 8
    },
    {   // Aku Aku Mask Recharge
        {100, 100, 0},   // 1
        {100, 100, 0},   // 2
        {100, 100, 0},   // 3
        {100, 100, 0},   // 4
        {100, 100, 0},   // 5
        {100, 100, 0},   // 6
        {100, 100, 0},   // 7
        {100, 100, 0},   // 8
    },
};

Gfx *meter_style_icon_dl_table[] = {
    NULL,
    &meter_hp_meter_hp_mesh,
    &meter_breath_meter_breath_mesh,
    &meter_aku_meter_aku_mesh,
    &meter_phase_meter_phase_mesh,
    &meter_phase_meter_phase_mesh,
    &meter_phase_meter_phase_mesh,
    &meter_rocket_meter_rocket_mesh,
    &meter_chronos_meter_chronos_mesh,
    &meter_booster_meter_booster_mesh,
    &meter_aku_meter_aku_mesh,
};

void render_meter(f32 x, f32 y, s32 meterStyle, s16 wedges, u8 a) {

    if (gHudDisplay.flags & HUD_DISPLAY_FLAG_TIMER) {
        // If timer is visible, move meters down
        y -= 24.0f;
    }

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, a);
    create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);

    gSPDisplayList(gDisplayListHead++, &meter_bg_meter_bg_mesh);

    if (meter_style_icon_dl_table[meterStyle] != NULL) {
        gSPDisplayList(gDisplayListHead++, meter_style_icon_dl_table[meterStyle]);
    }

    if (wedges > 0) {
        gDPSetEnvColor(gDisplayListHead++, meter_style_color_table[meterStyle][wedges - 1][0],
        meter_style_color_table[meterStyle][wedges - 1][1], meter_style_color_table[meterStyle][wedges - 1][2], a);
        gSPDisplayList(gDisplayListHead++, meter_wedges_dl_table[wedges]);
    }

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void render_esa_health(void) {
    if (esa_mhp != -1) {
        f32 poop_bar = ((f32)(esa_hp)/(f32)(esa_mhp))*98.0f;

        print_set_envcolour(255, 255, 255, 255);
        prepare_blank_box();
        render_blank_box(9, SCREEN_HEIGHT - 9, 111, SCREEN_HEIGHT - 21, 255, 255, 255, 255);
        render_blank_box(10, SCREEN_HEIGHT - 10, 110, SCREEN_HEIGHT - 20, 0, 0, 0, 255);
        render_blank_box(11, SCREEN_HEIGHT - 11, 11 + poop_bar, SCREEN_HEIGHT - 19, 255, 50, 50, 255);
        finish_blank_box();
        print_set_envcolour(150, 92, 0, 255);
        print_small_text(10, SCREEN_HEIGHT - 31, esa_str, PRINT_TEXT_ALIGN_LEFT, PRINT_ALL, FONT_OUTLINE);
        print_set_envcolour(255, 255, 255, 255);
    }
}

void render_marx_health(void) {
    print_set_envcolour(255, 255, 255, 255);
    render_blank_box((SCREEN_WIDTH / 2) - 60, SCREEN_HEIGHT - 10, (SCREEN_WIDTH / 2) + 60, SCREEN_HEIGHT - 20, 255, 255, 255, 255);
    render_blank_box((SCREEN_WIDTH / 2) - 59, SCREEN_HEIGHT - 11, (SCREEN_WIDTH / 2) + 59, SCREEN_HEIGHT - 19, 0, 0, 0, 255);
    print_set_envcolour(255, 255, 255, 255);
    print_small_text(SCREEN_WIDTH/2, SCREEN_HEIGHT - 30, "MARX", PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, FONT_OUTLINE);

    Mtx *mtx = alloc_display_list(sizeof(Mtx));

    if (mtx == NULL) {
        return;
    }
    
    extern Gfx marxHealth_Plane_005_mesh[];
    guTranslate(mtx, (f32) (SCREEN_WIDTH/2) - 59, (f32) 15, 0);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx++),
              G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, 0.99f * ((f32)gMarxHudHealth / 80.0f), 0.3f, 1.0f);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 255, 255, 255);
    gSPDisplayList(gDisplayListHead++, &marxHealth_Plane_005_mesh);


        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

f32 ability_get_alpha = 0.0f;
u8 ability_get_confirm = TRUE;

u16 hud_display_coins = 0;
f32 hud_alpha = 255.0f;

// Shop logic in mitm_hub.c
u8 shop_show_ui = FALSE;
char * shop_text[] = {
    "Compass, Mirror, Milk? You want it? It's yours\nmy friend, as long as you have enough coins.\nUse ^ and | to browse, A to buy, B to exit.",
    "Redstone Compass - 250 coins\nPoints to the nearest mission-specific object.\nCrafted with 4 iron bars and 1 redstone.",
    "Magic Mirror - 200 coins\nLets you instantly warp to the last checkpoint.\nGaze in the mirror to return home.",
    "Lon Lon Milk - 350 coins\nDrink it to instantly heal yourself.\nThe highest quality milk in Hyrule.",
    "121st Power Star - 200 coins\nAn additional power star.\nWas uncovered deep within the icy slide.",
    "Atreus' Artifact - 500 coins\nAn eye that pierces the fabric of universes.\nRequired to repair the Multiverse Machine.",
};
char shop_cant_afford_text[] = "Sorry Mario, I can't give credit!\nCome back when you're a little, mmm... richer!";
char shop_sold_out_text[] = "OUT OF STOCK";
extern s8 shop_target_item;
u8 shop_cant_afford = FALSE;
u8 shop_sold_out = FALSE;

// Hint logic ALSO in mitm_hub.c
u8 hint_show_ui = FALSE;

extern u8 show_mitm_credits;
extern u8 redd_painting_show_ui;
extern u8 music_menu_show_ui;

/**
 * Render HUD strings using hudDisplayFlags with it's render functions,
 * excluding the cannon reticle which detects a camera preset for it.
 */
extern u8 pipe_string_a[];
extern Gfx crackglass_Plane_mesh[];



//--E

static u8 *sE_HeadTexGroupD1[3][2] = {
    { e_hud_m_D1L_U_rgba16, e_hud_m_D1L_L_rgba16 }, { e_hud_m_D1M_U_rgba16, e_hud_m_D1M_L_rgba16 }, { e_hud_m_D1R_U_rgba16, e_hud_m_D1R_L_rgba16 }
};
static u8 *sE_HeadTexGroupD2[3][2] = {
    { e_hud_m_D2L_U_rgba16, e_hud_m_D2L_L_rgba16 }, { e_hud_m_D2M_U_rgba16, e_hud_m_D2M_L_rgba16 }, { e_hud_m_D2R_U_rgba16, e_hud_m_D2R_L_rgba16 }
};
static u8 *sE_HeadTexGroupD3[3][2] = {
    { e_hud_m_D3L_U_rgba16, e_hud_m_D3L_L_rgba16 }, { e_hud_m_D3M_U_rgba16, e_hud_m_D3M_L_rgba16 }, { e_hud_m_D3R_U_rgba16, e_hud_m_D3R_L_rgba16 }
};
static u8 *sE_HeadTexGroupD4[3][2] = {
    { e_hud_m_D4L_U_rgba16, e_hud_m_D4L_L_rgba16 }, { e_hud_m_D4M_U_rgba16, e_hud_m_D4M_L_rgba16 }, { e_hud_m_D4R_U_rgba16, e_hud_m_D4R_L_rgba16 }
};

u8 gE_C9MarioHealth = 100;
static u8 sE_HeadDirTimer = 0;
static u8 sE_CurrHeadDir  = 0;


static void e__x_offset(s32 *x, s32 printedVal) {
    if (printedVal > 99) {
        *x -= 24;
    } else if (printedVal > 9) {
        *x -= 12;
    }
}

void render_ability_get_hud(void) {
    if ((gMarioState->action == ACT_ABILITY_DANCE)&&(gMarioState->actionState == ACT_STATE_STAR_DANCE_DO_SAVE)) {
        ability_get_alpha = approach_f32_asymptotic(ability_get_alpha,255.0f,0.2f);
    } else {
        ability_get_alpha = approach_f32_asymptotic(ability_get_alpha,0.0f,0.2f);
    }

    if (ability_get_alpha > 0.1f) {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, (u8)ability_get_alpha);
        create_dl_translation_matrix(MENU_MTX_PUSH, 160, 120, 0);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
        gSPDisplayList(gDisplayListHead++, desconly_onlybox_mesh);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, (u8)ability_get_alpha);
        print_generic_string(43, 58, ability_string(gMarioState->usedObj->oBehParams2ndByte));
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    }
}

void print_p_rank_starcount(s16 x, s16 y) {
    u8 strToadCount[2];
    u8 strToadTotal[2];
    u8 textSymStar[] = { GLYPH_STAR, GLYPH_SPACE };
    u8 textSymSeparator[] = { GLYPH_SLASH, GLYPH_SPACE };

    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    print_hud_lut_string(HUD_LUT_GLOBAL, x +  0, y, textSymStar);
    int_to_str(p_rank_stars, strToadCount);
    print_hud_lut_string(HUD_LUT_GLOBAL, x + 16, y, strToadCount);
    print_hud_lut_string(HUD_LUT_GLOBAL, x + 32, y, textSymSeparator);
    int_to_str(5, strToadTotal);
    print_hud_lut_string(HUD_LUT_GLOBAL, x + 48, y, strToadTotal);
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
}

extern Gfx cbmeter_Plane_004_mesh[];
extern Gfx cbg_Plane_005_mesh[];
u8 combo_meter_visual = 201;

void render_hud(void) {
    //--E
    if ((gCurrLevelNum == LEVEL_E)&&(gHudDisplay.flags != HUD_DISPLAY_NONE)&&(!level_in_dream_comet_mode())) {
        create_dl_ortho_matrix();
        //--**
        create_dl_scale_matrix(MENU_MTX_PUSH, 0.75f, 0.75f, 0);

        if (sCurrPlayMode == PLAY_MODE_PAUSED || (gMarioState->action == ACT_ENTER_HUB_PIPE )) {
            hud_alpha = approach_f32_asymptotic(hud_alpha,0.0f,0.2f);
        } else {
            hud_alpha = approach_f32_asymptotic(hud_alpha,255.0f,0.2f);
        }

        if (hud_display_coins == 0) {
            hud_display_coins = gMarioState->numGlobalCoins;
        }
        if (hud_display_coins > gMarioState->numGlobalCoins) {
            hud_display_coins --;
        }
        if ((hud_display_coins < gMarioState->numGlobalCoins)&&(gGlobalTimer%3==0)) {
            hud_display_coins ++;
        }

        render_ability_dpad(60,265,(u8)hud_alpha);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, (u8)hud_alpha);

        render_hud_ability_meter();
        if (sAbilityMeterHUD.y > 0) {
            render_meter(253, 185, sAbilityMeterHUD.x, sAbilityMeterStoredValue, (u8)hud_alpha * (sAbilityMeterHUD.y / 255.0f));
        }        


        //BG
        gSPDisplayList(gDisplayListHead++, e_hud_model_mesh);

        //status
        s32 x = 0;
        s32 displayCoinCount = TRUE;
        if (using_ability(ABILITY_E_SHOTGUN)) {
            if (hud_display_coins <= 0) {
                if (gE_ShotgunTimer > 20) {
                    displayCoinCount = FALSE; }
            }
        }
        if (displayCoinCount) {
            x = 42;
            e__x_offset(&x, gMarioState->numGlobalCoins);
            print_text_fmt_int(x, 15, "%d", gMarioState->numGlobalCoins);
        }        

        x = 99;
        e__x_offset(&x, gE_C9MarioHealth);
        print_text_fmt_int(x, 15, "%d", gE_C9MarioHealth);

        x  = 220;
        e__x_offset(&x, gMarioState->numStars);
        print_text_fmt_int(x, 15, "%d", gMarioState->numStars);

        print_text(99 + 16, 15, "/");

        //keys
        if (gMarioState->numKeys & BIT(0)) {
            print_text(255, 26, "!");
        }
        if (gMarioState->numKeys & BIT(1)) {
            print_text(255, 15, "#");
        }
        if (gMarioState->numKeys & BIT(2)) {
            print_text(255, 4, "?");
        }

        //cam
        render_hud_camera_status(277, 213);

        //Mario head
        if (sE_HeadDirTimer) {
            sE_HeadDirTimer--;
        } else {
            sE_HeadDirTimer = (random_u16() / 1500);
            sE_CurrHeadDir  = (random_u16() / 21846);            
        }

        u8 *upper = NULL;
        u8 *lower = NULL;
        if (gE_C9MarioHealth == 0) {//:Deadge:
            upper = e_hud_m_D5_U_rgba16;
            lower = e_hud_m_D5_L_rgba16;
        } else {
            u8 *currHeadTexGroup = NULL;

            if (gE_C9MarioHealth >= 80) {
                upper = sE_HeadTexGroupD1[sE_CurrHeadDir][0];
                lower = sE_HeadTexGroupD1[sE_CurrHeadDir][1];
            } else if (gE_C9MarioHealth >= 60) {
                upper = sE_HeadTexGroupD2[sE_CurrHeadDir][0];
                lower = sE_HeadTexGroupD2[sE_CurrHeadDir][1];
            } else if (gE_C9MarioHealth >= 40) {
                upper = sE_HeadTexGroupD3[sE_CurrHeadDir][0];
                lower = sE_HeadTexGroupD3[sE_CurrHeadDir][1];
            } else {
                currHeadTexGroup = &sE_HeadTexGroupD4;
                upper = sE_HeadTexGroupD4[sE_CurrHeadDir][0];
                lower = sE_HeadTexGroupD4[sE_CurrHeadDir][1];                
            }
        }

        Gfx *tex = segmented_to_virtual(&mat_e_hud_m_d2r_u_f3d_layer1[7]);
        tex->words.w1 = upper;
        tex = segmented_to_virtual(&mat_e_hud_m_d2r_l_f3d_layer1[7]);
        tex->words.w1 = lower;

        gSPDisplayList(gDisplayListHead++, e_hud_m_modelH_mesh);

        create_dl_translation_matrix(MENU_MTX_PUSH, 0.f, 20.f, 0);
        render_ability_get_hud();
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

        return;
    }





    s16 hudDisplayFlags = gHudDisplay.flags;

    if (hudDisplayFlags == HUD_DISPLAY_NONE) {
        sPowerMeterHUD.animation = POWER_METER_HIDDEN;
        sPowerMeterStoredHealth = 8;
        sPowerMeterVisibleTimer = 0;
#ifdef BREATH_METER
        sBreathMeterHUD.animation = BREATH_METER_HIDDEN;
        sBreathMeterStoredValue = 8;
        sBreathMeterVisibleTimer = 0;
#endif
    } else {
#ifdef VERSION_EU
        // basically create_dl_ortho_matrix but guOrtho screen width is different
        Mtx *mtx = alloc_display_list(sizeof(*mtx));

        if (mtx == NULL) {
            return;
        }

        create_dl_identity_matrix();
        guOrtho(mtx, -16.0f, SCREEN_WIDTH + 16, 0, SCREEN_HEIGHT, -10.0f, 10.0f, 1.0f);
        gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
        gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx),
                  G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
#else
        create_dl_ortho_matrix();

        if ((gCurrLevelNum == LEVEL_L)&&(p_rank_challenge_enabled)) {
            f32 combo_meter_y = 0.0f;
            if (combo_meter < 100) {
                combo_meter_y = sins(gGlobalTimer*0x3000) * 1.0f;
            }
            if (combo_meter < 50) {
                combo_meter_y = sins(gGlobalTimer*0x3000) * 3.0f;
            }
            if (combo_meter == 0) {
                combo_meter_y = 0.0f;
            }
            if (combo_meter_visual < combo_meter) {
                combo_meter_visual = approach_f32_asymptotic(combo_meter_visual,combo_meter,0.3f);
            } else {
                combo_meter_visual = combo_meter;
            }
            create_dl_translation_matrix(MENU_MTX_PUSH, sins(gGlobalTimer*0x200) * 3.0f, combo_meter_y+7.0f, 0);
                create_dl_translation_matrix(MENU_MTX_PUSH, combo_meter_visual*.273f, 0, 0);
                    gSPDisplayList(gDisplayListHead++, cbg_Plane_005_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                gSPDisplayList(gDisplayListHead++, cbmeter_Plane_004_mesh);
                if (p_rank_true) {
                    print_p_rank_starcount(15,220);
                }
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
        }

        if (cm_cutscene_on) {
            u8 colorFade = sins(gGlobalTimer*0x500) * 50.0f + 200.0f;
            if (cm_textbox_alpha > 0.1f) {
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, (u8)cm_textbox_alpha);
                create_dl_translation_matrix(MENU_MTX_PUSH, 160, 120, 0);
                gDPSetRenderMode(gDisplayListHead++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
                gSPDisplayList(gDisplayListHead++, desconly_onlybox_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

                if (cm_textbox_text != NULL) {
                    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                    switch(cm_textbox_speaker) {
                        case CM_SPEAKER_PEACH:
                            gDPSetEnvColor(gDisplayListHead++, 255, 40, 200, (u8)cm_textbox_text_alpha);
                            print_generic_string_ascii(43, 58, "Peach:");
                            break;
                        case CM_SPEAKER_EGADD:
                            gDPSetEnvColor(gDisplayListHead++, 150, 200, 255, (u8)cm_textbox_text_alpha);
                            print_generic_string_ascii(43, 58, "E.Gadd:");
                            break;
                        case CM_SPEAKER_BOWSER:
                            gDPSetEnvColor(gDisplayListHead++, 255, 40, 40, (u8)cm_textbox_text_alpha);
                            print_generic_string_ascii(43, 58, "Bowser:");
                            break;
                    }


                    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, (u8)cm_textbox_text_alpha);
                    print_generic_string_ascii(43, 44, cm_textbox_text);

                    if ((cm_textbox_a_signal)&&(cm_textbox_text_alpha >= 254.0f)) {
                        gDPSetEnvColor(gDisplayListHead++, 50, 50, 255, colorFade);
                        print_generic_string(157, 14, pipe_string_a);
                    }

                    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
                }
            }
            if (cm_crack_signal) {
                gSPDisplayList(gDisplayListHead++, crackglass_Plane_mesh);
            }
            return;
        }
#endif

        if (sCurrPlayMode == PLAY_MODE_PAUSED || (gMarioState->action == ACT_ENTER_HUB_PIPE )||(shop_show_ui)||(hint_show_ui)||(show_mitm_credits)||(redd_painting_show_ui)||(music_menu_show_ui)) {
            hud_alpha = approach_f32_asymptotic(hud_alpha,0.0f,0.2f);
        } else {
            hud_alpha = approach_f32_asymptotic(hud_alpha,255.0f,0.2f);
            render_hud_camera_status(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_CAMERA_X), 205);
        }

        if (hud_display_coins == 0) {
            hud_display_coins = gMarioState->numGlobalCoins;
        }
        if (hud_display_coins > gMarioState->numGlobalCoins) {
            hud_display_coins --;
            // go fast if it's a lot
            if (hud_display_coins > gMarioState->numGlobalCoins+10) {
                hud_display_coins -=5;
            }
        }
        if ((hud_display_coins < gMarioState->numGlobalCoins)&&(gGlobalTimer%3==0)) {
            hud_display_coins ++;
        }


        create_dl_scale_matrix(MENU_MTX_PUSH, 0.75f, 0.75f, 0);
        render_ability_dpad(60,265,(u8)hud_alpha);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, (u8)hud_alpha);

        if (dream_comet_unlocked()) {
            gSPDisplayList(gDisplayListHead++, &extended_hudbar_extendedhudbar_mesh);
        } else {
            gSPDisplayList(gDisplayListHead++, &hudbar_hudbar_mesh);
        }
        if (level_in_dream_comet_mode()) {
            gSPDisplayList(gDisplayListHead++, &cometbar_cometbar_mesh);
        }

        s16 meterhp = gHudDisplay.wedges;
        if (level_in_dream_comet_mode()&&gCurrLevelNum==LEVEL_E) {
            meterhp = (gE_C9MarioHealth/100.0f)*8;
        }
        render_meter(293, 185, METER_STYLE_HP, meterhp, (u8)hud_alpha);

#ifdef BREATH_METER
        if (hudDisplayFlags & HUD_DISPLAY_FLAG_BREATH_METER) {
            render_hud_breath_meter();
            if (sBreathMeterHUD.y > 0) {
                render_meter(293, 145, METER_STYLE_BREATH, gHudDisplay.breath, (u8)hud_alpha * (sBreathMeterHUD.y / 255.0f));
            }
        }
#endif

        render_hud_ability_meter();
        if (sAbilityMeterHUD.y > 0) {
            render_meter(253, 185, sAbilityMeterHUD.x, sAbilityMeterStoredValue, (u8)hud_alpha * (sAbilityMeterHUD.y / 255.0f));
        }

        

        gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);

            //Need to do this twice... sadge
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, (u8)hud_alpha);
            int_to_str_000(gHudDisplay.stars, &hudbar_star[2]);
            int_to_str_000(gMarioState->numDreamCatalysts, &hudbar_dc[2]);
            //--E
            int_to_str_000(hud_display_coins, &hudbar_coin[2]);
            s32 displayCoinCount = TRUE;
            if (using_ability(ABILITY_E_SHOTGUN)) {
                if (hud_display_coins <= 0) {
                    if (gE_ShotgunTimer > 20) {//--E
                        displayCoinCount = FALSE; }
                }
            }

            s16 x_offset = 0;
            if (dream_comet_unlocked()) {
                x_offset -= 70;
                print_hud_lut_string(HUD_LUT_GLOBAL, 240, 14, hudbar_dc);
            }

            if (displayCoinCount) {
                print_hud_lut_string(HUD_LUT_GLOBAL, 170+x_offset, 14, hudbar_coin);
            }

            print_hud_lut_string(HUD_LUT_GLOBAL, 240+x_offset, 14, hudbar_star);

        gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);

        if (gCurrLevelNum == LEVEL_G && gCurrAreaIndex == 5 && gMarxHudHealth > 0) {
            render_marx_health();
        }

        render_esa_health();

        render_ability_get_hud();

        if (level_in_dream_comet_mode()) {
            render_dream_comet_hud(hud_alpha);
        }

        if (shop_show_ui) {
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-hud_alpha);
            create_dl_translation_matrix(MENU_MTX_PUSH, 160, 120, 0);
            gDPSetRenderMode(gDisplayListHead++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
            gSPDisplayList(gDisplayListHead++, desconly_onlybox_mesh);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-hud_alpha);
            char * text_to_print = shop_text[shop_target_item+1];
            if (shop_cant_afford) {
                text_to_print = &shop_cant_afford_text;
            }
            if (shop_sold_out) {
                text_to_print = &shop_sold_out_text;
            }
            print_generic_string_ascii(43, 58, text_to_print);
            gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

            gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255.0f-hud_alpha);
            if (shop_cant_afford) {
                gDPSetEnvColor(gDisplayListHead++, 255, 126.0f+sins(gGlobalTimer*0x1000)*126.0f, 126.0f+sins(gGlobalTimer*0x1000)*126.0f, 255.0f-hud_alpha);
            }
            int_to_str_000(hud_display_coins, &hudbar_coin[2]);
            print_hud_lut_string(HUD_LUT_GLOBAL, 43, 148, hudbar_coin);
            gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
        }

        if (hint_show_ui) {
            render_hint_ui(hud_alpha);
        }
        if (show_mitm_credits) {
            print_mitm_credits(hud_alpha);
        }
        if (redd_painting_show_ui) {
            render_painting_ui(hud_alpha);
        }
        if (music_menu_show_ui) {
            render_music_menu_ui(hud_alpha);
        }

        //revert (prolly not needed)
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);

        if (gCurrentArea != NULL && gCurrentArea->camera->mode == CAMERA_MODE_INSIDE_CANNON) {
            render_hud_cannon_reticle();
        }

#ifdef ENABLE_LIVES
        if (hudDisplayFlags & HUD_DISPLAY_FLAG_LIVES) {
            render_hud_mario_lives();
        }
#endif

/*
        if (hudDisplayFlags & HUD_DISPLAY_FLAG_CAMERA_AND_POWER) {
            //render_hud_power_meter();
#ifdef PUPPYCAM
            if (!gPuppyCam.enabled) {
#endif
            render_hud_camera_status(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_CAMERA_X), 205);
#ifdef PUPPYCAM
            }
#endif
        }
*/

        if (hudDisplayFlags & HUD_DISPLAY_FLAG_TIMER) {

            gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
            create_dl_translation_matrix(MENU_MTX_PUSH, 0, -25, 0);
            gSPDisplayList(gDisplayListHead++, &hudbar_hudbar_mesh);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
            gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

            render_hud_timer();
        }

#ifdef VANILLA_STYLE_CUSTOM_DEBUG
        if (gCustomDebugMode) {
            render_debug_mode();
        }
#endif
    }
}
