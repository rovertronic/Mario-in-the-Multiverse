#include <ultra64.h>
#include "sm64.h"
#include "surface_terrains.h"
#include "geo_commands.h"

#include "make_const_nonconst.h"

// Note: This bin does not use bin IDs, unlike the other segmented bins.
#include "mario/model.inc.c"

#include "bubble/model.inc.c"

#include "walk_smoke/model.inc.c"

#include "burn_smoke/model.inc.c"

#include "small_water_splash/model.inc.c"

#include "water_wave/model.inc.c"

#include "sparkle/model.inc.c"

#include "water_splash/model.inc.c"

#include "white_particle_small/model.inc.c"

#include "sparkle_animation/model.inc.c"

#ifdef S2DEX_TEXT_ENGINE
#include "src/s2d_engine/config.h"
#include FONT_C_FILE
#endif

#include "level_pipe/collision.inc.c"
#include "level_pipe/model.inc.c"
#include "round_box/model.inc.c"
#include "dpad/model.inc.c"
#include "ability/model.inc.c"
#include "default_hand/model.inc.c"
#include "saw_hand/model.inc.c"
#include "main_menu/model.inc.c"
#include "selector/model.inc.c"
#include "ability_unlock/model.inc.c"
#include "hudbar/model.inc.c"
#include "generic_pause/model.inc.c"
#include "ability_sign/model.inc.c"
#include "hat/model.inc.c"
#include "hp_8/model.inc.c"
#include "hp_7/model.inc.c"
#include "hp_6/model.inc.c"
#include "hp_5/model.inc.c"
#include "hp_4/model.inc.c"
#include "hp_3/model.inc.c"
#include "hp_2/model.inc.c"
#include "hp_1/model.inc.c"
#include "cutter_blade/model.inc.c"
#include "cutter_hand/model.inc.c"
#include "cutter_hat/model.inc.c"
#include "mario/anims/data.inc.c"
#include "mario/anims/table.inc.c"
#include "cutter_blast/model.inc.c"
#include "cutter_particle_slash/model.inc.c"
#include "dragonite/model.inc.c"
#include "dragonite/anims/data.inc.c"
#include "dragonite/anims/table.inc.c"
#include "pokeball_hand/model.inc.c"