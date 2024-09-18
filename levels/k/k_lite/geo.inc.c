#include "src/game/envfx_snow.h"

const GeoLayout k_lite_geo[] = {
	GEO_CULLING_RADIUS(100),
	GEO_OPEN_NODE(),
		GEO_ASM(GEO_TRANSPARENCY_MODE_DECAL, geo_update_layer_transparency),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, k_lite_Plane_011_mesh_layer_6),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
