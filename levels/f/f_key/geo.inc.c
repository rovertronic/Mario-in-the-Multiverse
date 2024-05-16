#include "src/game/envfx_snow.h"

const GeoLayout f_key_geo[] = {
	GEO_CULLING_RADIUS(100),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_key_Key_BOAT_SPARKLE_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_key_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
