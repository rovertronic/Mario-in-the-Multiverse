#ifndef HINTS_H
#define HINTS_H

#include "types.h"

struct hint {
    char * hint_text;
    u32 dependancies;
};

typedef struct hint hint;

#define ABILITY_FLAG_DEFAULT           (1 << 0)
#define ABILITY_FLAG_CUTTER            (1 << 1)
#define ABILITY_FLAG_BUBBLE_HAT        (1 << 2)
#define ABILITY_FLAG_SQUID             (1 << 3)
#define ABILITY_FLAG_SHOCK_ROCKET      (1 << 4)
#define ABILITY_FLAG_PHASEWALK         (1 << 5)
#define ABILITY_FLAG_BIG_DADDY         (1 << 6)
#define ABILITY_FLAG_KNIGHT            (1 << 7)
#define ABILITY_FLAG_CHRONOS           (1 << 8)
#define ABILITY_FLAG_E_SHOTGUN         (1 << 9)
#define ABILITY_FLAG_GADGET_WATCH      (1 << 10)
#define ABILITY_FLAG_HM_FLY            (1 << 11)
#define ABILITY_FLAG_AKU               (1 << 12)
#define ABILITY_FLAG_ESTEEMED_MORTAL   (1 << 13)
#define ABILITY_FLAG_MARBLE            (1 << 14)
#define ABILITY_FLAG_DASH_BOOSTER      (1 << 15)
#define ABILITY_FLAG_UTIL_COMPASS      (1 << 16)
#define ABILITY_FLAG_UTIL_MILK         (1 << 17)
#define ABILITY_FLAG_UTIL_MIRROR       (1 << 18)

#endif