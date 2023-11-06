#include "src/game/envfx_snow.h"

const GeoLayout g_moving_platform_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, g_moving_platform_Plane_021_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, g_moving_platform_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
