#include "actors/group0.h"
#include "actors/ability_unlock/texscroll.inc.c"
#include "actors/e_rocket_blast/texscroll.inc.c"
#include "actors/e_sg_spark/texscroll.inc.c"
#include "actors/e_sg_smoke/texscroll.inc.c"
#include "actors/cutter_particle_slash/texscroll.inc.c"
void scroll_textures_group0() {
	scroll_actor_geo_ability_unlock();
		scroll_actor_geo_cutter_particle_slash();
	scroll_actor_geo_e_rocket_blast();
		scroll_actor_dl_e_sg_spark();
	scroll_actor_dl_e_sg_smoke();
}
