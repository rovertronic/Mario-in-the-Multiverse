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
#include "levels/g/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_g_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _g_segment_7SegmentRomStart, _g_segment_7SegmentRomEnd), 
	LOAD_YAY0(0xa, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	LOAD_MODEL_FROM_GEO(MODEL_G_SIR_KIBBLE, sir_kibble_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_STAR_BLOCK, star_block_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_STAR_PROJECTILE, star_projectile_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_G_CHECKER_BLOCK_1, checker_block_1_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, g_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_G, 0x02, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, -1551, 436, -4278, 0, 0, 0, (ABILITY_CUTTER << 16), bhvAbilityUnlock),
		OBJECT(MODEL_LEVEL_PIPE, -1186, 329, -550, 0, 0, 0, 0x00000000, bhvLevelPipe),
		MARIO_POS(0x01, -180, -1155, 304, -1246),
		OBJECT(MODEL_NONE, 0, 365, -365, 0, 0, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -1155, 354, -1415, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_G_STAR_BLOCK, -1630, 3325, -12477, 0, 0, 0, 0x00000000, bhvStarProjectile),
		OBJECT(MODEL_G_STAR_BLOCK, -1370, 3332, -12184, 0, -63, 0, 0x00000000, bhvStarProjectile),
		OBJECT(MODEL_G_STAR_BLOCK, -1787, 3331, -12088, 0, 40, 0, 0x00000000, bhvStarProjectile),
		OBJECT(MODEL_NONE, -419, 3308, -15123, 0, 0, 0, (40 << 24) | (11 << 16), bhvWarp),
		TERRAIN(g_area_1_collision),
		MACRO_OBJECTS(g_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_SAVE_HUT),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, g_area_2),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_G, 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_G_CHECKER_BLOCK_1, 36, 569, -1576, 0, 0, 0, 0x00000000, bhvGAttachedBlock),
		OBJECT(MODEL_NONE, 148, -253, -309, 0, 0, 0, 0x00000000, bhvLevelGCutscenes),
		OBJECT(MODEL_NONE, 229, -258, -643, 0, 0, 0, (1 << 16), bhvLevelGCutscenes),
		OBJECT(MODEL_NONE, -1486, 500, 130, 0, 0, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -63, 500, 1623, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_G_SIR_KIBBLE, 0, 500, -527, 0, 0, 0, (1 << 16), bhvSirKibble),
		OBJECT(MODEL_G_STAR_BLOCK, 1036, 500, 750, 0, 0, 0, 0x00000000, bhvStarProjectile),
		OBJECT(MODEL_G_STAR_BLOCK, 1223, 500, 371, 0, 49, 0, 0x00000000, bhvStarProjectile),
		OBJECT(MODEL_G_STAR_BLOCK, -912, 500, -1110, 0, 96, 0, 0x00000000, bhvStarProjectile),
		OBJECT(MODEL_NONE, 32, 500, -1750, 0, -180, 0, 0x00000000, bhvGStarDoor),
		OBJECT(MODEL_G_STAR_PROJECTILE, 26, 791, -1629, 0, 90, 0, (1 << 16), bhvStarDoorStar),
		OBJECT(MODEL_G_STAR_PROJECTILE, 127, 723, -1629, 0, 90, 0, 0x00000000, bhvStarDoorStar),
		OBJECT(MODEL_G_STAR_PROJECTILE, -76, 723, -1629, 0, 90, 0, 0x00000000, bhvStarDoorStar),
		OBJECT(MODEL_G_STAR_PROJECTILE, 156, 639, -1629, 0, 90, 0, 0x00000000, bhvStarDoorStar),
		OBJECT(MODEL_G_STAR_PROJECTILE, -104, 639, -1629, 0, 90, 0, 0x00000000, bhvStarDoorStar),
		OBJECT(MODEL_G_STAR_PROJECTILE, 156, 554, -1629, 0, 90, 0, 0x00000000, bhvStarDoorStar),
		OBJECT(MODEL_G_STAR_PROJECTILE, -104, 554, -1629, 0, 90, 0, 0x00000000, bhvStarDoorStar),
		TERRAIN(g_area_2_collision),
		MACRO_OBJECTS(g_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CUSTOM_SAVE_HUT),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, -180, -1155, 304, -1246),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
