#ifndef E_DOOR_LIGHT_H
#define E_DOOR_LIGHT_H

#include <PR/ultratypes.h>
#include "include/types.h"

struct E_DoorLight {
    Vec3s verts[2];
    struct Object *door;
};

void e__create_door_light(struct Object *door);
Gfx *e__door_light(s32 callContext, struct GraphNode *node, UNUSED Mat4 unused);

#endif//E_DOOR_LIGHT_H
