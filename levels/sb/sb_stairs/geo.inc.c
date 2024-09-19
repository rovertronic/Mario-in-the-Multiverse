#include "src/game/envfx_snow.h"

const GeoLayout sb_stairs_geo[] = {
	GEO_CULLING_RADIUS(10000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, sb_stairs_hide_at_fight_start_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sb_stairs_hide_at_fight_start_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_ALPHA, sb_stairs_hide_at_fight_start_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
