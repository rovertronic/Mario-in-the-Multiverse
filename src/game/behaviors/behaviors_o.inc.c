//checkpoint flag

void bhv_checkpoint_flag(void) {
    if (o->oBehParams2ndByte!=gMarioState->numCheckpointFlag) {
        o->oAnimState = 0;
        if (o->oDistanceToMario < 100.0f) {
            gMarioState->numCheckpointFlag = o->oBehParams2ndByte;
            o->oAnimState = 1;
            o->oVelY = 4000.0f;
            o->oTimer = 0;

            play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gMarioState->marioObj->header.gfx.cameraToObject);

            //move the death warp to me
            struct Object *dw = cur_obj_nearest_object_with_behavior(bhvDeathWarp);
            if (dw) {
                dw->oPosX = o->oPosX;
                dw->oPosY = o->oPosY+150.0f;
                dw->oPosZ = o->oPosZ;
            }
        }
    }

    if (o->oVelY > 2000.0f) {
        struct Object *sparkleObj = spawn_object(o, MODEL_SPARKLES, bhvCoinSparkles);
        sparkleObj->oPosX += random_float() * 50.0f - 25.0f;
        sparkleObj->oPosY += random_float() * 100.0f;
        sparkleObj->oPosZ += random_float() * 50.0f - 25.0f;
    }

    o->oFaceAngleRoll = sins(o->oTimer*0x900)*o->oVelY;
    o->oVelY *= 0.97f;
}

//flip switch

#define oSwitchState oHealth

u8 tiles_active = 0;
u8 tiles_needed = 0;
u8 tiles_hasmodel_count = 0;
u8 tiles_star_spawned = FALSE;
void bhv_flipswitch(void) {
    if ((tiles_active == tiles_needed) && (o->oAction > 1)) {
        if (o->oSwitchState == TRUE) {
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_FLIPSWITCH_3];
            o->oSwitchState = FALSE;
            tiles_hasmodel_count --;
        }
        if ((tiles_hasmodel_count == 0)&&(!tiles_star_spawned)) {
            tiles_star_spawned = TRUE;
            spawn_default_star(o->oPosX,o->oPosY+400.0f,o->oPosZ);
        }
        return;
    }

    switch(o->oAction) {
        case 0://init
            o->oAction = 1;
            o->oSwitchState = FALSE;
            tiles_needed = 0;
            tiles_active = 0;
            tiles_hasmodel_count = 0;
            tiles_star_spawned = FALSE;
            cur_obj_scale(1.0f + (o->oBehParams2ndByte*0.5f));
        break;
        case 1:
            tiles_needed ++;
            o->oAction = 2;
        break;
        case 2: //mario off
            if (gMarioObject->platform == o) {
                cur_obj_play_sound_2(SOUND_GENERAL_BOWSER_KEY_LAND);
                o->oAction = 3;
                o->oSwitchState = !o->oSwitchState;

                if (o->oSwitchState) {
                    tiles_active++;
                    if (tiles_active != tiles_needed) { //prevent being the 2nd model for 1 frame
                        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_FLIPSWITCH_2];
                    }
                } else {
                    tiles_active--;
                    o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_FLIPSWITCH_1];
                }
                tiles_hasmodel_count = tiles_active;
            }
        break;
        case 3: //mario on
            if (gMarioObject->platform != o) {
                o->oAction = 2;
            }
        break;
    }
}

//noteblock (from orchestral keys & btcm)
void bhv_noteblock(void) {
    o->oPosY = o->oHomeY + (sins(o->oTimer*5000) * o->oVelY);
    o->oVelY *= 0.95f;

    if (cur_obj_is_mario_on_platform()) {
        mario_stop_riding_and_holding(gMarioState);
        o->oTimer = 0;
        o->oVelY = 50.0f;
        cur_obj_play_sound_2(SOUND_GENERAL_CRAZY_BOX_BOING_SLOW);
        set_mario_action(gMarioState, ACT_DOUBLE_JUMP, 0);
        gMarioStates[0].vel[1] = 95.0f;
    }
}

//star piece switch

u8 star_pieces_got = 0;
void bhv_star_piece_switch_loop(void) {
    // The switch's model is 1/3 size.
    cur_obj_scale(3.0f);

    switch (o->oAction) {
        case BLUE_COIN_SWITCH_ACT_IDLE:
            // If Mario is on the switch and has ground-pounded,
            // recede and get ready to start ticking.
            if (((gMarioObject->platform == o) && (gMarioStates[0].action == ACT_GROUND_POUND_LAND))
                || (o->oShotByShotgun == 2)) {//--E
                //set star pieces got to 0
                star_pieces_got = 0;
                // Set to BLUE_COIN_SWITCH_ACT_RECEDING
                o->oAction = BLUE_COIN_SWITCH_ACT_RECEDING;
                // Recede at a rate of 16 units/frame.
                o->oVelY = -16.0f;

                // Set gravity to 0 so it doesn't accelerate when receding.
                o->oGravity = 0.0f;

                cur_obj_play_sound_2(SOUND_GENERAL_SWITCH_DOOR_OPEN);
            }
            o->oShotByShotgun = 0;//--E

            // Have collision
            load_object_collision_model();

            break;

        case BLUE_COIN_SWITCH_ACT_RECEDING:
            // Recede for 6 frames before going invisible and ticking.
            // This is probably an off-by-one error, since the switch is 100 units tall
            // and recedes at 20 units/frame, which means it will fully recede after 5 frames.

            if (o->oTimer > 3) {

                // Set to BLUE_COIN_SWITCH_ACT_TICKING
                o->oAction = BLUE_COIN_SWITCH_ACT_TICKING;

                // ???
                o->oVelY    = 0.0f;
                o->oGravity = 0.0f;

                // Spawn particles. There's a function that calls this same function
                // with the same arguments, spawn_mist_particles, why didn't they just call that?
                spawn_mist_particles_variable(0, 0, 46.0f);
            } else {
                // Have collision while receding
                load_object_collision_model();
                // Recede
                cur_obj_move_using_fvel_and_gravity();
            }

            break;

        case BLUE_COIN_SWITCH_ACT_TICKING:
            // Tick faster when the blue coins start blinking
            if (o->oTimer < (o->oBehParams2ndByte == 0 ? 200 : (o->oBehParams2ndByte * 10) - 40)) {
                play_sound(SOUND_GENERAL2_SWITCH_TICK_FAST, gGlobalSoundSource);
            } else {
                play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
            }

            if (star_pieces_got > 4) {//if (cur_obj_nearest_object_with_behavior(bhvHiddenBlueCoin) == NULL) {
                spawn_default_star(o->oPosX,o->oPosY+400.0f,o->oPosZ);
                spawn_mist_particles_variable(0, 0, 46.0f);
                obj_mark_for_deletion(o);
            // Set to BLUE_COIN_SWITCH_ACT_EXTENDING after the coins unload after the 240-frame timer expires.
            } else if (o->oTimer > (o->oBehParams2ndByte == 0 ? 240 : o->oBehParams2ndByte * 10)) {
                o->oAction  = BLUE_COIN_SWITCH_ACT_EXTENDING;
                o->oVelY    = 16.0f;
                o->oGravity =  0.0f;
            }
            load_object_collision_model();
            break;
        case BLUE_COIN_SWITCH_ACT_EXTENDING:
            if (o->oTimer > 3) {
                // Set to BLUE_COIN_SWITCH_ACT_IDLE
                o->oAction = BLUE_COIN_SWITCH_ACT_IDLE;
                o->oPosY = o->oHomeY; //thy be no evil shenanigans
            } else {
                // Have collision while extending
                load_object_collision_model();
                // Extend
                cur_obj_move_using_fvel_and_gravity();
            }
            break;
    }
}

//star piece.
void bhv_star_piece_loop(void) {
    struct Object *sps;

    o->oFaceAngleYaw += 0x400;
    o->oPosY = o->oHomeY + 20.0f + (sins(o->oTimer*0x500)*20.0f);

    sps = cur_obj_nearest_object_with_behavior(bhvStarPieceSwitch);

    switch(o->oAction) {
        case 0: // init
            cur_obj_hide();
            o->oAction = 1;
        break;
        case 1: //waiting
            if (sps && sps->oAction == BLUE_COIN_SWITCH_ACT_TICKING) {
                o->oAction = 2;
                cur_obj_unhide();
            }
        break;
        case 2: //active
            if (o->oDistanceToMario < 160.0f) {
                cur_obj_hide();
                cur_obj_play_sound_2(SOUND_MENU_COLLECT_SECRET+star_pieces_got);
                star_pieces_got++;
                o->oAction = 3;
            }

        case 3: //collected
            if (sps && (sps->oAction == BLUE_COIN_SWITCH_ACT_EXTENDING || sps->oAction == BLUE_COIN_SWITCH_ACT_IDLE)) {
                cur_obj_hide();
                o->oAction = 1;
            }
        break;
    }
}

static struct SpawnParticlesInfo sZombieBlood = {
    /* behParam:        */ 0,
    /* count:           */ 10,
    /* model:           */ MODEL_ZOMBLOOD,
    /* offsetY:         */ 90,
    /* forwardVelBase:  */ 4,
    /* forwardVelRange: */ 4,
    /* velYBase:        */ 10,
    /* velYRange:       */ 15,
    /* gravity:         */ -4,
    /* dragStrength:    */ 0,
    /* sizeBase:        */ 4,
    /* sizeRange:       */ 4,
};

static struct SpawnParticlesInfo sZombieHeadBlood1 = {
    /* behParam:        */ 0,
    /* count:           */ 20,
    /* model:           */ MODEL_ZOMBLOOD,
    /* offsetY:         */ 127,
    /* forwardVelBase:  */ 4,
    /* forwardVelRange: */ 4,
    /* velYBase:        */ 10,
    /* velYRange:       */ 15,
    /* gravity:         */ -4,
    /* dragStrength:    */ 0,
    /* sizeBase:        */ 9,
    /* sizeRange:       */ 6,
};

static struct ObjectHitbox sZombieHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 3,
    /* numLootCoins:      */ 0,
    /* radius:            */ 60,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 60,
    /* hurtboxHeight:     */ 160,
};

s32 walker_check_dmg(void) {
    u8 damaged = FALSE;
    u8 damage_count = 1;
    o->oInteractType = INTERACT_DAMAGE;

    //mario states where he can kill well
    if ((gMarioState->action == ACT_ABILITY_AXE_JUMP)||(gMarioState->action == ACT_KNIGHT_SLIDE)||(aku_invincibility>0)) {
        o->oInteractType = INTERACT_BOUNCE_TOP;
        damage_count = 3;
        if (aku_invincibility>0) {
            damage_count = 1;
        }
    }
    if ((gMarioState->action == ACT_MOVE_PUNCHING)&&(using_ability(ABILITY_CHRONOS))) {
        o->oInteractType = INTERACT_BOUNCE_TOP;
        damage_count = 3;
    }
    if ((gMarioState->vel[1]>=0.0f)&&(using_ability(ABILITY_BIG_DADDY))) {
        o->oInteractType = INTERACT_BOUNCE_TOP;
        damage_count = 3;
    }

    if (o->oShotByShotgun > 0) {
        damaged = TRUE;
        if (o->oShotByShotgun == 2) {
            damage_count = 3;
        }
        o->oShotByShotgun = 0;
    }
    if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
        damaged = TRUE;
    }

    if (damaged) {
        o->oHealth-=damage_count;
        if (o->oHealth < 1) {
            cur_obj_play_sound_2(SOUND_MITM_LEVEL_O_WALKER_DIE);
            o->oAction = 5; //death
        } else {
            cur_obj_play_sound_2(SOUND_MITM_LEVEL_O_WALKER_HIT);
            o->oAction = 4; //hurt
        }
        return TRUE;
    }

    return FALSE;
}

s32 zombie_audio_variance[] = {
    SOUND_MITM_LEVEL_O_WALKER_AGGRO1,
    SOUND_MITM_LEVEL_O_WALKER_AGGRO2,
    SOUND_MITM_LEVEL_O_WALKER_AGGRO3,
    SOUND_MITM_LEVEL_O_WALKER_AGGRO4,
};

//zambie
void bhv_o_walker_update(void) {
    f32 walkspeed = 0.0f;
    u16 view_angle = ABS(o->oAngleToMario-o->oFaceAngleYaw);
    u8 touched_another_zombie = FALSE;
    u32 is_underwater = (o->oMoveFlags & (OBJ_MOVE_UNDERWATER_OFF_GROUND|OBJ_MOVE_UNDERWATER_ON_GROUND));

    lv_o_zombie_counting++;

    switch(o->oAction) {
        case 1:
        case 4:
        case 7:
        if (!(o->oInteractStatus & INT_STATUS_ATTACK_MASK)) {
            touched_another_zombie = obj_resolve_object_collisions_zombie(NULL);
        }
    }
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(78);


    switch(o->oAction) {
        case 0: //init
            obj_set_hitbox(o, &sZombieHitbox);
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_O_ZOMBIE_1+(random_u16()%3) ];
            o->oAction = 7;
            o->oForwardVel = 0.0f;
            o->oFaceAngleYaw = random_u16();

            cur_obj_init_animation_with_accel_and_sound(7, 1.0f);
        break;
        case 1://walking
            if (o->oTimer == 0) {
                o->header.gfx.animInfo.animFrame = random_u16()%48;
                o->oTimer = random_u16();
                if (is_underwater) {
                    cur_obj_init_animation_with_accel_and_sound(1, 2.0f);
                }
            }
            o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw, o->oAngleToMario+(sins(o->oTimer*0x50)*0x1000), 8);
            o->oFaceAngleYaw = o->oMoveAngleYaw;
            walkspeed = (sins((o->header.gfx.animInfo.animFrame/50.0f)*65535.0f ) * 1.0f)+4.0f;
            o->oForwardVel = approach_f32_asymptotic(o->oForwardVel,walkspeed,0.2f);

            if ((is_underwater)&&(gMarioState->pos[1] > o->oPosY)&&(o->oVelY < 15.0f)) {
                if (o->oVelY < 5.0f) {
                    o->oVelY = 5.0f;
                }
                o->oVelY += 0.8f;
            }

            if ((random_u16()%20)==0) {
                cur_obj_play_sound_2(zombie_audio_variance[random_u16()%4]);
            }

            if (o->oDistanceToMario>5000.0f) { //lose sight of mario
                o->oAction = 7; //idle
                cur_obj_init_animation_with_accel_and_sound(7, 1.0f);
            }

            if ((o->oMoveFlags & OBJ_MOVE_IN_AIR) && (!is_underwater)) {
                o->oAction = 2; //falling
                cur_obj_init_animation_with_accel_and_sound(1, 2.0f);
            }

            if (o->oDistanceToMario < 150.0f) {
                o->oAction = 6; //eating
            }

            walker_check_dmg();
        break;
        case 2: //falling
            o->oForwardVel = 2.0f;
            if (o->oMoveFlags & (OBJ_MOVE_LANDED|OBJ_MOVE_ON_GROUND)) {
                cur_obj_init_animation_with_accel_and_sound(2, 1.0f);
                o->oAction = 3; //getting up
                o->oVelY = 0.0f;
                cur_obj_play_sound_2(SOUND_GENERAL_SMALL_BOX_LANDING);
            }
            if (is_underwater) {
                o->oAction = 1;
            }
        break;
        case 3: //getting up
            if (o->oTimer >= 30) {
                o->oAction = 1; //walking
                cur_obj_init_animation_with_accel_and_sound(3, 1.0f);
            }
        break;
        case 4: //damaged
            o->oInteractType = INTERACT_NONE;
            cur_obj_become_intangible();
            if (o->oTimer == 0) {
                cur_obj_init_animation_with_accel_and_sound(4, 1.0f);
                cur_obj_spawn_particles(&sZombieBlood);
            }
            o->oForwardVel = -1.0f;
        
            if (o->oTimer >= 30) {
                cur_obj_become_tangible();
                o->oAction = 1; //walking
                cur_obj_init_animation_with_accel_and_sound(3, 1.0f);
            }
        break;
        case 5: //death
            cur_obj_become_intangible();
            o->oInteractType = INTERACT_NONE;
            if (o->oTimer == 0) {
                cur_obj_init_animation_with_accel_and_sound(5, 1.0f);
                o->oPosY += 30.0f;
                cur_obj_spawn_particles(&sZombieHeadBlood1);
                o->oPosY -= 30.0f;
            }

            o->oForwardVel = 0.0f;

            if (o->oTimer >= 60) {
                obj_mark_for_deletion(o);
            }
        break;
        case 6: //eating
            if (o->oTimer == 0) {
                cur_obj_init_animation_with_accel_and_sound(6, 1.0f);
            }

            o->oFaceAngleYaw = o->oAngleToMario;
            o->oForwardVel = 0.0f;

            if (o->oTimer % 20 == 0) {
                cur_obj_play_sound_2(SOUND_MITM_LEVEL_O_WALKER_EAT);
            }

            if (o->oTimer > 15) {
                gMarioState->health -= 4;
            }
            
            if (o->oDistanceToMario > 200.0f) {
                cur_obj_become_tangible();
                o->oAction = 1; //walking
                cur_obj_init_animation_with_accel_and_sound(3, 1.0f);
            }

            walker_check_dmg();
        break;
        case 7: //idle
            o->oForwardVel = 0.0f;

            if (o->oDistanceToMario<4000.0f) {
                if ((view_angle < 0x2000)||(o->numCollidedObjs > 0)) {
                    cur_obj_init_animation_with_accel_and_sound(3, 1.0f);
                    o->oAction = 1;
                }
            }

            walker_check_dmg();

        break;
    }

    o->oIntangibleTimer = 0;
    o->oInteractStatus = 0;

    if (o->oTimer > 0) {
        if ((o->oPosY < -8000.0f)||(o->oDistanceToMario>10000.0f)) {
            //despawn if the zombie falls off the map / gets too far from mario
            obj_mark_for_deletion(o);
        }
    }
}

void bhv_zambie_spawner() {
    u8 bells_tolling = FALSE;

    u8 zambie_thresh = 25;
    u16 timer_rand = 100;

    if (bells_tolling) {
        zambie_thresh = 40;
        timer_rand = 190;
    }

    if (o->oTimer > 200) {
        if ((o->oDistanceToMario>4000.0f)&&(o->oDistanceToMario<10000.0f)&&(lv_o_zombie_counter < zambie_thresh)) {
            spawn_object(o,MODEL_NONE,bhvOZombie);
        }
        o->oTimer = random_u16()%timer_rand;
    }
}

void bhv_o_tree_init(void) {
    cur_obj_scale(0.9f + (random_float()*0.3f));
    o->oFaceAngleYaw = random_u16();
}

void bhv_hidden_by_uv(void) {
    if (using_ability(ABILITY_GADGET_WATCH)) {
        cur_obj_unhide();
    } else {
        cur_obj_hide();
    }
}

void bhv_o_lift(void) {
    struct Object *rocketbutton = cur_obj_nearest_object_with_behavior(bhvRocketButton);
    switch(o->oAction) {
        case 0:
            o->oHomeY = o->oPosY;
            if ((rocketbutton) && (rocketbutton->oAction > 0)) {
                play_puzzle_jingle();
                o->oAction++;
                o->oPosY -= 3800.0f;
            }
        break;
        case 1:
            if (gMarioObject->platform == o) {
                o->oAction = 2;
            }
        break;
        case 2:
            if (o->oPosY < o->oHomeY) {
                o->oPosY += 40.0f;
                cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);
            } else {
                if (rocketbutton) {
                    o->oAction = 0;
                    rocketbutton->oAction = 0;
                }
            }
        break;
    }
}