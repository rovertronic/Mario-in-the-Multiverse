#include "src/game/envfx_snow.h"

const GeoLayout airlock_button_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, airlock_button_airlock_button_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, airlock_button_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
