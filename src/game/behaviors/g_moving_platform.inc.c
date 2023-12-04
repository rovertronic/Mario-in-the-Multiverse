void bhv_g_moving_platform_init(void) {
        o->oMoveAngleYaw = o->oFaceAngleYaw;
}

void bhv_g_moving_platform_loop(void) {
    o->oForwardVel = o->oBehParams2ndByte * sins(o->oTimer * 0x88 * GET_BPARAM1(o->oBehParams));
    cur_obj_move_xz_using_fvel_and_yaw();
}

