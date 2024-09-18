#include "src/game/envfx_snow.h"

const GeoLayout m_elevator_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, m_elevator_Cube_005_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, m_elevator_Cube_005_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
