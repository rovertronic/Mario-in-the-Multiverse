void bhv_great_cave_offensive_controller_init(void) {
   
}

void bhv_great_cave_offensive_controller_loop(void) {
    if (gMarioState->pos[0] < -6220) {
        play_secondary_music(SEQ_CUSTOM_TREES_IN_THE_DEPTHS, 0, 255, 30);
    }
    else {
        func_80321080(50);
    }
}

