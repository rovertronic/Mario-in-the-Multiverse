// 0x0F0004FC
const GeoLayout heart_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0x64, 100),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, heart_seg8_dl_0800DFE0),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

const GeoLayout ability_heart_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0x64, 100),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ability_heart_gfx),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
