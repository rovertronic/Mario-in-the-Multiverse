#include "src/game/envfx_snow.h"

const GeoLayout target_box_Bone_002_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 355, 0, 0, target_box_Bone_004_mesh_layer_1_mat_override_f3dlite_material_003_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout target_box_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, target_box_Bone_mesh_layer_4),
		GEO_OPEN_NODE(),
			GEO_SWITCH_CASE(2, geo_switch_anim_state),
			GEO_OPEN_NODE(),
				GEO_NODE_START(),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 355, 0, 0, target_box_Bone_004_mesh_layer_1),
				GEO_CLOSE_NODE(),
				GEO_BRANCH(1, target_box_Bone_002_opt1),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
