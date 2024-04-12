#include "levels/bowser_course/header.h"
#include "levels/bowser_course/matplatform/texscroll.inc.c"
#include "levels/bowser_course/texscroll.inc.c"
#include "levels/bowser_course/bc_stair/texscroll.inc.c"
void scroll_textures_bowser_course() {
	scroll_bowser_course_level_geo_matplatform();
	scroll_bowser_course();
	scroll_bowser_course_level_geo_bc_stair();
}
