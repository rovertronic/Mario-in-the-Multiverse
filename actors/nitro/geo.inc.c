#include "src/game/envfx_snow.h"

const GeoLayout nitro_geo[] = {
	GEO_CULLING_RADIUS(200),
	GEO_OPEN_NODE(),
		GEO_SHADOW(11, 204, 150),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, nitro_Cube_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, nitro_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
