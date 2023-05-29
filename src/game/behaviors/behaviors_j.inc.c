void bhv_dragonite_init(void){
    obj_scale_xyz(o, 0.0f, 0.0f, 0.0f);

}

void bhv_dragonite_loop(void){
    f32 xScale = o->header.gfx.scale[0];
    f32 yScale = o->header.gfx.scale[1];
    f32 zScale = o->header.gfx.scale[2];
    f32 maxScale = 0.8f;
    obj_set_pos(o, gMarioState->pos[0], gMarioState->pos[1] + 156.0f, gMarioState->pos[2]);
    o->oFaceAngleYaw = gMarioState->faceAngle[1];


    if (gMarioState->action != ACT_HM_FLY) {
        if (yScale > 0.0f) {
            yScale -= 0.15f;
        }
        if (xScale > 0.0f) {
            xScale -= 0.15f;
        }
        if (zScale > 0.0f) {
            zScale -= 0.15f;
        }
        if (yScale <= 0.0f) {
            obj_mark_for_deletion(o);
        }

    } else {
        if (yScale < maxScale) {
            yScale += 0.1f;
        }
        if (xScale < maxScale) {
            xScale += 0.1f;
        }
        if (zScale < maxScale) {
            zScale += 0.1f;
        }
    }

    obj_scale_xyz(o, xScale, yScale, zScale);
}