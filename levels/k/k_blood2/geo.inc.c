#include "src/game/envfx_snow.h"

const GeoLayout k_blood2_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, k_blood2_Plane_001_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
