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
#include "levels/h/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_h_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _h_segment_7SegmentRomStart, _h_segment_7SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, h_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_X, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, -5630, -1410, -581, 0, 0, 0, (ABILITY_PHASEWALK << 16), bhvAbilityUnlock),
		OBJECT(MODEL_CHECKPOINT_FLAG, -3303, -1410, -592, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 10329, -2218, 1671, 0, 0, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_LEVEL_PIPE, 2115, -1410, 11705, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_NONE, 2115, -886, 10467, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 2115, -1410, 10467, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		MARIO_POS(0x01, 0, 2115, -1410, 10467),
		OBJECT(MODEL_RED_COIN, 11021, -2218, 3532, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 13595, -2218, -535, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 13898, -3385, -6129, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 5140, -202, 1204, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 13079, 2011, 12404, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 6535, -1410, 10136, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 10262, -3060, -11664, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 14354, -1410, 10627, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, -11697, -1410, -574, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_NONE, 11104, -1720, 1121, 0, 0, 0, (1 << 24), bhvHiddenRedCoinStar),
		OBJECT(MODEL_NONE, 2726, 5168, -1142, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_NONE, -9932, -626, 10249, 0, 0, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_NONE, 633, 14252, 1061, 0, 0, 0, (4 << 24), bhvStar),
		OBJECT(MODEL_NONE, 433, 14252, 1061, 0, 0, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_NONE, 233, 14252, 1061, 0, 0, 0, (6 << 24), bhvStar),
		OBJECT(MODEL_NONE, 33, 14252, 1061, 0, 0, 0, (7 << 24), bhvStar),
		TERRAIN(h_area_1_collision),
		MACRO_OBJECTS(h_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 2115, -1410, 10467),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
