void bhv_g_cut_rock_init(void) {
    o->oGravity = 2.0f;
    o->oBounciness = 2.0f;
}

void bhv_g_cut_rock_loop(void) {
    o->oAction = 1;

    if (o->oAction == 1) {
        object_step();

        if (o->oTimer == 120) {
            o->oAction = 2;
        }
    }
}

