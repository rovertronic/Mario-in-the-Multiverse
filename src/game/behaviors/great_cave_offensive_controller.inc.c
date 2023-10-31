void bhv_great_cave_offensive_controller_init(void) {
   
}

void bhv_great_cave_offensive_controller_loop(void) {
    if (gMarioState->pos[0] < -6220) {
        play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_CUSTOM_TREES_IN_THE_DEPTHS), 0);
    }
    else {
        play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_CUSTOM_CRYSTAL_FIELD), 0);
    }
}

