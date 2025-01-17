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
#include "levels/J/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_J_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _J_segment_7SegmentRomStart, _J_segment_7SegmentRomEnd), 
	LOAD_YAY0(0xa, _ec_skybox_yay0SegmentRomStart, _ec_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_YAY0(0x5, _group3_yay0SegmentRomStart, _group3_yay0SegmentRomEnd), 
	LOAD_RAW(0xc, _group3_geoSegmentRomStart, _group3_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	LOAD_MODEL_FROM_GEO(MODEL_J_FALLING_PLATFORM, falling_platform_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_TILTY_HEXAGON, tilty_hexagon_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_GRAVELER, graveler_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_SKARMORY, skarmory_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_YOUNGSTER, youngster_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_SPINARAK, spinarak_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_GEODUDE, geodude_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BERRY, berry_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_HOOH, hooh_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_HOOH_ROCK, hooh_rock_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_MILTANK, miltank_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_GASTLY, gastly_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_HAUNTER, haunter_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_GENGAR, gengar_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_ELDER, elder_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_KIMONO_GIRL, kimono_girl_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_MORTY, morty_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_COWGIRL, cowgirl_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_SENTRET, sentret_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_SKIPLOOM, skiploom_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_OLD_MAN, old_man_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_SNORLAX, snorlax_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_J_MAGIKARP, magikarp_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(0, J_area_0),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_J, /*this area*/ 0x00, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x10, LEVEL_J, 0x01, 0x16, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 0, 0, 4673, 0, -180, 0, (25 << 24) | (0x10 << 16), bhvWarp),
		OBJECT(MODEL_J_GASTLY, 1350, 138, -654, 0, 0, 0, (1 << 16), bhvBoo),
		OBJECT(MODEL_J_GASTLY, 5746, 138, -6473, 0, 0, 0, (1 << 16), bhvBoo),
		OBJECT(MODEL_J_GASTLY, 383, 138, -10644, 0, 0, 0, (1 << 16), bhvBoo),
		OBJECT(MODEL_J_GASTLY, 383, 138, -14427, 0, 0, 0, (1 << 16), bhvBoo),
		OBJECT(MODEL_J_GASTLY, 821, 138, -18905, 0, 0, 0, (1 << 16), bhvBoo),
		OBJECT(MODEL_J_GENGAR, -153, 212, -22555, 0, 0, 0, (6 << 24) | (1 << 16), bhvGengar),
		OBJECT(MODEL_J_HAUNTER, 2211, 376, -4031, 0, 0, 0, (1 << 16), bhvHaunter),
		OBJECT(MODEL_J_HAUNTER, 3821, 376, -11085, 0, 0, 0, (1 << 16), bhvHaunter),
		OBJECT(MODEL_J_HAUNTER, -2933, 376, -11536, 0, 0, 0, (1 << 16), bhvHaunter),
		OBJECT(MODEL_J_HAUNTER, -6527, 1617, -11536, 0, 0, 0, (1 << 16), bhvHaunter),
		OBJECT(MODEL_J_HAUNTER, 3679, 478, -17027, 0, 0, 0, (1 << 16), bhvHaunter),
		OBJECT(MODEL_NONE, 0, 729, 3870, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 0, 0, 3878, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_ABILITY_SIGN, 508, -11, 3244, 0, 0, 0, (ABILITY_GADGET_WATCH << 16), bhvStaticObject),
		OBJECT(MODEL_J_MORTY, -186, 220, -25991, 0, 0, 0, (DIALOG_MORTY << 16), bhvMorty),
		TERRAIN(J_area_0_collision),
		MACRO_OBJECTS(J_area_0_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_GYM),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, J_area_2),
		WARP_NODE(0x0A, LEVEL_WDW, 0x02, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_J, 0x04, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_J, 0x02, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(0x01, LEVEL_J, 0x02, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0D, LEVEL_J, 0x01, 0x17, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0C, LEVEL_J, 0x02, 0x0C, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -10585, 2711, 1860, 0, 90, 0, (15 << 24) | (0x0D << 16), bhvWarp),
		OBJECT(MODEL_NONE, -10062, 2624, 1873, 0, 90, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -5538, 2624, 160, 0, 0, 0, (25 << 24) | (0x0B << 16), bhvWarp),
		OBJECT_WITH_ACTS(MODEL_NONE, -5598, 2624, 689, 0, 0, 0, (0x0C << 16), bhvInstantActiveWarp, ACT_1 | ACT_3 | ACT_4 | ACT_5 | ACT_6),
		OBJECT(MODEL_NONE, 5541, 8388, -6261, 0, -112, 0, 0x00000000, bhvBigBoulderGenerator),
		OBJECT(MODEL_NONE, 2232, 4632, -6392, 0, -90, 0, 0x00000000, bhvGravelerRamp),
		OBJECT(MODEL_CHECKPOINT_FLAG, 5676, 5624, -3388, 0, -90, 0, (4 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_NONE, 16484, 3819, -1145, 0, 90, 0, (0 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 5469, 5602, -4593, 0, 0, 0, (0 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -4740, 5324, -4764, 0, 0, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 5182, 3524, -1317, 0, 0, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -1106, 2228, 2204, 0, 0, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 2592, 7206, -5229, 0, 0, 0, (4 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, 18712, 4119, -7660, 0, 0, 0, (5 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_J_GEODUDE, -6147, 3824, -5920, 0, 0, 0, 0x00000000, bhvGeodude),
		OBJECT(MODEL_J_GEODUDE, -3611, 3824, -6013, 0, 0, 0, 0x00000000, bhvGeodude),
		OBJECT(MODEL_J_GEODUDE, -4695, 3824, -2811, 0, 0, 0, 0x00000000, bhvGeodude),
		OBJECT(MODEL_J_MAGIKARP, -1949, 2183, 2124, 0, 0, 0, 0x00000000, bhvMagikarp),
		OBJECT(MODEL_J_MAGIKARP, -43, 2183, 1271, 0, 0, 0, 0x00000000, bhvMagikarp),
		OBJECT(MODEL_J_MAGIKARP, 7829, 2183, 485, 0, 0, 0, 0x00000000, bhvMagikarp),
		OBJECT(MODEL_J_MAGIKARP, 9999, 2183, 2751, 0, 0, 0, 0x00000000, bhvMagikarp),
		OBJECT(MODEL_J_MAGIKARP, 101, 2183, 3410, 0, 0, 0, 0x00000000, bhvMagikarp),
		OBJECT(MODEL_J_MAGIKARP, -2437, 2183, 4202, 0, 0, 0, 0x00000000, bhvMagikarp),
		OBJECT(MODEL_J_MAGIKARP, 7829, 2183, 3278, 0, 0, 0, 0x00000000, bhvMagikarp),
		OBJECT(MODEL_J_MAGIKARP, 11217, 2183, 940, 0, 0, 0, 0x00000000, bhvMagikarp),
		OBJECT(MODEL_NONE, -9047, 2913, 1863, 0, 90, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_RED_COIN, 7238, 6246, -5917, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 7238, 5812, -3823, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 9255, 4719, -4735, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 10947, 5535, -3945, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 12412, 5831, -5099, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 10947, 6591, -6309, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 13977, 6642, -3777, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 13103, 7511, -6309, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, 16103, 7451, -4942, 0, 0, 0, (4 << 24) | (8 << 16), bhvHiddenRedCoinStar),
		OBJECT(MODEL_J_SENTRET, -5757, 2624, 1735, 0, 0, 0, 0x00000000, bhvSentret),
		OBJECT(MODEL_J_SENTRET, 4178, 2624, 2165, 0, 0, 0, 0x00000000, bhvSentret),
		OBJECT(MODEL_J_SENTRET, 15596, 2924, 1327, 0, 0, 0, 0x00000000, bhvSentret),
		OBJECT(MODEL_J_SKARMORY, -6346, 6856, -6893, 0, 45, 0, 0x00000000, bhvSkarmory),
		OBJECT(MODEL_J_SKARMORY, -7218, 4397, 2155, 0, 0, 0, (1 << 16), bhvSkarmory),
		OBJECT(MODEL_J_SKARMORY, 4294, 5626, 172, 0, 0, 0, (1 << 16), bhvSkarmory),
		OBJECT(MODEL_J_SKARMORY, 17818, 5780, -713, 0, -64, 0, 0x00000000, bhvSkarmory),
		OBJECT(MODEL_J_SKARMORY, 11986, 4404, 3566, 0, -177, 0, 0x00000000, bhvSkarmory),
		OBJECT(MODEL_NONE, -8651, 2849, 1016, 0, 0, 0, (5 << 24) | (5 << 16), bhvSkarmoryStarSpawner),
		OBJECT(MODEL_J_SKIPLOOM, 3554, 4360, -517, 0, 0, 0, 0x00000000, bhvSkiploom),
		OBJECT(MODEL_J_TILTY_HEXAGON, 7238, 5985, -5917, 0, 0, 0, 0x00000000, bhvTiltyHexagon),
		OBJECT(MODEL_J_TILTY_HEXAGON, 10947, 6335, -6309, 0, 0, 0, 0x00000000, bhvTiltyHexagon),
		OBJECT(MODEL_J_TILTY_HEXAGON, 9255, 4426, -4735, 0, 0, 0, 0x00000000, bhvTiltyHexagon),
		OBJECT(MODEL_J_TILTY_HEXAGON, 7238, 5485, -3823, 0, 0, 0, 0x00000000, bhvTiltyHexagon),
		OBJECT(MODEL_J_TILTY_HEXAGON, 10947, 5279, -3945, 0, 0, 0, 0x00000000, bhvTiltyHexagon),
		OBJECT(MODEL_J_TILTY_HEXAGON, 12412, 5546, -5099, 0, 0, 0, 0x00000000, bhvTiltyHexagon),
		OBJECT(MODEL_J_TILTY_HEXAGON, 13103, 7270, -6309, 0, 0, 0, 0x00000000, bhvTiltyHexagon),
		OBJECT(MODEL_J_TILTY_HEXAGON, 13977, 6363, -3777, 0, 0, 0, 0x00000000, bhvTiltyHexagon),
		OBJECT(MODEL_J_YOUNGSTER, -8653, 2624, 727, 0, 0, 0, (DIALOG_YOUNGSTER << 16), bhvYoungster),
		TERRAIN(J_area_2_collision),
		MACRO_OBJECTS(J_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_AZALEA),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, J_area_3),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_J, 0x03, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_J, /*this area*/ 0x03, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_J, 0x03, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_J, 0x01, 0x18, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 10541, 71, -93, 0, -90, 0, (15 << 24) | (0x0B << 16), bhvWarp),
		OBJECT(MODEL_NONE, 10031, 0, -98, 0, -90, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -2809, 400, 3430, 0, 90, 0, (0 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 4731, -100, 2447, 0, 90, 0, (0 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -6438, -600, 7371, 0, 90, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -9386, -200, 6014, 0, -180, 0, (0 << 16), bhvCoinFormation),
		OBJECT(MODEL_J_COWGIRL, -8056, 200, -1518, 0, 0, 0, (DIALOG_COWGIRL << 16), bhvYoungster),
		OBJECT(MODEL_NONE, -6005, 7002, 1101, 0, 0, 0, (3 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_J_MILTANK, 7829, 93, 129, 0, 56, 0, 0x00000000, bhvMiltank),
		OBJECT(MODEL_J_MILTANK, -4066, 267, -1863, 0, 0, 0, 0x00000000, bhvMiltank),
		OBJECT(MODEL_J_MILTANK, -6013, 7782, -8816, 0, 0, 0, 0x00000000, bhvMiltank),
		OBJECT(MODEL_J_MILTANK, -8346, 1290, -2547, 0, 0, 0, 0x00000000, bhvMiltank),
		OBJECT(MODEL_J_MILTANK, -6620, -536, 9194, 0, 0, 0, 0x00000000, bhvMiltank),
		OBJECT(MODEL_NONE, -8420, 486, -1624, 0, 0, 0, (1 << 24), bhvMiltankStar),
		OBJECT(MODEL_J_SENTRET, 3649, 0, -276, 0, 0, 0, 0x00000000, bhvSentret),
		OBJECT(MODEL_J_SENTRET, -6370, -600, 6559, 0, 0, 0, 0x00000000, bhvSentret),
		OBJECT(MODEL_J_SKIPLOOM, 6028, 400, 1078, 0, 0, 0, 0x00000000, bhvSkiploom),
		OBJECT(MODEL_J_SKIPLOOM, -6102, -200, 4921, 0, 0, 0, 0x00000000, bhvSkiploom),
		OBJECT(MODEL_J_SKIPLOOM, -7234, -200, 7777, 0, 0, 0, 0x00000000, bhvSkiploom),
		OBJECT(MODEL_J_SPINARAK, -5573, 3615, -8000, 0, 0, 0, 0x00000000, bhvSpinarak),
		OBJECT(MODEL_J_SPINARAK, -6459, 5363, -8000, 0, 0, 0, 0x00000000, bhvSpinarak),
		OBJECT(MODEL_J_SPINARAK, -7180, 6361, -8000, 0, 0, 0, 0x00000000, bhvSpinarak),
		TERRAIN(J_area_3_collision),
		MACRO_OBJECTS(J_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_AZALEA),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(4, J_area_4),
		WARP_NODE(0x0A, LEVEL_WDW, 0x04, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_J, 0x04, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(0x01, LEVEL_J, 0x04, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_J, 0x02, 0x0C, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -7637, 0, 5031, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -7637, 0, 5687, 0, -180, 0, (15 << 24) | (0x0B << 16), bhvWarp),
		OBJECT(MODEL_CHECKPOINT_FLAG, 2682, 4794, -5804, 0, -90, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 15521, 4441, 2626, 0, -90, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_ABILITY_SIGN, 3030, 4794, -4951, 0, -90, 0, (ABILITY_CHRONOS << 16), bhvStaticObject),
		OBJECT(MODEL_CONCRETE_BLOCK, -2872, -1950, -10976, 0, -90, 0, (2 << 24) | (140 << 16), bhvConcreteBlock),
		OBJECT(MODEL_CONCRETE_BLOCK, -7399, -685, -13613, 0, -90, 0, (2 << 24) | (140 << 16), bhvConcreteBlock),
		OBJECT(MODEL_NONE, -2659, 1778, -12626, 0, 0, 0, (6 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_J_FALLING_PLATFORM, 4632, 8552, -6713, 0, 0, 0, 0x00000000, bhvFallingPlatform),
		OBJECT(MODEL_J_FALLING_PLATFORM, 6729, 9295, -6713, 0, 0, 0, 0x00000000, bhvFallingPlatform),
		OBJECT(MODEL_J_FALLING_PLATFORM, 8789, 10229, -6713, 0, 0, 0, 0x00000000, bhvFallingPlatform),
		OBJECT(MODEL_J_FALLING_PLATFORM, 11096, 11176, -6713, 0, 0, 0, 0x00000000, bhvFallingPlatform),
		OBJECT(MODEL_J_FALLING_PLATFORM, 13280, 12026, -6713, 0, 0, 0, 0x00000000, bhvFallingPlatform),
		OBJECT(MODEL_ABILITY_SIGN, 1155, 0, -6494, 0, -26, 0, (ABILITY_HM_FLY << 16), bhvStaticObject),
		OBJECT(MODEL_ABILITY_SIGN, -9209, 0, 2891, 0, 132, 0, (ABILITY_KNIGHT << 16), bhvStaticObject),
		OBJECT(MODEL_J_MAGIKARP, -4964, 1111, -13610, 0, 0, 0, 0x00000000, bhvMagikarp),
		OBJECT(MODEL_J_MAGIKARP, -3651, 741, -11258, 0, 0, 0, 0x00000000, bhvMagikarp),
		OBJECT(MODEL_J_MAGIKARP, -6364, -1015, -11258, 0, 0, 0, 0x00000000, bhvMagikarp),
		OBJECT(MODEL_J_MAGIKARP, -7583, 31, -13721, 0, 0, 0, 0x00000000, bhvMagikarp),
		OBJECT(MODEL_J_MAGIKARP, -7583, -700, -11457, 0, 0, 0, 0x00000000, bhvMagikarp),
		OBJECT(MODEL_NONE, -7599, 265, 1910, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 15334, 2416, -5713, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_STAR_PIECE, -5235, -1155, -11480, 0, -90, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, -4431, -961, -14332, 0, -90, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, -2820, -167, -12350, 0, -90, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, -7402, -596, -13625, 0, -90, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, -2874, -1853, -10972, 0, -90, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_BLUE_COIN_SWITCH, -6356, -1950, -12533, 0, -90, 0, (3 << 24) | (120 << 16), bhvStarPieceSwitch),
		TERRAIN(J_area_4_collision),
		MACRO_OBJECTS(J_area_4_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_DARK_CAVE),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(1, J_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_J, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_J, 0x02, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0C, LEVEL_J, 0x03, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0D, LEVEL_J, 0x05, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0E, LEVEL_J, 0x01, 0x0E, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0F, LEVEL_J, 0x01, 0x10, WARP_NO_CHECKPOINT),
		WARP_NODE(0x10, LEVEL_J, 0x01, 0x10, WARP_NO_CHECKPOINT),
		WARP_NODE(0x11, LEVEL_J, 0x01, 0x12, WARP_NO_CHECKPOINT),
		WARP_NODE(0x12, LEVEL_J, 0x01, 0x12, WARP_NO_CHECKPOINT),
		WARP_NODE(0x13, LEVEL_J, 0x06, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x14, LEVEL_J, 0x01, 0x14, WARP_NO_CHECKPOINT),
		WARP_NODE(0x15, LEVEL_J, 0x00, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x16, LEVEL_J, 0x01, 0x16, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x17, LEVEL_J, 0x01, 0x17, WARP_NO_CHECKPOINT),
		WARP_NODE(0x18, LEVEL_J, 0x01, 0x18, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -3101, 1, 3606, 0, 0, 0, (0x16 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -3101, 1, 3076, 0, 0, 0, (25 << 24) | (0x15 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 5365, 64, 1928, 0, 0, 0, (25 << 24) | (0x0B << 16), bhvWarp),
		OBJECT(MODEL_NONE, -7146, 64, -99, 0, 0, 0, (25 << 24) | (0x0C << 16), bhvWarp),
		OBJECT(MODEL_NONE, -3101, 446, -3574, 0, 0, 0, (15 << 24) | (0x0D << 16), bhvWarp),
		OBJECT(MODEL_NONE, -3101, 400, -3228, 0, 0, 0, (0x0E << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 2916, 0, -5192, 0, 0, 0, (0x14 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 2916, 78, -5609, 0, 0, 0, (15 << 24) | (0x13 << 16), bhvWarp),
		OBJECT(MODEL_NONE, -450, 0, -6299, 0, 0, 0, (15 << 24) | (0x11 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 99, 3, -2968, 0, 0, 0, (15 << 24) | (0x0F << 16), bhvWarp),
		OBJECT(MODEL_NONE, 103, 0, -6303, 0, 90, 0, (0x10 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 100, 0, -2482, 0, 0, 0, (0x12 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_DRAGONITE, -3116, 2353, -3882, 0, -90, 0, (2 << 16), bhvDragonite),
		OBJECT(MODEL_NONE, -3371, 1086, -3867, 0, 0, 0, (0 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, 1108, 2051, 974, 0, 0, 0, (1 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, 2915, 6089, -5933, 0, 0, 0, (2 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_J_ELDER, 2916, 78, -5460, 0, 0, 0, (DIALOG_ELDER_BELL_TOWER << 16), bhvElder),
		OBJECT(MODEL_LEVEL_PIPE, -1116, 0, 981, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_J_KIMONO_GIRL, 1484, 0, 1497, 0, 0, 0, (DIALOG_DANCE_THEATER << 16), bhvKimonoGirl),
		OBJECT(MODEL_NONE, 0, 729, 3870, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 0, 0, 3878, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 4616, 0, 1908, 0, -90, 0, (0x17 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -6587, 0, -91, 0, 90, 0, (0x18 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_J_OLD_MAN, -3518, 0, -2601, 0, 0, 0, (DIALOG_OLD_MAN_1 << 16), bhvOldMan),
		OBJECT(MODEL_J_OLD_MAN, 898, 0, -547, 0, 0, 0, (DIALOG_OLD_MAN_2 << 16), bhvOldMan),
		OBJECT(MODEL_NONE, 2520, 5115, -5534, 0, 0, 0, (10 << 16), bhvCollectablePainting),
		OBJECT(MODEL_WOODEN_SIGNPOST, -560, 0, 1394, 0, 0, 0, (DIALOG_ECRUTEAK_SIGN << 16), bhvMessagePanel),
		OBJECT(MODEL_WOODEN_SIGNPOST, -2479, 0, -2469, 0, 0, 0, (DIALOG_BURNED_TOWER << 16), bhvMessagePanel),
		OBJECT(MODEL_J_SNORLAX, 193, -181, 4573, 0, 0, 0, 0x00000000, bhvSnorlax),
		OBJECT(MODEL_J_YOUNGSTER, -526, 0, 3461, 0, 0, 0, (DIALOG_YOUNGSTER_DRAGONITE << 16), bhvYoungster),
		TERRAIN(J_area_1_collision),
		MACRO_OBJECTS(J_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_ECRUTEAK),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(5, J_area_5),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x05, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_J, /*this area*/ 0x05, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x05, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_J, 0x01, 0x0E, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 21, 469, 2348, 0, -180, 0, (15 << 24) | (0x0B << 16), bhvWarp),
		OBJECT(MODEL_BERRY, -30, -236, -6907, 0, 0, 0, 0x00000000, bhvBerry),
		OBJECT(MODEL_DRAGONITE, 27, -1281, 31, 0, -180, 0, (0 << 24) | (1 << 16), bhvDragonite),
		OBJECT(MODEL_J_GEODUDE, -480, -881, -4015, 0, 0, 0, 0x00000000, bhvGeodude),
		OBJECT(MODEL_J_GEODUDE, 735, -881, -4015, 0, 0, 0, 0x00000000, bhvGeodude),
		OBJECT(MODEL_J_GEODUDE, 124, -881, -5047, 0, 0, 0, 0x00000000, bhvGeodude),
		OBJECT(MODEL_J_GEODUDE, -480, -881, -6022, 0, 0, 0, 0x00000000, bhvGeodude),
		OBJECT(MODEL_J_GEODUDE, 735, -881, -6022, 0, 0, 0, 0x00000000, bhvGeodude),
		OBJECT(MODEL_NONE, -2, -443, -1862, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -2, 469, 1645, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		TERRAIN(J_area_5_collision),
		MACRO_OBJECTS(J_area_5_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_UNION_CAVE),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(6, J_area_6),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x06, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_J, /*this area*/ 0x06, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x06, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_J, 0x01, 0x14, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0C, LEVEL_J, 0x07, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0D, LEVEL_J, 0x07, 0x0D, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 1141, 16808, 862, 0, 0, 0, (0x0D << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 60, 16423, 1281, 0, 0, 0, (5 << 24) | (0x0C << 16), bhvWarp),
		OBJECT(MODEL_NONE, 1982, -3572, 2007, 0, 0, 0, (7 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_HEART, 1225, 16575, -111, 0, 148, 0, 0x00000000, bhvRecoveryHeart),
		OBJECT(MODEL_J_HOOH, 0, 0, 0, 0, 0, 0, (0 << 16), bhvHooh),
		OBJECT(MODEL_J_KIMONO_GIRL, 584, 16423, 1244, 0, 148, 0, (DIALOG_KIMONO_GIRL_BELL_TOWER << 16), bhvKimonoGirl),
		OBJECT(MODEL_NONE, 11, -6675, 2001, 0, 180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 14, -7202, 1992, 0, 180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -7, -7202, 2880, 0, 0, 0, (15 << 24) | (0x0B << 16), bhvWarp),
		TERRAIN(J_area_6_collision),
		MACRO_OBJECTS(J_area_6_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_VS_HOOH),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(7, J_area_7),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x06, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_J, /*this area*/ 0x06, 0x0D, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x06, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_J, 0x01, 0x14, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_J, 0x01, 0x14, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_J_HOOH, 6, 10029, -306, 0, 180, 0, (7 << 24) | (1 << 16), bhvHooh),
		OBJECT(MODEL_NONE, 6, 10029, 2061, 0, 180, 0, (0x0A << 16), bhvInstantActiveWarp),
		TERRAIN(J_area_7_collision),
		MACRO_OBJECTS(J_area_7_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_VS_HOOH),
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
