#include "src/game/envfx_snow.h"

const GeoLayout o_speaker_3_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, o_speaker_3_Cube_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, o_speaker_3_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
