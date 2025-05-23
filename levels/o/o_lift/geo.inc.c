#include "src/game/envfx_snow.h"

const GeoLayout o_lift[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, o_lift_lift_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, o_lift_lift_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, o_lift_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, o_lift_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
