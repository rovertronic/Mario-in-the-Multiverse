#include "src/game/envfx_snow.h"

const GeoLayout octoball_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, octoball_body_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, octoball_body_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, octoball_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, octoball_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
