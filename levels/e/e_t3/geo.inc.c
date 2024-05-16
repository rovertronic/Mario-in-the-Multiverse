#include "src/game/envfx_snow.h"

const GeoLayout e_t3_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, e_t3_model3_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, e_t3_model3_mesh_layer_6),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, e_t3_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, e_t3_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
