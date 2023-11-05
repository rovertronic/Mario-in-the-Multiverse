#include "src/game/envfx_snow.h"

const GeoLayout magikarp_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, magikarp_Bone_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, magikarp_Bone_mesh_layer_4),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 53, -12, -3, 0, 69, -90),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, magikarp_l_Fin_mesh_layer_4),
			GEO_CLOSE_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -53, -12, -3, 0, -69, 90),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, magikarp_r_Fin_mesh_layer_4),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, magikarp_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, magikarp_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
