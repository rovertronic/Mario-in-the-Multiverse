// sound_waterfall.inc.c

void bhv_waterfall_sound_loop(void) {
    f32 soundRadius;
    // if no distance specified ignore comportement
    if((GET_BPARAM1(o->oBehParams) + GET_BPARAM2(o->oBehParams)) == 0){
        cur_obj_play_sound_1(SOUND_ENV_WATERFALL2);
    } else {
        // if Mario is closer than the specified distance
        soundRadius = GET_BPARAM12(o->oBehParams);
        if(o->oDistanceToMario < soundRadius){
            cur_obj_play_sound_1(SOUND_ENV_WATERFALL2);
        }

        /*char str[50];
        sprintf(str, "BPAR %f", soundRadius);
        print_text(160, 180, str);

        char str2[50];
        sprintf(str2, "DIST %f", o->oDistanceToMario);
        print_text(160, 160, str2);*/
    }
}
