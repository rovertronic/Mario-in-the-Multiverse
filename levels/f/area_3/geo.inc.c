#include "src/game/envfx_snow.h"

const GeoLayout f_area_3_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(2, geo_switch_area),
		GEO_OPEN_NODE(),
			GEO_BRANCH(1, f_dl_1_3_room_geo),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout f_dl_1_3_room_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ROTATION_NODE_WITH_DL(LAYER_OPAQUE, 90, 0, 0, f_dl_Area3Vis_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT, f_dl_Area3Vis_mesh_layer_5),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, f_dl_Area3Vis_mesh_layer_6),
			GEO_DISPLAY_LIST(LAYER_OPAQUE_DECAL, f_dl_Area3Vis_mesh_layer_2),
		GEO_CLOSE_NODE(),
		GEO_ASM(0, e__shotgun_effects),
		GEO_ROTATION_NODE(LAYER_OPAQUE, 0, -180, 0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout f_area_3[] = {
	GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
	GEO_OPEN_NODE(),
		GEO_ZBUFFER(0),
		GEO_OPEN_NODE(),
			GEO_NODE_ORTHO(100.0000),
			GEO_OPEN_NODE(),
				GEO_BACKGROUND_COLOR(0x0001),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_ZBUFFER(1),
		GEO_OPEN_NODE(),
			GEO_CAMERA_FRUSTUM_WITH_FUNC(45.0000, 100, 30000, geo_camera_fov),
			GEO_OPEN_NODE(),
				GEO_CAMERA(CAMERA_MODE_8_DIRECTIONS, 0, 0, 0, 0, -100, 0, geo_camera_main),
				GEO_OPEN_NODE(),
					GEO_BRANCH(1, f_area_3_geo),
					GEO_RENDER_OBJ(),
					GEO_ASM(ENVFX_MODE_NONE, geo_envfx_main),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
