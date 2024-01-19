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
#include "levels/f/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_f_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _f_segment_7SegmentRomStart, _f_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	LOAD_MODEL_FROM_GEO(MODEL_F_BRIEFCASE, f_briefcase_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_F_DOOR, f_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_F_KEYPAD, f_keypad_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_F_FENCE, f_fence_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_FTRINKET_1, trinket1_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_FTRINKET_2, trinket2_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_FTRINKET_3, trinket3_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BLASTWALL_1, blastwall1_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BLASTWALL_2, blastwall2_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_FDYNAMITE, fdynamite_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_FSG_KEYPAD, fsg_keypad_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_FHIDDEN, fhidden_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_GOLD_BTN_OFF, fbtnoff_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_GOLD_BTN_ON, fbtnon_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_F_SCH_BOARD_1, f_sch_board_1_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_F_SCH_BOARD_2, f_sch_board_2_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_F_TRAPDOOR, f_trapdoor_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, f_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_F, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02, LEVEL_F, 0x02, 0x04, WARP_NO_CHECKPOINT),
		WARP_NODE(0x03, LEVEL_F, 0x02, 0x05, WARP_NO_CHECKPOINT),
		WARP_NODE(0x04/*lexit*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x05/*rexit*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_CHECKPOINT_FLAG, 1238, 2271, 7015, 0, -180, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 1238, 2271, 6715, 0, -180, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_LEVEL_PIPE, -21853, 595, -7892, 0, -180, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_NONE, -22470, 960, -7892, 0, 0, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -22470, 595, -8285, 0, 0, 0, (0x04 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -13677, 595, -8285, 0, 0, 0, (0x05 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -22470, 595, -7892, 0, -90, 0, (0x0A << 16), bhvInstantActiveWarp),
		MARIO_POS(0x01, -180, -22470, 595, -7892),
		OBJECT(MODEL_NONE, -24221, 932, -6288, 0, -180, 0, (36 << 16), bhvPoleGrabbing),
		OBJECT(MODEL_NONE, -22039, 932, -6288, 0, -180, 0, (36 << 16), bhvPoleGrabbing),
		OBJECT(MODEL_NONE, -19852, 932, -6288, 0, -180, 0, (36 << 16), bhvPoleGrabbing),
		OBJECT(MODEL_NONE, -17669, 932, -6288, 0, -180, 0, (36 << 16), bhvPoleGrabbing),
		OBJECT(MODEL_NONE, -15483, 932, -6288, 0, -180, 0, (36 << 16), bhvPoleGrabbing),
		OBJECT(MODEL_NONE, -13298, 932, -6288, 0, -180, 0, (36 << 16), bhvPoleGrabbing),
		OBJECT(MODEL_NONE, -123, 2275, 7031, 0, -180, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_NONE, 77, 2275, 7031, 0, -180, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_NONE, 277, 2275, 7031, 0, -180, 0, (4 << 24), bhvStar),
		OBJECT(MODEL_NONE, 477, 2275, 7031, 0, -180, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_NONE, 677, 2275, 7031, 0, -180, 0, (6 << 24), bhvStar),
		OBJECT(MODEL_NONE, 877, 2275, 7031, 0, -180, 0, (7 << 24), bhvStar),
		OBJECT(MODEL_NONE, -22501, 595, -8786, 0, 0, 0, (10 << 24) | (2 << 16), bhvWarp),
		OBJECT(MODEL_NONE, -13677, 595, -8786, 0, 0, 0, (10 << 24) | (3 << 16), bhvWarp),
		TERRAIN(f_area_1_collision),
		ROOMS(f_area_1_collision_rooms),
		MACRO_OBJECTS(f_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_F_FRWL),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, f_area_2),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_F, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02, LEVEL_F, 0x01, 0x04, WARP_NO_CHECKPOINT),
		WARP_NODE(0x03, LEVEL_F, 0x01, 0x05, WARP_NO_CHECKPOINT),
		WARP_NODE(0x04/*lexit*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x05/*rexit*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x06/*vententer*/, LEVEL_F, 0x03, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x07/*ventexit*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY_SIGN, 2136, 151, 1698, 0, -90, 0, (ABILITY_GADGET_WATCH << 16), bhvStaticObject),
		OBJECT(MODEL_ABILITY_SIGN, 456, 545, -302, 0, -90, 0, (ABILITY_E_SHOTGUN << 16), bhvStaticObject),
		OBJECT(MODEL_F_BRIEFCASE, 501, 255, -10, 0, 0, 0, 0x00000000, bhvBriefcase),
		OBJECT(MODEL_F_BRIEFCASE, 1052, -288, 1361, 0, 0, 0, 0x00000000, bhvBriefcase),
		OBJECT(MODEL_F_BRIEFCASE, -1860, 138, 2151, 0, 0, 0, 0x00000000, bhvBriefcase),
		OBJECT(MODEL_F_BRIEFCASE, -2200, 782, -1043, 0, 0, 0, 0x00000000, bhvBriefcase),
		OBJECT(MODEL_F_BRIEFCASE, 355, -358, -3240, 0, 0, 0, 0x00000000, bhvBriefcase),
		OBJECT(MODEL_F_FENCE, -1365, 151, 1872, 0, 0, 0, (2 << 16), bhvFfence),
		OBJECT(MODEL_GOLD_BTN_OFF, -2200, 782, 1047, 0, 0, 0, 0x00000000, bhvFRocketButtonGold),
		OBJECT(MODEL_FHIDDEN, 2803, 1694, 0, 0, 0, 0, 0x00000000, bhvFhidden),
		OBJECT(MODEL_F_KEYPAD, 3956, 181, -3707, 29, 90, 0, (2 << 16), bhvKeypad),
		OBJECT(MODEL_NONE, 4215, -704, 3746, 0, -180, 0, (0x04 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 4215, -704, -3350, 0, 0, 0, (0x05 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, -1363, -429, -306, 0, -180, 0, (0x07 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 3047, 3228, -430, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 2559, 2928, -830, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 3047, 2628, -1230, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 2559, 2328, -1630, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 2559, 1750, -2030, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 3047, 1448, -2030, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 2559, 1145, -2030, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 2803, 639, -2033, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 2973, 1920, -2033, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 2803, 3120, -57, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 3047, 3228, 317, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 2559, 2928, 717, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 3047, 2628, 1117, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 2559, 2328, 1517, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 2973, 1920, 1920, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 2559, 1750, 1917, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 3047, 1448, 1917, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 2559, 1145, 1917, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_NONE, 2803, 639, 1920, 0, 0, 0, 0x00000000, bhvPoofOnWatch),
		OBJECT(MODEL_F_SCH_BOARD_1, 414, 341, -8, 0, 0, 0, 0x00000000, bhvF_SchBoard),
		OBJECT(MODEL_NONE, 3099, -147, 3096, 0, 0, 0, (2 << 24), bhvHiddenStar),
		OBJECT(MODEL_NONE, 2938, 3376, -57, 0, 0, 0, (3 << 24), bhvUVstar),
		OBJECT(MODEL_F_TRAPDOOR, -1363, 8, 5, 0, 0, 0, 0x00000000, bhvFtrapdoor),
		OBJECT(MODEL_NONE, 4215, -704, -3752, 0, 0, 0, (20 << 24) | (3 << 16), bhvWarp),
		OBJECT(MODEL_NONE, -1363, -1399, 5, 0, 0, 0, (10 << 24) | (6 << 16), bhvWarp),
		OBJECT(MODEL_NONE, 4215, -704, 4152, 0, 0, 0, (20 << 24) | (2 << 16), bhvWarp),
		TERRAIN(f_area_2_collision),
		ROOMS(f_area_2_collision_rooms),
		MACRO_OBJECTS(f_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_F_FRWL),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, f_area_3),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_F, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02, LEVEL_F, 0x02, 0x04, WARP_NO_CHECKPOINT),
		WARP_NODE(0x03, LEVEL_F, 0x02, 0x05, WARP_NO_CHECKPOINT),
		WARP_NODE(0x06/*ventleave*/, LEVEL_F, 0x02, 0x07, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, -1832, 254, 2022, 0, -180, 0, (ABILITY_GADGET_WATCH << 16), bhvAbilityUnlock),
		OBJECT(MODEL_BLASTWALL_1, -266, 341, -241, 0, 0, 0, 0x00000000, bhvFblastwall),
		OBJECT(MODEL_FDYNAMITE, -744, 230, -3573, 0, 0, 0, (1 << 24), bhvFdynamite),
		OBJECT(MODEL_F_KEYPAD, 901, 438, -1967, 0, -90, 0, (1 << 16), bhvKeypad),
		OBJECT(MODEL_NONE, 467, 243, 3180, 0, 0, 0, 0x00000000, bhvStaticObject),
		OBJECT(MODEL_NONE, -1560, 368, 3132, 0, 90, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_F_DOOR, -105, 230, -974, 0, 0, 0, (0 << 16), bhvFdoor),
		OBJECT(MODEL_F_DOOR, 1069, 230, -1946, 0, 0, 0, (1 << 16), bhvFdoor),
		OBJECT(MODEL_FTRINKET_1, -931, 483, 748, 0, 0, 0, 0x00000000, bhvFTrinket),
		OBJECT(MODEL_FTRINKET_3, 1019, 402, -2956, 0, 0, 0, 0x00000000, bhvFTrinket),
		OBJECT(MODEL_FTRINKET_2, 690, 473, 1492, 0, 0, 0, (1 << 16), bhvFTrinket),
		OBJECT(MODEL_FSG_KEYPAD, 68, 394, -946, 0, 0, 0, (0 << 16), bhvFSGkeypad),
		OBJECT(MODEL_NONE, -163, 405, -954, 0, 0, 0, (DIALOG_F_BOND1 << 16), bhvSignOnWall),
		OBJECT(MODEL_NONE, -2208, 352, 3132, 0, 0, 0, (10 << 24) | (6 << 16), bhvWarp),
		TERRAIN(f_area_3_collision),
		ROOMS(f_area_3_collision_rooms),
		MACRO_OBJECTS(f_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_F_FRWL),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, -180, -22470, 595, -7892),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
