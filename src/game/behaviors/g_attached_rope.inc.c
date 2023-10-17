#include "actors/attached_rope/geo_header.h"
#include "src/game/geo_misc.h"

#define ATTACHABLE_ROPE_DONT_CHECK_CEIL 1

static struct ObjectHitbox sAttachedRopeHitbox = {
    /* interactType:      */ INTERACT_NONE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 80,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 70,
    /* hurtboxHeight:     */ 100,
};

void bhv_g_attached_rope_init(void) {
    o->oGravity = 2.0f;
    o->oVelY = 0;

        struct Surface *surf;
        Vec3f originPos;
        Vec3f hitpos;
        Vec3f raydir;
        u8 rayResult = 0;

        raydir[0] = 0.0f;
        raydir[1] = 10000.0f;
        raydir[2] = 0.0f;

        vec3f_set(hitpos, 0.0f, 0.0f, 0.0f);

        vec3f_set(originPos, o->oPosX, o->oPosY, o->oPosZ);
        // ceil check
        find_surface_on_ray(originPos, raydir, &surf, hitpos, 4U);
        if (surf != NULL)
            rayResult = 3;

        if (rayResult == 3) {
            o->oBehParams = (o->oBehParams & 0xFFFF0000) | (u32)(hitpos[1] - o->oPosY);
        } else {
            obj_mark_for_deletion(o);
        }
    obj_set_hitbox(o, &sAttachedRopeHitbox);
    o->oUpdateRopeSize = TRUE;
}

u8 mario_can_cut_rope(void) {
    if (using_ability(ABILITY_CUTTER)) {
        if (gMarioState->action == ACT_FINAL_CUTTER_SEQUENCE || gMarioState->action == ACT_CUTTER_DASH 
            || gMarioState->action == ACT_DIVE || gMarioState->action == ACT_DIVE_SLIDE) {
                return TRUE;
        }
    }
    if (using_ability(ABILITY_CHRONOS)) {
        if (gMarioState->action == ACT_MOVE_PUNCHING || gMarioState->action == ACT_PUNCHING) {
                return TRUE;
        }
    }
    if (using_ability(ABILITY_ESTEEMED_MORTAL)) {
        if (gMarioState->action == ACT_ABILITY_AXE_JUMP) {
                return TRUE;
        }
    }

    return FALSE;
}

void bhv_g_attached_rope_loop(void) {
    for (int i = 0; i < o->numCollidedObjs; i++) {
        struct Object *other = o->collidedObjs[i];
        f32 marioHigherPos = gMarioState->pos[1] + 100;
        if ((obj_has_behavior(other, bhvCutterBlade) && other->oPosY - 30 > o->oPosY) || 
            (other == gMarioState->marioObj && marioHigherPos - 30 > o->oPosY && mario_can_cut_rope())) {
                f32 otherObjY = (other == gMarioState->marioObj ? marioHigherPos : other->oPosY);
                play_sound(SOUND_ABILITY_CUTTER_CATCH, o->header.gfx.cameraToObject);
                struct Object *cutRope = spawn_object_relative(0, 0, otherObjY - o->oPosY, 0, o, MODEL_ATTACHED_ROPE, bhvGAttachedRope);
                o->oBehParams = (o->oBehParams & 0xFFFF0000) | (u32)(otherObjY - o->oPosY);
                o->parentObj->oBehParams = (o->oBehParams & 0xFFFF00FF) | 0x0000;
                cur_obj_become_intangible();
                o->oUpdateRopeSize = TRUE;
                o->oAction = 1;
                o->oTimer = 0;
        }
    }

    if (o->oUpdateRopeSize) {
        u16 ropeHeight = GET_BPARAM34(o->oBehParams);
        o->hitboxHeight = ropeHeight + 10;
        o->hurtboxHeight = ropeHeight;
        o->oUpdateRopeSize = FALSE;
    }

    o->oFaceAngleYaw = atan2s(gCamera->pos[2] - o->oPosZ, gCamera->pos[0] - o->oPosX);

    if (o->oAction == 1) {
        o->oVelY -= o->oGravity;
        o->oPosY += o->oVelY;

        if (o->oTimer >= 60) {
            obj_mark_for_deletion(o);
        }
    }

    
}

Gfx *geo_generate_attached_rope(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
     Vtx *vertexBuffer;
    Gfx *dlStart, *dlHead;
    struct Object *obj;
    struct GraphNode *graphNode;
    s32 objDispX;
    s32 objDispY;
    s32 s, t;
    s16 startS, startT;
    f32 offsetS;
    f32 offsetT;
    graphNode = node;

    if (callContext == GEO_CONTEXT_RENDER) {
         obj = (struct Object *) gCurGraphNodeObject; 
        
        
        objDispY = (f32)GET_BPARAM34(obj->oBehParams);
        startS = 0;
        startT = -32000;
        offsetS = 1;
        offsetT = -(f32)objDispY / 100;
        s = startS - ((offsetS * 16) * 32U);
        t = startT - ((offsetT * 32) * 32U);
        graphNode->flags = (graphNode->flags & 0xFF) | (LAYER_ALPHA << 8);
        vertexBuffer = alloc_display_list(4 * sizeof(Vtx));
        
        make_vertex(vertexBuffer, 0, -20, objDispY, 0, startS, t, 0xFF, 0xE8, 0xBE, 0xFF);
        make_vertex(vertexBuffer, 1, 20, objDispY, 0, s, t, 0xFF, 0xE8, 0xBE, 0xFF);
        make_vertex(vertexBuffer, 2, 20, 0, 0, s, startT, 0xFF, 0xE8, 0xBE, 0xFF);
        make_vertex(vertexBuffer, 3, -20, 0, 0, startS, startT, 0xFF, 0xE8, 0xBE, 0xFF);

        dlHead = alloc_display_list(sizeof(Gfx) * (32 + 4));
        dlStart = dlHead;
        gSPDisplayList(dlHead++, mat_attached_rope_f3dlite_material_013);
        gSPVertex(dlHead++, VIRTUAL_TO_PHYSICAL(vertexBuffer), 4, 0);
        gSP2Triangles(dlHead++, 0, 1, 2, 0, 0, 2, 3, 0);
        gSPDisplayList(dlHead++, mat_revert_attached_rope_f3dlite_material_013);
        gSPEndDisplayList(dlHead++);
        
    }

    return dlStart;

}