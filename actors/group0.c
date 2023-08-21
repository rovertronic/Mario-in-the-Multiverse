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
#include "meter_bg/model.inc.c"
#include "meter_8/model.inc.c"
#include "meter_7/model.inc.c"
#include "meter_6/model.inc.c"
#include "meter_5/model.inc.c"
#include "meter_4/model.inc.c"
#include "meter_3/model.inc.c"
#include "meter_2/model.inc.c"
#include "meter_1/model.inc.c"
#include "meter_hp/model.inc.c"
#include "meter_breath/model.inc.c"
#include "meter_aku/model.inc.c"
#include "meter_phase/model.inc.c"
#include "meter_rocket/model.inc.c"
#include "meter_chronos/model.inc.c"
#include "meter_booster/model.inc.c"
#include "e__mario/model.inc.c"
#include "e__mario/anims/data.inc.c"
#include "e__mario/anims/table.inc.c"
#include "e_rocket_blast/model.inc.c"
#include "e_sg_smoke/model.inc.c"
#include "e_sg_wall_damage/model.inc.c"
#include "e_sg_piece/model.inc.c"
#include "e_sg_spark/model.inc.c"
#include "e_muzzle_flash/model.inc.c"
#include "mario_k/model.inc.c"
#include "ability_d_mask/model.inc.c"
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
#include "nitro/model.inc.c"
#include "pokeball_hand/model.inc.c"
#include "bigdaddyhat/model.inc.c"
#include "bigdaddyhand/model.inc.c"

#include "phasewalk_hand/model.inc.c"
#include "samplesphere/model.inc.c"

#include "rocket_hand/model.inc.c"
#include "rocket_button_off/model.inc.c"
#include "rocket_button_on/model.inc.c"

#include "squid/model.inc.c"
#include "squid/anims/data.inc.c"
#include "squid/anims/table.inc.c"
#include "squid_hat/model.inc.c"
#include "knight_mario/model.inc.c"
#include "pt_mb/collision.inc.c"
#include "pt_mb/model.inc.c"
#include "hat_f/model.inc.c"
#include "hand_f/model.inc.c"
#include "aim_f/model.inc.c"

#include "hand_m/model.inc.c"
#include "bubble_hat/model.inc.c"

#include "net_hand_2/model.inc.c"
#include "checkpoint_flag/model.inc.c"
#include "checkpoint_flag/anims/data.inc.c"
#include "checkpoint_flag/anims/table.inc.c"
#include "flipswitch3/model.inc.c"
#include "flipswitch1/model.inc.c"
#include "flipswitch2/model.inc.c"
#include "flipswitch/collision.inc.c"
#include "noteblock/collision.inc.c"
#include "noteblock/model.inc.c"
#include "star_piece/model.inc.c"
#include "concrete_block/model.inc.c"
#include "concrete_block/collision.inc.c"

#include "concrete_block_crack1/model.inc.c"
#include "concrete_block_crack2/model.inc.c"

#include "dbp/model.inc.c"