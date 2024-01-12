#include "src/game/envfx_snow.h"

const GeoLayout a_cage_geo[] = {
	GEO_CULLING_RADIUS(300),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, a_cage_Cube_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, a_cage_Cube_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, a_cage_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, a_cage_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
