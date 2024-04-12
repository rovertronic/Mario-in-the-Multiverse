#include "src/game/envfx_snow.h"

const GeoLayout bc_hoodmonger_bullet_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(LAYER_TRANSPARENT, 0, 0, 0, bc_hoodmonger_bullet_bullet_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bc_hoodmonger_bullet_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
