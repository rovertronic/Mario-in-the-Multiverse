#include "src/game/envfx_snow.h"

const GeoLayout k_tv2_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, k_tv2_Plane_007_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
