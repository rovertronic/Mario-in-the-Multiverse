#include "src/game/envfx_snow.h"

const GeoLayout bc_laser_geo[] = {
	GEO_CULLING_RADIUS(2000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bc_laser_Plane_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
