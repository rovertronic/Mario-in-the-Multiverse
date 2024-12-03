#include "src/game/envfx_snow.h"

const GeoLayout collectable_painting_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 204, 100),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, collectable_painting_star_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_BILLBOARD_WITH_PARAMS(LAYER_OPAQUE, 0, 0, 0),
				GEO_OPEN_NODE(),
					GEO_DISPLAY_LIST(LAYER_TRANSPARENT, collectable_painting_rainbow_mesh_layer_5),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
