#include "src/game/envfx_snow.h"

const GeoLayout windmill_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, windmill_moulin_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, windmill_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
