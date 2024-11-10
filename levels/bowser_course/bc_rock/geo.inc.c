#include "src/game/envfx_snow.h"

const GeoLayout bc_rock_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bc_rock_Icosphere_002_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
