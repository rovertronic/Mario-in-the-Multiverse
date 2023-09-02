#include "src/game/envfx_snow.h"

const GeoLayout f_keypad_geo[] = {
	GEO_CULLING_RADIUS(125),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_keypad_keypad_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_keypad_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
