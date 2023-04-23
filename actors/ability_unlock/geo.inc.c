#include "src/game/envfx_snow.h"

const GeoLayout ability_unlock_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(0, geo_ability_material),
		GEO_DISPLAY_LIST(LAYER_ALPHA, ability_unlock_ability_unlock_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ability_unlock_ability_unlock_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_ALPHA, ability_unlock_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ability_unlock_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
