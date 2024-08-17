#include "src/game/envfx_snow.h"

const GeoLayout nitroboom_geo[] = {
	GEO_CULLING_RADIUS(200),
	GEO_OPEN_NODE(),
		GEO_ASM(0, geo_update_layer_transparency),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, nitroboom_Icosphere_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
