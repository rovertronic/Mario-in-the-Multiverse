#include "src/game/envfx_snow.h"

const GeoLayout bc_crystalg_geo[] = {
	GEO_CULLING_RADIUS(300),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bc_crystalg_Cylinder_001_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
