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
#include "levels/B/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_B_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _B_segment_7SegmentRomStart, _B_segment_7SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	LOAD_MODEL_FROM_GEO(MODEL_BIG_DADDY, bigdaddy_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_LITTLE_SISTER, little_sister_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_FLOATY, floaty_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_GAUGE, gauge_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_WATERFALL, waterfall_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_DEBRIS, debris_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_AIRLOCK, airlock_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_AIRLOCK_BUTTON, airlock_button_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_AIRLOCK_WATER, airlock_water_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CRUSHER, crusher_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TURRET_BODY, turret_body_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TURRET_HEAD, turret_head_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TURRET_BULLET, turret_bullet_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TURRET_HEAVY, turret_head_heavy_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TURRET_PLATFORM, turret_platform_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TURRET_COVER, turret_cover_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, B_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_B, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_AIRLOCK, -2688, 82, -35, 0, 0, 0, (1 << 24), bhvAirlock),
		OBJECT(MODEL_AIRLOCK_BUTTON, -2350, 195, -99, 0, 0, 0, (0 << 24), bhvAirlockButton),
		OBJECT(MODEL_AIRLOCK_BUTTON, -2350, 195, 1009, 0, 0, 0, (0 << 24), bhvAirlockButton),
		OBJECT(MODEL_AIRLOCK, -2688, 82, 1072, 0, 0, 0, (0 << 24), bhvAirlock),
		OBJECT(MODEL_AIRLOCK_WATER, -2688, 82, 520, 0, 0, 0, (0 << 24), bhvAirlockWater),
		OBJECT(MODEL_BIG_DADDY, 2259, 50, -329, 0, 0, 0, 0x00000000, bhvBigDaddy),
		OBJECT(MODEL_CHECKPOINT_FLAG, 1439, 50, -1412, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 1439, 50, -1112, 0, 0, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 1101, -1222, 2623, 0, 0, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_BLUE_COIN_SWITCH, 1270, -1222, 2969, 0, 0, 0, (2 << 24) | (60 << 16), bhvStarPieceSwitch),
		OBJECT(MODEL_STAR_PIECE, 2920, -1222, 1867, 0, 0, 0, (2 << 24) | (30 << 16), bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, 5244, -1222, 3126, 0, 0, 0, (2 << 24) | (30 << 16), bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, 3080, -1222, 4328, 0, 0, 0, (2 << 24) | (30 << 16), bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, 5079, -1222, 5495, 0, 0, 0, (2 << 24) | (30 << 16), bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, 3975, -1222, 7803, 0, 0, 0, (2 << 24) | (30 << 16), bhvStarPiece),
		OBJECT(MODEL_NONE, -1194, 50, -604, 0, 0, 0, (1 << 16), bhvCoinFormation),
		OBJECT(MODEL_CONCRETE_BLOCK, 1690, 50, -2592, 0, 0, 0, 0x00000000, bhvConcreteBlock),
		OBJECT(MODEL_CONCRETE_BLOCK, 1359, 50, -2698, 0, 0, 0, (1 << 24) | (50 << 16), bhvConcreteBlock),
		OBJECT(MODEL_CONCRETE_BLOCK, 327, 50, -2836, 0, 0, 0, (2 << 24) | (0xFF << 16), bhvConcreteBlock),
		OBJECT(MODEL_GAUGE, -3959, 82, -1554, 0, 90, 0, (5 << 24), bhvGauge),
		OBJECT(MODEL_GAUGE, 300, 82, -1254, 0, 0, 0, (6 << 24), bhvGauge),
		OBJECT(MODEL_GAUGE, 821, 82, -1254, 0, 0, 0, (7 << 24), bhvGauge),
		OBJECT(MODEL_NONE, -3580, -781, -3184, 0, 0, 0, (6 << 24), bhvWaterfallHidden),
		OBJECT(MODEL_NONE, -3580, -973, -2264, 0, 0, 0, (5 << 24), bhvWaterfallHidden),
		OBJECT(MODEL_NONE, 300, 82, -1820, 0, 0, 0, (6 << 24), bhvWaterfall),
		OBJECT(MODEL_NONE, 821, 82, -1820, 0, 0, 0, (7 << 24), bhvWaterfall),
		OBJECT(MODEL_GAUGE, -4413, 192, -3183, 0, 90, 0, (7 << 24), bhvGauge),
		OBJECT(MODEL_GAUGE, -1104, 343, -3312, 0, 0, 0, (6 << 24), bhvGauge),
		OBJECT(MODEL_NONE, -3610, -593, -4105, 0, 0, 0, (7 << 24), bhvWaterfallHidden),
		OBJECT(MODEL_CONCRETE_BLOCK, -3580, 389, -4788, 0, 0, 0, (2 << 24) | (0xFF << 16), bhvConcreteBlock),
		OBJECT(MODEL_CRUSHER, 6573, 830, -886, 0, 0, 0, (10 << 24), bhvCrusher),
		OBJECT(MODEL_CRUSHER, 7701, 830, -1116, 0, 0, 0, (6 << 24), bhvCrusher),
		OBJECT(MODEL_LEVEL_PIPE, 0, 50, 691, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_FLOATY, 1524, 82, 6138, 0, -25, 0, 0x00000000, bhvBioshockFloaty),
		OBJECT(MODEL_FLOATY, 1551, 82, 7121, 0, -88, 0, 0x00000000, bhvBioshockFloaty),
		OBJECT(MODEL_FLOATY, 972, 82, 8122, 0, -118, 0, 0x00000000, bhvBioshockFloaty),
		OBJECT(MODEL_FLOATY, -350, 82, 8263, 0, 173, 0, 0x00000000, bhvBioshockFloaty),
		OBJECT(MODEL_FLOATY, -1492, 82, 7577, 0, -139, 0, 0x00000000, bhvBioshockFloaty),
		OBJECT(MODEL_FLOATY, -1657, 82, 6514, 0, -88, 0, 0x00000000, bhvBioshockFloaty),
		OBJECT(MODEL_FLOATY, -1266, 82, 5416, 0, -44, 0, 0x00000000, bhvBioshockFloaty),
		OBJECT(MODEL_FLOATY, -434, 82, 4931, 0, -78, 0, 0x00000000, bhvBioshockFloaty),
		OBJECT(MODEL_FLOATY, -617, 82, 5970, 0, -29, 0, 0x00000000, bhvBioshockFloaty),
		OBJECT(MODEL_FLOATY, -674, 82, 7036, 0, 8, 0, 0x00000000, bhvBioshockFloaty),
		OBJECT(MODEL_FLOATY, 200, 82, 7564, 0, 51, 0, 0x00000000, bhvBioshockFloaty),
		OBJECT(MODEL_FLOATY, 805, 82, 6693, 0, 102, 0, 0x00000000, bhvBioshockFloaty),
		OBJECT(MODEL_FLOATY, 391, 82, 5855, 0, 164, 0, 0x00000000, bhvBioshockFloaty),
		OBJECT(MODEL_FLOATY, 6, 82, 6494, 0, 164, 0, 0x00000000, bhvBioshockFloaty),
		OBJECT(MODEL_RED_COIN, -616, 118, 5965, 0, 164, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -682, 118, 7038, 0, 164, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 204, 118, 7571, 0, 164, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 804, 118, 6702, 0, 164, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 1552, 118, 7126, 0, 164, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 391, 118, 5855, 0, 164, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -1490, 118, 7582, 0, 164, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 655, 118, 5190, 0, 164, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, 6, 392, 6488, 0, 164, 0, 0x00000000, bhvBowserCourseRedCoinStar),
		OBJECT(MODEL_LITTLE_SISTER, -494, 50, -333, 0, 0, 0, 0x00000000, bhvLittleSister),
		OBJECT(MODEL_NONE, 0, 365, -365, 0, 0, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -6289, 51, 455, 0, 0, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_DEBRIS, 2920, -1222, 1867, 0, 116, 0, (0 << 24), bhvDebris),
		OBJECT(MODEL_DEBRIS, 5079, -1222, 5495, 0, -36, 0, (0 << 24), bhvDebris),
		OBJECT(MODEL_DEBRIS, 3080, -1222, 4328, 0, 140, 0, (0 << 24), bhvDebris),
		OBJECT(MODEL_DEBRIS, 3975, -1222, 7803, 0, 34, 0, (0 << 24), bhvDebris),
		OBJECT(MODEL_DEBRIS, 5244, -1222, 3126, 0, 74, 0, (0 << 24), bhvDebris),
		OBJECT(MODEL_NONE, 1453, 164, 1474, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_NONE, -3580, 735, -4788, 0, 0, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_NONE, 3975, -2038, 7803, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_NONE, 853, 164, 1474, 0, 0, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_NONE, 653, 164, 1474, 0, 0, 0, (4 << 24), bhvStar),
		OBJECT(MODEL_NONE, 453, 164, 1474, 0, 0, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_NONE, 253, 164, 1474, 0, 0, 0, (6 << 24), bhvStar),
		OBJECT(MODEL_NONE, 53, 164, 1474, 0, 0, 0, (7 << 24), bhvStar),
		OBJECT(MODEL_FLOATY, 656, 82, 5195, 0, 37, 0, 0x00000000, bhvBioshockFloaty),
		OBJECT(MODEL_TURRET_PLATFORM, 3476, -180, -1814, 0, -135, 0, (0 << 16), bhvTurretPlatform),
		OBJECT(MODEL_TURRET_PLATFORM, 3476, -180, -966, 0, 135, 0, (0 << 16), bhvTurretPlatform),
		OBJECT(MODEL_TURRET_PLATFORM, 4174, -180, -1839, 0, -180, 0, (1 << 16), bhvTurretPlatform),
		OBJECT(MODEL_TURRET_PLATFORM, 1596, 831, -102, -180, -45, 0, (1 << 16), bhvTurretPlatform),
		OBJECT(MODEL_TURRET_PLATFORM, 690, 831, -83, -180, 45, 0, (0 << 16), bhvTurretPlatform),
		OBJECT(MODEL_TURRET_PLATFORM, -7532, -212, -1051, 0, -45, 0, (2 << 24) | (0 << 16) | (2 << 8), bhvTurretPlatform),
		OBJECT(MODEL_TURRET_PLATFORM, -5258, -212, -1051, 0, -135, 0, (1 << 24) | (0 << 16) | (1 << 8), bhvTurretPlatform),
		OBJECT(MODEL_TURRET_PLATFORM, -5258, -212, -623, 0, -135, 0, (1 << 24) | (0 << 16) | (1 << 8), bhvTurretPlatform),
		OBJECT(MODEL_TURRET_PLATFORM, -7532, -212, -623, 0, -45, 0, (2 << 24) | (0 << 16) | (2 << 8), bhvTurretPlatform),
		OBJECT(MODEL_TURRET_BODY, -6866, 50, -1176, 0, -90, 0, (2 << 24), bhvTurretBody),
		OBJECT(MODEL_TURRET_BODY, -6866, 50, -208, 0, 180, 0, (2 << 24), bhvTurretPanel),
		OBJECT(MODEL_TURRET_BODY, -6866, 50, -749, 0, -90, 0, (2 << 24), bhvTurretBody),
		OBJECT(MODEL_TURRET_BODY, -5972, 50, -1176, 0, -90, 0, (1 << 24), bhvTurretBody),
		OBJECT(MODEL_TURRET_BODY, -5972, 50, -208, 0, 180, 0, (1 << 24), bhvTurretPanel),
		OBJECT(MODEL_TURRET_BODY, 1969, 831, -1389, -180, 90, 0, 0x00000000, bhvTurretBody),
		OBJECT(MODEL_TURRET_BODY, -5972, 50, -749, 0, -90, 0, (1 << 24), bhvTurretBody),
		TERRAIN(B_area_1_collision),
		MACRO_OBJECTS(B_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_WATER),
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
