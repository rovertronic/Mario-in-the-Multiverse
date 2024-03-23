void bhv_pt_mb(void) {
    f32 scale = (o->oBehParams2ndByte+1);

    cur_obj_scale(scale);
    o->oCollisionDistance = 500.0f*scale;

    if ((gMarioState->action == ACT_KNIGHT_SLIDE)||(gMarioState->action == ACT_KNIGHT_JUMP)) {
        //b destroyed
        if (o->oDistanceToMario < 120.0f*scale) {
            spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 3.0f, TINY_DIRT_PARTICLE_ANIM_STATE_YELLOW);
            cur_obj_shake_screen(SHAKE_POS_SMALL);
            create_sound_spawner(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION);
            mark_obj_for_deletion(o);
        }
    } else {
        load_object_collision_model(); //normal
    }
}

void bhv_l_pillar(void) {
    switch(o->oAction) {
        case 0:
            if (pizza_time) {
                mark_obj_for_deletion(o);
            } else {
                o->oAction++;
                o->oInteractType = INTERACT_BOUNCE_TOP;
                o->oVelY = 0.0f;
            }
        break;
        case 1:
            if (o->oDistanceToMario < 2000.0f) {
                play_secondary_music(SEQ_SOUND_PLAYER, 0, 255, 500);
            } else {
                func_80321080(50);
            }
            if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
                o->oAction++;
                o->oVelY = 30.0f;
        
                pizza_time = TRUE;
                pizza_timer = 6900;
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_F_BOND), 0);
                func_80321080(1);

                cur_obj_become_intangible();
                o->oInteractType = INTERACT_NONE;
            }
        break;
        case 2:
            o->oPosY += o->oVelY;
            o->oVelY -= 1.0f;
            o->oPosZ -= 10.0f;
        break;
    }

    o->oInteractStatus = 0;
    o->oIntangibleTimer = 0;
}