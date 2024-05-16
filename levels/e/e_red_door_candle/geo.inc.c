#include "src/game/envfx_snow.h"

const GeoLayout e_red_door_candle_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, e_red_door_candle_model_2_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, e_red_door_candle_model_2_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, e_red_door_candle_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, e_red_door_candle_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
