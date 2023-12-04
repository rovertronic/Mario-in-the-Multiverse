#include "src/game/envfx_snow.h"

const GeoLayout wooden_lever_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, wooden_lever_levier_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, wooden_lever_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
