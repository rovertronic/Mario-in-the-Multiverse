#include "src/game/envfx_snow.h"

const GeoLayout g_marx_laser_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, g_marx_laser_Circle_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, g_marx_laser_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
