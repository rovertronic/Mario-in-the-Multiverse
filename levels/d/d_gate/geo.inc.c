#include "src/game/envfx_snow.h"

const GeoLayout d_gate_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, d_gate_Plane_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, d_gate_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
