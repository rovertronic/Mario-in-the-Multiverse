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
#include "levels/bb/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_bb_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _bb_segment_7SegmentRomStart, _bb_segment_7SegmentRomEnd), 
	LOAD_YAY0(0xa, _cloud_floor_skybox_yay0SegmentRomStart, _cloud_floor_skybox_yay0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, bb_area_1),
		WARP_NODE(0xF1, LEVEL_BB, 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(0x01/*death entry*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 0, 8000, -9000, 0, 90, 0, (1 << 16), bhvAirborneDeathWarp),
		MARIO_POS(0x01, 90, 0, 7500, -9000),
		OBJECT(MODEL_NOTEBLOCK, 727, -512, 2038, 0, 0, 0, (0 << 16), bhvNoteblock),
		OBJECT(MODEL_NOTEBLOCK, 927, -512, 2038, 0, 0, 0, (0 << 16), bhvNoteblock),
		OBJECT(MODEL_NOTEBLOCK, 527, -512, 2038, 0, 0, 0, (0 << 16), bhvNoteblock),
		OBJECT(MODEL_NOTEBLOCK, -1234, -704, 7115, 0, 0, 0, (0 << 16), bhvNoteblock),
		OBJECT(MODEL_NOTEBLOCK, -1034, -704, 7115, 0, 0, 0, (0 << 16), bhvNoteblock),
		OBJECT(MODEL_NOTEBLOCK, -1434, -704, 7115, 0, 0, 0, (0 << 16), bhvNoteblock),
		OBJECT(MODEL_NOTEBLOCK, -7033, -1988, 7355, 0, 0, 0, (6 << 16), bhvNoteblock),
		OBJECT(MODEL_NOTEBLOCK, -6833, -1988, 7355, 0, 0, 0, (6 << 16), bhvNoteblock),
		OBJECT(MODEL_NOTEBLOCK, -7233, -1988, 7355, 0, 0, 0, (6 << 16), bhvNoteblock),
		OBJECT(MODEL_NONE, 0, 8000, -9000, 0, 90, 0, (0x0A << 16), bhvAirborneWarp),
		OBJECT(MODEL_STAR, -7753, -4151, -5565, 0, 0, 0, (0 << 24), bhvStar),
		TERRAIN(bb_area_1_collision),
		MACRO_OBJECTS(bb_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_BIGBLUE),
		TERRAIN_TYPE(TERRAIN_SLIDE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 90, 0, 7500, -9000),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
