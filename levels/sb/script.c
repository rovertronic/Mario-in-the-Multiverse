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
#include "levels/sb/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_sb_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x7, _sb_segment_7SegmentRomStart, _sb_segment_7SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	LOAD_MODEL_FROM_GEO(MODEL_SB_STAIRS, sb_stairs_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_SB_TORCH_1, sb_torch_1_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_SB_TORCH_2, sb_torch_2_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, sb_area_1),
		MARIO_POS(0x01, 0, -4, -1971, -9425),
		OBJECT(MODEL_SB_STAIRS, -2, 0, -4835, 0, 0, 0, 0x00000000, bhvStaticObject),
		OBJECT(MODEL_SB_TORCH_1, 0, -1726, -8751, 0, 0, 0, 0x00000000, bhvSbTorch),
		OBJECT(MODEL_SB_TORCH_1, 0, -1193, -8219, 0, 0, 0, 0x00000000, bhvSbTorch),
		OBJECT(MODEL_SB_TORCH_1, 0, -660, -7686, 0, 0, 0, 0x00000000, bhvSbTorch),
		OBJECT(MODEL_SB_TORCH_1, 0, -127, -6248, 0, 0, 0, 0x00000000, bhvSbTorch),
		OBJECT(MODEL_SB_TORCH_1, 0, 405, -5716, 0, 0, 0, 0x00000000, bhvSbTorch),
		OBJECT(MODEL_SB_TORCH_1, 0, 938, -5183, 0, 0, 0, 0x00000000, bhvSbTorch),
		OBJECT(MODEL_SB_TORCH_1, 0, 1471, -3745, 0, 0, 0, 0x00000000, bhvSbTorch),
		OBJECT(MODEL_SB_TORCH_1, 0, 2004, -3213, 0, 0, 0, 0x00000000, bhvSbTorch),
		OBJECT(MODEL_SB_TORCH_1, 0, 2537, -2680, 0, 0, 0, 0x00000000, bhvSbTorch),
		TERRAIN(sb_area_1_collision),
		MACRO_OBJECTS(sb_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -4, -1971, -9425),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
