#include "src/game/envfx_snow.h"

const GeoLayout star_piece_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 229, 50),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, star_piece_Cube_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, star_piece_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
