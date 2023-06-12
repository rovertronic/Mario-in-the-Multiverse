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
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
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

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, castle_inside_area_1),
		OBJECT(MODEL_ABILITY, -365, 0, 2423, 0, 142, 0, (ABILITY_ESTEEMED_MORTAL << 16), bhvAbilityUnlock),

		//2 blank objects for testing
												   /*0 is BehParam2*/
		OBJECT(MODEL_NITRO_BOX, -601, 0, 1572, 0, 94, 0, (0 << 16), bhvNitroBox),
		OBJECT(MODEL_NONE, -601, 0, 1061, 0, 87, 0, (0 << 16), bhvStaticObject),

		OBJECT(MODEL_LEVEL_PIPE, 800, 0, -2600, 0, 0, 0, (0 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, 800, 0, -2000, 0, 0, 0, (1 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, 800, 0, -1400, 0, 0, 0, (2 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, 800, 0, -800, 0, 0, 0, (3 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, 800, 0, -200, 0, 0, 0, (4 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, 800, 0, 400, 0, 0, 0, (5 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, 800, 0, 1000, 0, 0, 0, (6 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, 800, 0, 1600, 0, 0, 0, (7 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, 800, 0, 2200, 0, 0, 0, (8 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, -800, 0, -2600, 0, 0, 0, (9 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, -800, 0, -2000, 0, 0, 0, (10 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, -800, 0, -1400, 0, 0, 0, (11 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, -800, 0, -800, 0, 0, 0, (12 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, -800, 0, -200, 0, 0, 0, (13 << 16), bhvLevelPipe),
		OBJECT(MODEL_LEVEL_PIPE, -800, 0, 400, 0, 0, 0, (14 << 16), bhvLevelPipe),
		MARIO_POS(0x01, 0, 0, 0, 0),
		OBJECT(MODEL_ABILITY_SIGN, -787, 0, 2423, 0, 142, 0, (ABILITY_ESTEEMED_MORTAL << 16), bhvStaticObject),
		TERRAIN(castle_inside_area_1_collision),
		MACRO_OBJECTS(castle_inside_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 0, 0, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
