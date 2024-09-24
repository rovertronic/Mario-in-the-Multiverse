#include "src/game/envfx_snow.h"

const GeoLayout sb_blast_geo[] = {
	GEO_CULLING_RADIUS(3000),
	GEO_OPEN_NODE(),
		GEO_ASM(0, geo_update_layer_transparency),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sb_blast_Cylinder_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
