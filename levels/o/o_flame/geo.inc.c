#include "src/game/envfx_snow.h"

const GeoLayout o_flame_geo[] = {
	GEO_CULLING_RADIUS(100),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, o_flame_Plane_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, o_flame_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
