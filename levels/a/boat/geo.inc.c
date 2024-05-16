#include "src/game/envfx_snow.h"

const GeoLayout boat_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, boat_boat_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, boat_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
