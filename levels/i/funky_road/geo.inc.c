#include "src/game/envfx_snow.h"

const GeoLayout funky_road_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, funky_road_Plane_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, funky_road_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
