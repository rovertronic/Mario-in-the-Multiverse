#include "src/game/envfx_snow.h"

const GeoLayout f_fence_geo[] = {
	GEO_CULLING_RADIUS(2500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, f_fence_fence_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, f_fence_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
