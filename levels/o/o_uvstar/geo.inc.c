#include "src/game/envfx_snow.h"

const GeoLayout o_uvstar[] = {
	GEO_CULLING_RADIUS(100),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, o_uvstar_Circle_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, o_uvstar_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
