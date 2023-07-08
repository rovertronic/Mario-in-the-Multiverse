void bhv_dash_booster_particle(void) {
    if (o->oTimer%2 == 1) {
        o->oAnimState ++;
    }
    if (o->oAnimState >= 4) {
        mark_obj_for_deletion(o);
    }
}