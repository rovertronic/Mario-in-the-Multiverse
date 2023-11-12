
#define WEAKPOINT_OFFSET 570

void master_kaag_act_inactive(void) { // act 0
    o->oForwardVel = 0.0f;
    o->oVelY = 0.0f;

    cur_obj_become_intangible();
    gSecondCameraFocus = o;
    cur_obj_init_animation_with_sound(1);
    cur_obj_set_pos_to_home();
    o->oHealth = 3;

    if (o->oDistanceToMario < 100) {
        o->oObjF4 = spawn_object_relative(0, 0, WEAKPOINT_OFFSET, 0, o, MODEL_NONE, bhvMasterKaagWeakPoint);
        seq_player_unlower_volume(SEQ_PLAYER_LEVEL, 60);
        play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
        //gLakituState.mode = CAMERA_MODE_BOSS_FIGHT;
        o->oAction = MASTER_KAAG_ACT_START;
    }
}

void master_kaag_spawn_hoodoos(void) {
    spawn_object_abs_with_rot(o, 0, MODEL_HOODOO_SORCERER, bhvHoodooSorcerer, -2730, 0, 1140, 0, 0, 0);
        spawn_object_abs_with_rot(o, 0, MODEL_HOODOO_SORCERER, bhvHoodooSorcerer, 370, 0, -2930, 0, 0, 0);
        spawn_object_abs_with_rot(o, 0, MODEL_HOODOO_SORCERER, bhvHoodooSorcerer, 2370, 0, 1835, 0, 0, 0);
}

void master_kaag_act_start(void) { // act 0
    if(o->oTimer == 20){
        create_sound_spawner(SOUND_MITM_LEVEL_I_MASTER_KAGG_ANGRY);
    }

    if(o->oTimer > 50){
        obj_set_model(o->oObjF4, MODEL_MAGIC_SHIELD);
        o->oAction = MASTER_KAAG_ACT_FOLLOW_MARIO_INVINCIBLE;
        master_kaag_spawn_hoodoos();
    }
}

void master_kaag_moving(void) {
    cur_obj_become_tangible();
    o->oForwardVel = 15.0f;
    cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x180);
    cur_obj_init_animation(0);
    cur_obj_play_sound_at_anim_range(20, 40, SOUND_OBJ_POUNDING1);

    if((o->oTimer % 150) == 0){
        create_sound_spawner(SOUND_MITM_LEVEL_I_MASTER_KAGG_LAUGH);
    }
}

void master_kaag_act_follow_mario_invincible(void) {
    master_kaag_moving();
    o->oObjF4->oShotByShotgun = 0;
    if(count_objects_with_behavior(bhvHoodooSorcerer) == 0){
        obj_set_model(o->oObjF4, MODEL_NONE);
        o->oAction = 3;
    }
}

void master_kaag_act_follow_mario_weak(void) {
    master_kaag_moving();

    if((o->oObjF4->oInteractStatus & INT_STATUS_INTERACTED && o->oObjF4->oInteractStatus & INT_STATUS_WAS_ATTACKED) || o->oObjF4->oShotByShotgun == 2){
        o->oObjF4->oShotByShotgun = 0;
        create_sound_spawner(o->oDeathSound);
        o->oHealth--;
        if(o->oHealth > 0){
            create_sound_spawner(SOUND_MITM_LEVEL_I_MASTER_KAGG_DAMAGE);
            o->oAction = 4;
        } else {
            o->oAction = 5;
        }
        
    }
}

void master_kaag_act_taking_damage(void) {
    o->oForwardVel = 0.0f;
    if(cur_obj_init_animation_and_check_if_near_end(2)){
        o->oAction = 2;
        obj_set_model(o->oObjF4, MODEL_MAGIC_SHIELD);
        create_sound_spawner(SOUND_MITM_LEVEL_I_MAGIC_SHIELD);
        master_kaag_spawn_hoodoos();    
    }
    
}

void master_kaag_act_death(void) { // act 7

    o->oForwardVel = 0.0f;
    if(cur_obj_init_animation_and_check_if_near_end(2)){
        create_sound_spawner(SOUND_OBJ_KING_WHOMP_DEATH);

        cur_obj_hide();
        cur_obj_become_intangible();

        obj_mark_for_deletion(o->oObjF4);

        spawn_mist_particles_variable(0, 0, 200.0f);
        spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 3.0f, TINY_DIRT_PARTICLE_ANIM_STATE_YELLOW);
        cur_obj_shake_screen(SHAKE_POS_SMALL);

        stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
        SET_BPARAM1(o->oBehParams, 7);
        cur_obj_spawn_star_at_y_offset(0, 300.0f, 0, 200.0f);
        obj_mark_for_deletion(o);  
    }
    
}

ObjActionFunc sMasterKaagActions[] = {
    master_kaag_act_inactive,               //0
    master_kaag_act_start,                  //1
    master_kaag_act_follow_mario_invincible,//2
    master_kaag_act_follow_mario_weak,      //3
    master_kaag_act_taking_damage,          //4
    master_kaag_act_death,                  //5
};

void bhv_master_kaag_loop(void) {
    cur_obj_update_floor_and_walls();
    cur_obj_move_using_fvel_and_gravity();

    if(o->oObjF4 != NULL){
        obj_set_pos(o->oObjF4, o->oPosX, o->oPosY + WEAKPOINT_OFFSET, o->oPosZ);
    }

    cur_obj_call_action_function(sMasterKaagActions);

    print_text_fmt_int(180,180,"CAM %d", gLakituState.mode);
}

void bhv_hoodoo_sorcerer_init(void){
    spawn_mist_particles_variable(0, 100, 90.0f);
    create_sound_spawner(SOUND_GENERAL2_1UP_APPEAR);
}

void bhv_hoodoo_sorcerer_loop(void) {
    o->oDeathSound = SOUND_MITM_LEVEL_I_HOODOO_SORCERER_DEATH;

    if(o->parentObj != NULL){
        obj_turn_toward_object(o, o->parentObj, O_MOVE_ANGLE_YAW_INDEX, 0x1000);
    }

    if((o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED) || o->oShotByShotgun == 2){
        o->oHealth--;
        create_sound_spawner(o->oDeathSound);
        obj_die_if_health_non_positive();
    }
}