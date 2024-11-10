#include "levels/bowser_course/header.h"
#include "levels/bowser_course/matplatform/texscroll.inc.c"
#include "levels/bowser_course/texscroll.inc.c"
#include "levels/bowser_course/bc_stair/texscroll.inc.c"
#include "levels/bowser_course/bc_stair_2/texscroll.inc.c"
#include "levels/bowser_course/mverses_sky/texscroll.inc.c"
#include "levels/bowser_course/bc_atreus/texscroll.inc.c"
#include "levels/bowser_course/bc_bosslanding/texscroll.inc.c"
#include "levels/bowser_course/sb_gap/texscroll.inc.c"
#include "levels/bowser_course/sb_train/texscroll.inc.c"
#include "levels/bowser_course/bc_crystalp/texscroll.inc.c"
#include "levels/bowser_course/bc_crystalgp/texscroll.inc.c"
#include "levels/bowser_course/bc_laser/texscroll.inc.c"
#include "levels/bowser_course/bc_laseremit/texscroll.inc.c"
void scroll_textures_bowser_course() {
	scroll_bowser_course_level_geo_matplatform();
	scroll_bowser_course();
	scroll_bowser_course_level_geo_bc_stair();
	scroll_bowser_course_level_geo_bc_stair_2();
	scroll_bowser_course_level_dl_mverses_sky();
	scroll_bowser_course_level_geo_bc_atreus();
	scroll_bowser_course_level_geo_bc_bosslanding();
	scroll_sb_level_geo_sb_gap();
	scroll_sb_level_geo_sb_train();
	scroll_bowser_course_level_geo_bc_crystalp();
	scroll_bowser_course_level_geo_bc_crystalgp();
	scroll_bowser_course_level_geo_bc_laser();
	scroll_bowser_course_level_geo_bc_laseremit();
}
