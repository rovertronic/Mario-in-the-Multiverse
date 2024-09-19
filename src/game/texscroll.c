#include "types.h"
#include "include/segment_symbols.h"
#include "memory.h"
#include "engine/math_util.h"
#include "src/engine/behavior_script.h"
#include "tile_scroll.h"
#include "texscroll.h"

#ifdef TARGET_N64
#define SCROLL_CONDITION(condition) condition
#else
#define SCROLL_CONDITION(condition) 1
#endif


#include "src/game/texscroll/group0_texscroll.inc.c"
#include "src/game/texscroll/g_texscroll.inc.c"
#include "src/game/texscroll/B_texscroll.inc.c"
#include "src/game/texscroll/a_texscroll.inc.c"
#include "src/game/texscroll/f_texscroll.inc.c"
#include "src/game/texscroll/i_texscroll.inc.c"
#include "src/game/texscroll/J_texscroll.inc.c"
#include "src/game/texscroll/m_texscroll.inc.c"
#include "src/game/texscroll/o_texscroll.inc.c"
#include "src/game/texscroll/d_texscroll.inc.c"
#include "src/game/texscroll/n_texscroll.inc.c"
#include "src/game/texscroll/h_texscroll.inc.c"
#include "src/game/texscroll/castle_inside_texscroll.inc.c"
#include "src/game/texscroll/e_texscroll.inc.c"
#include "src/game/texscroll/l_texscroll.inc.c"
#include "src/game/texscroll/bowser_course_texscroll.inc.c"
#include "src/game/texscroll/c_texscroll.inc.c"

#include "src/game/texscroll/k_texscroll.inc.c"
#include "src/game/texscroll/sb_texscroll.inc.c"
void scroll_textures() {
	if(SCROLL_CONDITION(sSegmentROMTable[0x4] == (uintptr_t)_group0_yay0SegmentRomStart)) {
		scroll_textures_group0();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_g_segment_7SegmentRomStart)) {
		scroll_textures_g();
	}
	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_B_segment_7SegmentRomStart)) {
		scroll_textures_B();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_f_segment_7SegmentRomStart)) {
		scroll_textures_f();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_i_segment_7SegmentRomStart)) {
		scroll_textures_i();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_J_segment_7SegmentRomStart)) {
		scroll_textures_J();
	}
	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_m_segment_7SegmentRomStart)) {
		scroll_textures_m();
	}
	
	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_o_segment_7SegmentRomStart)) {
		scroll_textures_o();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_d_segment_7SegmentRomStart)) {
		scroll_textures_d();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_n_segment_7SegmentRomStart)) {
		scroll_textures_n();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_c_segment_7SegmentRomStart)) {
		scroll_textures_c();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_a_segment_7SegmentRomStart)) {
		scroll_textures_a();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_h_segment_7SegmentRomStart)) {
		scroll_textures_h();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_castle_inside_segment_7SegmentRomStart)) {
		scroll_textures_castle_inside();
	}
	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_e_segment_7SegmentRomStart)) {
		scroll_textures_e();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_l_segment_7SegmentRomStart)) {
		scroll_textures_l();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_bowser_course_segment_7SegmentRomStart)) {
		scroll_textures_bowser_course();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_k_segment_7SegmentRomStart)) {
		scroll_textures_k();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_sb_segment_7SegmentRomStart)) {
		scroll_textures_sb();
	}

}
