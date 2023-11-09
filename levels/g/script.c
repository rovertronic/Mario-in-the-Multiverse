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
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"
#include "actors/common1.h"

/* Fast64 begin persistent block [includes] */
#include "actors/common1.h"
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/g/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_g_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _g_segment_7SegmentRomStart, _g_segment_7SegmentRomEnd), 
	LOAD_YAY0(0xa, _bits_skybox_yay0SegmentRomStart, _bits_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	LOAD_MODEL_FROM_GEO(MODEL_G_SIR_KIBBLE, sir_kibble_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_STAR_BLOCK, star_block_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_STAR_PROJECTILE, star_projectile_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_CHECKER_BLOCK_1, checker_block_1_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_SPRING, g_spring_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_CUT_ROCK, g_cut_rock_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_CUT_ROCK2, g_cut_rock2_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_CUT_ROCK3, g_cut_rock3_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_CANNON, g_cannon_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_MARX, marx_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_MARX_CUTTER, g_marx_cutter_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_MARX_SEED, g_marx_seed_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_MARX_THORNS, g_marx_thorn_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_MARX_HALF_LEFT, g_marx_left_half_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_MARX_HALF_RIGHT, g_marx_right_half_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_MARX_BLACK_HOLE, g_marx_black_hole_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_MARX_ARROW, g_marx_arrow_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_MARX_MOUTH_FULL, g_marx_mouth_full_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_MARX_MOUTH_OPEN, g_marx_mouth_open_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_MARX_LASER, g_marx_laser_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_MARX_ICE_BOMB, g_marx_ice_bomb_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_MARX_ICE_RING, g_marx_ice_ring_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_MARX_BLACK_HOLE_EFFECT, g_marx_black_hole_effect_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_BRONTO_BURT, g_bronto_burt_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_MOVING_PLATFORM, g_moving_platform_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_MARX_DOOR, g_marx_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_WADDLE_DEE, g_waddle_dee_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_WARP_PIPE, warp_pipe_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, g_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_G, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_G, 0x02, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_CHECKPOINT_FLAG, -10084, 3308, -12948, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_G_WADDLE_DEE, -3059, 1788, -9944, 0, 0, 0, 0x00000000, bhvGWaddleDee),
		OBJECT(MODEL_G_WADDLE_DEE, -10203, 1732, -10329, 0, 0, 0, 0x00000000, bhvGWaddleDee),
		MARIO_POS(0x01, -180, -1155, 304, -1246),
		OBJECT(MODEL_NONE, 0, 365, -365, 0, 0, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -1155, 354, -1415, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_G_STAR_BLOCK, -1630, 3325, -12477, 0, 0, 0, 0x00000000, bhvStarProjectile),
		OBJECT(MODEL_G_STAR_BLOCK, -1370, 3332, -12184, 0, -63, 0, 0x00000000, bhvStarProjectile),
		OBJECT(MODEL_G_STAR_BLOCK, -1787, 3331, -12088, 0, 40, 0, 0x00000000, bhvStarProjectile),
		OBJECT(MODEL_NONE, -6547, -154, -12228, 0, 40, 0, 0x00000000, bhvWaterfallSoundLoop),
		OBJECT(MODEL_NONE, -419, 3308, -15123, 0, 0, 0, (40 << 24) | (11 << 16), bhvWarp),
		TERRAIN(g_area_1_collision),
		MACRO_OBJECTS(g_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_SAVE_HUT),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, g_area_2),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_G, 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_G, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_G_CHECKER_BLOCK_1, 36, 569, -1576, 0, 0, 0, 0x0000F000, bhvGAttachedBlock),
		OBJECT(MODEL_NONE, 148, -253, -309, 0, 0, 0, 0x00000000, bhvLevelGCutscenes),
		OBJECT(MODEL_NONE, 229, -258, -643, 0, 0, 0, (1 << 16), bhvLevelGCutscenes),
		OBJECT(MODEL_NONE, -1486, 500, 130, 0, 0, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -63, 500, 1623, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_G_SIR_KIBBLE, 0, 500, -527, 0, 0, 0, (1 << 16), bhvSirKibble),
		OBJECT(MODEL_G_STAR_BLOCK, 1036, 500, 750, 0, 0, 0, 0x00000000, bhvStarProjectile),
		OBJECT(MODEL_G_STAR_BLOCK, 1223, 500, 371, 0, 49, 0, 0x00000000, bhvStarProjectile),
		OBJECT(MODEL_G_STAR_BLOCK, -912, 500, -1110, 0, 96, 0, 0x00000000, bhvStarProjectile),
		OBJECT(MODEL_NONE, 32, 500, -1750, 0, -180, 0, 0x00000000, bhvGStarDoor),
		OBJECT(MODEL_G_STAR_PROJECTILE, 26, 791, -1629, 0, 90, 0, (1 << 16), bhvStarDoorStar),
		OBJECT(MODEL_G_STAR_PROJECTILE, 127, 723, -1629, 0, 90, 0, 0x00000000, bhvStarDoorStar),
		OBJECT(MODEL_G_STAR_PROJECTILE, -76, 723, -1629, 0, 90, 0, 0x00000000, bhvStarDoorStar),
		OBJECT(MODEL_G_STAR_PROJECTILE, 156, 639, -1629, 0, 90, 0, 0x00000000, bhvStarDoorStar),
		OBJECT(MODEL_G_STAR_PROJECTILE, -104, 639, -1629, 0, 90, 0, 0x00000000, bhvStarDoorStar),
		OBJECT(MODEL_G_STAR_PROJECTILE, 156, 554, -1629, 0, 90, 0, 0x00000000, bhvStarDoorStar),
		OBJECT(MODEL_G_STAR_PROJECTILE, -104, 554, -1629, 0, 90, 0, 0x00000000, bhvStarDoorStar),
		TERRAIN(g_area_2_collision),
		MACRO_OBJECTS(g_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_SAVE_HUT),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, g_area_3),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_G, 0x03, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_G, 0x04, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0C, LEVEL_G, 0x04, 0x0D, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_G_BRONTO_BURT, 4962, 4226, -1141, 0, -165, 0, 0x00000000, bhvGBrontoBurt),
		OBJECT(MODEL_G_BRONTO_BURT, 1980, 3056, -6224, 0, -122, 0, 0x00000000, bhvGBrontoBurt),
		OBJECT(MODEL_G_BRONTO_BURT, 2780, 3091, -5682, 0, -122, 0, 0x00000000, bhvGBrontoBurt),
		OBJECT(MODEL_G_BRONTO_BURT, 2780, 3375, -5682, 0, -122, 0, (2 << 16), bhvGBrontoBurt),
		OBJECT(MODEL_G_BRONTO_BURT, 5762, 5153, -865, 0, -4, 0, (2 << 16), bhvGBrontoBurt),
		OBJECT(MODEL_G_BRONTO_BURT, 4962, 4606, -1141, 0, -165, 0, (2 << 16), bhvGBrontoBurt),
		OBJECT(MODEL_G_BRONTO_BURT, 5540, 4415, -1284, 0, -148, 0, (1 << 16), bhvGBrontoBurt),
		OBJECT(MODEL_G_BRONTO_BURT, 5757, 5214, -1928, 0, -4, 0, (2 << 16), bhvGBrontoBurt),
		OBJECT(MODEL_G_BRONTO_BURT, 5767, 5153, -1412, 0, 0, 0, 0x00000000, bhvGBrontoBurt),
		OBJECT(MODEL_BLUE_COIN, 566, -682, 2558, 0, 0, 0, 0x0000F000, bhvBlueCoinJumping),
		OBJECT(MODEL_BLUE_COIN, 995, 1316, -5264, 0, 0, 0, 0x0000F000, bhvBlueCoinJumping),
		OBJECT(MODEL_G_CANNON, -2104, 3096, -10210, 0, 115, 0, 0x00000000, bhvGCannon),
		OBJECT(MODEL_PURPLE_SWITCH, -2997, 2763, -7245, 0, -30, 0, 0x00000000, bhvGCannonSwitch),
		OBJECT(MODEL_PURPLE_SWITCH, -1972, 2763, -7398, 0, 59, 0, 0x00000000, bhvGCannonSwitch),
		OBJECT(MODEL_PURPLE_SWITCH, -2628, 2763, -8792, 0, 180, 0, 0x00000000, bhvGCannonSwitch),
		OBJECT(MODEL_CHECKPOINT_FLAG, 210, 981, 202, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 410, 2763, -6702, 0, 0, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_NONE, -1003, -1636, 10508, 0, -163, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 437, -2262, 6678, 0, 178, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -306, -738, 2540, 0, 178, 0, (1 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 552, 479, 2458, 0, 178, 0, (1 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -1630, 1364, 768, 0, -101, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -5561, 2108, 383, 0, -166, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -4938, 2978, -2424, 0, -166, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -2370, 3077, -5060, 0, -166, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -5729, 4013, -6913, 0, -133, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1412, 3136, -11264, 0, -166, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 628, 3379, -8256, 0, -166, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -191, 3369, -5533, 0, 178, 0, (1 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 4598, 4021, -3125, 0, -164, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 5141, 4649, 1232, 0, 178, 0, (1 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 5693, 5182, -4, 0, 178, 0, (1 << 16), bhvCoinFormation),
		OBJECT(MODEL_G_CUT_ROCK, -2643, 4582, -8783, 0, 0, 0, (240 << 8), bhvGCutRock),
		OBJECT(MODEL_G_CUT_ROCK2, -2997, 3459, -7245, 0, 89, 0, (240 << 8), bhvGCutRock),
		OBJECT(MODEL_G_CUT_ROCK3, -1968, 4732, -7402, 0, 89, 0, (240 << 8), bhvGCutRock),
		OBJECT(MODEL_G_WADDLE_DEE, 300, -2348, 10492, 0, 0, 0, 0x00000000, bhvGWaddleDee),
		OBJECT(MODEL_G_WADDLE_DEE, 1071, -2387, 9072, 0, 0, 0, 0x00000000, bhvGWaddleDee),
		OBJECT(MODEL_G_WADDLE_DEE, 149, 849, -2907, 0, 0, 0, 0x00000000, bhvGWaddleDee),
		OBJECT(MODEL_G_WADDLE_DEE, 2583, 775, -3219, 0, 0, 0, 0x00000000, bhvGWaddleDee),
		OBJECT(MODEL_G_WADDLE_DEE, -4158, 2726, -3110, 0, 0, 0, 0x00000000, bhvGWaddleDee),
		OBJECT(MODEL_G_WADDLE_DEE, -3820, 2763, -5266, 0, 0, 0, 0x00000000, bhvGWaddleDee),
		OBJECT(MODEL_G_WADDLE_DEE, -358, 2763, -7213, 0, 0, 0, 0x00000000, bhvGWaddleDee),
		OBJECT(MODEL_G_WADDLE_DEE, 4410, 3237, -4660, 0, 0, 0, 0x00000000, bhvGWaddleDee),
		OBJECT(MODEL_NONE, 2212, -1780, -10226, 0, 0, 0, (70 << 24) | (11 << 16), bhvWarp),
		OBJECT(MODEL_LEVEL_PIPE, 909, 981, 219, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_GOOMBA, -496, -2108, 11816, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_GOOMBA, -1072, -1653, 8393, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_GOOMBA, 785, -1126, 6494, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_GOOMBA, 425, -2107, 6851, 0, 0, 0, (240 << 8), bhvGoomba),
		OBJECT(MODEL_G_SIR_KIBBLE, 875, -973, 4237, 0, 0, 0, 0x00000000, bhvSirKibble),
		OBJECT(MODEL_G_SIR_KIBBLE, 2267, 1662, 157, 0, 0, 0, 0x00000000, bhvSirKibble),
		OBJECT(MODEL_G_SIR_KIBBLE, 3154, 1662, 284, 0, 0, 0, 0x00000000, bhvSirKibble),
		OBJECT(MODEL_NONE, 520, -1861, 13853, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 530, -2205, 14095, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 3080, 2034, -8289, 0, -49, 0, (12 << 16), bhvWarpPipe),
		OBJECT(MODEL_RED_COIN, -1240, 1092, -969, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, -1332, 1530, -2249, 0, 14, 0, (1 << 24), bhvHiddenRedCoinStar),
		OBJECT(MODEL_RED_COIN, -671, 1666, -4179, 0, 14, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 2360, 695, -4630, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -671, 1350, -4179, 0, 14, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 963, 1633, -1580, 0, 14, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 2738, 1662, 168, 0, 14, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 3977, 884, -1140, 0, 14, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 2237, 758, 2273, 0, 14, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_G_SPRING, -328, -2439, 8837, 0, 0, 0, (19 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, -300, -2452, 3608, 0, 0, 0, (26 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, 3833, 3088, -3208, 0, 0, 0, (17 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, 1766, 975, -674, 0, 0, 0, (18 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, -1382, 2763, -6505, 0, 42, 0, (17 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, -1816, 3525, -6825, 0, 42, 0, (17 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, -1351, 3674, -7555, 0, 42, 0, (17 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, -1863, 4049, -7568, 0, 42, 0, (17 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, -2189, 3961, -6949, 0, 42, 0, (17 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, -2269, 4286, -7358, 0, 42, 0, (17 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, 2290, 3094, -6857, 0, 0, 0, (27 << 16) | (240 << 8), bhvGSpring),
		OBJECT(MODEL_NONE, 559, 745, 2055, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_NONE, 5818, 5204, -2822, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_NONE, 564, 5522, -11827, 0, 0, 0, (3 << 24), bhvStar),
		TERRAIN(g_area_3_collision),
		MACRO_OBJECTS(g_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_PEANUT_PLAINS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(4, g_area_4),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_BOB, 0x04, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_G, 0x04, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0C, LEVEL_G, 0x05, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0D, LEVEL_G, 0x03, 0x0C, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY_HEART, 9624, 2752, 10003, 0, -49, 0, 0x00000000, bhvAbilityRecoveryHeart),
		OBJECT(MODEL_ABILITY_HEART, -767, 3804, 9681, 0, -49, 0, 0x00000000, bhvAbilityRecoveryHeart),
		OBJECT(MODEL_ABILITY_HEART, -4490, 4767, 9773, 0, -49, 0, 0x00000000, bhvAbilityRecoveryHeart),
		OBJECT(MODEL_G_BRONTO_BURT, 1622, 570, 13911, 0, 13, 0, 0x00000000, bhvGBrontoBurt),
		OBJECT(MODEL_G_BRONTO_BURT, -12946, 732, 11850, 0, 59, 0, 0x00000000, bhvGBrontoBurt),
		OBJECT(MODEL_G_BRONTO_BURT, 6291, 801, 16362, 0, -35, 0, 0x00000000, bhvGBrontoBurt),
		OBJECT(MODEL_ROCKET_BUTTON_OFF, -18366, -338, 2664, -90, 0, 0, 0x00000000, bhvRocketButton),
		OBJECT(MODEL_ROCKET_BUTTON_OFF, -17899, 281, 9501, -90, 0, 0, 0x00000000, bhvRocketButton),
		OBJECT(MODEL_ROCKET_BUTTON_OFF, -8893, 693, -1008, -90, 0, 0, 0x00000000, bhvRocketButton),
		OBJECT(MODEL_ROCKET_BUTTON_OFF, -14601, -806, 8116, 0, -180, 0, 0x00000000, bhvRocketButton),
		OBJECT(MODEL_ROCKET_BUTTON_OFF, -10596, 1998, 5683, 0, -90, 0, 0x00000000, bhvRocketButton),
		OBJECT(MODEL_CHECKPOINT_FLAG, -9161, 446, 14013, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 8229, 2614, 10639, 0, 0, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_NONE, 3940, 3804, 9693, 0, -91, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 572, 3771, 9757, 0, -79, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, 0x00000000, bhvGreatCaveOffensiveController),
		OBJECT(MODEL_NONE, 1966, 813, 23500, 0, -91, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -5557, 3879, 17887, 0, -112, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -12624, 446, 14496, 0, -112, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -3215, 3940, 18841, 0, -112, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 8265, 3432, 9976, 0, -112, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 1599, 3036, 2376, 0, 156, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_G_WADDLE_DEE, -2323, 2598, 19668, 0, 0, 0, 0x00000000, bhvGWaddleDee),
		OBJECT(MODEL_G_WADDLE_DEE, -3498, 3511, 18618, 0, 0, 0, 0x00000000, bhvGWaddleDee),
		OBJECT(MODEL_G_WADDLE_DEE, -11059, 446, 16110, 0, 0, 0, 0x00000000, bhvGWaddleDee),
		OBJECT(MODEL_G_WADDLE_DEE, -13629, 446, 14427, 0, 0, 0, 0x00000000, bhvGWaddleDee),
		OBJECT(MODEL_ABILITY_SIGN, 7235, 808, 15721, 0, -49, 0, (5 << 16), bhvStaticObject),
		OBJECT(MODEL_ABILITY_SIGN, -13876, 237, 8376, 0, -40, 0, (4 << 16), bhvStaticObject),
		OBJECT(MODEL_NONE, 2208, 3178, 857, 0, 0, 0, (11 << 16), bhvAirborneDeathWarp),
		OBJECT(MODEL_ABILITY_SIGN, 4373, 3099, -2687, 0, -124, 0, (10 << 16), bhvStaticObject),
		OBJECT(MODEL_G_MARX_DOOR, 3751, 3761, -2503, 0, 0, 0, 0x00000000, bhvGMarxDoor),
		OBJECT(MODEL_NONE, -14374, 535, 1562, 0, 21, 0, (6 << 24), bhvGCOStar),
		OBJECT(MODEL_G_SIR_KIBBLE, 1776, -178, 8353, 0, 0, 0, 0x00000000, bhvSirKibble),
		OBJECT(MODEL_G_SIR_KIBBLE, -3547, 3511, 21660, 0, 0, 0, 0x00000000, bhvSirKibble),
		OBJECT(MODEL_G_SIR_KIBBLE, -14961, 1167, 14204, 0, 0, 0, 0x00000000, bhvSirKibble),
		OBJECT(MODEL_G_SIR_KIBBLE, -15194, 248, 6280, 0, 0, 0, 0x00000000, bhvSirKibble),
		OBJECT(MODEL_NONE, 2222, 3807, 21692, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_G_MOVING_PLATFORM, -2700, -75, 15771, 0, -90, 0, (3 << 24) | (25 << 16), bhvGMovingPlatform),
		OBJECT(MODEL_G_MOVING_PLATFORM, -4449, -396, 14676, 0, 180, 0, (3 << 24) | (15 << 16), bhvGMovingPlatform),
		OBJECT(MODEL_G_MOVING_PLATFORM, -7738, -534, 14157, 0, 0, 0, (3 << 24) | (25 << 16), bhvGMovingPlatform),
		OBJECT(MODEL_G_MOVING_PLATFORM, 1151, -470, 8402, 0, 0, 0, (3 << 24) | (30 << 16), bhvGMovingPlatform),
		OBJECT(MODEL_G_WARP_PIPE, 4962, 797, 23288, 0, -49, 0, (13 << 16), bhvWarpPipe),
		OBJECT(MODEL_NONE, -14374, 345, 1562, 0, 21, 0, 0x00000000, bhvRocketButtonGroup),
		OBJECT(MODEL_G_SPRING, -1533, 796, 20288, 0, 0, 0, (18 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, -1527, 1748, 19533, 0, 0, 0, (19 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, -2861, 2697, 20586, 0, 0, 0, (18 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, -2321, 1689, 20482, 0, 0, 0, (19 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, -1701, 2483, 19050, 0, 0, 0, (18 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, -1022, 796, 19710, 0, 0, 0, (18 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, -13955, 446, 17084, 0, 0, 0, (16 << 16), bhvGSpring),
		OBJECT(MODEL_G_SPRING, -10873, 446, 11965, 0, 0, 0, (20 << 16), bhvGSpring),
		OBJECT(MODEL_STAR_PIECE, -13496, 1313, 17125, 0, 21, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_BLUE_COIN_SWITCH, -10685, 538, 14630, 0, 21, 0, (4 << 24) | (90 << 16), bhvStarPieceSwitch),
		OBJECT(MODEL_STAR_PIECE, -14934, 1702, 14182, 0, 21, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, -10892, 1555, 11939, 0, 21, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, -10815, 818, 17301, 0, 21, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, -12868, 827, 11945, 0, 21, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR, -6556, 6991, 9637, 0, 21, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_NONE, 3328, 2734, -1692, 0, -124, 0, (50 << 24) | (12 << 16), bhvWarp),
		TERRAIN(g_area_4_collision),
		MACRO_OBJECTS(g_area_4_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_CRYSTAL_FIELD),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(5, g_area_5),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_G, 0x04, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_G, 0x04, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_G, 0x04, 0x0C, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_MARX, 90, 841, -897, 0, 0, 0, 0x00000000, bhvGMarx),
		OBJECT(MODEL_NONE, 24, 650, 779, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		TERRAIN(g_area_5_collision),
		MACRO_OBJECTS(g_area_5_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_MARX),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, -180, -1155, 304, -1246),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
