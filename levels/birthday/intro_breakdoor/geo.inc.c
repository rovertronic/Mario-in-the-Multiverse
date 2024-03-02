#include "src/game/envfx_snow.h"

const GeoLayout intro_breakdoor_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, intro_breakdoor_Map_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, intro_breakdoor_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
