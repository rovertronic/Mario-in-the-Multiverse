#include "src/game/envfx_snow.h"

const GeoLayout jelly_fish_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 153, 90),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 17, 0, jelly_fish_Bone_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 30, 0, jelly_fish_Bone_001_mesh_layer_1),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, -16, 42, 0, jelly_fish_Bone_003_mesh_layer_1),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 16, 42, 0, jelly_fish_Bone_005_mesh_layer_1),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 64, 0, jelly_fish_Bone_006_mesh_layer_1),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, jelly_fish_Bone_006_mesh_layer_6),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
