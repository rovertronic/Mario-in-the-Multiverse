#include "src/game/envfx_snow.h"

const GeoLayout level_pipe_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(0, geo_update_mverse_pipe),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, level_pipe_Level_Pipe_Visual_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, level_pipe_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
