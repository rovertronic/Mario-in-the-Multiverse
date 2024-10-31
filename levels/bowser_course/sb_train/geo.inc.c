#include "src/game/envfx_snow.h"

const GeoLayout sb_train_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, sb_train__000_farm_item_09_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sb_train__000_farm_item_09_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
