#include "src/game/envfx_snow.h"

const GeoLayout chained_cage_geo[] = {
	GEO_CULLING_RADIUS(300),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, chained_cage_Cube_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, chained_cage_Cube_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
