#include "src/game/envfx_snow.h"

const GeoLayout f_helidead_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_helidead_DamagedHeli_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_helidead_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
