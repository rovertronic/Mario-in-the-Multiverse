void bhv_g_attached_block_init(void) {
    //o->parentObj = spawn_object_relative(0, 0, 200, 0, o, MODEL_ATTACHED_ROPE, bhvGAttachedRope);

    o->oGravity = 2.0f;
    o->oBounciness = 2.0f;


    struct Surface * dummyfloor;
    o->oHomeY = find_floor(o->oPosX,o->oPosY,o->oPosZ,&dummyfloor);
}

void bhv_g_attached_block_loop(void) {
    /*
    //if (o->parentObj->oAction == 1) {
        o->oAction = 1;
    //}

    if (o->oAction == 1) {
        object_step();

        if (o->oTimer == 120) {
            o->oAction = 2;
        }
    }
    */
    //object_step();

    o->oPosY += o->oVelY;

    if (o->oPosY < o->oHomeY) {
        if (o->oVelY < -0.5f) {
            //bounce if y velocity is faster than -0.5f
            o->oVelY = -o->oVelY*0.4f;
        } else {
            o->oVelY = 0.0f;
        }
        o->oPosY = o->oHomeY;
        if (o->oAction == 0) {
            cur_obj_play_sound_2( SOUND_GENERAL_ELEVATOR_LAND);
            o->oAction++;
        }
    } else {
        o->oVelY -= 2.0f;
    }
}

