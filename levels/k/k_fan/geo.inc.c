#include "src/game/envfx_snow.h"

const GeoLayout k_fan_geo[] = {
	GEO_CULLING_RADIUS(10000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, k_fan_Plane_003_mesh_layer_6),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, k_fan_Plane_003_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
