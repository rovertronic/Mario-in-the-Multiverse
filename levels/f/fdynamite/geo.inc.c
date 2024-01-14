#include "src/game/envfx_snow.h"

const GeoLayout fdynamite_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, fdynamite_Dynamite__Retrieve___beginning__Timer_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, fdynamite_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
