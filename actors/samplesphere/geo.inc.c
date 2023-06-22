#include "src/game/envfx_snow.h"

const GeoLayout samplesphere_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, samplesphere_RollBall_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, samplesphere_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
