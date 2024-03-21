#include "src/game/envfx_snow.h"

const GeoLayout e_key_blue_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_NODE_START(),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, e_key_blue_b1_dl_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, e_key_blue_b1_dl_mesh_layer_6),
			GEO_CLOSE_NODE(),
			GEO_BILLBOARD_WITH_PARAMS(LAYER_OPAQUE, 0, 78, 0),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, -1, 0, e_key_blue_b3_glow_mesh_layer_5),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, e_key_blue_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, e_key_blue_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, e_key_blue_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
