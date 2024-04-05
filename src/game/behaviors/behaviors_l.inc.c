void bhv_pt_mb(void) {
    f32 scale = (o->oBehParams2ndByte+1);

    cur_obj_scale(scale);
    o->oCollisionDistance = 500.0f*scale;

    if ((gMarioState->action == ACT_KNIGHT_SLIDE)||(gMarioState->action == ACT_KNIGHT_JUMP)) {
        //b destroyed

        //bounding box check, radius check causes clipping issues
        if (
            (gMarioState->pos[0] < o->oPosX+(105.0f*scale))&&(gMarioState->pos[0] > o->oPosX-(105.0f*scale))&&
            (gMarioState->pos[1] < o->oPosY+(200.0f*scale))&&(gMarioState->pos[1] > o->oPosY-(5.0f*scale))&&
            (gMarioState->pos[2] < o->oPosZ+(105.0f*scale))&&(gMarioState->pos[2] > o->oPosZ-(105.0f*scale))
            ) {
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
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_L_PIZZA_TIME), 0);
                func_80321080(1);

                cur_obj_become_intangible();
                o->oInteractType = INTERACT_NONE;
                combo_meter = 201;
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

void bhv_l_johnblock(void) {
    u8 off = o->oBehParams2ndByte;
    if (pizza_time) {
        off = !off;
    }

    o->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;

    if (off) {
        o->oAnimState = 1;
    } else {
        o->oAnimState = 0;
        load_object_collision_model();
    }
}

void bhv_escape_collect_star_loop(void) {
    u8 cond;
    if (!p_rank_challenge_enabled) {
        // normal
        cond = (pizza_time);
    } else {
        // p rank mode
        cond = (pizza_time && p_rank_lap_2 && p_rank_stars >= 5);
    }

    if (cond) {
        o->oInteractType = INTERACT_STAR_OR_KEY;
        o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        o->oFaceAngleYaw += 0x800;

        if (o->oInteractStatus & INT_STATUS_INTERACTED) {
            obj_mark_for_deletion(o);
            o->oInteractStatus = INT_STATUS_NONE;
            pizza_time = FALSE;
            if (p_rank_challenge_enabled) {
                p_rank_success = TRUE;
                p_rank_challenge_enabled = FALSE;
            }
            level_control_timer(TIMER_CONTROL_HIDE);
        }
    } else {
        o->oInteractType = INTERACT_NONE;
        o->oInteractStatus = INT_STATUS_NONE;
        o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
    }
}

void bhv_l_clock(void) {
    switch(o->oAction) {
        case 0: // wait for pizza time
            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            if ((pizza_time)&&(p_rank_challenge_enabled)) {
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                o->oAction++;
            }
            break;
        case 1:
            if (obj_check_if_collided_with_object(o, gMarioObject)) {
                combo_meter = CLAMP(combo_meter+33,0,201);
                play_sound(SOUND_GENERAL2_SWITCH_TICK_FAST, gGlobalSoundSource);
                spawn_object(o, MODEL_SPARKLES, bhvCoinSparklesSpawner);
                o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
                o->oAction++;
            }
            break;
    }
    o->oInteractStatus = 0;
    o->oIntangibleTimer = 0;
}

void bhv_npc_pepperman_loop(void) {
    s32 dialogResponse;
    switch (o->oAction) {
        case 0:
            if (o->oDistanceToMario < 1000.0f) {
                o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x140);
            }

            if (o->oInteractStatus == INT_STATUS_INTERACTED) {
                o->oAction = 1;
            }

            if (p_rank_success) {
                p_rank_success = FALSE;
                spawn_default_star(0.0f, 200.0f, o->oPosZ - 300.0f);
                o->oAction = 3;
                o->oInteractType = INTERACT_IGLOO_BARRIER;
            }
            break;

        case 1:
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x1000);
            if ((s16) o->oMoveAngleYaw == (s16) o->oAngleToMario) {
                o->oAction = 2;
            }
            break;

        case 2:
            dialogResponse = cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP, DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_RACE_DIALOG, DIALOG_L_PEPPERMAN_2);
            if (dialogResponse != DIALOG_RESPONSE_NONE) {
                if (dialogResponse == DIALOG_RESPONSE_YES) {
                    o->oAction = 3;
                    initiate_warp(LEVEL_L, 0x01, 0x05, WARP_FLAGS_NONE);
                    fade_into_special_warp(WARP_SPECIAL_NONE, 0);
                    p_rank_challenge_prepare = TRUE;
                } else {
                    o->oAction = 0;
                }
            }
            break;
    }

    o->oInteractStatus = 0;
}

void bhv_pizza_portal_loop(void) {
    if (!p_rank_lap_2 && pizza_time && p_rank_challenge_enabled) {
        o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        if (o->oInteractStatus != INTERACT_NONE) {
            p_rank_lap_2 = TRUE;
        }
        bhv_warp_loop();
    } else {
        o->oInteractType = INTERACT_NONE;
        o->oInteractStatus = INT_STATUS_NONE;
        o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
    }
}

struct ObjectHitbox sPeppermanHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 4,
    /* numLootCoins:      */ 0,
    /* radius:            */ 100,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 110,
    /* hurtboxHeight:     */ 210,
};

enum {
    PM_ACT_INIT,
    PM_ACT_IDLE,
    PM_ACT_CHARGE,
    PM_ACT_REVERSE_CHARGE,
    PM_ACT_STUNNED,
    PM_ACT_PUNCHED,
    PM_ACT_FEAR,
};

void bhv_boss_pepperman_loop(void) {
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(-78);
    o->oFaceAngleYaw = o->oMoveAngleYaw;

    o->oAnimState = 0;
    switch(o->oAction) {
        case PM_ACT_INIT:
            obj_set_hitbox(o, &sPeppermanHitbox);
            o->oAction = PM_ACT_IDLE;
            break;
        case PM_ACT_IDLE:
            if (o->oTimer == 0) {
                cur_obj_init_animation(0);
            }
            o->oForwardVel = 0.0f;
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x300);
            o->oInteractType = INTERACT_IGLOO_BARRIER;
            o->oDamageOrCoinValue = 0;
            if (o->oTimer > 30) {
                cur_obj_init_animation(1);
                o->oDamageOrCoinValue = 3;
                o->oAction = PM_ACT_CHARGE;
                o->oAngleVelYaw = o->oAngleToMario; // Used for charge reverse dection
                o->oForwardVel = -20.0f;
            }
            break;
        case PM_ACT_CHARGE:
            if (o->oHealth <=2 && ABS(o->oAngleToMario-o->oAngleVelYaw) > 0x8000) {
                //mario's on the other side of my initial charge angle, reverse!
                o->oAction = PM_ACT_REVERSE_CHARGE;
                o->oForwardVel = -o->oForwardVel;
                o->oMoveAngleYaw += 0x8000;

                cur_obj_play_sound_2(SOUND_OBJ2_SCUTTLEBUG_ALERT);
            }
        case PM_ACT_REVERSE_CHARGE:
            if (o->oAction == PM_ACT_REVERSE_CHARGE) {
                o->oForwardVel += 3.0f;
                if (o->oForwardVel < 0.0f) {
                    o->oForwardVel += 3.0f;
                }
            }

            o->oInteractType = INTERACT_DAMAGE;
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x200);
            o->oForwardVel += 5.0f;
            if (o->oForwardVel>0.0f&&(o->oMoveFlags & (OBJ_MOVE_HIT_WALL|OBJ_MOVE_HIT_EDGE))) {
                cur_obj_play_sound_2(SOUND_ACTION_BONK);
                o->oDamageOrCoinValue = 0;
                o->oAction = PM_ACT_STUNNED;
                o->oForwardVel = -50.0f;
                o->oVelY = 30.0f;
            }
            break;
        case PM_ACT_STUNNED:
            o->header.gfx.animInfo.animFrame = 0;
            o->oForwardVel *= .8f;
            o->oInteractType = INTERACT_BOUNCE_TOP;
            if ((o->oTimer % 15 == 0)||(o->oTimer % 15 == 3)) {
                o->oAnimState = 1;
                cur_obj_play_sound_2(SOUND_GENERAL_BOWSER_KEY_LAND);
            }
            if ((o->oTimer % 15 == 1)||(o->oTimer % 15 == 4)) {
                o->oAnimState = 1;
            }
            if (o->oTimer > 70) {
                o->oAction = PM_ACT_IDLE;
            }
            if ((o->oInteractStatus & INT_STATUS_WAS_ATTACKED)||(o->oShotByShotgun > 0)) {
                o->oHealth --;
                o->oAction = PM_ACT_PUNCHED;
                o->oMoveAngleYaw = gMarioState->faceAngle[1];
                o->oForwardVel = 90.0f;
                o->oVelY = 50.0f;
            }
            break;
        case PM_ACT_PUNCHED:
            cur_obj_init_animation(2);
            o->oFaceAngleYaw = o->oMoveAngleYaw+0x8000;
            o->oForwardVel *= .99f;
            o->oInteractType = INTERACT_NONE;
            if (o->oMoveFlags & (OBJ_MOVE_HIT_WALL|OBJ_MOVE_HIT_EDGE)) {
                o->oMoveAngleYaw = random_u16();
            }
            if (o->oTimer > 60) {
                if (o->oHealth > 0) {
                    o->oAction = PM_ACT_IDLE;
                } else {
                    cur_obj_play_sound_2(SOUND_MENU_ENTER_PIPE);
                    o->oAction = PM_ACT_FEAR;
                    o->oDamageOrCoinValue = 0;
                }
            }
            break;
        case PM_ACT_FEAR:
            o->oInteractType = INTERACT_BOUNCE_TOP;
            if (o->oTimer < 200) {
                o->header.gfx.scale[0] = approach_f32_asymptotic(o->header.gfx.scale[0],0.5f,0.1f);
            } else {
                o->header.gfx.scale[0] = approach_f32_asymptotic(o->header.gfx.scale[0],1.0f,0.1f);
                if (o->header.gfx.scale[1] > 0.98f) {
                    o->oAction = PM_ACT_IDLE;
                    o->oHealth = 1;
                    cur_obj_scale(1.0f);
                    cur_obj_play_sound_2(SOUND_MENU_EXIT_PIPE);
                    break;
                }
            }
            cur_obj_scale(o->header.gfx.scale[0]);

            cur_obj_init_animation(3);
            if (o->oForwardVel < 55.0f) {
                o->oForwardVel += 4.0f;
            }
            if (o->oMoveFlags & (OBJ_MOVE_HIT_WALL|OBJ_MOVE_HIT_EDGE)) {
                o->oMoveAngleYaw = random_u16();
                if (o->oPosY < o->oHomeY + 10.0f) {
                    o->oVelY = 40.0f;
                    cur_obj_play_sound_2(SOUND_OBJ2_SCUTTLEBUG_ALERT);
                }
            }
            if ((o->oInteractStatus & INT_STATUS_WAS_ATTACKED)||(o->oShotByShotgun > 0)) {
                spawn_default_star(o->oHomeX,o->oHomeY+400.0f,o->oHomeZ);
                spawn_mist_particles_variable(0, 0, 200.0f);
                mark_obj_for_deletion(o);
            }
            break;
    }
    o->oInteractStatus = 0;
    o->oShotByShotgun = 0;
}