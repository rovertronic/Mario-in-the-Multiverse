// sound_waterfall.inc.c

void bhv_waterfall_sound_loop(void) {
    // if no distance specified ignore comportement
    if(GET_BPARAM1(o->oBehParams) == 0 && GET_BPARAM2(o->oBehParams) == 0){
        cur_obj_play_sound_1(SOUND_ENV_WATERFALL2);
    } else {
        // if Mario is farest than the specified distance
        if(!(o->oDistanceToMario > GET_BPARAM12(o->oBehParams))){
            cur_obj_play_sound_1(SOUND_ENV_WATERFALL2);
        }
    }
}
