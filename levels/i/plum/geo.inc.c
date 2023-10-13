#include "src/game/envfx_snow.h"

const GeoLayout plum_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, plum_prune_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, plum_prune_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, plum_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, plum_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
