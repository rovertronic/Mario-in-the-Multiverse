#include "src/game/envfx_snow.h"

const GeoLayout sb_torch_1_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, sb_torch_1_torchoff_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
