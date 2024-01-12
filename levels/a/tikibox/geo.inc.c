#include "src/game/envfx_snow.h"

const GeoLayout tikibox_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, tikibox_Plane_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, tikibox_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

const GeoLayout stone_tiki_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, stone_tiki_Plane_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, stone_tiki_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
