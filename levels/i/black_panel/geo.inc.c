#include "src/game/envfx_snow.h"

const GeoLayout black_panel_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, black_panel_Plane_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, black_panel_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
