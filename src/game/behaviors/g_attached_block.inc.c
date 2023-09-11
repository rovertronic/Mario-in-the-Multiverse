void bhv_g_attached_block_init(void) {
    //o->parentObj = spawn_object_relative(0, 0, 200, 0, o, MODEL_ATTACHED_ROPE, bhvGAttachedRope);

    o->oGravity = 2.0f;
    o->oBounciness = 2.0f;
}

void bhv_g_attached_block_loop(void) {
    //if (o->parentObj->oAction == 1) {
        o->oAction = 1;
    //}

    if (o->oAction == 1) {
        object_step();

        if (o->oTimer == 120) {
            o->oAction = 2;
        }
    }
}

