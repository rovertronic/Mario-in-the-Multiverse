#include "src/game/envfx_snow.h"

const GeoLayout bc_coinpile_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bc_coinpile_Plane_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
