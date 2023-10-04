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
#include "levels/o/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_o_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x7, _o_segment_7SegmentRomStart, _o_segment_7SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	LOAD_MODEL_FROM_GEO(MODEL_O_ZOMBIE_1, o_zombie1_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_O_ZOMBIE_2, o_zombie2_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_O_ZOMBIE_3, o_zombie3_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_ZOMBLOOD, o_zomblood_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, o_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_X, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, -1146, 50, 1211, 0, 0, 0, (ABILITY_DEFAULT << 16), bhvAbilityUnlock),
		OBJECT(MODEL_CHECKPOINT_FLAG, 1439, 50, -1412, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 1439, 50, -1112, 0, 0, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_NONE, -1352, 50, -1159, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1240, 50, -1159, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1081, 50, -1159, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -968, 50, -1159, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -829, 50, -1159, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_LEVEL_PIPE, 0, 50, 691, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_NONE, 0, 365, -365, 0, 0, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 0, 50, -761, 0, 0, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 1453, 164, 1474, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_NONE, 1253, 164, 1474, 0, 0, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_NONE, 1053, 164, 1474, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_NONE, 853, 164, 1474, 0, 0, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_NONE, 653, 164, 1474, 0, 0, 0, (4 << 24), bhvStar),
		OBJECT(MODEL_NONE, 453, 164, 1474, 0, 0, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_NONE, 253, 164, 1474, 0, 0, 0, (6 << 24), bhvStar),
		OBJECT(MODEL_NONE, 53, 164, 1474, 0, 0, 0, (7 << 24), bhvStar),
		OBJECT(MODEL_NONE, 4176, 1444, -111, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 5114, 50, 768, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 4557, 50, 1148, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 4051, 50, -233, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 5028, 50, -1413, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -1274, 116, -74, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -1274, 116, 304, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		TERRAIN(o_area_1_collision),
		MACRO_OBJECTS(o_area_1_macro_objs),
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
