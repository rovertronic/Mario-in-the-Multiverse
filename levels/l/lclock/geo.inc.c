#include "src/game/envfx_snow.h"

const GeoLayout lclock_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 130, 100),
		GEO_OPEN_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 0, 0, 0, -180, 0),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, lclock_root_mesh_layer_4),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_ALPHA, 0, -8, -4, lclock_hand1_mesh_layer_4),
					GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, -8, -4, 0, 0, 90),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, lclock_hand2_mesh_layer_4),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, lclock_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
