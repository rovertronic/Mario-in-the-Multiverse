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
	LOAD_MODEL_FROM_GEO(MODEL_N_BALL, n_ball_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, n_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0 /*win*/, LEVEL_N, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02, LEVEL_N, 0x02, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x03, LEVEL_N, 0x03, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x04, LEVEL_N, 0x04, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x05, LEVEL_N, 0x05, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x06, LEVEL_N, 0x06, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x07, LEVEL_N, 0x07, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x08, LEVEL_N, 0x00, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, 1001, 0, 0, 0, 0, 0, (ABILITY_MARBLE << 16), bhvAbilityUnlock),
		OBJECT(MODEL_N_BALL, -949, 2238, 0, 0, 90, 0, (7 << 24), bhvNball),
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
		SET_BACKGROUND_MUSIC(0x00, SEQ_HAMSTERBALL),
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
		OBJECT(MODEL_NONE, -5955, 1927, 485, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 4545, -2073, -3026, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -555, 2527, -84, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 3345, 2678, 1595, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -889, 2327, 3385, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 45, 3350, 5385, 0, 0, 0, (0 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, -7455, 2234, 485, 0, 90, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -7455, 2234, 485, 0, 90, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 1345, -1998, -1115, 0, 0, 0, (0 << 24), bhvStar),
		TERRAIN(n_area_2_collision),
		MACRO_OBJECTS(n_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_HAMSTERBALL),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, n_area_3),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*win*/0xF0, LEVEL_N, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 6296, 703, -853, 0, 0, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -3004, 5103, 6347, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -404, 4703, 2247, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -2804, 3603, -3260, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1004, 2203, -1799, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1104, 2203, -1799, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1204, 2203, -1799, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -904, 2203, -1799, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -804, 2203, -1799, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1004, 2603, -1753, 0, 0, 0, (1 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, -8004, 6354, 6347, 0, 90, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -8004, 6354, 6347, 0, 90, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 303, -768, 4347, 0, 0, 0, (1 << 24), bhvStar),
		TERRAIN(n_area_3_collision),
		MACRO_OBJECTS(n_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_HAMSTERBALL),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(4, n_area_4),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*win*/0xF0, LEVEL_N, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -4270, 3809, -1733, 0, 0, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -1070, 8999, 2462, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1070, 8499, 1862, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1070, 7999, 1262, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1870, 7499, -1938, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1970, 3799, -1738, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -2996, 5299, -4138, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 3930, 7568, 5662, 0, 0, 0, (2 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, -1070, 10222, 4462, 0, -90, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -1070, 10222, 4462, 0, -90, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -4270, 3932, 1062, 0, 0, 0, (2 << 24), bhvStar),
		TERRAIN(n_area_4_collision),
		MACRO_OBJECTS(n_area_4_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_HAMSTERBALL),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(5, n_area_5),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*win*/0xF0, LEVEL_N, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 3397, 10529, -5832, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 1797, 10529, -3843, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 1797, 10529, -2749, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -3520, 8329, -2443, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -4703, 9129, -8043, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 3597, 3879, 8857, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -743, -1671, 11757, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -5863, -1671, 11757, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -9898, 5764, 18052, 0, 0, 0, (3 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, 9697, 13287, -10343, 0, -90, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 9697, 13287, -10343, 0, -90, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -8203, -1523, 11757, 0, 0, 0, (3 << 24), bhvStar),
		TERRAIN(n_area_5_collision),
		MACRO_OBJECTS(n_area_5_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_HAMSTERBALL),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(6, n_area_6),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*win*/0xF0, LEVEL_N, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -6301, 2965, 2543, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -5749, 2965, 1394, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -5649, 2965, 1394, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -5849, 2965, 1394, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -3949, 1265, -6948, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1309, 8665, 1144, 0, -90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 2913, 5865, 2144, 0, -90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 3251, 5865, 3744, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -3749, 4465, 5557, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -6749, 2965, -1456, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 4251, 5865, 2944, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -749, 7875, -56, 0, -90, 0, (1 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -5749, 3365, 1394, 0, 0, 0, (4 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, -2749, 10684, 3344, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -2749, 10684, 3344, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -5748, 3073, 944, 0, 0, 0, (13 << 16), bhvCollectablePainting),
		OBJECT(MODEL_NONE, -3949, 515, -12068, 0, 0, 0, (4 << 24), bhvStar),
		TERRAIN(n_area_6_collision),
		MACRO_OBJECTS(n_area_6_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_HAMSTERBALL),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(7, n_area_7),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*win*/0xF0, LEVEL_N, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -2217, 9148, -512, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -2217, 9148, -5812, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1117, 7348, -5603, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 983, 7348, -6912, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 2783, 5348, -6913, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 7783, 3348, -4613, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 5383, -485, -1013, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 8583, -3752, 687, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 8283, -4352, 5303, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 4683, -1685, -1013, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 4483, -2742, -1013, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 3483, -3652, 1640, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -12525, 9509, -2916, 0, 0, 0, (5 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, -2217, 16296, 8488, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -2217, 16296, 8488, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 12576, -4902, 3987, 0, 0, 0, (5 << 24), bhvStar),
		TERRAIN(n_area_7_collision),
		MACRO_OBJECTS(n_area_7_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_HAMSTERBALL),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(0, n_area_0),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_N, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*win*/0xF0, LEVEL_N, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -17029, -42, -7220, 0, 0, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 8174, 9878, 2125, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 10274, 9058, -820, 0, 135, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 9474, 9058, -20, 0, 135, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 11874, 8458, -2420, 0, 135, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 11074, 8458, -1620, 0, 135, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 2074, 5530, -20, 0, -90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -626, 4259, -20, 0, -90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -5939, 2111, -1020, 0, -90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -9626, 2748, -1020, 0, -90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -13856, 1683, -2773, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -15426, 1058, -3220, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -17026, 565, -3667, 0, -180, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -13524, -2352, -8820, 0, -90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -8126, 4778, -1020, 0, 0, 0, (6 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, -7726, 1067, -1024, 0, 0, 0, 0x00000000, bhvMarbleCannon),
		OBJECT(MODEL_NONE, 5474, 12824, 10080, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 5474, 12824, 10080, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -11524, -2391, -8820, 0, 0, 0, (6 << 24), bhvStar),
		TERRAIN(n_area_0_collision),
		MACRO_OBJECTS(n_area_0_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_HAMSTERBALL),
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
