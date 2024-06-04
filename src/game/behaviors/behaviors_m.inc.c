void bhv_dash_booster_particle(void) {
    if (o->oTimer%2 == 1) {
        o->oAnimState ++;
    }
    if (o->oAnimState >= 4) {
        mark_obj_for_deletion(o);
    }
}

void bhv_m_boss_elevator(void) {
    switch(o->oBehParams2ndByte) {
        case 0:
            switch(o->oAction) {
                case 0:
                    if (o->oDistanceToMario < 600.0f) {
                        cur_obj_play_sound_2(SOUND_GENERAL_STAR_DOOR_OPEN);
                        o->oAction = 1;
                    }
                    break;
                case 1:
                    if (o->oTimer < 70) {
                        o->oPosZ += 10.0f;
                    }
                    break;
            }
            break;
    }
}