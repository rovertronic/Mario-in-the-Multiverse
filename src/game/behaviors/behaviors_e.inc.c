






//-- *** Level ***
























//-- *** Ablilty ***

void bhv_e__rocket_blast(void) {
    if (o->oTimer == 0) {
        o->oOpacity = 255;
        o->header.gfx.scale[0] = 0.45f;
        o->header.gfx.scale[2] = 0.45f;
        o->header.gfx.scale[1] = 1.f;
    }

    o->header.gfx.scale[0] += 0.08f;
    o->header.gfx.scale[2] += 0.08f;
    o->header.gfx.scale[1] = approach_f32_asymptotic(o->header.gfx.scale[1], 0.f, 0.15f);
    o->oPosY += 10.f;
    o->oFaceAngleYaw += DEGREES(1);

    o->oOpacity = approach_s32(o->oOpacity, 0, 26, 26);
    if (o->oOpacity == 0) {
        o->activeFlags = 0; }
}

void bhv_e__flattened_obj(void) {
    if (o->oAction) {
        Vec3f norm, lateralDir, leftDir, forwardDir;
        surface_normal_to_vec3f(norm, o->OBJECT_FIELD_S16P(0x1B));
        s16 yaw = o->oFaceAngleYaw;

        vec3f_set(lateralDir, sins(yaw), 0.0f, coss(yaw));
        vec3f_normalize(norm);
        vec3f_cross(leftDir, norm, lateralDir);
        vec3f_normalize(leftDir);
        vec3f_cross(forwardDir, leftDir, norm);
        vec3f_normalize(forwardDir);
        f32 negX = -forwardDir[0];
        f32 negY = -forwardDir[1];
        f32 negZ = -forwardDir[2];
        forwardDir[0] = negX;
        forwardDir[1] = negY;
        forwardDir[2] = negZ;
        vec3f_copy(o->transform[0], leftDir);
        vec3f_copy(o->transform[1], forwardDir);
        vec3f_copy(o->transform[2], norm);
        vec3f_copy(o->transform[3], &o->oPosX);
        MTXF_END(o->transform);
        o->header.gfx.throwMatrix = o->transform;
    }

    o->oUnk94 += 7000;
    o->oUpVel = approach_f32(o->oUpVel, 0.f, 0.0357142f, 0.0357142f);
    f32 bounce = (coss(o->oUnk94) * o->oUpVel);
    f32 x = (o->oVelX + bounce);
    f32 y = (o->oVelY + bounce);
    f32 z = 0.1f;
    o->header.gfx.scale[0] = x;
    o->header.gfx.scale[1] = y;
    o->header.gfx.scale[2] = z;

    o->oFloor = cur_obj_update_floor_height_and_get_floor();

    if (o->oFloor == NULL) {
        o->activeFlags = 0; }
    if (o->oTimer == 30) {
        spawn_mist_particles();
        if (o->oDeathSound) {
            create_sound_spawner(o->oDeathSound); }
        else {
            create_sound_spawner(SOUND_OBJ_DEFAULT_DEATH); }
        o->activeFlags = 0;
    }
}

void bhv_e__push_obj(void) {
    struct Object *obj = o->parentObj;
    //--**
    if (obj->oFloor != NULL) {
        o->oVelX = approach_f32_asymptotic(o->oVelX, 0.f, 0.1f);
        o->oVelZ = approach_f32_asymptotic(o->oVelZ, 0.f, 0.1f);

        f32 normY = obj->oFloor->normal.y;
        obj->oPosX += (o->oVelX * normY);
        obj->oPosZ += (o->oVelZ * normY);

        f32_find_wall_collision(&obj->oPosX, &obj->oPosY, &obj->oPosZ, 0.f, obj->hitboxRadius);

        f32 floorHeight = find_floor_height(obj->oPosX, (obj->oPosY + 100.f), obj->oPosZ);
        if (obj->oPosY < obj->oFloorHeight) {
            obj->oPosY = obj->oFloorHeight; }
    }

    if (o->oTimer > 40) {
        o->activeFlags = 0; }
}

//static s16 eq = DEGREES(35);//good: 45

void bhv_e__d(void) {
    //--D
    if (o->oTimer > 233) {
        o->activeFlags = 0;
    }


    f32 dist;
    vec3f_get_dist(&o->oPosX, &o->oHomeX, &dist);

    f32 div = (dist * 0.005f);
    if (div < 1.f) {
        div = 1.f;
    }
    s16 eq = (dist / div);
    o->header.gfx.scale[0] = eq;
    o->header.gfx.scale[1] = eq;
    o->header.gfx.scale[2] = eq;

    print_text_fmt_int(20, 50, "EQ %d", eq);

    o->oPosX += (sins(o->oFaceAngleYaw) * coss(o->oFaceAnglePitch)) * 70.f;
    o->oPosY += (sins(o->oFaceAnglePitch))                          * 70.f;
    o->oPosZ += (coss(o->oFaceAngleYaw) * coss(o->oFaceAnglePitch)) * 70.f;
    return;



#ifdef NEVER_DEFINED
    if (o->oTimer > 233) {
        o->activeFlags = 0;
    }
    

    f32 origDist = (f32)(o->oTimer * 70);
    s16 pitch = o->oFaceAnglePitch;
    s16 yaw = o->oFaceAngleYaw;


    s32 base = 8;
    f32 mul  = 6.f;
    /*if (origDist < 300.f) {//--D
        base = 45;
        mul  = 4.f;
    }*/

    //-f32 eq = ((DEGREES(base)) - ((s32)(sins(origDist + 1200.f) * (DEGREES(mul)))));


//    eq = approach_s16_asymptotic(eq, DEGREES(2), 75);//good: (eq, DEGREES(3), 60);
//    eq = ();
    f32 div = (origDist * 0.005f);
    if (div < 1.f) {
        div = 1.f; }
    s16 eq = (origDist * 0.7f/* + (sins((origDist) + 12000.f) * 546.f)*/);//((546.f / (origDist * 0.00025f)) + (sins((origDist) + 12000.f) * 546.f));//another good: (DEGREES(5) / (origDist * 0.0005f));
    print_text_fmt_int(20, 50, "EQ %d", eq);

    switch (o->oBehParams2ndByte) {
    case 1:
        yaw += eq;
        break;
    case 2:
        pitch -= eq;
        break;
    case 3:
        yaw -= eq;
        break;
    default:
        pitch += eq;
    }

    f32 dist = origDist + (origDist * sins(eq * 2));

    o->oPosX = o->oHomeX + (sins(yaw) * coss(pitch)) * dist;
    o->oPosY = o->oHomeY + (sins(pitch)) * dist;
    o->oPosZ = o->oHomeZ + (coss(yaw) * coss(pitch)) * dist;
#endif


    //--D
    /*
    o->header.gfx.scale[0] = 0.2f;
    o->header.gfx.scale[2] = 20.f;

    f32 div = (cur_obj_lateral_dist_to_home() * 0.0025f);
    if (div < 1.f) {
        div = 1.f; }
    o->oFaceAngleYaw = o->oMoveAngleYaw + ((7280.f / div)/* + (sins((origDist) + 12000.f) * 546.f)*R/);
    vec3f_copy(&o->oPosX, gMarioState->pos);*/



}









//--Geo


//obj

Gfx *e__0(s32 callContext, struct GraphNode *node, Mat4 *context) {
    /*if (callContext == GEO_CONTEXT_RENDER) {
        Gfx *dlS = alloc_display_list(sizeof(Gfx) * 3);
        Gfx *dlH = dlS
        
        if (dlS == NULL) {
            return; }

        struct Object *obj = (struct Object *) gCurGraphNodeObject; // TODO: change this to object pointer?
        if (obj->oShotByShotgun) {
            

            gDPSetLights1(dlHead++, 255, 255, 255, objectOpacity);
            gSPEndDisplayList(dlHead);
        }

        return dlStart;
    }

    return NULL;*/
}




//Mario



static void e__mario_aim_rotation(s16 *rn0, s16 *rn1, s16 *rn2, s32 div, s32 shootAnimDiv) {
    s16 pitch = (gE_UpperAimPitch / div);
    s16 yaw   = (gE_UpperAimYaw   / div);
    if (shootAnimDiv) {
        yaw /= shootAnimDiv; }
    *rn0 = approach_s16_asymptotic(*rn0, yaw, 4);
    *rn1 = 0;
    *rn2 = approach_s16_asymptotic(*rn2, pitch, 4);
}


Gfx *geo_e__mario_torso_rotation(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        struct GraphNodeRotation *rotNode = (struct GraphNodeRotation *) node->next;

        if (gE_ShotgunFlags & E_SGF_AIM_FIRE) {
            //first in geo
            gE_UpperAimPitch = ((s16)((calculate_pitch(gLakituState.focus, gLakituState.pos)) - gMarioState->faceAngle[0]));
            gE_UpperAimYaw   = ((s16)((gCamera->yaw + DEGREES(180)) - gMarioState->faceAngle[1]));//approach toward middle when racking the gun
            e__mario_aim_rotation(&rotNode->rotation[0], &rotNode->rotation[1], &rotNode->rotation[2], 3, 1);
        } else {
            s32 action = gMarioState->action;
            s16 *torsoAngle = &gMarioState->marioBodyState->torsoAngle;

            if ((action != ACT_BUTT_SLIDE) && (action != ACT_HOLD_BUTT_SLIDE) && (action != ACT_WALKING) && (action != ACT_RIDING_SHELL_GROUND)) {
                vec3_zero(torsoAngle); }

            rotNode->rotation[0] = torsoAngle[1];
            rotNode->rotation[1] = torsoAngle[2];
            rotNode->rotation[2] = torsoAngle[0];
        }
    }
    return NULL;
}

Gfx *geo_e__mario_head_rotation(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        struct GraphNodeRotation *rotNode = (struct GraphNodeRotation *) node->next;

        if (gE_ShotgunFlags & E_SGF_AIM_FIRE) {
            e__mario_aim_rotation(&rotNode->rotation[0], &rotNode->rotation[1], &rotNode->rotation[2], 2, 1); }
        else if (gCamera->mode == CAMERA_MODE_C_UP) {
            rotNode->rotation[0] = gPlayerCameraState->headRotation[1];
            rotNode->rotation[2] = gPlayerCameraState->headRotation[0];
        } else if (gMarioState->action & ACT_FLAG_WATER_OR_TEXT) {
            struct MarioBodyState *bodyState = &gBodyStates;
            rotNode->rotation[0] = bodyState->headAngle[1];
            rotNode->rotation[1] = bodyState->headAngle[2];
            rotNode->rotation[2] = bodyState->headAngle[0];
        } else {
            approach_vec3s_asymptotic(&rotNode->rotation, gVec3sZero, 4, 4, 4); }
    }
    return NULL;
}

Gfx *geo_e__mario_arm_rotation(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        struct GraphNodeRotation *rotNode = (struct GraphNodeRotation *) node->next;

        if (gE_ShotgunFlags & E_SGF_AIM_FIRE) {//aim mode
            s32 shootAnimDiv = (13 - ABS((gE_ShotgunTimer - 13)));
            e__mario_aim_rotation(&rotNode->rotation[1], &rotNode->rotation[2], &rotNode->rotation[0], 2, shootAnimDiv); }
        else {
            approach_vec3s_asymptotic(&rotNode->rotation, gVec3sZero, 4, 4, 4); }
    }
    return NULL;
}

Gfx *geo_e__mario_shotgun_scale(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        struct MarioState *m = gMarioState;
        struct GraphNodeScale *scaleNode = (struct GraphNodeScale *) node->next;
        s32 sgTimer = gE_ShotgunTimer;

        if (gE_UpperAnimInfo.animID == 28) {
            s32 timer = (32767 - (sgTimer * 1424));
            f32 scale = (1.f + (sins(timer) * 0.3f));
            scaleNode->scale = scale;
        } else {
            scaleNode->scale = 1.f; }
    }
    return NULL;
}

Gfx *geo_e__switch_mario_shotgun_hand(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        struct GraphNodeSwitchCase *switchCase = (struct GraphNodeSwitchCase *) node;
        switchCase->selectedCase = (gE_ShotgunFlags & E_SGF_LEFT_HAND);
    }
    return NULL;
}
