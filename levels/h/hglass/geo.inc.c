#include "src/game/envfx_snow.h"

const GeoLayout hglass_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hglass_SmallerBits_001_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hglass_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
