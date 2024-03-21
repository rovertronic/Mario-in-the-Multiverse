#include "src/game/envfx_snow.h"

const GeoLayout e_shells_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, e_shells_model_mesh_layer_6),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_INTER, e_shells_model_mesh_layer_7),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, e_shells_model_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, e_shells_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, e_shells_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_INTER, e_shells_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
