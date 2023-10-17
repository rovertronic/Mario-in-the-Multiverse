void bhv_star_door_star_init(void) {
    if (o->oBehParams2ndByte == 0) {
        cur_obj_scale(0.5f);
    }
    else {
        cur_obj_scale(1.0f);
    }
}

void bhv_star_door_star_loop(void) {
    o->oFaceAnglePitch += 0x800;
}

