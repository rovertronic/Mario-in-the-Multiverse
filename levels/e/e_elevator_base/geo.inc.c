#include "src/game/envfx_snow.h"

const GeoLayout e_elevator_base_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, e_elevator_base_model_base_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, e_elevator_base_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
