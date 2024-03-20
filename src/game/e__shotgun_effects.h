//Warning: rushed & bad

#ifndef E_SHOTGUN_EFFECTS_H
#define E_SHOTGUN_EFFECTS_H

#include <PR/ultratypes.h>
#include "include/types.h"


//type
struct SGWallDamage {
    u8 opacity;
    f32 scale;
    Vec3f pos;
    struct Surface *surf;
};

struct SGSmoke {
    s32 timer;
    f32 scale;
    f32 homeY;
    Vec3f pos;
};

struct SGPiece {
    f32 scale;
    Vec3f pos;
    Vec3f vel;
    s16 rX, rY;
};

struct SGSpark {
    f32 scale;
    Vec3f pos;
};


//spawn
struct SGWallDamage *e__sg_wall_damage(Vec3f pos, struct Surface *surf);
struct SGSmoke *e__sg_smoke(Vec3f pos);
struct SGPiece *e__sg_piece(Vec3f pos, Vec3f baseVel);
struct SGSpark *e__sg_spark(Vec3f pos, f32 scale);
void e__sg_obj_shot_sparks(struct Object *obj);
void e__sg_obj_explode(struct Object *obj, s32 count);


//main
Gfx *e__shotgun_effects(s32 callContext, struct GraphNode *node, UNUSED Mat4 unused);

#endif//E_SHOTGUN_EFFECTS_H
