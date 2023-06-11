#include "src/game/envfx_snow.h"

const GeoLayout cutter_blast_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, cutter_blast_Circle_001_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, cutter_blast_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
