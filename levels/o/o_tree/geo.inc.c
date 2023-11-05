#include "src/game/envfx_snow.h"

const GeoLayout o_tree_geo[] = {
	GEO_CULLING_RADIUS(300),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 153, 600),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, o_tree_tree_mesh_layer_4),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, o_tree_tree_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, o_tree_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, o_tree_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
