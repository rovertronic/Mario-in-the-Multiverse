#include "src/game/envfx_snow.h"

const GeoLayout f_briefcase_geo[] = {
	GEO_CULLING_RADIUS(100),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 153, 80),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, f_briefcase_BRIEFCASE_SECRETS_001_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_briefcase_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
