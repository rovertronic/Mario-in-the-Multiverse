#include "src/game/envfx_snow.h"

const GeoLayout m_jellylaser2_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, m_jellylaser2_Cylinder_001_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
