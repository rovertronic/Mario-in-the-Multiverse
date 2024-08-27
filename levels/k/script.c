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
#include "levels/k/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_k_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _k_segment_7SegmentRomStart, _k_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	LOAD_MODEL_FROM_GEO(MODEL_K_STRONG_TERRY, k_strong_terry_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_K_FAN, k_fan_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_K_BLOOD, k_blood_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_K_BLOOD_2, k_blood2_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_K_KAGUYA, kaguya_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_K_DISCO, k_disco_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_K_BARTENDER, k_bartender_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_K_ELECTROHEAD, electrohead_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, k_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_K, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_SSL, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(3/*clubenter*/, LEVEL_K, 0x03, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(4, LEVEL_K, 0x04, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(2, LEVEL_K, 0x02, 3, WARP_NO_CHECKPOINT),
		WARP_NODE(5/*clubexit*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_STAR_PIECE, 7944, -1734, 1122, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, 10429, -1568, 1122, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, 12968, -1685, 1162, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, 11017, -1436, 1122, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, 10063, -1568, 1136, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_CHECKPOINT_FLAG, 1675, -2351, 1657, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 11701, -1812, 4577, 0, 0, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, -1834, -410, 14363, 0, 0, 0, (2 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_NONE, 1935, -1986, 12766, 0, 0, 0, (1 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, 11744, -2565, 4764, 0, 0, 0, (2 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, 2799, 798, -9462, 0, 0, 0, (3 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, 994, -3650, -2619, 0, 0, 0, (4 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, 13911, -2633, 6548, 0, 0, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_NONE, 1820, -2421, -431, 0, 0, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_NONE, -1060, -3423, -2448, 0, 0, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_NONE, 12580, -2924, 10337, 0, 0, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_NONE, 10934, -2684, 9750, 0, 0, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_NONE, 8618, -2704, 10938, 0, 0, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_NONE, 7806, -2689, 12403, 0, 0, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_NONE, 7503, -2521, 13014, 0, 0, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_NONE, 12216, -2834, 13318, 0, 0, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_NONE, 9512, -2876, 14790, 0, 0, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_NONE, 6469, -2821, 15630, 0, 0, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_NONE, 1432, -1973, 2094, 0, 0, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 1389, -1919, 3935, 0, -180, 0, (52 << 24) | (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -5210, 487, 1761, 0, -90, 0, (5 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_RED_COIN, -2328, -41, 13879, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 94, 1202, 11050, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 709, 1715, 15678, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 1048, -1194, 14426, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -4690, -795, 11409, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -5224, -990, 16281, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_BLUE_COIN_SWITCH, 7642, -1674, 1162, 0, 0, 0, (1 << 24), bhvStarPieceSwitch),
		OBJECT(MODEL_NONE, -4386, -4702, -2571, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_NONE, -1876, -67, 11674, 0, 0, 0, (2 << 24), bhvHiddenRedCoinStar),
		OBJECT(MODEL_RED_COIN, -4192, -988, 13380, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 1956, -1450, 12224, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, -8063, 4297, -9407, 0, 0, 0, (4 << 24), bhvStar),
		OBJECT(MODEL_NONE, 13531, -2129, 12286, 0, 0, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_NONE, 1389, -1919, 4953, 0, 0, 0, (52 << 24) | (2 << 16), bhvWarp),
		OBJECT(MODEL_NONE, -4963, 571, 1773, 0, 0, 0, (3 << 16), bhvWarp),
		OBJECT(MODEL_NONE, -8138, -1399, 10291, 0, 0, 0, (4 << 16), bhvWarp),
		TERRAIN(k_area_1_collision),
		MACRO_OBJECTS(k_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_K_CHINATOWN),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, k_area_2),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_K, /*this area*/ 0x02, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_SSL, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(2, LEVEL_K, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(3, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, 5187, -9783, -6470, 0, 0, 0, (ABILITY_CHRONOS << 16), bhvAbilityUnlock),
		OBJECT(MODEL_CHECKPOINT_FLAG, 1523, -7908, -4750, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_NONE, 2168, -7247, -6909, 0, 0, 0, (0 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_LEVEL_PIPE, 1522, -10005, -12206, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_K_FAN, 2888, -7527, -4106, 0, 0, 0, 0x00000000, bhvKfan),
		OBJECT(MODEL_NONE, 4051, -6632, 3093, 0, 0, 0, (52 << 24) | (2 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 1507, -9640, -11646, 0, 0, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 4051, -6632, 2049, 0, -180, 0, (3 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 1522, -10005, -11644, 0, 0, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_K_STRONG_TERRY, 4098, -7908, -3192, 0, 14, 0, 0x00000000, bhvStrongTerry),
		TERRAIN(k_area_2_collision),
		MACRO_OBJECTS(k_area_2_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, k_area_3),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_K, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_SSL, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(2/*exit dj*/, LEVEL_K, 0x01, 5, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_K_BARTENDER, 2659, 199, -2053, 0, 0, 0, 0x00000000, bhvKbartender),
		MARIO_POS(0x03, 0, 0, 0, -539),
		OBJECT(MODEL_K_DISCO, -92, 709, -3547, 0, 0, 0, 0x00000000, bhvKDisco),
		OBJECT(MODEL_NONE, -1833, 3954, -3743, 0, 0, 0, (6 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, -697, 1495, -7019, 0, 0, 0, (5 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_K_ELECTROHEAD, 569, 2017, -6376, 0, -134, 0, (7 << 24), bhvElectrohead),
		OBJECT(MODEL_NONE, -6, 0, 650, 0, 0, 0, (42 << 24) | (2 << 16), bhvWarp),
		OBJECT(MODEL_K_KAGUYA, -156, 0, -2974, 0, 41, 0, 0x00000000, bhvKaguya),
		OBJECT(MODEL_NONE, -1241, -406, -7666, 0, -180, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_NONE, -1866, 0, -8027, 0, -180, 0, (6 << 24), bhvStar),
		OBJECT(MODEL_K_STRONG_TERRY, 434, 1617, -1957, 0, 0, 0, 0x00000000, bhvStrongTerry),
		OBJECT(MODEL_K_STRONG_TERRY, -2414, 1617, -1826, 0, 96, 0, 0x00000000, bhvStrongTerry),
		OBJECT(MODEL_K_STRONG_TERRY, -2388, 0, -1238, 0, 132, 0, 0x00000000, bhvStrongTerry),
		OBJECT(MODEL_K_STRONG_TERRY, 2523, 1617, -4012, 0, 0, 0, 0x00000000, bhvStrongTerry),
		OBJECT(MODEL_NONE, -4, 0, -638, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		TERRAIN(k_area_3_collision),
		MACRO_OBJECTS(k_area_3_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(4, k_area_4),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_K, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_SSL, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY_SIGN, 3954, -3300, 44, 0, -36, 0, (4 << 16), bhvStaticObject),
		OBJECT(MODEL_NONE, 3401, -3224, 277, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 2996, -3099, 186, 0, 0, 0, (7 << 24), bhvStar),
		TERRAIN(k_area_4_collision),
		MACRO_OBJECTS(k_area_4_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x03, 0, 0, 0, -539),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
