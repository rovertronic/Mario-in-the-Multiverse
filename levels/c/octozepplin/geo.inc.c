#include "src/game/envfx_snow.h"

const GeoLayout octozepplin_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, octozepplin_Cylinder_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, octozepplin_Cylinder_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, octozepplin_Cylinder_mesh_layer_6),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
