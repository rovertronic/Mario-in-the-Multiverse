#include "levels/k/header.h"
#include "levels/k/texscroll.inc.c"
#include "levels/k/electrohead/texscroll.inc.c"
#include "levels/k/k_tv1/texscroll.inc.c"
#include "levels/k/k_tv2/texscroll.inc.c"
#include "levels/k/k_tv3/texscroll.inc.c"
#include "levels/k/k_tv4/texscroll.inc.c"
void scroll_textures_k() {
	scroll_k();
	scroll_k_level_geo_electrohead();
	scroll_k_level_geo_k_tv1();
	scroll_k_level_geo_k_tv2();
	scroll_k_level_geo_k_tv3();
	scroll_k_level_geo_k_tv4();
}
