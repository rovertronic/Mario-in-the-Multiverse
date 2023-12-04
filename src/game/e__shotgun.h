#ifndef E_SHOTGUN_H
#define E_SHOTGUN_H

#include <PR/ultratypes.h>
#include "include/types.h"

void e__set_upper_anim(struct MarioState *m, s32 animID);
void e__animate_upper(void);
void e__fire_shotgun(void);
void e__fire_shotgun_air(void);

#endif//E_SHOTGUN_H
