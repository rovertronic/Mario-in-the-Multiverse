#include "src/game/envfx_snow.h"

const GeoLayout a_launched_box_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(SHADOW_SQUARE_PERMANENT, 153, 300),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, a_launched_box_root_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
