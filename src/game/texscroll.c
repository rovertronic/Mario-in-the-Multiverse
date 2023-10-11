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
#include "src/game/texscroll/B_texscroll.inc.c"
#include "src/game/texscroll/f_texscroll.inc.c"
#include "src/game/texscroll/o_texscroll.inc.c"
void scroll_textures() {
	if(SCROLL_CONDITION(sSegmentROMTable[0x4] == (uintptr_t)_group0_yay0SegmentRomStart)) {
		scroll_textures_group0();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_B_segment_7SegmentRomStart)) {
		scroll_textures_B();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_f_segment_7SegmentRomStart)) {
		scroll_textures_f();
	}

	if(SCROLL_CONDITION(sSegmentROMTable[0x7] == (uintptr_t)_o_segment_7SegmentRomStart)) {
		scroll_textures_o();
	}

}
