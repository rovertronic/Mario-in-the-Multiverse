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

#include "actors/common1.h"

/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/castle_inside/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_castle_inside_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _castle_inside_segment_7SegmentRomStart, _castle_inside_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _inside_yay0SegmentRomStart, _inside_yay0SegmentRomEnd), 
	LOAD_YAY0(0x06, _group15_yay0SegmentRomStart, _group15_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group15_geoSegmentRomStart, _group15_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_16), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_BOWSER_TRAP, castle_geo_000F18), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_WATER_LEVEL_PILLAR, castle_geo_001940), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_CLOCK_MINUTE_HAND, castle_geo_001530), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_CLOCK_HOUR_HAND, castle_geo_001548), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_CLOCK_PENDULUM, castle_geo_001518), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_CASTLE_DOOR, castle_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_WOODEN_DOOR, wooden_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_METAL_DOOR, metal_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_CASTLE_DOOR_UNUSED, castle_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_WOODEN_DOOR_UNUSED, wooden_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_DOOR_0_STARS, castle_door_0_star_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_DOOR_1_STAR, castle_door_1_star_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_DOOR_3_STARS, castle_door_3_stars_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_KEY_DOOR, key_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_STAR_DOOR_30_STARS, castle_geo_000F00), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_STAR_DOOR_8_STARS, castle_geo_000F00), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_STAR_DOOR_50_STARS, castle_geo_000F00), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_STAR_DOOR_70_STARS, castle_geo_000F00), 
	LOAD_MODEL_FROM_GEO(MODEL_LAYTON, layton_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HUBPLATFORM, hub_platform_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_SHOPITEM_1, shopitem1_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_SHOPITEM_2, shopitem2_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_SHOPITEM_4, shopitem4_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HUBSTARGOO, hub_stargoo_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HUBDOOR, hub_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_MORSHU, morshu_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HUB_TARGET_BOX, hub_target_box_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, castle_inside_area_1),
		WARP_NODE(20 /*exits 20-34*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(21, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(22, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(23, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(24, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(25, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(26, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(27, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(28, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(29, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(30, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(31, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(32, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(33, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(34 /*end exits*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(35/*enter bowser course*/, LEVEL_BOWSER_COURSE, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1/*death*/, LEVEL_CASTLE, 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(0x01 /*death entry*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_SHOPITEM_4, -8342, 3087, 93, 0, 90, 0, 0x00000000, bhvAArtifactOnMachine),
		OBJECT(MODEL_NONE, -2062, 1859, -687, 0, 0, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_EGADD, -7982, 2658, 439, 0, 117, 0, 0x00000000, bhvEgaddNPC),
		OBJECT(MODEL_HUBPLATFORM, -510, 2651, 1460, 0, 0, 0, 0x00000000, bhvHubPlatform),
		OBJECT(MODEL_HUBPLATFORM, -1214, 2407, 1059, 0, 0, 0, 0x00000000, bhvHubPlatform),
		OBJECT(MODEL_HUBPLATFORM, -1572, 2112, 518, 0, 0, 0, 0x00000000, bhvHubPlatform),
		OBJECT(MODEL_HUBPLATFORM, -1689, 1866, -224, 0, 0, 0, 0x00000000, bhvHubPlatform),
		OBJECT(MODEL_HUBPLATFORM, -3178, 1717, -1290, 0, 0, 0, 0x00000000, bhvHubPlatform),
		OBJECT(MODEL_HUBPLATFORM, -3670, 1838, -1526, 0, 0, 0, 0x00000000, bhvHubPlatform),
		OBJECT(MODEL_HUBPLATFORM, 6213, 1946, 0, 0, 0, 0, 0x00000000, bhvHubPlatform),
		OBJECT(MODEL_HUBPLATFORM, 6553, 2131, -484, 0, 0, 0, 0x00000000, bhvHubPlatform),
		OBJECT(MODEL_HUBPLATFORM, 6596, 2410, 248, 0, 0, 0, 0x00000000, bhvHubPlatform),
		OBJECT(MODEL_LAYTON, -1021, 1612, 2276, 0, 154, 0, 0x00000000, bhvLayton),
		OBJECT(MODEL_NONE, -5118, 2394, -1653, 0, 0, 0, (20 << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, -2212, 2394, -5474, 0, -161, 0, (21 << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 2116, 2335, -5289, 0, 168, 0, (23 << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, -1793, 2870, 4750, 0, 128, 0, (24 << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 5580, 3076, -5236, 0, -52, 0, (29 << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 5943, 3158, 5263, 0, -118, 0, (30 << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, -118, 3159, -7456, 0, -2, 0, (31 << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 43, 3158, 7481, 0, -177, 0, (32 << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, -5354, 3158, -5403, 0, 46, 0, (33 << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 7228, 3158, -195, 0, -104, 0, (28 << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 2553, 2394, 5033, 0, 179, 0, (26 << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, -5317, 3212, 5280, 0, 143, 0, (34 << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, -4636, 2543, 2304, 0, 82, 0, (22 << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 5387, 3484, 1732, 0, -51, 0, (27 << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 4652, 3209, -2098, 0, -131, 0, (25 << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_LEVEL_PIPE, -5118, 1994, -2127, 0, 0, 0, (0 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, -2106, 1994, -4987, 0, 0, 0, (1 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, 2024, 1994, -4793, 0, 0, 0, (3 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, -2051, 2594, 4976, 0, 0, 0, (4 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, 5782, 2658, -5383, 0, 0, 0, (9 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, 6395, 2658, 5665, 0, 0, 0, (10 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, -90, 2659, -7855, 0, 0, 0, (11 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, 53, 2778, 7971, 0, 0, 0, (12 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, -5515, 2658, -5852, 0, 0, 0, (13 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, 7562, 2658, -24, 0, 0, 0, (8 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, 1701, 1994, 4651, 0, 0, 0, (6 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, -5572, 2658, 5559, 0, 0, 0, (14 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, -5341, 1994, 2188, 0, 0, 0, (2 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, 5009, 2572, 2045, 0, 0, 0, (7 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, 5303, 3173, -1580, 0, 0, 0, (5 << 16), bhvLevelPipe),
		MARIO_POS(0x01, 0, -2062, 1612, -687),
		OBJECT(MODEL_MORSHU, 0, 2994, 0, 0, 0, 0, 0x00000000, bhvMorshu),
		OBJECT(MODEL_NITRO_BOX, 607, 2658, -8024, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -584, 2658, -7787, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NONE, -5639, 2533, -1813, 0, 0, 0, (1 << 24), bhvBowserCourseRedCoinStar),
		OBJECT(MODEL_RED_COIN, -2238, 4340, -4222, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 2024, 3058, -4793, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 4869, 2204, -1925, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 1913, 3584, 5205, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 582, 4176, -10281, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 6238, 2658, -5952, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 8550, 3997, 106, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 5291, 3263, 5862, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, 0, 2994, 0, 0, 0, 0, 0x00000000, bhvShopController),
		OBJECT(MODEL_STAR, -230, 3486, -191, 0, 0, 0, (2 << 16), bhvShopItem),
		OBJECT(MODEL_STAR, -265, 3315, 36, 0, 0, 0, (0 << 16), bhvShopItem),
		OBJECT(MODEL_STAR, 260, 3360, 63, 0, 0, 0, (1 << 16), bhvShopItem),
		OBJECT(MODEL_STAR, 295, 3531, 257, 0, 0, 0, (3 << 16), bhvShopItem),
		OBJECT(MODEL_STAR, 213, 3596, -284, 0, 0, 0, (4 << 16), bhvShopItem),
		OBJECT(MODEL_HUBDOOR, -8171, 2658, 162, 0, 0, 0, 0x00000000, bhvHubDoor),
		OBJECT(MODEL_HUBSTARGOO, -8293, 2751, 299, 0, 0, 0, 0x00000000, bhvStarGoo),
		OBJECT(MODEL_HUB_TARGET_BOX, -5126, 1994, 1688, 0, -16, 0, 0x00000000, bhvHubTargetBox),
		OBJECT(MODEL_NONE, -8399, 2700, 93, 0, 0, 0, (35 << 16), bhvWarp),
		TERRAIN(castle_inside_area_1_collision),
		MACRO_OBJECTS(castle_inside_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -2062, 1612, -687),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
