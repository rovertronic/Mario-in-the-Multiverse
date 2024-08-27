#include "src/game/envfx_snow.h"

const GeoLayout gas_cloud_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(LAYER_TRANSPARENT, 0, 0, 0, gas_cloud_Plane_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
