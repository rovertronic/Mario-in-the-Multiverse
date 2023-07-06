#include "src/game/envfx_snow.h"

const GeoLayout concrete_block_crack1_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, concrete_block_crack1_concrete_block_crack1_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, concrete_block_crack1_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
