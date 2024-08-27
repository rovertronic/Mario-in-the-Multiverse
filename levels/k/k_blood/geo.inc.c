#include "src/game/envfx_snow.h"

const GeoLayout k_blood_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, k_blood_Plane_006_mesh_layer_6),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
