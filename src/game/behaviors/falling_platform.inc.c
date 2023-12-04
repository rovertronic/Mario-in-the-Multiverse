void bhv_falling_platform_init(void) {
    o->oHomeY = o->oPosY;
}


void bhv_falling_platform_loop(void) {
    //struct Surface *floor;
    //f32 floorY = find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);
    o->oVelY = -25.0f;

    if (o->oTimer >= 640){
        o->oPosY = o->oHomeY;
        o->oTimer = 0;
    }

    object_step();
}