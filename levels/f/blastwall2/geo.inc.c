#include "src/game/envfx_snow.h"

const GeoLayout blastwall2_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, blastwall2_Barrel_Tower_BREAKS_GLASS_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, blastwall2_Barrel_Tower_BREAKS_GLASS_001_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, blastwall2_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, blastwall2_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
