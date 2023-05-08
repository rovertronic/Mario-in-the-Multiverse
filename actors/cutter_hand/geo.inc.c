#include "src/game/envfx_snow.h"

const GeoLayout cutter_hand_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 260, -10, 79, cutter_hand_right_hand_open_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, cutter_hand_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
