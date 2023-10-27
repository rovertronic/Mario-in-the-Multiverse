#include "src/game/envfx_snow.h"

const GeoLayout g_cut_rock_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, g_cut_rock_Cube_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, g_cut_rock_Cube_002_mesh_layer_6),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, g_cut_rock_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, g_cut_rock_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
