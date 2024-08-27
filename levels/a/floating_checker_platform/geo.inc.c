#include "src/game/envfx_snow.h"

const GeoLayout floating_checker_platform_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(SHADOW_SQUARE_SCALABLE, 0xB4, 300),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, floating_checker_platform_main_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, -41, 0, floating_checker_platform_spin_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, floating_checker_platform_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
