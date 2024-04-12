#include "src/game/envfx_snow.h"

const GeoLayout bc_fspinner_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bc_fspinner_Cylinder_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bc_fspinner_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
