#include "src/game/envfx_snow.h"

const GeoLayout bc_pingas_ball_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 178, 600),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, bc_pingas_ball_Sphere_mesh_layer_1),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, bc_pingas_ball_Sphere_mesh_layer_6),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
