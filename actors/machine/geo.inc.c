#include "src/game/envfx_snow.h"

const GeoLayout machine_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
		GEO_OPEN_NODE(),
			GEO_ASM(0, geo_update_layer_redness),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, machine_root_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, machine_root_mesh_layer_6),
				GEO_DISPLAY_LIST(LAYER_TRANSPARENT, machine_root_mesh_layer_5),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 181, 0, 70, machine_door_mesh_layer_1),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 429, 0, machine_eye_mesh_layer_1),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, machine_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, machine_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, machine_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
