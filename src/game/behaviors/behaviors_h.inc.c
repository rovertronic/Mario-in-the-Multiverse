void bhv_hglass_loop(void) {
    switch(o->oAction) {
        case 0:
            o->oHealth = 1;
            o->oAction++;
        break;
        case 1:
            if (o->oHealth < 1) {
                spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 3.0f, 4);
                create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
                obj_mark_for_deletion(o);
            }
        break;
    }
}