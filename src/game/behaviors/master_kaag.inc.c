
void master_kaag_act_inactive(void) { // act 0
    o->oForwardVel = 0.0f;
    o->oVelY = 0.0f;

    cur_obj_become_intangible();
    gSecondCameraFocus = o;
    cur_obj_init_animation_with_sound(KING_BOBOMB_ANIM_IDLE);
    cur_obj_set_pos_to_home();
    o->oHealth = 3;

    if (o->oDistanceToMario < 3000) {
        o->oObjF4 = spawn_object_relative(0, 0, 500, 0, o, MODEL_NONE, bhvMasterKaagWeakPoint);
        o->oAction = MASTER_KAAG_ACT_START;
    }
}

void master_kaag_act_start(void) { // act 0
    if(o->oTimer > 50){
        o->oAction = MASTER_KAAG_ACT_FOLLOW_MARIO_INVINCIBLE;
    }
}

void master_kaag_act_follow_mario_invincible(void) {
    cur_obj_become_tangible();
    o->oForwardVel = 10.0f;
    cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x100);
}

void master_kaag_act_follow_mario_weak(void) {
}

void master_kaag_act_taking_damage(void) {
}

void master_kaag_act_death(void) { // act 7

    create_sound_spawner(SOUND_OBJ_KING_WHOMP_DEATH);

    cur_obj_hide();
    cur_obj_become_intangible();

    spawn_mist_particles_variable(0, 0, 200.0f);
    spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 3.0f, TINY_DIRT_PARTICLE_ANIM_STATE_YELLOW);
    cur_obj_shake_screen(SHAKE_POS_SMALL);

    cur_obj_spawn_star_at_y_offset(2000.0f, 4500.0f, -4500.0f, 200.0f);

    o->oAction = KING_BOBOMB_ACT_STOP_MUSIC;
}

void master_kaag_act_stop_music(void) { // act 8
    if (o->oTimer == 60) {
        stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
    }
}

ObjActionFunc sMasterKaagActions[] = {
    master_kaag_act_inactive,
    master_kaag_act_start,
    master_kaag_act_follow_mario_invincible,
    master_kaag_act_follow_mario_weak,
    master_kaag_act_taking_damage,
    master_kaag_act_death,
    master_kaag_act_stop_music,
};

void bhv_master_kaag_loop(void) {
    cur_obj_update_floor_and_walls();
    cur_obj_move_using_fvel_and_gravity();

    if(o->oObjF4 != NULL){
        obj_set_pos(o->oObjF4, o->oPosX, o->oPosY + 500, o->oPosZ);
    }

    cur_obj_call_action_function(sMasterKaagActions);
    print_text_fmt_int(180, 180, "ACTION %d", o->oAction);
}