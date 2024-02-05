#include "src/game/envfx_snow.h"

const GeoLayout f_boat_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_ASM(GEO_TRANSPARENCY_MODE_NORMAL, geo_update_layer_transparency),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_boat_Boat_NEEDS_KEY_DRIVEABLE_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, f_boat_Boat_NEEDS_KEY_DRIVEABLE_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_boat_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, f_boat_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
