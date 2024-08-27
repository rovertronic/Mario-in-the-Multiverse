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
	LOAD_YAY0(0x05, _group1_yay0SegmentRomStart, _group1_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group1_geoSegmentRomStart, _group1_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_2), 
	LOAD_MODEL_FROM_GEO(MODEL_CRANE_ARROW, crane_arrow_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PAINT_GUN, paint_gun_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CRANE_HEAD, crane_head_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CRANE, crane_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_OCTOBALL, octoball_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_STAR_BOULDER, star_boulder_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PAINT_STAIN, paint_stain_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_SPLAT_TARGET, splat_target_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TARGET_BOX, target_box_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_OCTOMISSILE, octomissile_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_FLAG, flag_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_INK_MOVING_PLATFORM, ink_moving_platform_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PAINT_BULLET, paint_bullet_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_OCTOZEPPLIN, octozepplin_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_JELLY_FISH, jelly_fish_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_OCTOBA, octoba_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, c_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_C, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_TARGET_BOX, 1915, 1992, 3966, 0, 0, 0, (1 << 16) | (1), bhvTargetBox),
		OBJECT(MODEL_TARGET_BOX, 775, 1568, 5945, 0, 0, 0, (1 << 16) | (1), bhvTargetBox),
		OBJECT(MODEL_TARGET_BOX, -5775, 695, 147, 0, 0, 0, (1 << 16), bhvTargetBox),
		OBJECT(MODEL_TARGET_BOX, -9625, 284, -3082, 0, -4, 0, (1 << 16) | (0), bhvTargetBox),
		OBJECT(MODEL_TARGET_BOX, -9125, 284, -3348, 0, -39, 0, (1 << 16), bhvTargetBox),
		OBJECT(MODEL_TARGET_BOX, -9454, 284, -3481, 0, -39, 0, (1 << 16) | (1), bhvTargetBox),
		OBJECT(MODEL_TARGET_BOX, -10084, 284, 821, 0, 26, 0, (1 << 16), bhvTargetBox),
		OBJECT(MODEL_TARGET_BOX, -4897, 284, -1994, 0, 0, 0, (1 << 16) | (1), bhvTargetBox),
		OBJECT(MODEL_TARGET_BOX, -1063, 1568, -1055, 0, 0, 0, (1 << 16), bhvTargetBox),
		OBJECT(MODEL_TARGET_BOX, 6523, 2948, 8818, 0, 0, 0, (1 << 16), bhvTargetBox),
		OBJECT(MODEL_NONE, 4729, 6014, 9275, 0, 0, 0, 0x00000000, bhvCamera),
		OBJECT(MODEL_NONE, 1515, 2416, 3128, 0, 0, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 2256, 2438, 5385, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -2300, 2529, 1579, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_CRANE, 16430, 1070, 836, 0, 28, 0, 0x00000000, bhvCrane),
		OBJECT(MODEL_NONE, 8073, 3848, 7233, 0, 0, 0, 0x00000000, bhvCraneArrowController),
		OBJECT(MODEL_STAR_BOULDER, 15153, 1798, -4310, 0, 0, 0, 0x00000000, bhvCraneRock),
		OBJECT(MODEL_STAR_BOULDER, 21782, 1664, 444, 0, 0, 0, 0x00000000, bhvCraneRock),
		OBJECT(MODEL_STAR_BOULDER, 16464, 1749, 6422, 0, 0, 0, 0x00000000, bhvCraneRock),
		OBJECT(MODEL_NONE, -1117, 4992, -7570, 0, 0, 0, 0x00000000, bhvStaticObject),
		OBJECT(MODEL_NONE, -2942, 5108, -7716, 0, 0, 0, (0 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, 4634, 2915, 927, 0, 0, 0, (1 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, 5027, 5268, -4389, 0, 0, 0, (2 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, 6893, 2859, 9859, 0, 0, 0, (3 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_NONE, 6203, 1192, -4193, 0, 0, 0, (4 << 16), bhvDreamCatalyst),
		OBJECT(MODEL_EXCLAMATION_BOX, 936, 2003, -2597, 0, 0, 0, (5 << 16), bhvExclamationBox),
		OBJECT(MODEL_LEVEL_PIPE, -1633, 1948, 7425, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_NONE, 3992, 1202, -2044, 0, 0, 0, 0x00000000, bhvFightWavesManager),
		OBJECT(MODEL_FLAG, 7315, 5815, 8991, 0, -35, 0, 0x00000000, bhvFlag),
		OBJECT(MODEL_HEAVE_HO, -3469, 1568, 3680, 0, 0, 0, 0x00000000, bhvHeaveHo),
		OBJECT(MODEL_HEAVE_HO, 8297, 3848, 8719, 0, 0, 0, 0x00000000, bhvHeaveHo),
		OBJECT(MODEL_HEAVE_HO, -6716, 284, -2558, 0, 0, 0, 0x00000000, bhvHeaveHo),
		OBJECT(MODEL_TARGET_BOX, 1327, 2039, 7584, 0, 0, 0, (1), bhvHiddenObject),
		OBJECT(MODEL_TARGET_BOX, 1327, 2039, 9293, 0, 0, 0, (1), bhvHiddenObject),
		OBJECT(MODEL_TARGET_BOX, 1327, 2039, 8404, 0, 0, 0, 0x00000000, bhvHiddenObject),
		OBJECT(MODEL_TARGET_BOX, 3985, 2039, 9293, 0, 0, 0, 0x00000000, bhvHiddenObject),
		OBJECT(MODEL_TARGET_BOX, 3192, 2039, 9293, 0, 0, 0, (1), bhvHiddenObject),
		OBJECT(MODEL_TARGET_BOX, 2322, 2039, 9293, 0, 0, 0, 0x00000000, bhvHiddenObject),
		OBJECT(MODEL_INK_MOVING_PLATFORM, -689, 1768, -7505, 0, 0, 0, 0x00000000, bhvInkMovingPlatform),
		OBJECT(MODEL_JELLY_FISH, 1589, 2133, 2044, 0, -52, 0, (1 << 16), bhvJellyFish),
		OBJECT(MODEL_JELLY_FISH, 4706, 4575, -4560, 0, 109, 0, (3 << 16), bhvJellyFish),
		OBJECT(MODEL_JELLY_FISH, 7048, 3848, 7762, 0, 51, 0, (2 << 16), bhvJellyFish),
		OBJECT(MODEL_NONE, -1254, 1948, 6701, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -1254, 2448, 6701, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_OCTOBALL, 978, 1568, -2072, 0, 0, 0, 0x00000000, bhvOctoball),
		OBJECT(MODEL_OCTOBALL, -8772, 284, 197, 0, 0, 0, 0x00000000, bhvOctoball),
		OBJECT(MODEL_OCTOBALL, -4082, 1568, 772, 0, 0, 0, 0x00000000, bhvOctoball),
		OBJECT(MODEL_OCTOBALL, 2815, 1568, 2690, 0, 0, 0, 0x00000000, bhvOctoball),
		OBJECT(MODEL_OCTOMISSILE, 1399, 1764, 1294, 0, -180, 0, 0x00000000, bhvBulletBill),
		OBJECT(MODEL_OCTOMISSILE, -5280, 868, -71, 0, 0, 0, 0x00000000, bhvBulletBill),
		OBJECT(MODEL_OCTOMISSILE, -3522, 468, -2597, 0, -90, 0, 0x00000000, bhvBulletBill),
		OBJECT(MODEL_OCTOZEPPLIN, -13528, 1704, -5551, 0, 0, 0, (7 << 24), bhvOctozepplin),
		OBJECT(MODEL_PAINT_GUN, -1050, 2308, -460, 0, 0, 0, 0x00000000, bhvPaintGun),
		OBJECT(MODEL_PAINT_GUN, -10404, 737, -2678, 0, 0, 0, 0x00000000, bhvPaintGun),
		OBJECT(MODEL_FLIPSWITCH_1, -1265, 2529, 2230, 0, 0, 0, (1 << 24), bhvFlipswitch),
		OBJECT(MODEL_FLIPSWITCH_1, -4868, 695, 2175, 0, 0, 0, (1 << 24), bhvFlipswitch),
		OBJECT(MODEL_FLIPSWITCH_1, 457, 1948, 7483, 0, 0, 0, (1 << 24), bhvFlipswitch),
		OBJECT(MODEL_FLIPSWITCH_1, -3973, 284, -2211, 0, 0, 0, (1 << 24), bhvFlipswitch),
		OBJECT(MODEL_FLIPSWITCH_1, 3224, 1992, 4216, 0, 0, 0, (1 << 24), bhvFlipswitch),
		OBJECT(MODEL_PURPLE_SWITCH, 1515, 2416, 3128, 0, 180, 0, 0x00000000, bhvFloorSwitchHiddenObjects),
		OBJECT(MODEL_RED_COIN_NO_SHADOW, -3619, 1931, -7442, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN_NO_SHADOW, -2181, 2735, -7442, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN_NO_SHADOW, -4023, 2650, -7442, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN_NO_SHADOW, -2177, 3153, -7442, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN_NO_SHADOW, -4536, 4326, -7442, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN_NO_SHADOW, -3041, 4683, -7442, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN_NO_SHADOW, -2184, 4666, -7442, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN_NO_SHADOW, -2667, 3679, -7442, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, -2864, 1094, -5895, 0, 0, 0, (2 << 24), bhvHiddenRedCoinStar),
		OBJECT(MODEL_STAR, -9195, 548, 6641, 0, 0, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_STAR, 4634, 2183, 927, 0, 0, 0, (6 << 24), bhvStar),
		OBJECT(MODEL_SPLAT_TARGET, -669, 5549, 927, 1, 45, -1, 0x00000000, bhvLevelSplatoonTarget),
		OBJECT(MODEL_SPLAT_TARGET, 1198, 4980, -932, 1, 45, -1, 0x00000000, bhvLevelSplatoonTarget),
		OBJECT(MODEL_SPLAT_TARGET, 2996, 5261, -2723, 1, 45, -1, 0x00000000, bhvLevelSplatoonTarget),
		TERRAIN(c_area_1_collision),
		ROOMS(c_area_1_collision_rooms),
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
