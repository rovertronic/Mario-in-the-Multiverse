#include "src/game/envfx_snow.h"

const GeoLayout f_keydoor_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 116, 30, 0, f_keydoor_l_mesh_layer_1),
			GEO_ANIMATED_PART(LAYER_OPAQUE, -115, 30, 0, f_keydoor_r_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_keydoor_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
