#include "src/game/envfx_snow.h"

const GeoLayout pstatue1_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 153, 200),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, pstatue1_Cylinder_005_mesh_layer_1),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, pstatue1_Cylinder_005_mesh_layer_6),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, pstatue1_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, pstatue1_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
