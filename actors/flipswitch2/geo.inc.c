#include "src/game/envfx_snow.h"

const GeoLayout flipswitch2_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, flipswitch2_Cube_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flipswitch2_Cube_002_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, flipswitch2_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flipswitch2_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
