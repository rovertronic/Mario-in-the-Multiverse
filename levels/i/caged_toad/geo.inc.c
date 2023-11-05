#include "src/game/envfx_snow.h"

const GeoLayout caged_toad_geo[] = {
	GEO_SHADOW(SHADOW_CIRCLE_PLAYER, 0x9B, 200),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, caged_toad_cage_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, caged_toad_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
