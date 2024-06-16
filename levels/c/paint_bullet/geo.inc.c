#include "src/game/envfx_snow.h"

const GeoLayout paint_bullet_Bone_002_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_ALPHA, 94, 0, 0, paint_bullet_Bone_004_mesh_layer_4_mat_override_orange_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout paint_bullet_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
		GEO_OPEN_NODE(),
			GEO_SWITCH_CASE(2, geo_switch_anim_state),
			GEO_OPEN_NODE(),
				GEO_NODE_START(),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_ALPHA, 94, 0, 0, paint_bullet_Bone_004_mesh_layer_4),
				GEO_CLOSE_NODE(),
				GEO_BRANCH(1, paint_bullet_Bone_002_opt1),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
