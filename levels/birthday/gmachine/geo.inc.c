#include "src/game/envfx_snow.h"

const GeoLayout gmachine_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
		GEO_OPEN_NODE(),
			GEO_ASM(0, geo_update_layer_redness),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, gmachine_root_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, gmachine_root_mesh_layer_6),
				GEO_DISPLAY_LIST(LAYER_TRANSPARENT, gmachine_root_mesh_layer_5),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 181, 0, 70, gmachine_door_mesh_layer_1),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 429, 0, gmachine_eye_mesh_layer_1),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
