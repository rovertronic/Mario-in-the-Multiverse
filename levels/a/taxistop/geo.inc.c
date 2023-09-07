#include "src/game/envfx_snow.h"

const GeoLayout taxistop_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, taxistop_taxi_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, -313, 46, 5, taxistop_boat_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, taxistop_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
