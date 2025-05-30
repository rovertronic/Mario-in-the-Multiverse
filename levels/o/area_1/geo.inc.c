#include "src/game/envfx_snow.h"

const GeoLayout o_area_1_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(3, geo_switch_area),
		GEO_OPEN_NODE(),
			GEO_BRANCH(1, o_dl_1_room_normal_geo),
			GEO_BRANCH(1, o_dl_2_room_indoor_geo),
		GEO_CLOSE_NODE(),
		GEO_ASM(0, geo_update_uv_lights),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 0, -2484, 0),
		GEO_ASM(0, e__shotgun_effects),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 0, -2484, 0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout o_dl_1_room_normal_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, o_dl_bloodsiding_mesh_layer_6),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, o_dl_bloodvis_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, o_dl_bloodvis_mesh_layer_6),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_OPAQUE, -17160, -501, -623, 0, -180, 0, o_dl_Cube_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, o_dl_ishard_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, o_dl_room1_visonly_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, o_dl_viscol_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, o_dl_viscol_mesh_layer_4),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 250, -2494, 10, o_dl_viscol_001_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE_DECAL, 250, -2494, 10, o_dl_viscol_003_mesh_layer_2),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 250, -2494, 10, o_dl_visual_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT, o_dl_visual_mesh_layer_5),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, o_dl_visual_mesh_layer_6),
			GEO_DISPLAY_LIST(LAYER_ALPHA, o_dl_visual_mesh_layer_4),
			GEO_DISPLAY_LIST(LAYER_OPAQUE_DECAL, o_dl_visual_mesh_layer_2),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, o_dl_zuvlight_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout o_dl_2_room_indoor_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, o_dl_issoft_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, o_dl_issoft_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, o_dl_viscol_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, o_dl_viscol_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, o_dl_room2_collision_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout o_area_1[] = {
	GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
	GEO_OPEN_NODE(),
		GEO_ZBUFFER(1),
		GEO_OPEN_NODE(),
			GEO_CAMERA_FRUSTUM_WITH_FUNC(45.0000, 127, 65535, geo_camera_fov),
			GEO_OPEN_NODE(),
				GEO_CAMERA(CAMERA_MODE_8_DIRECTIONS, 0, 0, 0, 0, -100, 0, geo_camera_main),
				GEO_OPEN_NODE(),
					GEO_BRANCH(1, o_area_1_geo),
					GEO_RENDER_OBJ(),
					GEO_ASM(ENVFX_MODE_NONE, geo_envfx_main),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
