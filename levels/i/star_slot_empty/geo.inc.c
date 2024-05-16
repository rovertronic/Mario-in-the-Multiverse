#include "src/game/envfx_snow.h"

const GeoLayout star_slot_empty_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, star_slot_empty_star_slot_empty_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, star_slot_empty_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
