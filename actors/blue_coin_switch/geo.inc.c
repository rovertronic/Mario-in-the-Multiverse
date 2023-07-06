// 0x0F000000
const GeoLayout blue_coin_switch_geo[] = {
   GEO_CULLING_RADIUS(300),
   GEO_OPEN_NODE(),
      GEO_OPEN_NODE(),
      	GEO_SWITCH_CASE(2, geo_switch_anim_state),
			GEO_OPEN_NODE(),
            GEO_DISPLAY_LIST(LAYER_OPAQUE, blue_coin_switch_seg8_dl_08000E08),
            GEO_DISPLAY_LIST(LAYER_OPAQUE, star_switch_dl),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
