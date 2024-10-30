void bhv_great_cave_offensive_controller_init(void) {
   
}

void bhv_great_cave_offensive_controller_loop(void) {
    if (gMarioState->abilityId == ABILITY_MARBLE) {
        stop_background_music(SEQUENCE_ARGS(4, SEQ_CUSTOM_CRYSTAL_FIELD));
        stop_background_music(SEQUENCE_ARGS(4, SEQ_CUSTOM_TREES_IN_THE_DEPTHS));
        play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_MINECART_RIDING), 0);
        o->oF4 = 1;
    }
    else if (gMarioState->pos[0] < -6520 && o->oF4 == 0) {
        stop_background_music(SEQUENCE_ARGS(4, SEQ_CUSTOM_CRYSTAL_FIELD));
        stop_background_music(SEQUENCE_ARGS(4, SEQ_MINECART_RIDING));
        play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_CUSTOM_TREES_IN_THE_DEPTHS), 0);
        o->oF4 = 1;
    }
    else if (gMarioState->pos[0] >= -6520 && o->oF4 == 1) {
        stop_background_music(SEQUENCE_ARGS(4, SEQ_CUSTOM_TREES_IN_THE_DEPTHS));
        stop_background_music(SEQUENCE_ARGS(4, SEQ_MINECART_RIDING));
        play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_CUSTOM_CRYSTAL_FIELD), 0);
        o->oF4 = 0;
    }
}

