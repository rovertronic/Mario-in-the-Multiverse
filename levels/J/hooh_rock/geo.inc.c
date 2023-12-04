#include "src/game/envfx_snow.h"

const GeoLayout hooh_rock_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, hooh_rock_Bone_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_SHADOW(1, 194, 200),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hooh_rock_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
