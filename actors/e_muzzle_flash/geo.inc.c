#include "src/game/envfx_snow.h"

const GeoLayout e_muzzle_flash_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, e_muzzle_flash_model_001_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, e_muzzle_flash_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
