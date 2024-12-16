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
#include "levels/christmas/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_christmas_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _christmas_segment_7SegmentRomStart, _christmas_segment_7SegmentRomEnd), 
	LOAD_YAY0(0xa, _ccm_skybox_yay0SegmentRomStart, _ccm_skybox_yay0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, christmas_area_1),
		MARIO_POS(0x01, 0, -518, -298, -402),
		OBJECT(MODEL_NONE, -153, -219, -843, 0, 0, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NITRO_BOX, 0, -298, -1246, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_STAR, 1341, 2321, -13025, 0, 0, 0, 0x00000000, bhvStar),
		OBJECT(MODEL_BOBOMB_BUDDY, 1147, 299, -3859, 0, 0, 0, 0x00000000, bhvBobomb),
		OBJECT(MODEL_BOBOMB_BUDDY, -692, -569, -3224, 0, 0, 0, 0x00000000, bhvBobomb),
		TERRAIN(christmas_area_1_collision),
		MACRO_OBJECTS(christmas_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -518, -298, -402),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
