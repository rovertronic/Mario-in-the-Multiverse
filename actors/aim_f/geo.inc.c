#include "src/game/envfx_snow.h"

const GeoLayout aim_f_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, aim_f_Plane_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, aim_f_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
