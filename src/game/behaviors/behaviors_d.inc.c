void bhv_nitro_box_loop(void) {
    o->oPosY += o->oVelY;
    o->oVelY -= 2.0f;
    if (o->oPosY < o->oHomeY) {
        o->oPosY = o->oHomeY;
        o->oVelY = 0;
    }
    if (o->oTimer%20 == 0) {
        o->oVelY = 10.0f;
    }
}