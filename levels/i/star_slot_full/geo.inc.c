#include "src/game/envfx_snow.h"

const GeoLayout star_slot_full_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, star_slot_full_star_slot_full_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, star_slot_full_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
