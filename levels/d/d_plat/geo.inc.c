#include "src/game/envfx_snow.h"

const GeoLayout d_plat_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, d_plat_Cube_002_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
