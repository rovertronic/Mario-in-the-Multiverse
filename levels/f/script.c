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
#include "levels/f/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_f_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _f_segment_7SegmentRomStart, _f_segment_7SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, f_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_F, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02/*enter a2*/, LEVEL_F, 0x02, 0x02, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_LEVEL_PIPE, 0, 70, 967, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_NONE, 9, 863, -936, 0, 0, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 9, 422, -1490, 0, 0, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -6597, 1744, -6097, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_NONE, 8862, 1336, -4976, 0, 0, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_NONE, 5487, 1283, 5090, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_NONE, 17146, 646, -1497, 0, 0, 0, (2 << 16), bhvWarp),
		TERRAIN(f_area_1_collision),
		MACRO_OBJECTS(f_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, f_area_2),
		WARP_NODE(/*death*/ 0xF1, LEVEL_F, /*this area*/ 0x02, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02/*a2 entry*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x03/*fading return*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x04/*return*/, LEVEL_F, 0x02, 0x03, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, 225, 276, -917, 0, 0, 0, (ABILITY_GADGET_WATCH << 16), bhvAbilityUnlock),
		OBJECT(MODEL_CHECKPOINT_FLAG, -12, 0, -8144, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_NONE, 6, 375, 286, 0, 0, 0, (3 << 16), bhvFadingWarp),
		OBJECT(MODEL_NONE, 6, 375, 286, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, -180, 0, (0x02 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_RED_COIN, -460, 221, -1101, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -729, 327, -3643, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 958, 508, -4639, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -2166, 508, -5008, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -1654, 191, -6465, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -3157, 154, -8544, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -720, 0, -7007, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 1310, 700, -8455, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, 3041, 529, -3628, 0, 0, 0, (4 << 24), bhvStar),
		OBJECT(MODEL_NONE, 604, 275, -11378, 0, 0, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_NONE, 6533, 279, -7639, 0, 0, 0, (6 << 24), bhvStar),
		OBJECT(MODEL_NONE, 11, 415, -3242, 0, 0, 0, (7 << 24), bhvHiddenRedCoinStar),
		OBJECT(MODEL_NONE, 3513, 9, -3706, 0, 0, 0, (4 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 6929, 9, -7654, 0, 0, 0, (4 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 611, 9, -11817, 0, 0, 0, (4 << 16), bhvWarp),
		TERRAIN(f_area_2_collision),
		MACRO_OBJECTS(f_area_2_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
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
