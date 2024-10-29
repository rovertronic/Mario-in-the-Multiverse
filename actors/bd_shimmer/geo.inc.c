#include "src/game/envfx_snow.h"

const GeoLayout bd_shimmer_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(0, geo_update_layer_transparency),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bd_shimmer_Cone_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
