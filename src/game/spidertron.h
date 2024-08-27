#ifndef H_SPIDERTRON
#define H_SPIDERTRON

#include <PR/ultratypes.h>

#include "macros.h"
#include "types.h"

#define SPIDERTRON_LIMB_LENGTH 600.0f
#define SPIDERTRON_LIMB_MOVE_THRESHOLD 50.0f

struct Spidertron;
typedef struct Spidertron Spidertron;

typedef struct {
    Vec3f shoulder;
    Vec3f elbow;
    Vec3f wrist;
    Vec3f move_start;
    Vec3f move_end;
    f32 move_progress;
    struct Object * obj[2];
    u8 moving;
    Spidertron * owner;
} SpidertronLimb;

struct Spidertron {
    struct Object * obj;
    SpidertronLimb limbs[8];
    int moving_limbs;
};

void spidertron_update_limb(SpidertronLimb * limb);
void spidertron_create_limb(SpidertronLimb * limb, Spidertron * head);
void spidertron_create(Spidertron * head, struct Object * obj);
void spidertron_update(Spidertron * head);

#endif