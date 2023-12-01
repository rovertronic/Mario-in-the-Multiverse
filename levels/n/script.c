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
#include "levels/n/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_n_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _n_segment_7SegmentRomStart, _n_segment_7SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, n_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02, LEVEL_N, 0x02, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x03, LEVEL_N, 0x03, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x04, LEVEL_N, 0x04, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x05, LEVEL_N, 0x05, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x06, LEVEL_N, 0x06, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x07, LEVEL_N, 0x07, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x08, LEVEL_N, 0x00, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, 1001, 0, 0, 0, 0, 0, (ABILITY_MARBLE << 16), bhvAbilityUnlock),
		OBJECT(MODEL_LEVEL_PIPE, 0, 0, 0, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_NONE, 395, 200, 0, 0, 90, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 395, 200, 0, 0, 90, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_WOODEN_SIGNPOST, 1201, 0, -401, 0, -57, 0, (DIALOG_N_HAMSTERBALL << 16), bhvMessagePanel),
		OBJECT(MODEL_NONE, 1799, 19, 0, 0, 0, 0, (2 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 1057, 19, 1455, 0, 0, 0, (3 << 16), bhvWarp),
		OBJECT(MODEL_NONE, -466, 19, 1738, 0, 0, 0, (4 << 16), bhvWarp),
		OBJECT(MODEL_NONE, -1643, 19, 732, 0, 0, 0, (5 << 16), bhvWarp),
		OBJECT(MODEL_NONE, -1603, 19, -817, 0, 0, 0, (6 << 16), bhvWarp),
		OBJECT(MODEL_NONE, -374, 19, -1760, 0, 0, 0, (7 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 1132, 19, -1398, 0, 0, 0, (8 << 16), bhvWarp),
		TERRAIN(n_area_1_collision),
		MACRO_OBJECTS(n_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, n_area_2),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*win*/0xF0, LEVEL_N, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 1245, 2927, -115, 0, 0, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -7455, 2234, 485, 0, 90, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -7455, 2234, 485, 0, 90, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 1345, -1860, -1115, 0, 0, 0, (0 << 24), bhvStar),
		TERRAIN(n_area_2_collision),
		MACRO_OBJECTS(n_area_2_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, n_area_3),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*win*/0xF0, LEVEL_N, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -8004, 6354, 6347, 0, 90, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -8004, 6354, 6347, 0, 90, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 303, -768, 4347, 0, 0, 0, (1 << 24), bhvStar),
		TERRAIN(n_area_3_collision),
		MACRO_OBJECTS(n_area_3_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(4, n_area_4),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*win*/0xF0, LEVEL_N, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -1070, 10222, 4462, 0, -90, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -1070, 10222, 4462, 0, -90, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -4270, 3932, 1062, 0, 0, 0, (2 << 24), bhvStar),
		TERRAIN(n_area_4_collision),
		MACRO_OBJECTS(n_area_4_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(5, n_area_5),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*win*/0xF0, LEVEL_N, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 9697, 13287, -10343, 0, -90, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 9697, 13287, -10343, 0, -90, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -8203, -1523, 11757, 0, 0, 0, (3 << 24), bhvStar),
		TERRAIN(n_area_5_collision),
		MACRO_OBJECTS(n_area_5_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(6, n_area_6),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*win*/0xF0, LEVEL_N, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -2749, 10684, 3344, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -2749, 10684, 3344, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -3949, 515, -12068, 0, 0, 0, (4 << 24), bhvStar),
		TERRAIN(n_area_6_collision),
		MACRO_OBJECTS(n_area_6_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(7, n_area_7),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*win*/0xF0, LEVEL_N, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -2217, 16296, 8488, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -2217, 16296, 8488, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 12576, -4902, 3987, 0, 0, 0, (5 << 24), bhvStar),
		TERRAIN(n_area_7_collision),
		MACRO_OBJECTS(n_area_7_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(0, n_area_0),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*win*/0xF0, LEVEL_N, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -7726, 1067, -1024, 0, 0, 0, 0x00000000, bhvMarbleCannon),
		OBJECT(MODEL_NONE, 5474, 12824, 10080, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 5474, 12824, 10080, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -11524, -2391, -8820, 0, 0, 0, (6 << 24), bhvStar),
		TERRAIN(n_area_0_collision),
		MACRO_OBJECTS(n_area_0_macro_objs),
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
