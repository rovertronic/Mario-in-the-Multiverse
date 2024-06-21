#include "src/game/envfx_snow.h"

const GeoLayout paint_stain_Bone_002_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_TRANSPARENT, 144, 0, 0, paint_stain_Bone_006_mesh_layer_5_mat_override_paint2_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout paint_stain_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
		GEO_OPEN_NODE(),
			GEO_SWITCH_CASE(2, geo_switch_anim_state),
			GEO_OPEN_NODE(),
				GEO_NODE_START(),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_TRANSPARENT, 144, 0, 0, paint_stain_Bone_006_mesh_layer_5),
				GEO_CLOSE_NODE(),
				GEO_BRANCH(1, paint_stain_Bone_002_opt1),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
