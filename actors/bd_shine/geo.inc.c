#include "src/game/envfx_snow.h"

const GeoLayout bd_shine_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(0, geo_update_layer_transparency),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bd_shine_Circle_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
