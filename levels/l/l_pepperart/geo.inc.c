#include "src/game/envfx_snow.h"

const GeoLayout l_pepperart_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, l_pepperart_pepperartMesh_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
