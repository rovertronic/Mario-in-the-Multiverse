#include "src/game/envfx_snow.h"

const GeoLayout d_bridge_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, d_bridge_Cube_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, d_bridge_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
