#include "src/game/envfx_snow.h"

const GeoLayout watertemple_geo[] = {
	GEO_CULLING_RADIUS(1000000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_INTER, watertemple_watertemple_mesh_layer_7),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, watertemple_watertemple_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, watertemple_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_INTER, watertemple_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
