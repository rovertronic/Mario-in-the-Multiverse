#include "src/game/envfx_snow.h"

const GeoLayout turret_bullet_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_INTER, turret_bullet_turret_bullet_mesh_layer_7),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_INTER, turret_bullet_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
