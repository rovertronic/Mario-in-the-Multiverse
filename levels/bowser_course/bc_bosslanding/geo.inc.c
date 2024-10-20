#include "src/game/envfx_snow.h"

const GeoLayout bc_bosslanding_geo[] = {
	GEO_CULLING_RADIUS(3000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bc_bosslanding_vis_001_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
