#include "src/game/envfx_snow.h"

const GeoLayout o_zomblood_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, o_zomblood_Plane_001_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, o_zomblood_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
