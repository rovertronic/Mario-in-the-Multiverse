#include "src/game/envfx_snow.h"

const GeoLayout intro_cloth_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, intro_cloth_Cylinder_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, intro_cloth_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
