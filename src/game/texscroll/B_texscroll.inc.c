#include "levels/B/header.h"
#include "levels/B/texscroll.inc.c"
#include "levels/B/waterfall/texscroll.inc.c"
#include "levels/B/debris/texscroll.inc.c"
void scroll_textures_B() {
	scroll_B();
	scroll_B_level_geo_waterfall();
			scroll_B_level_geo_debris();
}
