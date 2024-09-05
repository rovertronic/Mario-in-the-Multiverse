//Warning: rushed & bad

#ifndef BULLET_SYSTEM_H
#define BULLET_SYSTEM_H

#include <PR/ultratypes.h>
#include "include/types.h"


#define BULLET_FLAG_NONE       (0 << 0)
#define BULLET_FLAG_ACTIVE     (1 << 0)
#define BULLET_FLAG_DEFLECTED  (1 << 1)

enum BulletType {
    BULLET_B,
    BULLET_F,
    BULLET_I,
    BULLET_K,
};

struct Bullet {
    Vec3f pos;
    f32   velF, velY, gravity;
    f32   hitSphereSize;
    s16   yaw;
    u32   timer  : 8;
    u32   flags  : 4;
    u32   damage : 4;
};


void dobj_spawn_bullet(Vec3f pos, s16 rX, s16 rY);

Gfx *dobj_bullets(s32 callContext);

s32 obj_hit_by_deflected_bullet(struct Object *obj, f32 objHitSphereSize);
s32 obj_hit_by_bullet(struct Object *obj, f32 objHitSphereSize);
void reset_bullet_system(void);

#endif //BULLET_SYSTEM_H