#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"


/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/d/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_d_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _d_segment_7SegmentRomStart, _d_segment_7SegmentRomEnd), 
	LOAD_YAY0(0xa, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, d_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02/*cave enter*/, LEVEL_D, 0x03, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x03/*cave exit*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x04/*ship entrance*/, LEVEL_D, 0x02, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_D, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, -524, 4167, -2312, 0, 0, 0, (ABILITY_DEFAULT << 16), bhvAbilityUnlock),
		OBJECT(MODEL_NONE, 1033, 4367, -506, 0, 0, 0, 0x00000000, bhvBirdsSoundLoop),
		OBJECT(MODEL_NONE, -4483, 3385, -18594, 0, 0, 0, (20 << 24) | (2 << 16), bhvWarp),
		OBJECT(MODEL_CHECKPOINT_FLAG, -6889, 3247, -1311, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 5966, 4324, -12486, 0, 0, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_LEVEL_PIPE, 3373, 2364, 1169, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_NONE, -4483, 3385, -17926, 0, 0, 0, (0x03 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 3373, 2668, 874, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 3373, 2668, 874, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 6264, 1016, 5109, 0, 0, 0, (20 << 24) | (4 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 2075, 4281, -2049, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_NONE, 1875, 4281, -2049, 0, 0, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_NONE, 1675, 4281, -2049, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_NONE, 1475, 4281, -2049, 0, 0, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_NONE, 1275, 4281, -2049, 0, 0, 0, (4 << 24), bhvStar),
		OBJECT(MODEL_NONE, 1075, 4281, -2049, 0, 0, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_NONE, 875, 4281, -2049, 0, 0, 0, (6 << 24), bhvStar),
		OBJECT(MODEL_NONE, 675, 4281, -2049, 0, 0, 0, (7 << 24), bhvStar),
		OBJECT(MODEL_NONE, -1845, 3189, -3930, 0, 0, 0, 0x00000000, bhvWaterfallSoundLoop),
		TERRAIN(d_area_1_collision),
		MACRO_OBJECTS(d_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, d_area_2),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x01/*death entry*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1/*death*/, LEVEL_D, 0x02, 0x01, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 1817, -1322, 64, 0, -90, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 1817, -169, 64, 0, -90, 0, (0x0A << 16), bhvInstantActiveWarp),
		TERRAIN(d_area_2_collision),
		MACRO_OBJECTS(d_area_2_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, d_area_3),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x01/*death entry*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1/*death*/, LEVEL_D, 0x03, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02/*cave exit*/, LEVEL_D, 0x01, 0x03, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY_SIGN, -9492, 1602, -4011, 0, 0, 0, (ABILITY_PHASEWALK << 16), bhvStaticObject),
		OBJECT(MODEL_ABILITY_SIGN, -9253, 1602, -4011, 0, 0, 0, (ABILITY_E_SHOTGUN << 16), bhvStaticObject),
		OBJECT(MODEL_NONE, 1577, -913, 16559, 0, 0, 0, (20 << 24) | (2 << 16), bhvWarp),
		OBJECT(MODEL_CHECKPOINT_FLAG, -6372, 7, 4866, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, -3072, 1152, 840, 0, 0, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, -8997, 1602, -3422, 0, 0, 0, (2 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_RED_FLAME, 1191, -73, 2761, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 1191, -73, -1499, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_NONE, 1577, -692, 15430, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 1577, -913, 15430, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		TERRAIN(d_area_3_collision),
		MACRO_OBJECTS(d_area_3_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(1, 0, 0, 0, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
