#include "levels/sb/header.h"
#include "levels/sb/sb_stairs/texscroll.inc.c"
#include "levels/sb/sbsky/texscroll.inc.c"
#include "levels/sb/sb_gap/texscroll.inc.c"
#include "levels/sb/sb_train/texscroll.inc.c"
void scroll_textures_sb() {
	scroll_sb_level_geo_sb_stairs();
	scroll_sb_level_dl_sbsky();
	scroll_sb_level_geo_sb_gap();
	scroll_sb_level_geo_sb_train();
}
