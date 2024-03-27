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
	LOAD_MODEL_FROM_GEO(MODEL_L_JOHN, johnp_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_L_JOHNBLOCK, l_johnblock_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_L_CHEESESLIME, cheeseslime_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_L_PEPPERMAN, pepperman_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, l_area_1),
		WARP_NODE(2, LEVEL_L, 0x02, 2, WARP_NO_CHECKPOINT),
		WARP_NODE(3, LEVEL_L, 0x01, 2, WARP_NO_CHECKPOINT),
		WARP_NODE(4 /* lap 2 */, LEVEL_L, 5, 4, WARP_NO_CHECKPOINT),
		WARP_NODE(5 /*exit*/, LEVEL_L, 0x06, 1, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_L_CHEESESLIME, 8016, 300, 0, 0, -90, 0, 0x00000000, bhvL_Cheeseslime),
		OBJECT(MODEL_L_CHEESESLIME, 5550, -600, 0, 0, 90, 0, 0x00000000, bhvL_Cheeseslime),
		OBJECT(MODEL_L_CHEESESLIME, -2900, -400, 0, 0, 90, 0, 0x00000000, bhvL_Cheeseslime),
		OBJECT(MODEL_L_CHEESESLIME, -6500, 0, 0, 0, 90, 0, 0x00000000, bhvL_Cheeseslime),
		OBJECT(MODEL_NONE, -5300, 300, 0, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 450, -100, 0, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 2000, -300, 0, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 6451, -300, 0, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -2450, 1200, 8, 0, -180, 0, (2 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, 6250, 300, 10, 0, -180, 0, (5 << 16), bhvLDoor),
		OBJECT(MODEL_L_JOHNBLOCK, 9450, 650, 0, 0, 0, 0, (0 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 9450, 750, 0, 0, 0, 0, (0 << 16), bhvJohnBlock),
		OBJECT(MODEL_NONE, 9700, 600, 0, 0, 0, 0, (4 << 16), bhvWarp),
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
		OBJECT(MODEL_RED_COIN, 9200, 600, 0, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 5300, -900, 0, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 3184, 193, 0, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -700, 300, 0, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, 8200, 600, 0, 0, 0, 0, (1 << 24), bhvHiddenRedCoinStar),
		OBJECT(MODEL_STAR, 6700, 600, 0, 0, 0, 0, (5 << 24), bhvL_EscapeStar),
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
		WARP_NODE(7, LEVEL_L, 0x03, 2, WARP_NO_CHECKPOINT),
		WARP_NODE(8, LEVEL_L, 0x04, 2, WARP_NO_CHECKPOINT),
		WARP_NODE(9, LEVEL_L, 0x05, 3, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, -541, 2638, -12, 0, 0, 0, (ABILITY_KNIGHT << 16), bhvAbilityUnlock),
		OBJECT(MODEL_ABILITY_SIGN, -11015, 16, 88, 0, -180, 0, (ABILITY_DASH_BOOSTER << 16), bhvStaticObject),
		OBJECT(MODEL_NONE, 2009, 1916, 14, 0, -180, 0, (2 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, 1009, -484, 14, 0, -180, 0, (3 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, -3991, 716, 14, 0, -180, 0, (4 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, -12691, -584, 14, 0, -180, 0, (5 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, 1609, -2784, 14, 0, -180, 0, (6 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, 6909, 216, 14, 0, -180, 0, (7 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, 8409, 1016, 14, 0, -180, 0, (8 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, 5109, -2684, 14, 0, -180, 0, (9 << 16), bhvLDoor),
		OBJECT(MODEL_L_JOHNBLOCK, 2609, 1266, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 2509, 1266, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 4709, -2734, 0, 0, 0, 0, (0 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 4609, -2734, 0, 0, 0, 0, (0 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 5709, -3234, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 5709, -3334, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 5709, -3434, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 2309, 966, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 2309, 1066, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 2309, 1166, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 2209, 1166, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 2209, 1066, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 2209, 966, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 2909, 1666, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 3009, 1666, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 1309, -134, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_PT_METAL_BOX, 3459, 116, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 3359, -3684, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 9359, -2384, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 7759, 216, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_STAR, -1941, 2771, 0, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_STAR, -10841, 2557, 0, 0, 0, 0, (2 << 24), bhvStar),
		TERRAIN(l_area_2_collision),
		MACRO_OBJECTS(l_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_L_HOT_SPAGHETTI),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, l_area_3),
		WARP_NODE(2, LEVEL_L, 0x02, 7, WARP_NO_CHECKPOINT),
		WARP_NODE(3, LEVEL_L, 0x03, 4, WARP_NO_CHECKPOINT),
		WARP_NODE(4, LEVEL_L, 0x03, 3, WARP_NO_CHECKPOINT),
		WARP_NODE(5, LEVEL_L, 0x02, 6/*undef*/, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 11950, 1150, 26, 0, -180, 0, (2 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, 11850, -350, 26, 0, -180, 0, (3 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, 3650, 250, 26, 0, -180, 0, (4 << 16), bhvLDoor),
		OBJECT(MODEL_PT_METAL_BOX, 1000, -150, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, -4700, 650, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_BLUE_COIN_SWITCH, 2000, 250, 0, 0, 0, 0, (3 << 24) | (45 << 16), bhvStarPieceSwitch),
		OBJECT(MODEL_STAR_PIECE, -5500, 650, 0, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, -6200, 150, 0, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, -5500, -350, 0, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, -6200, -850, 0, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, -5500, -1350, 0, 0, 0, 0, 0x00000000, bhvStarPiece),
		TERRAIN(l_area_3_collision),
		MACRO_OBJECTS(l_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_L_HOT_SPAGHETTI),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(4, l_area_4),
		WARP_NODE(2, LEVEL_L, 0x02, 8, WARP_NO_CHECKPOINT),
		WARP_NODE(3, LEVEL_L, 0x05, 2, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 2550, 5900, 10, 0, -180, 0, (2 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, -4650, -4800, 10, 0, -180, 0, (3 << 16), bhvLDoor),
		OBJECT(MODEL_PT_METAL_BOX, -2200, -4900, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 1400, -2100, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 1800, -3100, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 2700, 3000, 0, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_STAR, 3050, 3200, 0, 0, 0, 0, (4 << 24), bhvStar),
		TERRAIN(l_area_4_collision),
		MACRO_OBJECTS(l_area_4_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_L_HOT_SPAGHETTI),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(5, l_area_5),
		WARP_NODE(2, LEVEL_L, 0x04, 3, WARP_NO_CHECKPOINT),
		WARP_NODE(3, LEVEL_L, 0x02, 9, WARP_NO_CHECKPOINT),
		WARP_NODE(4 /* lap 2 start */, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -7950, 350, 21, 0, -180, 0, (2 << 16), bhvLDoor),
		OBJECT(MODEL_NONE, -17350, -550, 21, 0, -180, 0, (3 << 16), bhvLDoor),
		OBJECT(MODEL_L_JOHNBLOCK, 9150, -900, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, 9150, -800, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, -7150, -200, 0, 0, 0, 0, (0 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, -7250, -200, 0, 0, 0, 0, (0 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, -7250, -100, 0, 0, 0, 0, (0 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, -7150, -100, 0, 0, 0, 0, (0 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, -7450, 800, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, -7550, 800, 0, 0, 0, 0, (1 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, -1750, -400, 0, 0, 0, 0, (0 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, -1750, -500, 0, 0, 0, 0, (0 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, -2150, -300, 0, 0, 0, 0, (0 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, -2250, -300, 0, 0, 0, 0, (0 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, -2450, 100, 0, 0, 0, 0, (0 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHNBLOCK, -2550, 100, 0, 0, 0, 0, (0 << 16), bhvJohnBlock),
		OBJECT(MODEL_L_JOHN, 13688, -1150, 0, 0, 0, 0, 0x00000000, bhvL_JohnPillar),
		OBJECT(MODEL_NONE, 12800, -750, 0, 0, -90, 0, (4 << 16), bhvSpinAirborneWarp),
		TERRAIN(l_area_5_collision),
		MACRO_OBJECTS(l_area_5_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_L_HOT_SPAGHETTI),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(6, l_area_6),
		WARP_NODE(1 /*exit1*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(2 /*exit2*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(3 /*enter 1*/, LEVEL_L, 0x01, 5, WARP_NO_CHECKPOINT),
		WARP_NODE(4 /*enter 2*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -1356, 0, 0, 0, 0, 0, (10 << 24) | (3 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 1356, 0, 0, 0, 0, 0, (10 << 24) | (4 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 0, 500, 0, 0, 0, 0, (1 << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_LEVEL_PIPE, 0, 0, -1275, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_L_PEPPERMAN, 0, 0, 1267, 0, -180, 0, 0x00000000, bhvL_PeppermanNPC),
		TERRAIN(l_area_6_collision),
		MACRO_OBJECTS(l_area_6_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_L_MONDAYS),
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
