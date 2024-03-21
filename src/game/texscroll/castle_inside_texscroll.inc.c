#include "levels/castle_inside/header.h"
#include "levels/castle_inside/texscroll.inc.c"
#include "levels/castle_inside/hubsky/texscroll.inc.c"
#include "levels/castle_inside/hubsky2/texscroll.inc.c"
void scroll_textures_castle_inside() {
	scroll_castle_inside();
	scroll_castle_inside_level_dl_hubsky();
	scroll_castle_inside_level_dl_hubsky2();
}
