#include "src/game/envfx_snow.h"

const GeoLayout hub_stargoo_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hub_stargoo_machine_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hub_stargoo_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
