#include "src/game/envfx_snow.h"

const GeoLayout crane_head_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, crane_head_model_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, crane_head_model_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, crane_head_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, crane_head_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
