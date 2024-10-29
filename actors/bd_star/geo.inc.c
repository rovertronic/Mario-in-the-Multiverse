#include "src/game/envfx_snow.h"

const GeoLayout bd_star_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(0, geo_update_defeat_star),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bd_star_Circle_001_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
