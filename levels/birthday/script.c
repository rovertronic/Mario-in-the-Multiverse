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
#include "levels/birthday/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_birthday_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _birthday_segment_7SegmentRomStart, _birthday_segment_7SegmentRomEnd), 
	LOAD_YAY0(0xa, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group10_yay0SegmentRomStart, _group10_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group10_geoSegmentRomStart, _group10_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group15_yay0SegmentRomStart, _group15_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group15_geoSegmentRomStart, _group15_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_11), 
	JUMP_LINK(script_func_global_16), 
	LOAD_MODEL_FROM_GEO(MODEL_INTRO_BREAKDOOR, intro_breakdoor_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_INTRO_CLOTH, intro_cloth_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_INTRO_ROCK, intro_rock_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, birthday_area_1),
		WARP_NODE(0x01, LEVEL_CASTLE, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_INTRO_CLOTH, -1669, -150, -610, 0, 0, 0, 0x00000000, bhvIntroCloth),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, (0 << 16), bhvCutsceneManager),
		OBJECT(MODEL_NONE, -17, 291, 1572, 26, -180, 0, (0 << 16), bhvCutsceneCamera),
		OBJECT(MODEL_NONE, 440, 399, 31, 12, -159, 0, (1 << 16), bhvCutsceneCamera),
		OBJECT(MODEL_NONE, -17, -271, 462, 4, 0, 0, (2 << 16), bhvCutsceneCamera),
		OBJECT(MODEL_NONE, -642, 81, -252, 6, -94, 0, (3 << 16), bhvCutsceneCamera),
		OBJECT(MODEL_NONE, 979, 243, -421, -10, 155, 0, (4 << 16), bhvCutsceneCamera),
		OBJECT(MODEL_NONE, -1200, 31, -689, 0, -49, 0, (5 << 16), bhvCutsceneCamera),
		OBJECT(MODEL_NONE, -1564, 20, -544, 0, 52, 0, (6 << 16), bhvCutsceneCamera),
		OBJECT(MODEL_NONE, 347, -297, 1272, -4, -150, 0, (7 << 16), bhvCutsceneCamera),
		OBJECT(MODEL_EGADD, -1687, -150, -230, 0, 90, 0, 0x00000000, bhvIntroEgadd),
		OBJECT(MODEL_INTRO_BREAKDOOR, 1477, 339, -1162, 0, 0, 0, 0x00000000, bhvIntroBreakdoor),
		MARIO_POS(0x01, 0, -20, -383, 805),
		OBJECT(MODEL_PEACH, 251, 129, -540, 0, 14, 0, 0x00000000, bhvIntroPeach),
		OBJECT(MODEL_TOAD, -362, -337, 364, 0, 37, 0, 0x00000000, bhvIntroToad),
		OBJECT(MODEL_TOAD, 521, -337, 346, 0, -35, 0, 0x00000000, bhvIntroToad),
		OBJECT(MODEL_TOAD, 782, -337, -229, 0, -16, 0, 0x00000000, bhvIntroToad),
		OBJECT(MODEL_TOAD, -766, 129, -822, 0, -16, 0, 0x00000000, bhvIntroToad),
		OBJECT(MODEL_TOAD, 486, -337, 1258, 0, -136, 0, 0x00000000, bhvIntroToad),
		OBJECT(MODEL_TOAD, -219, -337, 1992, 0, 140, 0, 0x00000000, bhvIntroToad),
		TERRAIN(birthday_area_1_collision),
		MACRO_OBJECTS(birthday_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -20, -383, 805),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
