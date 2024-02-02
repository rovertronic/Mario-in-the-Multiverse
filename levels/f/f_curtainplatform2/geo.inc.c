#include "src/game/envfx_snow.h"

const GeoLayout f_curtainplatform2_geo[] = {
	GEO_CULLING_RADIUS(32000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_curtainplatform2_Appears_AFTER_Keypad_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE_DECAL, f_curtainplatform2_Appears_AFTER_Keypad_mesh_layer_2),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_curtainplatform2_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_OPAQUE_DECAL, f_curtainplatform2_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
