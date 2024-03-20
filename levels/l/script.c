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
#include "levels/l/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_l_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _l_segment_7SegmentRomStart, _l_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x05, _group3_yay0SegmentRomStart, _group3_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group3_geoSegmentRomStart, _group3_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_YAY0(0xa, _bitfs_skybox_yay0SegmentRomStart, _bitfs_skybox_yay0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_4), 
	JUMP_LINK(script_func_global_15), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, l_area_1),
		WARP_NODE(2, LEVEL_L, 0x02, 2, WARP_NO_CHECKPOINT),
		WARP_NODE(3, LEVEL_L, 0x01, 2, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -5300, 300, 0, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 450, -100, 0, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 2000, -300, 0, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 6451, -300, 0, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -2450, 1200, 8, 0, -180, 0, (2 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, 6250, 300, 10, 0, -180, 0, (3 << 16), bhvLDoor),
		MARIO_POS(0x01, 0, 6700, 300, 0),
		OBJECT(MODEL_PT_METAL_BOX, -7000, 0, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, -100, -603, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, -1000, -600, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 7100, -300, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 8700, -1100, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_RED_COIN, 8700, -1300, 0, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 7600, -300, 0, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -600, -600, 0, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -8000, -200, 0, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 9700, 600, 0, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 5300, -900, 0, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 3184, 193, 0, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -700, 300, 0, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, 8200, 600, 0, 0, 0, 0, (0 << 24), bhvHiddenRedCoinStar),
		TERRAIN(l_area_1_collision),
		MACRO_OBJECTS(l_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_L_HOT_SPAGHETTI),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, l_area_2),
		WARP_NODE(2, LEVEL_L, 0x01, 2, WARP_NO_CHECKPOINT),
		WARP_NODE(3, LEVEL_L, 0x02, 4, WARP_NO_CHECKPOINT),
		WARP_NODE(4, LEVEL_L, 0x02, 3, WARP_NO_CHECKPOINT),
		WARP_NODE(5, LEVEL_L, 0x02, 6, WARP_NO_CHECKPOINT),
		WARP_NODE(6, LEVEL_L, 0x02, 5, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, -541, 2638, -12, 0, 0, 0, (ABILITY_KNIGHT << 16), bhvAbilityUnlock),
		OBJECT(MODEL_ABILITY_SIGN, -11015, 16, 88, 0, -180, 0, (ABILITY_DASH_BOOSTER << 16), bhvStaticObject),
		OBJECT(MODEL_NONE, 2009, 1916, 14, 0, -180, 0, (2 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, 1009, -484, 14, 0, -180, 0, (3 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, -3991, 716, 14, 0, -180, 0, (4 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, -12691, -584, 14, 0, -180, 0, (5 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, 1609, -2784, 14, 0, -180, 0, (6 << 16), bhvLDoor),
		OBJECT(MODEL_PT_METAL_BOX, 3459, 116, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 3359, -3684, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 9359, -2384, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 7759, 216, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_STAR, -10841, 2557, 0, 0, 0, 0, (1 << 24), bhvStar),
		TERRAIN(l_area_2_collision),
		MACRO_OBJECTS(l_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_L_HOT_SPAGHETTI),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 6700, 300, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
