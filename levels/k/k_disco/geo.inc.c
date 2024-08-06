#include "src/game/envfx_snow.h"

const GeoLayout k_disco_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, k_disco_Sphere_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
