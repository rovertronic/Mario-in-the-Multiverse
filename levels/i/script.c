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
#include "levels/i/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_i_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _i_segment_7SegmentRomStart, _i_segment_7SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER, hoodboomer_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER_BOMB, hoodboomer_bomb_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PIGPOT, pigpot_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER, hoodboomer_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PIGPOT, pigpot_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER, hoodboomer_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PIGPOT, pigpot_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER, hoodboomer_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PIGPOT, pigpot_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER, hoodboomer_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PIGPOT, pigpot_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER, hoodboomer_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PIGPOT, pigpot_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER, hoodboomer_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PIGPOT, pigpot_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER, hoodboomer_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PIGPOT, pigpot_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER, hoodboomer_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PIGPOT, pigpot_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER, hoodboomer_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PIGPOT, pigpot_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER, hoodboomer_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PIGPOT, pigpot_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER, hoodboomer_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PIGPOT, pigpot_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER, hoodboomer_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PIGPOT, pigpot_geo), 

	/* Fast64 begin persistent block [level commands] */
	LOAD_MODEL_FROM_GEO(MODEL_HOODBOOMER, hoodboomer_geo),
	LOAD_MODEL_FROM_GEO(MODEL_PIGPOT, pigpot_geo),
	/* Fast64 end persistent block [level commands] */

	AREA(1, i_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_X, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, -1146, 50, 1211, 0, 0, 0, (ABILITY_SHOCK_ROCKET << 16), bhvAbilityUnlock),
		OBJECT(MODEL_NONE, 1863, 521, 1539, 0, -150, 0, (1 << 24) | (60 << 16), bhvRocketButton),
		OBJECT(MODEL_NONE, 2262, 509, 346, 0, -91, 0, (2 << 24), bhvRocketButton),
		OBJECT(MODEL_NONE, 1398, 591, 1819, 0, -148, 0, (1 << 24) | (60 << 16), bhvRocketButton),
		OBJECT(MODEL_NONE, 1297, -1362, -333, 0, 0, 0, (1 << 24), bhvRocketButtonGroup),
		OBJECT(MODEL_NONE, 1297, -1362, -333, 0, 0, 0, (2 << 24), bhvRocketButtonGroup),
		OBJECT(MODEL_CHECKPOINT_FLAG, 1439, 50, -1412, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 1439, 50, -1112, 0, 0, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_LEVEL_PIPE, 0, 50, 691, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_METAL_BOX, 1357, 50, 763, 0, 0, 0, (1 << 24) | (2 << 16) | (10 << 8) | (50), bhvGrillOpenableByRocketButton),
		OBJECT(MODEL_METAL_BOX, 727, 638, -2024, 0, -112, 0, (255 << 24), bhvRotatingGearDecorative),
		OBJECT(MODEL_HOODBOOMER, -1511, 50, -2, 0, 0, 0, 0x00000000, bhvHoodboomer),
		OBJECT(MODEL_NONE, 0, 365, -365, 0, 0, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 0, 50, -761, 0, 0, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_PIGPOT, -1167, 50, -1198, 0, 31, 0, 0x00000000, bhvPigpot),
		OBJECT(MODEL_PIGPOT, -908, 50, -1574, 0, -6, 0, 0x00000000, bhvPigpot),
		OBJECT(MODEL_NONE, 1453, 164, 1474, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_NONE, 1253, 164, 1474, 0, 0, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_NONE, 1053, 164, 1474, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_NONE, 853, 164, 1474, 0, 0, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_NONE, 653, 164, 1474, 0, 0, 0, (4 << 24), bhvStar),
		OBJECT(MODEL_NONE, 453, 164, 1474, 0, 0, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_NONE, 253, 164, 1474, 0, 0, 0, (6 << 24), bhvStar),
		OBJECT(MODEL_NONE, 53, 164, 1474, 0, 0, 0, (7 << 24), bhvStar),
		TERRAIN(i_area_1_collision),
		MACRO_OBJECTS(i_area_1_macro_objs),
		STOP_MUSIC(0),
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
