// sound_waterfall.inc.c

void bhv_waterfall_sound_loop(void) {

    print_text_fmt_int(160, 180, "BPAR %d", GET_BPARAM12(o->oBehParams));
    char str2[50];
    sprintf(str2, "DIST %f", dist_between_objects(o, gMarioObject));
    print_text(160, 160, str2);

    // if no distance no specified ignore comportement
    if(GET_BPARAM12(o->oBehParams) != 0){
        //if specified and in range
        if(dist_between_objects(o, gMarioObject) < GET_BPARAM12(o->oBehParams)){
            print_text_fmt_int(160, 140, "COND %d", dist_between_objects(o, gMarioObject) < GET_BPARAM12(o->oBehParams));
            play_sound(SOUND_ENV_WATERFALL2, gCurrentObject->header.gfx.cameraToObject);
        }
    } else {
        cur_obj_play_sound_1(SOUND_ENV_WATERFALL2);
    }
}
