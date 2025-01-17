#define OBJECT_FIELDS_INDEX_DIRECTLY

#include "sm64.h"

#include "object_constants.h"
#include "game/object_list_processor.h"
#include "game/interaction.h"
#include "game/behavior_actions.h"
#include "game/mario_actions_cutscene.h"
#include "game/mario_misc.h"
#include "game/object_helpers.h"
#include "game/debug.h"
#include "menu/file_select.h"
#include "engine/surface_load.h"
#include "game/mitm_hub.h"
#include "game/cutscene_manager.h"
#include "game/dream_comet.h"

#include "actors/common0.h"
#include "actors/common1.h"
#include "actors/group0.h"
#include "actors/group1.h"
#include "actors/group2.h"
#include "actors/group3.h"
#include "actors/group4.h"
#include "actors/group5.h"
#include "actors/group6.h"
#include "actors/group7.h"
#include "actors/group8.h"
#include "actors/group9.h"
#include "actors/group10.h"
#include "actors/group11.h"
#include "actors/group12.h"
#include "actors/group13.h"
#include "actors/group14.h"
#include "actors/group15.h"
#include "actors/group16.h"
#include "actors/group17.h"
#include "levels/bbh/header.h"
#include "levels/castle_inside/header.h"
#include "levels/hmc/header.h"
#include "levels/ssl/header.h"
#include "levels/bob/header.h"
#include "levels/sl/header.h"
#include "levels/wdw/header.h"
#include "levels/jrb/header.h"
#include "levels/thi/header.h"
#include "levels/ttc/header.h"
#include "levels/rr/header.h"
#include "levels/castle_grounds/header.h"
#include "levels/bitdw/header.h"
#include "levels/lll/header.h"
#include "levels/sa/header.h"
#include "levels/bitfs/header.h"
#include "levels/ddd/header.h"
#include "levels/wf/header.h"
#include "levels/bowser_2/header.h"
#include "levels/ttm/header.h"
#include "levels/e/header.h"
#include "levels/f/header.h"
#include "levels/J/header.h"
#include "levels/B/header.h"
#include "levels/o/header.h"
#include "levels/d/header.h"
#include "levels/i/header.h"
#include "levels/g/header.h"
#include "levels/h/header.h"
#include "levels/l/header.h"
#include "levels/m/header.h"
#include "levels/k/header.h"
#include "levels/bowser_course/header.h"
#include "levels/c/header.h"
#include "levels/sb/header.h"
#include "levels/birthday/header.h"

#include "make_const_nonconst.h"
#include "behavior_data.h"

#define BC_B(a) _SHIFTL(a, 24, 8)
#define BC_BB(a, b) (_SHIFTL(a, 24, 8) | _SHIFTL(b, 16, 8))
#define BC_BBBB(a, b, c, d) (_SHIFTL(a, 24, 8) | _SHIFTL(b, 16, 8) | _SHIFTL(c, 8, 8) | _SHIFTL(d, 0, 8))
#define BC_BBH(a, b, c) (_SHIFTL(a, 24, 8) | _SHIFTL(b, 16, 8) | _SHIFTL(c, 0, 16))
#define BC_B0H(a, b) (_SHIFTL(a, 24, 8) | _SHIFTL(b, 0, 16))
#define BC_H(a) _SHIFTL(a, 16, 16)
#define BC_HH(a, b) (_SHIFTL(a, 16, 16) | _SHIFTL(b, 0, 16))
#define BC_W(a) ((uintptr_t)(u32)(a))
#define BC_PTR(a) ((uintptr_t)(a))

enum BehaviorCommands {
    /*0x00*/ BHV_CMD_BEGIN,
    /*0x01*/ BHV_CMD_DELAY,
    /*0x02*/ BHV_CMD_CALL,
    /*0x03*/ BHV_CMD_RETURN,
    /*0x04*/ BHV_CMD_GOTO,
    /*0x05*/ BHV_CMD_BEGIN_REPEAT,
    /*0x06*/ BHV_CMD_END_REPEAT,
    /*0x07*/ BHV_CMD_END_REPEAT_CONTINUE,
    /*0x08*/ BHV_CMD_BEGIN_LOOP,
    /*0x09*/ BHV_CMD_END_LOOP,
    /*0x0A*/ BHV_CMD_BREAK,
    /*0x0B*/ BHV_CMD_BREAK_UNUSED,
    /*0x0C*/ BHV_CMD_CALL_NATIVE,
    /*0x0D*/ BHV_CMD_ADD_FLOAT,
    /*0x0E*/ BHV_CMD_SET_FLOAT,
    /*0x0F*/ BHV_CMD_ADD_INT,
    /*0x10*/ BHV_CMD_SET_INT,
    /*0x11*/ BHV_CMD_OR_INT,
    /*0x12*/ BHV_CMD_OR_LONG,
    /*0x13*/ BHV_CMD_BIT_CLEAR,
    /*0x14*/ BHV_CMD_SET_INT_RAND_RSHIFT,
    /*0x15*/ BHV_CMD_SET_RANDOM_FLOAT,
    /*0x16*/ BHV_CMD_SET_RANDOM_INT,
    /*0x17*/ BHV_CMD_ADD_RANDOM_FLOAT,
    /*0x18*/ BHV_CMD_ADD_INT_RAND_RSHIFT,
    /*0x19*/ BHV_CMD_NOP_1,
    /*0x1A*/ BHV_CMD_NOP_2,
    /*0x1B*/ BHV_CMD_SET_MODEL,
    /*0x1C*/ BHV_CMD_SPAWN_CHILD,
    /*0x1D*/ BHV_CMD_DEACTIVATE,
    /*0x1E*/ BHV_CMD_DROP_TO_FLOOR,
    /*0x1F*/ BHV_CMD_SUM_FLOAT,
    /*0x20*/ BHV_CMD_SUM_INT,
    /*0x21*/ BHV_CMD_BILLBOARD,
    /*0x22*/ BHV_CMD_HIDE,
    /*0x23*/ BHV_CMD_SET_HITBOX,
    /*0x24*/ BHV_CMD_NOP_4,
    /*0x25*/ BHV_CMD_DELAY_VAR,
    /*0x26*/ BHV_CMD_BEGIN_REPEAT_UNUSED,
    /*0x27*/ BHV_CMD_LOAD_ANIMATIONS,
    /*0x28*/ BHV_CMD_ANIMATE,
    /*0x29*/ BHV_CMD_SPAWN_CHILD_WITH_PARam,
    /*0x2A*/ BHV_CMD_LOAD_COLLISION_DATA,
    /*0x2B*/ BHV_CMD_SET_HITBOX_WITH_OFFSet,
    /*0x2C*/ BHV_CMD_SPAWN_OBJ,
    /*0x2D*/ BHV_CMD_SET_HOME,
    /*0x2E*/ BHV_CMD_SET_HURTBOX,
    /*0x2F*/ BHV_CMD_SET_INTERACT_TYPE,
    /*0x30*/ BHV_CMD_SET_OBJ_PHYSICS,
    /*0x31*/ BHV_CMD_SET_INTERACT_SUBTYPE,
    /*0x32*/ BHV_CMD_SCALE,
    /*0x33*/ BHV_CMD_PARENT_BIT_CLEAR,
    /*0x34*/ BHV_CMD_ANIMATE_TEXTURE,
    /*0x35*/ BHV_CMD_DISABLE_RENDERING,
    /*0x36*/ BHV_CMD_SET_INT_UNUSED,
    /*0x37*/ BHV_CMD_SPAWN_WATER_DROPLET,
};

// Defines the start of the behavior script as well as the object list the object belongs to.
// Has some special behavior for certain objects.
#define BEGIN(objList) \
    BC_BB(BHV_CMD_BEGIN, objList)

// Delays the behavior script for a certain number of frames.
#define DELAY(num) \
    BC_B0H(BHV_CMD_DELAY, num)

// Jumps to a new behavior command and stores the return address in the object's stack.
#define CALL(addr) \
    BC_B(BHV_CMD_CALL), \
    BC_PTR(addr)

// Jumps back to the behavior command stored in the object's stack.
#define RETURN() \
    BC_B(BHV_CMD_RETURN)

// Jumps to a new behavior script without saving anything.
#define GOTO(addr) \
    BC_B(BHV_CMD_GOTO), \
    BC_PTR(addr)

// Marks the start of a loop that will repeat a certain number of times.
#define BEGIN_REPEAT(count) \
    BC_B0H(BHV_CMD_BEGIN_REPEAT, count)

// Marks the end of a repeating loop.
#define END_REPEAT() \
    BC_B(BHV_CMD_END_REPEAT)

// Also marks the end of a repeating loop, but continues executing commands following the loop on the same frame.
#define END_REPEAT_CONTINUE() \
    BC_B(BHV_CMD_END_REPEAT_CONTINUE)

// Marks the beginning of an infinite loop.
#define BEGIN_LOOP() \
    BC_B(BHV_CMD_BEGIN_LOOP)

// Marks the end of an infinite loop.
#define END_LOOP() \
    BC_B(BHV_CMD_END_LOOP)

// Exits the behavior script.
// Often used to end behavior scripts that do not contain an infinite loop.
#define BREAK() \
    BC_B(BHV_CMD_BREAK)

// Exits the behavior script, unused.
#define BREAK_UNUSED() \
    BC_B(BHV_CMD_BREAK_UNUSED)

// Executes a native game function.
#define CALL_NATIVE(func) \
    BC_B(BHV_CMD_CALL_NATIVE), \
    BC_PTR(func)

// Adds a float to the specified field.
#define ADD_FLOAT(field, value) \
    BC_BBH(BHV_CMD_ADD_FLOAT, field, value)

// Sets the specified field to a float.
#define SET_FLOAT(field, value) \
    BC_BBH(BHV_CMD_SET_FLOAT, field, value)

// Adds an integer to the specified field.
#define ADD_INT(field, value) \
    BC_BBH(BHV_CMD_ADD_INT, field, value)

// Sets the specified field to an integer.
#define SET_INT(field, value) \
    BC_BBH(BHV_CMD_SET_INT, field, value)

// Performs a bitwise OR with the specified field and the given integer.
// Usually used to set an object's flags.
#define OR_INT(field, value) \
    BC_BBH(BHV_CMD_OR_INT, field, value)

// Performs a bitwise OR with the specified field and the given (32 bit) integer.
// Usually used to set an object's flags which use values above 16 bits.
#define OR_LONG(field, value) \
    BC_BB(BHV_CMD_OR_LONG, field), \
    BC_W(value)

// Performs a bit clear with the specified short. Unused in favor of the 32-bit version.
#define BIT_CLEAR(field, value) \
    BC_BBH(BHV_CMD_BIT_CLEAR, field, value)

// TODO: this one needs a better name / labelling
// Gets a random short, right shifts it the specified amount and adds min to it, then sets the specified field to that value.
#define SET_INT_RAND_RSHIFT(field, min, rshift) \
    BC_BBH(BHV_CMD_SET_INT_RAND_RSHIFT, field, min), \
    BC_H(rshift)

// Sets the specified field to a random float in the given range.
#define SET_RANDOM_FLOAT(field, min, range) \
    BC_BBH(BHV_CMD_SET_RANDOM_FLOAT, field, min), \
    BC_H(range)

// Sets the specified field to a random integer in the given range.
#define SET_RANDOM_INT(field, min, range) \
    BC_BBH(BHV_CMD_SET_RANDOM_INT, field, min), \
    BC_H(range)

// Adds a random float in the given range to the specified field.
#define ADD_RANDOM_FLOAT(field, min, range) \
    BC_BBH(BHV_CMD_ADD_RANDOM_FLOAT, field, min), \
    BC_H(range)

// TODO: better name (unused anyway)
// Gets a random short, right shifts it the specified amount and adds min to it, then adds the value to the specified field. Unused.
#define ADD_INT_RAND_RSHIFT(field, min, rshift) \
    BC_BBH(BHV_CMD_ADD_INT_RAND_RSHIFT, field, min), \
    BC_H(rshift)

// No operation. Unused.
#define CMD_NOP_1(field) \
    BC_BB(BHV_CMD_NOP_1, field)

// No operation. Unused.
#define CMD_NOP_2(field) \
    BC_BB(BHV_CMD_NOP_2, field)

// Sets the current model ID of the object.
#define SET_MODEL(modelID) \
    BC_B0H(BHV_CMD_SET_MODEL, modelID)

// Spawns a child object with the specified model and behavior.
#define SPAWN_CHILD(modelID, behavior) \
    BC_B(BHV_CMD_SPAWN_CHILD), \
    BC_W(modelID), \
    BC_PTR(behavior)

// Exits the behavior script and despawns the object.
// Often used to end behavior scripts that do not contain an infinite loop.
#define DEACTIVATE() \
    BC_B(BHV_CMD_DEACTIVATE)

// Finds the floor triangle directly under the object and moves the object down to it.
#define DROP_TO_FLOOR() \
    BC_B(BHV_CMD_DROP_TO_FLOOR)

// Sets the destination float field to the sum of the values of the given float fields.
#define SUM_FLOAT(fieldDst, fieldSrc1, fieldSrc2) \
    BC_BBBB(BHV_CMD_SUM_FLOAT, fieldDst, fieldSrc1, fieldSrc2)

// Sets the destination integer field to the sum of the values of the given integer fields. Unused.
#define SUM_INT(fieldDst, fieldSrc1, fieldSrc2) \
    BC_BBBB(BHV_CMD_SUM_INT, fieldDst, fieldSrc1, fieldSrc2)

// Billboards the current object, making it always face the camera.
#define BILLBOARD() \
    BC_B(BHV_CMD_BILLBOARD)

// Hides the current object.
#define HIDE() \
    BC_B(BHV_CMD_HIDE)

// Sets the size of the object's cylindrical hitbox.
#define SET_HITBOX(radius, height) \
    BC_B(BHV_CMD_SET_HITBOX), \
    BC_HH(radius, height)

// No operation. Unused.
#define CMD_NOP_4(field, value) \
    BC_BBH(BHV_CMD_NOP_4, field, value)

// Delays the behavior script for the number of frames given by the value of the specified field.
#define DELAY_VAR(field) \
    BC_BB(BHV_CMD_DELAY_VAR, field)

// Unused. Marks the start of a loop that will repeat a certain number of times.
// Uses a u8 as the argument, instead of a s16 like the other version does.
#define BEGIN_REPEAT_UNUSED(count) \
    BC_BB(BHV_CMD_BEGIN_REPEAT_UNUSED, count)

// Loads the animations for the object. <field> is always set to oAnimations.
#define LOAD_ANIMATIONS(field, anims) \
    BC_BB(BHV_CMD_LOAD_ANIMATIONS, field), \
    BC_PTR(anims)

// Begins animation and sets the object's current animation index to the specified value.
#define ANIMATE(animIndex) \
    BC_BB(BHV_CMD_ANIMATE, animIndex)

// Spawns a child object with the specified model and behavior, plus a behavior param.
#define SPAWN_CHILD_WITH_PARAM(bhvParam, modelID, behavior) \
    BC_B0H(BHV_CMD_SPAWN_CHILD_WITH_PARam, bhvParam), \
    BC_W(modelID), \
    BC_PTR(behavior)

// Loads collision data for the object.
#define LOAD_COLLISION_DATA(collisionData) \
    BC_B(BHV_CMD_LOAD_COLLISION_DATA), \
    BC_PTR(collisionData)

// Sets the size of the object's cylindrical hitbox, and applies a downwards offset.
#define SET_HITBOX_WITH_OFFSET(radius, height, downOffset) \
    BC_B(BHV_CMD_SET_HITBOX_WITH_OFFSet), \
    BC_HH(radius, height), \
    BC_H(downOffset)

// Spawns a new object with the specified model and behavior.
#define SPAWN_OBJ(modelID, behavior) \
    BC_B(BHV_CMD_SPAWN_OBJ), \
    BC_W(modelID), \
    BC_PTR(behavior)

// Sets the home position of the object to its current position.
#define SET_HOME() \
    BC_B(BHV_CMD_SET_HOME)

// Sets the size of the object's cylindrical hurtbox.
#define SET_HURTBOX(radius, height) \
    BC_B(BHV_CMD_SET_HURTBOX), \
    BC_HH(radius, height)

// Sets the object's interaction type.
#define SET_INTERACT_TYPE(type) \
    BC_B(BHV_CMD_SET_INTERACT_TYPE), \
    BC_W(type)

// Sets various parameters that the object uses for calculating physics.
#define SET_OBJ_PHYSICS(wallHitboxRadius, gravity, bounciness, dragStrength, friction, buoyancy, unused1, unused2) \
    BC_B(BHV_CMD_SET_OBJ_PHYSICS), \
    BC_HH(wallHitboxRadius, gravity), \
    BC_HH(bounciness, dragStrength), \
    BC_HH(friction, buoyancy), \
    BC_HH(unused1, unused2)

// Sets the object's interaction subtype. Unused.
#define SET_INTERACT_SUBTYPE(subtype) \
    BC_B(BHV_CMD_SET_INTERACT_SUBTYPE), \
    BC_W(subtype)

// Sets the object's size to the specified percentage.
#define SCALE(unusedField, percent) \
    BC_BBH(BHV_CMD_SCALE, unusedField, percent)

// Performs a bit clear on the object's parent's field with the specified value.
// Used for clearing active particle flags fron Mario's object.
#define PARENT_BIT_CLEAR(field, flags) \
    BC_BB(BHV_CMD_PARENT_BIT_CLEAR, field), \
    BC_W(flags)

// Animates an object using texture animation. <field> is always set to oAnimState.
#define ANIMATE_TEXTURE(field, rate) \
    BC_BBH(BHV_CMD_ANIMATE_TEXTURE, field, rate)

// Disables rendering for the object.
#define DISABLE_RENDERING() \
    BC_B(BHV_CMD_DISABLE_RENDERING)

// Unused. Sets the specified field to an integer. Wastes 4 bytes of space for no reason at all.
#define SET_INT_UNUSED(field, value) \
    BC_BB(BHV_CMD_SET_INT_UNUSED, field), \
    BC_HH(0, value)

// Spawns a water droplet with the given parameters.
#define SPAWN_WATER_DROPLET(dropletParams) \
    BC_B(BHV_CMD_SPAWN_WATER_DROPLET), \
    BC_PTR(dropletParams)

/* fast64 object exports get inserted here */
const BehaviorScript bhvGBananaDee[] = {
	BEGIN(OBJ_LIST_GENACTOR),
	OR_INT(oFlags, OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	SET_INTERACT_TYPE(INTERACT_TEXT),
	SET_HITBOX(130, 100),
	SET_INT(oInteractionSubtype, INT_SUBTYPE_NPC),
	LOAD_ANIMATIONS(oAnimations, g_banana_dee_anims),
	ANIMATE(0),
	BEGIN_LOOP(),
        CALL_NATIVE(bhv_npc_loop),
		SET_INT(oIntangibleTimer, 0),
		SET_INT(oInteractStatus, 0),
        SET_FLOAT(oDrawingDistance, 12000),
	END_LOOP(),
};

const BehaviorScript bhvStarDoor[] = {
    BEGIN(OBJ_LIST_SURFACE),
    SET_INT(oInteractType, INTERACT_DOOR),
    LOAD_COLLISION_DATA(inside_castle_seg7_collision_star_door),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_STAR_DOOR),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 100),
    SET_HOME(),
    SET_FLOAT(oDrawingDistance, 20000),
    CALL_NATIVE(bhv_door_init),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_star_door_loop),
        CALL_NATIVE(load_object_collision_model),
        CALL_NATIVE(bhv_door_rendering_loop),
    END_LOOP(),
};

extern void bhv_hidden_by_uv(void);

const BehaviorScript bhvMrI[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    SET_HOME(),
    SPAWN_CHILD(/*Model*/ MODEL_MR_I_IRIS, /*Behavior*/ bhvMrIIris),
    SET_MODEL(MODEL_MR_I_BODY),
    BILLBOARD(),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_mr_i_body_loop),
    END_LOOP(),
};

const BehaviorScript bhvMrIIris[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_mr_i_iris_loop),
    END_LOOP(),
};

const BehaviorScript bhvMrIParticle[] = {
    BEGIN(OBJ_LIST_LEVEL),
    BILLBOARD(),
    OR_LONG(oFlags, (OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    SET_INT(oIntangibleTimer, 0),
    SET_HITBOX(50, 50),
    SET_INT(oDamageOrCoinValue, 1),
    SET_INT(oInteractType, INTERACT_DAMAGE),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_mr_i_particle_loop),
    END_LOOP(),
};

const BehaviorScript bhvPurpleParticle[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    BILLBOARD(),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_REPEAT(10),
        CALL_NATIVE(bhv_piranha_particle_loop),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvGiantPole[] = {
    BEGIN(OBJ_LIST_POLELIKE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_INT(oInteractType, INTERACT_POLE),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 2100),
    SET_HOME(),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_giant_pole_loop),
    END_LOOP(),
};

const BehaviorScript bhvPoleGrabbing[] = {
    BEGIN(OBJ_LIST_POLELIKE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INT(oInteractType, INTERACT_POLE),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 1500),
    CALL_NATIVE(bhv_pole_init),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_pole_base_loop),
    END_LOOP(),
};

const BehaviorScript bhvThiHugeIslandTop[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(thi_seg7_collision_top_trap),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_thi_huge_island_top_loop),
    END_LOOP(),
};

const BehaviorScript bhvThiTinyIslandTop[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_thi_tiny_island_top_loop),
    END_LOOP(),
};

const BehaviorScript bhvCapSwitchBase[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(capswitch_collision_05003448),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvCapSwitch[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(capswitch_collision_050033D0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_cap_switch_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvKingBobomb[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BOSS)),//--E
    LOAD_ANIMATIONS(oAnimations, king_bobomb_seg5_anims_0500FE30),
    SET_INT(oInteractType, INTERACT_GRABBABLE),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 100),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_INT(oIntangibleTimer, 0),
    DROP_TO_FLOOR(),
    SET_HOME(),
    SPAWN_OBJ(/*Model*/ MODEL_NONE, /*Behavior*/ bhvBobombAnchorMario),
    SET_INT(oHealth, 3),
    SET_INT(oDamageOrCoinValue, 1),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_king_bobomb_loop),
    END_LOOP(),
};

const BehaviorScript bhvBobombAnchorMario[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_FLOAT(oParentRelativePosX, 100),
    SET_FLOAT(oParentRelativePosZ, 150),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bobomb_anchor_mario_loop),
    END_LOOP(),
};

const BehaviorScript bhvBetaChestBottom[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DROP_TO_FLOOR(),
    CALL_NATIVE(bhv_beta_chest_bottom_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_beta_chest_bottom_loop),
    END_LOOP(),
};

const BehaviorScript bhvBetaChestLid[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_beta_chest_lid_loop),
    END_LOOP(),
};

const BehaviorScript bhvBubbleParticleSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    DISABLE_RENDERING(),
    SET_RANDOM_INT(oWaterObjScaleXAngle, /*Minimum*/ 2, /*Range*/ 9),
    DELAY_VAR(oWaterObjScaleXAngle),
    SPAWN_CHILD(/*Model*/ MODEL_BUBBLE, /*Behavior*/ bhvSmallWaterWave),
    PARENT_BIT_CLEAR(oActiveParticleFlags, ACTIVE_PARTICLE_BUBBLE),
    DEACTIVATE(),
};

const BehaviorScript bhvBubbleMaybe[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    CALL_NATIVE(bhv_bubble_wave_init),
    SET_RANDOM_FLOAT(oWaterObjScaleXAngle, /*Minimum*/ -75, /*Range*/ 150),
    SET_RANDOM_FLOAT(oWaterObjScaleYAngle, /*Minimum*/ -75, /*Range*/ 150),
    SET_RANDOM_FLOAT(oWaterObjScaleXAngleVel, /*Minimum*/ -75, /*Range*/ 150),
    SUM_FLOAT(/*Dest*/ oPosX, /*Value 1*/ oPosX, /*Value 2*/ oWaterObjScaleXAngle),
    SUM_FLOAT(/*Dest*/ oPosZ, /*Value 1*/ oPosZ, /*Value 2*/ oWaterObjScaleYAngle),
    SUM_FLOAT(/*Dest*/ oPosY, /*Value 1*/ oPosY, /*Value 2*/ oWaterObjScaleXAngleVel),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_REPEAT(60),
        ADD_INT(oAnimState, 1),
        CALL_NATIVE(bhv_bubble_maybe_loop),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvSmallWaterWave[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    CALL_NATIVE(bhv_bubble_wave_init),
    SET_RANDOM_FLOAT(oWaterObjScaleXAngle, /*Minimum*/ -50, /*Range*/ 100),
    SET_RANDOM_FLOAT(oWaterObjScaleYAngle, /*Minimum*/ -50, /*Range*/ 100),
    SUM_FLOAT(/*Dest*/ oPosX, /*Value 1*/ oPosX, /*Value 2*/ oWaterObjScaleXAngle),
    SUM_FLOAT(/*Dest*/ oPosZ, /*Value 1*/ oPosZ, /*Value 2*/ oWaterObjScaleYAngle),
    SET_RANDOM_FLOAT(oWaterObjScaleXAngleVel, /*Minimum*/ 0, /*Range*/ 50),
    SUM_FLOAT(/*Dest*/ oPosY, /*Value 1*/ oPosY, /*Value 2*/ oWaterObjScaleXAngleVel),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    CALL(bhvSmallWaterWave398),
    BEGIN_REPEAT(60),
        CALL(bhvSmallWaterWave398),
        CALL_NATIVE(bhv_small_water_wave_loop),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvSmallWaterWave398[] = {
    ADD_INT(oAnimState, 1),
    ADD_FLOAT(oPosY, 7),
    SET_RANDOM_FLOAT(oWaterObjScaleXAngle, /*Minimum*/ -2, /*Range*/ 5),
    SET_RANDOM_FLOAT(oWaterObjScaleYAngle, /*Minimum*/ -2, /*Range*/ 5),
    SUM_FLOAT(/*Dest*/ oPosX, /*Value 1*/ oPosX, /*Value 2*/ oWaterObjScaleXAngle),
    SUM_FLOAT(/*Dest*/ oPosZ, /*Value 1*/ oPosZ, /*Value 2*/ oWaterObjScaleYAngle),
    RETURN(),
};

const BehaviorScript bhvWaterAirBubble[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 400, /*Height*/ 150, /*Downwards offset*/ -150),
    SET_INT(oIntangibleTimer, 0),
    SET_INTERACT_TYPE(INTERACT_WATER_RING),
    SET_INT(oDamageOrCoinValue, 5),
    CALL_NATIVE(bhv_water_air_bubble_init),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_water_air_bubble_loop),
    END_LOOP(),
};

const BehaviorScript bhvSmallParticle[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    BILLBOARD(),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_particle_init),
    BEGIN_REPEAT(70),
        CALL_NATIVE(bhv_particle_loop),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvPlungeBubble[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    PARENT_BIT_CLEAR(oActiveParticleFlags, ACTIVE_PARTICLE_PLUNGE_BUBBLE),
    DISABLE_RENDERING(),
    CALL_NATIVE(bhv_water_waves_init),
    DEACTIVATE(),
};

const BehaviorScript bhvSmallParticleSnow[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    BILLBOARD(),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_particle_init),
    BEGIN_REPEAT(30),
        CALL_NATIVE(bhv_particle_loop),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvSmallParticleBubbles[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    BILLBOARD(),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_particle_init),
    BEGIN_REPEAT(70),
        CALL_NATIVE(bhv_small_bubbles_loop),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvFishGroup[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_fish_group_loop),
    END_LOOP(),
};

const BehaviorScript bhvCannon[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SPAWN_CHILD(/*Model*/ MODEL_CANNON_BARREL, /*Behavior*/ bhvCannonBarrel),
    SET_INT(oInteractType, INTERACT_CANNON_BASE),
    ADD_FLOAT(oPosY, -340),
    SET_HOME(),
    SET_HITBOX(/*Radius*/ 150, /*Height*/ 150),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_cannon_base_loop),
    END_LOOP(),
};

const BehaviorScript bhvCannonBarrel[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DROP_TO_FLOOR(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_cannon_barrel_loop),
    END_LOOP(),
};

const BehaviorScript bhvCannonBaseUnused[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_REPEAT(8),
        CALL_NATIVE(bhv_cannon_base_unused_loop),
        ADD_INT(oAnimState, 1),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvChuckya[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    LOAD_ANIMATIONS(oAnimations, chuckya_seg8_anims_0800C070),
    ANIMATE(CHUCKYA_ANIM_SPAWN),
    SET_INT(oInteractType, INTERACT_GRABBABLE),
    SET_HITBOX(/*Radius*/ 150, /*Height*/ 100),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SPAWN_OBJ(/*Model*/ MODEL_NONE, /*Behavior*/ bhvChuckyaAnchorMario),
    SET_INT(oNumLootCoins, 5),
    SET_INT(oHealth, 3),//--E
    SET_INT(oIntangibleTimer, 0),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_chuckya_loop),
    END_LOOP(),
};

const BehaviorScript bhvChuckyaAnchorMario[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_FLOAT(oParentRelativePosY, -60),
    SET_FLOAT(oParentRelativePosZ, 150),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_chuckya_anchor_mario_loop),
    END_LOOP(),
};

const BehaviorScript bhvRotatingPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_rotating_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvTower[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(wf_seg7_collision_tower),
    SET_FLOAT(oDrawingDistance, 20000),
    CALL_NATIVE(load_object_static_model),
    BREAK(),
};

const BehaviorScript bhvBulletBillCannon[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_COLLISION_BREAKABLE)),//--E
    SET_HITBOX(/*Radius*/ 300, /*Height*/ 400),
    LOAD_COLLISION_DATA(wf_seg7_collision_bullet_bill_cannon),
    CALL_NATIVE(load_object_static_model),
    BREAK(),
};

const BehaviorScript bhvWfBreakableWallRight[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(wf_seg7_collision_breakable_wall),
    GOTO(bhvWfBreakableWallLeft + 1 + 2),
};

const BehaviorScript bhvWfBreakableWallLeft[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(wf_seg7_collision_breakable_wall_2),
    // WF breakable walls - common:
    OR_LONG(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_COLLISION_BREAKABLE)),//--E
    SET_HITBOX(/*Radius*/ 300, /*Height*/ 400),
    SET_FLOAT(oDrawingDistance, 4500),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_wf_breakable_wall_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvKickableBoard[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(wf_seg7_collision_kickable_board),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 1200),
    SET_HURTBOX(/*Radius*/ 1, /*Height*/ 1),
    SET_FLOAT(oCollisionDistance, 1500),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_kickable_board_loop),
    END_LOOP(),
};

const BehaviorScript bhvTowerDoor[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(wf_seg7_collision_tower_door),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 100),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tower_door_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvRotatingCounterClockwise[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    BREAK(),
};

const BehaviorScript bhvWfRotatingWoodenPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(wf_seg7_collision_clocklike_rotation),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_wf_rotating_wooden_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvKoopaShellUnderwater[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SILHOUETTE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_koopa_shell_underwater_loop),
    END_LOOP(),
};

const BehaviorScript bhvExitPodiumWarp[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_INT(oInteractType, INTERACT_WARP),
    DROP_TO_FLOOR(),
    SET_FLOAT(oDrawingDistance, 8000),
    SET_FLOAT(oCollisionDistance, 8000),
    LOAD_COLLISION_DATA(ttm_seg7_collision_podium_warp),
    SET_INT(oIntangibleTimer, 0),
    SET_HITBOX(/*Radius*/ 50, /*Height*/ 50),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
        SET_INT(oInteractStatus, INT_STATUS_NONE),
    END_LOOP(),
};

const BehaviorScript bhvFadingWarp[] = {
    BEGIN(OBJ_LIST_LEVEL),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_FADING_WARP),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_INT(oInteractType, INTERACT_WARP),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_fading_warp_loop),
    END_LOOP(),
};

const BehaviorScript bhvWarp[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_INT(oInteractType, INTERACT_WARP),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_warp_loop),
    END_LOOP(),
};

const BehaviorScript bhvWarpPipe[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_INT(oInteractType, INTERACT_WARP),
    LOAD_COLLISION_DATA(warp_pipe_seg3_collision_03009AC8),
    SET_FLOAT(oDrawingDistance, 16000),
    SET_INT(oIntangibleTimer, 0),
    SET_HITBOX(/*Radius*/ 70, /*Height*/ 50),
    CALL_NATIVE(load_object_static_model),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_warp_loop),
    END_LOOP(),
};

const BehaviorScript bhvWhitePuffExplosion[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_white_puff_exploding_loop),
    END_LOOP(),
};

const BehaviorScript bhvSpawnedStar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INT(oBehParams2ndByte, SPAWN_STAR_POS_CUTSCENE_BP_SPAWN_AT_HOME),
    GOTO(bhvSpawnedStarNoLevelExit + 1 + 1),
};

const BehaviorScript bhvSpawnedStarNoLevelExit[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    // Spawned star - common:
    SET_HOME(),
    CALL_NATIVE(bhv_spawned_star_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_spawned_star_loop),
    END_LOOP(),
};

const BehaviorScript bhvMrIBlueCoin[] = {
    BEGIN(OBJ_LIST_LEVEL),
    SET_INT(oInteractType, INTERACT_COIN),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_INT(oIntangibleTimer, 0),
    SET_FLOAT(oCoinBaseYVel, 20),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_coin_init),
    SET_INT(oDamageOrCoinValue, 5),
    SET_HITBOX(/*Radius*/ 120, /*Height*/ 64),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_coin_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvCoinInsideBoo[] = {
    BEGIN(OBJ_LIST_LEVEL),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 64),
    SET_INT(oInteractType, INTERACT_COIN),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BILLBOARD(),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_coin_inside_boo_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvCoinFormationSpawnedCoin[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_coin_formation_spawned_coin_loop),
    END_LOOP(),
};

const BehaviorScript bhvCoinFormation[] = {
    BEGIN(OBJ_LIST_SPAWNER),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_coin_formation_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_coin_formation_loop),
    END_LOOP(),
};

const BehaviorScript bhvOneCoin[] = {
    BEGIN(OBJ_LIST_LEVEL),
    SET_INT(oBehParams2ndByte, YELLOW_COIN_BP_ONE_COIN),
    GOTO(bhvYellowCoin + 1),
};

const BehaviorScript bhvYellowCoin[] = {
    BEGIN(OBJ_LIST_LEVEL),
    // Yellow coin - common:
    BILLBOARD(),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_init_room),
    CALL_NATIVE(bhv_yellow_coin_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_yellow_coin_loop),
    END_LOOP(),
};

const BehaviorScript bhvTemporaryYellowCoin[] = {
    BEGIN(OBJ_LIST_LEVEL),
    BILLBOARD(),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_init_room),
    CALL_NATIVE(bhv_yellow_coin_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_temp_coin_loop),
    END_LOOP(),
};

const BehaviorScript bhvThreeCoinsSpawn[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_REPEAT(3),
        SPAWN_CHILD(/*Model*/ MODEL_YELLOW_COIN, /*Behavior*/ bhvSingleCoinGetsSpawned),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvTenCoinsSpawn[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_REPEAT(10),
        SPAWN_CHILD(/*Model*/ MODEL_YELLOW_COIN, /*Behavior*/ bhvSingleCoinGetsSpawned),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvSingleCoinGetsSpawned[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    CALL_NATIVE(bhv_coin_init),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_coin_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvCoinSparkles[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_FLOAT(oGraphYOffset, 25),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_REPEAT(8),
        ADD_INT(oAnimState, 1),
    END_REPEAT(),
    BEGIN_REPEAT(2),
        CALL_NATIVE(bhv_coin_sparkles_loop),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvCoinSparklesSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    DISABLE_RENDERING(),
    BEGIN_REPEAT(3),
        CALL_NATIVE(bhv_golden_coin_sparkles_loop),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvWallTinyStarParticle[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    BEGIN_REPEAT(10),
        CALL_NATIVE(bhv_wall_tiny_star_particle_loop),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvVertStarParticleSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    DISABLE_RENDERING(),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    PARENT_BIT_CLEAR(oActiveParticleFlags, ACTIVE_PARTICLE_V_STAR),
    CALL_NATIVE(bhv_tiny_star_particles_init),
    DELAY(1),
    DEACTIVATE(),
};

const BehaviorScript bhvPoundTinyStarParticle[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    BEGIN_REPEAT(10),
        CALL_NATIVE(bhv_pound_tiny_star_particle_loop),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvHorStarParticleSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    DISABLE_RENDERING(),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    PARENT_BIT_CLEAR(oActiveParticleFlags, ACTIVE_PARTICLE_H_STAR),
    CALL_NATIVE(bhv_pound_tiny_star_particle_init),
    DELAY(1),
    DEACTIVATE(),
};

const BehaviorScript bhvPunchTinyTriangle[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_punch_tiny_triangle_loop),
    END_LOOP(),
};

const BehaviorScript bhvTriangleParticleSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    DISABLE_RENDERING(),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    PARENT_BIT_CLEAR(oActiveParticleFlags, ACTIVE_PARTICLE_TRIANGLE),
    CALL_NATIVE(bhv_punch_tiny_triangle_init),
    DELAY(1),
    DEACTIVATE(),
};

const BehaviorScript bhvDoorWarp[] = {
    BEGIN(OBJ_LIST_SURFACE),
    SET_INT(oInteractType, INTERACT_WARP_DOOR),
    GOTO(bhvDoor + 1 + 1),
};

const BehaviorScript bhvDoor[] = {
    BEGIN(OBJ_LIST_SURFACE),
    SET_INT(oInteractType, INTERACT_DOOR),
    // Door - common:
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, door_seg3_anims_030156C0),
    ANIMATE(DOOR_ANIM_CLOSED),
    LOAD_COLLISION_DATA(door_seg3_collision_door),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 100),
    SET_INT(oIntangibleTimer, 0),
    SET_FLOAT(oCollisionDistance, 1000),
    SET_HOME(),
    CALL_NATIVE(bhv_door_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_door_loop),
    END_LOOP(),
};

const BehaviorScript bhvDoorFake[] = {
    BEGIN(OBJ_LIST_SURFACE),
    // Door - common:
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, door_seg3_anims_030156C0),
    ANIMATE(DOOR_ANIM_CLOSED),
    LOAD_COLLISION_DATA(door_seg3_collision_door),
    SET_FLOAT(oCollisionDistance, 1000),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvGrindel[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(ssl_seg7_collision_grindel),
    DROP_TO_FLOOR(),
    ADD_FLOAT(oPosY, 1),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_grindel_thwomp_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvThwomp2[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(thwomp_seg5_collision_0500B92C),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DROP_TO_FLOOR(),
    ADD_FLOAT(oPosY, 1),
    SET_HOME(),
    SCALE(/*Unused*/ 0, /*Field*/ 140),
    SET_FLOAT(oDrawingDistance, 4000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_grindel_thwomp_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvThwomp[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(thwomp_seg5_collision_0500B7D0),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DROP_TO_FLOOR(),
    ADD_FLOAT(oPosY, 1),
    SCALE(/*Unused*/ 0, /*Field*/ 140),
    SET_HOME(),
    SET_FLOAT(oDrawingDistance, 4000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_grindel_thwomp_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvTumblingBridgePlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oCollisionDistance, 300),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tumbling_bridge_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvWfTumblingBridge[] = {
    BEGIN(OBJ_LIST_SPAWNER),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tumbling_bridge_loop),
    END_LOOP(),
};

const BehaviorScript bhvBbhTumblingBridge[] = {
    BEGIN(OBJ_LIST_SPAWNER),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    SET_INT(oBehParams2ndByte, TUMBLING_BRIDGE_BP_BBH),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tumbling_bridge_loop),
    END_LOOP(),
};

const BehaviorScript bhvLllTumblingBridge[] = {
    BEGIN(OBJ_LIST_SPAWNER),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    SET_INT(oBehParams2ndByte, TUMBLING_BRIDGE_BP_LLL),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tumbling_bridge_loop),
    END_LOOP(),
};

const BehaviorScript bhvFlame[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_HOME(),
    SCALE(/*Unused*/ 0, /*Field*/ 700),
    SET_INTERACT_TYPE(INTERACT_FLAME),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 50, /*Height*/ 25, /*Downwards offset*/ 25),
    SET_INT(oIntangibleTimer, 0),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        SET_INT(oInteractStatus, INT_STATUS_NONE),
        ANIMATE_TEXTURE(oAnimState, 2),
    END_LOOP(),
};

const BehaviorScript bhvAnotherElavator[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(hmc_seg7_collision_elevator),
    SET_HOME(),
    CALL_NATIVE(bhv_elevator_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_elevator_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvRrElevatorPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(rr_seg7_collision_elevator_platform),
    SET_HOME(),
    CALL_NATIVE(bhv_elevator_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_elevator_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvHmcElevatorPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(hmc_seg7_collision_elevator),
    SET_HOME(),
    CALL_NATIVE(bhv_elevator_init),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_elevator_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvWaterMist[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_INT(oOpacity, 254),
    SET_FLOAT(oForwardVel, 20),
    SET_FLOAT(oVelY, -8),
    ADD_FLOAT(oPosY, 62),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_water_mist_loop),
    END_LOOP(),
};

const BehaviorScript bhvBreathParticleSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_REPEAT(8),
        CALL_NATIVE(bhv_water_mist_spawn_loop),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvBreakBoxTriangle[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_REPEAT(18),
        CALL_NATIVE(cur_obj_rotate_face_angle_using_vel),
        CALL_NATIVE(cur_obj_move_using_fvel_and_gravity),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvWaterMist2[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    SET_INT(oFaceAnglePitch, 0xC000),
    SCALE(/*Unused*/ 0, /*Field*/ 2100),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_water_mist_2_loop),
    END_LOOP(),
};

const BehaviorScript bhvMistCircParticleSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_pound_white_puffs_init),
    DELAY(1),
    DEACTIVATE(),
};

const BehaviorScript bhvDirtParticleSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_ground_sand_init),
    DELAY(1),
    DEACTIVATE(),
};

const BehaviorScript bhvSnowParticleSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_ground_snow_init),
    DELAY(1),
    DEACTIVATE(),
};

const BehaviorScript bhvWind[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_wind_loop),
    END_LOOP(),
};

const BehaviorScript bhvEndToad[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_ANIMATIONS(oAnimations, toad_seg6_anims_0600FB58),
    ANIMATE(TOAD_ANIM_WEST_WAVE_THEN_TURN),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_end_toad_loop),
    END_LOOP(),
};

const BehaviorScript bhvEndPeach[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_ANIMATIONS(oAnimations, peach_seg5_anims_0501C41C),
    ANIMATE(PEACH_ANIM_0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_end_peach_loop),
    END_LOOP(),
};

const BehaviorScript bhvUnusedParticleSpawn[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_INT(oIntangibleTimer, 0),
    SET_HITBOX(/*Radius*/ 40, /*Height*/ 40),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_unused_particle_spawn_loop),
    END_LOOP(),
};

const BehaviorScript bhvUkiki[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    GOTO(bhvMacroUkiki + 1),
};

const BehaviorScript bhvUkikiCageChild[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_FLOAT(oPosX, 2560),
    SET_FLOAT(oPosY, 1457),
    SET_FLOAT(oPosZ, 1898),
    BREAK(),
};

const BehaviorScript bhvUkikiCageStar[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ukiki_cage_star_loop),
    END_LOOP(),
};

const BehaviorScript bhvUkikiCage[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
    SET_HOME(),
    LOAD_COLLISION_DATA(ttm_seg7_collision_ukiki_cage),
    SPAWN_CHILD(/*Model*/ MODEL_STAR, /*Behavior*/ bhvUkikiCageStar),
    SPAWN_CHILD(/*Model*/ MODEL_NONE, /*Behavior*/ bhvUkikiCageChild),
    SET_FLOAT(oCollisionDistance, 20000),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ukiki_cage_loop),
    END_LOOP(),
};

const BehaviorScript bhvBitfsSinkingPlatforms[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(bitfs_seg7_collision_sinking_platform),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bitfs_sinking_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvBitfsSinkingCagePlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(bitfs_seg7_collision_sinking_cage_platform),
    SET_HOME(),
    SPAWN_CHILD(/*Model*/ MODEL_BITFS_BLUE_POLE, /*Behavior*/ bhvDddMovingPole),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bitfs_sinking_cage_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvDddMovingPole[] = {
    BEGIN(OBJ_LIST_POLELIKE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_INT(oInteractType, INTERACT_POLE),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 710),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ddd_moving_pole_loop),
        CALL_NATIVE(bhv_pole_base_loop),
    END_LOOP(),
};

const BehaviorScript bhvBitfsTiltingInvertedPyramid[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(bitfs_seg7_collision_inverted_pyramid),
    SET_HOME(),
    CALL_NATIVE(bhv_platform_normals_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tilting_inverted_pyramid_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvSquishablePlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
    LOAD_COLLISION_DATA(bitfs_seg7_collision_squishable_platform),
    SET_FLOAT(oCollisionDistance, 10000),
    CALL_NATIVE(bhv_platform_normals_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_squishable_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvCutOutObject[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    DISABLE_RENDERING(),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BREAK(),
};

const BehaviorScript bhvBetaMovingFlamesSpawn[] = {
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_beta_moving_flames_spawn_loop),
    END_LOOP(),
};

const BehaviorScript bhvBetaMovingFlames[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_beta_moving_flames_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvRrRotatingBridgePlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(rr_seg7_collision_rotating_platform_with_fire),
    SET_FLOAT(oCollisionDistance, 1500),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_rr_rotating_bridge_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvFlamethrower[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_flamethrower_loop),
    END_LOOP(),
};

const BehaviorScript bhvFlamethrowerFlame[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INTERACT_TYPE(INTERACT_FLAME),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 50, /*Height*/ 25, /*Downwards offset*/ 25),
    BILLBOARD(),
    SET_HOME(),
    SET_INT(oIntangibleTimer, 0),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_flamethrower_flame_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvBouncingFireball[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DISABLE_RENDERING(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bouncing_fireball_spawner_loop),
    END_LOOP(),
};

const BehaviorScript bhvBouncingFireballFlame[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INTERACT_TYPE(INTERACT_FLAME),
    SET_FLOAT(oGraphYOffset, 30),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 50, /*Height*/ 25, /*Downwards offset*/ 25),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bouncing_fireball_flame_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvBowserShockWave[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_INT(oOpacity, 255),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bowser_shock_wave_loop),
    END_LOOP(),
};

const BehaviorScript bhvFireParticleSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_FLOAT(oGraphYOffset, 70),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_LOOP(),
        ADD_INT(oAnimState, 1),
        CALL_NATIVE(bhv_flame_mario_loop),
    END_LOOP(),
};

const BehaviorScript bhvBlackSmokeMario[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_FLOAT(oGraphYOffset, 50),
#ifdef BURN_SMOKE_FIX
    SET_INT(oOpacity, 255),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_black_smoke_mario_loop),
    END_LOOP(),
#else
    BEGIN_REPEAT(8),
        CALL_NATIVE(bhv_black_smoke_mario_loop),
        DELAY(1),
        CALL_NATIVE(bhv_black_smoke_mario_loop),
        DELAY(1),
        CALL_NATIVE(bhv_black_smoke_mario_loop),
    END_REPEAT(),
    DEACTIVATE(),
#endif
};

const BehaviorScript bhvBlackSmokeBowser[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_FLOAT(oGraphYOffset, 0),
    BEGIN_REPEAT(8),
        CALL_NATIVE(bhv_black_smoke_bowser_loop),
        ANIMATE_TEXTURE(oAnimState, 4),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvBlackSmokeUpward[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_REPEAT(4),
        CALL_NATIVE(bhv_black_smoke_upward_loop),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvBetaFishSplashSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DISABLE_RENDERING(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_beta_fish_splash_spawner_loop),
    END_LOOP(),
};

const BehaviorScript bhvSpindrift[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    LOAD_ANIMATIONS(oAnimations, spindrift_seg5_anims_05002D68),
    ANIMATE(SPINDRIFT_ANIM_DEFAULT),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_HOME(),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_TWIRL_BOUNCE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_spindrift_loop),
    END_LOOP(),
};

const BehaviorScript bhvTowerPlatformGroup[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    DISABLE_RENDERING(),
    ADD_FLOAT(oPosY, 300),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tower_platform_group_loop),
    END_LOOP(),
};

const BehaviorScript bhvWfSlidingTowerPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(wf_seg7_collision_platform),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_wf_sliding_tower_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvWfElevatorTowerPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(wf_seg7_collision_platform),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_wf_elevator_tower_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvWfSolidTowerPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(wf_seg7_collision_platform),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_wf_solid_tower_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvLeafParticleSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_snow_leaf_particle_spawn_init),
    DELAY(1),
    DEACTIVATE(),
};

const BehaviorScript bhvTreeSnow[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, (OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tree_snow_or_leaf_loop),
    END_LOOP(),
};

const BehaviorScript bhvTreeLeaf[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, (OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tree_snow_or_leaf_loop),
    END_LOOP(),
};

const BehaviorScript bhvAnotherTiltingPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    CALL_NATIVE(bhv_platform_normals_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tilting_inverted_pyramid_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvSquarishPathMoving[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(bitdw_seg7_collision_moving_pyramid),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_squarish_path_moving_loop),
    END_LOOP(),
};

const BehaviorScript bhvPiranhaPlantBubble[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_piranha_plant_bubble_loop),
    END_LOOP(),
};

const BehaviorScript bhvPiranhaPlantWakingBubbles[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    BILLBOARD(),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_REPEAT(10),
        CALL_NATIVE(bhv_piranha_plant_waking_bubbles_loop),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvFloorSwitchAnimatesObject[] = {
    BEGIN(OBJ_LIST_SURFACE),
    SET_INT(oBehParams2ndByte, PURPLE_SWITCH_BP_ANIMATES),
    GOTO(bhvFloorSwitchHardcodedModel + 1),
};

const BehaviorScript bhvFloorSwitchGrills[] = {
    BEGIN(OBJ_LIST_SURFACE),
    GOTO(bhvFloorSwitchHardcodedModel + 1),
};

const BehaviorScript bhvFloorSwitchHardcodedModel[] = {
    BEGIN(OBJ_LIST_SURFACE),
    // Floor switch - common:
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW)),//--E
    LOAD_COLLISION_DATA(purple_switch_seg8_collision_0800C7A8),
    SET_INT(oIntangibleTimer, 0),//--E
    SET_HITBOX(/*Radius*/ 160, /*Height*/ 100),//--E
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_purple_switch_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvGCannonSwitch[] = {
    BEGIN(OBJ_LIST_SURFACE),
    // Floor switch - common:
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW)),//--E
    LOAD_COLLISION_DATA(purple_switch_seg8_collision_0800C7A8),
    SET_FLOAT(oDrawingDistance, 16000),
    SET_INT(oIntangibleTimer, 0),//--E
    SET_HITBOX(/*Radius*/ 160, /*Height*/ 100),//--E
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_cannon_switch_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvFloorSwitchHiddenObjects[] = {
    BEGIN(OBJ_LIST_SURFACE),
    SET_INT(oBehParams2ndByte, PURPLE_SWITCH_BP_REVEAL_HIDDEN),
    GOTO(bhvFloorSwitchHardcodedModel + 1),
};

const BehaviorScript bhvHiddenObject[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(breakable_box_seg8_collision),
    SET_FLOAT(oCollisionDistance, 300),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hidden_object_loop),
    END_LOOP(),
};

const BehaviorScript bhvBreakableBox[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    LOAD_COLLISION_DATA(breakable_box_seg8_collision),
    SET_FLOAT(oCollisionDistance, 1000),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_breakable_box_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
    BREAK(),
};

const BehaviorScript bhvPushableMetalBox[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(metal_box_seg8_collision_08024C28),
    SET_FLOAT(oCollisionDistance, 500),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_pushable_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvHeaveHo[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BOSS)),//--E
    LOAD_ANIMATIONS(oAnimations, heave_ho_seg5_anims_0501534C),
    ANIMATE(HEAVE_HO_ANIM_MOVING),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 200, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 600, /*Unused*/ 0, 0),
    SPAWN_OBJ(/*Model*/ MODEL_NONE, /*Behavior*/ bhvHeaveHoThrowMario),
    SET_INT(oInteractType, INTERACT_GRABBABLE),
    SET_INT(oInteractionSubtype, (INT_SUBTYPE_NOT_GRABBABLE | INT_SUBTYPE_GRABS_MARIO)),
    SET_HITBOX(/*Radius*/ 120, /*Height*/ 100),
    SET_HOME(),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_heave_ho_loop),
    END_LOOP(),
};

const BehaviorScript bhvHeaveHoThrowMario[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_heave_ho_throw_mario_loop),
    END_LOOP(),
};

const BehaviorScript bhvCcmTouchedStarSpawn[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HITBOX(/*Radius*/ 500, /*Height*/ 500),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ccm_touched_star_spawn_loop),
    END_LOOP(),
};

const BehaviorScript bhvUnusedPoundablePlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(sl_seg7_collision_pound_explodes),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_unused_poundable_platform),
    END_LOOP(),
};

const BehaviorScript bhvBetaTrampolineTop[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(springboard_collision_05001A28),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_beta_trampoline_top_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvBetaTrampolineSpring[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_beta_trampoline_spring_loop),
    END_LOOP(),
};

const BehaviorScript bhvJumpingBox[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO  | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 600, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_jumping_box_loop),
    END_LOOP(),
};

const BehaviorScript bhvBooCage[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oGraphYOffset, 10),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_boo_cage_loop),
    END_LOOP(),
};

const BehaviorScript bhvStub[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    DISABLE_RENDERING(),
    BREAK(),
};

const BehaviorScript bhvIgloo[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INTERACT_TYPE(INTERACT_IGLOO_BARRIER),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 200),
    SET_INT(oIntangibleTimer, 0),
    SET_HOME(),
    BEGIN_LOOP(),
        SET_INT(oInteractStatus, INT_STATUS_NONE),
    END_LOOP(),
};

const BehaviorScript bhvBowserKey[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bowser_key_loop),
    END_LOOP(),
};

const BehaviorScript bhvGrandStar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INTERACT_TYPE(INTERACT_STAR_OR_KEY),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_GRAND_STAR),
    SET_HITBOX(/*Radius*/ 160, /*Height*/ 100),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_grand_star_loop),
    END_LOOP(),
};

const BehaviorScript bhvBetaBooKey[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HITBOX(/*Radius*/ 32, /*Height*/ 64),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_beta_boo_key_loop),
    END_LOOP(),
};

const BehaviorScript bhvAlphaBooKey[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HITBOX(/*Radius*/ 32, /*Height*/ 64),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_alpha_boo_key_loop),
    END_LOOP(),
};

const BehaviorScript bhvBulletBill[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    SET_HOME(),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 50, /*Height*/ 50, /*Downwards offset*/ 50),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    SET_INT(oDamageOrCoinValue, 3),
    SCALE(/*Unused*/ 0, /*Field*/ 40),
    SET_INT(oIntangibleTimer, 0),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_bullet_bill_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bullet_bill_loop),
    END_LOOP(),
};

const BehaviorScript bhvWhitePuffSmoke[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    ADD_FLOAT(oPosY, -100),
    CALL_NATIVE(bhv_white_puff_smoke_init),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_REPEAT(10),
        ADD_INT(oAnimState, 1),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvBowserTailAnchor[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 100, /*Height*/ 50, /*Downwards offset*/ -50),
    SET_INT(oIntangibleTimer, 0),
    DISABLE_RENDERING(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bowser_tail_anchor_loop),
    END_LOOP(),
};

const BehaviorScript bhvBowser[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BOSS)),//--E
    SET_INT(oInteractType, INTERACT_GRABBABLE),
    SET_HITBOX(/*Radius*/ 400, /*Height*/ 400),
    DROP_TO_FLOOR(),
    SET_HOME(),
    LOAD_ANIMATIONS(oAnimations, bowser_seg6_anims_06057690),
    SPAWN_CHILD(/*Model*/ MODEL_NONE, /*Behavior*/ bhvBowserBodyAnchor),
    SPAWN_CHILD(/*Model*/ MODEL_BOWSER_BOMB_CHILD_OBJ, /*Behavior*/ bhvBowserFlameSpawn),
    SPAWN_OBJ(/*Model*/ MODEL_NONE, /*Behavior*/ bhvBowserTailAnchor),
    // Beta leftover that spawn 50 coins when Bowser is defeated
    SET_INT(oNumLootCoins, 50),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_HOME(),
    CALL_NATIVE(bhv_bowser_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bowser_loop),
    END_LOOP(),
};

const BehaviorScript bhvBowserBodyAnchor[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 300),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_BIG_KNOCKBACK),
    DISABLE_RENDERING(),
    SET_INT(oDamageOrCoinValue, 2),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bowser_body_anchor_loop),
    END_LOOP(),
};

const BehaviorScript bhvBowserFlameSpawn[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_MODEL(MODEL_NONE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bowser_flame_spawn_loop),
    END_LOOP(),
};

const BehaviorScript bhvTiltingBowserLavaPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
    LOAD_COLLISION_DATA(bowser_2_seg7_collision_tilting_platform),
    SET_FLOAT(oDrawingDistance, 20000),
    SET_FLOAT(oCollisionDistance, 20000),
    SET_INT(oFaceAngleYaw, 0x0),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(cur_obj_rotate_face_angle_using_vel),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvFallingBowserPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
    SET_FLOAT(oDrawingDistance, 20000),
    SET_FLOAT(oCollisionDistance, 20000),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_falling_bowser_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvBlueBowserFlame[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INTERACT_TYPE(INTERACT_FLAME),
    BILLBOARD(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_blue_bowser_flame_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_blue_bowser_flame_loop),
        ANIMATE_TEXTURE(oAnimState, 2),
    END_LOOP(),
};

const BehaviorScript bhvFlameFloatingLanding[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INTERACT_TYPE(INTERACT_FLAME),
    BILLBOARD(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_flame_floating_landing_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_flame_floating_landing_loop),
        ANIMATE_TEXTURE(oAnimState, 2),
    END_LOOP(),
};

const BehaviorScript bhvBlueFlamesGroup[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_INTERACT_TYPE(INTERACT_FLAME),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_blue_flames_group_loop),
    END_LOOP(),
};

const BehaviorScript bhvFlameBouncing[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_INTERACT_TYPE(INTERACT_FLAME),
    BILLBOARD(),
    CALL_NATIVE(bhv_flame_bouncing_init),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_flame_bouncing_loop),
        ANIMATE_TEXTURE(oAnimState, 2),
    END_LOOP(),
};

const BehaviorScript bhvFlameMovingForwardGrowing[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INTERACT_TYPE(INTERACT_FLAME),
    BILLBOARD(),
    CALL_NATIVE(bhv_flame_moving_forward_growing_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_flame_moving_forward_growing_loop),
        ANIMATE_TEXTURE(oAnimState, 2),
    END_LOOP(),
};

const BehaviorScript bhvFlameBowser[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INTERACT_TYPE(INTERACT_FLAME),
    BILLBOARD(),
    CALL_NATIVE(bhv_flame_bowser_init),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_flame_bowser_loop),
        ANIMATE_TEXTURE(oAnimState, 2),
    END_LOOP(),
};

const BehaviorScript bhvFlameLargeBurningOut[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INTERACT_TYPE(INTERACT_FLAME),
    BILLBOARD(),
    CALL_NATIVE(bhv_flame_large_burning_out_init),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_flame_bowser_loop),
        ANIMATE_TEXTURE(oAnimState, 2),
    END_LOOP(),
};

const BehaviorScript bhvBlueFish[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    LOAD_ANIMATIONS(oAnimations, blue_fish_seg3_anims_0301C2B0),
    ANIMATE(FISH_ANIM_DEFAULT),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_blue_fish_movement_loop),
    END_LOOP(),
};

const BehaviorScript bhvTankFishGroup[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tank_fish_group_loop),
    END_LOOP(),
};

const BehaviorScript bhvCheckerboardElevatorGroup[] = {
    BEGIN(OBJ_LIST_SPAWNER),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_checkerboard_elevator_group_init),
    DELAY(1),
    DEACTIVATE(),
};

const BehaviorScript bhvCheckerboardPlatformSub[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(checkerboard_platform_seg8_collision_platform),
    CALL_NATIVE(bhv_checkerboard_platform_init),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_checkerboard_platform_loop),
    END_LOOP(),
};

const BehaviorScript bhvBowserKeyUnlockDoor[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    LOAD_ANIMATIONS(oAnimations, bowser_key_seg3_anims_list),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bowser_key_unlock_door_loop),
    END_LOOP(),
};

const BehaviorScript bhvBowserKeyCourseExit[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    LOAD_ANIMATIONS(oAnimations, bowser_key_seg3_anims_list),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bowser_key_course_exit_loop),
    END_LOOP(),
};

const BehaviorScript bhvInvisibleObjectsUnderBridge[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    CALL_NATIVE(bhv_invisible_objects_under_bridge_init),
    BREAK(),
};

const BehaviorScript bhvWaterLevelPillar[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(inside_castle_seg7_collision_water_level_pillar),
    CALL_NATIVE(bhv_water_level_pillar_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_water_level_pillar_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvDddWarp[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_FLOAT(oCollisionDistance, 30000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ddd_warp_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvMoatGrills[] = {
    BEGIN(OBJ_LIST_SURFACE),
#ifdef UNLOCK_ALL
    DEACTIVATE(),
#else
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(castle_grounds_seg7_collision_moat_grills),
    SET_FLOAT(oCollisionDistance, 30000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_moat_grills_loop),
    END_LOOP(),
#endif
};

const BehaviorScript bhvClockMinuteHand[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    SET_INT(oAngleVelRoll, -0x180),
    GOTO(bhvClockHourHand + 1 + 1),
};

const BehaviorScript bhvClockHourHand[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    SET_INT(oAngleVelRoll, -0x20),
    // Clock hand - common:
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_rotating_clock_arm_loop),
    END_LOOP(),
};

const BehaviorScript bhvMacroUkiki[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    // Ukiki - common:
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BOSS)),//--E
    SET_INT(oInteractType, INTERACT_GRABBABLE),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_HOLDABLE_NPC),
    SET_HITBOX(/*Radius*/ 40, /*Height*/ 40),
    SET_INT(oIntangibleTimer, 0),
    DROP_TO_FLOOR(),
    LOAD_ANIMATIONS(oAnimations, ukiki_seg5_anims_05015784),
    ANIMATE(UKIKI_ANIM_RUN),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_HOME(),
    CALL_NATIVE(bhv_ukiki_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ukiki_loop),
    END_LOOP(),
};

const BehaviorScript bhvLllRotatingHexagonalPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
    LOAD_COLLISION_DATA(lll_seg7_collision_hexagonal_platform),
    SET_HOME(),
    BEGIN_LOOP(),
        SET_INT(oAngleVelYaw,  0x100),
        ADD_INT(oMoveAngleYaw, 0x100),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvLllSinkingRockBlock[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(lll_seg7_collision_floating_block),
    ADD_FLOAT(oPosY, -50),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_lll_sinking_rock_block_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvLllMovingOctagonalMeshPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    ADD_FLOAT(oPosY, -50),
    LOAD_COLLISION_DATA(lll_seg7_collision_octagonal_moving_platform),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_lll_moving_octagonal_mesh_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvSnowBall[] = {
    BREAK(),
};

const BehaviorScript bhvLllRotatingBlockWithFireBars[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(lll_seg7_collision_rotating_fire_bars),
    SET_FLOAT(oCollisionDistance, 4000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_lll_rotating_block_fire_bars_loop),
    END_LOOP(),
};

const BehaviorScript bhvLllRotatingHexFlame[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_INTERACT_TYPE(INTERACT_FLAME),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 50, /*Height*/ 100, /*Downwards offset*/ 50),
    SET_INT(oIntangibleTimer, 0),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_lll_rotating_hex_flame_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvLllWoodPiece[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(lll_seg7_collision_wood_piece),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_lll_wood_piece_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvLllFloatingWoodBridge[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_MODEL(MODEL_NONE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_lll_floating_wood_bridge_loop),
    END_LOOP(),
};

const BehaviorScript bhvVolcanoFlames[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    BEGIN_LOOP(),
        ADD_INT(oAnimState, 1),
        CALL_NATIVE(bhv_volcano_flames_loop),
    END_LOOP(),
};

const BehaviorScript bhvLllRotatingHexagonalRing[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(lll_seg7_collision_rotating_platform),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_lll_rotating_hexagonal_ring_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvLllSinkingRectangularPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(lll_seg7_collision_slow_tilting_platform),
    SET_FLOAT(oCollisionDistance, 2000),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_lll_sinking_rectangular_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvLllSinkingSquarePlatforms[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(lll_seg7_collision_sinking_pyramids),
    ADD_FLOAT(oPosY, 5),
    SET_FLOAT(oCollisionDistance, 2000),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_lll_sinking_square_platforms_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvLllTiltingInvertedPyramid[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(lll_seg7_collision_inverted_pyramid),
    ADD_FLOAT(oPosY, 5),
    SET_HOME(),
    CALL_NATIVE(bhv_platform_normals_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tilting_inverted_pyramid_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvKoopaShell[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SILHOUETTE)), //! Silhouette doesn't show up in-game, due to combiner modes.
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_koopa_shell_loop),
    END_LOOP(),
};

const BehaviorScript bhvKoopaShellFlame[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INTERACT_TYPE(INTERACT_FLAME),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_koopa_shell_flame_loop),
        ANIMATE_TEXTURE(oAnimState, 2),
    END_LOOP(),
};

const BehaviorScript bhvToxBox[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(ssl_seg7_collision_tox_box),
    ADD_FLOAT(oPosY, 256),
    SET_FLOAT(oDrawingDistance, 8000),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tox_box_loop),
    END_LOOP(),
};

const BehaviorScript bhvPiranhaPlant[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    LOAD_ANIMATIONS(oAnimations, piranha_plant_seg6_anims_0601C31C),
    ANIMATE(PIRANHA_PLANT_ANIM_BITE),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 200),
    SET_HURTBOX(/*Radius*/ 50, /*Height*/ 200),
    SET_INT(oIntangibleTimer,   0),
    SET_INT(oDamageOrCoinValue, 3),
    SET_INT(oNumLootCoins,      5),
    SPAWN_CHILD(/*Model*/ MODEL_BUBBLE, /*Behavior*/ bhvPiranhaPlantBubble),
    SET_FLOAT(oDrawingDistance, 2000),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_piranha_plant_loop),
    END_LOOP(),
};

const BehaviorScript bhvLllBowserPuzzlePiece[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
    LOAD_COLLISION_DATA(lll_seg7_collision_puzzle_piece),
    SET_HOME(),
    SET_FLOAT(oCollisionDistance, 3000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_lll_bowser_puzzle_piece_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvLllBowserPuzzle[] = {
    BEGIN(OBJ_LIST_SPAWNER),
    DISABLE_RENDERING(),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_lll_bowser_puzzle_loop),
    END_LOOP(),
};

const BehaviorScript bhvTuxiesMother[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, penguin_seg5_anims_05008B74),
    ANIMATE(PENGUIN_ANIM_IDLE),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    SET_HOME(),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    SET_HITBOX(/*Radius*/ 200, /*Height*/ 300),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tuxies_mother_loop),
    END_LOOP(),
};

const BehaviorScript bhvPenguinBaby[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    BREAK(),
};

const BehaviorScript bhvSmallPenguinReturned[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    BREAK(),
};

const BehaviorScript bhvSmallPenguin[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DROP_TO_FLOOR(),
    LOAD_ANIMATIONS(oAnimations, penguin_seg5_anims_05008B74),
    ANIMATE(PENGUIN_ANIM_WALK),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_INT(oInteractType, INTERACT_GRABBABLE),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_HOLDABLE_NPC),
    SET_INT(oIntangibleTimer, 0),
    SET_HITBOX(/*Radius*/ 40, /*Height*/ 40),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_small_penguin_loop),
    END_LOOP(),
};

const BehaviorScript bhvManyBlueFishSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    SET_INT(oBehParams2ndByte, FISH_SPAWNER_BP_MANY_BLUE),
    GOTO(bhvFishSpawner + 1),
};

const BehaviorScript bhvFewBlueFishSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    SET_INT(oBehParams2ndByte, FISH_SPAWNER_BP_FEW_BLUE),
    GOTO(bhvFishSpawner + 1),
};

const BehaviorScript bhvFishSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    // Fish Spawner - common:
    DISABLE_RENDERING(),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_fish_spawner_loop),
    END_LOOP(),
};

const BehaviorScript bhvFish[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_fish_loop),
    END_LOOP(),
};

const BehaviorScript bhvWdwExpressElevator[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(wdw_seg7_collision_express_elevator_platform),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_wdw_express_elevator_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvWdwExpressElevatorPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(wdw_seg7_collision_express_elevator_platform),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvBubSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    SET_INT(oCheepCheepSpawnerSpawnAmount, 1),
    DISABLE_RENDERING(),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bub_spawner_loop),
    END_LOOP(),
};

const BehaviorScript bhvBub[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, bub_seg6_anims_06012354),
    ANIMATE(BUB_ANIM_SWIM),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 20, /*Height*/ 10, /*Downwards offset*/ 10),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    SET_INT(oDamageOrCoinValue, 1),
    SET_HOME(),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bub_loop),
    END_LOOP(),
};

const BehaviorScript bhvExclamationBox[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),//--E
    LOAD_COLLISION_DATA(exclamation_box_outline_seg8_collision_08025F78),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_FLOAT(oCollisionDistance, 300),
    SET_HOME(),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_exclamation_box_loop),
    END_LOOP(),
};

const BehaviorScript bhvRotatingExclamationMark[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SCALE(/*Unused*/ 0, /*Field*/ 200),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_rotating_exclamation_mark_loop),
        ADD_INT(oMoveAngleYaw, 0x800),
    END_LOOP(),
};

const BehaviorScript bhvSoundSpawner[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    DELAY(3),
    CALL_NATIVE(bhv_sound_spawner_init),
    DELAY(30),
    DEACTIVATE(),
};

const BehaviorScript bhvRockSolid[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(jrb_seg7_collision_rock_solid),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvBowserSubDoor[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(ddd_seg7_collision_bowser_sub_door),
    SET_FLOAT(oDrawingDistance, 20000),
    CALL_NATIVE(bhv_bowsers_sub_init),
    BREAK(),
};

const BehaviorScript bhvBowsersSub[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oDrawingDistance, 20000),
    LOAD_COLLISION_DATA(ddd_seg7_collision_submarine),
    CALL_NATIVE(bhv_bowsers_sub_init),
    BREAK(),
};

const BehaviorScript bhvSushiShark[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, sushi_seg5_anims_0500AE54),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 100, /*Height*/ 50, /*Downwards offset*/ 50),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    SET_INT(oDamageOrCoinValue, 3),
    SET_HOME(),
    ANIMATE(SUSHI_ANIM_SWIM),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sushi_shark_loop),
    END_LOOP(),
};

const BehaviorScript bhvJrbSlidingBox[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(jrb_seg7_collision_floating_box),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_jrb_sliding_box_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvShipPart3[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ship_part_3_loop),
    END_LOOP(),
};

const BehaviorScript bhvInSunkenShip3[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(jrb_seg7_collision_in_sunken_ship_3),
    SET_HOME(),
    SET_FLOAT(oDrawingDistance, 4000),
    SET_FLOAT(oCollisionDistance, 4000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ship_part_3_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvSunkenShipPart[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SCALE(/*Unused*/ 0, /*Field*/ 50),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sunken_ship_part_loop),
    END_LOOP(),
};

const BehaviorScript bhvSunkenShipSetRotation[] = {
    SET_INT(oFaceAnglePitch, 0xE958),
    SET_INT(oFaceAngleYaw, 0xEE6C),
    SET_INT(oFaceAngleRoll, 0x0C80),
    RETURN(),
};

const BehaviorScript bhvSunkenShipPart2[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SCALE(/*Unused*/ 0, /*Field*/ 100),
    SET_FLOAT(oDrawingDistance, 6000),
    SET_HOME(),
    CALL(bhvSunkenShipSetRotation),
    BREAK(),
};

const BehaviorScript bhvInSunkenShip[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(jrb_seg7_collision_in_sunken_ship),
    GOTO(bhvInSunkenShip2 + 1 + 2),
};

const BehaviorScript bhvInSunkenShip2[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(jrb_seg7_collision_in_sunken_ship_2),
    // Sunken ship - common:
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oDrawingDistance, 4000),
    SET_FLOAT(oCollisionDistance, 4000),
    CALL(bhvSunkenShipSetRotation),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvMistParticleSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    PARENT_BIT_CLEAR(oActiveParticleFlags, ACTIVE_PARTICLE_DUST),
    DISABLE_RENDERING(),
    SPAWN_CHILD(/*Model*/ MODEL_MIST, /*Behavior*/ bhvWhitePuff1),
    SPAWN_CHILD(/*Model*/ MODEL_SMOKE, /*Behavior*/ bhvWhitePuff2),
    DELAY(1),
    DEACTIVATE(),
};

const BehaviorScript bhvWhitePuff1[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    PARENT_BIT_CLEAR(oActiveParticleFlags, ACTIVE_PARTICLE_DUST),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_white_puff_1_loop),
    END_LOOP(),
};

const BehaviorScript bhvWhitePuff2[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, (OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_REPEAT(7),
        CALL_NATIVE(bhv_white_puff_2_loop),
        ADD_INT(oAnimState, 1),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvWhitePuffSmoke2[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_REPEAT(7),
        CALL_NATIVE(bhv_white_puff_2_loop),
        CALL_NATIVE(cur_obj_move_using_fvel_and_gravity),
        ADD_INT(oAnimState, 1),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvPurpleSwitchHiddenBoxes[] = {
    BEGIN(OBJ_LIST_SURFACE),
    SET_INT(oBehParams2ndByte, PURPLE_SWITCH_BP_REVEAL_HIDDEN),
    GOTO(bhvFloorSwitchHardcodedModel + 1),
};

const BehaviorScript bhvBlueCoinSwitch[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW),//--E
    LOAD_COLLISION_DATA(blue_coin_switch_seg8_collision_08000E98),
    SET_INT(oIntangibleTimer, 0),//--E
    SET_HITBOX(/*Radius*/ 120, /*Height*/ 100),//--E
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_blue_coin_switch_loop),
    END_LOOP(),
};

const BehaviorScript bhvHiddenBlueCoin[] = {
    BEGIN(OBJ_LIST_LEVEL),
    SET_INT(oInteractType, INTERACT_COIN),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 64),
    SET_INT(oDamageOrCoinValue, 5),
    SET_INT(oIntangibleTimer, 0),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hidden_blue_coin_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvOpenableCageDoor[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oDrawingDistance, 15000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_openable_cage_door_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvOpenableGrill[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_openable_grill_loop),
    END_LOOP(),
};

const BehaviorScript bhvWaterLevelDiamond[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HITBOX(/*Radius*/ 70, /*Height*/ 30),
    SET_FLOAT(oCollisionDistance, 200),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_water_level_diamond_loop),
    END_LOOP(),
};

const BehaviorScript bhvInitializeChangingWaterLevel[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_init_changing_water_level_loop),
    END_LOOP(),
};

const BehaviorScript bhvTweesterSandParticle[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, (OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tweester_sand_particle_loop),
    END_LOOP(),
};

const BehaviorScript bhvTweester[] = {
    BEGIN(OBJ_LIST_POLELIKE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    DROP_TO_FLOOR(),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tweester_loop),
    END_LOOP(),
};

const BehaviorScript bhvMerryGoRoundBooManager[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_merry_go_round_boo_manager_loop),
    END_LOOP(),
};

const BehaviorScript bhvAnimatedTexture[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -70, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_animated_texture_loop),
        ADD_INT(oAnimState, 1),
        ANIMATE_TEXTURE(oAnimState, 2),
    END_LOOP(),
};

const BehaviorScript bhvBooInCastle[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),//--E
    SET_HOME(),
    SET_FLOAT(oGraphYOffset, 60),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_boo_in_castle_loop),
    END_LOOP(),
};

const BehaviorScript bhvBooWithCage[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),//--E
    SET_HOME(),
    SET_INT(oDamageOrCoinValue, 3),
    SET_HURTBOX(/*Radius*/ 80, /*Height*/ 120),
    SET_HITBOX(/*Radius*/ 180, /*Height*/ 140),
    SET_FLOAT(oGraphYOffset, 60),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_boo_with_cage_init),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_boo_with_cage_loop),
    END_LOOP(),
};

const BehaviorScript bhvBalconyBigBoo[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    SET_INT(oBehParams2ndByte, BIG_BOO_BP_BALCONY),
    SET_INT(oBigBooNumMinionBoosKilled, 10),
    GOTO(bhvGhostHuntBigBoo + 1),
};

const BehaviorScript bhvMerryGoRoundBigBoo[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    SET_INT(oBehParams2ndByte, BIG_BOO_BP_MERRY_GO_ROUND),
    // Set number of minion boos killed to 10, which is greater than 5 so that the boo always loads without needing to kill any boos.
    SET_INT(oBigBooNumMinionBoosKilled, 10),
    GOTO(bhvGhostHuntBigBoo + 1),
};

const BehaviorScript bhvGhostHuntBigBoo[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    // Big boo - common:
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),//--E
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_init_room),
    CALL_NATIVE(bhv_boo_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_big_boo_loop),
    END_LOOP(),
};

const BehaviorScript bhvCourtyardBooTriplet[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    DISABLE_RENDERING(),
    CALL_NATIVE(bhv_courtyard_boo_triplet_init),
    DEACTIVATE(),
};

const BehaviorScript bhvBoo[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    SET_INT(oBehParams2ndByte, BOO_BP_NORMAL),
    GOTO(bhvGhostHuntBoo + 1),
};

const BehaviorScript bhvMerryGoRoundBoo[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    SET_INT(oBehParams2ndByte, BOO_BP_MERRY_GO_ROUND),
    GOTO(bhvGhostHuntBoo + 1),
};

const BehaviorScript bhvGhostHuntBoo[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    // Boo - common:
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),//--E
    SET_INT(oIntangibleTimer, 0),
    SET_HOME(),
    SET_INT(oDamageOrCoinValue, 2),
    SET_HITBOX(/*Radius*/ 140, /*Height*/ 80),
    SET_HURTBOX(/*Radius*/ 40, /*Height*/ 60),
    SET_FLOAT(oGraphYOffset, 30),
    CALL_NATIVE(bhv_init_room),
    SPAWN_CHILD(/*Model*/ MODEL_YELLOW_COIN, /*Behavior*/ bhvCoinInsideBoo),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_boo_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_boo_loop),
    END_LOOP(),
};

const BehaviorScript bhvHiddenStaircaseStep[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(bbh_seg7_collision_staircase_step),
    SET_INT(oRoom, 1),
    SET_FLOAT(oCollisionDistance, 1000),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvBooStaircase[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(bbh_seg7_collision_staircase_step),
    SET_INT(oRoom, 1),
    SET_FLOAT(oCollisionDistance, 1000),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_boo_staircase),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvBbhTiltingTrapPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(bbh_seg7_collision_tilt_floor_platform),
    SET_HOME(),
    SET_INT(oRoom, 2),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bbh_tilting_trap_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvHauntedBookshelf[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(bbh_seg7_collision_haunted_bookshelf),
    SET_HOME(),
    SET_INT(oRoom, 6),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_haunted_bookshelf_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvMeshElevator[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(bbh_seg7_collision_mesh_elevator),
    SET_HOME(),
    SET_INT(oRoom, 12),
    SET_INT(oBehParams2ndByte, ELEVATOR_BP_BBH_MESH),
    CALL_NATIVE(bhv_elevator_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_elevator_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvMerryGoRound[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(bbh_seg7_collision_merry_go_round),
    SET_FLOAT(oCollisionDistance, 2000),
    SET_INT(oRoom, 10),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_merry_go_round_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvPlaysMusicTrackWhenTouched[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_play_music_track_when_touched_loop),
    END_LOOP(),
};

const BehaviorScript bhvBetaBowserAnchor[] = {
    BEGIN(OBJ_LIST_DESTRUCTIVE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_HOME(),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 300),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        ADD_INT(oAnimState, 1),
        CALL_NATIVE(bhv_beta_bowser_anchor_loop),
    END_LOOP(),
};

const BehaviorScript bhvStaticCheckeredPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(checkerboard_platform_seg8_collision_platform),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_static_checkered_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvUnusedFakeStar[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        ADD_INT(oFaceAnglePitch, 0x100),
        ADD_INT(oFaceAngleYaw,   0x100),
    END_LOOP(),
};

const BehaviorScript bhvStaticObject[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BREAK(),
};

extern void bhv_pepper_art(void);
const BehaviorScript bhvPepperArt[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_pepper_art),
    BREAK(),
};

const BehaviorScript bhvCastleFloorTrap[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    DISABLE_RENDERING(),
    CALL_NATIVE(bhv_castle_floor_trap_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_castle_floor_trap_loop),
    END_LOOP(),
};

const BehaviorScript bhvFloorTrapInCastle[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(inside_castle_seg7_collision_floor_trap),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_floor_trap_in_castle_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvTree[] = {
    BEGIN(OBJ_LIST_POLELIKE),
    BILLBOARD(),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_OPACITY_FROM_CAMERA_DIST)),
    SET_INT(oInteractType, INTERACT_POLE),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 500),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_pole_base_loop),
    END_LOOP(),
};

const BehaviorScript bhvSparkle[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    BILLBOARD(),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_REPEAT(9),
        ADD_INT(oAnimState, 1),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvSparkleSpawn[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sparkle_spawn_loop),
    END_LOOP(),
};

const BehaviorScript bhvSparkleParticleSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    PARENT_BIT_CLEAR(oActiveParticleFlags, ACTIVE_PARTICLE_SPARKLES),
    BEGIN(OBJ_LIST_UNIMPORTANT),
    BILLBOARD(),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_FLOAT(oGraphYOffset, 25),
    SET_RANDOM_FLOAT(oMarioParticleFlags, /*Minimum*/ -50, /*Range*/ 100),
    SUM_FLOAT(/*Dest*/ oPosX, /*Value 1*/ oPosX, /*Value 2*/ oMarioParticleFlags),
    SET_RANDOM_FLOAT(oMarioParticleFlags, /*Minimum*/ -50, /*Range*/ 100),
    SUM_FLOAT(/*Dest*/ oPosZ, /*Value 1*/ oPosZ, /*Value 2*/ oMarioParticleFlags),
    SET_RANDOM_FLOAT(oMarioParticleFlags, /*Minimum*/ -50, /*Range*/ 100),
    SUM_FLOAT(/*Dest*/ oPosY, /*Value 1*/ oPosY, /*Value 2*/ oMarioParticleFlags),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_REPEAT(12),
        ADD_INT(oAnimState, 1),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvScuttlebug[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    LOAD_ANIMATIONS(oAnimations, scuttlebug_seg6_anims_06015064),
    ANIMATE(SCUTTLEBUG_ANIM_JUMP),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 80, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_HOME(),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_scuttlebug_loop),
    END_LOOP(),
};

const BehaviorScript bhvScuttlebugSpawn[] = {
    BEGIN(OBJ_LIST_SPAWNER),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_scuttlebug_spawn_loop),
    END_LOOP(),
};

const BehaviorScript bhvWhompKingBoss[] = {
    BEGIN(OBJ_LIST_SURFACE),
    SET_INT(oBehParams2ndByte, WHOMP_BP_KING),
    SET_INT(oHealth, 3),
    GOTO(bhvSmallWhomp + 1 + 1),
};

const BehaviorScript bhvSmallWhomp[] = {
    BEGIN(OBJ_LIST_SURFACE),
    SET_INT(oNumLootCoins, 5),
    // Whomp - common:
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, whomp_seg6_anims_06020A04),
    LOAD_COLLISION_DATA(whomp_seg6_collision_06020A0C),
    SET_HITBOX(/*Radius*/ 200, /*Height*/ 400),//--E
    ANIMATE(WHOMP_ANIM_WALK),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_whomp_loop),
    END_LOOP(),
};

// The large splash Mario makes when he jumps into a pool of water.
const BehaviorScript bhvWaterSplash[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_REPEAT(3),
        ADD_INT(oAnimState, 1),
        CALL_NATIVE(bhv_water_splash_spawn_droplets),
        DELAY(1),
        CALL_NATIVE(bhv_water_splash_spawn_droplets),
    END_REPEAT(),
    BEGIN_REPEAT(5),
        ADD_INT(oAnimState, 1),
        DELAY(1),
    END_REPEAT(),
    PARENT_BIT_CLEAR(oActiveParticleFlags, ACTIVE_PARTICLE_WATER_SPLASH),
    DEACTIVATE(),
};

// Droplets of water that spawn as a result of various water splashes.
const BehaviorScript bhvWaterDroplet[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_water_droplet_loop),
    END_LOOP(),
};

// Small splashes that are seen when a water droplet lands back into the water.
const BehaviorScript bhvWaterDropletSplash[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INT(oFaceAnglePitch, 0),
    SET_INT(oFaceAngleYaw, 0),
    SET_INT(oFaceAngleRoll, 0),
    CALL_NATIVE(bhv_water_droplet_splash_init),
    ADD_FLOAT(oPosY, 5),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_REPEAT(6),
        ADD_INT(oAnimState, 1),
    END_REPEAT(),
    DEACTIVATE(),
};

// The splash created when an air bubble hits the surface of the water.
const BehaviorScript bhvBubbleSplash[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INT(oFaceAnglePitch, 0),
    SET_INT(oFaceAngleYaw, 0),
    SET_INT(oFaceAngleRoll, 0),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    CALL_NATIVE(bhv_bubble_splash_init),
    BEGIN_REPEAT(6),
        ADD_INT(oAnimState, 1),
    END_REPEAT(),
    DEACTIVATE(),
};

// The water wave surrounding Mario when he is idle in a pool of water.
const BehaviorScript bhvIdleWaterWave[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INT(oFaceAnglePitch, 0),
    SET_INT(oFaceAngleYaw, 0),
    SET_INT(oFaceAngleRoll, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_idle_water_wave_loop),
        ADD_INT(oAnimState, 1),
        BEGIN_REPEAT(6),
            CALL_NATIVE(bhv_idle_water_wave_loop),
        END_REPEAT(),
        CALL_NATIVE(bhv_idle_water_wave_loop),
    END_LOOP(),
};

// Water splashes similar to the splashes created by water droplets, but are created by other objects.
const BehaviorScript bhvObjectWaterSplash[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INT(oFaceAnglePitch, 0),
    SET_INT(oFaceAngleYaw, 0),
    SET_INT(oFaceAngleRoll, 0),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_REPEAT(6),
        ADD_INT(oAnimState, 1),
    END_REPEAT(),
    DEACTIVATE(),
};

// Waves that are generated when running in shallow water.
const BehaviorScript bhvShallowWaterWave[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    DISABLE_RENDERING(),
    BEGIN_REPEAT(5),
        SPAWN_WATER_DROPLET(&gShallowWaterWaveDropletParams),
    END_REPEAT_CONTINUE(),
    DELAY(1),
    PARENT_BIT_CLEAR(oActiveParticleFlags, ACTIVE_PARTICLE_SHALLOW_WATER_WAVE),
    DEACTIVATE(),
};

// A small water splash that occurs when jumping in and out of shallow water.
// Unlike the larger water splash it has no visible model of its own.
// It has a 1 in 256 chance of spawning the fish particle easter egg.
const BehaviorScript bhvShallowWaterSplash[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    DISABLE_RENDERING(),
    BEGIN_REPEAT(18),
        SPAWN_WATER_DROPLET(&gShallowWaterSplashDropletParams),
    END_REPEAT_CONTINUE(),
    CALL_NATIVE(bhv_shallow_water_splash_init),
    DELAY(1),
    PARENT_BIT_CLEAR(oActiveParticleFlags, ACTIVE_PARTICLE_SHALLOW_WATER_SPLASH),
    DEACTIVATE(),
};

// Waves created by other objects along the water's surface, specifically the koopa shell and Sushi.
const BehaviorScript bhvObjectWaveTrail[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    GOTO(bhvWaveTrail + 1 + 1 + 2), // Wave trail - common
};

// The waves created by Mario while he is swimming.
const BehaviorScript bhvWaveTrail[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    PARENT_BIT_CLEAR(oActiveParticleFlags, ACTIVE_PARTICLE_WAVE_TRAIL),
    // Wave trail - common:
    SET_INT(oFaceAnglePitch, 0),
    SET_INT(oFaceAngleYaw, 0),
    SET_INT(oFaceAngleRoll, 0),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_REPEAT(8),
        ADD_INT(oAnimState, 1),
        CALL_NATIVE(bhv_wave_trail_shrink),
        DELAY(1),
        CALL_NATIVE(bhv_wave_trail_shrink),
    END_REPEAT(),
    DEACTIVATE(),
};

// Tiny wind particles that provide aesthetics to the strong winds generated by the Snowman and Fwoosh.
// As they are unimportant objects, they don't have collision with Mario.
const BehaviorScript bhvTinyStrongWindParticle[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_strong_wind_particle_loop),
    END_LOOP(),
};

// Strong wind particles generated by the Snowman and Fwoosh that blow Mario back and knock his cap off.
const BehaviorScript bhvStrongWindParticle[] = {
    BEGIN(OBJ_LIST_POLELIKE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_strong_wind_particle_loop),
    END_LOOP(),
};

// The handler for the strong wind blown by the Snowman in SL. Triggers dialog and then aims towards Mario.
const BehaviorScript bhvSLSnowmanWind[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sl_snowman_wind_loop),
    END_LOOP(),
};

// The penguin that walks erratically along the ice bridge in front of the Snowman in SL.
// Blocks strong wind particles, allowing Mario to walk behind it.
const BehaviorScript bhvSLWalkingPenguin[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(penguin_seg5_collision_05008B88),
    LOAD_ANIMATIONS(oAnimations, penguin_seg5_anims_05008B74),
    ANIMATE(PENGUIN_ANIM_WALK),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SCALE(/*Unused*/ 0, /*Field*/ 600),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sl_walking_penguin_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvYellowBall[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    BREAK(),
};

UNUSED static const u64 behavior_data_unused_0 = 0;
const BehaviorScript bhvMario[] = {
    BEGIN(OBJ_LIST_PLAYER),
    SET_INT(oIntangibleTimer, 0),
    OR_LONG(oFlags, (OBJ_FLAG_PLAYER | OBJ_FLAG_SILHOUETTE | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW)),
    OR_INT(oUnk94, 0x0001),
    SET_HITBOX(/*Radius*/ 37, /*Height*/ 160),
    BEGIN_LOOP(),
#ifdef VANILLA_DEBUG
        CALL_NATIVE(try_print_debug_mario_level_info),
#endif
        CALL_NATIVE(bhv_mario_update),
#ifdef VANILLA_DEBUG
        CALL_NATIVE(try_do_mario_debug_object_spawn),
#endif
    END_LOOP(),
};

const BehaviorScript bhvToadMessage[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, toad_seg6_anims_0600FB58),
    ANIMATE(TOAD_ANIM_WEST_WAVING_BOTH_ARMS),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 100),
    SET_INT(oIntangibleTimer, 0),
    CALL_NATIVE(bhv_init_room),
    CALL_NATIVE(bhv_toad_message_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_toad_message_loop),
    END_LOOP(),
};

const BehaviorScript bhvUnlockDoorStar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_unlock_door_star_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_unlock_door_star_loop),
    END_LOOP(),
};

const BehaviorScript bhvInstantActiveWarp[] = {
    BREAK(),
};

const BehaviorScript bhvAirborneWarp[] = {
    BREAK(),
};

const BehaviorScript bhvHardAirKnockBackWarp[] = {
    BREAK(),
};

const BehaviorScript bhvSpinAirborneCircleWarp[] = {
    BREAK(),
};

const BehaviorScript bhvDeathWarp[] = {
    BREAK(),
};

const BehaviorScript bhvSpinAirborneWarp[] = {
    BREAK(),
};

const BehaviorScript bhvFlyingWarp[] = {
    BREAK(),
};

const BehaviorScript bhvPaintingStarCollectWarp[] = {
    BREAK(),
};

const BehaviorScript bhvPaintingDeathWarp[] = {
    BREAK(),
};

const BehaviorScript bhvAirborneDeathWarp[] = {
    BREAK(),
};

const BehaviorScript bhvAirborneStarCollectWarp[] = {
    BREAK(),
};

const BehaviorScript bhvLaunchStarCollectWarp[] = {
    BREAK(),
};

const BehaviorScript bhvLaunchDeathWarp[] = {
    BREAK(),
};

const BehaviorScript bhvSwimmingWarp[] = {
    BREAK(),
};

UNUSED static const u64 behavior_data_unused_1 = 0;
const BehaviorScript bhvRandomAnimatedTexture[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_FLOAT(oGraphYOffset, -16),
    BILLBOARD(),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_LOOP(),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvYellowBackgroundInMenu[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(beh_yellow_background_menu_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(beh_yellow_background_menu_loop),
    END_LOOP(),
};

const BehaviorScript bhvMenuButton[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_menu_button_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_menu_button_loop),
    END_LOOP(),
};

const BehaviorScript bhvMenuButtonManager[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_SET_THROW_MATRIX_FROM_TRANSFORM | OBJ_FLAG_UPDATE_TRANSFORM_FOR_THROW_MATRIX | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_menu_button_manager_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_menu_button_manager_loop),
    END_LOOP(),
};

const BehaviorScript bhvActSelectorStarType[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_act_selector_star_type_loop),
    END_LOOP(),
};

const BehaviorScript bhvActSelector[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_act_selector_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_act_selector_loop),
    END_LOOP(),
};

const BehaviorScript bhvMovingYellowCoin[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 64),
    SET_INT(oInteractType, INTERACT_COIN),
    SET_INT(oIntangibleTimer, 0),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    CALL_NATIVE(bhv_moving_yellow_coin_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_moving_yellow_coin_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvMovingBlueCoin[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_ATTACHABLE_BY_ROPE),
    BILLBOARD(),
    SET_INT(oIntangibleTimer, 0),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    CALL_NATIVE(bhv_moving_blue_coin_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_moving_blue_coin_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvBlueCoinSliding[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_INT(oIntangibleTimer, 0),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    CALL_NATIVE(bhv_blue_coin_sliding_jumping_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_blue_coin_sliding_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvBlueCoinJumping[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_ATTACHABLE_BY_ROPE)),
    BILLBOARD(),
    SET_INT(oIntangibleTimer, 0),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    CALL_NATIVE(bhv_blue_coin_sliding_jumping_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_blue_coin_jumping_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvSeaweed[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_ANIMATIONS(oAnimations, seaweed_seg6_anims_0600A4D4),
    ANIMATE(SEAWEED_ANIM_WAVE),
    CALL_NATIVE(bhv_seaweed_init),
    BEGIN_LOOP(),
    END_LOOP(),
};

const BehaviorScript bhvSeaweedBundle[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    DROP_TO_FLOOR(),
    CALL_NATIVE(bhv_seaweed_bundle_init),
    BEGIN_LOOP(),
    END_LOOP(),
};

const BehaviorScript bhvBobomb[] = {
    BEGIN(OBJ_LIST_DESTRUCTIVE),
    OR_LONG(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    LOAD_ANIMATIONS(oAnimations, bobomb_seg8_anims_0802396C),
    DROP_TO_FLOOR(),
    ANIMATE(BOBOMB_ANIM_WALKING),
    SET_INT(oIntangibleTimer, 0),
    SET_HOME(),
    CALL_NATIVE(bhv_bobomb_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bobomb_loop),
    END_LOOP(),
};

const BehaviorScript bhvBobombFuseSmoke[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    CALL_NATIVE(bhv_bobomb_fuse_smoke_init),
    DELAY(1),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_dust_smoke_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvBobombBuddy[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_INT(oBobombBuddyRole, 0),
    LOAD_ANIMATIONS(oAnimations, bobomb_seg8_anims_0802396C),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 60),
    ANIMATE(BOBOMB_ANIM_WALKING),
    SET_HOME(),
    CALL_NATIVE(bhv_bobomb_buddy_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_bobomb_buddy_loop),
    END_LOOP(),
};

const BehaviorScript bhvBobombBuddyOpensCannon[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_INT(oBobombBuddyRole, 1),
    GOTO(bhvBobombBuddy + 1 + 2),
};

const BehaviorScript bhvCannonClosed[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(cannon_lid_seg8_collision_08004950),
    SET_HOME(),
    CALL_NATIVE(bhv_cannon_closed_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_cannon_closed_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvWhirlpool[] = {
    BEGIN(OBJ_LIST_POLELIKE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_whirlpool_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_whirlpool_loop),
    END_LOOP(),
};

const BehaviorScript bhvJetStream[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_jet_stream_loop),
    END_LOOP(),
};

const BehaviorScript bhvMessagePanel[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(wooden_signpost_seg3_collision_0302DD80),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_SIGN),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 150, /*Height*/ 80),
    SET_INT(oWoodenPostTotalMarioAngle, 0),
    CALL_NATIVE(bhv_init_room),
    CALL_NATIVE(load_object_static_model),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        SET_INT(oInteractStatus, INT_STATUS_NONE),
    END_LOOP(),
};

const BehaviorScript bhvSignOnWall[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_SIGN),
    SET_HITBOX(/*Radius*/ 150, /*Height*/ 80),
    SET_INT(oWoodenPostTotalMarioAngle, 0),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        SET_INT(oInteractStatus, INT_STATUS_NONE),
    END_LOOP(),
};

const BehaviorScript bhvHomingAmp[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    LOAD_ANIMATIONS(oAnimations, dAmpAnimsList),
    ANIMATE(AMP_ANIM_DEFAULT),
    SET_FLOAT(oGraphYOffset, 40),
    SET_INT(oIntangibleTimer, 0),
    CALL_NATIVE(bhv_homing_amp_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_homing_amp_loop),
    END_LOOP(),
};

const BehaviorScript bhvCirclingAmp[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    LOAD_ANIMATIONS(oAnimations, dAmpAnimsList),
    ANIMATE(AMP_ANIM_DEFAULT),
    SET_FLOAT(oGraphYOffset, 40),
    SET_INT(oIntangibleTimer, 0),
    CALL_NATIVE(bhv_circling_amp_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_circling_amp_loop),
    END_LOOP(),
};

const BehaviorScript bhvButterfly[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, butterfly_seg3_anims_030056B0),
    DROP_TO_FLOOR(),
    SET_FLOAT(oGraphYOffset, 5),
    CALL_NATIVE(bhv_butterfly_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_butterfly_loop),
    END_LOOP(),
};

const BehaviorScript bhvHoot[] = {
    BEGIN(OBJ_LIST_POLELIKE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, hoot_seg5_anims_05005768),
    SET_INT(oInteractType, INTERACT_HOOT),
    SET_HITBOX(/*Radius*/ 75, /*Height*/ 75),
    CALL_NATIVE(bhv_hoot_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hoot_loop),
    END_LOOP(),
};

const BehaviorScript bhvBetaHoldableObject[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_HOLDABLE | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_INT(oInteractType, INTERACT_GRABBABLE),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 40, /*Height*/ 50),
    CALL_NATIVE(bhv_beta_holdable_object_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_beta_holdable_object_loop),
    END_LOOP(),
};

const BehaviorScript bhvCarrySomethingHeld[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    BREAK(),
};

const BehaviorScript bhvCarrySomethingDropped[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    BREAK(),
};

const BehaviorScript bhvCarrySomethingThrown[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    BREAK(),
};

const BehaviorScript bhvObjectBubble[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, (OBJ_FLAG_MOVE_Y_WITH_TERMINAL_VEL | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    CALL_NATIVE(bhv_object_bubble_init),
    SET_RANDOM_FLOAT(oVelY, /*Minimum*/ 3, /*Range*/ 6),
    SET_INT_RAND_RSHIFT(oMoveAngleYaw, /*Minimum*/ 0, /*Right shift*/ 0),
    DELAY(1),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_object_bubble_loop),
    END_LOOP(),
};

const BehaviorScript bhvObjectWaterWave[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INT(oFaceAnglePitch, 0),
    SET_INT(oFaceAngleYaw, 0),
    SET_INT(oFaceAngleRoll, 0),
    CALL_NATIVE(bhv_object_water_wave_init),
    DELAY(6),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_object_water_wave_loop),
        ADD_INT(oAnimState, 1),
    BEGIN_REPEAT(6),
        CALL_NATIVE(bhv_object_water_wave_loop),
    END_REPEAT(),
    END_LOOP(),
};

const BehaviorScript bhvExplosion[] = {
    BEGIN(OBJ_LIST_DESTRUCTIVE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    SET_INT(oDamageOrCoinValue, 2),
    SET_INT(oIntangibleTimer, 0),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 150, /*Height*/ 150, /*Downwards offset*/ 150),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    CALL_NATIVE(bhv_explosion_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_explosion_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvExplosionVisual[] = {
    BEGIN(OBJ_LIST_DESTRUCTIVE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_INTERACT_TYPE(INTERACT_NONE),
    SET_INT(oDamageOrCoinValue, 2),
    SET_INT(oIntangibleTimer, 0),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 150, /*Height*/ 150, /*Downwards offset*/ 150),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    CALL_NATIVE(bhv_explosion_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_explosion_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvBobombBullyDeathSmoke[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, (OBJ_FLAG_MOVE_Y_WITH_TERMINAL_VEL | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    CALL_NATIVE(bhv_bobomb_bully_death_smoke_init),
    DELAY(1),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_dust_smoke_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvSmoke[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, (OBJ_FLAG_MOVE_Y_WITH_TERMINAL_VEL | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    DELAY(1),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_dust_smoke_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvBobombExplosionBubble[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    BILLBOARD(),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_bobomb_explosion_bubble_init),
    ADD_RANDOM_FLOAT(oPosX, /*Minimum*/ -50, /*Range*/ 100),
    ADD_RANDOM_FLOAT(oPosY, /*Minimum*/ -50, /*Range*/ 100),
    ADD_RANDOM_FLOAT(oPosZ, /*Minimum*/ -50, /*Range*/ 100),
    CALL(bhvBobombExplosionBubble3600),
    DELAY(1),
    BEGIN_LOOP(),
        CALL(bhvBobombExplosionBubble3600),
        CALL_NATIVE(bhv_bobomb_explosion_bubble_loop),
    END_LOOP(),
};

const BehaviorScript bhvBobombExplosionBubble3600[] = {
    ADD_RANDOM_FLOAT(oPosX, /*Minimum*/ -2, /*Range*/ 4),
    ADD_RANDOM_FLOAT(oPosZ, /*Minimum*/ -2, /*Range*/ 4),
    RETURN(),
};

const BehaviorScript bhvRespawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_respawner_loop),
    END_LOOP(),
};

const BehaviorScript bhvSmallBully[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BOSS)),//--E
    LOAD_ANIMATIONS(oAnimations, bully_seg5_anims_0500470C),
    DROP_TO_FLOOR(),
    SET_HOME(),
    CALL_NATIVE(bhv_small_bully_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_bully_loop),
    END_LOOP(),
};

const BehaviorScript bhvBigBully[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BOSS)),//--E
    LOAD_ANIMATIONS(oAnimations, bully_seg5_anims_0500470C),
    DROP_TO_FLOOR(),
    SET_HOME(),
    CALL_NATIVE(bhv_big_bully_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_bully_loop),
    END_LOOP(),
};

const BehaviorScript bhvBigBullyWithMinions[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET | OBJ_FLAG_E__SG_CUSTOM)),
    LOAD_ANIMATIONS(oAnimations, bully_seg5_anims_0500470C),
    SET_HOME(),
    CALL_NATIVE(bhv_big_bully_init),
    CALL_NATIVE(bhv_big_bully_with_minions_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_big_bully_with_minions_loop),
    END_LOOP(),
};

extern void bhv_nball_init(void);
extern void bhv_nball_loop(void);
const BehaviorScript bhvNball[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    CALL_NATIVE(bhv_nball_init),
    SET_FLOAT(oGraphYOffset, 100),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_nball_loop),
    END_LOOP(),
};

const BehaviorScript bhvSmallChillBully[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BOSS)),//--E
    LOAD_ANIMATIONS(oAnimations, chilly_chief_seg6_anims_06003994),
    DROP_TO_FLOOR(),
    SET_HOME(),
    SET_INT(oBullySubtype, 0x0010),
    CALL_NATIVE(bhv_small_bully_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_bully_loop),
    END_LOOP(),
};

const BehaviorScript bhvBigChillBully[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BOSS)),//--E
    LOAD_ANIMATIONS(oAnimations, chilly_chief_seg6_anims_06003994),
    DROP_TO_FLOOR(),
    SET_HOME(),
    SET_INT(oBullySubtype, 0x0010),
    CALL_NATIVE(bhv_big_bully_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_bully_loop),
    END_LOOP(),
};

const BehaviorScript bhvJetStreamRingSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    HIDE(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_jet_stream_ring_spawner_loop),
    END_LOOP(),
};

const BehaviorScript bhvJetStreamWaterRing[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_ANIMATIONS(oAnimations, water_ring_seg6_anims_06013F7C),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 75, /*Height*/ 20, /*Downwards offset*/ 20),
    SET_INTERACT_TYPE(INTERACT_WATER_RING),
    SET_INT(oDamageOrCoinValue, 2),
    SET_INT(oIntangibleTimer, 0),
    CALL_NATIVE(bhv_jet_stream_water_ring_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_jet_stream_water_ring_loop),
    END_LOOP(),
};

const BehaviorScript bhvMantaRayWaterRing[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_ANIMATIONS(oAnimations, water_ring_seg6_anims_06013F7C),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 75, /*Height*/ 20, /*Downwards offset*/ 20),
    SET_INTERACT_TYPE(INTERACT_WATER_RING),
    SET_INT(oDamageOrCoinValue, 2),
    SET_INT(oIntangibleTimer, 0),
    CALL_NATIVE(bhv_manta_ray_water_ring_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_manta_ray_water_ring_loop),
    END_LOOP(),
};

const BehaviorScript bhvMantaRayRingManager[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    BEGIN_LOOP(),
    END_LOOP(),
};

const BehaviorScript bhvBowserBomb[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INT(oIntangibleTimer, 0),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 40, /*Height*/ 40, /*Downwards offset*/ 40),
    DELAY(1),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_bowser_bomb_loop),
    END_LOOP(),
};

const BehaviorScript bhvBowserBombExplosion[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_FLOAT(oGraphYOffset, -288),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bowser_bomb_explosion_loop),
    END_LOOP(),
};

const BehaviorScript bhvBowserBombSmoke[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_FLOAT(oGraphYOffset, -288),
    SET_INT(oOpacity, 255),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bowser_bomb_smoke_loop),
    END_LOOP(),
};

const BehaviorScript bhvCelebrationStar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_celebration_star_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_celebration_star_loop),
    END_LOOP(),
};

const BehaviorScript bhvCelebrationStarSparkle[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    BILLBOARD(),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_FLOAT(oGraphYOffset, 25),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_LOOP(),
        ADD_INT(oAnimState, 1),
        CALL_NATIVE(bhv_celebration_star_sparkle_loop),
    END_LOOP(),
};

const BehaviorScript bhvStarKeyCollectionPuffSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    BILLBOARD(),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_star_key_collection_puff_spawner_loop),
    END_LOOP(),
};

const BehaviorScript bhvLllDrawbridgeSpawner[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    HIDE(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_lll_drawbridge_spawner_loop),
    END_LOOP(),
};

const BehaviorScript bhvLllDrawbridge[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(lll_seg7_collision_drawbridge),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_lll_drawbridge_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvSmallBomp[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_COLLISION_BREAKABLE)),//--E
    LOAD_COLLISION_DATA(wf_seg7_collision_small_bomp),
    CALL_NATIVE(bhv_small_bomp_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_small_bomp_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvLargeBomp[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_COLLISION_BREAKABLE)),//--E
    LOAD_COLLISION_DATA(wf_seg7_collision_large_bomp),
    CALL_NATIVE(bhv_large_bomp_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_large_bomp_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvWfSlidingPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(wf_seg7_collision_sliding_brick_platform),
    CALL_NATIVE(bhv_wf_sliding_platform_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_wf_sliding_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvMoneybag[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    LOAD_ANIMATIONS(oAnimations, moneybag_seg6_anims_06005E5C),
    DROP_TO_FLOOR(),
    SET_HOME(),
    SET_INT(oIntangibleTimer, -1),
    CALL_NATIVE(bhv_moneybag_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_moneybag_loop),
    END_LOOP(),
};

const BehaviorScript bhvMoneybagHidden[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    SET_FLOAT(oGraphYOffset, 27),
    BILLBOARD(),
    SET_HITBOX(/*Radius*/ 110, /*Height*/ 100),
    SET_INT(oIntangibleTimer, 0),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_LOOP(),
        ADD_INT(oAnimState, 1),
        CALL_NATIVE(bhv_moneybag_hidden_loop),
    END_LOOP(),
};

const BehaviorScript bhvPitBowlingBall[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    BILLBOARD(),
    SET_FLOAT(oGraphYOffset, 130),
    CALL_NATIVE(bhv_bob_pit_bowling_ball_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bob_pit_bowling_ball_loop),
    END_LOOP(),
};

const BehaviorScript bhvFreeBowlingBall[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    BILLBOARD(),
    SET_FLOAT(oGraphYOffset, 130),
    CALL_NATIVE(bhv_free_bowling_ball_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_free_bowling_ball_loop),
    END_LOOP(),
};

const BehaviorScript bhvBowlingBall[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    BILLBOARD(),
    SET_FLOAT(oGraphYOffset, 130),
    CALL_NATIVE(bhv_bowling_ball_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bowling_ball_loop),
    END_LOOP(),
};

const BehaviorScript bhvTtmBowlingBallSpawner[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INT(oBBallSpawnerPeriodMinus1, 63),
    CALL_NATIVE(bhv_generic_bowling_ball_spawner_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_generic_bowling_ball_spawner_loop),
    END_LOOP(),
};

const BehaviorScript bhvBobBowlingBallSpawner[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INT(oBBallSpawnerPeriodMinus1, 127),
    CALL_NATIVE(bhv_generic_bowling_ball_spawner_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_generic_bowling_ball_spawner_loop),
    END_LOOP(),
};

const BehaviorScript bhvThiBowlingBallSpawner[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_thi_bowling_ball_spawner_loop),
    END_LOOP(),
};

const BehaviorScript bhvRrCruiserWing[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_rr_cruiser_wing_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_rr_cruiser_wing_loop),
    END_LOOP(),
};

const BehaviorScript bhvSpindel[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(ssl_seg7_collision_spindel),
    CALL_NATIVE(bhv_spindel_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_spindel_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvSslMovingPyramidWall[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(ssl_seg7_collision_0702808C),
    CALL_NATIVE(bhv_ssl_moving_pyramid_wall_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ssl_moving_pyramid_wall_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvPyramidElevator[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(ssl_seg7_collision_pyramid_elevator),
    SET_HOME(),
    SET_FLOAT(oDrawingDistance, 20000),
    SET_FLOAT(oCollisionDistance, 20000),
    CALL_NATIVE(bhv_pyramid_elevator_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_pyramid_elevator_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvPyramidElevatorTrajectoryMarkerBall[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_pyramid_elevator_trajectory_marker_ball_loop),
    END_LOOP(),
};

const BehaviorScript bhvPyramidTop[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(ssl_seg7_collision_pyramid_top),
    SET_HOME(),
    SET_FLOAT(oDrawingDistance, 20000),
    SET_FLOAT(oCollisionDistance, 20000),
    CALL_NATIVE(bhv_pyramid_top_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_pyramid_top_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvPyramidTopFragment[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_pyramid_top_fragment_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_pyramid_top_fragment_loop),
    END_LOOP(),
};

const BehaviorScript bhvPyramidPillarTouchDetector[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HITBOX(/*Radius*/ 50, /*Height*/ 50),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_pyramid_pillar_touch_detector_loop),
    END_LOOP(),
};

const BehaviorScript bhvWaterfallSoundLoop[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_COMPUTE_DIST_TO_MARIO),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_waterfall_sound_loop),
    END_LOOP(),
};

const BehaviorScript bhvVolcanoSoundLoop[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_volcano_sound_loop),
    END_LOOP(),
};

const BehaviorScript bhvCastleFlagWaving[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_ANIMATIONS(oAnimations, castle_grounds_seg7_anims_flags),
    ANIMATE(CASTLE_FLAG_ANIM_WAVE),
    CALL_NATIVE(bhv_castle_flag_init),
    BEGIN_LOOP(),
    END_LOOP(),
};

const BehaviorScript bhvBirdsSoundLoop[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_birds_sound_loop),
    END_LOOP(),
};

const BehaviorScript bhvAmbientSounds[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    CALL_NATIVE(bhv_ambient_sounds_init),
    BEGIN_LOOP(),
    END_LOOP(),
};

const BehaviorScript bhvSandSoundLoop[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sand_sound_loop),
    END_LOOP(),
};

const BehaviorScript bhvHiddenAt120Stars[] = {
    BEGIN(OBJ_LIST_SURFACE),
#ifdef UNLOCK_ALL
    DEACTIVATE(),
#else
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(castle_grounds_seg7_collision_cannon_grill),
    SET_FLOAT(oCollisionDistance, 4000),
    CALL_NATIVE(bhv_castle_cannon_grate_init),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
#endif
};

const BehaviorScript bhvSnowmansBottom[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DROP_TO_FLOOR(),
    SET_INT(oIntangibleTimer, 0),
    CALL_NATIVE(bhv_snowmans_bottom_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_snowmans_bottom_loop),
    END_LOOP(),
};

const BehaviorScript bhvSnowmansHead[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DROP_TO_FLOOR(),
    SET_FLOAT(oGraphYOffset, 110),
    CALL_NATIVE(bhv_snowmans_head_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_snowmans_head_loop),
    END_LOOP(),
};

const BehaviorScript bhvSnowmansBodyCheckpoint[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_snowmans_body_checkpoint_loop),
    END_LOOP(),
};

const BehaviorScript bhvBigSnowmanWhole[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_FLOAT(oGraphYOffset, 180),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    SET_HITBOX(/*Radius*/ 210, /*Height*/ 550),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
    END_LOOP(),
};

const BehaviorScript bhvBigBoulder[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oGraphYOffset, 180),
    CALL_NATIVE(bhv_big_boulder_init),
    SET_FLOAT(oDrawingDistance, 20000),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_big_boulder_loop),
    END_LOOP(),
};

const BehaviorScript bhvBigBoulderGenerator[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_big_boulder_generator_loop),
    END_LOOP(),
};

const BehaviorScript bhvWingCap[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SILHOUETTE)),
    CALL_NATIVE(bhv_wing_cap_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_wing_vanish_cap_loop),
    END_LOOP(),
};

const BehaviorScript bhvMetalCap[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SILHOUETTE)),
    CALL_NATIVE(bhv_metal_cap_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_metal_cap_loop),
    END_LOOP(),
};

const BehaviorScript bhvNormalCap[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SILHOUETTE)),
    CALL_NATIVE(bhv_normal_cap_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_normal_cap_loop),
    END_LOOP(),
};

const BehaviorScript bhvVanishCap[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SILHOUETTE)),
    CALL_NATIVE(bhv_vanish_cap_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_wing_vanish_cap_loop),
    END_LOOP(),
};

const BehaviorScript bhvStar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET),
    //CALL_NATIVE(bhv_init_room),
    CALL_NATIVE(bhv_collect_star_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_collect_star_loop),
    END_LOOP(),
};

const BehaviorScript bhvUVstar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    CALL_NATIVE(bhv_collect_star_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hidden_by_uv),
        CALL_NATIVE(bhv_collect_star_loop),
    END_LOOP(),
};

const BehaviorScript bhvStarSpawnCoordinates[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_collect_star_init),
    CALL_NATIVE(bhv_star_spawn_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_star_spawn_loop),
    END_LOOP(),
};

const BehaviorScript bhvHiddenRedCoinStar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    CALL_NATIVE(bhv_hidden_red_coin_star_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hidden_red_coin_star_loop),
    END_LOOP(),
};

const BehaviorScript bhvRedCoin[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET),
    BILLBOARD(),
    SET_INT(oIntangibleTimer, 0),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    CALL_NATIVE(bhv_init_room),
    CALL_NATIVE(bhv_red_coin_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_red_coin_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvBowserCourseRedCoinStar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_bowser_course_red_coin_star_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bowser_course_red_coin_star_loop),
    END_LOOP(),
};

const BehaviorScript bhvHiddenStar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    CALL_NATIVE(bhv_hidden_star_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hidden_star_loop),
    END_LOOP(),
};

const BehaviorScript bhvGCOStar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_gco_star_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_gco_star_loop),
    END_LOOP(),
};

const BehaviorScript bhvHiddenStarTrigger[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 100),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hidden_star_trigger_loop),
    END_LOOP(),
};

const BehaviorScript bhvTtmRollingLog[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(ttm_seg7_collision_pitoune_2),
    SET_HOME(),
    SET_FLOAT(oCollisionDistance, 2000),
    CALL_NATIVE(bhv_ttm_rolling_log_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_rolling_log_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvLllVolcanoFallingTrap[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(lll_seg7_collision_falling_wall),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_volcano_trap_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvLllRollingLog[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(lll_seg7_collision_pitoune),
    SET_HOME(),
    SET_FLOAT(oCollisionDistance, 2000),
    CALL_NATIVE(bhv_lll_rolling_log_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_rolling_log_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhv1upWalking[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 30, /*Height*/ 30, /*Downwards offset*/ 0),
    SET_FLOAT(oGraphYOffset, 30),
    CALL_NATIVE(bhv_1up_common_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_1up_walking_loop),
    END_LOOP(),
};

const BehaviorScript bhv1upRunningAway[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 30, /*Height*/ 30, /*Downwards offset*/ 0),
    SET_FLOAT(oGraphYOffset, 30),
    CALL_NATIVE(bhv_1up_common_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_1up_running_away_loop),
    END_LOOP(),
};

const BehaviorScript bhv1upSliding[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 30, /*Height*/ 30, /*Downwards offset*/ 0),
    SET_FLOAT(oGraphYOffset, 30),
    CALL_NATIVE(bhv_1up_common_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_1up_sliding_loop),
    END_LOOP(),
};

const BehaviorScript bhv1Up[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 30, /*Height*/ 30, /*Downwards offset*/ 0),
    SET_FLOAT(oGraphYOffset, 30),
    CALL_NATIVE(bhv_1up_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_1up_loop),
    END_LOOP(),
};

const BehaviorScript bhv1upJumpOnApproach[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 30, /*Height*/ 30, /*Downwards offset*/ 0),
    SET_FLOAT(oGraphYOffset, 30),
    CALL_NATIVE(bhv_1up_common_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_1up_jump_on_approach_loop),
    END_LOOP(),
};

const BehaviorScript bhvHidden1up[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 30, /*Height*/ 30, /*Downwards offset*/ 0),
    SET_FLOAT(oGraphYOffset, 30),
    CALL_NATIVE(bhv_1up_common_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_1up_hidden_loop),
    END_LOOP(),
};

const BehaviorScript bhvHidden1upTrigger[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 100),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_1up_hidden_trigger_loop),
    END_LOOP(),
};

const BehaviorScript bhvHidden1upInPole[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 30, /*Height*/ 30, /*Downwards offset*/ 0),
    SET_FLOAT(oGraphYOffset, 30),
    CALL_NATIVE(bhv_1up_common_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_1up_hidden_in_pole_loop),
    END_LOOP(),
};

const BehaviorScript bhvHidden1upInPoleTrigger[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 100),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_1up_hidden_in_pole_trigger_loop),
    END_LOOP(),
};

const BehaviorScript bhvHidden1upInPoleSpawner[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_1up_hidden_in_pole_spawner_loop),
    END_LOOP(),
};

const BehaviorScript bhvControllablePlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_THROW_MATRIX_FROM_TRANSFORM | OBJ_FLAG_UPDATE_TRANSFORM_FOR_THROW_MATRIX | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(hmc_seg7_collision_controllable_platform),
    SET_HOME(),
    CALL_NATIVE(bhv_controllable_platform_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_controllable_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvControllablePlatformSub[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(hmc_seg7_collision_controllable_platform_sub),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_controllable_platform_sub_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvBreakableBoxSmall[] = {
    BEGIN(OBJ_LIST_DESTRUCTIVE),
    OR_LONG(oFlags, (OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    DROP_TO_FLOOR(),
    SET_HOME(),
    CALL_NATIVE(bhv_breakable_box_small_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_breakable_box_small_loop),
    END_LOOP(),
};

const BehaviorScript bhvSlidingSnowMound[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    LOAD_COLLISION_DATA(sl_seg7_collision_sliding_snow_mound),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sliding_snow_mound_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvSnowMoundSpawn[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_snow_mound_spawn_loop),
    END_LOOP(),
};

const BehaviorScript bhvWdwSquareFloatingPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(wdw_seg7_collision_square_floating_platform),
    SET_FLOAT(oFloatingPlatformHeightOffset, 64),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_floating_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvWdwRectangularFloatingPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(wdw_seg7_collision_rect_floating_platform),
    SET_FLOAT(oFloatingPlatformHeightOffset, 64),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_floating_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvJrbFloatingPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(jrb_seg7_collision_floating_platform),
    SET_FLOAT(oFloatingPlatformHeightOffset, 64),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_floating_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvArrowLift[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(wdw_seg7_collision_arrow_lift),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_arrow_lift_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvOrangeNumber[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    CALL_NATIVE(bhv_orange_number_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_orange_number_loop),
    END_LOOP(),
};

const BehaviorScript bhvMantaRay[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, manta_seg5_anims_05008EB4),
    ANIMATE(MANTA_ANIM_SWIM),
    CALL_NATIVE(bhv_manta_ray_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_manta_ray_loop),
    END_LOOP(),
};

const BehaviorScript bhvFallingPillar[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BOSS)),//--E
    SET_HOME(),
    CALL_NATIVE(bhv_falling_pillar_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_falling_pillar_loop),
    END_LOOP(),
};

const BehaviorScript bhvFallingPillarHitbox[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BOSS)),//--E
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_falling_pillar_hitbox_loop),
    END_LOOP(),
};

const BehaviorScript bhvPillarBase[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(jrb_seg7_collision_pillar_base),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvJrbFloatingBox[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(jrb_seg7_collision_floating_box),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_jrb_floating_box_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvDecorativePendulum[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_init_room),
    CALL_NATIVE(bhv_decorative_pendulum_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_decorative_pendulum_loop),
    END_LOOP(),
};

const BehaviorScript bhvTreasureChestsShip[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    DROP_TO_FLOOR(),
    CALL_NATIVE(bhv_treasure_chest_ship_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_treasure_chest_ship_loop),
    END_LOOP(),
};

const BehaviorScript bhvTreasureChestsJrb[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    DROP_TO_FLOOR(),
    CALL_NATIVE(bhv_treasure_chest_jrb_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_treasure_chest_jrb_loop),
    END_LOOP(),
};

const BehaviorScript bhvTreasureChests[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    DROP_TO_FLOOR(),
    CALL_NATIVE(bhv_treasure_chest_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_treasure_chest_loop),
    END_LOOP(),
};

const BehaviorScript bhvTreasureChestBottom[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    DROP_TO_FLOOR(),
    CALL_NATIVE(bhv_treasure_chest_bottom_init),
    SET_INT(oIntangibleTimer, -1),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_treasure_chest_bottom_loop),
    END_LOOP(),
};

const BehaviorScript bhvTreasureChestTop[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_treasure_chest_top_loop),
    END_LOOP(),
};

const BehaviorScript bhvMips[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_HOLDABLE | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, mips_seg6_anims_06015634),
    SET_INT(oInteractType, INTERACT_GRABBABLE),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 50, /*Height*/ 75),
    SET_INT(oIntangibleTimer, 0),
    CALL_NATIVE(bhv_mips_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_mips_loop),
    END_LOOP(),
};

const BehaviorScript bhvYoshi[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, yoshi_seg5_anims_05024100),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 160, /*Height*/ 150),
    ANIMATE(YOSHI_ANIM_IDLE),
    SET_HOME(),
    CALL_NATIVE(bhv_yoshi_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_yoshi_loop),
    END_LOOP(),
};

const BehaviorScript bhvKoopa[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    DROP_TO_FLOOR(),
    LOAD_ANIMATIONS(oAnimations, koopa_seg6_anims_06011364),
    ANIMATE(KOOPA_ANIM_WALK),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 50, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SCALE(/*Unused*/ 0, /*Field*/ 150),
    SET_FLOAT(oKoopaAgility, 1),
    CALL_NATIVE(bhv_koopa_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_koopa_update),
    END_LOOP(),
};

const BehaviorScript bhvKoopaRaceEndpoint[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DROP_TO_FLOOR(),
    SPAWN_CHILD_WITH_PARAM(/*Bhv param*/ 0, /*Model*/ MODEL_KOOPA_FLAG, /*Behavior*/ bhvKoopaFlag),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_koopa_race_endpoint_update),
    END_LOOP(),
};

const BehaviorScript bhvKoopaFlag[] = {
    BEGIN(OBJ_LIST_POLELIKE),
    SET_INTERACT_TYPE(INTERACT_POLE),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 700),
    SET_INT(oIntangibleTimer, 0),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    DROP_TO_FLOOR(),
    LOAD_ANIMATIONS(oAnimations, koopa_flag_seg6_anims_06001028),
    ANIMATE(KOOPA_FLAG_ANIM_WAVE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_pole_base_loop),
    END_LOOP(),
};

const BehaviorScript bhvPokey[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DROP_TO_FLOOR(),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 60, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_pokey_update),
    END_LOOP(),
};

const BehaviorScript bhvPokeyBodyPart[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 60, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_pokey_body_part_update),
    END_LOOP(),
};

const BehaviorScript bhvSwoop[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    LOAD_ANIMATIONS(oAnimations, swoop_seg6_anims_060070D0),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 50, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_init_room),
    SCALE(/*Unused*/ 0, /*Field*/ 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_swoop_update),
    END_LOOP(),
};

const BehaviorScript bhvFlyGuy[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY | OBJ_FLAG_NO_DREAM_COMET)),//--E
    LOAD_ANIMATIONS(oAnimations, flyguy_seg8_anims_08011A64),
    ANIMATE(FLY_GUY_ANIM_FLYING),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 50, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 1000, /*Buoyancy*/ 600, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_init_room),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_TWIRL_BOUNCE),
    SET_FLOAT(oGraphYOffset, 30),
    SCALE(/*Unused*/ 0, /*Field*/ 150),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_fly_guy_update),
    END_LOOP(),
};

const BehaviorScript bhvGoomba[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY | OBJ_FLAG_ATTACHABLE_BY_ROPE)),//--E
    DROP_TO_FLOOR(),
    LOAD_ANIMATIONS(oAnimations, goomba_seg8_anims_0801DA4C),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 40, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_goomba_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_goomba_update),
    END_LOOP(),
};

const BehaviorScript bhvGoombaTripletSpawner[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DROP_TO_FLOOR(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_goomba_triplet_spawner_update),
    END_LOOP(),
};

#ifdef FLOOMBAS
const BehaviorScript bhvFloomba[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    SET_INT(oIsFloomba, TRUE),
    GOTO(bhvGoomba + 1),
};

#ifdef INTRO_FLOOMBAS
const BehaviorScript bhvFloombaStartup[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    SET_INT(oIsFloomba, TRUE),
    SET_INT(oAction, FLOOMBA_ACT_STARTUP),
    OR_INT(oFlags, OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_ANIMATIONS(oAnimations, goomba_seg8_anims_0801DA4C),
    SET_HOME(),
    CALL_NATIVE(bhv_goomba_init),
    SET_FLOAT(oDrawingDistance, 30000),
    SET_INT(oIntangibleTimer, -1),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 0, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_goomba_update),
    END_LOOP(),
};
#endif

const BehaviorScript bhvFloombaTripletSpawner[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    SET_INT(oIsFloomba, TRUE),
    GOTO(bhvGoombaTripletSpawner + 1),
};
#endif

const BehaviorScript bhvChainChomp[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    DROP_TO_FLOOR(),
    LOAD_ANIMATIONS(oAnimations, chain_chomp_seg6_anims_06025178),
    ANIMATE(CHAIN_CHOMP_ANIM_CHOMPING),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    HIDE(),
    SET_HOME(),
    SET_FLOAT(oGraphYOffset, 240),
    SCALE(/*Unused*/ 0, /*Field*/ 200),
    SPAWN_CHILD_WITH_PARAM(/*Bhv param*/ 0, /*Model*/ MODEL_WOODEN_POST, /*Behavior*/ bhvWoodenPost),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_chain_chomp_update),
    END_LOOP(),
};

const BehaviorScript bhvChainChompChainPart[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_FLOAT(oGraphYOffset, 40),
    SCALE(/*Unused*/ 0, /*Field*/ 200),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_chain_chomp_chain_part_update),
    END_LOOP(),
};

const BehaviorScript bhvWoodenPost[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(poundable_pole_collision_wooden_post),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST | OBJ_FLAG_E__SG_CUSTOM)),//--E
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_HITBOX(/*Radius*/ 50, /*Height*/ 200),//--E
    SET_INT(oIntangibleTimer, 0),//--E
    SET_INT(oNumLootCoins, 5),
    DROP_TO_FLOOR(),
    SET_HOME(),
    SCALE(/*Unused*/ 0, /*Field*/ 50),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_wooden_post_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvChainChompGate[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(bob_seg7_collision_chain_chomp_gate),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_chain_chomp_gate_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_chain_chomp_gate_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvWigglerHead[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    DROP_TO_FLOOR(),
    LOAD_ANIMATIONS(oAnimations, wiggler_seg5_anims_0500EC8C),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 60, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    HIDE(),
    SCALE(/*Unused*/ 0, /*Field*/ 400),
    SET_FLOAT(oWigglerFallThroughFloorsHeight, 5000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_wiggler_update),
    END_LOOP(),
};

const BehaviorScript bhvWigglerBody[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_ANIMATIONS(oAnimations, wiggler_seg5_anims_0500C874),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SCALE(/*Unused*/ 0, /*Field*/ 400),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_wiggler_body_part_update),
    END_LOOP(),
};

const BehaviorScript bhvEnemyLakitu[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    LOAD_ANIMATIONS(oAnimations, lakitu_enemy_seg5_anims_050144D4),
    ANIMATE(ENEMY_LAKITU_ANIM_SPAWN),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 40, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_enemy_lakitu_update),
    END_LOOP(),
};

const BehaviorScript bhvCameraLakitu[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, lakitu_seg6_anims_060058F8),
    ANIMATE(CAMERA_LAKITU_ANIM_DEFAULT),
    CALL_NATIVE(bhv_init_room),
    CALL_NATIVE(bhv_camera_lakitu_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_camera_lakitu_update),
    END_LOOP(),
};

const BehaviorScript bhvCloud[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_HOME(),
    SET_INT(oOpacity, 240),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_cloud_update),
    END_LOOP(),
};

const BehaviorScript bhvCloudPart[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INT(oOpacity, 240),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_cloud_part_update),
    END_LOOP(),
};

const BehaviorScript bhvSpiny[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    LOAD_ANIMATIONS(oAnimations, spiny_seg5_anims_05016EAC),
    ANIMATE(SPINY_ANIM_DEFAULT),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 40, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_spiny_update),
    END_LOOP(),
};

const BehaviorScript bhvMontyMole[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    DROP_TO_FLOOR(),
    LOAD_ANIMATIONS(oAnimations, monty_mole_seg5_anims_05007248),
    ANIMATE(MONTY_MOLE_ANIM_BEGIN_JUMP_INTO_HOLE),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    HIDE(),
    SET_INT(oIntangibleTimer, -1),
    SET_FLOAT(oGraphYOffset, -60),
    SCALE(/*Unused*/ 0, /*Field*/ 150),
    DELAY(1),
    CALL_NATIVE(bhv_monty_mole_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_monty_mole_update),
    END_LOOP(),
};

const BehaviorScript bhvMontyMoleHole[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DROP_TO_FLOOR(),
    SCALE(/*Unused*/ 0, /*Field*/ 150),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_monty_mole_hole_update),
    END_LOOP(),
};

const BehaviorScript bhvMontyMoleRock[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    BILLBOARD(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_FLOAT(oGraphYOffset, 10),
    SCALE(/*Unused*/ 0, /*Field*/ 200),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_monty_mole_rock_update),
    END_LOOP(),
};

const BehaviorScript bhvPlatformOnTrack[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 50, /*Gravity*/ -100, /*Bounciness*/ -50, /*Drag strength*/ 100, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_init_room),
    CALL_NATIVE(bhv_platform_on_track_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_platform_on_track_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvTrackBall[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    CALL_NATIVE(bhv_init_room),
    SCALE(/*Unused*/ 0, /*Field*/ 15),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_track_ball_update),
    END_LOOP(),
};

const BehaviorScript bhvSeesawPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_seesaw_platform_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_seesaw_platform_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvFerrisWheelAxle[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    ADD_INT(oMoveAngleYaw, 0x4000),
    CALL_NATIVE(bhv_ferris_wheel_axle_init),
    BEGIN_LOOP(),
        ADD_INT(oFaceAngleRoll, 400),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvFerrisWheelPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ferris_wheel_platform_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvWaterBombSpawner[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DROP_TO_FLOOR(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_water_bomb_spawner_update),
    END_LOOP(),
};

const BehaviorScript bhvWaterBomb[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 120, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_water_bomb_update),
    END_LOOP(),
};

const BehaviorScript bhvWaterBombShadow[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SCALE(/*Unused*/ 0, /*Field*/ 150),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_water_bomb_shadow_update),
    END_LOOP(),
};

const BehaviorScript bhvTTCRotatingSolid[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    SET_FLOAT(oCollisionDistance, 450),
    CALL_NATIVE(bhv_ttc_rotating_solid_init),
    SET_INT(oTTCRotatingSolidNumTurns, 1),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ttc_rotating_solid_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvTTCPendulum[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(ttc_seg7_collision_clock_pendulum),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oCollisionDistance, 1500),
    CALL_NATIVE(bhv_ttc_pendulum_init),
    SET_FLOAT(oTTCPendulumAccelDir, 1),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ttc_pendulum_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvTTCTreadmill[] = {
    BEGIN(OBJ_LIST_SURFACE),
#ifdef PLATFORM_DISPLACEMENT_2
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_VELOCITY_PLATFORM)),
#else
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
#endif
    SET_FLOAT(oCollisionDistance, 750),
    CALL_NATIVE(bhv_ttc_treadmill_init),
    DELAY(1),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ttc_treadmill_update),
        CALL_NATIVE(cur_obj_compute_vel_xz),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvTTCMovingBar[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(ttc_seg7_collision_sliding_surface),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    SET_FLOAT(oCollisionDistance, 550),
    CALL_NATIVE(bhv_ttc_moving_bar_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ttc_moving_bar_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvTTCCog[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oCollisionDistance, 400),
    CALL_NATIVE(bhv_ttc_cog_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ttc_cog_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvTTCPitBlock[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    SET_FLOAT(oCollisionDistance, 350),
    CALL_NATIVE(bhv_ttc_pit_block_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ttc_pit_block_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvTTCElevator[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(ttc_seg7_collision_clock_platform),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    SET_FLOAT(oCollisionDistance, 400),
    CALL_NATIVE(bhv_ttc_elevator_init),
    SET_FLOAT(oTTCElevatorDir, 1),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ttc_elevator_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvTTC2DRotator[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(ttc_seg7_collision_clock_main_rotation),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oCollisionDistance, 1800),
    CALL_NATIVE(bhv_ttc_2d_rotator_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ttc_2d_rotator_update),
    END_LOOP(),
};

const BehaviorScript bhvTTCSpinner[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(ttc_seg7_collision_rotating_clock_platform2),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_FLOAT(oCollisionDistance, 450),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ttc_spinner_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvMrBlizzard[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    DROP_TO_FLOOR(),
    LOAD_ANIMATIONS(oAnimations, snowman_seg5_anims_0500D118),
    ANIMATE(MR_BLIZZARD_ANIM_SPAWN_SNOWBALL),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_mr_blizzard_init),
    SET_FLOAT(oMrBlizzardScale, 1),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_mr_blizzard_update),
    END_LOOP(),
};

const BehaviorScript bhvMrBlizzardSnowball[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    BILLBOARD(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -300, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SCALE(/*Unused*/ 0, /*Field*/ 200),
    ADD_INT(oMoveAngleYaw, -0x5B58),
    SET_FLOAT(oForwardVel, 5),
    SET_FLOAT(oVelY, -1),
    SET_FLOAT(oGraphYOffset, 10),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_mr_blizzard_snowball),
    END_LOOP(),
};

const BehaviorScript bhvSlidingPlatform2[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    CALL_NATIVE(bhv_sliding_platform_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sliding_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvOctagonalPlatformRotating[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_rotating_octagonal_plat_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_rotating_octagonal_plat_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvAnimatesOnFloorSwitchPress[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW)),
    SET_FLOAT(oDrawingDistance, 8000),
    SET_FLOAT(oCollisionDistance, 8000),
    CALL_NATIVE(bhv_animates_on_floor_switch_press_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_animates_on_floor_switch_press_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvActivatedBackAndForthPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    CALL_NATIVE(bhv_activated_back_and_forth_platform_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_activated_back_and_forth_platform_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvRecoveryHeart[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_recovery_heart_loop),
    END_LOOP(),
};

const BehaviorScript bhvAbilityRecoveryHeart[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ability_heart_loop),
    END_LOOP(),
};

const BehaviorScript bhvWaterBombCannon[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_water_bomb_cannon_loop),
    END_LOOP(),
};

const BehaviorScript bhvCannonBarrelBubbles[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bubble_cannon_barrel_loop),
    END_LOOP(),
};

const BehaviorScript bhvUnagi[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, unagi_seg5_anims_05012824),
    ANIMATE(UNAGI_ANIM_IDLE_2),
    SET_HOME(),
    SCALE(/*Unused*/ 0, /*Field*/ 300),
    SET_FLOAT(oDrawingDistance, 6000),
    CALL_NATIVE(bhv_unagi_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_unagi_loop),
    END_LOOP(),
};

const BehaviorScript bhvUnagiSubobject[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_unagi_subobject_loop),
    END_LOOP(),
};

const BehaviorScript bhvDorrie[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(dorrie_seg6_collision_0600F644),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, dorrie_seg6_anims_0600F638),
    SET_HOME(),
    SET_FLOAT(oCollisionDistance, 30000),
    ADD_FLOAT(oPosX, 2000),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_dorrie_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvHauntedChair[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    DROP_TO_FLOOR(),
    LOAD_ANIMATIONS(oAnimations, chair_seg5_anims_05005784),
    ANIMATE(HAUNTED_CHAIR_ANIM_DEFAULT),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 40, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_HOME(),
    CALL_NATIVE(bhv_init_room),
    CALL_NATIVE(bhv_haunted_chair_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_haunted_chair_loop),
    END_LOOP(),
};

const BehaviorScript bhvMadPiano[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BOSS)),//--E
    DROP_TO_FLOOR(),
    LOAD_ANIMATIONS(oAnimations, mad_piano_seg5_anims_05009B14),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 40, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_HOME(),
    ADD_INT(oMoveAngleYaw, 0x4000),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_mad_piano_update),
    END_LOOP(),
};

const BehaviorScript bhvFlyingBookend[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    LOAD_ANIMATIONS(oAnimations, bookend_seg5_anims_05002540),
    ANIMATE(FLYING_BOOKEND_ANIM_SPAWN),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 60, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_INT(oMoveFlags, OBJ_MOVE_NONE),
    SCALE(/*Unused*/ 0, /*Field*/ 70),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_flying_bookend_loop),
    END_LOOP(),
};

const BehaviorScript bhvBookendSpawn[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bookend_spawn_loop),
    END_LOOP(),
};

const BehaviorScript bhvHauntedBookshelfManager[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_haunted_bookshelf_manager_loop),
    END_LOOP(),
};

const BehaviorScript bhvBookSwitch[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    SET_FLOAT(oGraphYOffset, 30),
    ADD_INT(oMoveAngleYaw, 0x4000),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_book_switch_loop),
    END_LOOP(),
};

const BehaviorScript bhvFirePiranhaPlant[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    DROP_TO_FLOOR(),
    LOAD_ANIMATIONS(oAnimations, piranha_plant_seg6_anims_0601C31C),
    ANIMATE(FIRE_PIRANHA_PLANT_ANIM_SHRINK),
    SET_HOME(),
    HIDE(),
    CALL_NATIVE(bhv_fire_piranha_plant_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_fire_piranha_plant_update),
    END_LOOP(),
};

const BehaviorScript bhvMovingFlame[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_moving_flame_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvMovingFlameEmber[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 0, /*Gravity*/ 200, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_moving_flame_particle_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};

const BehaviorScript bhvFireSpitter[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SCALE(/*Unused*/ 0, /*Field*/ 40),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_fire_spitter_update),
    END_LOOP(),
};

const BehaviorScript bhvSnufit[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        SET_INT(oSnufitRecoil, 0),
        CALL_NATIVE(bhv_snufit_loop),
    END_LOOP(),
};

const BehaviorScript bhvSnufitBalls[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    BILLBOARD(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 10, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_init_room),
    SET_FLOAT(oGraphYOffset, 10),
    SCALE(/*Unused*/ 0, /*Field*/ 10),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_snufit_balls_loop),
    END_LOOP(),
};

const BehaviorScript bhvHorizontalGrindel[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(ssl_seg7_collision_grindel),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    DROP_TO_FLOOR(),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 40, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SCALE(/*Unused*/ 0, /*Field*/ 90),
    CALL_NATIVE(bhv_horizontal_grindel_init),
    BEGIN_LOOP(),
        CALL_NATIVE(cur_obj_update_floor_and_walls),
        CALL_NATIVE(bhv_horizontal_grindel_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvEyerokBoss[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_eyerok_boss_loop),
    END_LOOP(),
};

const BehaviorScript bhvEyerokHand[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, eyerok_seg5_anims_050116E4),
    ANIMATE(EYEROK_HAND_ANIM_SLEEPING),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 150, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_HOME(),
    SET_INT(oAnimState, EYEROK_HAND_ANIM_STATE_EYE_CLOSED),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_eyerok_hand_loop),
    END_LOOP(),
};

const BehaviorScript bhvKlepto[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),//--E
    LOAD_ANIMATIONS(oAnimations, klepto_seg5_anims_05008CFC),
    ANIMATE(KLEPTO_ANIM_DIVE_0),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 100, /*Gravity*/ 0, /*Bounciness*/ -20, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_HOME(),
    CALL_NATIVE(bhv_klepto_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_klepto_update),
    END_LOOP(),
};

const BehaviorScript bhvBird[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, birds_seg5_anims_050009E8),
    ANIMATE(BIRD_ANIM_FLY),
    HIDE(),
    SCALE(/*Unused*/ 0, /*Field*/ 70),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bird_update),
    END_LOOP(),
};

const BehaviorScript bhvRacingPenguin[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, penguin_seg5_anims_05008B74),
    ANIMATE(PENGUIN_ANIM_IDLE),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 300, /*Gravity*/ -800, /*Bounciness*/ -5, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    SCALE(/*Unused*/ 0, /*Field*/ 400),
    CALL_NATIVE(bhv_racing_penguin_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_racing_penguin_update),
    END_LOOP(),
};

const BehaviorScript bhvPenguinRaceFinishLine[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_penguin_race_finish_line_update),
    END_LOOP(),
};

const BehaviorScript bhvPenguinRaceShortcutCheck[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_penguin_race_shortcut_check_update),
    END_LOOP(),
};

const BehaviorScript bhvCoffinSpawner[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_coffin_spawner_loop),
    END_LOOP(),
};

const BehaviorScript bhvCoffin[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(bbh_seg7_collision_coffin),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_coffin_loop),
    END_LOOP(),
};

const BehaviorScript bhvClamShell[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DROP_TO_FLOOR(),
    LOAD_ANIMATIONS(oAnimations, clam_shell_seg5_anims_05001744),
    SET_FLOAT(oGraphYOffset, 10),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_clam_loop),
    END_LOOP(),
};

const BehaviorScript bhvSkeeter[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    LOAD_ANIMATIONS(oAnimations, skeeter_seg6_anims_06007DE0),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 180, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 1200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_skeeter_update),
    END_LOOP(),
};

const BehaviorScript bhvSkeeterWave[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_skeeter_wave_update),
    END_LOOP(),
};

const BehaviorScript bhvSwingPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(rr_seg7_collision_pendulum),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oCollisionDistance, 2000),
    CALL_NATIVE(bhv_swing_platform_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_swing_platform_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvDonutPlatformSpawner[] = {
    BEGIN(OBJ_LIST_SPAWNER),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_donut_platform_spawner_update),
    END_LOOP(),
};

const BehaviorScript bhvDonutPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(rr_seg7_collision_donut_platform),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_donut_platform_update),
    END_LOOP(),
};

const BehaviorScript bhvDDDPole[] = {
    BEGIN(OBJ_LIST_POLELIKE),
    SET_INTERACT_TYPE(INTERACT_POLE),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 800),
    SET_INT(oIntangibleTimer, 0),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HOME(),
    CALL_NATIVE(bhv_ddd_pole_init),
    SET_FLOAT(oDDDPoleVel, 10),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ddd_pole_update),
        CALL_NATIVE(bhv_pole_base_loop),
    END_LOOP(),
};

const BehaviorScript bhvRedCoinStarMarker[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    DROP_TO_FLOOR(),
    SCALE(/*Unused*/ 0, /*Field*/ 150),
    SET_INT(oFaceAnglePitch, 0x4000),
    ADD_FLOAT(oPosY, 60),
    CALL_NATIVE(bhv_red_coin_star_marker_init),
    BEGIN_LOOP(),
        ADD_INT(oFaceAngleYaw, 0x100),
    END_LOOP(),
};

const BehaviorScript bhvTripletButterfly[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, butterfly_seg3_anims_030056B0),
    ANIMATE(BUTTERFLY_ANIM_FLYING),
    HIDE(),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 0, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_FLOAT(oTripletButterflyScale, 1),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_triplet_butterfly_update),
    END_LOOP(),
};

const BehaviorScript bhvBubba[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 200, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    SCALE(/*Unused*/ 0, /*Field*/ 50),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bubba_loop),
    END_LOOP(),
};

const BehaviorScript bhvBeginningLakitu[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_ANIMATIONS(oAnimations, lakitu_seg6_anims_060058F8),
    ANIMATE(INTRO_LAKITU_ANIM_DEFAULT),
    SET_INT(oOpacity, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_intro_lakitu_loop),
    END_LOOP(),
};

const BehaviorScript bhvBeginningPeach[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_ANIMATIONS(oAnimations, peach_seg5_anims_0501C41C),
    ANIMATE(PEACH_ANIM_0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_intro_peach_loop),
    END_LOOP(),
};

const BehaviorScript bhvEndBirds1[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, birds_seg5_anims_050009E8),
    ANIMATE(END_BIRDS_ANIM_FLY),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_end_birds_1_loop),
    END_LOOP(),
};

const BehaviorScript bhvEndBirds2[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, birds_seg5_anims_050009E8),
    ANIMATE(END_BIRDS_ANIM_FLY),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_end_birds_2_loop),
    END_LOOP(),
};

const BehaviorScript bhvIntroScene[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_intro_scene_loop),
    END_LOOP(),
};

const BehaviorScript bhvIntroSkybox[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        ADD_FLOAT(oPosX, 5),
    END_LOOP(),
};

const BehaviorScript bhvLevelPipe[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(level_pipe_collision),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oDrawingDistance, 20000),
    CALL_NATIVE(level_pipe_init),
    BEGIN_LOOP(),
        CALL_NATIVE(level_pipe_loop),
    END_LOOP(),
};

extern void bhv_hub_platform_loop(void);
const BehaviorScript bhvHubPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(hub_platform_collision),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oDrawingDistance, 20000),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hub_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern void bhv_shopitem_loop(void);
const BehaviorScript bhvShopItem[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_FLOAT(oDrawingDistance, 20000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_shopitem_loop),
    END_LOOP(),
};

extern void bhv_shop_controller(void);
const BehaviorScript bhvShopController[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_shop_controller),
    END_LOOP(),
};

extern void bhv_ability(void);
const BehaviorScript bhvAbilityUnlock[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_FLOAT(oGraphYOffset, 100),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ability),
    END_LOOP(),
};

const BehaviorScript bhvCheckpointFlag[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, checkpoint_flag_anims),
    SCALE(/*Unused*/ 0, /*Field*/ 140),
    ANIMATE(0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_checkpoint_flag),
    END_LOOP(),
};

const BehaviorScript bhvFlipswitch[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET),
    LOAD_COLLISION_DATA(flipswitch_collision),
    SET_FLOAT(oDrawingDistance, 20000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_flipswitch),
    END_LOOP(),
};

const BehaviorScript bhvNoteblock[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(noteblock_collision),
    SET_FLOAT(oDrawingDistance, 4000),
    SET_FLOAT(oCollisionDistance, 1000),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_noteblock),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvStarPieceSwitch[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW | OBJ_FLAG_NO_DREAM_COMET),//--E
    LOAD_COLLISION_DATA(blue_coin_switch_seg8_collision_08000E98),
    SET_INT(oIntangibleTimer, 0),//--E
    SET_HITBOX(/*Radius*/ 120, /*Height*/ 100),//--E
    SET_INT(oAnimState, 1),
    SET_HOME(),//prevent fucking the bcs with timeslow
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_star_piece_switch_loop),
    END_LOOP(),
};

const BehaviorScript bhvStarPiece[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_star_piece_loop),
    END_LOOP(),
};

const BehaviorScript bhvDashBoosterParticle[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_dash_booster_particle),
    END_LOOP(),
};

const BehaviorScript bhvCutsceneManager[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    BEGIN_LOOP(),
        CALL_NATIVE(cm_manager_object_loop),
    END_LOOP(),
};
const BehaviorScript bhvCutsceneCamera[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(cm_camera_object_loop),
    END_LOOP(),
};

const BehaviorScript bhvBioshockFloaty[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(floaty_collision),
    SET_FLOAT(oFloatingPlatformHeightOffset, 64),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_floating_platform_b_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvGauge[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_NO_DREAM_COMET),
    LOAD_COLLISION_DATA(gauge_collision),
    LOAD_ANIMATIONS(oAnimations, gauge_anims),
    ANIMATE(0),
    CALL_NATIVE(bhv_gauge_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_gauge_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvWaterfallHidden[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE )),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_waterfall_hidden_loop),
    END_LOOP(),
};

const BehaviorScript bhvWaterfall[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE )),
    LOAD_COLLISION_DATA(waterfall_collision),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_waterfall_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvDebris[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE )),
    LOAD_COLLISION_DATA(debris_collision),
    SET_FLOAT(oDrawingDistance, 7000),
    CALL_NATIVE(bhv_debris_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_debris_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvAirlock[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE )),
    LOAD_COLLISION_DATA(airlock_collision),
    SET_FLOAT(oDrawingDistance, 20000),
    SET_HOME(),
    CALL_NATIVE(bhv_airlock_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_airlock_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvAirlockButton[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE )),
    LOAD_COLLISION_DATA(airlock_button_collision),
    SET_FLOAT(oDrawingDistance, 7000),
    CALL_NATIVE(bhv_airlock_button_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_airlock_button_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvAirlockWater[] = {
    BEGIN(OBJ_LIST_SPAWNER),
    LOAD_COLLISION_DATA(airlock_water_collision),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO)),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
        CALL_NATIVE(bhv_airlock_water_loop),
    END_LOOP(),
};

const BehaviorScript bhvBigDaddy[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_ANIMATIONS(oAnimations, bigdaddy_anims),
    ANIMATE(2),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    SET_HOME(),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    SET_HITBOX(/*Radius*/ 170, /*Height*/ 420),
    SET_INT(oIntangibleTimer, 0),
    CALL_NATIVE(bhv_big_daddy_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_big_daddy_loop),
    END_LOOP(),
};

const BehaviorScript bhvLittleSister[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    DROP_TO_FLOOR(),
    LOAD_ANIMATIONS(oAnimations, little_sister_anims),
    ANIMATE(0),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_INT(oInteractType, INTERACT_TEXT),
    //SET_INT(oInteractionSubtype, INT_SUBTYPE_HOLDABLE_NPC),
    SET_INT(oIntangibleTimer, 0),
    SET_HITBOX(/*Radius*/ 55, /*Height*/ 230),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_little_sister_loop),
    END_LOOP(),
};

const BehaviorScript bhvCrusher[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(crusher_collision),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO)),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    SET_HITBOX(/*Radius*/ 243, /*Height*/ 706),
    SET_FLOAT(oDrawingDistance, 4000),
    CALL_NATIVE(bhv_crusher_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_crusher_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvTurretBody[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    SET_HITBOX(/*Radius*/ 110, /*Height*/ 210),
    SET_INTERACT_TYPE(INTERACT_SPINY_WALKING),
    SET_FLOAT(oDamageOrCoinValue, 2),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 40, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_turret_body_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_turret_body_loop),
    END_LOOP(),
};

const BehaviorScript bhvTurretHead[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags,(OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, turret_head_heavy_anims),
    CALL_NATIVE(bhv_turret_head_init),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_turret_head_loop),
    END_LOOP(),
};

const BehaviorScript bhvTurretHeavy[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags,(OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, turret_head_heavy_anims),
    CALL_NATIVE(bhv_turret_head_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_turret_head_loop),
    END_LOOP(),
};

const BehaviorScript bhvTurretPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(turret_platform_collision),
    OR_INT(oFlags,(OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_ACTIVE_FROM_AFAR)),
    SET_FLOAT(oDrawingDistance, 4000),
    CALL_NATIVE(bhv_turret_platform_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_turret_platform),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvTurretCover[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags,(OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_ACTIVE_FROM_AFAR)),
    //LOAD_COLLISION_DATA(turret_cover_collision),
    SET_FLOAT(oDrawingDistance, 4000),
    CALL_NATIVE(bhv_turret_cover_init),
    BEGIN_LOOP(),
        //CALL_NATIVE(load_object_collision_model),
        CALL_NATIVE(bhv_turret_cover),
    END_LOOP(),
};

const BehaviorScript bhvTurretPanel[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags,(OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_ACTIVE_FROM_AFAR)),
    SET_FLOAT(oDrawingDistance, 4000),
    LOAD_COLLISION_DATA(turret_panel_collision),
    CALL_NATIVE(bhv_turret_panel_init),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
        CALL_NATIVE(bhv_turret_panel),
    END_LOOP(),
};

const BehaviorScript bhvGate[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags,(OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_ACTIVE_FROM_AFAR)),
    SET_HOME(),
    LOAD_COLLISION_DATA(bgate_collision),
    SET_FLOAT(oDrawingDistance, 4000),
    CALL_NATIVE(bhv_gate_init),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
        CALL_NATIVE(bhv_gate),
    END_LOOP(),
};

const BehaviorScript bhvAlarm[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_ANIMATIONS(oAnimations, alarm_anims),
    ANIMATE(0),
    SET_FLOAT(oDrawingDistance, 4000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_alarm),
    END_LOOP(),
};

const BehaviorScript bhvCork[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(megacork_collision),
    SET_FLOAT(oDrawingDistance, 6000),
    //CALL_NATIVE(bhv_cork_init),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
        CALL_NATIVE(bhv_cork),
    END_LOOP(),
};

extern void bhv_watertemple_init(void);
const BehaviorScript bhvWaterTemple[] = {
    BEGIN(OBJ_LIST_SPAWNER),
    LOAD_COLLISION_DATA(watertemple_collision),
    SET_HOME(),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO)),
    CALL_NATIVE(bhv_watertemple_init),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
        CALL_NATIVE(bhv_watertemple),
    END_LOOP(),
};

const BehaviorScript bhvBossDaddy[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_MOVE_Y_WITH_TERMINAL_VEL | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_ANIMATIONS(oAnimations, bigdaddy_anims),
    ANIMATE(2),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 170, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 5000, /*Friction*/ 5000, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    SET_HITBOX(/*Radius*/ 170, /*Height*/ 420),
    SET_INTERACT_TYPE(INTERACT_BULLY),
    SET_FLOAT(oDrawingDistance, 6000),
    SET_HOME(),
    CALL_NATIVE(bhv_init_room),
    CALL_NATIVE(bhv_boss_daddy_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_boss_daddy),
    END_LOOP(),
};

const BehaviorScript bhvSafeExplosion[] = {
    BEGIN(OBJ_LIST_SPAWNER),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_INTERACT_TYPE(INTERACT_NONE),
    SET_INT(oIntangibleTimer, 0),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    CALL_NATIVE(bhv_explosion_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_explosion_loop),
        ADD_INT(oAnimState, 1),
    END_LOOP(),
};
/* GROUP B END */

/* GROUP E START */

//--Level
const BehaviorScript bhvE_PistolGuy[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_E__SG_ENEMY)),
    SET_INT(oBehParams2ndByte, 0),
    GOTO(bhvE_Enemy + 1),
};

const BehaviorScript bhvE_ChaingunGuy[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_E__SG_ENEMY)),
    SET_INT(oBehParams2ndByte, 1),
    GOTO(bhvE_Enemy + 1),
};

const BehaviorScript bhvE_Caco[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_E__SG_ENEMY)),
    SET_INT(oBehParams2ndByte, 3),
    GOTO(bhvE_Enemy + 1),
};

const BehaviorScript bhvIntroCloth[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
    END_LOOP(),
};

const BehaviorScript bhvIntroBreakdoor[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
    END_LOOP(),
};

const BehaviorScript bhvE_Door[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_E__SG_COLLISION_CUSTOM)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_e__door),
    END_LOOP(),
};

const BehaviorScript bhvE_Key[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_E__SG_CUSTOM)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_e__key),
    END_LOOP(),
};

const BehaviorScript bhvE_KeyCollect[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_e__key_collect),
    END_LOOP(),
};

const BehaviorScript bhvE_Elevator[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_e__elevator),
    END_LOOP(),
};
const BehaviorScript bhvE_ElevatorBase[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    LOAD_COLLISION_DATA(e_elevator_base_collision),
    SET_FLOAT(oDrawingDistance, 20000),
    CALL_NATIVE(load_object_static_model),
    BREAK(),
};

const BehaviorScript bhvE_Candelabra[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_E__SG_CUSTOM)),
    CALL_NATIVE(bhv_e__candelabra),
    BREAK(),
};

const BehaviorScript bhvE_Switch[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_E__SG_COLLISION_CUSTOM | OBJ_FLAG_NO_DREAM_COMET)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_e__switch),
    END_LOOP(),
};

const BehaviorScript bhvE_Teleport[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_e__teleport),
    END_LOOP(),
};
const BehaviorScript bhvE_TeleportEffect[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_e__teleport_effect),
    END_LOOP(),
};
const BehaviorScript bhvE_Medkit[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_E__SG_CUSTOM)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_e__medkit),
    END_LOOP(),
};

const BehaviorScript bhvE_Tutorial[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_e__tutorial),
    END_LOOP(),
};
const BehaviorScript bhvE_Target[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(e_tb_collision),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_e__target),
    END_LOOP(),
};

//--Ability
/* GROUP E END */

const BehaviorScript bhvIntroPeach[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INT(oOpacity, 255),
    LOAD_ANIMATIONS(oAnimations, peach_seg5_anims_0501C41C),
    ANIMATE(PEACH_ANIM_WAVING),
    BEGIN_LOOP(),
    END_LOOP(),
};
const BehaviorScript bhvIntroToad[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_ANIMATIONS(oAnimations, toad_seg6_anims_0600FB58),
    ANIMATE(TOAD_ANIM_WEST_WAVING_BOTH_ARMS),
    SET_INT(oOpacity, 255),
    BEGIN_LOOP(),
    END_LOOP(),
};
const BehaviorScript bhvIntroEgadd[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_ANIMATIONS(oAnimations, egadd_anims),
    ANIMATE(0),
    BEGIN_LOOP(),
    END_LOOP(),
};
const BehaviorScript bhvIntroMachine[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_ANIMATIONS(oAnimations, machine_anims),
    ANIMATE(0),
    SET_INT(oOpacity, 0),
    BEGIN_LOOP(),
    END_LOOP(),
};

const BehaviorScript bhvIntroBowser[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_ANIMATIONS(oAnimations, wedser_anims),
    ANIMATE(1),
    DROP_TO_FLOOR(),
    BEGIN_LOOP(),
    END_LOOP(),
};

const BehaviorScript bhvEndBowser[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_ANIMATIONS(oAnimations, endser_anims),
    ANIMATE(0),
    BEGIN_LOOP(),
    END_LOOP(),
};

/* GROUP F START */

extern void bhv_layton_hint_loop(void);
const BehaviorScript bhvLayton[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, layton_anims),
    DROP_TO_FLOOR(),
    SCALE(0, 45),
    ANIMATE(0),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_NPC),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 250),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_layton_hint_loop),
    END_LOOP(),
};

extern void bhv_morshu_loop(void);
const BehaviorScript bhvMorshu[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO)),
    LOAD_ANIMATIONS(oAnimations, morshu_anims),
    DROP_TO_FLOOR(),
    ANIMATE(0),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_NPC),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 250),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_morshu_loop),
    END_LOOP(),
};

extern void bhv_music_menu_loop(void);
extern void bhv_redd_paintings_loop(void);
const BehaviorScript bhvRedd[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO)),
    LOAD_ANIMATIONS(oAnimations, redd_anims),
    DROP_TO_FLOOR(),
    ANIMATE(0),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_NPC),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 250),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_redd_paintings_loop),
    END_LOOP(),
};

const BehaviorScript bhvMumbo[] = {
	BEGIN(OBJ_LIST_GENACTOR),
	OR_INT(oFlags, OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_ANIMATIONS(oAnimations, mumbo_anims),
    ANIMATE(0),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_NPC),
    SET_HITBOX(/*Radius*/ 175, /*Height*/ 250),
    SPAWN_CHILD(MODEL_SYNTHESIZER, bhvSynthesizer),
	BEGIN_LOOP(),
		SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_music_menu_loop),
	END_LOOP(),
};

const BehaviorScript bhvSynthesizer[] = {
	BEGIN(OBJ_LIST_SURFACE),
	OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
	LOAD_COLLISION_DATA(synthesizer_collision),
	BEGIN_LOOP(),
		//CALL_NATIVE(load_object_collision_model),
	END_LOOP(),
};

/* GROUP A START */
extern const struct Animation *const jelly_anims[];
const BehaviorScript bhvJelly[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),
    LOAD_ANIMATIONS(oAnimations, jelly_anims),
    CALL_NATIVE(jelly_init),
    ANIMATE(0),
    BEGIN_LOOP(),
        CALL_NATIVE(jelly_loop),
    END_LOOP(),
};

extern const Collision jfplatform_collision[];
const BehaviorScript bhvJellyfishFieldsPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(jfplatform_collision),
    SET_FLOAT(oDrawingDistance, 8000),
    BEGIN_LOOP(),
        CALL_NATIVE(jfplatform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern const Collision taxistop_collision[];
const BehaviorScript bhvTaxiStop[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(taxistop_collision),
    SCALE(0, 200),
    SET_FLOAT(oDrawingDistance, 30000),
    BEGIN_LOOP(),
        CALL_NATIVE(taxistop_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern const struct Animation *const boat_anims[];
const BehaviorScript bhvtsBoat[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, boat_anims),
    ANIMATE(0),
    SCALE(0, 200),
    BEGIN_LOOP(),
        CALL_NATIVE(tsboat_loop),
    END_LOOP(),
};

extern const Collision tikibox_collision[];
const BehaviorScript bhvTikiBox[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(tikibox_collision),
    SCALE(0, 150),
    CALL_NATIVE(tiki_box_init),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
        CALL_NATIVE(tiki_box_loop),
    END_LOOP(),
};

extern const Collision tramp_collision[];
const BehaviorScript bhvTramp[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(tramp_collision),
    SET_FLOAT(oDrawingDistance, 9000.0f),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
        CALL_NATIVE(trampoline_loop),
    END_LOOP(), 
};

extern const Collision floating_checker_platform_collision[];
extern const struct Animation *const floating_checker_platform_anims[];
const BehaviorScript bhvFloatingCheckerPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(floating_checker_platform_collision),
    ANIMATE(0),
    SCALE(0, 160),
    LOAD_ANIMATIONS(oAnimations, floating_checker_platform_anims),
    SET_FLOAT(oDrawingDistance, 8000),
    BEGIN_LOOP(),
        CALL_NATIVE(fcp_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern const struct Animation *const kingjelly_anims[];
const BehaviorScript bhvKingJelly[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_NO_DREAM_COMET)),
    SCALE(0, 400),
    ANIMATE(0),
    LOAD_ANIMATIONS(oAnimations, kingjelly_anims),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(king_jelly_boss_loop),
    END_LOOP(),
};

const BehaviorScript bhvKingJellyZap[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    LOAD_ANIMATIONS(oAnimations, dAmpAnimsList),
    ANIMATE(AMP_ANIM_DEFAULT),
    SCALE(0, 600),
    BEGIN_LOOP(),
    END_LOOP(),
};

const BehaviorScript bhvKingJellyShock[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),
    SCALE(0, 120),
    BEGIN_LOOP(),
        //CALL_NATIVE(king_jelly_boss_shock),
    END_LOOP(),
};

extern const struct Animation *const squidward_anims[];
const BehaviorScript bhvSquidward[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    ANIMATE(0),
    LOAD_ANIMATIONS(oAnimations, squidward_anims),
    CALL_NATIVE(squidward_init),
    SCALE(0, 230),
    BEGIN_LOOP(),
        CALL_NATIVE(squidward_loop),
        SET_INT(oInteractStatus, 0),
    END_LOOP(),
};

extern const Collision kktable_collision[];
const BehaviorScript bhvKKTable[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(kktable_collision),
    SCALE(0, 180),
    CALL_NATIVE(load_object_static_model),
    BEGIN_LOOP(),
        //CALL_NATIVE(kktable_loop),
    END_LOOP(),
};

extern const Collision kkb_collision[];
const BehaviorScript bhvKKB[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(kkb_collision),
    SCALE(0, 180),
    CALL_NATIVE(load_object_static_model),
    BEGIN_LOOP(),
        //CALL_NATIVE(kktable_loop),
    END_LOOP(),
};

extern const Collision bh_red_button_collision[];
const BehaviorScript bhvBhButton[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(bh_red_button_collision),
    BEGIN_LOOP(),
        CALL_NATIVE(button_for_bridge_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvBhButton2[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(bh_red_button_collision),
    BEGIN_LOOP(),
        CALL_NATIVE(button_for_bridge_loop_2),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern const Collision bhbridge_collision[];
extern const struct Animation *const bhbridge_anims[];
const BehaviorScript bhvRBridge[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(bhbridge_collision),
    LOAD_ANIMATIONS(oAnimations, bhbridge_anims),
    ANIMATE(0),
    BEGIN_LOOP(),
        CALL_NATIVE(bridge_loop),
        //CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern const Collision a_plank_collision[];
extern const struct Animation *const a_plank_anims[];
const BehaviorScript bhvRPlank[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, a_plank_anims),
    ANIMATE(0),
    LOAD_COLLISION_DATA(a_plank_collision),
    BEGIN_LOOP(),
        //CALL_NATIVE(load_object_collision_model),
        CALL_NATIVE(bridge2_loop),
    END_LOOP(),
};

const BehaviorScript bhvGooSwitch[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(bh_red_button_collision),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
        //CALL_NATIVE(king_jelly_boss_goo_switch),
    END_LOOP(),
};

const BehaviorScript bhvSpawnJellyKJ[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_E__SG_ENEMY)),
    LOAD_ANIMATIONS(oAnimations, jelly_anims),
    ANIMATE(0),
    BEGIN_LOOP(),
        //CALL_NATIVE(king_jelly_boss_jelly),
    END_LOOP(),
};

const BehaviorScript bhvGooDrop[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        //CALL_NATIVE(king_jellyfish_goo_loop),
    END_LOOP(),
};

extern const Collision a_cage_collision[];
void a_cage_loop(void);
const BehaviorScript bhvAcage[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_ATTACHABLE_BY_ROPE)),
    LOAD_COLLISION_DATA(a_cage_collision),
    SET_FLOAT(oDrawingDistance, 9000.0f),
    SET_FLOAT(oCollisionDistance, 9000.0f),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(a_cage_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(), 
};

extern const Collision a_ufo_robot_collision[];
extern const struct Animation *const a_ufo_robot_anims[];
void a_ufo_robot_init(void);
void a_ufo_robot_loop(void);
const BehaviorScript bhvAUFORobot[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    LOAD_COLLISION_DATA(a_ufo_robot_collision),
    LOAD_ANIMATIONS(oAnimations, a_ufo_robot_anims),
    ANIMATE(0),
    CALL_NATIVE(a_ufo_robot_init),
    BEGIN_LOOP(),
        CALL_NATIVE(a_ufo_robot_loop),
    END_LOOP(),
};

void chum_bucket_cutscene_loop(void);
const BehaviorScript bhvChumBucketCutscene[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(chum_bucket_cutscene_loop),
    END_LOOP(),
};

void beat_em_up_object(void);
const BehaviorScript bhvBeatEmUpObject[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW)),
    BEGIN_LOOP(),
        CALL_NATIVE(beat_em_up_object),
    END_LOOP(),
};

extern const struct Animation *const a_ham_robot_anims[];
void ham_robot_init(void);
void ham_robot_loop(void);
const BehaviorScript bhvAHamRobot[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    LOAD_ANIMATIONS(oAnimations, a_ham_robot_anims),
    ANIMATE(0),
    CALL_NATIVE(ham_robot_init),
    BEGIN_LOOP(),
        CALL_NATIVE(ham_robot_loop),
    END_LOOP(),
};

extern const struct Animation *const a_launched_box_anims[];
void a_launched_box(void);
const BehaviorScript bhvALaunchedBox[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, a_launched_box_anims),
    ANIMATE(0),
    SCALE(0, 50),
    BEGIN_LOOP(),
        CALL_NATIVE(a_launched_box),
    END_LOOP(),
};

void a_robot_launcher_loop(void);
const BehaviorScript bhvARobotLauncher[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(a_robot_launcher_loop),
    END_LOOP(),
};

extern const struct Animation *const dog_robot_anims[];
void a_dog_robot_init(void);
void a_dog_robot_loop(void);
const BehaviorScript bhvADogRobot[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    LOAD_ANIMATIONS(oAnimations, dog_robot_anims),
    ANIMATE(0),
    CALL_NATIVE(a_dog_robot_init),
    BEGIN_LOOP(),
        CALL_NATIVE(a_dog_robot_loop),
    END_LOOP(),
};

void a_gas_cloud_loop(void);
const BehaviorScript bhvAGasCloud[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),
    BEGIN_LOOP(),
        CALL_NATIVE(a_gas_cloud_loop),
    END_LOOP(),
};

void a_chained_cage_loop(void);
const BehaviorScript bhvAChainedCage[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(a_chained_cage_loop),
    END_LOOP(),
};

/* GROUP A END */

/* GROUP B START */

const BehaviorScript bhvConcreteBlock[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_E__SG_COLLISION_BREAKABLE)),
    LOAD_COLLISION_DATA(concrete_block_collision),
    SET_FLOAT(oCollisionDistance, 1000),
    CALL_NATIVE(bhv_concrete_block_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_concrete_block_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
    BREAK(),
};



/* GROUP B END */

/* GROUP C START */

const BehaviorScript bhvFightWavesManager[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_fight_waves_manager_loop),
    END_LOOP(),
};

const BehaviorScript bhvCrane[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW)),
        CALL_NATIVE(bhv_crane_init),
    BEGIN_LOOP(),
    END_LOOP(),
};

const BehaviorScript bhvCraneHead[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_crane_head_loop),
    END_LOOP(),
};

const BehaviorScript bhvCraneArrowController[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_crane_arrow_controller_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_crane_arrow_controller_loop),
    END_LOOP(),
};

const BehaviorScript bhvCraneArrow[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_COLLISION_DATA(crane_arrow_collision),
    DROP_TO_FLOOR(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_crane_arrow_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvCraneRock[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oDrawingDistance, 9000.0f),
    CALL_NATIVE(bhv_crane_rock_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_crane_rock_loop),
    END_LOOP(),
};

const BehaviorScript bhvPaintGun[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_NO_DREAM_COMET)),
    SET_INT(oInteractType, INTERACT_GRABBABLE),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_NOT_GRABBABLE),
    SET_INT(oAnimState, 1),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_paint_gun_loop),
        SET_INT(oIntangibleTimer, 0),
    END_LOOP(),
};

const BehaviorScript bhvPaintBullet[] = {
    BEGIN(OBJ_LIST_DESTRUCTIVE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oDrawingDistance, 8000),
    SET_FLOAT(oCollisionDistance, 500),
    SET_FLOAT(oForwardVel, 70.0f),
    SET_INT(oWallHitboxRadius, 40),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_paint_bullet_loop),
    END_LOOP(),
};

const BehaviorScript bhvCamera[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BREAK(),
};

const BehaviorScript bhvOctoball[] = {
    BEGIN(OBJ_LIST_DESTRUCTIVE),
    OR_LONG(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),//--E
    DROP_TO_FLOOR(),
    SET_INT(oIntangibleTimer, 0),
    SET_FLOAT(oGraphYOffset, 85),
    SCALE(0, 85.0f),
    SET_HOME(),
    CALL_NATIVE(bhv_octoball_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_octoball_loop),
    END_LOOP(),
};

const BehaviorScript bhvPaintStain[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    DROP_TO_FLOOR(),
    SET_INT(oOpacity, 255),
    CALL_NATIVE(bhv_paint_stain_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_paint_stain_loop),
    END_LOOP(),
};

const BehaviorScript bhvLevelSplatoonTarget[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    SET_INT(oIntangibleTimer, 0),
    SET_INT(oInteractStatus, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_target_loop),
    END_LOOP(),
};

const BehaviorScript bhvTargetBox[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    LOAD_COLLISION_DATA(target_box_collision),
    SET_FLOAT(oCollisionDistance, 1000),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_breakable_box_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
    BREAK(),
};

const BehaviorScript bhvFlag[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, flag_anims),
    ANIMATE(0),
    BEGIN_LOOP(),
    END_LOOP(),
};

const BehaviorScript bhvInkMovingPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(ink_moving_platform_collision),
    SET_FLOAT(oCollisionDistance, 1000),
    SET_FLOAT(oDrawingDistance, 10000),
    SET_INT(oF4, 1),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ink_moving_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvOctozepplin[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_MOVE_XZ_USING_FVEL  |OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW)),
    SET_FLOAT(oDrawingDistance, 15000),
    SET_FLOAT(oForwardVel, 15.0f),
    SET_INT(oHealth, 50),
    SET_INT(oF4, 0),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_octozepplin_loop),
    END_LOOP(),
};

const BehaviorScript bhvJellyFish[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_INT(oBobombBuddyRole, 0),
    LOAD_ANIMATIONS(oAnimations, jelly_fish_anims),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 60),
    ANIMATE(0),
    SET_HOME(),
    CALL_NATIVE(bhv_bobomb_buddy_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_jelly_fish_loop),
    END_LOOP(),
};

/* GROUP C END */

/* GROUP D START */
const BehaviorScript bhvNitroBox[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_E__SG_CUSTOM)),
    SET_INT(oIntangibleTimer, 0),
    SET_INT(oDamageOrCoinValue, 99),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    SET_HOME(),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 150, /*Height*/ 150, /*Downwards offset*/ 0),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_bowser_bomb_loop),
        CALL_NATIVE(bhv_nitro_box_loop),
    END_LOOP(),
};
extern void bhv_nitro_boom_loop(void);
const BehaviorScript bhvNitroBoom[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_nitro_boom_loop),
    END_LOOP(),
};
extern void bhv_d_elevator(void);
const BehaviorScript bhvDelevator[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(d_elevator_collision),
    SET_FLOAT(oDrawingDistance, 16000),
    SET_FLOAT(oCollisionDistance, 1000),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_d_elevator),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};
const BehaviorScript bhvDbridge[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_seesaw_platform_init),
    LOAD_COLLISION_DATA(d_bridge_collision),
    SET_FLOAT(oDrawingDistance, 20000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_seesaw_platform_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};
/* GROUP D END */

/* GROUP E START */

//--Level

const BehaviorScript bhvE_Enemy[] = {//base enemy behavior
    BEGIN(OBJ_LIST_PUSHABLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_e__enemy),
    END_LOOP(),
};



//--Ability
const BehaviorScript bhvE_RocketBlast[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_e__rocket_blast),
    END_LOOP(),
};

const BehaviorScript bhvE_MuzzleFlash[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DELAY(1),
    DEACTIVATE(),
};
const BehaviorScript bhvE_FlattenedObj[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_e__flattened_obj),
    END_LOOP(),
};
const BehaviorScript bhvE_PushObj[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_e__push_obj),
    END_LOOP(),
};

/* GROUP E END */

/* GROUP F START */
const BehaviorScript bhvGadgetAim[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_gadget_aim),
    END_LOOP(),
};

const BehaviorScript bhvBriefcase[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 100),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        ADD_INT(oFaceAngleYaw, 0x100),
        CALL_NATIVE(bhv_hidden_star_trigger_loop),
    END_LOOP(),
};

extern void bhv_fdoor_loop(void);
const BehaviorScript bhvFdoor[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW),//--E
    LOAD_COLLISION_DATA(f_door_collision),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_fdoor_loop),
    END_LOOP(),
};

const BehaviorScript bhvKeypad[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_PERSISTENT_RESPAWN)),//--E
    BEGIN_LOOP(),
    END_LOOP(),
};

extern void bhv_ffence_loop(void);
const BehaviorScript bhvFfence[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW),//--E
    LOAD_COLLISION_DATA(f_fence_collision),
    SET_FLOAT(oDrawingDistance, 25000),
    SET_FLOAT(oCollisionDistance, 5000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ffence_loop),
    END_LOOP(),
};

extern void bhv_ftrinket_loop(void);
const BehaviorScript bhvFTrinket[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_ftrinket_loop),
    END_LOOP(),
};

extern void bhv_fblastwall_loop(void);
const BehaviorScript bhvFblastwall[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW),//--E
    LOAD_COLLISION_DATA(blastwall1_collision),
    SET_FLOAT(oDrawingDistance, 25000),
    SET_FLOAT(oCollisionDistance, 5000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_fblastwall_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern void bhv_fdynamite_loop(void);
const BehaviorScript bhvFdynamite[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    DROP_TO_FLOOR(),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_fdynamite_loop),
    END_LOOP(),
};

extern void bhv_fsg_keypad_loop(void);
const BehaviorScript bhvFSGkeypad[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_PERSISTENT_RESPAWN)),//--E
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_fsg_keypad_loop),
    END_LOOP(),
};

const BehaviorScript bhvFhidden[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_PERSISTENT_RESPAWN)),//--E
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hidden_by_uv),
    END_LOOP(),
};

extern void bhv_poof_on_watch(void);
const BehaviorScript bhvPoofOnWatch[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_poof_on_watch),
    END_LOOP(),
};

extern void bhv_gold_button_f_init(void);
const BehaviorScript bhvFRocketButtonGold[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW | OBJ_FLAG_E__SG_CUSTOM)),
    SET_INT(oIntangibleTimer, 0),
    SET_FLOAT(oDrawingDistance, 16000),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 130),
    //SET_FLOAT(oGraphYOffset, 65),
    CALL_NATIVE(bhv_gold_button_f_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_rocket_button_loop),
    END_LOOP(),
};

extern void bhv_sch_board_loop(void);
const BehaviorScript bhvF_SchBoard[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST | OBJ_FLAG_E__SG_COLLISION_BREAKABLE)),//--E
    LOAD_COLLISION_DATA(f_sch_board_collision),
    SET_FLOAT(oDrawingDistance, 25000),
    SET_FLOAT(oCollisionDistance, 5000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sch_board_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern void bhv_f_trapdoor(void);
const BehaviorScript bhvFtrapdoor[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_COLLISION_DATA(f_trapdoor_collision),
    SET_FLOAT(oDrawingDistance, 25000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_f_trapdoor),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern void bhv_f_key(void);
const BehaviorScript bhvFkey[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE|OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_f_key),
    END_LOOP(),
};

extern void bhv_f_shooter(void);
const BehaviorScript bhvFshooter[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    SET_FLOAT(oDrawingDistance, 10000),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_E__SG_ENEMY | OBJ_FLAG_NO_DREAM_COMET)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_f_shooter),
    END_LOOP(),
};

extern void bhv_f_shooter_star(void);
const BehaviorScript bhvFshooterStar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, OBJ_FLAG_NO_DREAM_COMET),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_f_shooter_star),
    END_LOOP(),
};

extern void bhv_f_keydoor(void);
const BehaviorScript bhvFKeydoor[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(f_keydoor_collision),
    LOAD_ANIMATIONS(oAnimations, keydoor_anims),
    SET_FLOAT(oDrawingDistance, 25000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_f_keydoor),
    END_LOOP(),
};

extern void bhv_f_curtainplatform(void);
const BehaviorScript bhvFCurtainPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(f_curtainplatform_collision),
    SET_FLOAT(oDrawingDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_f_curtainplatform),
    END_LOOP(),
};

extern void bhv_f_missiles(void);
const BehaviorScript bhvFMissiles[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oDrawingDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_f_missiles),
    END_LOOP(),
};

extern void bhv_f_blowvent(void);
const BehaviorScript bhvFBlowVent[] = {
    BEGIN(OBJ_LIST_LEVEL),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_f_blowvent),
    END_LOOP(),
};

extern void bhv_f_boat(void);
const BehaviorScript bhvFBoat[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_COLLISION_DATA(f_boat_collision),
    SET_FLOAT(oDrawingDistance, 32000),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_f_boat),
    END_LOOP(),
};

extern void bhv_f_heli(void);
const BehaviorScript bhvFHeli[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    SET_FLOAT(oDrawingDistance, 32000),
    LOAD_ANIMATIONS(oAnimations, f_heli_anims),
    ANIMATE(0),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_NO_DREAM_COMET)),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_f_heli),
    END_LOOP(),
};

extern void bhv_helicopter_ball_loop(void);
const BehaviorScript bhvHeliBalls[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    BILLBOARD(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 10, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_init_room),
    SET_FLOAT(oGraphYOffset, 10),
    SCALE(/*Unused*/ 0, /*Field*/ 20),
    SET_FLOAT(oDrawingDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_helicopter_ball_loop),
    END_LOOP(),
};

extern void bhv_f_laser(void);
const BehaviorScript bhvFLaser[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_f_laser),
    END_LOOP(),
};
/* GROUP F END */

/* GROUP G START */
const BehaviorScript bhvCutterBlade[] = {
    BEGIN(OBJ_LIST_DESTRUCTIVE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    SET_HOME(),
    CALL_NATIVE(bhv_cutter_blade_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_cutter_blade_loop),
    END_LOOP(),
};

/* GROUP G END */

/* GROUP H START */
const BehaviorScript bhvHLoader[] = {
    BEGIN(OBJ_LIST_SURFACE),
    SET_INT(oNumLootCoins, 5),
    // Whomp - common:
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, hloader_anims),
    LOAD_COLLISION_DATA(whomp_seg6_collision_06020A0C),
    SET_HITBOX(/*Radius*/ 200, /*Height*/ 400),//--E
    ANIMATE(WHOMP_ANIM_WALK),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 0, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_whomp_loop),
    END_LOOP(),
};

extern void bhv_hglass_loop(void);
const BehaviorScript bhvHGlass[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST | OBJ_FLAG_E__SG_COLLISION_BREAKABLE)),
    LOAD_COLLISION_DATA(hglass_collision),
    SET_FLOAT(oCollisionDistance, 3000),
    SET_FLOAT(oDrawingDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hglass_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
    BREAK(),
};
/* GROUP H END */

/* GROUP I START */
const BehaviorScript bhvShockRocket[] = {
    BEGIN(OBJ_LIST_DESTRUCTIVE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO |OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW)),
    SCALE(/*Unused*/ 0, /*Field*/ 20),
    SET_INT(oWallHitboxRadius, 40),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_shock_rocket_loop),
    END_LOOP(),
};

const BehaviorScript bhvRocketSmoke[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_FLOAT(oGraphYOffset, -5),
    BILLBOARD(),
    CALL_NATIVE(bhv_rocket_smoke_init),
    SET_INT(oAnimState, OBJ_ANIM_STATE_INIT_ANIM),
    BEGIN_REPEAT(3),
        ADD_INT(oAnimState, 1),
    END_REPEAT(),
    DEACTIVATE(),
};

const BehaviorScript bhvRocketButton[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW | OBJ_FLAG_E__SG_CUSTOM)),
    SET_INT(oIntangibleTimer, 0),
    SET_FLOAT(oDrawingDistance, 16000),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 130),
    SET_FLOAT(oGraphYOffset, 65),
    CALL_NATIVE(bhv_rocket_button_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_rocket_button_loop),
    END_LOOP(),
};

const BehaviorScript bhvRocketButtonGroup[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_rocket_button_group_loop),
    END_LOOP(),
};

const BehaviorScript bhvHoodmonger[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW | OBJ_FLAG_E__SG_ENEMY)),
    LOAD_ANIMATIONS(oAnimations, hoodmonger_anims),
    SET_FLOAT(oDrawingDistance, 6000),
    SET_INT(oDamageOrCoinValue, 2),
    SET_INT(oHealth, 1),
    SET_INT(oNumLootCoins, 3),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    ANIMATE(0),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 210),
    CALL_NATIVE(bhv_hoodmonger_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hoodmonger_loop),
        SET_INT(oIntangibleTimer, 0),
        SET_INT(oInteractStatus, 0),
    END_LOOP(),
};


const BehaviorScript bhvHoodmongerAlertManager[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hoodmonger_alert_manager_loop),
    END_LOOP(),
};

const BehaviorScript bhvHoodmongerBullet[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oDrawingDistance, 8000),
    SET_FLOAT(oCollisionDistance, 500),
    SET_FLOAT(oForwardVel, 25.0f),
    SET_FLOAT(oGraphYOffset, 40),
    SET_INT(oDamageOrCoinValue, 2),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    SET_INT(oWallHitboxRadius, 40),
    SET_HITBOX(/*Radius*/ 45, /*Height*/ 80),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hoodmonger_bullet_loop),
        SET_INT(oIntangibleTimer, 0),
        SET_INT(oInteractStatus, 0),
    END_LOOP(),
};

const BehaviorScript bhvBlackLums[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SCALE(0, 40),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_blacklums_update),
    END_LOOP(),
};

const BehaviorScript bhvDollar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oDrawingDistance, 8000),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_dollar_loop),
    END_LOOP(),
};

const BehaviorScript bhvHoodboomer[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW | OBJ_FLAG_E__SG_ENEMY)),
    LOAD_ANIMATIONS(oAnimations, hoodboomer_anims),
    SET_FLOAT(oDrawingDistance, 6000),
    SET_INT(oDamageOrCoinValue, 3),
    SET_INT(oHealth, 1),
    SET_INT(oNumLootCoins, -1),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    ANIMATE(0),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 210),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hoodboomer_loop),
        SET_INT(oIntangibleTimer, 0),
        SET_INT(oInteractStatus, 0),
    END_LOOP(),
};

const BehaviorScript bhvHoodboomerBomb[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    SET_HITBOX(80, 50),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    SET_INT(oDamageOrCoinValue, 4),
    CALL_NATIVE(bhv_hoodboomer_bomb_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hoodboomer_bomb_loop),
        CALL_NATIVE(bhv_three_axis_rotative_object),
        SET_INT(oIntangibleTimer, 0),
        SET_INT(oInteractStatus, 0),
    END_LOOP(),
};

const BehaviorScript bhvBlackSmokeHoodboomer[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_FLOAT(oGraphYOffset, 50),
    SET_INT(oOpacity, 255),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_black_smoke_hoodboomer_loop),
    END_LOOP(),
};

const BehaviorScript bhvPigpot[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_E__SG_CUSTOM)),
    DROP_TO_FLOOR(),
    SET_INT(oNumLootCoins, 3),
    SET_INT(oInteractType, INTERACT_GRABBABLE),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_NOT_GRABBABLE),
    SET_HITBOX(/*Radius*/ 60, /*Height*/ 100),
    SET_INT(oIntangibleTimer, 0),
    SET_FLOAT(oDeathSound, SOUND_GENERAL_BREAK_BOX),
    SCALE(0, 120),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_pigpot_loop),
    END_LOOP(),
};

const BehaviorScript bhvRotatingGearDecorative[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_rotating_gear_decorative_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_rotating_gear_decorative_loop),
    END_LOOP(),
};

const BehaviorScript bhvGrillOpenableByRocketButton[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_COLLISION_DATA(i_gate_collision),
    SET_FLOAT(oCollisionDistance, 500),
    SET_FLOAT(oDrawingDistance, 10000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_grill_openable_by_rocket_button_loop),
        CALL_NATIVE(load_object_collision_model),
        SET_INT(oIntangibleTimer, 0),
    END_LOOP(),
};

const BehaviorScript bhvWoodenLever[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DROP_TO_FLOOR(),
    SET_INT(oIntangibleTimer, 0),
    SET_INT(oInteractType, INTERACT_GRABBABLE),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_NOT_GRABBABLE),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 110),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_wooden_lever_loop),
        SET_INT(oInteractStatus, INT_STATUS_NONE),
    END_LOOP(),
};

const BehaviorScript bhvPlum[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_INT(oInteractType, INTERACT_GRABBABLE),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 100),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 100, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_INT(oIntangibleTimer, 0),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_plum_loop),
    END_LOOP(),
};

const BehaviorScript bhvPlumBucket[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_HITBOX(/*Radius*/ 200, /*Height*/ 200),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_plum_bucket_loop),
    END_LOOP(),
};

const BehaviorScript bhvCagedToad[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_NO_DREAM_COMET)),
    SET_HITBOX(/*Radius*/ 120, /*Height*/ 200),
    SET_INT(oIntangibleTimer, 0),
    SET_FLOAT(oDrawingDistance, 8000),
    SET_FLOAT(oGraphYOffset, 60),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_caged_toad_loop),
    END_LOOP(),
};

const BehaviorScript bhvFallingToad[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 100, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    GOTO(bhvToadMessage + 1),
};

const BehaviorScript bhvHiddenCagedToadsStar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    CALL_NATIVE(bhv_caged_toad_star_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bhv_caged_toad_star_loop),
    END_LOOP(),
};

const BehaviorScript bhvPlankAttachedToRope[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_ATTACHABLE_BY_ROPE | OBJ_FLAG_DONT_CALC_COLL_DIST)),
    SET_FLOAT(oCollisionDistance, 6000),
    SET_FLOAT(oDrawingDistance, 6000),
    SET_FLOAT(oGravity, 2),
    SET_FLOAT(oBounciness, -50),
    LOAD_COLLISION_DATA(plank_rope_collision),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_plank_attached_to_rope_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvBarrierAttachedToRope[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_ATTACHABLE_BY_ROPE)),
    LOAD_COLLISION_DATA(barrier_rope_collision),
    SET_FLOAT(oCollisionDistance, 4000),
    SET_FLOAT(oDrawingDistance, 7000),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 100, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_barrier_attached_to_rope_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvFunkyShell[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_funky_shell_loop),
    END_LOOP(),
};

const BehaviorScript bhvSkrinkingBlackDoorSpawner[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_skrinking_black_door_spawner),
    END_LOOP(),
};

const BehaviorScript bhvSkrinkingBlackDoor[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    SET_FLOAT(oDrawingDistance, 6000),
    SET_FLOAT(oFloatF4, 1.0f),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_skrinking_black_door),
    END_LOOP(),
};

const BehaviorScript bhvRotatingFunkyPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    LOAD_COLLISION_DATA(funky_road_collision),
    SET_FLOAT(oDrawingDistance, 5000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_rotating_funky_platform),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvMovingFunkyPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    LOAD_COLLISION_DATA(funky_road_collision),
    SET_FLOAT(oDrawingDistance, 5000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_moving_funky_platform),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvThreeAxisRotativeObject[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    SET_FLOAT(oDrawingDistance, 16000),
     BEGIN_LOOP(),
        CALL_NATIVE(bhv_three_axis_rotative_object),
    END_LOOP(),
};

const BehaviorScript bhvOpeningWall[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(opening_wall_collision),
    SET_FLOAT(oDrawingDistance, 5000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_opening_wall_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvMasterKaag[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),//--E
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    LOAD_ANIMATIONS(oAnimations, master_kaag_anims),
    SET_INT(oIntangibleTimer, 0),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    SET_HITBOX(/*Radius*/ 300, /*Height*/ 300),
    SET_HOME(),
    DROP_TO_FLOOR(),
    ANIMATE(0),
    SCALE(0, 150),
    SET_INT(oHealth, 3),
    SET_INT(oDamageOrCoinValue, 3),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_master_kaag_loop),
        SET_INT(oInteractStatus, 0),
    END_LOOP(),
};

const BehaviorScript bhvMasterKaagWeakPoint[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 180),
    SET_INT(oIntangibleTimer, 0),
    SET_FLOAT(oGraphYOffset, 65),
    BEGIN_LOOP(),
        SET_INT(oInteractStatus, 0),
    END_LOOP(),
};

const BehaviorScript bhvHoodooSorcerer[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW | OBJ_FLAG_E__SG_ENEMY)),
    LOAD_ANIMATIONS(oAnimations, hoodoo_sorcerer_anims),
    SET_FLOAT(oDrawingDistance, 8000),
    SET_INT(oDamageOrCoinValue, 1),
    SET_INT(oHealth, 1),
    SET_INT(oNumLootCoins, 3),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    DROP_TO_FLOOR(),
    ANIMATE(0),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 400),
    CALL_NATIVE(bhv_hoodoo_sorcerer_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hoodoo_sorcerer_loop),
        SET_INT(oIntangibleTimer, 0),
        SET_INT(oInteractStatus, 0),
    END_LOOP(),
};

const BehaviorScript bhvLevelIBossDoor[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW)),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 100, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    LOAD_COLLISION_DATA(boss_gate_collision),
    SET_FLOAT(oDrawingDistance, 16000),
    SET_HITBOX(10, 10),
    //DROP_TO_FLOOR(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_level_I_boss_door_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvLevelIBossDoorStarSlot[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW)),
    SET_FLOAT(oDrawingDistance, 16000),
    BEGIN_LOOP(),
    END_LOOP(),
};

const BehaviorScript bhvBountyHunterToad[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_ANIMATIONS(oAnimations, toad_seg6_anims_0600FB58),
    ANIMATE(TOAD_ANIM_WEST_WAVING_BOTH_ARMS),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 100),
    SET_INT(oIntangibleTimer, 0),
    SET_FLOAT(oDrawingDistance, 32000),
    CALL_NATIVE(bhv_init_room),
    CALL_NATIVE(bhv_bounty_hunter_toad_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_bounty_hunter_toad_loop),
    END_LOOP(),
};

const BehaviorScript bhvLevelIStartToad[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_level_I_start_toad_init),
    GOTO(bhvToadMessage + 1),
};

/* GROUP I END */

/* GROUP J START */
const BehaviorScript bhvDragonite[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW | OBJ_FLAG_PERSISTENT_RESPAWN)),
    LOAD_ANIMATIONS(oAnimations, dragonite_anims),
    SET_FLOAT(oDrawingDistance, 32000),
    CALL_NATIVE(bhv_dragonite_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_dragonite_loop),
    END_LOOP(),
};

const BehaviorScript bhvFallingPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW)),
    LOAD_COLLISION_DATA(falling_platform_collision),
    SET_FLOAT(oCollisionDistance, 2000),
    SET_FLOAT(oDrawingDistance, 32000),
    CALL_NATIVE(bhv_falling_platform_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_falling_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};


const BehaviorScript bhvTiltyHexagon[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(tilty_hexagon_collision),
    SET_HOME(),
    CALL_NATIVE(bhv_platform_normals_init),
    SET_FLOAT(oDrawingDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_tilting_inverted_pyramid_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvSkarmory[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    LOAD_ANIMATIONS(oAnimations, skarmory_anims),
    SET_FLOAT(oDrawingDistance, 20000),
    CALL_NATIVE(bhv_skarmory_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_skarmory_loop),
    END_LOOP(),
};

const BehaviorScript bhvSkarmoryStarSpawner[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_skarmory_star_spawner_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_skarmory_star_spawner_loop),
    END_LOOP(),
};

const BehaviorScript bhvYoungster[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, youngster_anims),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 60),
    ANIMATE(0),
    SET_HOME(),
    CALL_NATIVE(bhv_youngster_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_npc_loop),
    END_LOOP(),
};

const BehaviorScript bhvSpinarak[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE | OBJ_FLAG_E__SG_ENEMY)),
    LOAD_ANIMATIONS(oAnimations, spinarak_anims),
    ANIMATE(0),
    SET_HOME(),
    CALL_NATIVE(bhv_spinarak_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_spinarak_loop),
    END_LOOP(),
};

const BehaviorScript bhvGeodude[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW)),
    LOAD_ANIMATIONS(oAnimations, geodude_anims),
    SET_HOME(),
    CALL_NATIVE(bhv_geodude_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_geodude_loop),
    END_LOOP(),
};

const BehaviorScript bhvGeodudePunchHitbox[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_geodude_punch_hitbox_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_geodude_punch_hitbox_loop),
    END_LOOP(),
};

const BehaviorScript bhvBerry[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    DROP_TO_FLOOR(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 0, /*Friction*/ 0, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    SET_INT(oInteractType, INTERACT_GRABBABLE),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_HOLDABLE_NPC),
    SET_INT(oIntangibleTimer, 0),
    SET_HITBOX(/*Radius*/ 40, /*Height*/ 40),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_berry_loop),
    END_LOOP(),
};

const BehaviorScript bhvHooh[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_ANIMATIONS(oAnimations, hooh_anims),
    SET_HOME(),
    SET_FLOAT(oDrawingDistance, 32000),
    CALL_NATIVE(bhv_hooh_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hooh_loop),
    END_LOOP(),
};

const BehaviorScript bhvHoohFlame[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_HOME(),
    SCALE(/*Unused*/ 0, /*Field*/ 700),
    SET_INTERACT_TYPE(INTERACT_FLAME),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 50, /*Height*/ 25, /*Downwards offset*/ 25),
    SET_INT(oIntangibleTimer, 0),
    CALL_NATIVE(bhv_hooh_flame_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hooh_flame_loop),
        SET_INT(oInteractStatus, INT_STATUS_NONE),
        ANIMATE_TEXTURE(oAnimState, 2),
    END_LOOP(),
};

const BehaviorScript bhvHoohRock[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 100, /*Height*/ 100, /*Downwards offset*/ 0),
    SET_INT(oIntangibleTimer, 0),
    SET_INT(oDamageOrCoinValue, 2),
    CALL_NATIVE(bhv_hooh_rock_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hooh_rock_loop),
        SET_INT(oInteractStatus, INT_STATUS_NONE),
    END_LOOP(),   
};

const BehaviorScript bhvHoohFlame2[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BILLBOARD(),
    SET_HOME(),
    SCALE(/*Unused*/ 0, /*Field*/ 700),
    SET_INTERACT_TYPE(INTERACT_FLAME),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 50, /*Height*/ 25, /*Downwards offset*/ 25),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hooh_flame2_loop),
        SET_INT(oInteractStatus, INT_STATUS_NONE),
        ANIMATE_TEXTURE(oAnimState, 2),
    END_LOOP(),
};

const BehaviorScript bhvMiltank[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_LONG(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_NO_DREAM_COMET)),
    CALL_NATIVE(bhv_miltank_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_miltank_loop),
    END_LOOP(),
};

const BehaviorScript bhvMiltankStar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_miltank_star_loop),
    END_LOOP(),
};

const BehaviorScript bhvHaunter[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    // Boo - common:
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),//--E
    SET_INT(oIntangibleTimer, 0),
    SET_HOME(),
    SET_INT(oDamageOrCoinValue, 2),
    LOAD_ANIMATIONS(oAnimations, haunter_anims),
    ANIMATE(0),
    SET_HITBOX(/*Radius*/ 140, /*Height*/ 80),
    SET_HURTBOX(/*Radius*/ 40, /*Height*/ 60),
    SET_FLOAT(oGraphYOffset, 30),
    CALL_NATIVE(bhv_init_room),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_boo_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_boo_loop),
    END_LOOP(),
};

const BehaviorScript bhvGengar[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    // Big boo - common:
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),//--E
    SET_HOME(),
    LOAD_ANIMATIONS(oAnimations, gengar_anims),
    ANIMATE(0),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ 0, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 200, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_init_room),
    CALL_NATIVE(bhv_boo_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_big_boo_loop),
    END_LOOP(),
};

const BehaviorScript bhvElder[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_ANIMATIONS(oAnimations, elder_anims),
    DROP_TO_FLOOR(),
    ANIMATE(0),
    SET_HOME(),
    CALL_NATIVE(bhv_elder_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_npc_loop),
    END_LOOP(),
};

const BehaviorScript bhvKimonoGirl[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_ANIMATIONS(oAnimations, elder_anims),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 60),
    ANIMATE(0),
    SET_HOME(),
    CALL_NATIVE(bhv_npc_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_npc_loop),
    END_LOOP(),
};

const BehaviorScript bhvMorty[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_ANIMATIONS(oAnimations, morty_anims),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 60),
    ANIMATE(0),
    SET_FLOAT(oDrawingDistance, 32000),
    SET_HOME(),
    CALL_NATIVE(bhv_npc_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_npc_loop),
    END_LOOP(),
};

const BehaviorScript bhvSentret[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_E__SG_ENEMY)),
    LOAD_ANIMATIONS(oAnimations, sentret_anims),
    SET_HOME(),
    CALL_NATIVE(bhv_sentret_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sentret_loop),
    END_LOOP(),
};

const BehaviorScript bhvSkiploom[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    LOAD_ANIMATIONS(oAnimations, skiploom_anims),
    ANIMATE(0),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 50, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 1000, /*Buoyancy*/ 600, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_init_room),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_TWIRL_BOUNCE),
    SET_FLOAT(oGraphYOffset, 30),
    SCALE(/*Unused*/ 0, /*Field*/ 150),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_fly_guy_update),
    END_LOOP(),
};

const BehaviorScript bhvGravelerRamp[] = {
    BEGIN(OBJ_LIST_SPAWNER),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_graveler_ramp_loop),
    END_LOOP(),
};

const BehaviorScript bhvOldMan[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, old_man_anims),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 60),
    ANIMATE(0),
    SET_HOME(),
    CALL_NATIVE(bhv_npc_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_npc_loop),
    END_LOOP(),
};

const BehaviorScript bhvSnorlax[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    LOAD_ANIMATIONS(oAnimations, snorlax_anims),
    SET_INTERACT_TYPE(INTERACT_IGLOO_BARRIER),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 200, /*Height*/ 200),
    ANIMATE(0),
    CALL_NATIVE(bhv_snorlax_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_snorlax_loop),
    END_LOOP(),
};

const BehaviorScript bhvMagikarp[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE |  OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW)),
    LOAD_ANIMATIONS(oAnimations, magikarp_anims),
    ANIMATE(0),
    SET_HOME(),
    CALL_NATIVE(bhv_magikarp_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_magikarp_loop),
    END_LOOP(),
};

/* GROUP J END */

/* GROUP K START */
extern void bhv_k_fan(void);
const BehaviorScript bhvKfan[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(k_fan_collision),
    SET_FLOAT(oDrawingDistance, 32000),
    SET_FLOAT(oCollisionDistance, 500),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_k_fan),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern void bhv_k_blood(void);
const BehaviorScript bhvKblood[] = {
    SET_FLOAT(oDrawingDistance, 32000),
    SET_FLOAT(oCollisionDistance, 500),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_k_blood),
    END_LOOP(),
};

void bhv_dancer(void);
const BehaviorScript bhvKdancer[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, kdancer_anims),
    ANIMATE(0),
    SET_HOME(),
    SET_FLOAT(oGraphYOffset, -25),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_dancer),
    END_LOOP(),
};

const BehaviorScript bhvKDisco[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        ADD_INT(oFaceAngleYaw, 0x200),
    END_LOOP(),
};

extern void bhv_k_bartender(void);
const BehaviorScript bhvKbartender[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, k_bartender_anims),
    ANIMATE(0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_k_bartender),
    END_LOOP(),
};

extern void bhv_k_strong_terry(void);
const BehaviorScript bhvStrongTerry[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    LOAD_ANIMATIONS(oAnimations, humanoid_anims),
    ANIMATE(1),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_k_strong_terry),
    END_LOOP(),
};

extern void bhv_k_skinny_ricky(void);
const BehaviorScript bhvSkinnyRicky[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    LOAD_ANIMATIONS(oAnimations, humanoid_anims),
    ANIMATE(1),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_k_skinny_ricky),
    END_LOOP(),
};

extern void bhv_k_shieldo(void);
const BehaviorScript bhvShieldo[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    LOAD_ANIMATIONS(oAnimations, humanoid_anims),
    ANIMATE(1),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_k_shieldo),
    END_LOOP(),
};

extern void bhv_k_electrohead(void);
const BehaviorScript bhvElectrohead[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_ANIMATIONS(oAnimations, humanoid_anims),
    ANIMATE(1),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_k_electrohead),
    END_LOOP(),
};

extern void bhv_k_billionare(void);
const BehaviorScript bhvKbillionare[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_ANIMATIONS(oAnimations, humanoid_anims),
    ANIMATE(1),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_k_billionare),
    END_LOOP(),
};

extern void bhv_k_tv(void);
const BehaviorScript bhvKtv[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_NO_DREAM_COMET),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_k_tv),
    END_LOOP(),
};

extern void bhv_k_tv_aim(void);
const BehaviorScript bhvKtvAim[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_k_tv_aim),
    END_LOOP(),
};

extern void bhv_k_pounder(void);
const BehaviorScript bhvKpounder[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(k_pounder_collision),
    SET_FLOAT(oDrawingDistance, 32000),
    SET_FLOAT(oCollisionDistance, 3000),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_k_pounder),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};
/* GROUP K END */

/* GROUP L START */
const BehaviorScript bhvPtMetalBox[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(pt_mb_collision),
    SET_FLOAT(oDrawingDistance, 16000),
    SET_FLOAT(oCollisionDistance, 500),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_pt_mb),
    END_LOOP(),
};

extern void bhv_l_door_loop(void);
const BehaviorScript bhvLDoor[] = {
    BEGIN(OBJ_LIST_SURFACE),
    SET_INT(oInteractType, INTERACT_WARP_DOOR),
    // Door - common:
    OR_INT(oFlags, (OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, door_seg3_anims_030156C0),
    ANIMATE(DOOR_ANIM_CLOSED),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 100),
    SET_INT(oIntangibleTimer, 0),
    SET_FLOAT(oCollisionDistance, 1000),
    SET_HOME(),
    CALL_NATIVE(bhv_door_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_l_door_loop),
    END_LOOP(),
};

extern void bhv_l_pillar(void);
const BehaviorScript bhvL_JohnPillar[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_LONG(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_NO_DREAM_COMET),
    SET_HITBOX(/*Radius*/ 212, /*Height*/ 1000),
    LOAD_ANIMATIONS(oAnimations, johnp_anims),
    ANIMATE(0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_l_pillar),
    END_LOOP(),
};

extern void bhv_l_johnblock(void);
const BehaviorScript bhvJohnBlock[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(johnblock_collision),
    SET_FLOAT(oDrawingDistance, 16000),
    SET_FLOAT(oCollisionDistance, 500),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_NO_DREAM_COMET)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_l_johnblock),
    END_LOOP(),
};

extern void bhv_escape_collect_star_loop(void);
const BehaviorScript bhvL_EscapeStar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_init_room),
    CALL_NATIVE(bhv_collect_star_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_escape_collect_star_loop),
    END_LOOP(),
};

const BehaviorScript bhvL_Cheeseslime[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY | OBJ_FLAG_ATTACHABLE_BY_ROPE)),//--E
    DROP_TO_FLOOR(),
    LOAD_ANIMATIONS(oAnimations, cheeseslime_anims),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 40, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_goomba_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_goomba_update),
    END_LOOP(),
};

extern void bhv_npc_pepperman_loop(void);
const BehaviorScript bhvL_PeppermanNPC[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_ANIMATIONS(oAnimations, pepperman_anims),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 60),
    ANIMATE(0),
    SET_HOME(),
    CALL_NATIVE(bhv_npc_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_npc_pepperman_loop),
    END_LOOP(),
};

extern void bhv_boss_pepperman_loop(void);
const BehaviorScript bhvL_PeppermanBoss[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_NO_DREAM_COMET)),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 100, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 500, /*Friction*/ 500, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    LOAD_ANIMATIONS(oAnimations, pepperman_anims),
    DROP_TO_FLOOR(),
    ANIMATE(0),
    SET_HOME(),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_boss_pepperman_loop),
    END_LOOP(),
};

extern void bhv_boss_pepperman_statue(void);
const BehaviorScript bhvL_PeppermanStatue[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 100, /*Gravity*/ -400, /*Bounciness*/ -50, /*Drag strength*/ 500, /*Friction*/ 500, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_boss_pepperman_statue),
    END_LOOP(),
};

extern void bhv_l_clock(void);
const BehaviorScript bhvLclock[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 100),
    LOAD_ANIMATIONS(oAnimations, lclock_anims),
    ANIMATE(0),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_l_clock),
    END_LOOP(),
};

extern void bhv_pizza_portal_loop(void);
const BehaviorScript bhvL_PizzaPortal[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_INT(oInteractType, INTERACT_WARP),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_pizza_portal_loop),
    END_LOOP(),
};
/* GROUP L END */

/* GROUP M START */
extern void bhv_m_boss_elevator(void);
const BehaviorScript bhvM_BossElevator[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_COLLISION_DATA(m_bossplatform_collision),
    SET_FLOAT(oCollisionDistance, 4000),
    SET_FLOAT(oDrawingDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_m_boss_elevator),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern void bhv_m_classc(void);
const BehaviorScript bhvM_ClassC[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_NO_DREAM_COMET)),
    SET_FLOAT(oDrawingDistance, 32000),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_m_classc),
    END_LOOP(),
};

extern void bhv_m_gate(void);
const BehaviorScript bhvM_Gate[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_COLLISION_DATA(m_gate_collision),
    SET_FLOAT(oCollisionDistance, 4000),
    SET_FLOAT(oDrawingDistance, 32000),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_m_gate),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern void goliath_jelly_boss_loop(void);
const BehaviorScript bhvM_Jelly[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_NO_DREAM_COMET)),
    SCALE(0, 400),
    ANIMATE(0),
    LOAD_ANIMATIONS(oAnimations, m_jelly_anims),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(goliath_jelly_boss_loop),
    END_LOOP(),
};

extern void bhv_m_elevator(void);
const BehaviorScript bhvMelevator[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_COLLISION_DATA(m_elevator_collision),
    SET_FLOAT(oCollisionDistance, 4000),
    SET_FLOAT(oDrawingDistance, 32000),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_m_elevator),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern void bhv_m_jelly_laser_loop(void);
const BehaviorScript bhvM_JellyLaser[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_m_jelly_laser_loop),
    END_LOOP(),
};
/* GROUP M END */

/* GROUP N START */
const BehaviorScript bhvPhysicsMarble[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    CALL_NATIVE(bhv_marble_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_marble_loop),
    END_LOOP(),
};
extern void bhv_marble_cannon_loop(void);
const BehaviorScript bhvMarbleCannon[] = {
    CALL_NATIVE(bhv_marble_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_marble_cannon_loop),
    END_LOOP(),
};
/* GROUP N END */

/* GROUP O START */
extern void bhv_red_arrow(void);
const BehaviorScript bhvRedArrow[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_red_arrow),
    END_LOOP(),
};

extern void bhv_o_walker_update(void);
const BehaviorScript bhvOZombie[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    DROP_TO_FLOOR(),
    LOAD_ANIMATIONS(oAnimations, o_zombie_anims),
    ANIMATE(0),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 40, /*Gravity*/ -400, /*Bounciness*/ -1, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 130),
    SET_FLOAT(oDrawingDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_o_walker_update),
    END_LOOP(),
};

extern void bhv_zambie_spawner(void);
const BehaviorScript bhvOZombieSpawner[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_COMPUTE_DIST_TO_MARIO),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_zambie_spawner),
    END_LOOP(),
};

extern void bhv_o_tree_init(void);
const BehaviorScript bhvOTree[] = {
    BEGIN(OBJ_LIST_POLELIKE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_OPACITY_FROM_CAMERA_DIST)),
    SET_INT(oInteractType, INTERACT_POLE),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 500),
    SET_INT(oIntangibleTimer, 0),
    SET_FLOAT(oDrawingDistance, 32000),
    CALL_NATIVE(bhv_o_tree_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_pole_base_loop),
    END_LOOP(),
};

const BehaviorScript bhvOuvstar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_NO_DREAM_COMET),
    SET_HITBOX(/*Radius*/ 150, /*Height*/ 100),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        ADD_INT(oFaceAngleYaw, 0x200),
        CALL_NATIVE(bhv_hidden_star_trigger_loop),
        CALL_NATIVE(bhv_hidden_by_uv),
    END_LOOP(),
};

extern void bhv_o_lift(void);
const BehaviorScript bhvOlift[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(o_lift_collision),
    SET_FLOAT(oDrawingDistance, 16000),
    SET_FLOAT(oCollisionDistance, 800),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_o_lift),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern void bhv_o_garage(void);
const BehaviorScript bhvOgarage[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(o_garage_collision),
    SET_FLOAT(oDrawingDistance, 32000),
    SET_FLOAT(oCollisionDistance, 800),
    SET_HOME(),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_ATTACHABLE_BY_ROPE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_o_garage),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern void bhv_o_speaker(void);
const BehaviorScript bhvOspeaker[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_LONG(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_NO_DREAM_COMET),
    SET_HITBOX(/*Radius*/ 200, /*Height*/ 200),
    SET_FLOAT(oGraphYOffset, 100),
    SET_INT(oIntangibleTimer, 0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_o_speaker),
    END_LOOP(),
};

extern void bhv_o_easystreet_mission_controller(void);
const BehaviorScript bhvOeasystreetcontroller[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_NO_DREAM_COMET)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_o_easystreet_mission_controller),
    END_LOOP(),
};

extern void bhv_o_gerik(void);
const BehaviorScript bhvO_Gerik[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM | OBJ_FLAG_NO_DREAM_COMET)),
    LOAD_ANIMATIONS(oAnimations, humanoid_anims),
    ANIMATE(0),
    SET_HOME(),
    SCALE(/*Unused*/ 0, /*Field*/ 250),
    SET_HITBOX(/*Radius*/ 500, /*Height*/ 300),
    SET_FLOAT(oDrawingDistance, 30000),
    SET_INTERACT_TYPE(INTERACT_NONE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_o_gerik),
    END_LOOP(),
};

/* Group O; Secret Boss */

extern void bhv_sb_torch(void);
const BehaviorScript bhvSbTorch[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sb_torch),
    END_LOOP(),
};

extern void bhv_sb_actor(void);
const BehaviorScript bhvSbGaster[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    LOAD_ANIMATIONS(oAnimations, sb_humanoid_anims),
    ANIMATE(0),
    SET_HOME(),
    SET_FLOAT(oDrawingDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sb_actor),
    END_LOOP(),
};

const BehaviorScript bhvSbYukari[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    LOAD_ANIMATIONS(oAnimations, sb_humanoid_anims),
    ANIMATE(0),
    SET_HOME(),
    SET_FLOAT(oDrawingDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sb_actor),
    END_LOOP(),
};

void bhv_sb_gap(void);
const BehaviorScript bhvSbGap[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_HOME(),
    SET_FLOAT(oDrawingDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sb_gap),
    END_LOOP(),
};

extern void bhv_sb_manager(void);
const BehaviorScript bhvSbManager[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    LOAD_ANIMATIONS(oAnimations, humanoid_anims),
    ANIMATE(1),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sb_manager),
    END_LOOP(),
};

extern void bhv_sb_train(void);
const BehaviorScript bhvSbTrain[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(sb_train_collision),
    SET_FLOAT(oDrawingDistance, 32000),
    SET_FLOAT(oCollisionDistance, 8000),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_DONT_CALC_COLL_DIST)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sb_train),
    END_LOOP(),
};

extern void bhv_sb_blaster(void);
const BehaviorScript bhvSbBlaster[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, sb_blaster_anims),
    ANIMATE(0),
    SET_HOME(),
    SET_FLOAT(oDrawingDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sb_blaster),
    END_LOOP(),
};


extern void bhv_sb_blast(void);
const BehaviorScript bhvSbBlast[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oDrawingDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sb_blast),
    END_LOOP(),
};

/* GROUP O END */

const BehaviorScript bhvCutterBlast[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oDrawingDistance, 20000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_cutter_blast_loop),
    END_LOOP(),
};

const BehaviorScript bhvSlashParticle[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_slash_particle_loop),
    END_LOOP(),
};

const BehaviorScript bhvSirKibble[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_E__SG_CUSTOM)),
    LOAD_ANIMATIONS(oAnimations, sir_kibble_anims),
    SET_FLOAT(oDrawingDistance, 16000),
    CALL_NATIVE(bhv_sir_kibble_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_sir_kibble_loop),
    END_LOOP(),
};

const BehaviorScript bhvStarProjectile[] = {
    BEGIN(OBJ_LIST_DESTRUCTIVE),
    OR_LONG(oFlags, (OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    DROP_TO_FLOOR(),
    SET_HOME(),
    CALL_NATIVE(bhv_star_projectile_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_star_projectile_loop),
    END_LOOP(),
};
const BehaviorScript bhvLevelGCutscenes[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_level_g_cutscenes_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_level_g_cutscenes_loop),
    END_LOOP(),
};

const BehaviorScript bhvStarDrop[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_star_drop_init),
    SET_FLOAT(oDrawingDistance, 16000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_star_drop_loop),
    END_LOOP(),
};

const BehaviorScript bhvGAttachedRope[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_g_attached_rope_init),
    SET_FLOAT(oDrawingDistance, 16000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_attached_rope_loop),
    END_LOOP(),
};

const BehaviorScript bhvGAttachedBlock[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST | OBJ_FLAG_ATTACHABLE_BY_ROPE)),
    LOAD_COLLISION_DATA(g_fixed_block_collision),
    SET_FLOAT(oCollisionDistance, 2000),
    CALL_NATIVE(bhv_g_attached_block_init),
    SET_FLOAT(oDrawingDistance, 16000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_attached_block_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvStarDoorStar[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_star_door_star_init),
    SET_FLOAT(oDrawingDistance, 16000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_star_door_star_loop),
    END_LOOP(),
};

const BehaviorScript bhvGStarDoor[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_g_star_door_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_star_door_loop),
    END_LOOP(),
};

const BehaviorScript bhvGSpring[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_ATTACHABLE_BY_ROPE)),
    LOAD_COLLISION_DATA(g_spring_collision),
    SET_FLOAT(oDrawingDistance, 16000),
    CALL_NATIVE(bhv_g_spring_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_spring_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvGCutRock[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_ATTACHABLE_BY_ROPE)),
    LOAD_COLLISION_DATA(g_cut_rock_collision),
    SET_FLOAT(oDrawingDistance, 16000),
    CALL_NATIVE(bhv_g_cut_rock_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_cut_rock_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvGCannon[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    LOAD_COLLISION_DATA(g_cannon_collision),
    SET_FLOAT(oDrawingDistance, 16000),
    CALL_NATIVE(bhv_g_cannon_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_cannon_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvGreatCaveOffensiveController[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_great_cave_offensive_controller_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_great_cave_offensive_controller_loop),
    END_LOOP(),
};

const BehaviorScript bhvGMarx[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_E__SG_BOSS | OBJ_FLAG_PERSISTENT_RESPAWN | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_ACTIVE_FROM_AFAR)),
    LOAD_ANIMATIONS(oAnimations, marx_anims),
    CALL_NATIVE(bhv_g_marx_init),
    SET_FLOAT(oDrawingDistance, 16000),
    ANIMATE(0),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_marx_loop),
    END_LOOP(),
};

const BehaviorScript bhvGMarxCutter[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_g_marx_cutter_init),
    SET_FLOAT(oDrawingDistance, 16000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_marx_cutter_loop),
    END_LOOP(),
};

const BehaviorScript bhvGMarxSeed[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    CALL_NATIVE(bhv_g_marx_seed_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_marx_seed_loop),
    END_LOOP(),
};

const BehaviorScript bhvGMarxVine[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    CALL_NATIVE(bhv_g_marx_vine_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_marx_vine_loop),
    END_LOOP(),
};

const BehaviorScript bhvGMarxThornSegment[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    SET_FLOAT(oDrawingDistance, 16000),
    CALL_NATIVE(bhv_g_marx_thorn_segment_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_marx_thorn_segment_loop),
    END_LOOP(),
};

const BehaviorScript bhvGMarxHalf[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oDrawingDistance, 16000),
    CALL_NATIVE(bhv_g_marx_half_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_marx_half_loop),
    END_LOOP(),
};

const BehaviorScript bhvGMarxBlackHole[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    BILLBOARD(),
    SET_FLOAT(oDrawingDistance, 16000),
    CALL_NATIVE(bhv_g_marx_black_hole_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_marx_black_hole_loop),
    END_LOOP(),
};

const BehaviorScript bhvGMarxArrow[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW)),
    CALL_NATIVE(bhv_g_marx_arrow_init),
    SET_FLOAT(oDrawingDistance, 16000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_marx_arrow_loop),
    END_LOOP(),
};

const BehaviorScript bhvGMarxBodyLaser[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW)),
    CALL_NATIVE(bhv_g_marx_body_laser_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_marx_body_laser_loop),
    END_LOOP(),
};

const BehaviorScript bhvGMarxLaser[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_g_marx_laser_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_marx_laser_loop),
    END_LOOP(),
};

const BehaviorScript bhvGMarxIceBomb[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    BILLBOARD(),
    SET_FLOAT(oDrawingDistance, 16000),
    CALL_NATIVE(bhv_g_marx_ice_bomb_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_marx_ice_bomb_loop),
    END_LOOP(),
};

const BehaviorScript bhvGMarxBlackHoleEffect[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(bhv_g_marx_black_hole_effect_init),
    SET_FLOAT(oDrawingDistance, 16000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_marx_black_hole_effect_loop),
    END_LOOP(),
};

const BehaviorScript bhvGBrontoBurt[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    LOAD_ANIMATIONS(oAnimations, g_bronto_burt_anims),
    SET_HOME(),
    SET_FLOAT(oDrawingDistance, 16000),
    ANIMATE(0),
    CALL_NATIVE(bhv_g_bronto_burt_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_bronto_burt_loop),
    END_LOOP(),
};

const BehaviorScript bhvGMovingPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_MOVE_XZ_USING_FVEL)),
    LOAD_COLLISION_DATA(g_moving_platform_collision),
    SET_FLOAT(oDrawingDistance, 20000),
    CALL_NATIVE(bhv_g_moving_platform_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_moving_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvGMarxDoor[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    LOAD_COLLISION_DATA(g_marx_door_collision),
    SET_FLOAT(oDrawingDistance, 16000),
    CALL_NATIVE(bhv_g_marx_door_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_marx_door_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvGWaddleDee[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_E__SG_ENEMY | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW )),
    LOAD_ANIMATIONS(oAnimations, g_waddle_dee_anims),
    SET_HOME(),
    SET_FLOAT(oDrawingDistance, 16000),
    ANIMATE(0),
    CALL_NATIVE(bhv_g_waddle_dee_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_waddle_dee_loop),
    END_LOOP(),
};

extern void bhv_matplatform(void);
const BehaviorScript bhvMatPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_matplatform),
        //CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvBcTilting[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(bc_tilting_collision),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_seesaw_platform_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvBcWaddleDee[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_E__SG_ENEMY | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW )),
    LOAD_ANIMATIONS(oAnimations, bc_waddle_dee_anims),
    SET_HOME(),
    SET_FLOAT(oDrawingDistance, 16000),
    ANIMATE(0),
    CALL_NATIVE(bhv_g_waddle_dee_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_g_waddle_dee_loop),
    END_LOOP(),
};

const BehaviorScript bhvBcJelly[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),
    LOAD_ANIMATIONS(oAnimations, bc_jelly_anims),
    CALL_NATIVE(jelly_init),
    ANIMATE(0),
    BEGIN_LOOP(),
        CALL_NATIVE(jelly_loop),
    END_LOOP(),
};

const BehaviorScript bhvBcHoodmonger[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_ABILITY_CHRONOS_SMOOTH_SLOW | OBJ_FLAG_E__SG_ENEMY)),
    LOAD_ANIMATIONS(oAnimations, bc_hoodmonger_anims),
    SET_FLOAT(oDrawingDistance, 6000),
    SET_INT(oDamageOrCoinValue, 2),
    SET_INT(oHealth, 1),
    SET_INT(oNumLootCoins, 3),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    ANIMATE(0),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 80, /*Height*/ 210),
    CALL_NATIVE(bhv_hoodmonger_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_hoodmonger_loop),
        SET_INT(oIntangibleTimer, 0),
        SET_INT(oInteractStatus, 0),
    END_LOOP(),
};

const BehaviorScript bhvBcFspinner[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(bc_fspinner_collision),
    SET_FLOAT(oCollisionDistance, 4000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_lll_rotating_block_fire_bars_loop),
    END_LOOP(),
};

void bc_stair_loop(void);
const BehaviorScript bhvBcStair[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_VELOCITY_PLATFORM)),
    LOAD_COLLISION_DATA(bc_stair_collision),
    SET_FLOAT(oCollisionDistance, 4000),
    SET_FLOAT(oDrawingDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bc_stair_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvBcSkiploom[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_ENEMY)),//--E
    LOAD_ANIMATIONS(oAnimations, bc_skiploom_anims),
    ANIMATE(0),
    SET_HOME(),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 50, /*Gravity*/ 0, /*Bounciness*/ 0, /*Drag strength*/ 0, /*Friction*/ 1000, /*Buoyancy*/ 600, /*Unused*/ 0, 0),
    CALL_NATIVE(bhv_init_room),
    SET_INT(oInteractionSubtype, INT_SUBTYPE_TWIRL_BOUNCE),
    SET_FLOAT(oGraphYOffset, 30),
    SCALE(/*Unused*/ 0, /*Field*/ 150),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_fly_guy_update),
    END_LOOP(),
};

extern void bhv_atreus_bosscontroller(void);
const BehaviorScript bhvBcAtreus[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    LOAD_ANIMATIONS(oAnimations, bc_atreus_anims),
    ANIMATE(0),
    SET_HOME(),
    SET_FLOAT(oDrawingDistance, 32000),
    SCALE(/*Unused*/ 0, /*Field*/ 900),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_atreus_bosscontroller),
    END_LOOP(),
};

extern void bhv_final_boss_bowser(void);
const BehaviorScript bhvBcBowser[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO)),
    LOAD_ANIMATIONS(oAnimations, bc_bowser_anims),
    ANIMATE(2),
    DROP_TO_FLOOR(),
    SET_HOME(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_final_boss_bowser),
    END_LOOP(),
};

extern void bhv_pingas_plane(void);
const BehaviorScript bhvBcPingasPlane[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_E__SG_CUSTOM)),
    LOAD_ANIMATIONS(oAnimations, bc_pingas_plane_anims),
    ANIMATE(1),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_pingas_plane),
    END_LOOP(),
};

const BehaviorScript bhvBcPingasBall[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO)),
    SET_INT(oIntangibleTimer, 0),
    SET_INT(oDamageOrCoinValue, 1),
    SET_INTERACT_TYPE(INTERACT_DAMAGE),
    SET_HOME(),
    SET_HITBOX_WITH_OFFSET(/*Radius*/ 250, /*Height*/ 400, /*Downwards offset*/ 145),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        SET_INT(oInteractStatus, 0),
    END_LOOP(),
};

const BehaviorScript bhvBcBosslanding[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_PERSISTENT_RESPAWN)),
    LOAD_COLLISION_DATA(bc_bosslanding_collision),
    SET_FLOAT(oDrawingDistance, 32000),
    SET_FLOAT(oCollisionDistance, 32000),
    BEGIN_LOOP(),
        //CALL_NATIVE(bhv_seesaw_platform_update),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern void bhv_golem_limb(void);
const BehaviorScript bhvBcGolemBody[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(bc_golem_body_collision),
    OR_LONG(oFlags, (OBJ_FLAG_DONT_CALC_COLL_DIST)),
    SET_FLOAT(oCollisionDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_golem_limb),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvBcGolemLimb[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(bc_golem_limb_collision),
    OR_LONG(oFlags, (OBJ_FLAG_DONT_CALC_COLL_DIST)),
    SET_FLOAT(oCollisionDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_golem_limb),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvBcGolemHead[] = {
    BEGIN(OBJ_LIST_SURFACE),
    LOAD_COLLISION_DATA(bc_golem_head_collision),
    OR_LONG(oFlags, (OBJ_FLAG_DONT_CALC_COLL_DIST)),
    SET_FLOAT(oCollisionDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_golem_limb),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

extern void bhv_golem_crystal(void);
const BehaviorScript bhvBcGolemCrystal[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_golem_crystal),
    END_LOOP(),
};

extern void bhv_golem_crystalp(void);
const BehaviorScript bhvBcGolemCrystalp[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_E__SG_CUSTOM)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_golem_crystalp),
    END_LOOP(),
};

extern void bhv_golem_foot(void);
const BehaviorScript bhvBcGolemFoot[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_golem_foot),
    END_LOOP(),
};

extern void bhv_golem_laser(void);
const BehaviorScript bhvBcGolemLaser[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_golem_laser),
    END_LOOP(),
};

extern void bhv_npc_egadd_loop(void);
const BehaviorScript bhvEgaddNPC[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, egadd_anims),
    SET_INTERACT_TYPE(INTERACT_TEXT),
    DROP_TO_FLOOR(),
    SET_HITBOX(/*Radius*/ 100, /*Height*/ 60),
    ANIMATE(0),
    SET_HOME(),
    CALL_NATIVE(bhv_npc_init),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_npc_egadd_loop),
    END_LOOP(),
};

extern void bhv_artreus_artifact_on_machine(void);
const BehaviorScript bhvAArtifactOnMachine[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_FLOAT(oDrawingDistance, 20000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_artreus_artifact_on_machine),
    END_LOOP(),
};

void bhv_machine_door(void);
const BehaviorScript bhvHubDoor[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(hub_door_collision),
    SET_FLOAT(oCollisionDistance, 4000),
    SET_FLOAT(oDrawingDistance, 32000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_machine_door),
    END_LOOP(),
};

extern void bhv_stargoo(void);
const BehaviorScript bhvStarGoo[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_FLOAT(oDrawingDistance, 20000),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_stargoo),
    END_LOOP(),
};

const BehaviorScript bhvHubTargetBox[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_LONG(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_DONT_CALC_COLL_DIST | OBJ_FLAG_E__SG_BREAKABLE)),//--E
    LOAD_COLLISION_DATA(hub_target_box_collision),
    SET_FLOAT(oCollisionDistance, 1000),
    CALL_NATIVE(bhv_init_room),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_breakable_box_loop),
        CALL_NATIVE(load_object_collision_model),
        CALL_NATIVE(bhv_target_box_init),
    END_LOOP(),
    BREAK(),
};

extern void bhv_credits_slab_loob(void);
const BehaviorScript bhvCreditsSlab[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        SET_INT(oIntangibleTimer, 0),
        CALL_NATIVE(bhv_credits_slab_loob),
    END_LOOP(),
};

const BehaviorScript bhvDreamCatalyst[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_dream_catalyst),
    END_LOOP(),
};

extern void bhv_collectable_painting(void);
const BehaviorScript bhvCollectablePainting[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_collectable_painting),
    END_LOOP(),
};

extern void bhv_cardstar_init(void);
extern void bhv_cardstar(void);
const BehaviorScript bhvCarboardStarBody[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO)),
    CALL_NATIVE(bhv_cardstar_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_cardstar),
    END_LOOP(),
};

extern void bhv_boss_defeat_star(void);
const BehaviorScript bhvBdStar[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BILLBOARD(),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_boss_defeat_star),
    END_LOOP(),
};

extern void bhv_boss_defeat_wave(void);
const BehaviorScript bhvBdWave[] = {
    BEGIN(OBJ_LIST_UNIMPORTANT),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_boss_defeat_wave),
    END_LOOP(),
};

extern void bhv_final_boss_hint_sign(void);
const BehaviorScript bhvBcFinalBossHintSign[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_final_boss_hint_sign),
    END_LOOP(),
};

extern void bhv_floor_switch_teleporter(void);
const BehaviorScript bhvFloorSwitchTeleporter[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_floor_switch_teleporter),
    END_LOOP(),
};

extern void bhv_coin_pile_init(void);
const BehaviorScript bhvCoinPile[] = {
    BEGIN(OBJ_LIST_LEVEL),
    // Yellow coin - common:
    OR_INT(oFlags, (OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_PERSISTENT_RESPAWN)),
    CALL_NATIVE(bhv_coin_pile_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_yellow_coin_loop),
    END_LOOP(),
};