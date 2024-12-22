void bhv_star_drop_init(void) {
    gCamera->cutscene = 1;
    func_80321080(180);
}

void bhv_star_drop_loop(void) {
    if (o->oTimer == 0) {
        set_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
        o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
    }
    o->oFaceAngleYaw += 0x400;

    o->oFaceAnglePitch += 0x800;

    if (o->oTimer >= 30 && o->oTimer < 90) {
        gLakituState.goalFocus[0] = o->oPosX;
        gLakituState.goalFocus[1] = o->oPosY;
        gLakituState.goalFocus[2] = o->oPosZ;
        o->oPosY += 20 * coss(0x222 * (o->oTimer - 30));
        approach_f32_asymptotic_bool(&o->oPosX, 0, 0.8f);
        approach_f32_asymptotic_bool(&o->oPosZ, 0, 0.8f);
    }
    else if (o->oTimer >= 90) {
        o->oPosY += 4 * coss(0x222 * (o->oTimer - 90));

        if (o->oTimer == 110) {
            struct Object * abilityo = spawn_object_relative(ABILITY_CUTTER, 0, 0, 0, o, MODEL_ABILITY, bhvAbilityUnlock);
            abilityo->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
            cur_obj_hide();
            spawn_mist_particles();
            spawn_triangle_break_particles(20, MODEL_CARTOON_STAR, 0.2f, 3);
            create_sound_spawner(SOUND_GENERAL_SHORT_STAR);
        }
        if (o->oTimer == 140) {
            clear_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
            obj_mark_for_deletion(o);
            obj_mark_for_deletion(o->parentObj);
            gCamera->cutscene = 0;
        }
    }
    
}
