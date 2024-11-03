#include "src/game/envfx_snow.h"

const GeoLayout bc_crystalp_geo[] = {
	GEO_CULLING_RADIUS(200),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bc_crystalp_Icosphere_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bc_crystalp_Icosphere_001_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
