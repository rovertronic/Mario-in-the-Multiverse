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

	AREA(4, n_area_4),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, -1146, 50, 1211, 0, 0, 0, (ABILITY_DEFAULT << 16), bhvAbilityUnlock),
		OBJECT(MODEL_CHECKPOINT_FLAG, 1439, 50, -1412, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 1439, 50, -1112, 0, 0, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_LEVEL_PIPE, 0, 50, 691, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_NONE, -3726, 1265, 249, 0, 0, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -3726, 968, 249, 0, 0, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 1280, 1706, -3, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_NONE, 1080, 1706, -3, 0, 0, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_NONE, 880, 1706, -3, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_NONE, 680, 1706, -3, 0, 0, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_NONE, 480, 1706, -3, 0, 0, 0, (4 << 24), bhvStar),
		OBJECT(MODEL_NONE, 280, 1706, -3, 0, 0, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_NONE, 80, 1706, -3, 0, 0, 0, (6 << 24), bhvStar),
		OBJECT(MODEL_NONE, -120, 1706, -3, 0, 0, 0, (7 << 24), bhvStar),
		TERRAIN(n_area_4_collision),
		MACRO_OBJECTS(n_area_4_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, n_area_3),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -3232, 3381, 3193, 0, 90, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -3232, 3084, 3193, 0, 90, 0, (0x0A << 16), bhvInstantActiveWarp),
		TERRAIN(n_area_3_collision),
		MACRO_OBJECTS(n_area_3_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(1, n_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 4638, 6668, -5172, 0, -90, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 4638, 6465, -5172, 0, -90, 0, (0x0A << 16), bhvInstantActiveWarp),
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
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -4084, 1715, -273, 0, 0, 0, 0x00000000, bhvMarbleCannon),
		OBJECT(MODEL_NONE, 2517, 7883, 5272, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 2517, 7587, 5272, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		TERRAIN(n_area_2_collision),
		MACRO_OBJECTS(n_area_2_macro_objs),
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
