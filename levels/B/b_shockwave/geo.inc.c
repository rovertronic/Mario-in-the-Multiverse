#include "src/game/envfx_snow.h"

const GeoLayout b_shockwave_geo[] = {
   GEO_CULLING_RADIUS(10000),
   GEO_OPEN_NODE(),
      GEO_ASM(GEO_TRANSPARENCY_MODE_DECAL, geo_update_layer_transparency),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, b_shockwave_001_displaylist_mesh_layer_6),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
