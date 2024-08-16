#include "src/game/envfx_snow.h"

const GeoLayout bc_skiploom_geo[] = {
	GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xC8, 100),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, bc_skiploom_Body_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, bc_skiploom_Body_mesh_layer_4),
			GEO_ANIMATED_PART(LAYER_ALPHA, 0, 35, 0, bc_skiploom_Flower_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bc_skiploom_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bc_skiploom_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
