#include "texscroll.h"
#include <ultra64.h>

#include "sm64.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "audio/external.h"
#include "audio/synthesis.h"
#include "level_update.h"
#include "game_init.h"
#include "level_update.h"
#include "main.h"
#include "engine/math_util.h"
#include "engine/graph_node.h"
#include "area.h"
#include "save_file.h"
#include "sound_init.h"
#include "mario.h"
#include "camera.h"
#include "object_list_processor.h"
#include "ingame_menu.h"
#include "obj_behaviors.h"
#include "save_file.h"
#if MULTILANG
#include "memory.h"
#include "eu_translation.h"
#include "segment_symbols.h"
#endif
#include "level_table.h"
#include "course_table.h"
#include "rumble_init.h"
#include "puppycam2.h"
#include "puppyprint.h"
#include "puppylights.h"
#include "level_commands.h"
#include "ability.h"
#include "cutscene_manager.h"
#include "mitm_hub.h"
#include "ability.h"

#include "config.h"

// TODO: Make these ifdefs better
const char *credits00[] = { "1COLLAB HOST", "ROVERTRONIC" };
const char *credits01[] = { "1MARIO SUPER STAR ULTRA", "COWQUACK" };
const char *credits02[] = { "1MARIO IN BIKINI BOTTOM","JOSHTHEBOSH"};
const char *credits03[] = { "2SPLATOON", "DRAHNOKKS", "WOISSIL" };
const char *credits04[] = { "1MUSHROOM HAVOC","DRAHNOKKS" };
const char *credits05[] = { "1OPPORTUNITY","JOOPII"};
const char *credits06[] = { "1BIOSHOCK","FURYIOUSFIGHT"};
const char *credits07[] = { "1BEYOND THE CURSED PIZZA","LUIGIMAN O64O"};
const char *credits08[] = { "2NEW MECCA","AXOLLYON","KEYBLADER"};
const char *credits09[] = { "1DOOM", "DAN GPTV" };
const char *credits10[] = { "1FROM RUSSIA WITH LOVE","AEZA"}; 
const char *credits11[] = { "1ECRUTEAK CITY","SPK" };
const char *credits12[] = { "1NEW N SANITY ISLAND", "JAKE DOWER" };
const char *credits13[] = { "1SAINTS SINNERS AND MARIO", "ROVERTRONIC" };
const char *credits14[] = { "1MARIO IN HAMSTERBALL","LINCRASH"};
const char *credits15[] = { "1ENVIRONMENTAL STATION ALPHA", "MEL" };
const char *credits16[] = { "5SCREEN TEXT WRITER", "TRANSLATION", "LESLIE SWAN", "MINA AKINO", "HIRO YAMADA" }; 
const char *credits17[] = { "4MARIO VOICE", "PEACH VOICE", "CHARLES MARTINET", "LESLIE SWAN" };
const char *credits18[] = { "3SPECIAL THANKS TO", "JYOHO KAIHATUBU", "ALL NINTENDO", "MARIO CLUB STAFF" };
const char *credits19[] = { "1PRODUCER", "SHIGERU MIYAMOTO" };
const char *credits20[] = { "1EXECUTIVE PRODUCER", "HIROSHI YAMAUCHI" };


struct CreditsEntry sCreditsSequence[] = {
    { LEVEL_CASTLE, 1, 1, 117, {-5635,2250,-1806}, credits00 , ABILITY_DEFAULT},
    { LEVEL_G, 3, 1, 0, {475,1283,-1275}, credits01, ABILITY_CUTTER},
    { LEVEL_A, 4, 50, 126, {-4465,-31,12360}, credits02, ABILITY_BUBBLE_HAT},
    { LEVEL_JRB, 1, 18, 22, { 3800, 9840, 2727 }, credits03, ABILITY_SQUID},
    { LEVEL_I, 3, 34, 205, {6732,440,-3848}, credits04, ABILITY_SHOCK_ROCKET},
    { LEVEL_H, 1, 1, 240, {-1514,-245,858}, credits05, ABILITY_PHASEWALK},
    { LEVEL_JRB, 1, 18, 22, { 3800, 9840, 2727 }, credits06, ABILITY_BIG_DADDY},
    { LEVEL_L, 1, 17, -64, {1512,-300,0}, credits07, ABILITY_KNIGHT},
    { LEVEL_JRB, 1, 18, 22, { 3800, 9840, 2727 }, credits08, ABILITY_CHRONOS},
    { LEVEL_E, 1, 65, 0, {-8827,6226,-4956}, credits09, ABILITY_E_SHOTGUN},
    { LEVEL_F, 3, 50, 0, {-759,230,2346}, credits10, ABILITY_GADGET_WATCH},
    { LEVEL_J, 2, 17, 114, {-3399,3224,-538}, credits11, ABILITY_HM_FLY},
    { LEVEL_D, 1, 33, 0, {-1851,3216,-4258}, credits12, ABILITY_AKU},
    { LEVEL_O, 1, 2, 99, {2231,-2250,229}, credits13, ABILITY_ESTEEMED_MORTAL},
    { LEVEL_N, 2, 51, 57, {-29,617,294}, credits14, ABILITY_DEFAULT},
    { LEVEL_TTC, 1, 17, -72, { -1304, -71, -967 }, credits15, ABILITY_DASH_BOOSTER},
    { LEVEL_CASTLE_GROUNDS, 1, 1, -128, { 0, 906, -1200 }, NULL, ABILITY_DEFAULT},
    { LEVEL_NONE, 0, 1, 0, { 0, 0, 0 }, NULL, ABILITY_DEFAULT},
};

struct MarioState gMarioStates[1];
struct HudDisplay gHudDisplay;
s16 sCurrPlayMode;
s16 sTransitionTimer;
void (*sTransitionUpdate)(s16 *);
struct WarpDest sWarpDest;
s16 sSpecialWarpDest;
s16 sDelayedWarpOp;
s16 sDelayedWarpTimer;
s16 sSourceWarpNodeId;
s32 sDelayedWarpArg;
s8 sTimerRunning;
s8 gNeverEnteredCastle;
// Prevent multiple 100 coin stars from spawning
u8 g100CoinStarSpawned = FALSE;

struct MarioState *gMarioState = &gMarioStates[0];
s8 sWarpCheckpointActive = FALSE;

u16 level_control_timer(s32 timerOp) {
    switch (timerOp) {
        case TIMER_CONTROL_SHOW:
            gHudDisplay.flags |= HUD_DISPLAY_FLAG_TIMER;
            sTimerRunning = FALSE;
            gHudDisplay.timer = 0;
            break;

        case TIMER_CONTROL_START:
            sTimerRunning = TRUE;
            break;

        case TIMER_CONTROL_STOP:
            sTimerRunning = FALSE;
            break;

        case TIMER_CONTROL_HIDE:
            gHudDisplay.flags &= ~HUD_DISPLAY_FLAG_TIMER;
            sTimerRunning = FALSE;
            gHudDisplay.timer = 0;
            break;
    }

    return gHudDisplay.timer;
}

u32 pressed_pause(void) {
    u32 dialogActive = get_dialog_id() >= 0;
    u32 intangible = (gMarioState->action & ACT_FLAG_INTANGIBLE) != 0;

    if (gCurrLevelNum == LEVEL_G || gCurrAreaIndex == 5) {
        //poison marx pause
        return FALSE;
    }

#ifdef PUPPYPRINT_DEBUG
#ifdef BETTER_REVERB
    if (sPPDebugPage == PUPPYPRINT_PAGE_RAM || sPPDebugPage == PUPPYPRINT_PAGE_LEVEL_SELECT || sPPDebugPage == PUPPYPRINT_PAGE_BETTER_REVERB) {
#else
    if (sPPDebugPage == PUPPYPRINT_PAGE_RAM || sPPDebugPage == PUPPYPRINT_PAGE_LEVEL_SELECT) {
#endif
        return FALSE;
    }
#endif

    if (!intangible && !dialogActive && !gWarpTransition.isActive && sDelayedWarpOp == WARP_OP_NONE && !cm_cutscene_on
        && (gPlayer1Controller->buttonPressed & START_BUTTON)) {
        return TRUE;
    }

    return FALSE;
}

void set_play_mode(s16 playMode) {
    sCurrPlayMode = playMode;
}

void warp_special(s32 arg) {
    sCurrPlayMode = PLAY_MODE_CHANGE_LEVEL;
    sSpecialWarpDest = arg;
}

void fade_into_special_warp(u32 arg, u32 color) {
    if (color != 0) {
        color = 0xFF;
    }

    fadeout_music(190);
    play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x10, color, color, color);
    level_set_transition(30, NULL);

    warp_special(arg);
}

void load_level_init_text(u32 arg) {
    s32 gotAchievement;
    u32 dialogID = gCurrentArea->dialog[arg];

    switch (dialogID) {
        case DIALOG_129:
            gotAchievement = save_file_get_flags() & SAVE_FLAG_HAVE_VANISH_CAP;
            break;

        case DIALOG_130:
            gotAchievement = save_file_get_flags() & SAVE_FLAG_HAVE_METAL_CAP;
            break;

        case DIALOG_131:
            gotAchievement = save_file_get_flags() & SAVE_FLAG_HAVE_WING_CAP;
            break;

        case (u8)DIALOG_NONE: // 255, cast value to u8 to match (-1)
            gotAchievement = TRUE;
            break;

        default:
            gotAchievement =
                save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(gCurrCourseNum));
            break;
    }

    if (!gotAchievement) {
        level_set_transition(-1, NULL);
        create_dialog_box(dialogID);
    }
}

void init_door_warp(struct SpawnInfo *spawnInfo, u32 warpDestFlags) {
    if (warpDestFlags & WARP_FLAG_DOOR_FLIP_MARIO) {
        spawnInfo->startAngle[1] += 0x8000;
    }

    spawnInfo->startPos[0] += 300.0f * sins(spawnInfo->startAngle[1]);
    spawnInfo->startPos[2] += 300.0f * coss(spawnInfo->startAngle[1]);
}

void set_mario_initial_cap_powerup(struct MarioState *m) {
    u32 capCourseIndex = gCurrCourseNum - COURSE_CAP_COURSES;

    switch (capCourseIndex) {
        case COURSE_COTMC - COURSE_CAP_COURSES:
            m->flags |= MARIO_METAL_CAP | MARIO_CAP_ON_HEAD;
            m->capTimer = 600;
            break;

        case COURSE_TOTWC - COURSE_CAP_COURSES:
            m->flags |= MARIO_WING_CAP | MARIO_CAP_ON_HEAD;
            m->capTimer = 1200;
            break;

        case COURSE_VCUTM - COURSE_CAP_COURSES:
            m->flags |= MARIO_VANISH_CAP | MARIO_CAP_ON_HEAD;
            m->capTimer = 600;
            break;
    }
}

void set_mario_initial_action(struct MarioState *m, u32 spawnType, u32 actionArg) {
    switch (spawnType) {
        case MARIO_SPAWN_DOOR_WARP:
            set_mario_action(m, ACT_WARP_DOOR_SPAWN, actionArg);
            break;
        case MARIO_SPAWN_IDLE:
            set_mario_action(m, ACT_IDLE, 0);
            break;
        case MARIO_SPAWN_PIPE:
            set_mario_action(m, ACT_EMERGE_FROM_PIPE, 0);
            break;
        case MARIO_SPAWN_TELEPORT:
            set_mario_action(m, ACT_TELEPORT_FADE_IN, 0);
            break;
        case MARIO_SPAWN_INSTANT_ACTIVE:
            set_mario_action(m, ACT_IDLE, 0);
            break;
        case MARIO_SPAWN_AIRBORNE:
            set_mario_action(m, ACT_SPAWN_NO_SPIN_AIRBORNE, 0);
            break;
        case MARIO_SPAWN_HARD_AIR_KNOCKBACK:
            set_mario_action(m, ACT_HARD_BACKWARD_AIR_KB, 0);
            break;
        case MARIO_SPAWN_SPIN_AIRBORNE_CIRCLE:
            set_mario_action(m, ACT_SPAWN_SPIN_AIRBORNE, 0);
            break;
        case MARIO_SPAWN_DEATH:
            set_mario_action(m, ACT_FALLING_DEATH_EXIT, 0);
            break;
        case MARIO_SPAWN_SPIN_AIRBORNE:
            set_mario_action(m, ACT_SPAWN_SPIN_AIRBORNE, 0);
            break;
        case MARIO_SPAWN_FLYING:
            set_mario_action(m, ACT_FLYING, 2);
            break;
        case MARIO_SPAWN_SWIMMING:
            set_mario_action(m, ACT_WATER_IDLE, 1);
            break;
        case MARIO_SPAWN_PAINTING_STAR_COLLECT:
            set_mario_action(m, ACT_EXIT_AIRBORNE, 0);
            break;
        case MARIO_SPAWN_PAINTING_DEATH:
            set_mario_action(m, ACT_DEATH_EXIT, 0);
            break;
        case MARIO_SPAWN_AIRBORNE_STAR_COLLECT:
            set_mario_action(m, ACT_FALLING_EXIT_AIRBORNE, 0);
            break;
        case MARIO_SPAWN_AIRBORNE_DEATH:
            set_mario_action(m, ACT_UNUSED_DEATH_EXIT, 0);
            break;
        case MARIO_SPAWN_LAUNCH_STAR_COLLECT:
            set_mario_action(m, ACT_SPECIAL_EXIT_AIRBORNE, 0);
            break;
        case MARIO_SPAWN_LAUNCH_DEATH:
            set_mario_action(m, ACT_SPECIAL_DEATH_EXIT, 0);
            break;
    }

#ifdef PREVENT_DEATH_LOOP
    if (m->isDead) {
        m->health = 0x880;
        m->isDead = FALSE;
    }
#endif

    set_mario_initial_cap_powerup(m);
}

void init_mario_after_warp(void) {
    struct ObjectWarpNode *spawnNode = area_get_warp_node(sWarpDest.nodeId);
    u32 marioSpawnType = get_mario_spawn_type(spawnNode->object);

    if (gMarioState->action != ACT_UNINITIALIZED) {
        magic_mirror_disable = FALSE;

        gPlayerSpawnInfos[0].startPos[0] = (s16) spawnNode->object->oPosX;
        gPlayerSpawnInfos[0].startPos[1] = (s16) spawnNode->object->oPosY;
        gPlayerSpawnInfos[0].startPos[2] = (s16) spawnNode->object->oPosZ;

        gPlayerSpawnInfos[0].startAngle[0] = 0;
        gPlayerSpawnInfos[0].startAngle[1] = spawnNode->object->oMoveAngleYaw;
        gPlayerSpawnInfos[0].startAngle[2] = 0;

        if (marioSpawnType == MARIO_SPAWN_DOOR_WARP) {
            init_door_warp(&gPlayerSpawnInfos[0], sWarpDest.arg);
        }

        if (sWarpDest.type == WARP_TYPE_CHANGE_LEVEL) {
            gMarioState->areaCheckpointFlag = -1;
            gMarioState->numCheckpointFlag = -1;
        }
        if (sWarpDest.type == WARP_TYPE_CHANGE_LEVEL || sWarpDest.type == WARP_TYPE_CHANGE_AREA) {
            gPlayerSpawnInfos[0].areaIndex = sWarpDest.areaIdx;
            load_mario_area();
            chronos_timer = 360;
        }

        init_mario();
        set_mario_initial_action(gMarioState, marioSpawnType, sWarpDest.arg);
        gMarioState->marioObj->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;

        gMarioState->interactObj = spawnNode->object;
        gMarioState->usedObj = spawnNode->object;
    }

    reset_camera(gCurrentArea->camera);
    sWarpDest.type = WARP_TYPE_NOT_WARPING;
    sDelayedWarpOp = WARP_OP_NONE;

    switch (marioSpawnType) {
        case MARIO_SPAWN_PIPE:
            play_transition(WARP_TRANSITION_FADE_FROM_STAR, 0x10, 0x00, 0x00, 0x00);
            break;
        case MARIO_SPAWN_DOOR_WARP:
            play_transition(WARP_TRANSITION_FADE_FROM_CIRCLE, 0x10, 0x00, 0x00, 0x00);
            break;
        case MARIO_SPAWN_TELEPORT:
            play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 0x14, 0xFF, 0xFF, 0xFF);
            break;
        case MARIO_SPAWN_SPIN_AIRBORNE:
            play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 0x1A, 0xFF, 0xFF, 0xFF);
            break;
        case MARIO_SPAWN_SPIN_AIRBORNE_CIRCLE:
            play_transition(WARP_TRANSITION_FADE_FROM_CIRCLE, 0x10, 0x00, 0x00, 0x00);
            break;
        case MARIO_SPAWN_FADE_FROM_BLACK:
            play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 0x10, 0x00, 0x00, 0x00);
            break;
        default:
            play_transition(WARP_TRANSITION_FADE_FROM_STAR, 0x10, 0x00, 0x00, 0x00);
            break;
    }

    if (gCurrDemoInput == NULL) {
#ifdef BETTER_REVERB
        gBetterReverbPresetValue = gCurrentArea->betterReverbPreset;
#endif
        set_background_music(gCurrentArea->musicParam, gCurrentArea->musicParam2, 0);

        if (gMarioState->flags & MARIO_METAL_CAP) {
            play_cap_music(SEQUENCE_ARGS(4, SEQ_EVENT_METAL_CAP));
        }

        if (gMarioState->flags & (MARIO_VANISH_CAP | MARIO_WING_CAP)) {
            play_cap_music(SEQUENCE_ARGS(4, SEQ_EVENT_POWERUP));
        }

#ifdef ENABLE_VANILLA_LEVEL_SPECIFIC_CHECKS
        if (gCurrLevelNum == LEVEL_BOB
            && get_current_background_music() != SEQUENCE_ARGS(4, SEQ_LEVEL_SLIDE) && sTimerRunning) {
            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_LEVEL_SLIDE), 0);
        }

        if (sWarpDest.levelNum == LEVEL_CASTLE && sWarpDest.areaIdx == 1
            && (sWarpDest.nodeId == 32)
        ) {
            play_sound(SOUND_MENU_MARIO_CASTLE_WARP, gGlobalSoundSource);
        }

        if (sWarpDest.levelNum == LEVEL_CASTLE_GROUNDS && sWarpDest.areaIdx == 1
            && (sWarpDest.nodeId == 7 || sWarpDest.nodeId == 10 || sWarpDest.nodeId == 20
                || sWarpDest.nodeId == 30)) {
            play_sound(SOUND_MENU_MARIO_CASTLE_WARP, gGlobalSoundSource);
        }
#endif
#ifndef DISABLE_EXIT_COURSE
       if (sWarpDest.arg == WARP_FLAG_EXIT_COURSE) {
            play_sound(SOUND_MENU_MARIO_CASTLE_WARP, gGlobalSoundSource);
        }
#endif
    }
#ifdef PUPPYPRINT_DEBUG
    gPuppyWarp = 0;
    gLastWarpID = sWarpDest.nodeId;
    gPuppyWarpArea = 0;
#endif
}

// used for warps inside one level
void warp_area(void) {
    if (sWarpDest.type != WARP_TYPE_NOT_WARPING) {
        if (sWarpDest.type == WARP_TYPE_CHANGE_AREA) {
            level_control_timer(TIMER_CONTROL_HIDE);
            unload_mario_area();
            load_area(sWarpDest.areaIdx);
        }

        init_mario_after_warp();
    }
}

// used for warps between levels
void warp_level(void) {
    gCurrLevelNum = sWarpDest.levelNum;

    level_control_timer(TIMER_CONTROL_HIDE);

    load_area(sWarpDest.areaIdx);
    init_mario_after_warp();
}

void warp_credits(void) {
    s32 marioAction = ACT_UNINITIALIZED;

    switch (sWarpDest.nodeId) {

        case WARP_NODE_CREDITS_START:
        case WARP_NODE_CREDITS_NEXT:
            sEndCutsceneVp.vp.vscale[0] = 640;
            sEndCutsceneVp.vp.vscale[1] = 360;
            sEndCutsceneVp.vp.vtrans[0] = 640;
            sEndCutsceneVp.vp.vtrans[1] = 480;
            marioAction = ACT_CREDITS_CUTSCENE;
            break;

        case WARP_NODE_CREDITS_END:
            marioAction = ACT_END_WAVING_CUTSCENE;
            break;
    }

    gCurrLevelNum = sWarpDest.levelNum;

    load_area(sWarpDest.areaIdx);

    vec3s_set(gPlayerSpawnInfos[0].startPos, gCurrCreditsEntry->marioPos[0],
              gCurrCreditsEntry->marioPos[1], gCurrCreditsEntry->marioPos[2]);

    vec3s_set(gPlayerSpawnInfos[0].startAngle, 0, 0x100 * gCurrCreditsEntry->marioAngle, 0);

    gPlayerSpawnInfos[0].areaIndex = sWarpDest.areaIdx;

    load_mario_area();
    init_mario();

    set_mario_action(gMarioState, marioAction, 0);

    reset_camera(gCurrentArea->camera);

    sWarpDest.type = WARP_TYPE_NOT_WARPING;
    sDelayedWarpOp = WARP_OP_NONE;

    play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 0x14, 0x00, 0x00, 0x00);

    if (gCurrCreditsEntry == NULL || gCurrCreditsEntry == sCreditsSequence) {
#ifdef BETTER_REVERB
        gBetterReverbPresetValue = gCurrentArea->betterReverbPreset;
#endif
        set_background_music(gCurrentArea->musicParam, gCurrentArea->musicParam2, 0);
    }
}

extern u8 magic_mirror_area_change_flag;
void check_instant_warp(void) {
    s16 cameraAngle;
    struct Surface *floor;

#ifdef ENABLE_VANILLA_LEVEL_SPECIFIC_CHECKS
 #ifdef UNLOCK_ALL
    if (gCurrLevelNum == LEVEL_CASTLE) {
 #else // !UNLOCK_ALL
    if (gCurrLevelNum == LEVEL_CASTLE
        && save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1) >= 70) {
 #endif // !UNLOCK_ALL
        return;
    }
#endif // ENABLE_VANILLA_LEVEL_SPECIFIC_CHECKS

    if ((floor = gMarioState->floor) != NULL) {
        s32 index = floor->type - SURFACE_INSTANT_WARP_1B;
        if (index >= INSTANT_WARP_INDEX_START && index < INSTANT_WARP_INDEX_STOP
            && gCurrentArea->instantWarps != NULL) {
            struct InstantWarp *warp = &gCurrentArea->instantWarps[index];

            if (warp->id != 0) {
                gMarioState->pos[0] += warp->displacement[0];
                gMarioState->pos[1] += warp->displacement[1];
                gMarioState->pos[2] += warp->displacement[2];

                gMarioState->marioObj->oPosX = gMarioState->pos[0];
                gMarioState->marioObj->oPosY = gMarioState->pos[1];
                gMarioState->marioObj->oPosZ = gMarioState->pos[2];

                // Fix instant warp offset not working when warping across different areas
                gMarioObject->header.gfx.pos[0] = gMarioState->pos[0];
                gMarioObject->header.gfx.pos[1] = gMarioState->pos[1];
                gMarioObject->header.gfx.pos[2] = gMarioState->pos[2];

                cameraAngle = gMarioState->area->camera->yaw;

                change_area(warp->area);
                gMarioState->area = gCurrentArea;

                warp_camera(warp->displacement[0], warp->displacement[1], warp->displacement[2]);

                gMarioState->area->camera->yaw = cameraAngle;

                if (gCurrLevelNum == LEVEL_M) {
                    switch(gCurrAreaIndex) {
                        case 1:
                        case 2:
                            stop_background_music(SEQUENCE_ARGS(4, SEQ_CUSTOM_ESA_AMMOINEN));
                            stop_background_music(SEQUENCE_ARGS(4, SEQ_CUSTOM_ESA_SUBMERGED));
                            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_CUSTOM_ESA_VALIANT), 0);
                            break;
                        case 3:
                            stop_background_music(SEQUENCE_ARGS(4, SEQ_CUSTOM_ESA_VALIANT));
                            stop_background_music(SEQUENCE_ARGS(4, SEQ_CUSTOM_ESA_SUBMERGED));
                            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_CUSTOM_ESA_AMMOINEN), 0);
                            break;
                        case 4:
                            stop_background_music(SEQUENCE_ARGS(4, SEQ_CUSTOM_ESA_AMMOINEN));
                            stop_background_music(SEQUENCE_ARGS(4, SEQ_CUSTOM_ESA_VALIANT));
                            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_CUSTOM_ESA_SUBMERGED), 0);
                            break;
                    }
                }
            }
        }
    }

    if (magic_mirror_area_change_flag) {
        magic_mirror_area_change_flag = FALSE;

        change_area(gMarioState->areaCheckpointFlag);
        gMarioState->area = gCurrentArea;
        vec3f_copy(gMarioState->pos,gMarioState->vecCheckpointFlag);
        gMarioState->marioObj->oPosX = gMarioState->pos[0];
        gMarioState->marioObj->oPosY = gMarioState->pos[1];
        gMarioState->marioObj->oPosZ = gMarioState->pos[2];

        set_background_music(gCurrentArea->musicParam, gCurrentArea->musicParam2, 0);
        play_sound(SOUND_ABILITY_MAGIC_MIRROR, gGlobalSoundSource);
    }
}

s16 music_unchanged_through_warp(s16 arg) {
    struct ObjectWarpNode *warpNode = area_get_warp_node(arg);
    s16 levelNum = warpNode->node.destLevel & 0x7F;

    s16 destArea = warpNode->node.destArea;
    s16 unchanged = TRUE;

#ifdef ENABLE_VANILLA_LEVEL_SPECIFIC_CHECKS
    s16 currBgMusic;
    if (levelNum == LEVEL_BOB && levelNum == gCurrLevelNum && destArea == gCurrAreaIndex) {
        currBgMusic = get_current_background_music();
        if (currBgMusic == SEQUENCE_ARGS(4, SEQ_EVENT_POWERUP | SEQ_VARIATION)
            || currBgMusic == SEQUENCE_ARGS(4, SEQ_EVENT_POWERUP)) {
            unchanged = FALSE;
        }
    } else {
#endif
        u16 destParam1 = gAreas[destArea].musicParam;
        u16 destParam2 = gAreas[destArea].musicParam2;
#ifdef BETTER_REVERB
        u16 destParam3 = gAreas[destArea].betterReverbPreset;
        unchanged = levelNum == gCurrLevelNum && destParam1 == gCurrentArea->musicParam
               && destParam2 == gCurrentArea->musicParam2 && destParam3 == gCurrentArea->betterReverbPreset;
#else
        unchanged = levelNum == gCurrLevelNum && destParam1 == gCurrentArea->musicParam
               && destParam2 == gCurrentArea->musicParam2;
#endif

        if (get_current_background_music() != destParam2) {
            unchanged = FALSE;
        }
#ifdef ENABLE_VANILLA_LEVEL_SPECIFIC_CHECKS
    }
#endif
    return unchanged;
}

/**
 * Set the current warp type and destination level/area/node.
 */
void initiate_warp(s16 destLevel, s16 destArea, s16 destWarpNode, s32 warpFlags) {
    if (destWarpNode >= WARP_NODE_CREDITS_MIN) {
        sWarpDest.type = WARP_TYPE_CHANGE_LEVEL;
    } else if (warpFlags == WARP_FLAG_EXIT_COURSE) {
        sWarpDest.type = WARP_TYPE_CHANGE_LEVEL;
    } else if (destLevel != gCurrLevelNum) {
        sWarpDest.type = WARP_TYPE_CHANGE_LEVEL;
    } else if (destArea != gCurrentArea->index) {
        sWarpDest.type = WARP_TYPE_CHANGE_AREA;
    } else {
        sWarpDest.type = WARP_TYPE_SAME_AREA;
    }

    if ((gCurrAreaIndex == 6)&&(gCurrLevelNum == LEVEL_L)) {
        // reset level for p ranks and retries
        sWarpDest.type = WARP_TYPE_CHANGE_LEVEL;
    }

    sWarpDest.levelNum = destLevel;
    sWarpDest.areaIdx = destArea;
    sWarpDest.nodeId = destWarpNode;
    sWarpDest.arg = warpFlags;
#if defined(PUPPYCAM) || defined(PUPPYLIGHTS)
    s32 i = 0;
#endif
#ifdef PUPPYCAM
    if (sWarpDest.type == WARP_TYPE_CHANGE_LEVEL)
    {
        for (i = 0; i < gPuppyVolumeCount; i++)
        {
            mem_pool_free(gPuppyMemoryPool, sPuppyVolumeStack[i]);
        }
        gPuppyVolumeCount = 0;
    }
#endif
#ifdef PUPPYLIGHTS
    if (sWarpDest.type == WARP_TYPE_CHANGE_LEVEL)
    {
        for (i = 0; i < gNumLights; i++)
        {
            mem_pool_free(gLightsPool, gPuppyLights[i]);
        }
        gNumLights = 0;
        levelAmbient = FALSE;
    }
#endif
}

// From Surface 0xD3 to 0xFC
#define PAINTING_WARP_INDEX_START 0x00 // Value greater than or equal to Surface 0xD3
#define PAINTING_WARP_INDEX_FA 0x2A    // THI Huge Painting index left
#define PAINTING_WARP_INDEX_END 0x2D   // Value less than Surface 0xFD

/**
 * Check if Mario is above and close to a painting warp floor, and return the
 * corresponding warp node.
 */
struct WarpNode *get_painting_warp_node(void) {
    struct WarpNode *warpNode = NULL;
    s32 paintingIndex = gMarioState->floor->type - SURFACE_PAINTING_WARP_D3;

    if (paintingIndex >= PAINTING_WARP_INDEX_START && paintingIndex < PAINTING_WARP_INDEX_END) {
        if (paintingIndex < PAINTING_WARP_INDEX_FA
            || gMarioState->pos[1] - gMarioState->floorHeight < 80.0f) {
            warpNode = &gCurrentArea->paintingWarpNodes[paintingIndex];
        }
    }

    return warpNode;
}

/**
 * Check is Mario has entered a painting, and if so, initiate a warp.
 */
void initiate_painting_warp(void) {
    if (gCurrentArea->paintingWarpNodes != NULL && gMarioState->floor != NULL) {
        struct WarpNode warpNode;
        struct WarpNode *pWarpNode = get_painting_warp_node();

        if (pWarpNode != NULL) {
            if (gMarioState->action & ACT_FLAG_INTANGIBLE) {
                play_painting_eject_sound();
            } else if (pWarpNode->id != 0) {
                warpNode = *pWarpNode;

                if (!(warpNode.destLevel & WARP_NO_CHECKPOINT)) {
                    sWarpCheckpointActive = check_warp_checkpoint(&warpNode);
                }

                initiate_warp(warpNode.destLevel & 0x7F, warpNode.destArea, warpNode.destNode, WARP_FLAGS_NONE);
                check_if_should_set_warp_checkpoint(&warpNode);

                play_transition_after_delay(WARP_TRANSITION_FADE_INTO_COLOR, 30, 255, 255, 255, 45);
                level_set_transition(74, basic_update);

                set_mario_action(gMarioState, ACT_DISAPPEARED, 0);

                gMarioState->marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;

                play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
                fadeout_music(398);
#if ENABLE_RUMBLE
                queue_rumble_data(80, 70);
                queue_rumble_decay(1);
#endif
            }
        }
    }
}

/**
 * If there is not already a delayed warp, schedule one. The source node is
 * based on the warp operation and sometimes Mario's used object.
 * Return the time left until the delayed warp is initiated.
 */
s16 level_trigger_warp(struct MarioState *m, s32 warpOp) {
    s32 fadeMusic = TRUE;

    if (sDelayedWarpOp == WARP_OP_NONE) {
        m->invincTimer = -1;
        sDelayedWarpArg = WARP_FLAGS_NONE;
        sDelayedWarpOp = warpOp;

        switch (warpOp) {
            case WARP_OP_DEMO_NEXT:
            case WARP_OP_DEMO_END:
                sDelayedWarpTimer = 20;
                sSourceWarpNodeId = WARP_NODE_DEFAULT;
                gSavedCourseNum = COURSE_NONE;
                fadeMusic = FALSE;
                play_transition(WARP_TRANSITION_FADE_INTO_STAR, sDelayedWarpTimer, 0x00, 0x00, 0x00);
                break;

            case WARP_OP_CREDITS_END:
                sDelayedWarpTimer = 60;
                sSourceWarpNodeId = WARP_NODE_DEFAULT;
                fadeMusic = FALSE;
                gSavedCourseNum = COURSE_NONE;
                play_transition(WARP_TRANSITION_FADE_INTO_COLOR, sDelayedWarpTimer, 0x00, 0x00, 0x00);
                break;

            case WARP_OP_STAR_EXIT:
                sDelayedWarpTimer = 32;
                sSourceWarpNodeId = WARP_NODE_DEFAULT;
                gSavedCourseNum = COURSE_NONE;
                play_transition(WARP_TRANSITION_FADE_INTO_MARIO, sDelayedWarpTimer, 0x00, 0x00, 0x00);
                break;

            case WARP_OP_DEATH:
#ifdef ENABLE_LIVES
                if (m->numLives == 0) {
                    sDelayedWarpOp = WARP_OP_GAME_OVER;
                }
#endif
                sDelayedWarpTimer = 48;
                sSourceWarpNodeId = WARP_NODE_DEATH;
                play_transition(WARP_TRANSITION_FADE_INTO_BOWSER, sDelayedWarpTimer, 0x00, 0x00, 0x00);
                play_sound(SOUND_MENU_BOWSER_LAUGH, gGlobalSoundSource);
#ifdef PREVENT_DEATH_LOOP
                m->isDead = TRUE;
#endif
                break;

            case WARP_OP_WARP_FLOOR:
                if ((m->floor) && (m->floor->force & 0xFF)) {
                    sSourceWarpNodeId = m->floor->force & 0xFF;
                } else {
                    sSourceWarpNodeId = WARP_NODE_WARP_FLOOR;
                    if (area_get_warp_node(sSourceWarpNodeId) == NULL) {
#ifdef ENABLE_LIVES
                        if (m->numLives == 0) {
                            sDelayedWarpOp = WARP_OP_GAME_OVER;
                        } else {
                            sSourceWarpNodeId = WARP_NODE_DEATH;
                        }
#else
                        sSourceWarpNodeId = WARP_NODE_DEATH;
#endif
                    }                    
                }

                sDelayedWarpTimer = 20;
                play_transition(WARP_TRANSITION_FADE_INTO_CIRCLE, sDelayedWarpTimer, 0x00, 0x00, 0x00);
                break;

            case WARP_OP_LOOK_UP: // enter totwc
                sDelayedWarpTimer = 30;
                sSourceWarpNodeId = WARP_NODE_LOOK_UP;
                play_transition(WARP_TRANSITION_FADE_INTO_COLOR, sDelayedWarpTimer, 0xFF, 0xFF, 0xFF);
                play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
                break;

            case WARP_OP_SPIN_SHRINK: // bbh enter
                sDelayedWarpTimer = 30;
                sSourceWarpNodeId = GET_BPARAM2(m->usedObj->oBehParams);
                play_transition(WARP_TRANSITION_FADE_INTO_COLOR, sDelayedWarpTimer, 0xFF, 0xFF, 0xFF);
                break;

            case WARP_OP_TELEPORT:
                sDelayedWarpTimer = 20;
                sSourceWarpNodeId = GET_BPARAM2(m->usedObj->oBehParams);
                fadeMusic = !music_unchanged_through_warp(sSourceWarpNodeId);
                play_transition(WARP_TRANSITION_FADE_INTO_COLOR, sDelayedWarpTimer, 0xFF, 0xFF, 0xFF);
                break;

            case WARP_OP_WARP_DOOR:
                sDelayedWarpTimer = 20;
                sDelayedWarpArg = m->actionArg;
                sSourceWarpNodeId = GET_BPARAM2(m->usedObj->oBehParams);
                fadeMusic = !music_unchanged_through_warp(sSourceWarpNodeId);
                play_transition(WARP_TRANSITION_FADE_INTO_CIRCLE, sDelayedWarpTimer, 0x00, 0x00, 0x00);
                break;

            case WARP_OP_WARP_OBJECT:
                sDelayedWarpTimer = 20;
                sSourceWarpNodeId = GET_BPARAM2(m->usedObj->oBehParams);
                fadeMusic = !music_unchanged_through_warp(sSourceWarpNodeId);
                play_transition(WARP_TRANSITION_FADE_INTO_STAR, sDelayedWarpTimer, 0x00, 0x00, 0x00);
                break;

            case WARP_OP_CREDITS_START:
                sDelayedWarpTimer = 30;
                play_transition(WARP_TRANSITION_FADE_INTO_COLOR, sDelayedWarpTimer, 0x00, 0x00, 0x00);
                break;

            case WARP_OP_CREDITS_NEXT:
                if (gCurrCreditsEntry == &sCreditsSequence[0]) {
                    sDelayedWarpTimer = 60;
                    play_transition(WARP_TRANSITION_FADE_INTO_COLOR, sDelayedWarpTimer, 0x00, 0x00, 0x00);
                } else {
                    sDelayedWarpTimer = 20;
                    play_transition(WARP_TRANSITION_FADE_INTO_COLOR, sDelayedWarpTimer, 0x00, 0x00, 0x00);
                }
                fadeMusic = FALSE;
                break;
        }

        if (pizza_time) {
            fadeMusic = FALSE;
        }

        if (fadeMusic && gCurrDemoInput == NULL) {
            fadeout_music((3 * sDelayedWarpTimer / 2) * 8 - 2);
        }
    }

    return sDelayedWarpTimer;
}

/**
 * If a delayed warp is ready, initiate it.
 */
void initiate_delayed_warp(void) {
    struct ObjectWarpNode *warpNode;
    s32 destWarpNode;

#ifdef PUPPYPRINT_DEBUG
    if (gPuppyWarp) {
        initiate_warp(gPuppyWarp, gPuppyWarpArea, 0x0A, 0);
    }
#endif

    if (sDelayedWarpOp != WARP_OP_NONE && --sDelayedWarpTimer == 0) {
        reset_dialog_render_state();

        if (gDebugLevelSelect && (sDelayedWarpOp & WARP_OP_TRIGGERS_LEVEL_SELECT)) {
            warp_special(WARP_SPECIAL_LEVEL_SELECT);
        } else if (gCurrDemoInput != NULL) {
            if (sDelayedWarpOp == WARP_OP_DEMO_END) {
                warp_special(WARP_SPECIAL_INTRO_SPLASH_SCREEN);
            } else {
                warp_special(WARP_SPECIAL_MARIO_HEAD_REGULAR);
            }
        } else {
            switch (sDelayedWarpOp) {
                case WARP_OP_GAME_OVER:
                    save_file_reload();
                    warp_special(WARP_SPECIAL_MARIO_HEAD_DIZZY);
                    break;

                case WARP_OP_CREDITS_END:
                    warp_special(WARP_SPECIAL_ENDING);
                    sound_banks_enable(SEQ_PLAYER_SFX, SOUND_BANKS_ALL & ~SOUND_BANKS_DISABLED_AFTER_CREDITS);
                    break;

                case WARP_OP_DEMO_NEXT:
                    warp_special(WARP_SPECIAL_MARIO_HEAD_REGULAR);
                    break;

                case WARP_OP_CREDITS_START:
                    gCurrCreditsEntry = &sCreditsSequence[0];
                    initiate_warp(gCurrCreditsEntry->levelNum, gCurrCreditsEntry->areaIndex,
                                  WARP_NODE_CREDITS_START, WARP_FLAGS_NONE);
                    break;

                case WARP_OP_CREDITS_NEXT:
                    sound_banks_disable(SEQ_PLAYER_SFX, SOUND_BANKS_ALL);

                    gCurrCreditsEntry++;
                    gCurrActNum = gCurrCreditsEntry->actNum & 0x07;
                    if ((gCurrCreditsEntry + 1)->levelNum == LEVEL_NONE) {
                        destWarpNode = WARP_NODE_CREDITS_END;
                    } else {
                        destWarpNode = WARP_NODE_CREDITS_NEXT;
                    }

                    initiate_warp(gCurrCreditsEntry->levelNum, gCurrCreditsEntry->areaIndex, destWarpNode, WARP_FLAGS_NONE);
                    change_ability(gCurrCreditsEntry->abilityid);
                    break;

                case WARP_OP_DEATH:
                    milk_drunk = FALSE;
                    p_rank_challenge_enabled = FALSE;
                    pizza_time = FALSE;

                default:
                    warpNode = area_get_warp_node(sSourceWarpNodeId);

                    initiate_warp(warpNode->node.destLevel & 0x7F, warpNode->node.destArea,
                                  warpNode->node.destNode, sDelayedWarpArg);

                    check_if_should_set_warp_checkpoint(&warpNode->node);
                    if (sWarpDest.type != WARP_TYPE_CHANGE_LEVEL) {
                        level_set_transition(2, NULL);
                    }
                    break;
            }
        }
    }
}

void update_hud_values(void) {
    if (gCurrCreditsEntry == NULL) {
        s16 numHealthWedges = gMarioState->health > 0 ? gMarioState->health >> 8 : 0;

#ifdef BREATH_METER
        s16 numBreathWedges = gMarioState->breath > 0 ? gMarioState->breath >> 8 : 0;
#endif
        COND_BIT((gCurrCourseNum >= COURSE_MIN), gHudDisplay.flags, HUD_DISPLAY_FLAG_COIN_COUNT);

        if (gHudDisplay.coins < gMarioState->numCoins) {
            if (gGlobalTimer & 1) {
                u32 coinSound;
                if (gMarioState->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER)) {
                    coinSound = SOUND_GENERAL_COIN_WATER;
                } else {
                    coinSound = SOUND_GENERAL_COIN;
                }

                gHudDisplay.coins++;
                play_sound(coinSound, gMarioState->marioObj->header.gfx.cameraToObject);
            }
        }

#ifdef ENABLE_LIVES
        if (gMarioState->numLives > MAX_NUM_LIVES) {
            gMarioState->numLives = MAX_NUM_LIVES;
        }
#endif

        if (gMarioState->numCoins > MAX_NUM_COINS) {
            gMarioState->numCoins = MAX_NUM_COINS;
        }

        if (gHudDisplay.coins > MAX_NUM_COINS) {
            gHudDisplay.coins = MAX_NUM_COINS;
        }

        gHudDisplay.stars = gMarioState->numStars;
        gHudDisplay.lives = gMarioState->numLives;
        gHudDisplay.keys = gMarioState->numKeys;

        if (numHealthWedges > gHudDisplay.wedges) {
            play_sound(SOUND_MENU_POWER_METER, gGlobalSoundSource);
        }
        gHudDisplay.wedges = numHealthWedges;

        COND_BIT((gMarioState->hurtCounter > 0), gHudDisplay.flags, HUD_DISPLAY_FLAG_EMPHASIZE_POWER);
#ifdef BREATH_METER
        gHudDisplay.breath = numBreathWedges;
        COND_BIT((gMarioState->breath > 0), gHudDisplay.flags, HUD_DISPLAY_FLAG_BREATH_METER);
#endif
    }
}

/**
 * Update objects, HUD, and camera. This update function excludes things like
 * endless staircase, warps, pausing, etc. This is used when entering a painting,
 * presumably to allow painting and camera updating while avoiding triggering the
 * warp twice.
 */
void basic_update(void) {
    area_update_objects();
    update_hud_values();
#ifdef PUPPYLIGHTS
    delete_lights();
#endif

    if (gCurrentArea != NULL) {
        update_camera(gCurrentArea->camera);
    }
}

s32 play_mode_normal(void) {
#ifndef DISABLE_DEMO
    if (gCurrDemoInput != NULL) {
        print_intro_text();
        if (gPlayer1Controller->buttonPressed & END_DEMO) {
            level_trigger_warp(gMarioState, gCurrLevelNum == LEVEL_PSS ? WARP_OP_DEMO_END : WARP_OP_DEMO_NEXT);
        } else if (!gWarpTransition.isActive && sDelayedWarpOp == WARP_OP_NONE
                   && (gPlayer1Controller->buttonPressed & START_BUTTON)) {
            level_trigger_warp(gMarioState, WARP_OP_DEMO_NEXT);
        }
    }
#endif

    warp_area();
    check_instant_warp();

#ifdef PUPPYPRINT_DEBUG
#ifdef BETTER_REVERB
    if (sPPDebugPage != PUPPYPRINT_PAGE_RAM && sPPDebugPage != PUPPYPRINT_PAGE_LEVEL_SELECT && sPPDebugPage != PUPPYPRINT_PAGE_BETTER_REVERB) {
#else
    if (sPPDebugPage != PUPPYPRINT_PAGE_RAM && sPPDebugPage != PUPPYPRINT_PAGE_LEVEL_SELECT) {
#endif
        if (sTimerRunning && gHudDisplay.timer < 17999) {
            gHudDisplay.timer++;
        }
        area_update_objects();
    }
#else
    if (sTimerRunning && gHudDisplay.timer < 17999) {
        gHudDisplay.timer++;
    }
    area_update_objects();
#endif
    update_hud_values();
#ifdef PUPPYLIGHTS
    delete_lights();
#endif
    if (gCurrentArea != NULL) {
#ifdef PUPPYPRINT_DEBUG
#ifdef BETTER_REVERB
    if (sPPDebugPage != PUPPYPRINT_PAGE_RAM && sPPDebugPage != PUPPYPRINT_PAGE_LEVEL_SELECT && sPPDebugPage != PUPPYPRINT_PAGE_BETTER_REVERB) {
#else
    if (sPPDebugPage != PUPPYPRINT_PAGE_RAM && sPPDebugPage != PUPPYPRINT_PAGE_LEVEL_SELECT) {
#endif
            update_camera(gCurrentArea->camera);
        }
#else
        update_camera(gCurrentArea->camera);
#endif
    }

    initiate_painting_warp();
    initiate_delayed_warp();

    // If either initiate_painting_warp or initiate_delayed_warp initiated a
    // warp, change play mode accordingly.
    if (sCurrPlayMode == PLAY_MODE_NORMAL) {
        if (sWarpDest.type == WARP_TYPE_CHANGE_LEVEL) {
            set_play_mode(PLAY_MODE_CHANGE_LEVEL);
        } else if (sTransitionTimer != 0) {
            set_play_mode(PLAY_MODE_CHANGE_AREA);
        } else if (pressed_pause()) {
            lower_background_noise(1);
#if ENABLE_RUMBLE
            cancel_rumble();
#endif
            gCameraMovementFlags |= CAM_MOVE_PAUSE_SCREEN;
            set_play_mode(PLAY_MODE_PAUSED);
        }
    }
    
    return FALSE;
}

s32 play_mode_paused(void) {
    if (gMenuOptSelectIndex == MENU_OPT_NONE) {
        set_menu_mode(MENU_MODE_RENDER_PAUSE_SCREEN);
    } else if (gMenuOptSelectIndex == MENU_OPT_DEFAULT) {
        raise_background_noise(1);
        gCameraMovementFlags &= ~CAM_MOVE_PAUSE_SCREEN;
        set_play_mode(PLAY_MODE_NORMAL);
#ifndef DISABLE_EXIT_COURSE
    } else { // MENU_OPT_EXIT_COURSE
        if (gDebugLevelSelect) {
            fade_into_special_warp(WARP_SPECIAL_LEVEL_SELECT, 1);
        } else {
#ifdef DEATH_ON_EXIT_COURSE
            raise_background_noise(1);
            gCameraMovementFlags &= ~CAM_MOVE_PAUSE_SCREEN;
            set_play_mode(PLAY_MODE_NORMAL);
            level_trigger_warp(gMarioState, WARP_OP_DEATH);
#else
            initiate_warp(LEVEL_CASTLE, 0x01, get_hub_return_id(hub_level_current_index), WARP_FLAGS_NONE);
            fade_into_special_warp(WARP_SPECIAL_NONE, 0);
            gSavedCourseNum = COURSE_NONE;
#endif
        }

        gCameraMovementFlags &= ~CAM_MOVE_PAUSE_SCREEN;
#endif
    }

    return FALSE;
}

/**
 * Debug mode that lets you frame advance by pressing D-pad down. Unfortunately
 * it uses the pause camera, making it basically unusable in most levels.
 */
s32 play_mode_frame_advance(void) {
    if (gPlayer1Controller->buttonPressed & D_JPAD) {
        gCameraMovementFlags &= ~CAM_MOVE_PAUSE_SCREEN;
        play_mode_normal();
    } else if (gPlayer1Controller->buttonPressed & START_BUTTON) {
        gCameraMovementFlags &= ~CAM_MOVE_PAUSE_SCREEN;
        raise_background_noise(1);
        set_play_mode(PLAY_MODE_NORMAL);
    } else {
        gCameraMovementFlags |= CAM_MOVE_PAUSE_SCREEN;
    }

    return FALSE;
}

/**
 * Set the transition, which is a period of time after the warp is initiated
 * but before it actually occurs. If updateFunction is not NULL, it will be
 * called each frame during the transition.
 */
void level_set_transition(s16 length, void (*updateFunction)()) {
    sTransitionTimer = length;
    sTransitionUpdate = updateFunction;
}

/**
 * Play the transition and then return to normal play mode.
 */
s32 play_mode_change_area(void) {
    // sm64ex-alo
    // Change function to have similar change_level defines
    if (sTransitionUpdate != NULL) {
        sTransitionUpdate(&sTransitionTimer);
    }

    if (--sTransitionTimer == -1) {
        update_camera(gCurrentArea->camera);
        sTransitionTimer = 0;
        sTransitionUpdate = NULL;
        set_play_mode(PLAY_MODE_NORMAL);
    }

    return FALSE;
}

/**
 * Play the transition and then return to normal play mode.
 */
s32 play_mode_change_level(void) {
    milk_drunk = FALSE;
    p_rank_challenge_enabled = FALSE;
    pizza_time = FALSE;

    if (sTransitionUpdate != NULL) {
        sTransitionUpdate(&sTransitionTimer);
    }

    if (--sTransitionTimer == -1) {
        gHudDisplay.flags = HUD_DISPLAY_NONE;
        sTransitionTimer = 0;
        sTransitionUpdate = NULL;

        if (sWarpDest.type != WARP_TYPE_NOT_WARPING) {
            return sWarpDest.levelNum;
        } else {
            return sSpecialWarpDest;
        }
    }

    return FALSE;
}

/**
 * Unused play mode. Doesn't call transition update and doesn't reset transition at the end.
 */
UNUSED static s32 play_mode_unused(void) {
    if (--sTransitionTimer == -1) {
        gHudDisplay.flags = HUD_DISPLAY_NONE;

        if (sWarpDest.type != WARP_TYPE_NOT_WARPING) {
            return sWarpDest.levelNum;
        } else {
            return sSpecialWarpDest;
        }
    }

    return FALSE;
}

s32 update_level(void) {
    s32 changeLevel = FALSE;

    switch (sCurrPlayMode) {
        case PLAY_MODE_NORMAL:
            changeLevel = play_mode_normal(); // Hopefully Fast64 doesn't overwrite this
            
            if (ability_chronos_frame_can_progress()) {
                scroll_textures();
            }
            break;
        case PLAY_MODE_PAUSED:
            changeLevel = play_mode_paused();
            break;
        case PLAY_MODE_CHANGE_AREA:
            changeLevel = play_mode_change_area();
            break;
        case PLAY_MODE_CHANGE_LEVEL:
            changeLevel = play_mode_change_level();
            break;
        case PLAY_MODE_FRAME_ADVANCE:
            changeLevel = play_mode_frame_advance();
            break;
    }

    if (changeLevel) {
        reset_volume();
        enable_background_sound();
    }

    return changeLevel;
}

s32 init_level(void) {
    s32 fadeFromColor = FALSE;
#ifdef PUPPYPRINT_DEBUG
    OSTime first = osGetTime();
#endif

    set_play_mode(PLAY_MODE_NORMAL);

    aku_invincibility = 0;

    sDelayedWarpOp = WARP_OP_NONE;
    sTransitionTimer = 0;
    sSpecialWarpDest = WARP_SPECIAL_NONE;

    g100CoinStarSpawned = FALSE;

    switch(gCurrLevelNum) {
        case LEVEL_CASTLE:
            hub_level_current_index = HUBLEVEL_HUB;
            break;
        case LEVEL_BOWSER_COURSE:
            hub_level_current_index = HUBLEVEL_BOWSER;
            break;
        case LEVEL_G:
            hub_level_current_index = HUBLEVEL_C1;
            break;
    }

    // NOTE: gStarModelLastCollected reset here as a safety to prevent possible UB if assigned a model used
    // in a non-global group. This checked can be removed as needed.
    if (gStarModelLastCollected != MODEL_BOWSER_KEY
#ifdef STAR_DANCE_USES_STARS_MODEL
         || gStarModelLastCollected != MODEL_TRANSPARENT_STAR
#endif
    ) {
        gStarModelLastCollected = MODEL_STAR;
    }

    if (gCurrCreditsEntry == NULL) {
        gHudDisplay.flags = HUD_DISPLAY_DEFAULT;
    } else {
        gHudDisplay.flags = HUD_DISPLAY_NONE;
    }

    sTimerRunning = FALSE;

    if (sWarpDest.type != WARP_TYPE_NOT_WARPING) {
        if (sWarpDest.nodeId >= WARP_NODE_CREDITS_MIN) {
            warp_credits();
        } else {
            warp_level();
        }
    } else {
        if (gPlayerSpawnInfos[0].areaIndex >= 0) {
            load_mario_area();
            init_mario();
        }

        if (gCurrentArea != NULL) {
            reset_camera(gCurrentArea->camera);

#ifdef PEACH_SKIP
            if (gCurrDemoInput != NULL) {
                set_mario_action(gMarioState, ACT_IDLE, 0);
            } else if (!gDebugLevelSelect) {
                if (gMarioState->action != ACT_UNINITIALIZED) {
                    set_mario_action(gMarioState, ACT_IDLE, 0);
                }
            }
        }
#else
            if (gCurrDemoInput != NULL) {
                set_mario_action(gMarioState, ACT_IDLE, 0);
            } else if (!gDebugLevelSelect) {
                if (gMarioState->action != ACT_UNINITIALIZED) {
                    if (save_file_exists(gCurrSaveFileNum - 1)) {
                        set_mario_action(gMarioState, ACT_IDLE, 0);
                    } else {
                        set_mario_action(gMarioState, ACT_INTRO_CUTSCENE, 0);
                        fadeFromColor = TRUE;
                    }
                }
            }
        }
#endif
        //if (fadeFromColor) {
            play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 0x10, 0xFF, 0xFF, 0xFF);
        //} else {
        //    play_transition(WARP_TRANSITION_FADE_FROM_STAR, 0x10, 0xFF, 0xFF, 0xFF);
        //}

        if (gCurrDemoInput == NULL) {
#ifdef BETTER_REVERB
            gBetterReverbPresetValue = gCurrentArea->betterReverbPreset;
#endif
            set_background_music(gCurrentArea->musicParam, gCurrentArea->musicParam2, 0);
        }
    }
#if ENABLE_RUMBLE
    if (gCurrDemoInput == NULL) {
        cancel_rumble();
    }
#endif

    if (gMarioState->action == ACT_INTRO_CUTSCENE) {
        sound_banks_disable(SEQ_PLAYER_SFX, SOUND_BANKS_DISABLED_DURING_INTRO_CUTSCENE);
    }

#ifdef PUPPYLIGHTS
    puppylights_allocate();
#endif

    append_puppyprint_log("Level loaded in %d" PP_CYCLE_STRING ".", (s32)(PP_CYCLE_CONV(osGetTime() - first)));
    return TRUE;
}

/**
 * Initialize the current level if initOrUpdate is 0, or update the level if it is 1.
 */
s32 lvl_init_or_update(s16 initOrUpdate, UNUSED s32 unused) {
    return (initOrUpdate ? update_level() : init_level());
}

#if MULTILANG
void load_language_text(void) {
    switch (gInGameLanguage - 1) {
        case LANGUAGE_ENGLISH:
            load_segment_decompress(SEGMENT_EU_TRANSLATION, _translation_en_yay0SegmentRomStart, _translation_en_yay0SegmentRomEnd);
            break;
        case LANGUAGE_FRENCH:
            load_segment_decompress(SEGMENT_EU_TRANSLATION, _translation_fr_yay0SegmentRomStart, _translation_fr_yay0SegmentRomEnd);
            break;
        case LANGUAGE_GERMAN:
            load_segment_decompress(SEGMENT_EU_TRANSLATION, _translation_de_yay0SegmentRomStart, _translation_de_yay0SegmentRomEnd);
            break;
    }
}
#endif

s32 lvl_init_from_save_file(UNUSED s16 initOrUpdate, s32 levelNum) {
#if MULTILANG
    gInGameLanguage = eu_get_language()+1;
    load_language_text();
#endif
    sWarpDest.type = WARP_TYPE_NOT_WARPING;
    sDelayedWarpOp = WARP_OP_NONE;
#ifdef ENABLE_VANILLA_LEVEL_SPECIFIC_CHECKS
    gNeverEnteredCastle = !save_file_exists(gCurrSaveFileNum - 1);
#else
    gNeverEnteredCastle = 0;
#endif
    gCurrLevelNum = levelNum;
    gCurrCourseNum = COURSE_NONE;
    gSavedCourseNum = COURSE_NONE;
    gCurrCreditsEntry = NULL;
    gSpecialTripleJump = FALSE;

    init_mario_from_save_file();
    disable_warp_checkpoint();
    save_file_move_cap_to_default_location();
    select_mario_cam_mode();
    set_yoshi_as_not_dead();

    return levelNum;
}

s32 lvl_set_current_level(UNUSED s16 initOrUpdate, s32 levelNum) {
    s32 warpCheckpointActive = sWarpCheckpointActive;

    sWarpCheckpointActive = FALSE;
    gCurrLevelNum = levelNum;
    gCurrCourseNum = gLevelToCourseNumTable[levelNum - 1];
	if (gCurrLevelNum == LEVEL_BOWSER_COURSE) return 0;
	if (gCurrLevelNum == LEVEL_G) return 0;

    if (gCurrDemoInput != NULL || gCurrCreditsEntry != NULL || gCurrCourseNum == COURSE_NONE) {
        return FALSE;
    }

    if (gCurrLevelNum != LEVEL_BOWSER_1 && gCurrLevelNum != LEVEL_BOWSER_2 && gCurrLevelNum != LEVEL_BOWSER_3) {
        gMarioState->numCoins = 0;
        gHudDisplay.coins = 0;
        gCurrCourseStarFlags =
            save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(gCurrCourseNum));
    }

    if (gSavedCourseNum != gCurrCourseNum) {
        gSavedCourseNum = gCurrCourseNum;
        disable_warp_checkpoint();
    }

    if (gCurrCourseNum > COURSE_STAGES_MAX || warpCheckpointActive) {
        return FALSE;
    }

    return FALSE; // This hack has star select disabled.
    return !gDebugLevelSelect;
}

/**
 * Play the "thank you so much for to playing my game" sound.
 */
s32 lvl_play_the_end_screen_sound(UNUSED s16 initOrUpdate, UNUSED s32 levelNum) {
    play_sound(SOUND_MENU_THANK_YOU_PLAYING_MY_GAME, gGlobalSoundSource);
    return TRUE;
}