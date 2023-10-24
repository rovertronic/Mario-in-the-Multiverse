#include "levels/o/header.h"
#include "levels/o/texscroll.inc.c"
#include "levels/o/o_spooky_sky/texscroll.inc.c"
#include "levels/o/o_flame/texscroll.inc.c"
void scroll_textures_o() {
	scroll_o();
	scroll_o_level_dl_o_spooky_sky();
	scroll_o_level_geo_o_flame();
}
