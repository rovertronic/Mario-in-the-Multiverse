#include "src/game/envfx_snow.h"

const GeoLayout sb_blaster_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 204, 150),
		GEO_OPEN_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 38, 0, 131, 0, 0),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, sb_blaster_jaw_mesh_layer_1),
			GEO_CLOSE_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 38, 0, 96, 0, 0),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, sb_blaster_root_mesh_layer_1),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
