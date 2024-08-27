#include "src/game/envfx_snow.h"

const GeoLayout a_robot_launcher_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, a_robot_launcher_Plane_003_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
