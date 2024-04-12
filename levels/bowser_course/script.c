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
#include "levels/bowser_course/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_bowser_course_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _bowser_course_segment_7SegmentRomStart, _bowser_course_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	LOAD_MODEL_FROM_GEO(MODEL_MATPLATFORM, matplatform_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BC_TILTING, bc_tilting_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BC_WADDLE_DEE, bc_waddle_dee_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BC_JELLY, bc_jelly_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BC_HOODMONGER, bc_hoodmonger_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BC_HOODMONGER_BULLET, bc_hoodmonger_bullet_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BC_FIRESPINNER, bc_fspinner_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BC_STAIR, bc_stair_geo),
	LOAD_MODEL_FROM_GEO(MODEL_BC_STAIR_2, bc_stair_2_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, bowser_course_area_1),
		WARP_NODE(0x0A /*spawn*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(241 /*death*/, LEVEL_BOWSER_COURSE, 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(0x01 /*death entry*/, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(2/*fading warp in*/, LEVEL_BOWSER_COURSE, 0x01, 0x03, WARP_NO_CHECKPOINT),
		WARP_NODE(3/*fading warp out*/, LEVEL_BOWSER_COURSE, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY_SIGN, 9695, 5580, 7543, 0, -32, 0, (ABILITY_KNIGHT << 16), bhvStaticObject),
		OBJECT(MODEL_ABILITY_SIGN, 4106, 6004, -915, 0, 150, 0, (ABILITY_BUBBLE_HAT << 16), bhvStaticObject),
		OBJECT(MODEL_ABILITY_SIGN, -6519, 3638, 4030, 0, 50, 0, (ABILITY_AKU << 16), bhvStaticObject),
		OBJECT(MODEL_ABILITY_SIGN, -9492, 4712, 2948, 0, -2, -42, (ABILITY_PHASEWALK << 16), bhvStaticObject),
		OBJECT(MODEL_ABILITY_SIGN, -9276, 5592, -10324, 0, -43, 0, (ABILITY_SHOCK_ROCKET << 16), bhvStaticObject),
		OBJECT(MODEL_ABILITY_SIGN, -9913, 5455, -4889, 5, 165, 18, (ABILITY_SHOCK_ROCKET << 16), bhvStaticObject),
		OBJECT(MODEL_BC_FIRESPINNER, 2613, 5433, 1549, 0, 0, 0, 0x00000000, bhvBcFspinner),
		OBJECT(MODEL_BC_FIRESPINNER, -2118, 4383, 56, 0, 0, 0, 0x00000000, bhvBcFspinner),
		OBJECT(MODEL_BC_FIRESPINNER, -3722, 3638, 4243, 0, 0, 0, 0x00000000, bhvBcFspinner),
		OBJECT(MODEL_BC_FIRESPINNER, -8103, 5283, -6338, 0, 0, 0, 0x00000000, bhvBcFspinner),
		OBJECT(MODEL_BC_FIRESPINNER, -11012, 5283, -6338, 0, 0, 0, 0x00000000, bhvBcFspinner),
		OBJECT(MODEL_ROCKET_BUTTON_OFF, -9557, 5376, -4533, 90, 0, 0, (140 << 16), bhvRocketButton),
		OBJECT(MODEL_CHECKPOINT_FLAG, 8857, 3218, -6570, 0, -180, 0, 0x00000000, bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, -5233, 3638, 4213, 0, 90, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, -9557, 5592, -8374, 0, 0, 0, (2 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_NONE, 9416, 5401, 13034, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_EXCLAMATION_BOX, 9416, 4451, -6219, 0, 0, 0, (4 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 5309, 4026, -6738, 0, 0, 0, (4 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 2360, 5550, -6884, 0, 0, 0, (4 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -8089, 5046, -2614, 0, 0, 0, (4 << 16), bhvExclamationBox),
		OBJECT(MODEL_NONE, 9435, 3251, -7290, 0, 0, 0, (2 << 16), bhvFadingWarp),
		OBJECT(MODEL_NONE, 9416, 6039, 7988, 0, -180, 0, (3 << 16), bhvFadingWarp),
		OBJECT(MODEL_NONE, 7428, 3819, -9131, 0, 90, 0, 0x00000000, bhvFlamethrower),
		OBJECT(MODEL_NONE, 3018, 5122, -6449, 0, -180, 0, 0x00000000, bhvFlamethrower),
		OBJECT(MODEL_NONE, 8813, 5558, 9433, 0, 90, 0, 0x00000000, bhvFlamethrower),
		OBJECT(MODEL_NONE, 5268, 6176, -10578, 0, 90, 0, 0x00000000, bhvFlamethrower),
		OBJECT(MODEL_BC_HOODMONGER, 3511, 6006, -3222, 0, 132, 0, 0x00000000, bhvBcHoodmonger),
		OBJECT(MODEL_BC_HOODMONGER, 3663, 6188, -2383, 0, 132, 0, 0x00000000, bhvBcHoodmonger),
		OBJECT(MODEL_BC_HOODMONGER, 5035, 6054, -2728, 0, -147, 0, 0x00000000, bhvBcHoodmonger),
		OBJECT(MODEL_BC_HOODMONGER, -9557, 4761, 4213, 0, 132, 0, 0x00000000, bhvBcHoodmonger),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, 0x00000000, bhvHoodmongerAlertManager),
		OBJECT(MODEL_BC_JELLY, 7605, 4647, -9736, 0, 0, 0, 0x00000000, bhvBcJelly),
		OBJECT(MODEL_BC_JELLY, 8466, 4152, -10569, 0, 0, 0, 0x00000000, bhvBcJelly),
		OBJECT(MODEL_BC_JELLY, 8465, 5583, -10140, 0, 0, 0, 0x00000000, bhvBcJelly),
		OBJECT(MODEL_BC_JELLY, 7407, 5958, -10582, 0, 0, 0, 0x00000000, bhvBcJelly),
		OBJECT(MODEL_BC_JELLY, 6645, 5958, -9872, 0, 0, 0, 0x00000000, bhvBcJelly),
		OBJECT(MODEL_BC_JELLY, 5811, 5958, -11264, 0, 0, 0, 0x00000000, bhvBcJelly),
		OBJECT(MODEL_BC_JELLY, 4915, 4811, -6883, 0, 0, 0, 0x00000000, bhvBcJelly),
		OBJECT(MODEL_BC_JELLY, 4645, 6128, -2992, 0, 0, 0, 0x00000000, bhvBcJelly),
		OBJECT(MODEL_BC_JELLY, 3986, 6128, -2946, 0, 0, 0, 0x00000000, bhvBcJelly),
		MARIO_POS(0x01, 0, -9597, 5592, -9995),
		OBJECT(MODEL_NITRO_BOX, -6837, 3638, 4213, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -7137, 3638, 4213, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -7437, 3638, 4213, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -7737, 3638, 4213, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -8037, 3638, 4213, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -7776, 4177, 4213, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -7476, 4177, 4213, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -7176, 4177, 4213, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -6774, 5464, 4213, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -7224, 4761, 4213, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -7524, 4761, 4213, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -7824, 4761, 4213, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -8124, 4761, 4213, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -8424, 4761, 4213, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -8724, 4761, 4213, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -9024, 4761, 4213, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -9557, 4761, 2852, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -9557, 4911, 2852, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -9557, 5061, 2852, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -9557, 5211, 2852, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NITRO_BOX, -9557, 5361, 2852, 0, 0, 0, 0x00000000, bhvNitroBox),
		OBJECT(MODEL_NOTEBLOCK, 8077, 4477, -9724, 0, 0, 0, 0x00000000, bhvNoteblock),
		OBJECT(MODEL_PT_METAL_BOX, 9416, 3218, -3723, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 9416, 3218, -3523, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 9416, 3218, -3323, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 9416, 3218, -3923, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 9416, 3218, -4123, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 9416, 3677, -6019, 0, 0, 0, (1 << 16), bhvPtMetalBox),
		OBJECT(MODEL_RED_COIN, 9416, 3677, -6419, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 5965, 3659, -7187, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 4308, 5706, -2980, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 6186, 6188, -10578, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -9557, 5527, -4533, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, 9416, 5401, 13034, 0, -180, 0, (0x0A << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_BC_STAIR, -8248, 5922, -10602, 0, 0, 0, (1 << 16), bhvBcStair),
		OBJECT(MODEL_BC_STAIR, -7918, 6253, -10602, 0, 0, 0, 0x00000000, bhvBcStair),
		OBJECT(MODEL_BC_STAIR, -7588, 6583, -10602, 0, 0, 0, 0x00000000, bhvBcStair),
		OBJECT(MODEL_BC_STAIR, -7258, 6913, -10602, 0, 0, 0, 0x00000000, bhvBcStair),
		OBJECT(MODEL_BC_STAIR, -6927, 7243, -10602, 0, 0, 0, 0x00000000, bhvBcStair),
		OBJECT(MODEL_BC_STAIR, -6597, 7573, -10602, 0, 0, 0, 0x00000000, bhvBcStair),
		OBJECT(MODEL_BC_STAIR, -6267, 7903, -10602, 0, 0, 0, 0x00000000, bhvBcStair),
		OBJECT(MODEL_BC_STAIR, -5937, 8234, -10602, 0, 0, 0, 0x00000000, bhvBcStair),
		OBJECT(MODEL_BC_TILTING, 5899, 4462, -6888, 0, -90, 0, 0x00000000, bhvBcTilting),
		OBJECT(MODEL_BC_TILTING, 4020, 4766, -6888, 0, -90, 0, 0x00000000, bhvBcTilting),
		OBJECT(MODEL_BC_TILTING, 2747, 5076, -6888, 0, -90, 0, 0x00000000, bhvBcTilting),
		OBJECT(MODEL_BC_TILTING, 3410, 5724, -6888, 0, 90, 0, 0x00000000, bhvBcTilting),
		OBJECT(MODEL_BC_TILTING, -8066, 5034, -4498, 0, 180, 0, 0x00000000, bhvBcTilting),
		OBJECT(MODEL_BC_TILTING, -11048, 5034, -4498, 0, 180, 0, 0x00000000, bhvBcTilting),
		OBJECT(MODEL_BC_TILTING, -9557, 5377, -6764, 0, 180, 0, 0x00000000, bhvBcTilting),
		OBJECT(MODEL_BC_WADDLE_DEE, 8870, 3218, -7271, 0, 0, 0, 0x00000000, bhvBcWaddleDee),
		OBJECT(MODEL_BC_WADDLE_DEE, 9428, 5133, 10972, 0, 0, 0, 0x00000000, bhvBcWaddleDee),
		OBJECT(MODEL_BC_WADDLE_DEE, 4306, 5924, -4191, 0, 0, 0, 0x00000000, bhvBcWaddleDee),
		OBJECT(MODEL_BC_WADDLE_DEE, -6043, 3638, 4213, 0, -90, 0, 0x00000000, bhvBcWaddleDee),
		TERRAIN(bowser_course_area_1_collision),
		MACRO_OBJECTS(bowser_course_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -9597, 5592, -9995),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
