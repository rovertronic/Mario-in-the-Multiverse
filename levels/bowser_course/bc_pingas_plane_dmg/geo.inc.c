#include "src/game/envfx_snow.h"

const GeoLayout bc_pingas_plane_dmg_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bc_pingas_plane_dmg_eggmobile_001_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
