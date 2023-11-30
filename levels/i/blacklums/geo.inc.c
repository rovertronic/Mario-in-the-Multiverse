#include "src/game/envfx_snow.h"

const GeoLayout blacklums_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, blacklums_body_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, blacklums_body_mesh_layer_4),
			GEO_BILLBOARD_WITH_PARAMS_AND_DL(LAYER_ALPHA, 0, 0, 0, blacklums_fur_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, blacklums_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, blacklums_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
