#include "src/game/envfx_snow.h"

const GeoLayout g_marx_seed_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, g_marx_seed_Plane_001_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, g_marx_seed_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
