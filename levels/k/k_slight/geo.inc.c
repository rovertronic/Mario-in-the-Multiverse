#include "src/game/envfx_snow.h"

const GeoLayout k_slight_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, k_slight_Cube_009_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, k_slight_Cube_009_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
