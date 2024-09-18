#include "src/game/envfx_snow.h"

const GeoLayout k_pounder_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, k_pounder_Cube_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
