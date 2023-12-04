#include "src/game/envfx_snow.h"

const GeoLayout rocket_button_on_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rocket_button_on_rayman_missile_bouton_on_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rocket_button_on_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
