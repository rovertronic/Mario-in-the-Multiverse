#include "src/game/envfx_snow.h"

const GeoLayout sb_gap_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sb_gap_Plane_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_ALPHA, sb_gap_Plane_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
