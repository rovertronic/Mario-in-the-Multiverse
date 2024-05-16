#include "levels/e/header.h"
#include "levels/e/e_candelabra/texscroll.inc.c"
#include "levels/e/e_medkit/texscroll.inc.c"
#include "levels/e/e_shells/texscroll.inc.c"
#include "levels/e/texscroll.inc.c"
#include "levels/e/e_red_door_candle/texscroll.inc.c"
#include "levels/e/e_candelabra_o/texscroll.inc.c"
void scroll_textures_e() {
		scroll_e_level_geo_e_candelabra();
				scroll_e_level_geo_e_medkit();
	scroll_e_level_geo_e_shells();
		scroll_e();
	scroll_e_level_geo_e_red_door_candle();
	scroll_e_level_geo_e_candelabra_o();
}
