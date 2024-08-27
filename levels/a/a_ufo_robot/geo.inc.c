#include "src/game/envfx_snow.h"

const GeoLayout a_ufo_robot_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 153, 300),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, a_ufo_robot_ufo_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
