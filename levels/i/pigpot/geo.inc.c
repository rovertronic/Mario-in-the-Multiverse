#include "src/game/envfx_snow.h"

const GeoLayout pigpot_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(2, 153, 136),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, pigpot_pigpot_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, pigpot_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
