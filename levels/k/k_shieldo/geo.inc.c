#include "src/game/envfx_snow.h"

const GeoLayout k_shieldo_switch_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, -5, NULL),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 69, 0, k_shieldo_Butt_mesh_layer_1_mat_override_muzzle_flash_empty_0),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, k_shieldo_Chest_skinned_mesh_layer_1_mat_override_muzzle_flash_empty_0),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 30, 0, k_shieldo_Chest_mesh_layer_1_mat_override_muzzle_flash_empty_0),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 39, 0, k_shieldo_Head_mesh_layer_1_mat_override_muzzle_flash_empty_0),
					GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 27, 30, 0, -90, 0, -88),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Left_Upper_Arm_mesh_layer_1_mat_override_muzzle_flash_empty_0),
						GEO_OPEN_NODE(),
							GEO_DISPLAY_LIST(LAYER_OPAQUE, k_shieldo_Left_Forearm_skinned_mesh_layer_1_mat_override_muzzle_flash_empty_0),
							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 29, 0, 0, 0, -4),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Left_Forearm_mesh_layer_1_mat_override_muzzle_flash_empty_0),
								GEO_OPEN_NODE(),
									GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 27, 0, 0, 0, 2),
									GEO_OPEN_NODE(),
										GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Left_Hand_mesh_layer_1_mat_override_muzzle_flash_empty_0),
										GEO_OPEN_NODE(),
											GEO_DISPLAY_LIST(LAYER_TRANSPARENT, k_shieldo_Left_Hand_mesh_layer_5_mat_override_muzzle_flash_empty_0),
										GEO_CLOSE_NODE(),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
					GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -27, 30, 0, -90, 0, 88),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Right_Upper_Arm_mesh_layer_1_mat_override_muzzle_flash_empty_0),
						GEO_OPEN_NODE(),
							GEO_DISPLAY_LIST(LAYER_OPAQUE, k_shieldo_Right_Forearm_skinned_mesh_layer_1_mat_override_muzzle_flash_empty_0),
							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 29, 0, 0, 0, 4),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Right_Forearm_mesh_layer_1_mat_override_muzzle_flash_empty_0),
								GEO_OPEN_NODE(),
									GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 27, 0, 0, 0, -2),
									GEO_OPEN_NODE(),
										GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Right_Hand_mesh_layer_1_mat_override_muzzle_flash_empty_0),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 13, 6, 0, 178, 0, 0),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Left_Thigh_mesh_layer_1_mat_override_muzzle_flash_empty_0),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_OPAQUE, k_shieldo_Left_Lower_Leg_skinned_mesh_layer_1_mat_override_muzzle_flash_empty_0),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 29, 0, 4, 0, 0),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Left_Lower_Leg_mesh_layer_1_mat_override_muzzle_flash_empty_0),
							GEO_OPEN_NODE(),
								GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 35, 0, -82, 0, 0),
								GEO_OPEN_NODE(),
									GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Left_Foot_mesh_layer_1_mat_override_muzzle_flash_empty_0),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -13, 6, 0, 178, 0, 0),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Right_Thigh_mesh_layer_1_mat_override_muzzle_flash_empty_0),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_OPAQUE, k_shieldo_Right_Lower_Leg_skinned_mesh_layer_1_mat_override_muzzle_flash_empty_0),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 29, 0, 4, 0, 0),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Right_Lower_Leg_mesh_layer_1_mat_override_muzzle_flash_empty_0),
							GEO_OPEN_NODE(),
								GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 35, 0, -82, 0, 0),
								GEO_OPEN_NODE(),
									GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Right_Foot_mesh_layer_1_mat_override_muzzle_flash_empty_0),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
			GEO_SHADOW(1, 150, 100),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout k_shieldo_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(2, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, -5, NULL),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 69, 0, k_shieldo_Butt_mesh_layer_1),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_OPAQUE, k_shieldo_Chest_skinned_mesh_layer_1),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 30, 0, k_shieldo_Chest_mesh_layer_1),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 39, 0, k_shieldo_Head_mesh_layer_1),
							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 27, 30, 0, -90, 0, -88),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Left_Upper_Arm_mesh_layer_1),
								GEO_OPEN_NODE(),
									GEO_DISPLAY_LIST(LAYER_OPAQUE, k_shieldo_Left_Forearm_skinned_mesh_layer_1),
									GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 29, 0, 0, 0, -4),
									GEO_OPEN_NODE(),
										GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Left_Forearm_mesh_layer_1),
										GEO_OPEN_NODE(),
											GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 27, 0, 0, 0, 2),
											GEO_OPEN_NODE(),
												GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Left_Hand_mesh_layer_1),
												GEO_OPEN_NODE(),
													GEO_DISPLAY_LIST(LAYER_TRANSPARENT, k_shieldo_Left_Hand_mesh_layer_5),
												GEO_CLOSE_NODE(),
											GEO_CLOSE_NODE(),
										GEO_CLOSE_NODE(),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -27, 30, 0, -90, 0, 88),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Right_Upper_Arm_mesh_layer_1),
								GEO_OPEN_NODE(),
									GEO_DISPLAY_LIST(LAYER_OPAQUE, k_shieldo_Right_Forearm_skinned_mesh_layer_1),
									GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 29, 0, 0, 0, 4),
									GEO_OPEN_NODE(),
										GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Right_Forearm_mesh_layer_1),
										GEO_OPEN_NODE(),
											GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 27, 0, 0, 0, -2),
											GEO_OPEN_NODE(),
												GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Right_Hand_mesh_layer_1),
											GEO_CLOSE_NODE(),
										GEO_CLOSE_NODE(),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 13, 6, 0, 178, 0, 0),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Left_Thigh_mesh_layer_1),
							GEO_OPEN_NODE(),
								GEO_DISPLAY_LIST(LAYER_OPAQUE, k_shieldo_Left_Lower_Leg_skinned_mesh_layer_1),
								GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 29, 0, 4, 0, 0),
								GEO_OPEN_NODE(),
									GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Left_Lower_Leg_mesh_layer_1),
									GEO_OPEN_NODE(),
										GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 35, 0, -82, 0, 0),
										GEO_OPEN_NODE(),
											GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Left_Foot_mesh_layer_1),
										GEO_CLOSE_NODE(),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -13, 6, 0, 178, 0, 0),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Right_Thigh_mesh_layer_1),
							GEO_OPEN_NODE(),
								GEO_DISPLAY_LIST(LAYER_OPAQUE, k_shieldo_Right_Lower_Leg_skinned_mesh_layer_1),
								GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 29, 0, 4, 0, 0),
								GEO_OPEN_NODE(),
									GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Right_Lower_Leg_mesh_layer_1),
									GEO_OPEN_NODE(),
										GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 35, 0, -82, 0, 0),
										GEO_OPEN_NODE(),
											GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, k_shieldo_Right_Foot_mesh_layer_1),
										GEO_CLOSE_NODE(),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
					GEO_SHADOW(1, 150, 100),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, k_shieldo_switch_opt1),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
