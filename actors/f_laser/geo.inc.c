#include "src/game/envfx_snow.h"

const GeoLayout f_laser_geo[] = {
	GEO_CULLING_RADIUS(2128),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_laser_Plane_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_laser_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
