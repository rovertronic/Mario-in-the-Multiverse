#include "src/game/envfx_snow.h"

const GeoLayout miltank_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, miltank_Bone_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, miltank_Bone_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, miltank_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, miltank_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
