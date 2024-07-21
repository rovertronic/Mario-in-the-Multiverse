#include "src/game/envfx_snow.h"

const GeoLayout dream_catalyst_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 204, 100),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, dream_catalyst_star_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_ALPHA, dream_catalyst_star_mesh_layer_4),
				GEO_BILLBOARD_WITH_PARAMS(LAYER_OPAQUE, 0, 0, 0),
				GEO_OPEN_NODE(),
					GEO_DISPLAY_LIST(LAYER_TRANSPARENT, dream_catalyst_rainbow_mesh_layer_5),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
