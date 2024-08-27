#include "sm64.h"
#include "spidertron.h"
#include "engine/math_util.h"

#include "area.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "debug.h"
#include "dialog_ids.h"
#include "engine/behavior_script.h"
#include "engine/geo_layout.h"
#include "engine/surface_collision.h"
#include "game_init.h"
#include "helper_macros.h"
#include "ingame_menu.h"
#include "interaction.h"
#include "level_table.h"
#include "level_update.h"
#include "mario.h"
#include "mario_actions_cutscene.h"
#include "memory.h"
#include "obj_behaviors.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "rendering_graph_node.h"
#include "spawn_object.h"
#include "spawn_sound.h"
#include "puppylights.h"
#include "ability.h"

void spidertron_update_limb(SpidertronLimb * limb) {
    // Elbow solve

    // Get "up" angle relative to the shoulder->wrist line
    Mat4 shoulder_wrist_up;
    mtxf_lookat_nosuck(shoulder_wrist_up, limb->shoulder,limb->wrist,0);

    // Calculate shoulder->wrist line
    Vec3f shoulder_wrist_line_centre;
    for (int i = 0; i<3; i++) {
        shoulder_wrist_line_centre[i] = (limb->shoulder[i]+limb->wrist[i])/2.0f;
    }

    // Calculate elbow triangle height
    f32 shoulder_wrist_dist;
    vec3f_get_dist(limb->shoulder,limb->wrist,&shoulder_wrist_dist);
    f32 elbow_protrude = sqrtf(SPIDERTRON_LIMB_LENGTH * SPIDERTRON_LIMB_LENGTH - (shoulder_wrist_dist * shoulder_wrist_dist) / 4.0f);
    if (shoulder_wrist_dist > SPIDERTRON_LIMB_LENGTH * 2.0f) {
        elbow_protrude = 0.0f;
    }

    // Compute elbow position
    // Use "up" vector from the transform matrix to make our lives easy
    for (int i = 0; i<3; i++) {
        limb->elbow[i] = shoulder_wrist_line_centre[i] + ( shoulder_wrist_up[1][i] * elbow_protrude );
    }

    // Complete the satisfying IK chain... Set limb object transforms
    mtxf_lookat_nosuck(limb->obj[0]->transform,limb->shoulder,limb->elbow,0);
    vec3f_copy(&limb->obj[0]->transform[3][0],limb->shoulder);
    limb->obj[0]->header.gfx.throwMatrix = limb->obj[0]->transform;

    mtxf_lookat_nosuck(limb->obj[1]->transform,limb->elbow,limb->wrist,0);
    vec3f_copy(&limb->obj[1]->transform[3][0],limb->elbow);
    limb->obj[1]->header.gfx.throwMatrix = limb->obj[1]->transform;

    // Trigger a move if past the threshold

    if (!limb->moving) {
        // Stationary state
        if ((limb->owner->moving_limbs < 4)) {
            f32 error;
            vec3f_get_dist_squared(limb->wrist,limb->move_end,&error);

            if (error > SPIDERTRON_LIMB_MOVE_THRESHOLD*SPIDERTRON_LIMB_MOVE_THRESHOLD) {
                // Initiate a move
                vec3f_copy(limb->move_start,limb->wrist);
                limb->move_progress = 0.0f;
                limb->moving = TRUE;
                limb->owner->moving_limbs ++;
            }
        }
    } else {
        // Move to target
        if (limb->move_progress > 1.0f) {
            limb->move_progress = 1.0f;
            limb->moving = FALSE;
            limb->owner->moving_limbs --;
        }
        for (int i = 0; i<3; i++) {
            limb->wrist[i] = approach_f32_asymptotic(limb->move_start[i],limb->move_end[i],limb->move_progress);
        }
        limb->wrist[1] += sinf(limb->move_progress*3.14f)*100.0f;
        limb->move_progress += 0.1f;
    }

    // Forearm collision
    Vec3f hitpos;
    struct Surface * hit;
    Vec3f forearm_ray;
    vec3f_diff(forearm_ray,limb->wrist,limb->elbow);
    find_surface_on_ray(limb->elbow,forearm_ray,&hit,hitpos,RAYCAST_FIND_WALL);
    if (hit) {
        vec3f_copy(limb->wrist,hitpos);
    }

    // Upperarm collision
    Vec3f upperarm_ray;
    vec3f_diff(upperarm_ray,limb->elbow,limb->shoulder);
    find_surface_on_ray(limb->shoulder,upperarm_ray,&hit,hitpos,RAYCAST_FIND_WALL);
    if (hit) {
        vec3f_copy(limb->move_start,hitpos);
        vec3f_copy(limb->move_end,hitpos);
        limb->move_progress = 1.0f;
    }
}

void spidertron_create_limb(SpidertronLimb * limb, Spidertron * head) {

    limb->owner = head;

    vec3f_copy(limb->shoulder,gVec3fZero);
    vec3f_copy(limb->elbow,gVec3fZero);
    vec3f_copy(limb->wrist,gVec3fZero);
    vec3f_copy(limb->move_start,gVec3fZero);
    vec3f_copy(limb->move_end,gVec3fZero);
    limb->moving = FALSE;
    limb->move_progress = 0.0f;

    limb->obj[0] = spawn_object(gMarioObject,MODEL_SPIDERTRON_LIMB_1,bhvStaticObject);
    limb->obj[1] = spawn_object(gMarioObject,MODEL_SPIDERTRON_LIMB_1,bhvStaticObject);
}

void spidertron_create(Spidertron * head, struct Object * obj) {
    head->obj = obj;
    head->moving_limbs = 0;
    for (int i = 0; i < 8; i++) {
        spidertron_create_limb(&head->limbs[i],&head);
    }
}

void spidertron_update(Spidertron * head) {
    for (int i = 0; i < 8; i++) {
        // Update shoulder positions
        SpidertronLimb * limb = &head->limbs[i];

        s16 arm_angle = (i*0x2000)+0x1000;
        Vec3f shoulder_pos = {head->obj->oPosX + sins(arm_angle)*150.0f,head->obj->oPosY+150.0f,head->obj->oPosZ + coss(arm_angle)*150.0f};
        vec3f_copy(limb->shoulder,&shoulder_pos);

        // Send raycasts for target if not moving
        //if (!limb->moving) {
            Vec3f target_cast_origin = {head->obj->oPosX + sins(arm_angle)*800.0f,head->obj->oPosY+400.0f,head->obj->oPosZ + coss(arm_angle)*800.0f};
            Vec3f target_cast = {0.0f,-1000.0f,0.0f};
            Vec3f hitpos;
            struct Surface * hit;
            find_surface_on_ray(target_cast_origin,target_cast,&hit,&hitpos, RAYCAST_FIND_FLOOR);

            if (hit) {
                vec3f_copy(limb->move_end,hitpos);
            }
        //}

        spidertron_update_limb(limb);
    }
}