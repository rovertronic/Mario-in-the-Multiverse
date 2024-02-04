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
#include "levels/c/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_c_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _c_segment_7SegmentRomStart, _c_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x7, _c_segment_7SegmentRomStart, _c_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group15_yay0SegmentRomStart, _group15_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group15_geoSegmentRomStart, _group15_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_16), 
	LOAD_MODEL_FROM_GEO(MODEL_CRANE_ARROW, crane_arrow_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PAINT_GUN, paint_gun_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CRANE_HEAD, crane_head_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CRANE, crane_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, c_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_X, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 4729, 6014, 9275, 0, 0, 0, 0x00000000, bhvCamera),
		OBJECT(MODEL_CRANE, 13029, 1922, 1682, 0, 0, 0, 0x00000000, bhvCrane),
		OBJECT(MODEL_NONE, 8073, 3848, 7233, 0, 0, 0, 0x00000000, bhvCraneArrowController),
		OBJECT(MODEL_LEVEL_PIPE, 0, 1850, 691, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_NONE, 4041, 980, -1958, 0, 0, 0, 0x00000000, bhvFightWavesManager),
		OBJECT(MODEL_NONE, -1454, 1948, 7061, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 0, 1850, -761, 0, 0, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_PAINT_GUN, -1050, 2332, -460, 0, 0, 0, 0x00000000, bhvPaintGun),
		OBJECT(MODEL_FLIPSWITCH_1, -1265, 2529, 2230, 0, 0, 0, (1 << 24), bhvFlipswitch),
		OBJECT(MODEL_FLIPSWITCH_1, -4788, 695, 2175, 0, 0, 0, (1 << 24), bhvFlipswitch),
		OBJECT(MODEL_FLIPSWITCH_1, 457, 1948, 7483, 0, 0, 0, (1 << 24), bhvFlipswitch),
		OBJECT(MODEL_FLIPSWITCH_1, -3990, 284, -2278, 0, 0, 0, (1 << 24), bhvFlipswitch),
		OBJECT(MODEL_FLIPSWITCH_1, 3224, 1992, 4216, 0, 0, 0, (1 << 24), bhvFlipswitch),
		OBJECT(MODEL_PURPLE_SWITCH, 1515, 2416, 3128, 0, 0, 0, 0x00000000, bhvPurpleSwitchHiddenBoxes),
		OBJECT(MODEL_STAR, -9195, 548, 6641, 0, 0, 0, (2 << 24), bhvStar),
		TERRAIN(c_area_1_collision),
		MACRO_OBJECTS(c_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_C_SEA_ME_NOW),
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
