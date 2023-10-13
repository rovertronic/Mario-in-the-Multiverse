#include "src/game/envfx_snow.h"

const GeoLayout f_door_geo[] = {
	GEO_CULLING_RADIUS(625),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_door_Door___keypad_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_door_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
