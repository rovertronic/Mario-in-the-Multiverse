enum GSpringActions {
    G_SPRING_ACTION_WAITING,
    G_SPRING_ACTION_SPRING,
    G_SPRING_ACTION_COOLDOWN,
    G_SPRING_ACTION_TIED
};

void bhv_g_spring_init(void) {
    if (GET_BPARAM3(o->oBehParams) == 240) {
        o->oAction = G_SPRING_ACTION_TIED;
    }
}

void bhv_g_spring_loop(void) {
    switch (o->oAction) {
        case G_SPRING_ACTION_WAITING:
            obj_scale_xyz(o, 1, 1, 1);
            if (gMarioObject->platform == o) {
                o->oAction = G_SPRING_ACTION_SPRING;
            }
        break;
        case G_SPRING_ACTION_SPRING:
            obj_scale_xyz(o, 1, 1.0f - CLAMP(sins(o->oTimer * 2348), -1.0f, 0.9f), 1);
            if (o->oTimer == 15) {
                o->oAction = G_SPRING_ACTION_COOLDOWN;
            }
            if (o->oTimer == 2 && gMarioObject->platform == o) {
                gMarioState->action = ACT_TRIPLE_JUMP;
                gMarioState->vel[1] = 5 * o->oBehParams2ndByte;
                cur_obj_play_sound_2(SOUND_GENERAL_CRAZY_BOX_BOING_SLOW);
            }
        break;
        case G_SPRING_ACTION_COOLDOWN:
            obj_scale_xyz(o, 1, 1.0f - ((f32)CLAMP(sins(o->oTimer * 2348), 0.1f, 2) / (f32)(o->oTimer + 1.0f)), 1);
            if (o->oTimer == 30) {
                o->oAction = G_SPRING_ACTION_WAITING;
            }
        break;
        
    }

    if (o->oAction == G_SPRING_ACTION_TIED) {
        o->oGravity = 3.0f;
        
        if (object_step() & OBJ_COL_FLAG_GROUNDED) {
            o->oAction = G_SPRING_ACTION_WAITING;
        }
    }
}
