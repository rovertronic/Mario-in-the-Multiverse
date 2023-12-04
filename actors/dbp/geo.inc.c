#include "src/game/envfx_snow.h"

const GeoLayout dbp_Bone_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, dbp_root_mesh_layer_4_mat_override_db_2_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout dbp_Bone_opt2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, dbp_root_mesh_layer_4_mat_override_db_3_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout dbp_Bone_opt3[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, dbp_root_mesh_layer_4_mat_override_db_4_2),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout dbp_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(4, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_ALPHA, dbp_root_mesh_layer_4),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, dbp_Bone_opt1),
			GEO_BRANCH(1, dbp_Bone_opt2),
			GEO_BRANCH(1, dbp_Bone_opt3),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, dbp_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
