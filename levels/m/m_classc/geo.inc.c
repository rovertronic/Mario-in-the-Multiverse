#include "src/game/envfx_snow.h"

const GeoLayout m_classc_switch_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, m_classc_dl_mesh_layer_1_mat_override_nolight_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout m_classc_switch_opt2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, m_classc_dl_mesh_layer_1_mat_override_white_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout m_classc_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 204, 400),
		GEO_OPEN_NODE(),
			GEO_SWITCH_CASE(3, geo_switch_anim_state),
			GEO_OPEN_NODE(),
				GEO_NODE_START(),
				GEO_OPEN_NODE(),
					GEO_DISPLAY_LIST(LAYER_OPAQUE, m_classc_dl_mesh_layer_1),
				GEO_CLOSE_NODE(),
				GEO_BRANCH(1, m_classc_switch_opt1),
				GEO_BRANCH(1, m_classc_switch_opt2),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
