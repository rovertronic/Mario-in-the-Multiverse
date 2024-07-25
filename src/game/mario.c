#include <PR/ultratypes.h>

#include "sm64.h"
#include "area.h"
#include "audio/external.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "game_init.h"
#include "interaction.h"
#include "level_table.h"
#include "level_update.h"
#include "main.h"
#include "mario.h"
#include "mario_actions_airborne.h"
#include "mario_actions_automatic.h"
#include "mario_actions_cutscene.h"
#include "mario_actions_moving.h"
#include "mario_actions_object.h"
#include "mario_actions_stationary.h"
#include "mario_actions_submerged.h"
#include "mario_misc.h"
#include "mario_step.h"
#include "memory.h"
#include "object_fields.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "print.h"
#include "save_file.h"
#include "sound_init.h"
#include "rumble_init.h"
#include "ability.h"
#include "seq_ids.h"
#include "rigid_body.h"
#include "src/buffers/buffers.h"
#include "dialog_ids.h"
#include "cutscene_manager.h"

s16 check_water_height = -10000;
Bool8 have_splashed;
Bool8 bd_submerged;

u8 lastAbility = ABILITY_DEFAULT;
Bool8 toZeroMeter = FALSE;

/**************************************************
 *                    ANIMATIONS                  *
 **************************************************/

/**
 * Checks if Mario's animation has reached its end point.
 */
s32 is_anim_at_end(struct MarioState *m) {
    struct Object *marioObj = m->marioObj;

    return (marioObj->header.gfx.animInfo.animFrame + 1) == marioObj->header.gfx.animInfo.curAnim->loopEnd;
}

/**
 * Checks if Mario's animation has surpassed 2 frames before its end point.
 */
s32 is_anim_past_end(struct MarioState *m) {
    struct Object *marioObj = m->marioObj;

    return marioObj->header.gfx.animInfo.animFrame >= (marioObj->header.gfx.animInfo.curAnim->loopEnd - 2);
}

/**
 * Sets Mario's animation without any acceleration, running at its default rate.
 */
s16 set_mario_animation(struct MarioState *m, s32 targetAnimID) {
    struct Object *marioObj = m->marioObj;
    struct Animation *targetAnim = m->animList->bufTarget;

    if (load_patchable_table(m->animList, targetAnimID)) {
        targetAnim->values = (void *) VIRTUAL_TO_PHYSICAL((u8 *) targetAnim + (uintptr_t) targetAnim->values);
        targetAnim->index  = (void *) VIRTUAL_TO_PHYSICAL((u8 *) targetAnim + (uintptr_t) targetAnim->index);
    }

    if (marioObj->header.gfx.animInfo.animID != targetAnimID) {
        marioObj->header.gfx.animInfo.animID = targetAnimID;
        marioObj->header.gfx.animInfo.curAnim = targetAnim;
        marioObj->header.gfx.animInfo.animAccel = 0;
        marioObj->header.gfx.animInfo.animYTrans = m->animYTrans;

        if (targetAnim->flags & ANIM_FLAG_NO_ACCEL) {
            marioObj->header.gfx.animInfo.animFrame = targetAnim->startFrame;
        } else {
            if (targetAnim->flags & ANIM_FLAG_FORWARD) {
                marioObj->header.gfx.animInfo.animFrame = targetAnim->startFrame + 1;
            } else {
                marioObj->header.gfx.animInfo.animFrame = targetAnim->startFrame - 1;
            }
        }
    }

    return marioObj->header.gfx.animInfo.animFrame;
}

extern const struct Animation *const mario_anims[];

s16 set_custom_mario_animation(struct MarioState *m, s32 targetAnimID) {
    struct Object *o = m->marioObj;

    if (o->header.gfx.animInfo.animID != targetAnimID) {
        struct Animation **animPtrAddr = &mario_anims[targetAnimID];
        struct Animation **animSegmented = segmented_to_virtual(animPtrAddr);
        struct Animation *targetAnim = segmented_to_virtual(*animSegmented);

        o->header.gfx.animInfo.animID = targetAnimID;
        o->header.gfx.animInfo.curAnim = targetAnim;
        o->header.gfx.animInfo.animAccel = 0;
        o->header.gfx.animInfo.animYTrans = m->animYTrans;

        if (targetAnim->flags & ANIM_FLAG_NO_ACCEL) {
            o->header.gfx.animInfo.animFrame = targetAnim->startFrame;
        } else {
            if (targetAnim->flags & ANIM_FLAG_FORWARD) {
                o->header.gfx.animInfo.animFrame = targetAnim->startFrame + 1;
            } else {
                o->header.gfx.animInfo.animFrame = targetAnim->startFrame - 1;
            }
        }
    }

    return o->header.gfx.animInfo.animFrame;
}

s16 set_custom_mario_animation_with_accel(struct MarioState *m, s32 targetAnimID, s32 accel) {
    struct Object *o = m->marioObj;

    if (o->header.gfx.animInfo.animID != targetAnimID) {
        struct Animation **animPtrAddr = &mario_anims[targetAnimID];
        struct Animation **animSegmented = segmented_to_virtual(animPtrAddr);
        struct Animation *targetAnim = segmented_to_virtual(*animSegmented);

        o->header.gfx.animInfo.animID = targetAnimID;
        o->header.gfx.animInfo.curAnim = targetAnim;
        o->header.gfx.animInfo.animYTrans = m->animYTrans;

        if (targetAnim->flags & ANIM_FLAG_NO_ACCEL) {
            o->header.gfx.animInfo.animFrameAccelAssist = (targetAnim->startFrame << 0x10);
        } else {
            if (targetAnim->flags & ANIM_FLAG_FORWARD) {
                o->header.gfx.animInfo.animFrameAccelAssist = (targetAnim->startFrame << 0x10) + accel;
            } else {
                o->header.gfx.animInfo.animFrameAccelAssist = (targetAnim->startFrame << 0x10) - accel;
            }
        }

        o->header.gfx.animInfo.animFrame = (o->header.gfx.animInfo.animFrameAccelAssist >> 0x10);
    }

    o->header.gfx.animInfo.animAccel = accel;

    return o->header.gfx.animInfo.animFrame;
}

/**
 * Sets Mario's animation where the animation is sped up or
 * slowed down via acceleration.
 */
s16 set_mario_anim_with_accel(struct MarioState *m, s32 targetAnimID, s32 accel) {
    struct Object *marioObj = m->marioObj;
    struct Animation *targetAnim = m->animList->bufTarget;

    if (load_patchable_table(m->animList, targetAnimID)) {
        targetAnim->values = (void *) VIRTUAL_TO_PHYSICAL((u8 *) targetAnim + (uintptr_t) targetAnim->values);
        targetAnim->index = (void *) VIRTUAL_TO_PHYSICAL((u8 *) targetAnim + (uintptr_t) targetAnim->index);
    }

    if (marioObj->header.gfx.animInfo.animID != targetAnimID) {
        marioObj->header.gfx.animInfo.animID = targetAnimID;
        marioObj->header.gfx.animInfo.curAnim = targetAnim;
        marioObj->header.gfx.animInfo.animYTrans = m->animYTrans;

        if (targetAnim->flags & ANIM_FLAG_NO_ACCEL) {
            marioObj->header.gfx.animInfo.animFrameAccelAssist = (targetAnim->startFrame << 0x10);
        } else {
            if (targetAnim->flags & ANIM_FLAG_FORWARD) {
                marioObj->header.gfx.animInfo.animFrameAccelAssist = (targetAnim->startFrame << 0x10) + accel;
            } else {
                marioObj->header.gfx.animInfo.animFrameAccelAssist = (targetAnim->startFrame << 0x10) - accel;
            }
        }

        marioObj->header.gfx.animInfo.animFrame = (marioObj->header.gfx.animInfo.animFrameAccelAssist >> 0x10);
    }

    marioObj->header.gfx.animInfo.animAccel = accel;

    return marioObj->header.gfx.animInfo.animFrame;
}

/**
 * Sets the animation to a specific "next" frame from the frame given.
 */
void set_anim_to_frame(struct MarioState *m, s16 animFrame) {
    struct AnimInfo *animInfo = &m->marioObj->header.gfx.animInfo;
    struct Animation *curAnim = animInfo->curAnim;

    if (animInfo->animAccel) {
        if (curAnim->flags & ANIM_FLAG_FORWARD) {
            animInfo->animFrameAccelAssist = (animFrame << 0x10) + animInfo->animAccel;
        } else {
            animInfo->animFrameAccelAssist = (animFrame << 0x10) - animInfo->animAccel;
        }
    } else {
        if (curAnim->flags & ANIM_FLAG_FORWARD) {
            animInfo->animFrame = animFrame + 1;
        } else {
            animInfo->animFrame = animFrame - 1;
        }
    }
}

s32 is_anim_past_frame(struct MarioState *m, s16 animFrame) {
    s32 isPastFrame;
    s32 acceleratedFrame = animFrame << 0x10;
    struct AnimInfo *animInfo = &m->marioObj->header.gfx.animInfo;
    struct Animation *curAnim = animInfo->curAnim;

    if (animInfo->animAccel) {
        if (curAnim->flags & ANIM_FLAG_FORWARD) {
            isPastFrame =
                (animInfo->animFrameAccelAssist > acceleratedFrame)
                && (acceleratedFrame >= (animInfo->animFrameAccelAssist - animInfo->animAccel));
        } else {
            isPastFrame =
                (animInfo->animFrameAccelAssist < acceleratedFrame)
                && (acceleratedFrame <= (animInfo->animFrameAccelAssist + animInfo->animAccel));
        }
    } else {
        if (curAnim->flags & ANIM_FLAG_FORWARD) {
            isPastFrame = (animInfo->animFrame == (animFrame + 1));
        } else {
            isPastFrame = ((animInfo->animFrame + 1) == animFrame);
        }
    }

    return isPastFrame;
}

/**
 * Rotates the animation's translation into the global coordinate system
 * and returns the animation's flags.
 */
s16 find_mario_anim_flags_and_translation(struct Object *obj, s32 yaw, Vec3s translation) {
    f32 dx, dz;

    struct Animation *curAnim = (void *) obj->header.gfx.animInfo.curAnim;
    s16 animFrame = geo_update_animation_frame(&obj->header.gfx.animInfo, NULL);
    u16 *animIndex = segmented_to_virtual((void *) curAnim->index);
    s16 *animValues = segmented_to_virtual((void *) curAnim->values);

    f32 s = (f32) sins(yaw);
    f32 c = (f32) coss(yaw);

    dx = *(animValues + (retrieve_animation_index(animFrame, &animIndex))) / 4.0f;
    translation[1] = *(animValues + (retrieve_animation_index(animFrame, &animIndex))) / 4.0f;
    dz = *(animValues + (retrieve_animation_index(animFrame, &animIndex))) / 4.0f;

    translation[0] = ( dx * c) + (dz * s);
    translation[2] = (-dx * s) + (dz * c);

    return curAnim->flags;
}

/**
 * Updates Mario's position from his animation's translation.
 */
void update_mario_pos_for_anim(struct MarioState *m) {
    Vec3s translation;
    s16 flags;

    flags = find_mario_anim_flags_and_translation(m->marioObj, m->faceAngle[1], translation);

    if (flags & (ANIM_FLAG_HOR_TRANS | ANIM_FLAG_NO_TRANS)) {
        m->pos[0] += (f32) translation[0];
        m->pos[2] += (f32) translation[2];
    }

    if (flags & (ANIM_FLAG_VERT_TRANS | ANIM_FLAG_NO_TRANS)) {
        m->pos[1] += (f32) translation[1];
    }
}

/**
 * Finds the vertical translation from Mario's animation.
 */
s16 return_mario_anim_y_translation(struct MarioState *m) {
    Vec3s translation;
    find_mario_anim_flags_and_translation(m->marioObj, 0, translation);

    return translation[1];
}

/**************************************************
 *                      AUDIO                     *
 **************************************************/

/**
 * Plays a sound if if Mario doesn't have the flag being checked.
 */
void play_sound_if_no_flag(struct MarioState *m, u32 soundBits, u32 flags) {
    if (!(m->flags & flags)) {
        play_sound(soundBits, m->marioObj->header.gfx.cameraToObject);
        m->flags |= flags;
    }
}

/**
 * Plays a jump sound if one has not been played since the last action change.
 */
void play_mario_jump_sound(struct MarioState *m) {
    if (!(m->flags & MARIO_MARIO_SOUND_PLAYED)) {
        if (m->action == ACT_TRIPLE_JUMP) {
            play_sound(SOUND_MARIO_YAHOO_WAHA_YIPPEE + ((gAudioRandom % 5) << 16),
                       m->marioObj->header.gfx.cameraToObject);
        } else {
            play_sound(SOUND_MARIO_YAH_WAH_HOO + ((gAudioRandom % 3) << 16),
                       m->marioObj->header.gfx.cameraToObject);
        }
        m->flags |= MARIO_MARIO_SOUND_PLAYED;
    }
}

/**
 * Adjusts the volume/pitch of sounds from Mario's speed.
 */
void adjust_sound_for_speed(struct MarioState *m) {
    s32 absForwardVel = (m->forwardVel > 0.0f) ? m->forwardVel : -m->forwardVel;
    set_sound_moving_speed(SOUND_BANK_MOVING, (absForwardVel > 100) ? 100 : absForwardVel);
}

/**
 * Spawns particles if the step sound says to, then either plays a step sound or relevant other sound.
 */
void play_sound_and_spawn_particles(struct MarioState *m, u32 soundBits, u32 waveParticleType) {
    if (m->terrainSoundAddend == (SOUND_TERRAIN_WATER << 16)) {
        if(m->floor->type != SURFACE_TOXIC_INK){
            if (waveParticleType != 0) {
                m->particleFlags |= PARTICLE_SHALLOW_WATER_SPLASH;
            } else {
                m->particleFlags |= PARTICLE_SHALLOW_WATER_WAVE;
            }
        } else {
            m->particleFlags |= PARTICLE_PLUNGE_BUBBLE;
        }
    } else {
        if (m->terrainSoundAddend == (SOUND_TERRAIN_SAND << 16)) {
            m->particleFlags |= PARTICLE_DIRT;
        } else if (m->terrainSoundAddend == (SOUND_TERRAIN_SNOW << 16)) {
            m->particleFlags |= PARTICLE_SNOW;
        }
    }

    if ((m->flags & MARIO_METAL_CAP) || soundBits == SOUND_ACTION_UNSTUCK_FROM_GROUND
        || soundBits == SOUND_MARIO_PUNCH_HOO) {
        play_sound(soundBits, m->marioObj->header.gfx.cameraToObject);
    } else {
        play_sound(m->terrainSoundAddend + soundBits, m->marioObj->header.gfx.cameraToObject);
    }
}

/**
 * Plays an environmental sound if one has not been played since the last action change.
 */
void play_mario_action_sound(struct MarioState *m, u32 soundBits, u32 waveParticleType) {
    if (!(m->flags & MARIO_ACTION_SOUND_PLAYED)) {
        play_sound_and_spawn_particles(m, soundBits, waveParticleType);
        m->flags |= MARIO_ACTION_SOUND_PLAYED;
    }
}

/**
 * Plays a landing sound, accounting for metal cap.
 */
void play_mario_landing_sound(struct MarioState *m, u32 soundBits) {
    play_sound_and_spawn_particles(
        m, (m->flags & MARIO_METAL_CAP) ? SOUND_ACTION_METAL_LANDING : soundBits, 1);
}

/**
 * Plays a landing sound, accounting for metal cap. Unlike play_mario_landing_sound,
 * this function uses play_mario_action_sound, making sure the sound is only
 * played once per action.
 */
void play_mario_landing_sound_once(struct MarioState *m, u32 soundBits) {
    play_mario_action_sound(
        m, (m->flags & MARIO_METAL_CAP) ? SOUND_ACTION_METAL_LANDING : soundBits, 1);
}

/**
 * Plays a heavy landing (ground pound, etc.) sound, accounting for metal cap.
 */
void play_mario_heavy_landing_sound(struct MarioState *m, u32 soundBits) {
    play_sound_and_spawn_particles(
        m, (m->flags & MARIO_METAL_CAP) ? SOUND_ACTION_METAL_HEAVY_LANDING : soundBits, 1);
}

/**
 * Plays a heavy landing (ground pound, etc.) sound, accounting for metal cap.
 * Unlike play_mario_heavy_landing_sound, this function uses play_mario_action_sound,
 * making sure the sound is only played once per action.
 */
void play_mario_heavy_landing_sound_once(struct MarioState *m, u32 soundBits) {
    play_mario_action_sound(
        m, (m->flags & MARIO_METAL_CAP) ? SOUND_ACTION_METAL_HEAVY_LANDING : soundBits, 1);
}

/**
 * Plays action and Mario sounds relevant to what was passed into the function.
 */
void play_mario_sound(struct MarioState *m, s32 actionSound, s32 marioSound) {
    if (actionSound == SOUND_ACTION_TERRAIN_JUMP) {
        play_mario_action_sound(m, (m->flags & MARIO_METAL_CAP) ? (s32) SOUND_ACTION_METAL_JUMP
                                                                : (s32) SOUND_ACTION_TERRAIN_JUMP, 1);
    } else {
        play_sound_if_no_flag(m, actionSound, MARIO_ACTION_SOUND_PLAYED);
    }

    if (marioSound == 0) {
        play_mario_jump_sound(m);
    }

    if (marioSound != -1) {
        play_sound_if_no_flag(m, marioSound, MARIO_MARIO_SOUND_PLAYED);
    }
}

/**************************************************
 *                     ACTIONS                    *
 **************************************************/

/**
 * Sets Mario's other velocities from his forward speed.
 */
void mario_set_forward_vel(struct MarioState *m, f32 forwardVel) {
    m->forwardVel = forwardVel;

    m->slideVelX = sins(m->faceAngle[1]) * m->forwardVel;
    m->slideVelZ = coss(m->faceAngle[1]) * m->forwardVel;

    m->vel[0] = (f32) m->slideVelX;
    m->vel[2] = (f32) m->slideVelZ;
}

/**
 * Returns the slipperiness class of Mario's floor.
 */
s32 mario_get_floor_class(struct MarioState *m) {
    s32 floorClass;

    // The slide terrain type defaults to slide slipperiness.
    // This doesn't matter too much since normally the slide terrain
    // is checked for anyways.
    if ((m->area->terrainType & TERRAIN_MASK) == TERRAIN_SLIDE) {
        floorClass = SURFACE_CLASS_VERY_SLIPPERY;
    } else {
        floorClass = SURFACE_CLASS_DEFAULT;
    }

    if (m->floor != NULL) {
        switch (m->floor->type) {
            case SURFACE_NOT_SLIPPERY:
            case SURFACE_HARD_NOT_SLIPPERY:
            case SURFACE_SWITCH:
            case SURFACE_FORCE_SHADOW_NOSLIP:
                floorClass = SURFACE_CLASS_NOT_SLIPPERY;
                break;

            case SURFACE_SLIPPERY:
            case SURFACE_NOISE_SLIPPERY:
            case SURFACE_HARD_SLIPPERY:
            case SURFACE_NO_CAM_COL_SLIPPERY:
                floorClass = SURFACE_CLASS_SLIPPERY;
                break;

            case SURFACE_SUPER_SLIPPERY:
            case SURFACE_VERY_SLIPPERY:
            case SURFACE_ICE:
            case SURFACE_HARD_VERY_SLIPPERY:
            case SURFACE_NOISE_VERY_SLIPPERY_73:
            case SURFACE_NOISE_VERY_SLIPPERY_74:
            case SURFACE_NOISE_VERY_SLIPPERY:
            case SURFACE_NO_CAM_COL_VERY_SLIPPERY:
                floorClass = SURFACE_CLASS_VERY_SLIPPERY;
                break;
        }
    }

    // Crawling allows Mario to not slide on certain steeper surfaces.
    if (m->action == ACT_CRAWLING && m->floor->normal.y > 0.5f && floorClass == SURFACE_CLASS_DEFAULT) {
        floorClass = SURFACE_CLASS_NOT_SLIPPERY;
    }

    return floorClass;
}

// clang-format off
s8 sTerrainSounds[7][6] = {
    // default,              hard,                 slippery,
    // very slippery,        noisy default,        noisy slippery
    { SOUND_TERRAIN_DEFAULT, SOUND_TERRAIN_STONE,  SOUND_TERRAIN_GRASS,
      SOUND_TERRAIN_GRASS,   SOUND_TERRAIN_GRASS,  SOUND_TERRAIN_DEFAULT }, // TERRAIN_GRASS
    { SOUND_TERRAIN_STONE,   SOUND_TERRAIN_STONE,  SOUND_TERRAIN_STONE,
      SOUND_TERRAIN_STONE,   SOUND_TERRAIN_GRASS,  SOUND_TERRAIN_GRASS }, // TERRAIN_STONE
    { SOUND_TERRAIN_SNOW,    SOUND_TERRAIN_ICE,    SOUND_TERRAIN_SNOW,
      SOUND_TERRAIN_ICE,     SOUND_TERRAIN_STONE,  SOUND_TERRAIN_STONE }, // TERRAIN_SNOW
    { SOUND_TERRAIN_SAND,    SOUND_TERRAIN_STONE,  SOUND_TERRAIN_SAND,
      SOUND_TERRAIN_SAND,    SOUND_TERRAIN_STONE,  SOUND_TERRAIN_STONE }, // TERRAIN_SAND
    { SOUND_TERRAIN_SPOOKY,  SOUND_TERRAIN_SPOOKY, SOUND_TERRAIN_SPOOKY,
      SOUND_TERRAIN_SPOOKY,  SOUND_TERRAIN_STONE,  SOUND_TERRAIN_STONE }, // TERRAIN_SPOOKY
    { SOUND_TERRAIN_DEFAULT, SOUND_TERRAIN_STONE,  SOUND_TERRAIN_GRASS,
      SOUND_TERRAIN_ICE,     SOUND_TERRAIN_STONE,  SOUND_TERRAIN_ICE }, // TERRAIN_WATER
    { SOUND_TERRAIN_STONE,   SOUND_TERRAIN_STONE,  SOUND_TERRAIN_STONE,
      SOUND_TERRAIN_STONE,   SOUND_TERRAIN_ICE,    SOUND_TERRAIN_ICE }, // TERRAIN_SLIDE
};
// clang-format on

/**
 * Computes a value that should be added to terrain sounds before playing them.
 * This depends on surfaces and terrain.
 */
u32 mario_get_terrain_sound_addend(struct MarioState *m) {
    s16 floorSoundType;
    s16 terrainType = m->area->terrainType & TERRAIN_MASK;
    s32 ret = SOUND_TERRAIN_DEFAULT << 16;
    s32 floorType;

    if (m->floor != NULL) {
        floorType = m->floor->type;

        if (((gCurrLevelNum != LEVEL_LLL) && (m->floorHeight < (m->waterLevel - 10))) || (m->pos[1] < (check_water_height - 10) && m->pos[1] > (check_water_height - 200))) {
            // Water terrain sound, excluding LLL since it uses water in the volcano.
            ret = SOUND_TERRAIN_WATER << 16;
        } else if (SURFACE_IS_QUICKSAND(floorType)) {
            ret = SOUND_TERRAIN_SAND << 16;
        } else if (floorType == SURFACE_TOXIC_INK) {
            ret = SOUND_TERRAIN_WATER << 16;
        }else {
            switch (floorType) {
                default:
                    floorSoundType = 0;
                    break;

                case SURFACE_NOT_SLIPPERY:
                case SURFACE_HARD:
                case SURFACE_HARD_NOT_SLIPPERY:
                case SURFACE_SWITCH:
                    floorSoundType = 1;
                    break;

                case SURFACE_SLIPPERY:
                case SURFACE_HARD_SLIPPERY:
                case SURFACE_NO_CAM_COL_SLIPPERY:
                    floorSoundType = 2;
                    break;

                case SURFACE_SUPER_SLIPPERY:
                case SURFACE_VERY_SLIPPERY:
                case SURFACE_ICE:
                case SURFACE_HARD_VERY_SLIPPERY:
                case SURFACE_NOISE_VERY_SLIPPERY_73:
                case SURFACE_NOISE_VERY_SLIPPERY_74:
                case SURFACE_NOISE_VERY_SLIPPERY:
                case SURFACE_NO_CAM_COL_VERY_SLIPPERY:
                    floorSoundType = 3;
                    break;

                case SURFACE_NOISE_DEFAULT:
                    floorSoundType = 4;
                    break;

                case SURFACE_NOISE_SLIPPERY:
                    floorSoundType = 5;
                    break;
            }

            ret = sTerrainSounds[terrainType][floorSoundType] << 16;
        }
    }

    return ret;
}

/**
 * Determines if Mario is facing "downhill."
 */
s32 mario_facing_downhill(struct MarioState *m, s32 turnYaw) {
    // Forces Mario to do a belly slide rather than a butt slide when on a super slippery floor, no matter his angle, so that the player can't jump.
    if (m->floor && m->floor->type == SURFACE_SUPER_SLIPPERY)
        return FALSE;

    s16 faceAngleYaw = m->faceAngle[1];

    // This is never used in practice, as turnYaw is
    // always passed as zero.
    if (turnYaw && m->forwardVel < 0.0f) {
        faceAngleYaw += 0x8000;
    }

    faceAngleYaw = m->floorYaw - faceAngleYaw;

    return (-0x4000 < faceAngleYaw) && (faceAngleYaw < 0x4000);
}

/**
 * Determines if a surface is slippery based on the surface class.
 */
u32 mario_floor_is_slippery(struct MarioState *m) {
    f32 normY;

    if (((m->area->terrainType & TERRAIN_MASK) == TERRAIN_SLIDE  && m->floor->normal.y < COS1) || (m->floor->type == SURFACE_SUPER_SLIPPERY)) {
        return TRUE;
    }

    switch (mario_get_floor_class(m)) {
        case SURFACE_CLASS_VERY_SLIPPERY: normY = COS10; break;
        case SURFACE_CLASS_SLIPPERY:      normY = COS20; break;
        default:                          normY = COS38; break;
        case SURFACE_CLASS_NOT_SLIPPERY:  normY = 0.0f;  break;
    }

    return m->floor->normal.y <= normY;
}

/**
 * Determines if a surface is a slope based on the surface class.
 */
s32 mario_floor_is_slope(struct MarioState *m) {
    f32 normY;

    if (((m->area->terrainType & TERRAIN_MASK) == TERRAIN_SLIDE
        && m->floor->normal.y < COS1) || (m->floor->type == SURFACE_SUPER_SLIPPERY)) {
        return TRUE;
    }

    switch (mario_get_floor_class(m)) {
        case SURFACE_CLASS_VERY_SLIPPERY: normY = COS5;  break;
        case SURFACE_CLASS_SLIPPERY:      normY = COS10; break;
        default:                          normY = COS15; break;
        case SURFACE_CLASS_NOT_SLIPPERY:  normY = COS20; break;
    }

    return m->floor->normal.y <= normY;
}

/**
 * Determines if a surface is steep based on the surface class.
 */
s32 mario_floor_is_steep(struct MarioState *m) {
    f32 normY;
    if (m->floor->type == SURFACE_SUPER_SLIPPERY)
        return TRUE;

#ifdef JUMP_KICK_FIX
    if (m->floor->type == SURFACE_NOT_SLIPPERY) {
        return FALSE;
    }
#endif

    // Interestingly, this function does not check for the
    // slide terrain type. This means that steep behavior persists for
    // non-slippery and slippery surfaces.
    // This does not matter in vanilla game practice.
    if (!mario_facing_downhill(m, FALSE)) {
        switch (mario_get_floor_class(m)) {
            case SURFACE_CLASS_VERY_SLIPPERY: normY = COS15; break;
            case SURFACE_CLASS_SLIPPERY:      normY = COS20; break;
            default:                          normY = COS30; break;
            case SURFACE_CLASS_NOT_SLIPPERY:  normY = COS30; break;
        }

        return m->floor->normal.y <= normY;
    }

    return FALSE;
}

/**
 * Finds the floor height relative from Mario given polar displacement.
 */
f32 find_floor_height_relative_polar(struct MarioState *m, s16 angleFromMario, f32 distFromMario) {
    struct Surface *floor;

    f32 y = sins(m->faceAngle[1] + angleFromMario) * distFromMario;
    f32 x = coss(m->faceAngle[1] + angleFromMario) * distFromMario;

    return find_floor(m->pos[0] + y, m->pos[1] + 100.0f, m->pos[2] + x, &floor);
}

/**
 * Returns the slope of the floor based off points around Mario.
 */
s16 find_floor_slope(struct MarioState *m, s16 yawOffset) {
    struct Surface *floor = m->floor;
    f32 forwardFloorY, backwardFloorY;
    f32 forwardYDelta, backwardYDelta;
    s16 result;

    f32 x = sins(m->faceAngle[1] + yawOffset) * 5.0f;
    f32 z = coss(m->faceAngle[1] + yawOffset) * 5.0f;
#ifdef FAST_FLOOR_ALIGN
    if (absf(m->forwardVel) > FAST_FLOOR_ALIGN) {
        forwardFloorY  = get_surface_height_at_location(m->pos[0] + x, m->pos[2] + z, floor);
        backwardFloorY = get_surface_height_at_location(m->pos[0] - x, m->pos[2] - z, floor);
    } else {
        forwardFloorY  = find_floor(m->pos[0] + x, m->pos[1] + 100.0f, m->pos[2] + z, &floor);
        if (floor == NULL)  forwardFloorY = m->floorHeight; // handle OOB slopes
        backwardFloorY = find_floor(m->pos[0] - x, m->pos[1] + 100.0f, m->pos[2] - z, &floor);
        if (floor == NULL) backwardFloorY = m->floorHeight; // handle OOB slopes
    }
#else
    forwardFloorY  = find_floor(m->pos[0] + x, m->pos[1] + 100.0f, m->pos[2] + z, &floor);
    if (floor == NULL)  forwardFloorY = m->floorHeight; // handle OOB slopes
    backwardFloorY = find_floor(m->pos[0] - x, m->pos[1] + 100.0f, m->pos[2] - z, &floor);
    if (floor == NULL) backwardFloorY = m->floorHeight; // handle OOB slopes
#endif

    forwardYDelta = forwardFloorY - m->pos[1];
    backwardYDelta = m->pos[1] - backwardFloorY;

    if (sqr(forwardYDelta) < sqr(backwardYDelta)) {
        result = atan2s(5.0f, forwardYDelta);
    } else {
        result = atan2s(5.0f, backwardYDelta);
    }

    return result;
}

Bool32 set_mario_wall(struct MarioState *m, struct Surface *wall) {
    if (m->wall != wall) {
        m->wall = wall;
        if (m->wall != NULL) m->wallYaw = SURFACE_YAW(wall);
    }
    return (m->wall != NULL);
}

Bool32 set_mario_ceil(struct MarioState *m, struct Surface *ceil, f32 ceilHeight) {
    if (m->ceil != ceil) {
        m->ceil = ceil;
        if (m->ceil != NULL) m->ceilYaw = SURFACE_YAW(ceil);
    }
    m->ceilHeight = ceilHeight;
    return (m->ceil != NULL);
}

Bool32 set_mario_floor(struct MarioState *m, struct Surface *floor, f32 floorHeight) {
    if (m->floor != floor) {
        m->floor = floor;
        if (m->floor != NULL) m->floorYaw = SURFACE_YAW(floor);
    }
    m->floorHeight = floorHeight;
    return (m->floor != NULL);
}

/**
 * Adjusts Mario's camera and sound based on his action status.
 */
void update_mario_sound_and_camera(struct MarioState *m) {
    u32 action = m->action;
    s32 camPreset = m->area->camera->mode;

    if (action == ACT_FIRST_PERSON) {
        raise_background_noise(2);
        gCameraMovementFlags &= ~CAM_MOVE_C_UP_MODE;
        // Go back to the last camera mode
        set_camera_mode(m->area->camera, -1, 1);
    } else if (action == ACT_SLEEPING) {
        raise_background_noise(2);
    }

    if (!(action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER)) && (camPreset == DEEP_WATER_CAMERA_MODE || camPreset == WATER_SURFACE_CAMERA_MODE)) {
        set_camera_mode(m->area->camera, m->area->camera->defMode, 1);
    }
}

/**
 * Transitions Mario to a steep jump action.
 */
void set_steep_jump_action(struct MarioState *m) {
    m->marioObj->oMarioSteepJumpYaw = m->faceAngle[1];

    if (m->forwardVel > 0.0f) {
        //! ((s16)0x8000) has undefined behavior. Therefore, this downcast has
        // undefined behavior if m->floorYaw >= 0.
        s16 angleTemp = m->floorYaw + 0x8000;
        s16 faceAngleTemp = m->faceAngle[1] - angleTemp;

        f32 y = sins(faceAngleTemp) * m->forwardVel;
        f32 x = coss(faceAngleTemp) * m->forwardVel * 0.75f;

        m->forwardVel = sqrtf(sqr(y) + sqr(x));
        m->faceAngle[1] = atan2s(x, y) + angleTemp;
    }

    drop_and_set_mario_action(m, ACT_STEEP_JUMP, 0);
}

/**
 * Sets Mario's vertical speed from his forward speed.
 */
void set_mario_y_vel_based_on_fspeed(struct MarioState *m, f32 initialVelY, f32 multiplier) {
    // get_additive_y_vel_for_jumps is always 0 and a stubbed function.
    // It was likely trampoline related based on code location.
    m->vel[1] = initialVelY + get_additive_y_vel_for_jumps() + m->forwardVel * multiplier;

    if (m->squishTimer != 0 || m->quicksandDepth > 1.0f) {
        m->vel[1] *= 0.5f;
    }
}

/**
 * Transitions for a variety of airborne actions.
 */
u32 set_mario_action_airborne(struct MarioState *m, u32 action, u32 actionArg) {
    f32 forwardVel;

    if ((m->squishTimer != 0 || m->quicksandDepth >= 1.0f)
        && (action == ACT_DOUBLE_JUMP || action == ACT_TWIRLING)) {
        action = ACT_JUMP;
    }

    switch (action) {
        case ACT_DOUBLE_JUMP:
            set_mario_y_vel_based_on_fspeed(m, 52.0f, 0.25f);
            m->forwardVel *= 0.8f;
            break;

        case ACT_BACKFLIP:
            m->marioObj->header.gfx.animInfo.animID = -1;
            m->forwardVel = -16.0f;
            set_mario_y_vel_based_on_fspeed(m, 62.0f, 0.0f);
            break;

        case ACT_TRIPLE_JUMP:
            set_mario_y_vel_based_on_fspeed(m, 69.0f, 0.0f);
            m->forwardVel *= 0.8f;
            break;

        case ACT_FLYING_TRIPLE_JUMP:
            set_mario_y_vel_based_on_fspeed(m, 82.0f, 0.0f);
            break;

        case ACT_WATER_JUMP:
        case ACT_HOLD_WATER_JUMP:
            if (actionArg == 0) {
                set_mario_y_vel_based_on_fspeed(m, 42.0f, 0.0f);
            }
            break;

        case ACT_BURNING_JUMP:
            m->vel[1] = 31.5f;
            m->forwardVel = 8.0f;
            break;

        case ACT_RIDING_SHELL_JUMP:
            set_mario_y_vel_based_on_fspeed(m, 42.0f, 0.25f);
            break;

        case ACT_JUMP:
        case ACT_HOLD_JUMP:
            m->marioObj->header.gfx.animInfo.animID = -1;
            set_mario_y_vel_based_on_fspeed(m, 42.0f, 0.25f);
            m->forwardVel *= 0.8f;
            break;

        case ACT_WALL_KICK_AIR:
        case ACT_TOP_OF_POLE_JUMP:
            set_mario_y_vel_based_on_fspeed(m, 62.0f, 0.0f);
            if (m->forwardVel < 24.0f) {
                m->forwardVel = 24.0f;
            }
            m->wallKickTimer = 0;
            break;

        case ACT_SIDE_FLIP:
            set_mario_y_vel_based_on_fspeed(m, 62.0f, 0.0f);
            m->forwardVel = 8.0f;
            m->faceAngle[1] = m->intendedYaw;
            break;

        case ACT_STEEP_JUMP:
            m->marioObj->header.gfx.animInfo.animID = -1;
            set_mario_y_vel_based_on_fspeed(m, 42.0f, 0.25f);
            m->faceAngle[0] = -0x2000;
            break;

        case ACT_LAVA_BOOST:
            m->vel[1] = 84.0f;
            if (actionArg == 0) {
                m->forwardVel = 0.0f;
            }
            break;

        case ACT_DIVE:
        if (m->abilityId == ABILITY_CUTTER) {
            if ((forwardVel = m->forwardVel + 25.0f) > 58.0f) {
                forwardVel = 58.0f;
            }
            m->vel[1] -= 25.0f;
        }
        else {
            if ((forwardVel = m->forwardVel + 15.0f) > 48.0f) {
                forwardVel = 48.0f;
            }
        }
            mario_set_forward_vel(m, forwardVel);
            break;

        case ACT_LONG_JUMP:
            m->marioObj->header.gfx.animInfo.animID = -1;
            set_mario_y_vel_based_on_fspeed(m, 30.0f, 0.0f);
            m->marioObj->oMarioLongJumpIsSlow = m->forwardVel > 16.0f ? FALSE : TRUE;

            //! (BLJ's) This properly handles long jumps from getting forward speed with
            //  too much velocity, but misses backwards longs allowing high negative speeds.
            if ((m->forwardVel *= 1.5f) > 48.0f) {
                m->forwardVel = 48.0f;
            }
            break;

        case ACT_SLIDE_KICK:
            m->vel[1] = 12.0f;
            if (m->forwardVel < 32.0f) {
                m->forwardVel = 32.0f;
            }
            break;

        case ACT_JUMP_KICK:
        case ACT_CUTTER_THROW_AIR:
            m->vel[1] = 20.0f;
            break;
    }

    if (phasewalk_state == 2) {
        m->vel[1] *= 1.25f;
        play_sound(SOUND_GENERAL_CRAZY_BOX_BOING_FAST, m->marioObj->header.gfx.cameraToObject);
    }

    m->peakHeight = m->pos[1];
    m->flags |= MARIO_JUMPING;

    return action;
}

/**
 * Transitions for a variety of moving actions.
 */
u32 set_mario_action_moving(struct MarioState *m, u32 action, UNUSED u32 actionArg) {
    s16 floorClass = mario_get_floor_class(m);
    f32 forwardVel = m->forwardVel;
    f32 mag = MIN(m->intendedMag, 8.0f);

    switch (action) {
        case ACT_WALKING:
            if (floorClass != SURFACE_CLASS_VERY_SLIPPERY) {
                if (0.0f <= forwardVel && forwardVel < mag) {
                    m->forwardVel = mag;
                }
            }

            m->marioObj->oMarioWalkingPitch = 0;
            break;

        case ACT_HOLD_WALKING:
            if (0.0f <= forwardVel && forwardVel < mag / 2.0f) {
                m->forwardVel = mag / 2.0f;
            }
            break;

        case ACT_BEGIN_SLIDING:
            if (mario_facing_downhill(m, FALSE)) {
                action = ACT_BUTT_SLIDE;
            } else {
                action = ACT_STOMACH_SLIDE;
            }
            break;

        case ACT_HOLD_BEGIN_SLIDING:
            if (mario_facing_downhill(m, FALSE)) {
                action = ACT_HOLD_BUTT_SLIDE;
            } else {
                action = ACT_HOLD_STOMACH_SLIDE;
            }
            break;
    }

    return action;
}

/**
 * Transition for certain submerged actions, which is actually just the metal jump actions.
 */
u32 set_mario_action_submerged(struct MarioState *m, u32 action, UNUSED u32 actionArg) {
    if (action == ACT_METAL_WATER_JUMP || action == ACT_HOLD_METAL_WATER_JUMP) {
        m->vel[1] = 32.0f;
    }

    return action;
}

/**
 * Transitions for a variety of cutscene actions.
 */
u32 set_mario_action_cutscene(struct MarioState *m, u32 action, UNUSED u32 actionArg) {
    switch (action) {
        case ACT_EMERGE_FROM_PIPE:
            m->vel[1] = 52.0f;
            break;

        case ACT_FALL_AFTER_STAR_GRAB:
            mario_set_forward_vel(m, 0.0f);
            break;

        case ACT_SPAWN_SPIN_AIRBORNE:
            mario_set_forward_vel(m, 2.0f);
            break;

        case ACT_SPECIAL_EXIT_AIRBORNE:
        case ACT_SPECIAL_DEATH_EXIT:
            m->vel[1] = 64.0f;
            break;
    }

    return action;
}

/**
 * Puts Mario into a given action, putting Mario through the appropriate
 * specific function if needed.
 */
u32 set_mario_action(struct MarioState *m, u32 action, u32 actionArg) {
    switch (action & ACT_GROUP_MASK) {
        case ACT_GROUP_MOVING:    action = set_mario_action_moving(   m, action, actionArg); break;
        case ACT_GROUP_AIRBORNE:  action = set_mario_action_airborne( m, action, actionArg); break;
        case ACT_GROUP_SUBMERGED: action = set_mario_action_submerged(m, action, actionArg); break;
        case ACT_GROUP_CUTSCENE:  action = set_mario_action_cutscene( m, action, actionArg); break;
    }

    // Resets the sound played flags, meaning Mario can play those sound types again.
    m->flags &= ~(MARIO_ACTION_SOUND_PLAYED | MARIO_MARIO_SOUND_PLAYED);

    if (!(m->action & ACT_FLAG_AIR)) {
        m->flags &= ~MARIO_FALL_SOUND_PLAYED;
    }

    // Initialize the action information.
    m->prevAction = m->action;
    m->action = action;
    m->actionArg = actionArg;
    m->actionState = 0;
    m->actionTimer = 0;

    return TRUE;
}

/**
 * Puts Mario into a specific jumping action from a landing action.
 */
s32 set_jump_from_landing(struct MarioState *m) {
    if (m->quicksandDepth >= 11.0f) {
        if (m->heldObj == NULL) {
            return set_mario_action(m, ACT_QUICKSAND_JUMP_LAND, 0);
        } else {
            return set_mario_action(m, ACT_HOLD_QUICKSAND_JUMP_LAND, 0);
        }
    }

    if (mario_floor_is_steep(m)) {
        set_steep_jump_action(m);
    } else {
        if ((m->doubleJumpTimer == 0) || (m->squishTimer != 0)) {
            set_mario_action(m, ACT_JUMP, 0);
        } else {
            switch (m->prevAction) {
                case ACT_JUMP_LAND:
                    set_mario_action(m, ACT_DOUBLE_JUMP, 0);
                    break;

                case ACT_FREEFALL_LAND:
                    set_mario_action(m, ACT_DOUBLE_JUMP, 0);
                    break;

                case ACT_SIDE_FLIP_LAND_STOP:
                    set_mario_action(m, ACT_DOUBLE_JUMP, 0);
                    break;

                case ACT_DOUBLE_JUMP_LAND:
                    // If Mario has a wing cap, he ignores the typical speed
                    // requirement for a triple jump.
                    if (m->flags & MARIO_WING_CAP) {
                        set_mario_action(m, ACT_FLYING_TRIPLE_JUMP, 0);
                    } else if (m->forwardVel > 20.0f) {
                        set_mario_action(m, ACT_TRIPLE_JUMP, 0);
                    } else {
                        set_mario_action(m, ACT_JUMP, 0);
                    }
                    break;

                default:
                    set_mario_action(m, ACT_JUMP, 0);
                    break;
            }
        }
    }

    m->doubleJumpTimer = 0;

    return TRUE;
}

/**
 * Puts Mario in a given action, as long as it is not overruled by
 * either a quicksand or steep jump.
 */
s32 set_jumping_action(struct MarioState *m, u32 action, u32 actionArg) {
    if (m->quicksandDepth >= 11.0f) {
        // Checks whether Mario is holding an object or not.
        if (m->heldObj == NULL) {
            return set_mario_action(m, ACT_QUICKSAND_JUMP_LAND, 0);
        } else {
            return set_mario_action(m, ACT_HOLD_QUICKSAND_JUMP_LAND, 0);
        }
    }

    if (mario_floor_is_steep(m)) {
        set_steep_jump_action(m);
    } else {
        set_mario_action(m, action, actionArg);
    }

    return TRUE;
}

/**
 * Drop anything Mario is holding and set a new action.
 */
s32 drop_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg) {
    mario_stop_riding_and_holding(m);

    return set_mario_action(m, action, actionArg);
}

/**
 * Increment Mario's hurt counter and set a new action.
 */
s32 hurt_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg, s16 hurtCounter) {
    m->hurtCounter = hurtCounter;

    return set_mario_action(m, action, actionArg);
}

/**
 * Checks a variety of inputs for common transitions between many different
 * actions. A common variant of the below function.
 */
s32 check_common_action_exits(struct MarioState *m) {
    if (m->input & INPUT_A_PRESSED) {
        return set_mario_action(m, ACT_JUMP, 0);
    }
    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }
    if (m->input & INPUT_NONZERO_ANALOG) {
        return set_mario_action(m, ACT_WALKING, 0);
    }
    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    return FALSE;
}

/**
 * Checks a variety of inputs for common transitions between many different
 * object holding actions. A holding variant of the above function.
 */
s32 check_common_hold_action_exits(struct MarioState *m) {
    if (m->input & INPUT_A_PRESSED     ) return set_mario_action(m, ACT_HOLD_JUMP,          0);
    if (m->input & INPUT_OFF_FLOOR     ) return set_mario_action(m, ACT_HOLD_FREEFALL,      0);
    if (m->input & INPUT_NONZERO_ANALOG) return set_mario_action(m, ACT_HOLD_WALKING,       0);
    if (m->input & INPUT_ABOVE_SLIDE   ) return set_mario_action(m, ACT_HOLD_BEGIN_SLIDING, 0);
    return FALSE;
}

/**
 * Transitions Mario from a submerged action to a walking action.
 */
s32 transition_submerged_to_walking(struct MarioState *m) {
    set_camera_mode(m->area->camera, m->area->camera->defMode, 1);

    vec3_zero(m->angleVel);

    if (m->heldObj == NULL) {
        return set_mario_action(m, ACT_WALKING, 0);
    } else {
        return set_mario_action(m, ACT_HOLD_WALKING, 0);
    }
}

/**
 * Transitions Mario from a submerged action to an airborne action.
 * You may want to change these actions to fit your hack
 */
s32 transition_submerged_to_airborne(struct MarioState *m) {
    set_camera_mode(m->area->camera, m->area->camera->defMode, 1);

    vec3_zero(m->angleVel);

    if (m->heldObj == NULL) {
        if (m->input & INPUT_A_DOWN) return set_mario_action(m, ACT_DIVE, 0);
        else return set_mario_action(m, ACT_FREEFALL, 0);
    } else {
        if (m->input & INPUT_A_DOWN) return set_mario_action(m, ACT_HOLD_JUMP, 0);
        else return set_mario_action(m, ACT_HOLD_FREEFALL, 0);
    }
}

/**
 * This is the transition function typically for entering a submerged action for a
 * non-submerged action. This also applies the water surface camera preset.
 */
s32 set_water_plunge_action(struct MarioState *m) {
    m->forwardVel = m->forwardVel / 4.0f;
    m->vel[1] = m->vel[1] / 2.0f;

#ifdef WATER_PLUNGE_UPWARP
    m->pos[1] = m->waterLevel - 100;
#endif

    m->faceAngle[2] = 0;

    vec3_zero(m->angleVel);

    if (!(m->action & ACT_FLAG_DIVING)) {
        m->faceAngle[0] = 0;
    }

    if (m->area->camera->mode != WATER_SURFACE_CAMERA_MODE) {
        set_camera_mode(m->area->camera, WATER_SURFACE_CAMERA_MODE, 1);
    }

    return set_mario_action(m, ACT_WATER_PLUNGE, 0);
}

/**
 * These are the scaling values for the x and z axis for Mario
 * when he is close to unsquishing.
 */
u8 sSquishScaleOverTime[16] = { 0x46, 0x32, 0x32, 0x3C, 0x46, 0x50, 0x50, 0x3C,
                                0x28, 0x14, 0x14, 0x1E, 0x32, 0x3C, 0x3C, 0x28 };

/**
 * Applies the squish to Mario's model via scaling.
 */
void squish_mario_model(struct MarioState *m) {
    if (m->squishTimer != 0xFF) {
        // If no longer squished, scale back to default.
        if (m->squishTimer == 0) {
            vec3f_set(m->marioObj->header.gfx.scale, 1.0f, 1.0f, 1.0f);
        }
        // If timer is less than 16, rubber-band Mario's size scale up and down.
        else if (m->squishTimer <= 16) {
            m->squishTimer -= 1;

            m->marioObj->header.gfx.scale[1] =
                1.0f - ((sSquishScaleOverTime[15 - m->squishTimer] * 0.6f) / 100.0f);
            m->marioObj->header.gfx.scale[0] =
                ((sSquishScaleOverTime[15 - m->squishTimer] * 0.4f) / 100.0f) + 1.0f;

            m->marioObj->header.gfx.scale[2] = m->marioObj->header.gfx.scale[0];
        } else {
            m->squishTimer -= 1;

            vec3f_set(m->marioObj->header.gfx.scale, 1.4f, 0.4f, 1.4f);
        }
    }
}

#ifdef VANILLA_DEBUG
/**
 * Debug function that prints floor normal, velocity, and action information.
 */
void debug_print_speed_action_normal(struct MarioState *m) {
    f32 steepness;
    f32 floor_nY;

    if (gShowDebugText) {
        steepness = sqrtf(sqr(m->floor->normal.x) + sqr(m->floor->normal.z));
        floor_nY = m->floor->normal.y;

        print_text_fmt_int(210, 88, "ANG %d", (atan2s(floor_nY, steepness) * 180.0f) / 32768.0f);

        print_text_fmt_int(210, 72, "SPD %d", m->forwardVel);

        // STA short for "status," the official action name via SMS map.
        print_text_fmt_int(210, 56, "STA %x", (m->action & ACT_ID_MASK));
    }
}
#endif

/**
 * Update the button inputs for Mario.
 */
void update_mario_button_inputs(struct MarioState *m) {
    if (m->controller->buttonPressed & A_BUTTON) m->input |= INPUT_A_PRESSED;
    if (m->controller->buttonDown    & A_BUTTON) m->input |= INPUT_A_DOWN;

    // Don't update for these buttons if squished.
    if (m->squishTimer == 0) {
        if (m->controller->buttonDown    & B_BUTTON) m->input |= INPUT_B_DOWN;
        if (m->controller->buttonPressed & B_BUTTON) m->input |= INPUT_B_PRESSED;
        if (m->controller->buttonDown    & Z_TRIG  ) m->input |= INPUT_Z_DOWN;
        if (m->controller->buttonPressed & Z_TRIG  ) m->input |= INPUT_Z_PRESSED;
    }

    if (m->input & INPUT_A_PRESSED) {
        m->framesSinceA = 0;
    } else if (m->framesSinceA < 0xFF) {
        m->framesSinceA++;
    }

    if (m->input & INPUT_B_PRESSED) {
        m->framesSinceB = 0;
    } else if (m->framesSinceB < 0xFF) {
        m->framesSinceB++;
    }
}

/**
 * Updates the joystick intended magnitude.
 */
void update_mario_joystick_inputs(struct MarioState *m) {
    struct Controller *controller = m->controller;
    f32 mag = ((controller->stickMag / 64.0f) * (controller->stickMag / 64.0f)) * 64.0f;

    f32 fake_stick_y = controller->stickY;
    if (is_2d_area()) {
        fake_stick_y = 0.0f;
    }

    if (m->squishTimer == 0) {
        m->intendedMag = mag / 2.0f;
    } else {
        m->intendedMag = mag / 8.0f;
    }

    if (m->intendedMag > 0.0f) {
        m->intendedYaw = atan2s(-fake_stick_y, controller->stickX) + m->area->camera->yaw;
        m->input |= INPUT_NONZERO_ANALOG;
    } else {
        m->intendedYaw = m->faceAngle[1];
    }

    if (is_2d_area()) {
        if (gPlayer1Controller->rawStickX > 0.0f) {
            m->intendedYaw = -0x4000;
        } else if (gPlayer1Controller->rawStickX < 0.0f) {
            m->intendedYaw = 0x4000;
        } else {
            m->intendedYaw = 0x4000;
            m->input &= ~INPUT_NONZERO_ANALOG;
        }
    }
}

/**
 * Resolves wall collisions, and updates a variety of inputs.
 */
void update_mario_geometry_inputs(struct MarioState *m) {
    f32 gasLevel;
    f32 ceilToFloorDist;

    if (gMarioState->action != ACT_SQUID) {
        f32_find_wall_collision(&m->pos[0], &m->pos[1], &m->pos[2], 60.0f, 50.0f);
        f32_find_wall_collision(&m->pos[0], &m->pos[1], &m->pos[2], 30.0f, 24.0f);
    }

    m->floorHeight = find_floor(m->pos[0], m->pos[1], m->pos[2], &m->floor);

    // If Mario is OOB, move his position to his graphical position (which was not updated)
    // and check for the floor there.
    // This can cause errant behavior when combined with astral projection,
    // since the graphical position was not Mario's previous location.
    if (m->floor == NULL) {
        vec3f_copy(m->pos, m->marioObj->header.gfx.pos);
        m->floorHeight = find_floor(m->pos[0], m->pos[1], m->pos[2], &m->floor);
    }

    m->ceilHeight = find_mario_ceil(m->pos, m->floorHeight, &m->ceil);
    gasLevel = find_poison_gas_level(m->pos[0], m->pos[2]);

    if (using_ability(ABILITY_BIG_DADDY)){
        check_water_height = find_water_level(m->pos[0], m->pos[2]);
        m->waterLevel = -10000;

        if (m->pos[1] < (check_water_height - 200)){
            m->particleFlags |= PARTICLE_BUBBLE;
        } 

        if (check_water_height > m->pos[1]){
            bd_submerged = TRUE;

            if (bd_submerged == TRUE && have_splashed == FALSE){
                m->particleFlags |= PARTICLE_WATER_SPLASH;
                play_sound(SOUND_ACTION_WATER_PLUNGE, m->marioObj->header.gfx.cameraToObject);
                have_splashed = TRUE;
            }
        } 

        if (bd_submerged == TRUE && check_water_height < m->pos[1]){
            m->particleFlags |= PARTICLE_WATER_SPLASH;
            play_sound(SOUND_ACTION_WATER_PLUNGE, m->marioObj->header.gfx.cameraToObject);
            bd_submerged = FALSE;
            have_splashed = FALSE;
        }
        
    } else {
        check_water_height = -10000;
        m->waterLevel = find_water_level(m->pos[0], m->pos[2]);
        bd_submerged = FALSE;
        have_splashed = FALSE;
    }

    if (m->floor != NULL) {
        m->floorYaw = atan2s(m->floor->normal.z, m->floor->normal.x);
        m->terrainSoundAddend = mario_get_terrain_sound_addend(m);

        if ((m->pos[1] > m->waterLevel - 40) && mario_floor_is_slippery(m)) {
            m->input |= INPUT_ABOVE_SLIDE;
        }

        if ((m->floor->flags & SURFACE_FLAG_DYNAMIC)
            || (m->ceil && m->ceil->flags & SURFACE_FLAG_DYNAMIC)) {
            ceilToFloorDist = m->ceilHeight - m->floorHeight;

            if ((0.0f <= ceilToFloorDist) && (ceilToFloorDist <= 150.0f)) {
                m->input |= INPUT_SQUISHED;
            }
        }

        if (m->pos[1] > m->floorHeight + 100.0f) {
            m->input |= INPUT_OFF_FLOOR;
        }

        if ((m->pos[1] < (m->waterLevel - 10)) || (m->pos[1] < (check_water_height - 10) && m->pos[1] > (check_water_height - 200))) {
            m->input |= INPUT_IN_WATER;
        }

        if (m->pos[1] < (gasLevel - 100.0f) || m->floor->type == SURFACE_TOXIC_INK) {
            m->input |= INPUT_IN_POISON_GAS;
        }

    } else {
        level_trigger_warp(m, WARP_OP_DEATH);
    }
}

/**
 * Handles Mario's input flags as well as a couple timers.
 */
void update_mario_inputs(struct MarioState *m) {
    m->particleFlags = PARTICLE_NONE;
    m->input = INPUT_NONE;
    m->collidedObjInteractTypes = m->marioObj->collidedObjInteractTypes;
    m->flags &= 0xFFFFFF;

#ifdef PUPPYCAM
    if (gPuppyCam.mode3Flags & PUPPYCAM_MODE3_ENTER_FIRST_PERSON || (gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_FREE && gPuppyCam.debugFlags & PUPPYDEBUG_LOCK_CONTROLS)) {
        m->input = INPUT_FIRST_PERSON;
        return;
    }
#endif

    if (!cm_cutscene_on) {
        update_mario_button_inputs(m);
        update_mario_joystick_inputs(m);
    }
    update_mario_geometry_inputs(m);
#ifdef VANILLA_DEBUG
    debug_print_speed_action_normal(m);
#endif
    if (gCameraMovementFlags & CAM_MOVE_C_UP_MODE) {
        if (m->action & ACT_FLAG_ALLOW_FIRST_PERSON) {
            m->input |= INPUT_FIRST_PERSON;
        } else {
            gCameraMovementFlags &= ~CAM_MOVE_C_UP_MODE;
        }
    }

    if (!(m->input & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED))) {
        m->input |= INPUT_IDLE;
    }

    // These 3 flags are defined by Bowser stomping attacks
    if (m->marioObj->oInteractStatus
        & (INT_STATUS_MARIO_STUNNED | INT_STATUS_MARIO_KNOCKBACK_DMG | INT_STATUS_MARIO_SHOCKWAVE)) {
        m->input |= INPUT_STOMPED;
    }

    // This function is located near other unused trampoline functions,
    // perhaps logically grouped here with the timers.
    stub_mario_step_1(m);

    if (m->wallKickTimer > 0) {
        m->wallKickTimer--;
    }

    if (m->doubleJumpTimer > 0) {
        m->doubleJumpTimer--;
    }
}

/**
 * Set's the camera preset for submerged action behaviors.
 */
void set_submerged_cam_preset_and_spawn_bubbles(struct MarioState *m) {
    f32 heightBelowWater;
    s16 camPreset;

    if ((m->action & ACT_GROUP_MASK) == ACT_GROUP_SUBMERGED) {
        heightBelowWater = (f32)(m->waterLevel - 80) - m->pos[1];
        camPreset = m->area->camera->mode;

        if (m->action & ACT_FLAG_METAL_WATER) {
#ifdef USE_COURSE_DEFAULT_MODE
            // Being metal and in the water uses the default camera mode
            if (camPreset != m->area->camera->defMode) {
                set_camera_mode(m->area->camera, m->area->camera->defMode, 1);
            }
#else
            if (camPreset != CAMERA_MODE_CLOSE) {
                set_camera_mode(m->area->camera, CAMERA_MODE_CLOSE, 1);
            }
#endif
        } else {
            if ((heightBelowWater > 800.0f) && (camPreset != DEEP_WATER_CAMERA_MODE)) {
                set_camera_mode(m->area->camera, DEEP_WATER_CAMERA_MODE, 1);
            }

            if ((heightBelowWater < 400.0f) && (camPreset != WATER_SURFACE_CAMERA_MODE)) {
                set_camera_mode(m->area->camera, WATER_SURFACE_CAMERA_MODE, 1);
            }

            // As long as Mario isn't drowning or at the top
            // of the water with his head out, spawn bubbles.
            if (!(m->action & ACT_FLAG_INTANGIBLE)) {
                if ((m->pos[1] < (f32)(m->waterLevel - 160)) || (m->faceAngle[0] < -0x800)) {
                    m->particleFlags |= PARTICLE_BUBBLE;
                }
            }
        }
    }
}

/**
 * Both increments and decrements Mario's HP.
 */
void update_mario_health(struct MarioState *m) {
    s32 terrainIsSnow;

    if (m->health >= 0x100) {
        // When already healing or hurting Mario, Mario's HP is not changed any more here.
        if (((u32) m->healCounter | (u32) m->hurtCounter) == 0) {
            if ((m->input & INPUT_IN_POISON_GAS) && !(m->action & ACT_FLAG_INTANGIBLE)) {
                if (!(m->flags & MARIO_METAL_CAP) && !gDebugLevelSelect) {
                    m->health -= 4;
                }
            } else {
                if ((m->action & ACT_FLAG_SWIMMING) && !(m->action & ACT_FLAG_INTANGIBLE)) {
                    terrainIsSnow = (m->area->terrainType & TERRAIN_MASK) == TERRAIN_SNOW;
#ifdef BREATH_METER
                    // when in snow terrains lose 3 health.
                    if ((m->pos[1] < (m->waterLevel - 140)) && terrainIsSnow) {
                        m->health -= 3;
                    }
#else
                    // When Mario is near the water surface, recover health (unless in snow),
                    // when in snow terrains lose 3 health.
                    // If using the debug level select, do not lose any HP to water.
                    if ((m->pos[1] >= (m->waterLevel - 140)) && !terrainIsSnow) {
                        m->health += 0x1A;
                    } else if (!gDebugLevelSelect) {
                        m->health -= (terrainIsSnow ? 3 : 1);
                    }
#endif
                }
            }
        }

        if (m->healCounter > 0) {
            m->health += 0x40;
            m->healCounter--;
        }
        if (m->hurtCounter > 0) {
            m->health -= 0x40;
            m->hurtCounter--;
        }

        if (m->health > 0x880) m->health = 0x880;
        if (m->health < 0x100) m->health = 0xFF;

#ifndef BREATH_METER
        // Play a noise to alert the player when Mario is close to drowning.
        if (((m->action & ACT_GROUP_MASK) == ACT_GROUP_SUBMERGED) && (m->health < 0x300)) {
            play_sound(SOUND_MOVING_ALMOST_DROWNING, gGlobalSoundSource);
#if ENABLE_RUMBLE
            if (gRumblePakTimer == 0) {
                gRumblePakTimer = 36;
                if (is_rumble_finished_and_queue_empty()) {
                    queue_rumble_data(3, 30);
                }
            }
        } else {
            gRumblePakTimer = 0;
#endif
        }
#endif
    }
}

#ifdef BREATH_METER
void update_mario_breath(struct MarioState *m) {
    if (m->breath >= 0x100 && m->health >= 0x100) {
        if (m->pos[1] < (m->waterLevel - 140) && !(m->flags & MARIO_METAL_CAP) && !(m->action & ACT_FLAG_INTANGIBLE)) {
            if (gCurrLevelNum == LEVEL_B){
                m->breath-=8;
            } else {
            m->breath--;
            }
            if (m->breath < 0x300) {
                // Play a noise to alert the player when Mario is close to drowning.
                play_sound(SOUND_MOVING_ALMOST_DROWNING, gGlobalSoundSource);
#if ENABLE_RUMBLE
                if (gRumblePakTimer == 0) {
                    gRumblePakTimer = 36;
                    if (is_rumble_finished_and_queue_empty()) {
                        queue_rumble_data(3, 30);
                    }
                }
            } else {
                gRumblePakTimer = 0;
#endif
            }
        } else if (!(m->input & INPUT_IN_POISON_GAS) && (bd_submerged == FALSE)) {
            m->breath += 0x1A;
        }
        if (m->breathCounter > 0) {
            m->breath += 0x40;
            m->breathCounter--;
        }
        if (m->breath > 0x880) m->breath = 0x880;
        if (m->breath < 0x100) {
            // If breath is "zero", set health to "zero"
            m->breath =  0xFF;
            m->health =  0xFF;
        }
    }
}
#endif

/**
 * Updates some basic info for camera usage.
 */
void update_mario_info_for_cam(struct MarioState *m) {
    m->marioBodyState->action = m->action;
    m->statusForCamera->action = m->action;

    vec3s_copy(m->statusForCamera->faceAngle, m->faceAngle);

    if (!(m->flags & MARIO_LEDGE_CLIMB_CAMERA)) {
        vec3f_copy(m->statusForCamera->pos, m->pos);
    }
}

/**
 * Resets Mario's model, done every time an action is executed.
 */
void mario_reset_bodystate(struct MarioState *m) {
    struct MarioBodyState *bodyState = m->marioBodyState;

    bodyState->capState = MARIO_HAS_DEFAULT_CAP_OFF;
    bodyState->eyeState = MARIO_EYES_BLINK;
    bodyState->handState = MARIO_HAND_FISTS;
    bodyState->modelState = 0;
    bodyState->wingFlutter = FALSE;

    m->flags &= ~MARIO_METAL_SHOCK;
}

/**
 * Adjusts Mario's graphical height for quicksand.
 */
void sink_mario_in_quicksand(struct MarioState *m) {
    struct Object *marioObj = m->marioObj;

    if (marioObj->header.gfx.throwMatrix) {
        (*marioObj->header.gfx.throwMatrix)[3][1] -= m->quicksandDepth;
    }

    marioObj->header.gfx.pos[1] -= m->quicksandDepth;
}

/**
 * Is a binary representation of the frames to flicker Mario's cap when the timer
 * is running out.
 * 0x4444449249255555
 *
 * Equals [1000]^5 . [100]^8 . [10]^9 . [1] in binary, which is
 * 100010001000100010001001001001001001001001001010101010101010101.
 */
u64 sCapFlickerFrames = 0b100010001000100010001001001001001001001001001010101010101010101;

/**
 * Updates the cap flags mainly based on the cap timer.
 */
u32 update_and_return_cap_flags(struct MarioState *m) {
    u32 flags = m->flags;
    u32 action;

    if (m->capTimer > 0) {
        action = m->action;

        if ((m->capTimer <= 60)
            || ((action != ACT_READING_AUTOMATIC_DIALOG) && (action != ACT_READING_NPC_DIALOG)
                && (action != ACT_READING_SIGN) && (action != ACT_IN_CANNON))) {
            m->capTimer -= 1;
        }

        if (m->capTimer == 0) {
            stop_cap_music();

            m->flags &= ~MARIO_SPECIAL_CAPS;
            if (!(m->flags & MARIO_CAPS)) {
                m->flags &= ~MARIO_CAP_ON_HEAD;
            }
        }

        if (m->capTimer == 60) {
            fadeout_cap_music();
        }

        // This code flickers the cap through a long binary string, increasing in how
        // common it flickers near the end.
        if ((m->capTimer < 64) && ((1ULL << m->capTimer) & sCapFlickerFrames)) {
            flags &= ~MARIO_SPECIAL_CAPS;
            if (!(flags & MARIO_CAPS)) {
                flags &= ~MARIO_CAP_ON_HEAD;
            }
        }
    }

    return flags;
}

/**
 * Updates the Mario's cap, rendering, and hitbox.
 */
void mario_update_hitbox_and_cap_model(struct MarioState *m) {
    struct MarioBodyState *bodyState = m->marioBodyState;
    s32 flags = update_and_return_cap_flags(m);

    if (flags & MARIO_VANISH_CAP) {
        bodyState->modelState = MODEL_STATE_NOISE_ALPHA;
    }

    if (flags & (MARIO_METAL_CAP | MARIO_METAL_SHOCK)) {
        bodyState->modelState |= MODEL_STATE_METAL;
    }

    //! (Pause buffered hitstun) Since the global timer increments while paused,
    //  this can be paused through to give continual invisibility. This leads to
    //  no interaction with objects.
    if ((m->invincTimer >= 3) && (gGlobalTimer & 1)) {
        m->marioObj->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
    }

    if (flags & MARIO_CAP_IN_HAND) {
        if (flags & MARIO_WING_CAP) {
            bodyState->handState = MARIO_HAND_HOLDING_WING_CAP;
        } else {
            bodyState->handState = MARIO_HAND_HOLDING_CAP;
        }
    }

    if (flags & MARIO_CAP_ON_HEAD) {
        if (flags & MARIO_WING_CAP) {
            bodyState->capState = MARIO_HAS_WING_CAP_ON;
        } else {
            bodyState->capState = MARIO_HAS_DEFAULT_CAP_ON;
        }
    }

    // Short hitbox for crouching/crawling/etc.
    if (m->action & ACT_FLAG_SHORT_HITBOX) {
        m->marioObj->hitboxHeight = 100.0f;
    } else {
        m->marioObj->hitboxHeight = 160.0f;
    }

    if (phasewalk_state > 0) {
        bodyState->modelState &= ~MODEL_STATE_MASK;
        bodyState->modelState |= (MODEL_STATE_ALPHA | 128);
    }

    if ((m->flags & MARIO_TELEPORTING) && (m->fadeWarpOpacity != MODEL_STATE_MASK)) {
        bodyState->modelState &= ~MODEL_STATE_MASK;
        bodyState->modelState |= (MODEL_STATE_ALPHA | m->fadeWarpOpacity);
    }
}

/**
 * An unused and possibly a debug function. Z + another button input
 * sets Mario with a different cap.
 */
UNUSED static void debug_update_mario_cap(u16 button, s32 flags, u16 capTimer, u16 capMusic) {
    // This checks for Z_TRIG instead of Z_DOWN flag
    // (which is also what other debug functions do),
    // so likely debug behavior rather than unused behavior.
    if ((gPlayer1Controller->buttonDown & Z_TRIG) && (gPlayer1Controller->buttonPressed & button)
        && !(gMarioState->flags & flags)) {
        gMarioState->flags |= (flags + MARIO_CAP_ON_HEAD);

        if (capTimer > gMarioState->capTimer) {
            gMarioState->capTimer = capTimer;
        }

        play_cap_music(capMusic);
    }
}

#if ENABLE_RUMBLE
void queue_rumble_particles(struct MarioState *m) {
    if (m->particleFlags & PARTICLE_HORIZONTAL_STAR) {
        queue_rumble_data(5, 80);
    } else if (m->particleFlags & PARTICLE_VERTICAL_STAR) {
        queue_rumble_data(5, 80);
    } else if (m->particleFlags & PARTICLE_TRIANGLE) {
        queue_rumble_data(5, 80);
    }
    if (m->heldObj && m->heldObj->behavior == segmented_to_virtual(bhvBobomb)) {
        reset_rumble_timers_slip();
    }
}
#endif

s32 ground_check_knight(struct MarioState *m) {
    struct Surface *floor = m->floor;
    f32 steepness = sqrtf(sqr(floor->normal.x) + sqr(floor->normal.z));
    s16 floorDYaw = atan2s(floor->normal.z,floor->normal.x)+0x8000;

    if (!using_ability(ABILITY_KNIGHT)) {
        return FALSE;
    }

    if (steepness > 0.2f) {
        m->forwardVel = 48.0f;
        if (abs_angle_diff(m->faceAngle[1],floorDYaw) < 0x4000) {
            m->faceAngle[1] = floorDYaw+0x8000;
        }
        return set_mario_action(m, ACT_KNIGHT_SLIDE, 0);
    } else {
        return FALSE;
    }
}

s32 check_dashboost_inputs(struct MarioState *m) {
    if (!using_ability(ABILITY_DASH_BOOSTER)||m->remainingDashes == 0) {
        return FALSE;
    }

    if (gPlayer1Controller->buttonPressed & L_TRIG) {
        if (((gMarioState->action & ACT_GROUP_MASK) == ACT_GROUP_MOVING)||
        ((gMarioState->action & ACT_GROUP_MASK) == ACT_GROUP_STATIONARY)) {
            m->pos[1] += 15.0f;
        }

        play_sound(SOUND_GENERAL_EXPLOSION6, gGlobalSoundSource);
        m->remainingDashes--;
        return set_mario_action(m,ACT_DASH_BOOST,0);
    }

    if (gPlayer1Controller->buttonPressed & Z_TRIG) {
        play_sound(SOUND_GENERAL_EXPLOSION6, gGlobalSoundSource);
        m->remainingDashes--;
        return set_mario_action(m,ACT_DASH_BOOST,1);
    }

    return FALSE;
}

u8 pizza_time = FALSE;
u16 pizza_timer = 0;
u8 combo_meter = 201;
u8 p_rank_challenge_enabled = FALSE;
u8 p_rank_challenge_prepare = FALSE;
u8 p_rank_lap_2 = FALSE;
u8 p_rank_stars = 0;
u8 p_rank_success = FALSE;
u8 p_rank_true = FALSE;

u8 magic_mirror_timer = 20;
u8 magic_mirror_area_change_flag = FALSE;
u8 magic_mirror_disable = FALSE;

f32 flowpipe_vel = 0.0f;
s16 flowpipe_angle = 0;


s8 esa_hp = -1;
s8 esa_mhp = -1;
char * esa_str = NULL;

s32 is_2d_area(void) {
    return ((gCurrLevelNum == LEVEL_L)&&(gCurrAreaIndex < 6));
}

/**
 * Main function for executing Mario's behavior. Returns particleFlags.
 */
s32 execute_mario_action(UNUSED struct Object *obj) {
    s32 inLoop = TRUE;

    //debug activate credits
    //if (gPlayer1Controller->buttonPressed & D_JPAD) {
    //    level_trigger_warp(gMarioState, WARP_OP_CREDITS_START);
    //    gMarioState->actionState = ACT_STATE_END_PEACH_CUTSCENE_FADE_OUT_END;
    //}
    
    // Updates once per frame:
    vec3f_get_dist_and_lateral_dist_and_angle(gMarioState->prevPos, gMarioState->pos, &gMarioState->moveSpeed, &gMarioState->lateralSpeed, &gMarioState->movePitch, &gMarioState->moveYaw);
    vec3f_copy(gMarioState->prevPos, gMarioState->pos);

    if (pizza_time) {
        level_control_timer(TIMER_CONTROL_SHOW);
        gHudDisplay.timer = pizza_timer;
        if (pizza_timer > 0) {
            pizza_timer --;
        } else {
            //outta time, summon the green demon
            if (!cur_obj_nearest_object_with_behavior(bhvHidden1upInPole)) {
                spawn_object(gMarioObject,MODEL_L_DEMON,bhvHidden1upInPole);
            }
        }
    } else {
        if (gCurrLevelNum == LEVEL_L) {
            level_control_timer(TIMER_CONTROL_HIDE);
        }
    }
    //combo meter logic
    if ((p_rank_challenge_enabled) && ((gMarioState->action & ACT_GROUP_MASK) != ACT_GROUP_CUTSCENE)) {
        if (combo_meter > 0) {
            if ((gGlobalTimer % 2 == 0)||(p_rank_true)) {
                combo_meter--;
            }
        } else {
            if (gMarioState->action != ACT_DISAPPEARED) {
                set_mario_action(gMarioState, ACT_DISAPPEARED, 1);
                level_trigger_warp(gMarioState, WARP_OP_DEATH);
            }
        }
    }

    if (toZeroMeter) {  // Reset ability meter if it's not set past this point
        gHudDisplay.abilityMeter = 0;
        toZeroMeter = FALSE;
    }
    else {
        gHudDisplay.abilityMeter = -1;
    }

    if (gMarioState->action) {
#ifdef ENABLE_DEBUG_FREE_MOVE
        if (
            (gMarioState->controller->buttonDown & U_JPAD) &&
            !(gMarioState->controller->buttonDown & L_TRIG)
        ) {
            set_camera_mode(gMarioState->area->camera, CAMERA_MODE_8_DIRECTIONS, 1);
            set_mario_action(gMarioState, ACT_DEBUG_FREE_MOVE, 0);
        }
#endif
#ifdef ENABLE_CREDITS_BENCHMARK
        static s32 startedBenchmark = FALSE;
        if (!startedBenchmark) {
            set_mario_action(gMarioState, ACT_IDLE, 0);
            level_trigger_warp(gMarioState, WARP_OP_CREDITS_START);
            startedBenchmark = TRUE;
        }
#endif

        gMarioState->marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        mario_reset_bodystate(gMarioState);
        update_mario_inputs(gMarioState);

#ifdef PUPPYCAM
        if (!(gPuppyCam.flags & PUPPYCAM_BEHAVIOUR_FREE)) {
#endif
        mario_handle_special_floors(gMarioState);
#ifdef PUPPYCAM
        }
#endif
        mario_process_interactions(gMarioState);

        // If Mario is OOB, stop executing actions.
        if (gMarioState->floor == NULL) {
            return ACTIVE_PARTICLE_NONE;
        }

        if ((gCurrLevelNum == LEVEL_F) && ((gMarioState->action & ACT_GROUP_MASK) == ACT_GROUP_STATIONARY) && (gCurrCreditsEntry == NULL)) {
            // Level F automatic dialog

            // Get watch dialog
            if (!(gSaveBuffer.files[gCurrSaveFileNum - 1][0].level_f_flags & (1<<LEVEL_F_FLAG_BOND_MESSAGE_1))) {
                if (save_file_check_ability_unlocked(ABILITY_GADGET_WATCH)) {
                    set_mario_action(gMarioState, ACT_READING_AUTOMATIC_DIALOG, DIALOG_F_BOND2);
                    gSaveBuffer.files[gCurrSaveFileNum - 1][0].level_f_flags |= (1<<LEVEL_F_FLAG_BOND_MESSAGE_1);
                }
            }
        
            // Blow up wall dialog
            if (!(gSaveBuffer.files[gCurrSaveFileNum - 1][0].level_f_flags & (1<<LEVEL_F_FLAG_BOND_MESSAGE_2))) {
                struct Object * bombwall = cur_obj_nearest_object_with_behavior(bhvFblastwall);
                if ((bombwall) && (bombwall->oAction == 2)) {
                    set_mario_action(gMarioState, ACT_READING_AUTOMATIC_DIALOG, DIALOG_F_BOND4);
                    gSaveBuffer.files[gCurrSaveFileNum - 1][0].level_f_flags |= (1<<LEVEL_F_FLAG_BOND_MESSAGE_2);
                }
            }

            // Get 1st star dialog
            if (!(gSaveBuffer.files[gCurrSaveFileNum - 1][0].level_f_flags & (1<<LEVEL_F_FLAG_BOND_MESSAGE_3))) {
                if (save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_SL)) & 1) {
                    set_mario_action(gMarioState, ACT_READING_AUTOMATIC_DIALOG, DIALOG_F_BOND3);
                    gSaveBuffer.files[gCurrSaveFileNum - 1][0].level_f_flags |= (1<<LEVEL_F_FLAG_BOND_MESSAGE_3);
                }
            }
        }

        f32 dist_to_nearest_star = 9999.0f;
        struct Object * nearest_star = cur_obj_nearest_object_with_behavior(bhvStar);
        if (nearest_star) {
            dist_to_nearest_star = dist_between_objects(gMarioObject,nearest_star);
        }

        //attempt to take a screenshot every 10 seconds. only take when he's idle or moving on the ground.
        //also, do not take screenshots when near a star.
        if ((((gMarioState->action & ACT_GROUP_MASK) == ACT_GROUP_MOVING) ||
        ((gMarioState->action & ACT_GROUP_MASK) == ACT_GROUP_STATIONARY)) &&
        (gGlobalTimer % 300 == 0) &&
        (dist_to_nearest_star > 2000.0f)) {
            save_file_screenshot();
        }

        //--E SG
        if (using_ability(ABILITY_E_SHOTGUN)) {
            struct MarioState *m = gMarioState;
            gE_ShotgunFlags &= ~E_SGF_AIM_FIRE;
            if (!(m->floor->normal.y < COS73)) {
                if (!mario_is_in_air_action()) {
                    gE_ShotgunFlags &= ~E_SGF_AIR_SHOT_USED; }
            }
        }
        if ((gCurrLevelNum == LEVEL_E) && !(obj_has_model(gMarioObject, MODEL_SQUID))) {//--C9
            if ((gGlobalTimer % 3) == 0) {
                gMarioObject->header.gfx.sharedChild = gLoadedGraphNodes[ability_struct[gMarioState->abilityId].model_id];
            }
        }

        u8 chronos_active = FALSE;
        // Chronos Ability Code
        if (using_ability(ABILITY_CHRONOS)) {
            if (!(gPlayer1Controller->buttonDown & L_TRIG)) {
                chronos_expended = FALSE;
            }

            if (
                (gMarioState->action & ACT_GROUP_MASK) != ACT_GROUP_CUTSCENE &&
                (gPlayer1Controller->buttonDown & L_TRIG) &&
                chronos_timer > 0 &&
                !chronos_expended
            ) {
                if (gMarioState->abilityChronosTimeSlowActive == FALSE) {
                    play_sound(SOUND_MENU_CHRONOS_SLOMO_ENGAGE, gGlobalSoundSource);
                }
                gMarioState->abilityChronosTimeSlowActive = TRUE;
                chronos_active = TRUE;
                chronos_timer = MAX(chronos_timer - 2, 0);
                if (chronos_timer == 0) {
                    chronos_expended = TRUE;
                }
            }
        }
        if (!chronos_active) {
            if (gMarioState->abilityChronosTimeSlowActive == TRUE) {
                play_sound(SOUND_MENU_CHRONOS_SLOMO_DISENGAGE, gGlobalSoundSource);
            }
            gMarioState->abilityChronosTimeSlowActive = FALSE;
            if (chronos_timer < 360) {
                chronos_timer++;
            }
        }

        //Dash Booster Meter
        if (using_ability(ABILITY_DASH_BOOSTER)) {
            gHudDisplay.abilityMeterStyle = METER_STYLE_DASH_BOOSTER;
            switch(gMarioState->remainingDashes) {
                case 0:
                    gHudDisplay.abilityMeter = 0;
                break;
                case 1:
                    gHudDisplay.abilityMeter = 3;
                break;
                case 2:
                    gHudDisplay.abilityMeter = 5;
                break;
                case 3:
                    gHudDisplay.abilityMeter = 8;
                break;
            }
        }

        // Pizza Tower 2D
        if (is_2d_area()) {
            gMarioState->pos[2] = 0.0f;
            // Only angle-lock the knight suit ability
            if ((gMarioState->action == ACT_KNIGHT_SLIDE)||(gMarioState->action == ACT_KNIGHT_JUMP)) {
                if (gMarioState->faceAngle[1] > 0) {
                    gMarioState->faceAngle[1] = 0x4000;
                } else {
                    gMarioState->faceAngle[1] = -0x4000;
                }
            }
        }

        if (gMarioState->floor->type == SURFACE_FLOWPIPE) {
            flowpipe_angle = gMarioState->floor->force << 8;
            if (flowpipe_vel < 70.0f) {
                flowpipe_vel += 2.0f;
            }
        } else {
            flowpipe_vel *= .9f;
        }

        if (flowpipe_vel > 1.0f) {
            gMarioState->pos[0] += sins(flowpipe_angle) * flowpipe_vel;
            gMarioState->pos[2] += coss(flowpipe_angle) * flowpipe_vel;
        }

        // The function can loop through many action shifts in one frame,
        // which can lead to unexpected sub-frame behavior. Could potentially hang
        // if a loop of actions were found, but there has not been a situation found.
        while (inLoop) {
            switch (gMarioState->action & ACT_GROUP_MASK) {
                case ACT_GROUP_STATIONARY: inLoop = mario_execute_stationary_action(gMarioState); break;
                case ACT_GROUP_MOVING:     inLoop = mario_execute_moving_action(gMarioState);     break;
                case ACT_GROUP_AIRBORNE:   inLoop = mario_execute_airborne_action(gMarioState);   break;
                case ACT_GROUP_SUBMERGED:  inLoop = mario_execute_submerged_action(gMarioState);  break;
                case ACT_GROUP_CUTSCENE:   inLoop = mario_execute_cutscene_action(gMarioState);   break;
                case ACT_GROUP_AUTOMATIC:  inLoop = mario_execute_automatic_action(gMarioState);  break;
                case ACT_GROUP_OBJECT:     inLoop = mario_execute_object_action(gMarioState);     break;
            }
        }

        //--E
        if (using_ability(ABILITY_E_SHOTGUN)) {
            e__animate_upper(); }

        struct Surface * marble_floor;
        f32 marble_floor_y = find_floor(gMarioState->pos[0],gMarioState->pos[1],gMarioState->pos[2],&marble_floor);
        u8 force_marble = ((marble_floor)&&(marble_floor->type == SURFACE_FORCE_MARBLE)&&(gMarioState->pos[1] < marble_floor_y+120.0f)&&((gMarioState->action & ACT_GROUP_MASK) != ACT_GROUP_CUTSCENE));

        if (using_ability(ABILITY_BUBBLE_HAT) && (gMarioState->action != ACT_BUBBLE_HAT_JUMP)) {
            change_ability(ABILITY_BUBBLE_HAT);
        }

        if ((!force_marble)&&(gMarioState->action != ACT_BUBBLE_HAT_JUMP)&&(gMarioState->action != ACT_SQUID)) {
            control_ability_dpad();
        }


        if ((gMarioState->action & ACT_GROUP_MASK) == ACT_GROUP_CUTSCENE) {
            gMarioState->abilityChronosTimeSlowActive = FALSE;
        }

        sink_mario_in_quicksand(gMarioState);
        squish_mario_model(gMarioState);
        set_submerged_cam_preset_and_spawn_bubbles(gMarioState);
        update_mario_health(gMarioState);
#ifdef BREATH_METER
        update_mario_breath(gMarioState);
#endif
        update_mario_info_for_cam(gMarioState);
        mario_update_hitbox_and_cap_model(gMarioState);

        // Both of the wind handling portions play wind audio only in
        // non-Japanese releases.
        if (gMarioState->floor->type == SURFACE_HORIZONTAL_WIND) {
            spawn_wind_particles(0, (gMarioState->floor->force << 8));
            play_sound(SOUND_ENV_WIND2, gMarioState->marioObj->header.gfx.cameraToObject);
        }

        if (gMarioState->floor->type == SURFACE_VERTICAL_WIND) {
            spawn_wind_particles(1, 0);
            play_sound(SOUND_ENV_WIND2, gMarioState->marioObj->header.gfx.cameraToObject);
        }

        play_infinite_stairs_music();
        gMarioState->marioObj->oInteractStatus = INT_STATUS_NONE;
#if ENABLE_RUMBLE
        queue_rumble_particles(gMarioState);
#endif

        if (using_ability(ABILITY_CHRONOS)) {
            gHudDisplay.abilityMeterStyle = METER_STYLE_CHRONOS;
            if (chronos_active) {
                gHudDisplay.abilityMeter = MIN((s16)((chronos_timer / 360.0f) * 8.0f) + 1, 8);
            }
            else {
                gHudDisplay.abilityMeter = (s16)((chronos_timer / 360.0f) * 8.0f);
            }
        }

        // Drink Milk Code
        if ((!milk_drunk)&&(using_ability(ABILITY_UTIL_MILK))&&(gPlayer1Controller->buttonPressed & L_TRIG)&&((gMarioState->action & ACT_GROUP_MASK) != ACT_GROUP_CUTSCENE)) {
            milk_drunk = TRUE;
            gMarioState->healCounter += 20;
            play_sound(SOUND_GENERAL_HEART_SPIN, gGlobalSoundSource);
        }

        // Magic Mirror Code
        if ((!magic_mirror_disable)&&(using_ability(ABILITY_UTIL_MIRROR))&&(gPlayer1Controller->buttonPressed & L_TRIG)&&((gMarioState->action & ACT_GROUP_MASK) != ACT_GROUP_CUTSCENE)) {
            if (gMarioState->areaCheckpointFlag == gCurrAreaIndex) {
                // Checkpoint flag in same area
                if (gMarioState->numCheckpointFlag != -1) {
                    struct Object *dw = cur_obj_nearest_object_with_behavior(bhvDeathWarp);
                    if (dw) {
                        Vec3f displacement;
                        vec3f_diff(displacement,&dw->oPosVec,gMarioState->pos);

                        vec3f_add(gMarioState->pos,displacement);

                        magic_mirror_timer = 0;
                        
                        gLakituState.curPos[1] += displacement[1];
                        gLakituState.curFocus[1] += displacement[1];
                        gLakituState.goalPos[1] += displacement[1];
                        gLakituState.goalFocus[1] += displacement[1];
                        
                        gLakituState.focHSpeed = 1.f;
                        gLakituState.focVSpeed = 1.f;
                        gLakituState.posHSpeed = 1.f;
                        gLakituState.posVSpeed = 1.f;

                        play_sound(SOUND_ABILITY_MAGIC_MIRROR, gGlobalSoundSource);
                    }
                } else {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            } else {
                // Checkpoint flag NOT in same area
                if (gMarioState->areaCheckpointFlag != -1) {
                    magic_mirror_area_change_flag = TRUE;
                    magic_mirror_timer = 0;
                } else {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            }
        }
        if (magic_mirror_timer == 2) {
            gLakituState.focHSpeed = 0.8f;
            gLakituState.focVSpeed = 0.3f;
            gLakituState.posHSpeed = 0.3f;
            gLakituState.posVSpeed = 0.3f;
        }
        if (magic_mirror_timer < 20) {
            struct Object *sparkleObj = spawn_object(o, MODEL_SPARKLES, bhvCoinSparkles);
            sparkleObj->oPosX += random_float() * 100.0f - 50.0f;
            sparkleObj->oPosY += random_float() * 100.0f;
            sparkleObj->oPosZ += random_float() * 100.0f - 50.0f;
            magic_mirror_timer ++;
        }

        // Compass Code
        if (using_ability(ABILITY_UTIL_COMPASS)) {
            struct Object *rarrow = cur_obj_nearest_object_with_behavior(bhvRedArrow);
            if (!rarrow) {
                spawn_object(o,MODEL_RED_ARROW,bhvRedArrow);
            }
        } else {
            //no more gadget watch
            struct Object *rarrow = cur_obj_nearest_object_with_behavior(bhvRedArrow);
            if (rarrow) {
                obj_mark_for_deletion(rarrow);
            }   
        }

        // Aku Ability Code
        if (!using_ability(ABILITY_AKU)) {
            if (aku_invincibility != 0) {
                aku_invincibility = 0;
                //stop_cap_music();
            }
        } else {
            if ((gPlayer1Controller->buttonDown & L_TRIG)&&(aku_invincibility == 0)&&(aku_recharge >= 300)&&(gMarioState->numGlobalCoins >= 10)&&((gMarioState->action & ACT_GROUP_MASK) != ACT_GROUP_CUTSCENE)) {
                aku_invincibility = 300;
                aku_recharge = 0;
                gMarioState->numGlobalCoins -= 10;
                if(!(gCurrCourseNum == COURSE_CCM && gCurrAreaIndex == 4)) //Don't play the music in the LEVEL_I funky shell section to not desynchronized the music
                //    play_cap_music(SEQUENCE_ARGS(4, SEQ_EVENT_POWERUP));
                cool_down_ability(ABILITY_AKU);
            }

            if (aku_invincibility > 0) {
                gHudDisplay.abilityMeter = MIN((s16)((aku_invincibility / 300.0f) * 8.0f) + 1, 8);
                gHudDisplay.abilityMeterStyle = METER_STYLE_AKU;
                toZeroMeter = TRUE;
            } else {
                if (aku_recharge < 300) {
                    gHudDisplay.abilityMeter = MIN((s16)((aku_recharge / 300.0f) * 8.0f) + 1, 8);
                    gHudDisplay.abilityMeterStyle = METER_STYLE_AKU_RECHARGE;
                }
            }
        }
        if (aku_invincibility > 0) {
            struct Object *sparkleObj = spawn_object(o, MODEL_SPARKLES, bhvCoinSparkles);
            sparkleObj->oPosX += random_float() * 50.0f - 25.0f;
            sparkleObj->oPosY += random_float() * 100.0f;
            sparkleObj->oPosZ += random_float() * 50.0f - 25.0f;

            aku_invincibility --;
        } else {
            if (aku_recharge < 300) {
                aku_recharge++;
            } else {
                ability_ready(ABILITY_AKU);
            }
        }

        //Phasewalk ability code
        if (using_ability(ABILITY_PHASEWALK)) {

             if ((gPlayer1Controller->buttonDown & L_TRIG)&&(phasewalk_timer == 0)) {
                phasewalk_state = 1;
                phasewalk_timer = 240;
                play_sound(SOUND_GENERAL_VANISH_SFX, gMarioState->marioObj->header.gfx.cameraToObject);
                cool_down_ability(ABILITY_PHASEWALK);
             }
            if (phasewalk_timer == 180) {
                phasewalk_state = 2;
            }
            if (phasewalk_timer == 150) {
                phasewalk_state = 0;
            }

            if (phasewalk_state == 0) {
                if (phasewalk_timer == 0) {
                    gHudDisplay.abilityMeter = 8;
                    gHudDisplay.abilityMeterStyle = METER_STYLE_PHASEWALK;
                }
                else {
                    gHudDisplay.abilityMeter = (s16)(((150 - phasewalk_timer) / 150.0f) * 8.0f);
                    gHudDisplay.abilityMeterStyle = METER_STYLE_PHASEWALK_RECHARGE;
                }
            }
            else {
                u16 phasewalk_remaining = phasewalk_timer - 150;
                gHudDisplay.abilityMeter =  MIN((s16)((phasewalk_remaining / 90.0f) * 8.0f) + 1, 8);
                if (phasewalk_state == 2) {
                    //spawn sparkles to indicate superjump
                    struct Object *sparkleObj = spawn_object(o, MODEL_SPARKLES, bhvCoinSparkles);
                    sparkleObj->oPosX += random_float() * 50.0f - 25.0f;
                    sparkleObj->oPosY += random_float() * 100.0f;
                    sparkleObj->oPosZ += random_float() * 50.0f - 25.0f;

                    gHudDisplay.abilityMeterStyle = METER_STYLE_PHASEWALK_SUPERJUMP;
                }
                else {
                    gHudDisplay.abilityMeterStyle = METER_STYLE_PHASEWALK;
                }
            }
        } else {
            phasewalk_state = 0;
            if (phasewalk_timer > 140) {
                phasewalk_timer = 140;
            }
        }
        //the phasewalk timer runs unconditionally
        if (phasewalk_timer > 0) {
            phasewalk_timer --;
            if (phasewalk_timer == 0) {
                ability_ready(ABILITY_PHASEWALK);
            }
        }

        if (using_ability(ABILITY_SHOCK_ROCKET)) {
            if (count_objects_with_behavior(bhvShockRocket) != 0) {
                struct Object *rocket = cur_obj_nearest_object_with_behavior(bhvShockRocket);
                if (rocket->oAction == SHOCK_ROCKET_ACT_MOVE) {
                    gHudDisplay.abilityMeterStyle = METER_STYLE_ROCKET;
                    gHudDisplay.abilityMeter =  MIN((s16)(((300 - rocket->oTimer) / 300.0f) * 8.0f) + 1, 8);
                    toZeroMeter = TRUE;
                }
            }
        }

        // Kick Mario out of the marble if he is forcibly set to another state
        if (gMarioState->action != ACT_MARBLE) {
            struct Object *marble = cur_obj_nearest_object_with_behavior(bhvPhysicsMarble);
            if (marble) {
                deallocate_rigid_body(marble->rigidBody);
                obj_mark_for_deletion(marble);
                change_ability(ABILITY_DEFAULT);
            }
        }

        //Marble Ability
        if (force_marble) {
            gMarioState->canHMFly = TRUE;
            gE_ShotgunFlags &= ~E_SGF_AIR_SHOT_USED;
            if (!using_ability(ABILITY_MARBLE)) {
                change_ability(ABILITY_MARBLE);
                gMarioState->forwardVel = 0.0f;
                gMarioState->vel[1] = 0.0;
                gMarioState->pos[1] = marble_floor_y + 51.0f;//102.0f;
                gMarioObject->oPosY = marble_floor_y + 51.0f;//102.0f;
            }
        }

        if (using_ability(ABILITY_MARBLE)) {
            struct Object *marble = cur_obj_nearest_object_with_behavior(bhvPhysicsMarble);
            if (!marble && !(gMarioState->riddenObj != NULL && obj_has_behavior(gMarioState->riddenObj, bhvFunkyShell))) {
                set_mario_action(gMarioState,ACT_MARBLE,0);
                gMarioState->pos[1] += 100.0f;
                gMarioObject->oPosY += 100.0f;
                marble = spawn_object(o,MODEL_MARBLE,bhvPhysicsMarble);

                set_camera_mode(gMarioState->area->camera, gMarioState->area->camera->defMode, 1);
            }
            gMarioObject->hitboxHeight = 200;
            gMarioObject->hitboxRadius = 100;
            gMarioObject->hitboxDownOffset = 50;
            gMarioObject->hurtboxHeight = 200;
            gMarioObject->hurtboxRadius = 100;

        } else {
            struct Object *marble = cur_obj_nearest_object_with_behavior(bhvPhysicsMarble);
            if (marble) {
                //vec3f_copy(gMarioState->vel,marble->rigidBody->linearVel);
                //marble->rigidBody->linearVel[1] = 0.0f;
                gMarioState->vel[1] = marble->rigidBody->linearVel[1];
                marble->rigidBody->linearVel[1] = 0.0f;
                gMarioState->forwardVel = vec3_mag(marble->rigidBody->linearVel);
                gMarioState->faceAngle[1] = atan2s(marble->rigidBody->linearVel[2],marble->rigidBody->linearVel[0]);
                gMarioState->action = ACT_FREEFALL;
                deallocate_rigid_body(marble->rigidBody);
                obj_mark_for_deletion(marble);
                gMarioState->pos[1] -= 100.0f;
                gMarioObject->oPosY -= 100.0f;
            }
            gMarioObject->hitboxHeight = 160;
            gMarioObject->hitboxRadius = 37;
            gMarioObject->hitboxDownOffset = 0;
            gMarioObject->hurtboxHeight = 160;
            gMarioObject->hurtboxRadius = 37;
        }

        struct SpawnParticlesInfo D_8032F270 = { 2, 20, MODEL_MIST, 0, 40, 5, 30, 20, 252, 30, 10.0f, 10.0f };

        //Squid Ability
        gMarioState->marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        if(using_ability(ABILITY_SQUID)){
            if (gPlayer1Controller->buttonPressed & L_TRIG){
                cur_obj_spawn_particles(&D_8032F270);
                if (gMarioState->action == ACT_SQUID) {
                    obj_set_model(gMarioObject, MODEL_MARIO);
                    set_mario_action(gMarioState, ACT_IDLE, 0);
                    gMarioState->marioObj->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
                } else {
                    obj_set_model(gMarioObject, MODEL_SQUID);
                    set_mario_action(gMarioState, ACT_SQUID, 0);
                    gMarioState->marioObj->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
                }
            }
        }

        //Watch Ability
        if (using_ability(ABILITY_GADGET_WATCH)) {
            struct Object *aim = cur_obj_nearest_object_with_behavior(bhvGadgetAim);
            if (!aim) {
                spawn_object(o,MODEL_WATCH_AIM,bhvGadgetAim);
            }
        } else {
            //no more gadget watch
            struct Object *aim = cur_obj_nearest_object_with_behavior(bhvGadgetAim);
            if (aim) {
                obj_mark_for_deletion(aim);
            }   
        }

        if (lastAbility != gMarioState->abilityId) {
            gHudDisplay.abilityMeter = -1;
            lastAbility = gMarioState->abilityId;
        }

        return gMarioState->particleFlags;
    }

    return ACTIVE_PARTICLE_NONE;
}

/**************************************************
 *                  INITIALIZATION                *
 **************************************************/

void init_mario(void) {
    esa_mhp = -1;
    
    //set_camera_mode(gMarioState->area->camera, gMarioState->area->camera->defMode, 1);

    gMarioState->actionTimer = 0;
    gMarioState->framesSinceA = 0xFF;
    gMarioState->framesSinceB = 0xFF;

    gMarioState->invincTimer = 0;
    gMarioState->keypad_id = -1;

    if (save_file_get_flags()
        & (SAVE_FLAG_CAP_ON_GROUND | SAVE_FLAG_CAP_ON_KLEPTO | SAVE_FLAG_CAP_ON_UKIKI
           | SAVE_FLAG_CAP_ON_MR_BLIZZARD)) {
        gMarioState->flags = 0;
    } else {
        gMarioState->flags = (MARIO_NORMAL_CAP | MARIO_CAP_ON_HEAD);
    }

    gMarioState->knightDoubleJump = FALSE;

    gMarioState->forwardVel = 0.0f;
    gMarioState->squishTimer = 0;

    gMarioState->hurtCounter = 0;
    gMarioState->healCounter = 0;

    gMarioState->capTimer = 0;
    gMarioState->quicksandDepth = 0.0f;

    gMarioState->heldObj = NULL;
    gMarioState->riddenObj = NULL;
    gMarioState->usedObj = NULL;

    gMarioState->waterLevel = find_water_level(gMarioSpawnInfo->startPos[0], gMarioSpawnInfo->startPos[2]);

    gMarioState->area = gCurrentArea;
    gMarioState->marioObj = gMarioObject;
    gMarioState->marioObj->header.gfx.animInfo.animID = -1;
    vec3s_copy(gMarioState->faceAngle, gMarioSpawnInfo->startAngle);
    vec3_zero(gMarioState->angleVel);
    vec3s_to_vec3f(gMarioState->pos, gMarioSpawnInfo->startPos);
    vec3f_copy(gMarioState->prevPos, gMarioState->pos);
    vec3_zero(gMarioState->vel);
    gMarioState->floorHeight =
        find_floor(gMarioState->pos[0], gMarioState->pos[1], gMarioState->pos[2], &gMarioState->floor);

    if (gMarioState->pos[1] < gMarioState->floorHeight) {
        gMarioState->pos[1] = gMarioState->floorHeight;
    }

    gMarioState->marioObj->header.gfx.pos[1] = gMarioState->pos[1];

    gMarioState->action =
        (gMarioState->pos[1] <= (gMarioState->waterLevel - 100)) ? ACT_WATER_IDLE : ACT_IDLE;

    mario_reset_bodystate(gMarioState);
    update_mario_info_for_cam(gMarioState);
    gMarioState->marioBodyState->punchState = 0;

    vec3f_copy(&gMarioState->marioObj->oPosVec, gMarioState->pos);
    vec3s_to_vec3i(&gMarioState->marioObj->oMoveAngleVec, gMarioState->faceAngle);

    vec3f_copy(gMarioState->marioObj->header.gfx.pos, gMarioState->pos);
    vec3s_set(gMarioState->marioObj->header.gfx.angle, 0, gMarioState->faceAngle[1], 0);

    /*
    Vec3s capPos;
    if (save_file_get_cap_pos(capPos)) {
        struct Object *capObject = spawn_object(gMarioState->marioObj, MODEL_MARIOS_CAP, bhvNormalCap);
        vec3s_to_vec3f(&capObject->oPosVec, capPos);

        capObject->oForwardVel = 0;
        capObject->oMoveAngleYaw = 0;
    }
    */

    //--E | No first-frame gun position
    e__set_upper_anim(gMarioState, 2);

    gMarioObject->header.gfx.sharedChild = gLoadedGraphNodes[ability_struct[gMarioState->abilityId].model_id];

}

void init_mario_from_save_file(void) {
    save_file_get_coins();
    if (save_file_exists(gCurrSaveFileNum - 1)) {
        save_file_get_ability_dpad();
    } else {
        save_file_init_ability_dpad();
        gSaveBuffer.files[gCurrSaveFileNum - 1][0].levels_unlocked = 1;
    }
    gMarioState->numCheckpointFlag = -1;
    gMarioState->areaCheckpointFlag = -1;
    gMarioState->abilityId = 0;
    gMarioState->playerID = 0;
    gMarioState->flags = MARIO_NONE;
    gMarioState->action = ACT_UNINITIALIZED;
    gMarioState->spawnInfo = &gPlayerSpawnInfos[0];
    gMarioState->statusForCamera = &gPlayerCameraState[0];
    gMarioState->marioBodyState = &gBodyStates[0];
    gMarioState->controller = &gControllers[0];
    gMarioState->animList = &gMarioAnimsBuf;

    gMarioState->numCoins = 0;
    gMarioState->numStars = save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1);
    gMarioState->numKeys = 0;
#ifdef ENABLE_LIVES
    gMarioState->numLives = ENABLE_LIVES;
#else
    gMarioState->numLives = 0;
#endif
    gMarioState->health = 0x880;
#ifdef BREATH_METER
    gMarioState->breath = 0x880;
    gHudDisplay.breath = 8;
#endif
    gHudDisplay.abilityMeter = -1;
    gMarioState->prevNumStarsForDialog = gMarioState->numStars;
    gMarioState->animYTrans = 0xBD;

    gHudDisplay.coins = 0;
    gHudDisplay.wedges = 8;

    chronos_timer = 360;
}


u16 update_mario_action_timer_pre(struct MarioState *m) {
    if (ability_chronos_frame_can_progress()) {
        m->actionTimer++;
    }
    return m->actionTimer;
}

u16 update_mario_action_timer_post(struct MarioState *m) {
    u16 output = m->actionTimer;
    if (ability_chronos_frame_can_progress()) {
        m->actionTimer++;
    }
    return output;
}
