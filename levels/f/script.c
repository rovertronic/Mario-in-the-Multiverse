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
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	LOAD_MODEL_FROM_GEO(MODEL_F_BRIEFCASE, f_briefcase_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_F_DOOR, f_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_F_KEYPAD, f_keypad_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_F_FENCE, f_fence_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, f_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_F, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02/*enter a2*/, LEVEL_F, 0x02, 0x02, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY_SIGN, -4277, -173, -2596, 0, -41, 0, (ABILITY_KNIGHT << 16), bhvStaticObject),
		OBJECT(MODEL_ABILITY_SIGN, 14937, 577, -1796, 0, -65, 0, (ABILITY_GADGET_WATCH << 16), bhvStaticObject),
		OBJECT(MODEL_ABILITY_SIGN, -4421, 577, -5157, 0, -158, 0, (ABILITY_GADGET_WATCH << 16), bhvStaticObject),
		OBJECT(MODEL_BLUE_COIN_SWITCH, 39, 577, 6143, 0, 12, 0, 0x00000000, bhvBlueCoinSwitch),
		OBJECT(MODEL_BLUE_COIN, -251, 380, 5066, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -703, -83, 3614, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -1321, -173, 1928, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -1774, -172, 550, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -2243, -172, -755, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_F_BRIEFCASE, -7746, -104, 2566, 0, 0, 0, 0x00000000, bhvBriefcase),
		OBJECT(MODEL_F_BRIEFCASE, -3971, 646, 5941, 0, 0, 0, 0x00000000, bhvBriefcase),
		OBJECT(MODEL_F_BRIEFCASE, 9205, 646, 213, 0, 0, 0, 0x00000000, bhvBriefcase),
		OBJECT(MODEL_F_BRIEFCASE, 14574, 1021, 3536, 0, 0, 0, 0x00000000, bhvBriefcase),
		OBJECT(MODEL_F_BRIEFCASE, 12799, 646, -5068, 0, 0, 0, 0x00000000, bhvBriefcase),
		OBJECT(MODEL_NONE, 7712, 1013, -5236, 0, -74, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -1485, -174, -3325, 0, -74, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -5448, 1380, -749, 0, -74, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 9179, 579, 231, 0, -74, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 14327, 579, -996, 0, -74, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 4189, -173, -2208, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 128, -175, -4720, 0, 62, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -175, -173, -903, 0, 93, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -7069, -173, 3728, 0, -164, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -3802, 1021, -5367, 0, -177, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -2000, 578, 6550, 0, -80, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 6214, 1760, 1675, 0, -158, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 7078, 250, -2498, 0, -110, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 12087, 1388, -6219, 0, -71, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 14048, 577, 1840, 0, -72, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 14391, 709, 5305, 0, -88, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 9718, 622, 1988, 0, -74, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_LEVEL_PIPE, 8458, -173, -4282, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_F_FENCE, 4773, 1333, 4212, 0, 0, 0, 0x00000000, bhvFfence),
		OBJECT(MODEL_F_KEYPAD, 6404, 1146, 1438, 0, 113, 0, 0x00000000, bhvKeypad),
		OBJECT(MODEL_NONE, 9365, 220, -4423, 0, 99, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 9351, -173, -4349, 0, 99, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_PT_METAL_BOX, -3892, -173, -2268, 0, 11, 0, (1 << 16), bhvPtMetalBox),
		OBJECT(MODEL_BLUE_COIN_SWITCH, -4585, 577, -5454, 0, 0, 0, (0 << 24), bhvStarPieceSwitch),
		OBJECT(MODEL_NONE, -3545, -30, -2361, 0, 0, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_NONE, 4899, 1145, 4545, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_NONE, 1642, 87, -1858, 0, 0, 0, (3 << 24), bhvHiddenStar),
		OBJECT(MODEL_STAR_PIECE, -4546, 1450, -4410, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, -5365, 1825, -5026, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, -5388, 1450, -6088, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, -5891, 1472, -5419, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, -6171, 1832, -6199, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_NONE, 15309, 577, -1337, 0, 0, 0, (2 << 16), bhvWarp),
		TERRAIN(f_area_1_collision),
		MACRO_OBJECTS(f_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_MATT_MONRO),
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
		OBJECT(MODEL_ABILITY, 201, 247, -818, 0, 0, 0, (ABILITY_GADGET_WATCH << 16), bhvAbilityUnlock),
		OBJECT(MODEL_CHECKPOINT_FLAG, -11, 0, -7271, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_NONE, 5, 335, 255, 0, 0, 0, (3 << 16), bhvFadingWarp),
		OBJECT(MODEL_F_DOOR, 517, 0, -1797, 0, 0, 0, (0 << 16), bhvFdoor),
		OBJECT(MODEL_F_DOOR, 443, 0, -7711, 0, 0, 0, (1 << 16), bhvFdoor),
		OBJECT(MODEL_F_DOOR, 815, 0, -6411, 0, -90, 0, (2 << 16), bhvFdoor),
		OBJECT(MODEL_F_KEYPAD, 451, 207, -1855, 0, -90, 0, 0x00000000, bhvKeypad),
		OBJECT(MODEL_F_KEYPAD, 922, 312, -7647, 0, 0, 0, (1 << 16), bhvKeypad),
		OBJECT(MODEL_F_KEYPAD, 922, 312, -6477, 0, -180, 0, (2 << 16), bhvKeypad),
		OBJECT(MODEL_NONE, 5, 335, 255, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, -180, 0, (0x02 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_RED_COIN, -411, 197, -983, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -651, 292, -3253, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 856, 454, -4142, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -1934, 454, -4471, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -1477, 171, -5773, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -2818, 137, -7629, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -643, 0, -6257, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 1170, 625, -7549, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, 2715, 472, -3239, 0, 0, 0, (4 << 24), bhvStar),
		OBJECT(MODEL_NONE, 539, 245, -10159, 0, 0, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_NONE, 5833, 249, -6821, 0, 0, 0, (6 << 24), bhvStar),
		OBJECT(MODEL_NONE, 10, 371, -2895, 0, 0, 0, (7 << 24), bhvHiddenRedCoinStar),
		OBJECT(MODEL_NONE, 3137, 8, -3309, 0, 0, 0, (4 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 6187, 8, -6834, 0, 0, 0, (4 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 545, 8, -10550, 0, 0, 0, (4 << 16), bhvWarp),
		TERRAIN(f_area_2_collision),
		MACRO_OBJECTS(f_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_INRBIO),
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
