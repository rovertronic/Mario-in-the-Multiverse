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
#include "levels/a/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_a_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _a_segment_7SegmentRomStart, _a_segment_7SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	LOAD_MODEL_FROM_GEO(MODEL_JELLY, jelly_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_JF_PLATFORM, jfplatform_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TAXISTOP, taxistop_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TSBOAT, boat_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TIKI_WOOD, tikibox_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_TIKI_STONE, stone_tiki_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, a_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_X, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, -1146, 50, 5451, 0, 0, 0, (ABILITY_BUBBLE_HAT << 16), bhvAbilityUnlock),
		OBJECT(MODEL_CHECKPOINT_FLAG, 1439, 50, 2828, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 1439, 50, 3128, 0, 0, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_JELLY, -2805, -153, 5461, 0, 0, 0, 0x00000000, bhvJelly),
		OBJECT(MODEL_JELLY, -3766, -198, 4509, 0, 0, 0, 0x00000000, bhvJelly),
		OBJECT(MODEL_JELLY, -4191, -83, 62, 0, 0, 0, 0x00000000, bhvJelly),
		OBJECT(MODEL_JF_PLATFORM, -1419, 637, 3323, 0, 15, 0, 0x00000000, bhvJellyfishFieldsPlatform),
		OBJECT(MODEL_JF_PLATFORM, -5459, 583, 5492, 0, -170, 0, 0x00000000, bhvJellyfishFieldsPlatform),
		OBJECT(MODEL_JF_PLATFORM, -837, 905, 6718, 0, -85, 0, 0x00000000, bhvJellyfishFieldsPlatform),
		OBJECT(MODEL_JF_PLATFORM, -3206, 583, 1417, 0, 0, 0, 0x00000000, bhvJellyfishFieldsPlatform),
		OBJECT(MODEL_NONE, -5684, -81, 4350, 0, 0, 0, (0x0 << 16), bhvTikiBox),
		OBJECT(MODEL_NONE, -5684, -81, 5104, 0, 0, 0, (0x0 << 16), bhvTikiBox),
		OBJECT(MODEL_NONE, -5684, -336, 4717, 0, 0, 0, (0x0 << 16), bhvTikiBox),
		OBJECT(MODEL_NONE, -5684, -336, 5104, 0, 0, 0, (0x0 << 16), bhvTikiBox),
		OBJECT(MODEL_NONE, -5684, -336, 4350, 0, 0, 0, (0x0 << 16), bhvTikiBox),
		OBJECT(MODEL_NONE, -5684, -81, 4717, 0, 0, 0, (0x0 << 16), bhvTikiBox),
		OBJECT(MODEL_JELLY, -3766, -92, -4402, 0, 0, 0, 0x00000000, bhvJelly),
		OBJECT(MODEL_JELLY, -5157, -92, -5749, 0, 0, 0, 0x00000000, bhvJelly),
		OBJECT(MODEL_JELLY, -4820, -92, -9696, 0, 0, 0, 0x00000000, bhvJelly),
		OBJECT(MODEL_JELLY, -2804, 541, -9219, 0, 0, 0, 0x00000000, bhvJelly),
		OBJECT(MODEL_TAXISTOP, 5180, -163, -7061, 0, -90, 0, 0x00000000, bhvTaxiStop),
		OBJECT(MODEL_LEVEL_PIPE, 1591, -163, 4557, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_NONE, 500, 365, 5075, 0, -95, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 500, 50, 5079, 0, -90, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 1453, 164, 5714, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_NONE, 1253, 164, 5714, 0, 0, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_NONE, 1053, 164, 5714, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_NONE, 853, 164, 5714, 0, 0, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_NONE, 653, 164, 5714, 0, 0, 0, (4 << 24), bhvStar),
		OBJECT(MODEL_NONE, 453, 164, 5714, 0, 0, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_NONE, 253, 164, 5714, 0, 0, 0, (6 << 24), bhvStar),
		OBJECT(MODEL_NONE, 53, 164, 5714, 0, 0, 0, (7 << 24), bhvStar),
		TERRAIN(a_area_1_collision),
		MACRO_OBJECTS(a_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_WATER),
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
