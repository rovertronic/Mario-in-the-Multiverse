#include "src/game/envfx_snow.h"

const GeoLayout f_sch_board_2_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_sch_board_2_Schedule_Board_SHOTGUN_CRACKED_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, f_sch_board_2_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
