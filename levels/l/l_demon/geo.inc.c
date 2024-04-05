#include "src/game/envfx_snow.h"

const GeoLayout l_demon_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 153, 100),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, l_demon_Plane_007_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, l_demon_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
