void bhv_pt_mb(void) {
    f32 scale = (o->oBehParams2ndByte+1);

    cur_obj_scale(scale);
    o->oCollisionDistance = 500.0f*scale;

    if (gMarioState->action == ACT_KNIGHT_SLIDE) {
        //b destroyed
        if (o->oDistanceToMario < 120.0f*scale) {
            spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 3.0f, TINY_DIRT_PARTICLE_ANIM_STATE_YELLOW);
            cur_obj_shake_screen(SHAKE_POS_SMALL);
            create_sound_spawner(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION);
            mark_obj_for_deletion(o);
        }
    } else {
        load_object_collision_model(); //normal
    }
}