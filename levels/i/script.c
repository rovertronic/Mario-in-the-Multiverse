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

#include "actors/group15.h"

/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/i/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_i_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _i_segment_7SegmentRomStart, _i_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group15_yay0SegmentRomStart, _group15_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group15_geoSegmentRomStart, _group15_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_16), 
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER, hoodboomer_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER_BOMB, hoodboomer_bomb_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PIGPOT, pigpot_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_WINDMILL, windmill_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_GATE, gate_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_WOODEN_LEVER, wooden_lever_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PLUM, plum_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CAGED_TOAD, caged_toad_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PLANK_ROPE, plank_rope_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BARRIER_ROPE, barrier_rope_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BLACK_PANEL, black_panel_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_FUNKY_ROAD, funky_road_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_OPENING_WALL, opening_wall_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, i_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_X, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*to area 2*/0x0B, LEVEL_I, 0x02, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/* from area 2*/ 0x0C, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/* to area 3*/ 0x0D, LEVEL_I, 0x03, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -4522, 357, 4333, 0, 65, 0, (1 << 24) | (60 << 16), bhvRocketButton),
		OBJECT(MODEL_NONE, -3225, 791, 3199, 0, 155, 0, (2 << 24), bhvRocketButton),
		OBJECT(MODEL_NONE, 1297, -1362, -333, 0, 0, 0, (1 << 24), bhvRocketButtonGroup),
		OBJECT(MODEL_NONE, 1297, -1362, -333, 0, 0, 0, (2 << 24), bhvRocketButtonGroup),
		OBJECT(MODEL_LEVEL_PIPE, 720, 680, -4131, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_GATE, -3281, -202, 3293, 0, -25, 0, (1 << 24) | (2 << 16) | (10 << 8) | (50), bhvGrillOpenableByRocketButton),
		OBJECT(MODEL_GATE, -4542, -202, 6062, 0, -25, 0, (1 << 24) | (2 << 16) | (10 << 8) | (50), bhvGrillOpenableByRocketButton),
		OBJECT(MODEL_PIGPOT, -1250, 0, -880, 0, 31, 0, 0x00000000, bhvPigpot),
		OBJECT(MODEL_PIGPOT, -992, 0, -1257, 0, -6, 0, 0x00000000, bhvPigpot),
		OBJECT(MODEL_NONE, -2664, 890, 5253, 0, -115, 0, (12 << 16), bhvAirborneWarp),
		OBJECT(MODEL_NONE, 0, 365, -365, 0, 0, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 944, 792, -3561, 0, 0, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 574, 193, 4988, 0, 0, 0, (11 << 16), bhvWarp),
		OBJECT(MODEL_KOOPA_SHELL, 414, 680, -3248, 0, 0, 0, (50 << 24) | (13 << 16), bhvWarp),
		TERRAIN(i_area_1_collision),
		ROOMS(i_area_1_collision_rooms),
		MACRO_OBJECTS(i_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, i_area_2),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*to area 1*/0x0B, LEVEL_I, 0x01, 0x0C, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, 2306, 1860, 1562, 0, 0, 0, (ABILITY_SHOCK_ROCKET << 16), bhvAbilityUnlock),
		OBJECT(MODEL_NONE, 8271, 2583, 1576, -59, -90, 0, (1 << 24) | (60 << 16), bhvRocketButton),
		OBJECT(MODEL_NONE, 2486, 2203, -2154, 0, -90, 0, (1 << 24) | (60 << 16), bhvRocketButton),
		OBJECT(MODEL_NONE, 3021, 460, 886, 0, 0, 0, (1 << 24), bhvRocketButtonGroup),
		OBJECT(MODEL_GATE, 2308, 1640, 2832, 0, -1, 0, (1 << 24) | (2 << 16) | (10 << 8) | (50), bhvGrillOpenableByRocketButton),
		OBJECT(MODEL_STAR, 2269, 1996, 3360, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_NONE, -6620, -1129, -2108, 0, 0, 0, (10 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 2303, 1518, 4325, 0, 0, 0, (11 << 16), bhvWarp),
		TERRAIN(i_area_2_collision),
		MACRO_OBJECTS(i_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_UNDERGROUND),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, i_area_3),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B/*to area 4*/, LEVEL_I, 0x04, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY_SIGN, 426, -689, 11128, 0, 176, 0, (10 << 16), bhvStaticObject),
		OBJECT(MODEL_BARRIER_ROPE, -6305, 367, -1205, 0, 90, 0, (240 << 8), bhvBarrierAttachedToRope),
		OBJECT(MODEL_NONE, 5198, -596, 5925, 0, 0, 0, (3 << 24), bhvRocketButton),
		OBJECT(MODEL_NONE, 5199, -63, 10886, 0, -180, 0, (3 << 24), bhvRocketButton),
		OBJECT(MODEL_NONE, 5886, 1768, 5657, 0, 0, 0, (3 << 24), bhvRocketButtonGroup),
		OBJECT(MODEL_CAGED_TOAD, 606, 1815, -353, 0, 0, 0, 0x00000000, bhvCagedToad),
		OBJECT(MODEL_CAGED_TOAD, -4822, 574, -4728, 0, 0, 0, 0x00000000, bhvCagedToad),
		OBJECT(MODEL_CAGED_TOAD, -1417, 553, 11173, 0, 0, 0, 0x00000000, bhvCagedToad),
		OBJECT(MODEL_CAGED_TOAD, 3806, 790, -7838, 0, 0, 0, 0x00000000, bhvCagedToad),
		OBJECT(MODEL_NONE, 4159, -241, -1831, 0, 0, 0, (2 << 24), bhvHiddenCagedToadsStar),
		OBJECT(MODEL_CONCRETE_BLOCK, 5198, -816, 6465, 0, 0, 0, (2 << 24) | (155 << 16), bhvConcreteBlock),
		OBJECT(MODEL_GATE, 5935, 2214, 7900, 0, 135, 0, (3 << 24) | (5 << 8) | (70), bhvGrillOpenableByRocketButton),
		OBJECT(MODEL_GATE, 7072, 1352, 4295, 0, 14, 0, (3 << 24) | (5 << 8) | (70), bhvGrillOpenableByRocketButton),
		OBJECT(MODEL_HOODBOOMER, -1564, 10, 9005, 0, 0, 0, 0x00000000, bhvHoodboomer),
		OBJECT(MODEL_WOODEN_LEVER, -178, 396, 11105, 0, -90, 0, 0x00000000, bhvWoodenLever),
		OBJECT(MODEL_WOODEN_LEVER, 6909, 508, 8626, 0, 90, 0, 0x00000000, bhvWoodenLever),
		OBJECT(MODEL_OPENING_WALL, 5199, -28, 10577, 0, 0, 0, 0x00000000, bhvOpeningWall),
		OBJECT(MODEL_PIGPOT, -3469, 440, -1579, 0, -60, 0, 0x00000000, bhvPigpot),
		OBJECT(MODEL_PIGPOT, -3760, 440, -1914, 0, -14, 0, 0x00000000, bhvPigpot),
		OBJECT(MODEL_PLANK_ROPE, -6226, 663, 3631, 0, 90, 0, (240 << 8), bhvPlankAttachedToRope),
		OBJECT(MODEL_PLANK_ROPE, -4034, 1235, 331, 0, 90, 0, (240 << 8), bhvPlankAttachedToRope),
		OBJECT(MODEL_PLUM, -7055, -133, 4881, 0, 0, 0, 0x00000000, bhvPlum),
		OBJECT(MODEL_NONE, -8025, 494, -1067, 0, 0, 0, (4 << 24), bhvPlumBucket),
		OBJECT(MODEL_NONE, 8165, 2211, 6267, 0, 0, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_NONE, 5880, 626, -3184, 0, 0, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 5880, 428, -3184, 0, 0, 0, (11 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 1852, -816, 8623, 0, 90, 0, (2 << 16), bhvOpenableGrill),
		TERRAIN(i_area_3_collision),
		MACRO_OBJECTS(i_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CLEARLEAF_FOREST),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(4, i_area_4),
		INSTANT_WARP(0x00/*instant from section 1 to 2*/, 0x04, 11189, 137, 43412),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 4924, 360, 23121, 0, 0, 0, 0x00000000, bhvSkrinkingBlackDoorSpawner),
		OBJECT(MODEL_FUNKY_ROAD, 4438, 14, -2107, 0, 0, 0, 0x00000000, bhvRotatingFunkyPlatform),
		OBJECT(MODEL_FUNKY_ROAD, 5393, 14, -15933, 0, 0, 0, 0x00000000, bhvRotatingFunkyPlatform),
		OBJECT(MODEL_FUNKY_ROAD, 5443, 14, -2118, 0, 0, 0, 0x00000000, bhvRotatingFunkyPlatform),
		OBJECT(MODEL_FUNKY_ROAD, 3938, 14, -3835, 0, 0, 0, 0x00000000, bhvRotatingFunkyPlatform),
		OBJECT(MODEL_FUNKY_ROAD, 4943, 14, -3835, 0, 0, 0, 0x00000000, bhvRotatingFunkyPlatform),
		OBJECT(MODEL_FUNKY_ROAD, 5953, 14, -3835, 0, 0, 0, 0x00000000, bhvRotatingFunkyPlatform),
		OBJECT(MODEL_FUNKY_ROAD, 4429, 14, -8823, 0, 0, 0, 0x00000000, bhvRotatingFunkyPlatform),
		OBJECT(MODEL_FUNKY_ROAD, 5446, 14, -8823, 0, 0, 0, 0x00000000, bhvRotatingFunkyPlatform),
		OBJECT(MODEL_FUNKY_ROAD, 5403, 14, -12831, 0, 0, 0, 0x00000000, bhvRotatingFunkyPlatform),
		OBJECT(MODEL_FUNKY_ROAD, 5930, 14, -14336, 0, 0, 0, 0x00000000, bhvRotatingFunkyPlatform),
		OBJECT(MODEL_KOOPA_SHELL, -6251, 0, 21550, 0, 0, 0, 0x00000000, bhvFunkyShell),
		OBJECT(MODEL_STAR, 5007, 0, -6479, 0, 0, 0, (6 << 24), bhvStar),
		OBJECT(MODEL_NONE, -6251, 725, 21549, 0, -180, 0, (10 << 16), bhvInstantActiveWarp),
		TERRAIN(i_area_4_collision),
		MACRO_OBJECTS(i_area_4_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_SLIDE),
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
