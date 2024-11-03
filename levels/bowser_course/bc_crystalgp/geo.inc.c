#include "src/game/envfx_snow.h"

const GeoLayout bc_crystalgp_geo[] = {
	GEO_CULLING_RADIUS(300),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bc_crystalgp_Cylinder_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bc_crystalgp_Cylinder_002_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
