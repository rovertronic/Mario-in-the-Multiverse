#include "src/game/envfx_snow.h"

const GeoLayout fhidden_geo[] = {
	GEO_CULLING_RADIUS(2200),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, fhidden_hiddencol_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
