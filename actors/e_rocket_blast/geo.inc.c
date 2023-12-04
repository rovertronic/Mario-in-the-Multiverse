#include "src/game/envfx_snow.h"

const GeoLayout e_rocket_blast_switchTransparency_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(0, geo_update_layer_transparency),
		GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, e_rocket_blast_b1_dl_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout e_rocket_blast_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_NODE_START(),
		GEO_OPEN_NODE(),
			GEO_SWITCH_CASE(2, geo_switch_anim_state),
			GEO_OPEN_NODE(),
				GEO_NODE_START(),
				GEO_OPEN_NODE(),
					GEO_ASM(0, geo_update_layer_transparency),
					GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, e_rocket_blast_b1_dl_mesh_layer_5),
				GEO_CLOSE_NODE(),
				GEO_BRANCH(1, e_rocket_blast_switchTransparency_opt1),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, e_rocket_blast_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
