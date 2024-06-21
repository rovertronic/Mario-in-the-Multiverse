#include "src/game/envfx_snow.h"

const GeoLayout ink_moving_platform_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ink_moving_platform_moving_platform_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, ink_moving_platform_moving_platform_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
