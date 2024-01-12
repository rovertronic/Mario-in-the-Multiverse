#include "src/game/envfx_snow.h"

const GeoLayout o_garage_geo[] = {
	GEO_CULLING_RADIUS(1500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, o_garage_garage_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, o_garage_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
