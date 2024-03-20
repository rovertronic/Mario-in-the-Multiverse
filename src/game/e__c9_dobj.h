#ifndef E__C9_DOBJ_H
#define E__C9_DOBJ_H

#include <PR/ultratypes.h>
#include "include/types.h"

struct E_C9Dobj {
    u32   state : 3;
    Vec3f pos;
    f32   velF, velY;
    f32   hitSphereSize;
    s16   pitch, yaw;
    u32   timer : 13;
    struct Object *attacker, *target;
};


void e__spawn_c9_dobj(struct Object *attacker, struct Object *target, s32 type, Vec3f pos, f32 velF, f32 hitSphereSize, s16 yaw);

Gfx *e__c9_dobj(s32 callContext, struct GraphNode *node, UNUSED Mat4 unused);

Gfx *e__c9_sky(s32 callContext, struct GraphNode *node, Mat4 mtxf);

#endif //E__C9_DOBJ_H