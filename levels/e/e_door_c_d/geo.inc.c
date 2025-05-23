#include "src/game/envfx_snow.h"

const GeoLayout e_door_c_d_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, e_door_c_d_door_castle_d_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, e_door_c_d_door_castle_d_mesh_layer_6),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, e_door_c_d_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, e_door_c_d_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
