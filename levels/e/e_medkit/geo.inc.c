#include "src/game/envfx_snow.h"

const GeoLayout e_medkit_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, e_medkit_model_mesh_layer_6),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_INTER, e_medkit_model_mesh_layer_7),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, e_medkit_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_INTER, e_medkit_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
