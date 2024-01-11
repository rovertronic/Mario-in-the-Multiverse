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
#include "levels/h/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_h_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _h_segment_7SegmentRomStart, _h_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x05, _group1_yay0SegmentRomStart, _group1_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group1_geoSegmentRomStart, _group1_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_15), 
	JUMP_LINK(script_func_global_2), 
	LOAD_MODEL_FROM_GEO(MODEL_HLOADER, hloader_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HGLASS, hglass_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, h_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_H, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, -5630, -1410, -581, 0, 0, 0, (ABILITY_PHASEWALK << 16), bhvAbilityUnlock),
		OBJECT(MODEL_ABILITY_SIGN, -7588, -1410, -1171, 0, 90, 0, (ABILITY_PHASEWALK << 16), bhvStaticObject),
		OBJECT(MODEL_ABILITY_SIGN, 8936, -318, 13217, 0, 25, 0, (ABILITY_HM_FLY << 16), bhvStaticObject),
		OBJECT(MODEL_ABILITY_SIGN, 11905, -3385, -7831, 0, 14, 0, (ABILITY_E_SHOTGUN << 16), bhvStaticObject),
		OBJECT(MODEL_CHECKPOINT_FLAG, -3303, -1410, -592, 0, 90, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 10329, -2218, 1671, 0, 90, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_NONE, 2106, -1410, 7095, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 3900, -2615, -7912, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 6881, -2925, -7888, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 11545, 104, 24, 0, 109, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 9037, -1410, 8492, 0, -115, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 10144, 2379, 12425, 0, -126, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 7712, -1405, 2177, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1165, 61, 6697, 0, -7, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1700, 61, 11757, 0, -7, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -11630, 61, 10089, 0, 5, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -3594, 2844, -4677, 0, 142, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 501, 1551, 146, 0, -57, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 2140, 2190, 1523, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -12902, 938, -593, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_LEVEL_PIPE, 2115, -1410, 11705, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_FLIPSWITCH_1, 13566, -1410, 11710, 0, 7, 0, (4 << 24), bhvFlipswitch),
		OBJECT(MODEL_FLIPSWITCH_1, 14344, -2506, -7400, 0, 39, 0, (4 << 24), bhvFlipswitch),
		OBJECT(MODEL_FLIPSWITCH_1, -2407, -3366, 6690, 0, -11, 0, (4 << 24), bhvFlipswitch),
		OBJECT(MODEL_HEAVE_HO, 8874, -1410, 9588, 0, 113, 0, 0x00000000, bhvHeaveHo),
		OBJECT(MODEL_HEAVE_HO, 11530, -1410, 13403, 0, 178, 0, 0x00000000, bhvHeaveHo),
		OBJECT(MODEL_HEAVE_HO, 10473, -3385, -7751, 0, -112, 0, 0x00000000, bhvHeaveHo),
		OBJECT(MODEL_HEAVE_HO, -2430, -1410, -2896, 0, 45, 0, 0x00000000, bhvHeaveHo),
		OBJECT(MODEL_HGLASS, 11735, -2208, -8718, 0, 0, 0, 0x00000000, bhvHGlass),
		OBJECT(MODEL_HLOADER, 169, -1410, 629, 0, 0, 0, 0x00000000, bhvHLoader),
		OBJECT(MODEL_HLOADER, 10978, -1410, 10905, 0, 134, 0, 0x00000000, bhvHLoader),
		OBJECT(MODEL_HLOADER, 12823, -3385, -7235, 0, -56, 0, 0x00000000, bhvHLoader),
		OBJECT(MODEL_HLOADER, -8321, -3366, 8387, 0, 134, 0, 0x00000000, bhvHLoader),
		OBJECT(MODEL_HLOADER, -4652, -3366, 8165, 0, -172, 0, 0x00000000, bhvHLoader),
		OBJECT(MODEL_HLOADER, -4418, -1410, -6475, 0, 119, 0, 0x00000000, bhvHLoader),
		OBJECT(MODEL_HLOADER, 3132, -1410, -3098, 0, -71, 0, 0x00000000, bhvHLoader),
		OBJECT(MODEL_HLOADER, 11673, -2218, -1420, 0, -1, 0, 0x00000000, bhvHLoader),
		OBJECT(MODEL_NONE, 2115, -886, 10467, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 2115, -1410, 10467, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		MARIO_POS(0x01, 0, 2115, -1410, 10467),
		OBJECT(MODEL_RED_COIN, 11021, -2218, 3532, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 13595, -2218, -535, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 13898, -3385, -6129, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 5140, -202, 1204, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 13377, -1735, -6618, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 6535, -1410, 10136, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 10262, -3060, -11664, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 14354, -1410, 10627, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, -11207, -1059, -574, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_NONE, 11104, -1720, 1121, 0, 0, 0, (1 << 24), bhvHiddenRedCoinStar),
		OBJECT(MODEL_NONE, 2726, 5168, -1142, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_NONE, -9932, -626, 10249, 0, 0, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_NONE, 7802, 5916, 11618, 0, 0, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_NONE, 11735, -2208, -8718, 0, 0, 0, (6 << 24), bhvStar),
		OBJECT(MODEL_NONE, -2397, 2111, -4632, 0, 0, 0, (7 << 24), bhvStar),
		OBJECT(MODEL_NONE, 4901, -1284, 3480, 0, 0, 0, (1 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 13229, -2092, 3174, 0, 0, 0, (1 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 808, -22, -4714, 0, 0, 0, (1 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 13808, 39, 10605, 0, 0, 0, (1 << 16), bhvCoinFormation),
		TERRAIN(h_area_1_collision),
		MACRO_OBJECTS(h_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 2115, -1410, 10467),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
