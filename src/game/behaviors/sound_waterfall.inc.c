// sound_waterfall.inc.c

void bhv_waterfall_sound_loop(void) {
    // if no distance no specified ignore comportement
    if(GET_BPARAM12(o->oBehParams) != 0){
        //if specified and in range
        if(dist_between_objects(o, gMarioObject) < GET_BPARAM12(o->oBehParams)){
            struct Object *emitter = cur_obj_nearest_object_with_behavior_and_bparam1(bhvWaterfallSoundLoop, 1);
            if(emitter != NULL)
                play_sound(SOUND_ENV_WATERFALL2, emitter->header.gfx.cameraToObject);
        }
    } else {
        cur_obj_play_sound_1(SOUND_ENV_WATERFALL2);
    }
}
