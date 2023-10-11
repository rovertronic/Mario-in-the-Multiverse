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
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	LOAD_MODEL_FROM_GEO(MODEL_O_ZOMBIE_1, o_zombie1_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_O_ZOMBIE_2, o_zombie2_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_O_ZOMBIE_3, o_zombie3_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_ZOMBLOOD, o_zomblood_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_O_TREE, o_tree_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, o_area_1),
		WARP_NODE(/*entry*/ 0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death*/ 0xF1, LEVEL_O, /*this area*/ 0x01, 0x01, WARP_NO_CHECKPOINT),
		WARP_NODE(/*death entry*/ 0x01, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_ABILITY, -858, 5065, 907, 0, 0, 0, (ABILITY_DEFAULT << 16), bhvAbilityUnlock),
		OBJECT(MODEL_ABILITY_SIGN, -20249, -10, 924, 0, 45, 0, (ABILITY_MARBLE << 16), bhvStaticObject),
		OBJECT(MODEL_BLUE_COIN_SWITCH, -19267, 1926, -5543, 0, 0, 0, 0x00000000, bhvBlueCoinSwitch),
		OBJECT(MODEL_BLUE_COIN, -19267, 1926, -6343, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -19267, 1926, -4743, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -18467, 1926, -6343, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -18467, 1926, -4743, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -20067, 1926, -6343, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -20067, 1926, -4743, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -18467, 1926, -5543, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -20067, 1926, -5543, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_CHECKPOINT_FLAG, 250, -10, 4637, 0, 0, 0, (0 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 13559, 2730, 10, 0, 0, 0, (1 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, -16463, -10, -8399, 0, 0, 0, (2 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_CHECKPOINT_FLAG, 250, 1129, -22638, 0, 0, 0, (3 << 16), bhvCheckpointFlag),
		OBJECT(MODEL_NONE, 68, -10, 13462, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 151, -10, 13462, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 271, -10, 13462, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 355, -10, 13462, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 459, -10, 13462, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -571, 945, 4085, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 1097, 945, 1335, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 4285, 945, -813, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 2919, 945, 833, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 4022, 1900, -805, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 2035, 1900, -805, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -2736, 1900, 804, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_LEVEL_PIPE, 0, 0, 19924, 0, 0, 0, 0x00000000, bhvLevelPipe),
		OBJECT(MODEL_NONE, 0, 235, 19503, 0, -180, 0, (0x01 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 0, 0, 19503, 0, -180, 0, (0x0A << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 1088, 4832, 1104, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_NONE, 939, 4832, 1104, 0, 0, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_NONE, 789, 4832, 1104, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_NONE, 639, 4832, 1104, 0, 0, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_NONE, 489, 4832, 1104, 0, 0, 0, (4 << 24), bhvStar),
		OBJECT(MODEL_NONE, 340, 4832, 1104, 0, 0, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_NONE, 190, 4832, 1104, 0, 0, 0, (6 << 24), bhvStar),
		OBJECT(MODEL_NONE, 40, 4832, 1104, 0, 0, 0, (7 << 24), bhvStar),
		OBJECT(MODEL_O_TREE, -6348, 126, 891, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -7524, 165, 741, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -9005, 102, 1128, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -9670, 182, 2501, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -9313, 120, 3908, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -11699, 246, 2937, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -12301, 283, 4299, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -13088, 383, 1841, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -14860, 556, 2925, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -17168, 101, 1717, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -17987, 450, 4181, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -16443, 703, 4601, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -17453, 88, 6934, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -19208, 54, 6258, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -13630, 345, 6161, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -10569, 187, 7338, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -8630, 328, 7334, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -7641, 105, 6494, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_O_TREE, -7844, 53, 8081, 0, 0, 0, 0x00000000, bhvOTree),
		OBJECT(MODEL_NONE, 4446, 945, -794, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 3546, 945, -794, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 2388, 945, -794, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 1545, 945, -794, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 1026, 945, -1623, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 1026, 945, -2908, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 1026, 945, -3994, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -581, 945, -3994, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -581, 945, -2498, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -581, 945, -1485, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -1146, 945, -765, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -2592, 945, -765, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -4201, 945, -765, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -3657, 945, 840, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -2152, 945, 840, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -576, 945, 840, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -576, 945, 2284, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -576, 945, 3833, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -605, 1900, 865, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -605, 1900, -811, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 1079, 1900, -811, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 1079, 1900, 863, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 1079, 1900, 4663, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 1079, 1900, -4501, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -4306, 1900, -787, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 582, -10, -314, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 445, -10, 325, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -517, -10, 65, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 74, -10, -498, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 426, -10, -729, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, 908, -10, 97, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -16738, -10, -1017, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -15994, -10, -1795, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -16584, -10, -2769, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -16011, -10, -3991, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -16668, -10, -5542, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -16034, -10, -6734, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -15236, -10, -3418, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -15303, 607, 5317, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -16368, 239, 2016, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
		OBJECT(MODEL_NONE, -10565, -10, 5433, 0, 0, 0, 0x00000000, bhvOZombieSpawner),
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
