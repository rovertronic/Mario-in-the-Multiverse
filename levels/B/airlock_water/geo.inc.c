#include "src/game/envfx_snow.h"

const GeoLayout airlock_water_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, airlock_water_Cube_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
