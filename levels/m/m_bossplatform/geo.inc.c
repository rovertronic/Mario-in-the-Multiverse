#include "src/game/envfx_snow.h"

const GeoLayout m_bossplatform_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, m_bossplatform_Cube_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, m_bossplatform_Cube_002_mesh_layer_6),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
