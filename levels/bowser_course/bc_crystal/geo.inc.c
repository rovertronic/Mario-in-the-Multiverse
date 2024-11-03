#include "src/game/envfx_snow.h"

const GeoLayout bc_crystal_geo[] = {
	GEO_CULLING_RADIUS(200),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bc_crystal_Icosphere_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
