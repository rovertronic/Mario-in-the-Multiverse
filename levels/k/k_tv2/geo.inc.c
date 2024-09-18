#include "src/game/envfx_snow.h"

const GeoLayout k_tv2_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, k_tv2_Plane_008_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, k_tv2_Plane_008_mesh_layer_6),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
