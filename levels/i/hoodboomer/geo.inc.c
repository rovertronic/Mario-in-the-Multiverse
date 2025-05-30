#include "src/game/envfx_snow.h"

const GeoLayout hoodboomer_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, hoodboomer_Bone_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, hoodboomer_Bone_002_skinned_mesh_layer_1),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 106, 0, hoodboomer_Bone_002_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, hoodboomer_Bone_001_skinned_mesh_layer_1),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 88, 0, hoodboomer_Bone_001_mesh_layer_1),
				GEO_OPEN_NODE(),
					GEO_DISPLAY_LIST(LAYER_ALPHA, hoodboomer_Bone_001_mesh_layer_4),
				GEO_CLOSE_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, -55, 61, 1, hoodboomer_Bone_004_mesh_layer_1),
				GEO_OPEN_NODE(),
					GEO_DISPLAY_LIST(LAYER_OPAQUE, hoodboomer_Bone_008_skinned_mesh_layer_1),
					GEO_ANIMATED_PART(LAYER_OPAQUE, -62, 0, 0, hoodboomer_Bone_008_mesh_layer_1),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, -96, -9, 0, hoodboomer_Bone_011_mesh_layer_1),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 55, 61, 1, hoodboomer_Bone_005_mesh_layer_1),
				GEO_OPEN_NODE(),
					GEO_DISPLAY_LIST(LAYER_OPAQUE, hoodboomer_Bone_009_skinned_mesh_layer_1),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 62, 0, 0, hoodboomer_Bone_009_mesh_layer_1),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 93, -9, 0, hoodboomer_Bone_013_mesh_layer_1),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hoodboomer_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hoodboomer_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
