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
#include "levels/m/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_m_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _m_segment_7SegmentRomStart, _m_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, m_area_1),
		WARP_NODE(0x0A, LEVEL_M, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_M, 0x01, 0xF0, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_M, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x20, LEVEL_M, 0x02, 0x20, WARP_NO_CHECKPOINT),
		INSTANT_WARP(0x00, 0x02, -19900, 0, 0),
		INSTANT_WARP(0x01, 0x03, -9900, 5000, 0),
		OBJECT(MODEL_NONE, -6600, 2600, 11500, 0, 0, 0, 0x00F00000, bhvDeathWarp),
		OBJECT(MODEL_NONE, 0, -1000, -5500, 0, 0, 0, 0x80200000, bhvWarp),
		MARIO_POS(0x01, 0, -6600, 2600, 11500),
		OBJECT(MODEL_ABILITY, -3900, 1700, -9700, 0, 0, 0, (ABILITY_DASH_BOOSTER << 16), bhvAbilityUnlock),
		OBJECT(MODEL_LEVEL_PIPE, -6600, 2600, 12500, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_NONE, -6600, 5400, 10000, 0, 0, 0, (0 << 24), bhvStar),
		TERRAIN(m_area_1_collision),
		ROOMS(m_area_1_collision_rooms),
		MACRO_OBJECTS(m_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_ESA_VALIANT),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, m_area_2),
		WARP_NODE(0x0A, LEVEL_M, 0x02, 0x20, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_M, 0x02, 0xF0, WARP_NO_CHECKPOINT),
		WARP_NODE(0x20, LEVEL_M, 0x02, 0x20, WARP_NO_CHECKPOINT),
		INSTANT_WARP(0x01, 0x04, 0, 0, -27000),
		INSTANT_WARP(0x02, 0x02, -2000, 10700, 4700),
		INSTANT_WARP(0x03, 0x02, 2000, -10700, -4700),
		INSTANT_WARP(0x00, 0x01, 19900, 0, 0),
		OBJECT(MODEL_ABILITY_SIGN, 400, 200, 4500, 0, -135, 0, 0x00070000, bhvStaticObject),
		OBJECT(MODEL_CHECKPOINT_FLAG, 0, -350, -4900, 0, 0, 0, 0x00060000, bhvCheckpointFlag),
		OBJECT(MODEL_NONE, 0, 3600, -4400, 0, 90, 0, 0x00F00000, bhvDeathWarp),
		OBJECT(MODEL_NONE, 0, 3800, -4400, 0, 90, 0, 0x00200000, bhvInstantActiveWarp),
		OBJECT(MODEL_PT_METAL_BOX, -200, 400, 5400, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 0, 400, 5400, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 200, 400, 5400, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, -200, 600, 5400, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 0, 600, 5400, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 200, 600, 5400, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, -200, 800, 5400, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 0, 800, 5400, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 200, 800, 5400, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_NONE, 0, 100, 12500, 0, 0, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_NONE, -4300, -3100, -12700, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_NONE, -6300, 275, -9000, 0, 0, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_STAR_PIECE, 7700, -5500, -1300, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, 6700, -1000, -4400, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, 9130, -2400, -4230, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, 8100, -3400, -2400, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_STAR_PIECE, 8360, -4000, -5660, 0, 0, 0, 0x00000000, bhvStarPiece),
		OBJECT(MODEL_BLUE_COIN_SWITCH, 7700, -5400, -5000, 0, 0, 0, 0x05C00000, bhvStarPieceSwitch),
		TERRAIN(m_area_2_collision),
		ROOMS(m_area_2_collision_rooms),
		MACRO_OBJECTS(m_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_ESA_VALIANT),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, m_area_3),
		TERRAIN(m_area_3_collision),
		MACRO_OBJECTS(m_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_ESA_AMMOINEN),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(4, m_area_4),
		WARP_NODE(0x20, LEVEL_M, 0x01, 0x20, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_M, 0x01, 0xF0, WARP_NO_CHECKPOINT),
		INSTANT_WARP(0x00, 0x04, 13000, 14000, 0),
		INSTANT_WARP(0x01, 0x04, -13000, -14000, 0),
		INSTANT_WARP(0x02, 0x02, 0, 0, 27000),
		OBJECT(MODEL_ABILITY_HEART, 0, 400, -1500, 0, 0, 0, 0x00000000, bhvAbilityRecoveryHeart),
		OBJECT(MODEL_ABILITY_HEART, 0, 2400, -6500, 0, 0, 0, 0x00000000, bhvAbilityRecoveryHeart),
		OBJECT(MODEL_ABILITY_HEART, 0, 7900, -3500, 0, 0, 0, 0x00000000, bhvAbilityRecoveryHeart),
		OBJECT(MODEL_ABILITY_SIGN, 600, -2900, 900, 0, 0, 0, 0x00040000, bhvStaticObject),
		OBJECT(MODEL_ABILITY_SIGN, 400, -7000, -5300, 0, -135, 0, 0x00060000, bhvStaticObject),
		OBJECT(MODEL_CHECKPOINT_FLAG, 0, -6950, -6300, 0, 0, 0, 0x00000000, bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 2775, -7150, 7675, 0, 0, 0, 0x00010000, bhvCheckpointFlag),
		OBJECT(MODEL_NONE, 0, -7000, -7000, 0, -180, 0, 0x00F00000, bhvDeathWarp),
		OBJECT(MODEL_ROCKET_BUTTON_OFF, 0, 9400, -500, 0, -180, 0, 0x00000000, bhvRocketButton),
		OBJECT(MODEL_NONE, 0, -6800, -15800, 0, -180, 0, 0x00200000, bhvWarp),
		OBJECT(MODEL_PT_METAL_BOX, 9800, -3400, 1900, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 10000, -3400, 1900, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 10200, -3400, 1900, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 9800, -3200, 1900, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 10000, -3200, 1900, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 10200, -3200, 1900, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 9800, -3000, 1900, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 10000, -3000, 1900, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_PT_METAL_BOX, 10200, -3000, 1900, 0, 0, 0, 0x00000000, bhvPtMetalBox),
		OBJECT(MODEL_NONE, 10000, -6300, 8000, 0, 0, 0, (6 << 24), bhvStar),
		TERRAIN(m_area_4_collision),
		ROOMS(m_area_4_collision_rooms),
		MACRO_OBJECTS(m_area_4_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_ESA_SUBMERGED),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -6600, 2600, 11500),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
