#include "src/game/envfx_snow.h"

const GeoLayout g_marx_black_hole_effect_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, g_marx_black_hole_effect_Sphere_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, g_marx_black_hole_effect_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
