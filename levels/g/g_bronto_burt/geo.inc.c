#include "src/game/envfx_snow.h"

const GeoLayout g_bronto_burt_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, g_bronto_burt_root_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 22, -44, -5, g_bronto_burt_footL_mesh_layer_1),
			GEO_ANIMATED_PART(LAYER_OPAQUE, -21, -44, -5, g_bronto_burt_footR_mesh_layer_1),
			GEO_SHADOW(1, 102, 100),
			GEO_ANIMATED_PART(LAYER_TRANSPARENT, 41, -11, 0, g_bronto_burt_wingL_mesh_layer_5),
			GEO_ANIMATED_PART(LAYER_TRANSPARENT, -42, -11, 0, g_bronto_burt_wingR_mesh_layer_5),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, g_bronto_burt_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, g_bronto_burt_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
