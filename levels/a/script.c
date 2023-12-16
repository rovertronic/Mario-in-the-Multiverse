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
#include "levels/a/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_a_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _a_segment_7SegmentRomStart, _a_segment_7SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	LOAD_MODEL_FROM_GEO(MODEL_JELLY, jelly_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_JF_PLATFORM, jfplatform_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TAXISTOP, taxistop_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TSBOAT, boat_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TIKI_WOOD, tikibox_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TIKI_STONE, stone_tiki_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TRAMP, tramp_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_FLOATING_CHECKER_PLATFORM, floating_checker_platform_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_KING_JELLY, kingjelly_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_KING_JELLY_SHOCK, kingjellyshock_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BUBBLENET_RED_BUTTON, bh_red_button_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_JELLYS, jellys_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_KKTABLE, kktable_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_KKB, kkb_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_SQUIDWARD, squidward_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BHBRIDGE, bhbridge_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_A_PLANK, a_plank_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_GOO_DROP, goodrop_geo),

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, a_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_X, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x03, LEVEL_A, 0x02, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x04, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, -1146, 50, 5451, 0, 0, 0, (ABILITY_BUBBLE_HAT << 16), bhvAbilityUnlock),
		OBJECT(MODEL_CHECKPOINT_FLAG, -4406, -163, 195, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, -46, -24, -13435, 0, 0, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_JELLY, -2805, -153, 5461, 0, 0, 0, 0x00000000, bhvJelly),
		OBJECT(MODEL_JELLY, -3766, -198, 4509, 0, 0, 0, 0x00000000, bhvJelly),
		OBJECT(MODEL_JELLY, -4191, -83, 62, 0, 0, 0, 0x00000000, bhvJelly),
		OBJECT(MODEL_JF_PLATFORM, -1419, 637, 3323, 0, 15, 0, 0x00000000, bhvJellyfishFieldsPlatform),
		OBJECT(MODEL_JF_PLATFORM, -5459, 583, 5492, 0, -170, 0, 0x00000000, bhvJellyfishFieldsPlatform),
		OBJECT(MODEL_JF_PLATFORM, -837, 905, 6718, 0, -85, 0, 0x00000000, bhvJellyfishFieldsPlatform),
		OBJECT(MODEL_JF_PLATFORM, -3206, 583, 1417, 0, 0, 0, 0x00000000, bhvJellyfishFieldsPlatform),
		OBJECT(MODEL_NONE, -5684, -81, 4607, 0, 0, 0, (0x0 << 16), bhvTikiBox),
		OBJECT(MODEL_NONE, -5684, -81, 5104, 0, 0, 0, (0x0 << 16), bhvTikiBox),
		OBJECT(MODEL_NONE, -5684, -336, 4861, 0, 0, 0, (0x0 << 16), bhvTikiBox),
		OBJECT(MODEL_NONE, -5684, -336, 5104, 0, 0, 0, (0x0 << 16), bhvTikiBox),
		OBJECT(MODEL_NONE, -5684, -336, 4607, 0, 0, 0, (0x0 << 16), bhvTikiBox),
		OBJECT(MODEL_NONE, -5684, -81, 4861, 0, 0, 0, (0x0 << 16), bhvTikiBox),
		OBJECT(MODEL_JELLY, -3766, -92, -4402, 0, 0, 0, 0x00000000, bhvJelly),
		OBJECT(MODEL_JELLY, -5157, -92, -5749, 0, 0, 0, 0x00000000, bhvJelly),
		OBJECT(MODEL_JELLY, -4820, -92, -9696, 0, 0, 0, 0x00000000, bhvJelly),
		OBJECT(MODEL_JELLY, -2804, 541, -9219, 0, 0, 0, 0x00000000, bhvJelly),
		OBJECT(MODEL_TAXISTOP, 5180, -163, -7061, 0, -90, 0, (1 << 16), bhvTaxiStop),
		OBJECT(MODEL_NONE, -6360, -222, 4723, 0, 0, 0, (0x03 << 16), bhvWarp),
		OBJECT(MODEL_NONE, -4853, -336, 4680, 0, 90, 0, (0x04 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_FLOATING_CHECKER_PLATFORM, -2226, 27, 4626, 0, 0, 0, (0 << 16), bhvFloatingCheckerPlatform),
		OBJECT(MODEL_FLOATING_CHECKER_PLATFORM, -2226, 27, 5026, 0, 0, 0, (1 << 16), bhvFloatingCheckerPlatform),
		OBJECT(MODEL_FLOATING_CHECKER_PLATFORM, -2226, 27, 4137, 0, 0, 0, (2 << 16), bhvFloatingCheckerPlatform),
		OBJECT(MODEL_NONE, -5684, -336, 4365, 0, 0, 0, (0x0 << 16), bhvTikiBox),
		OBJECT(MODEL_NONE, -5684, -81, 4365, 0, 0, 0, (0x0 << 16), bhvTikiBox),
		OBJECT(MODEL_LEVEL_PIPE, 1591, -163, 4557, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_NONE, 500, 365, 5075, 0, -95, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 500, -163, 5079, 0, -90, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 5125, 62, -7940, 0, 0, 0, (0 << 24), bhvStar),
		TERRAIN(a_area_1_collision),
		MACRO_OBJECTS(a_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_JELLYFISH_FIELDS),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, a_area_2),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x05, LEVEL_A, 0x01, 0x04, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -3711, 205, -1326, 0, 90, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_TRAMP, -353, -242, -1882, 0, 0, 0, 0x00000000, bhvTramp),
		OBJECT(MODEL_TRAMP, 1117, -242, -650, 0, 0, 0, 0x00000000, bhvTramp),
		OBJECT(MODEL_TRAMP, 1814, -28, 1114, 0, 0, 0, 0x00000000, bhvTramp),
		OBJECT(MODEL_TRAMP, 2560, 134, 2234, 0, 0, 0, 0x00000000, bhvTramp),
		OBJECT(MODEL_TRAMP, 4057, 134, 4234, 0, 0, 0, 0x00000000, bhvTramp),
		OBJECT(MODEL_TRAMP, 5466, -18, 3776, 0, 0, 0, 0x00000000, bhvTramp),
		OBJECT(MODEL_RED_COIN, 1752, 40, -1755, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 2682, 253, 4260, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 6855, 134, 3383, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 5466, 189, 3776, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 4057, 420, 4234, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 2560, 339, 2234, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 1814, 260, 1114, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -353, 15, -1882, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, -3090, 494, -1307, 0, 0, 0, (3 << 24), bhvHiddenRedCoinStar),
		OBJECT(MODEL_NONE, -4530, 205, -1355, 0, 0, 0, (0x05 << 16), bhvWarp),
		TERRAIN(a_area_2_collision),
		MACRO_OBJECTS(a_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_JELLYFISH_SECRET),
		TERRAIN_TYPE(TERRAIN_SNOW),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, a_area_3),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x09, LEVEL_A, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 3212, 75, -11, 0, 0, 0, (0x09 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 2264, 0, -11, 0, 90, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_KING_JELLY, 0, 263, -41, 0, 0, 0, 0x00000000, bhvKingJelly),
		OBJECT(MODEL_BUBBLENET_RED_BUTTON, 154, 0, -2039, 0, 0, 0, 0x00000000, bhvGooSwitch),
		OBJECT(MODEL_BUBBLENET_RED_BUTTON, 884, 0, -1696, 0, 0, 0, 0x00000000, bhvGooSwitch),
		OBJECT(MODEL_BUBBLENET_RED_BUTTON, 437, 0, -2466, 0, 0, 0, 0x00000000, bhvGooSwitch),
		TERRAIN(a_area_3_collision),
		MACRO_OBJECTS(a_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_WATER),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(4, a_area_4),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x07, LEVEL_A, 0x05, 0x0E, WARP_NO_CHECKPOINT),
		WARP_NODE(0x08, LEVEL_A, 0x04, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0E, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x15, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_FLOATING_CHECKER_PLATFORM, -1634, -234, 929, 0, 0, 0, (2 << 16), bhvFloatingCheckerPlatform),
		OBJECT(MODEL_STAR, -1494, 2179, 3687, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_FLOATING_CHECKER_PLATFORM, -684, 62, 459, 0, -90, 0, (0 << 16), bhvFloatingCheckerPlatform),
		OBJECT(MODEL_FLOATING_CHECKER_PLATFORM, -3, 238, 1420, 0, 0, 0, (2 << 16), bhvFloatingCheckerPlatform),
		OBJECT(MODEL_FLOATING_CHECKER_PLATFORM, -3, 173, 2120, 0, 0, 0, (2 << 16), bhvFloatingCheckerPlatform),
		OBJECT(MODEL_FLOATING_CHECKER_PLATFORM, -3, 473, 3920, 0, 0, 0, (0 << 16), bhvFloatingCheckerPlatform),
		OBJECT(MODEL_FLOATING_CHECKER_PLATFORM, -503, 973, 4420, 0, 0, 0, (2 << 16), bhvFloatingCheckerPlatform),
		OBJECT(MODEL_FLOATING_CHECKER_PLATFORM, -1403, 1473, 3120, 0, 0, 0, (2 << 16), bhvFloatingCheckerPlatform),
		OBJECT(MODEL_TAXISTOP, -11752, 316, -5001, 0, 0, 0, (2 << 16), bhvTaxiStop),
		OBJECT(MODEL_NONE, -1078, -418, 3039, 0, 0, 0, (1 << 16), bhvJelly),
		OBJECT(MODEL_NONE, -2278, -418, 4539, 0, 0, 0, (1 << 16), bhvJelly),
		OBJECT(MODEL_NONE, 2422, -418, 4739, 0, 0, 0, (1 << 16), bhvJelly),
		OBJECT(MODEL_NONE, 2022, -418, -261, 0, 0, 0, (1 << 16), bhvJelly),
		OBJECT(MODEL_NONE, 4222, -418, 639, 0, 0, 0, (1 << 16), bhvJelly),
		OBJECT(MODEL_NONE, -4878, -90, 12645, 0, 0, 0, (0x07 << 16), bhvWarp),
		OBJECT(MODEL_NONE, -4866, -176, 11472, 0, -180, 0, (0x15 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_BUBBLENET_RED_BUTTON, -498, -476, 1525, 0, 180, 0, (0 << 16), bhvBhButton),
		OBJECT(MODEL_BHBRIDGE, 1136, -476, 1765, 0, 0, 0, 0x00000000, bhvRBridge),
		OBJECT(MODEL_A_PLANK, -76, -1070, -6251, 0, 0, 0, 0x00000000, bhvRPlank),
		OBJECT(MODEL_BUBBLENET_RED_BUTTON, 802, -1070, -4175, 0, -90, 0, (1 << 16), bhvBhButton2),
		OBJECT(MODEL_TAXISTOP, 10473, 118, 1823, 0, 0, 0, (3 << 16), bhvTaxiStop),
		OBJECT(MODEL_NONE, -11136, 316, -5001, 0, -90, 0, (0x0A << 16), bhvInstantActiveWarp),
		TERRAIN(a_area_4_collision),
		MACRO_OBJECTS(a_area_4_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_WATER),
		TERRAIN_TYPE(TERRAIN_SAND),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(5, a_area_5),
		WARP_NODE(0x0E, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x08, LEVEL_A, 0x04, 0x15, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_KKTABLE, 2076, -2500, -1499, 0, 0, 0, 0x00000000, bhvKKTable),
		OBJECT(MODEL_KKTABLE, 2268, -2500, -464, 0, 0, 0, 0x00000000, bhvKKTable),
		OBJECT(MODEL_KKTABLE, 4389, -2500, 20, 0, 0, 0, 0x00000000, bhvKKTable),
		OBJECT(MODEL_KKTABLE, 4652, -2500, -1311, 0, 0, 0, 0x00000000, bhvKKTable),
		OBJECT(MODEL_NONE, 3161, -2420, -2633, 0, 0, 0, (0x08 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 3161, -2500, -2074, 0, 0, 0, (0x0E << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_KKB, 4553, -2500, 279, 0, 0, 0, 0x00000000, bhvKKB),
		OBJECT(MODEL_KKB, 4202, -2500, -265, 0, 0, 0, 0x00000000, bhvKKB),
		OBJECT(MODEL_KKB, 4340, -2500, -1185, 0, 80, 0, 0x00000000, bhvKKB),
		OBJECT(MODEL_KKB, 4937, -2500, -1437, 0, 80, 0, 0x00000000, bhvKKB),
		OBJECT(MODEL_KKB, 2393, -2500, -1605, 0, 80, 0, 0x00000000, bhvKKB),
		OBJECT(MODEL_KKB, 1796, -2500, -1354, 0, 80, 0, 0x00000000, bhvKKB),
		OBJECT(MODEL_KKB, 1967, -2500, -652, 0, 30, 0, 0x00000000, bhvKKB),
		OBJECT(MODEL_KKB, 2543, -2500, -356, 0, 30, 0, 0x00000000, bhvKKB),
		OBJECT(MODEL_CONCRETE_BLOCK, 2268, -2271, -464, 0, 0, 0, (2 << 24) | (2 << 16), bhvConcreteBlock),
		OBJECT(MODEL_CONCRETE_BLOCK, 2076, -2271, -1499, 0, 0, 0, (2 << 24) | (2 << 16), bhvConcreteBlock),
		OBJECT(MODEL_CONCRETE_BLOCK, 4652, -2271, -1311, 0, 0, 0, (2 << 24) | (2 << 16), bhvConcreteBlock),
		OBJECT(MODEL_CONCRETE_BLOCK, 4389, -2271, 20, 0, 0, 0, (2 << 24) | (2 << 16), bhvConcreteBlock),
		OBJECT(MODEL_CONCRETE_BLOCK, 1380, -2500, 599, 0, 0, 0, (2 << 24) | (2 << 16), bhvConcreteBlock),
		OBJECT(MODEL_NONE, 3192, -2238, -1204, 0, 0, 0, (4 << 24), bhvHiddenStar),
		OBJECT(MODEL_ABILITY_SIGN, 3608, -2500, -1899, 0, -80, 0, (6 << 16), bhvStaticObject),
		OBJECT(MODEL_SQUIDWARD, 3192, -2626, 517, 0, 180, 0, 0x00000000, bhvSquidward),
		TERRAIN(a_area_5_collision),
		MACRO_OBJECTS(a_area_5_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_JELLYFISH_SECRET),
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
