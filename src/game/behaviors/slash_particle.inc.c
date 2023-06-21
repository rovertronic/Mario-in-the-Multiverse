void bhv_slash_particle_loop(void) {
    s16 yaw;

    if (o->oBehParams2ndByte == 3) {
        yaw = o->parentObj->oFaceAngleYaw;
        o->oPosX = o->parentObj->oPosX + sins(o->parentObj->oFaceAngleYaw) * 100;
        o->oPosY = o->parentObj->oPosY + 50;
        o->oPosZ = o->parentObj->oPosZ + coss(o->parentObj->oFaceAngleYaw) * 100;
        o->oFaceAnglePitch = 0x4000;
        o->oFaceAnglePitch = 0x4000;
        obj_scale_xyz(o, -1.0f, 1.0f, -1.0f);
    }
    else {
        switch (o->oBehParams2ndByte) {
            case 0:
                o->oFaceAngleRoll = -0x800;
                o->oMoveAngleRoll = -0x800;
                obj_scale_xyz(o, -1.0f, 1.0f, -1.0f);
                break;
            case 1:
                o->oFaceAngleRoll = 0x2000;
                o->oMoveAngleRoll = 0x2000;
                break;
            case 2:
                o->oFaceAngleRoll = 0x2000;
                o->oMoveAngleRoll = 0x2000;
                obj_scale_xyz(o, -1.0f, -1.0f, -1.0f);
                break;
        }

        vec3f_get_yaw(&o->oPosVec, gCamera->pos, &yaw);
    }

    o->oFaceAngleYaw = yaw;
    o->oMoveAngleYaw = yaw;

    if (o->oTimer >= 5) {
        obj_mark_for_deletion(o);
    }
}