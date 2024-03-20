#include "src/game/envfx_snow.h"

const GeoLayout e_medkit_effect_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_NODE_START(),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_TRANSPARENT_DECAL, 0, 0, 0, e_medkit_effect_b1_dl_mesh_layer_6),
			GEO_BILLBOARD_WITH_PARAMS(LAYER_OPAQUE, 0, 151, 0),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, -67, 0, e_medkit_effect_b3_glow_mesh_layer_5),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, e_medkit_effect_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, e_medkit_effect_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
