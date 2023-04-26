#include "src/game/envfx_snow.h"

const GeoLayout ability_sign_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(0, geo_ability_material),
		GEO_DISPLAY_LIST(LAYER_ALPHA, ability_sign_absign_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, ability_sign_absign_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, ability_sign_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, ability_sign_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
