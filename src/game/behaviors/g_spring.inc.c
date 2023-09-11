enum GSpringActions {
    G_SPRING_ACTION_WAITING,
    G_SPRING_ACTION_SPRING,
    G_SPRING_ACTION_COOLDOWN
};

void bhv_g_spring_init(void) {

}

void bhv_g_spring_loop(void) {
    switch (o->oAction) {
        case G_SPRING_ACTION_WAITING:
            if (gMarioObject->platform == o) {
                o->oAction = G_SPRING_ACTION_SPRING;
            }
        break;
        case G_SPRING_ACTION_SPRING:
            obj_scale_xyz(o, 1, 1.0f - CLAMP(sins(o->oTimer * 2348), -1.0f, 0.9f), 1);
            if (o->oTimer == 15) {
                o->oAction = G_SPRING_ACTION_COOLDOWN;
            }
            if (o->oTimer == 8 && gMarioObject->platform == o) {
                gMarioState->action = ACT_TRIPLE_JUMP;
                gMarioState->vel[1] = 85.0f;
                cur_obj_play_sound_2(SOUND_GENERAL_CRAZY_BOX_BOING_SLOW);
            }
        break;
        case G_SPRING_ACTION_COOLDOWN:
            obj_scale_xyz(o, 1, 1.0f - ((f32)CLAMP(sins(o->oTimer * 2348), 0.1f, 2) / (f32)(o->oTimer + 1.0f)), 1);
            if (o->oTimer == 60) {
                o->oAction = G_SPRING_ACTION_WAITING;
            }
        break;
        
    }
}
