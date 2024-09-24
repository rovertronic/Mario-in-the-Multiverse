//checkpoint flag

void bhv_checkpoint_flag(void) {
    if ((o->oBehParams2ndByte==gMarioState->numCheckpointFlag)&&(gCurrAreaIndex == gMarioState->areaCheckpointFlag))  {
        // Am the current checkpoint flag
        if (o->oAnimState != 1) {
            o->oAnimState = 1;

            //move the death warp to me
            struct Object *dw = cur_obj_nearest_object_with_behavior(bhvDeathWarp);
            if (dw) {
                dw->oPosX = o->oPosX+sins(o->oFaceAngleYaw)*101.0f;
                dw->oPosY = o->oPosY+150.0f;
                dw->oPosZ = o->oPosZ+coss(o->oFaceAngleYaw)*101.0f;
                vec3f_copy(gMarioState->vecCheckpointFlag,&dw->oPosVec);
            }
        }
    } else {
        // Not the current checkpoint flag
        o->oAnimState = 0;
        if (o->oDistanceToMario < 100.0f) {
            gMarioState->numCheckpointFlag = o->oBehParams2ndByte;
            gMarioState->areaCheckpointFlag = gCurrAreaIndex;
            o->oAnimState = 1;
            o->oVelY = 4000.0f;
            o->oTimer = 0;

            play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gMarioState->marioObj->header.gfx.cameraToObject);

            //move the death warp to me
            struct Object *dw = cur_obj_nearest_object_with_behavior(bhvDeathWarp);
            if (dw) {
                dw->oPosX = o->oPosX+sins(o->oFaceAngleYaw)*101.0f;
                dw->oPosY = o->oPosY+150.0f;
                dw->oPosZ = o->oPosZ+coss(o->oFaceAngleYaw)*101.0f;
                vec3f_copy(gMarioState->vecCheckpointFlag,&dw->oPosVec);
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
            load_object_static_model();
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
            if (sps && sps->oTimer > (sps->oBehParams2ndByte == 0 ? 200 : (sps->oBehParams2ndByte * 10) - 40)) {
                if (gGlobalTimer % 2 == 0) {
                    cur_obj_unhide();
                } else {
                    cur_obj_hide();
                }
            }

            if (o->oDistanceToMario < 160.0f) {
                cur_obj_hide();
                cur_obj_play_sound_2(SOUND_MENU_COLLECT_SECRET+star_pieces_got);
                spawn_object(o, MODEL_SPARKLES, bhvCoinSparklesSpawner);
                star_pieces_got++;
                spawn_orange_number(star_pieces_got, 0, 0, 0);
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
            cur_obj_init_animation_with_accel_and_sound(7, 1.0f);
            if (o->oBehParams2ndByte == 1) {
                o->oAction = 1;
                cur_obj_init_animation_with_accel_and_sound(3, 1.0f);
            }
            o->oForwardVel = 0.0f;
            o->oFaceAngleYaw = random_u16();
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

            if ((o->oDistanceToMario>5000.0f)&&(o->oBehParams2ndByte!=1)) { //lose sight of mario
                o->oAction = 7; //idle
                cur_obj_init_animation_with_accel_and_sound(7, 1.0f);
            }

            if ((o->oMoveFlags & OBJ_MOVE_IN_AIR) && (!is_underwater) && (o->oFloorHeight < o->oPosY-10.0f)) {
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
                if (gSaveBuffer.menuData.config[SETTINGS_BLOOD] == 0) {
                    cur_obj_spawn_particles(&sZombieBlood);
                }
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
                if (gSaveBuffer.menuData.config[SETTINGS_BLOOD] == 0) {
                    o->oPosY += 30.0f;
                    cur_obj_spawn_particles(&sZombieHeadBlood1);
                    o->oPosY -= 30.0f;
                }
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

    if ((o->oFloorType == SURFACE_INSTANT_QUICKSAND)&&(o->oMoveFlags & (OBJ_MOVE_LANDED|OBJ_MOVE_ON_GROUND))) {
        create_sound_spawner(SOUND_ACTION_WATER_PLUNGE);
        obj_mark_for_deletion(o);
    }
}

u8 speakers_shot = 0;
u8 easystreet_mission_state = 0;

void bhv_zambie_spawner() {
    u8 zambie_thresh = 25;
    u16 timer_rand = 100;

    if (o->oBehParams2ndByte==1) {
        if (easystreet_mission_state != 2) {
            //don't spawn zombies til easy street starts playing
            return;
        }
        zambie_thresh = 30;
        timer_rand = 195;
    }

    if (o->oTimer > 200) {
        if ((o->oDistanceToMario>4000.0f)&&(o->oDistanceToMario<10000.0f)&&(lv_o_zombie_counter < zambie_thresh)) {
            struct Object * zambie = spawn_object(o,MODEL_NONE,bhvOZombie);
            zambie->oBehParams2ndByte = o->oBehParams2ndByte;
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

void bhv_o_garage(void) {
    o->oPosY += o->oVelY;
    o->oVelY -= 2.0f;

    if (o->oPosY < o->oHomeY-900.0f) {
        o->oPosY = o->oHomeY-900.0f;
        if (o->oAction == 0) {
            cur_obj_play_sound_2( SOUND_GENERAL_ELEVATOR_LAND);
            o->oAction++;
        }
    }
}

void bhv_o_speaker(void) {
    switch(o->oAction) {
        case 0: //init
            o->oAction++;
            o->oInteractType = INTERACT_BOUNCE_TOP;
            o->oVelY = 0.0f;
            cur_obj_become_intangible();
        break;
        case 1://wait to play
            if (easystreet_mission_state == 2) {
                o->oAction++;
                cur_obj_become_tangible();
            }
        break;
        case 2://playing
            cur_obj_scale( 1.0f + sins(o->oTimer*0x1000)*0.1f );

            if (easystreet_mission_state < 2) {
                //stop sound
                o->oAction--;
            }

            if ((o->oShotByShotgun > 0)||(o->oInteractStatus & INT_STATUS_WAS_ATTACKED)) {
                speakers_shot++;
                o->oAction++;
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_O_SPEAKER_2];
                o->oVelY = 10.0f;
                o->oMoveAngleYaw = o->oFaceAngleYaw-0x4000;

                struct Object *other_half = spawn_object(o,MODEL_O_SPEAKER_3,bhvOspeaker);
                other_half->oAction = 3;
                other_half->oVelY = 10.0f;
                other_half->oMoveAngleYaw = o->oFaceAngleYaw+0x4000;
            }
        break;
        case 3://destroyed
            o->oPosY += o->oVelY;
            o->oVelY -= 2.0f;

            o->oPosX += sins(o->oMoveAngleYaw)*20.0f;
            o->oPosZ += coss(o->oMoveAngleYaw)*20.0f;

            if (o->oTimer > 50) {
                obj_mark_for_deletion(o);
            }
        break;
    }
    o->oInteractStatus = 0;
    o->oIntangibleTimer = 0;
}

void bhv_o_easystreet_mission_controller(void) {
    switch(o->oAction) {
        case 0://init
            speakers_shot = 0;
            o->oAction++;
        break;
        case 1://wait for easy street mission to begin
            if ((gMarioState->pos[1] < o->oPosY)&&(o->oDistanceToMario<6700.0f)) {
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_O_EASYSTREET), 0);
                o->oAction++;
            }
        break;
        case 2://easy street playing
            if (gMarioState->pos[1] > o->oPosY) { //mario left
                stop_background_music(SEQUENCE_ARGS(4, SEQ_O_EASYSTREET));
                o->oAction = 1;
            }
            if (speakers_shot == 7) {
                stop_background_music(SEQUENCE_ARGS(4, SEQ_O_EASYSTREET));
                o->oAction++;
            }
        break;
        case 3://mission end
            if (o->oTimer > 30) {
                spawn_default_star(o->oPosX,o->oPosY-1400.0f,o->oPosZ);
                o->oAction++;
            }
        break;
    }

    easystreet_mission_state = o->oAction;
}

u32 mission_behavior_list[] = {
    bhvRedCoin,
    bhvBriefcase,
    bhvOuvstar,
    bhvHiddenStarTrigger,
    bhvCagedToad,
    bhvFlipswitch,
};

struct Object *mario_find_nearest_object_with_behavior_exclude_used_mission_objects(const BehaviorScript *behavior) {
    uintptr_t *behaviorAddr = segmented_to_virtual(behavior);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;
    struct Object *closestObj = NULL;
    f32 minDist = 0x20000;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr
            && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED
            // discriminate against used mission objects
            && (!(obj_has_behavior(obj,bhvFlipswitch)&&obj->oSwitchState == TRUE))
        ) {
            f32 objDist = dist_between_objects(gMarioObject, obj);
            if (objDist < minDist) {
                closestObj = obj;
                minDist = objDist;
            }
        }

        obj = (struct Object *) obj->header.next;
    }

    return closestObj;
}

struct Object *find_nearest_mission_target(void) {
    //stupid ass function
    struct Object *result;
    struct Object *closest = NULL;
    struct Object *myself = o;
    f32 closest_dist = 9999.0f;

    for (u8 i=0; i < sizeof(mission_behavior_list)/4; i++) {
        result = mario_find_nearest_object_with_behavior_exclude_used_mission_objects(mission_behavior_list[i]);
        if (result) {
            f32 this_dist = dist_between_objects(gMarioObject,result);
            if (this_dist < closest_dist) {
                closest_dist = this_dist;
                closest = result;
            }
        }
    }

    return closest;
}

void bhv_red_arrow(void) {
    o->oFaceAngleRoll = 0;
    o->oFaceAnglePitch = 0;

    struct Object * target = find_nearest_mission_target();
    if (target!=NULL) {
        o->oFaceAngleYaw = obj_angle_to_object(o, target);
    } else {
        o->oFaceAngleYaw += 0x200;
    }

    vec3f_copy(&o->oPosVec,gMarioState->pos);
}

void bhv_hub_platform_loop(void) {
    if (o->oTimer==0) {
        o->oFaceAngleYaw = random_u16();
    }
    if (gMarioObject->platform == o) {
        o->oFaceAngleYaw += 80;
        o->oPosY = approach_f32_asymptotic(o->oPosY,o->oHomeY-50.0f,0.2f);
    } else {
        o->oPosY = approach_f32_asymptotic(o->oPosY,o->oHomeY,0.2f);
        o->oFaceAngleYaw += 40;
    }
}

void bhv_matplatform(void) {
    Mat4 *transform = &o->transform;

    transform[0][1][0] = sins(o->oTimer*0x200);
    transform[0][1][2] = coss(o->oTimer*0x200);
    vec3f_copy(transform[0][3],&o->oPosVec);

    o->header.gfx.throwMatrix = transform;
}

void bc_stair_loop(void) {
    struct Object *rocketbutton = cur_obj_nearest_object_with_behavior(bhvRocketButton);
    Mat4 *transform = &o->transform;
    Mat4 *transform2 = NULL;
    if (o->prevObj) {
        transform2 = &o->prevObj->transform;
    }

    switch(o->oAction) {
        case 0:
            o->prevObj = spawn_object(o,MODEL_BC_STAIR_2,bhvStaticObject);
            o->prevObj->oPosX -= 330.0f;
            o->prevObj->oPosY -= 330.0f;
            transform2 = &o->prevObj->transform;
            o->oHealth = 0;
            o->oAction = 1;
            break;
        case 1:
            if(rocketbutton->oAction > 0){
                o->oAction = 2;
                gCamera->cutscene = 1;
            }
            break;
        case 2:
            if (o->oBehParams2ndByte == 1) {
                vec3f_copy(&gLakituState.goalFocus,&o->oPosVec);
                vec3f_copy(&gLakituState.goalPos,&o->oPosVec);
                gLakituState.goalPos[0] -= 1000.0f;
                gLakituState.goalPos[1] += 1000.0f;
                gLakituState.goalPos[2] += 1000.0f;
                if (o->oTimer > 45) {
                    o->oAction = 3;
                    gCamera->cutscene = 0;
                }
            }
            break;
        case 3:

            break;
    }

    if ((rocketbutton->oAction == 0)&&(o->oHealth<30)) {
        o->oHealth ++;
    }

    if ((rocketbutton->oAction > 0)&&(o->oHealth>0)) {
        o->oHealth --;
    }

    f32 y = o->oHealth/30.0f;

    transform[0][0][1] = y;
    transform2[0][1][1] = 1.0f-y;
    vec3f_copy(transform[0][3],&o->oPosVec);
    vec3f_copy(transform2[0][3],&o->prevObj->oPosVec);

    o->header.gfx.throwMatrix = transform;
    o->prevObj->header.gfx.throwMatrix = transform2;
}

void bhv_machine_door(void) {
    u8 have_enough_stars = TRUE;
    u8 have_artifact = TRUE;

    if ((have_enough_stars)&&(have_artifact)) {
        o->oFaceAngleYaw = -0x7000;
    } else {
        o->oFaceAngleYaw = 0;
        load_object_collision_model();
    }
}

void bhv_artreus_artifact_on_machine(void) {
    u8 have_artifact = TRUE;

    if (have_artifact) {
        cur_obj_unhide();
        o->oFaceAnglePitch += ABS(sins(o->oTimer*0x300)*0x300);
    } else {
        cur_obj_hide();
    }
}

void bhv_npc_egadd_loop(void) {
    s32 dialogResponse;
    u8 have_enough_stars = FALSE;
    u8 have_artifact = FALSE;

    s32 egadd_advice_dialog = DIALOG_EGADD_1;
    if ((have_enough_stars)&&(!have_artifact)) {
        egadd_advice_dialog = DIALOG_EGADD_2;
    }
    if ((!have_enough_stars)&&(have_artifact)) {
        egadd_advice_dialog = DIALOG_EGADD_3;
    }
    if ((have_enough_stars)&&(have_artifact)) {
        egadd_advice_dialog = DIALOG_EGADD_4;
    }

    switch (o->oAction) {
        case 0:
            if (o->oDistanceToMario < 1000.0f) {
                o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x140);
            }
            if (o->oInteractStatus == INT_STATUS_INTERACTED) {
                o->oAction = 1;
            }
            break;

        case 1:
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x1000);
            if ((s16) o->oMoveAngleYaw == (s16) o->oAngleToMario) {
                o->oAction = 2;
            }
            break;

        case 2:
            dialogResponse = cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP, DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, egadd_advice_dialog);
            if (dialogResponse != DIALOG_RESPONSE_NONE) {
                o->oAction = 0;
            }
            break;
    }

    o->oInteractStatus = 0;
}

void bhv_stargoo(void) {
    f32 scale = gMarioState->numStars/70.0f;
    if (scale < 0.05f) {
        scale = 0.05f;
    }
    if (scale > 1.0f) {
        scale = 1.0f;
    }
    o->header.gfx.scale[1] = scale;
}


enum {
    GERIK_INIT,
    GERIK_PATROL,
    GERIK_CHASE,
    GERIK_LEAVE,
    GERIK_GRABMARIO,
};

#define GERIK_PATROL_RADIUS 21000.0f

u8 gerik_jump_desire = 0;
s16 gerik_boredom = 0;
s16 gerik_patrol_angle = 0;

void gerik_step_sound(void) {
    switch(o->header.gfx.animInfo.animFrame) {
        case 0:
        case 11:
            cur_obj_play_sound_2(SOUND_ACTION_METAL_STEP);
            cur_obj_shake_screen(SHAKE_POS_MEDIUM);
        break;
    }
}

void gerik_step_sound_slow(void) {
    if (o->oDistanceToMario < 6000.0f) {
        switch(o->header.gfx.animInfo.animFrame) {
            case 0:
            case 21:
                cur_obj_play_sound_2(SOUND_ACTION_METAL_STEP);
            break;
        }
    }
}

void gerik_init_loop() {
    u8 starflags = save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_THI));
    u8 starsinlevel = 0;
    for (int i = 0; i < 8; i++) {
        if (starflags & (1<<i)) {
            starsinlevel++;
        }
    }

    if (starsinlevel<3) {
        cur_obj_hide();
        cur_obj_become_intangible();
    } else {
        cur_obj_unhide();
        cur_obj_become_tangible();
        cur_obj_init_animation_with_sound(4);
        o->oAction = GERIK_PATROL;

        o->oGravity = -2.0f;
        o->oWallHitboxRadius = 100.0f;
        gerik_jump_desire = 0;
    }
}

void gerik_patrol(void) {
    if (cur_obj_lateral_dist_to_home() > GERIK_PATROL_RADIUS) {
        o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw, cur_obj_angle_to_home(), 8);
    } else {
        o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw, gerik_patrol_angle, 8);
    }

    switch(o->oSubAction) {
        case 0: // stand for a bit before choosing new patrol spot
            if (o->oTimer > 60) {
                o->oSubAction = 1;
                o->oTimer = 0;
                cur_obj_init_animation_with_sound(5);
            }
            break;
        case 1: // walk to new patrol

            o->oForwardVel = 15.0f;

            cur_obj_update_floor_and_walls();
            cur_obj_move_standard(78);

            if (o->oMoveFlags & (OBJ_MOVE_HIT_WALL|OBJ_MOVE_HIT_EDGE)) {
                o->oSubAction = 0;
                o->oTimer = 0;
                gerik_patrol_angle = random_u16();
                cur_obj_init_animation_with_sound(4);
                break;
            }

            gerik_step_sound_slow();

            if (o->oTimer > 80) {
                o->oSubAction = 0;
                o->oTimer = 0;
                gerik_patrol_angle = random_u16();
                cur_obj_init_animation_with_sound(4);
            }
            break;
    }

    u16 view_angle = ABS(o->oAngleToMario-o->oFaceAngleYaw);
    
    Vec3f hitPos;
    struct Surface * surf = NULL;

    Vec3f ray_start = {o->oPosX,o->oPosY+100.0f,o->oPosZ};
    Vec3f ray_vector = {gMarioState->pos[0]-o->oPosX,(gMarioState->pos[1]-o->oPosY)+100.0f,gMarioState->pos[2]-o->oPosZ};
    if (o->oDistanceToMario < 6000.0f) {
        find_surface_on_ray(ray_start, ray_vector, &surf, hitPos, (RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL | RAYCAST_FIND_WALL));
    }

    if (gerik_boredom > 0) {
        gerik_boredom -= 2;
    }
    if ((gerik_boredom < 1)&&(view_angle < 0x3000)&&(o->oDistanceToMario < 6000.0f)&&(!surf)) {
        o->oAction = GERIK_CHASE;
        gerik_boredom = 0;
        cur_obj_init_animation_with_sound(0);
    }
}

void gerik_kill_walkers() {
    struct Object * walker = cur_obj_nearest_object_with_behavior(bhvOZombie);
    if ((walker)&&(dist_between_objects(o,walker) < 300.0f)) {
        if (walker->oAction != 5) {
            walker->oAction = 5;
        }
    }
}

void bhv_o_gerik(void) {

    switch(o->oAction) {
        case GERIK_INIT:
            gerik_init_loop();
            break;
        case GERIK_CHASE:
            if (gerik_boredom == 0) {
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_MASTER_KAAG_BOSS), 0);
            }
            gerik_boredom ++;
            if ((o->oMoveFlags & (OBJ_MOVE_HIT_WALL|OBJ_MOVE_HIT_EDGE))&&(o->oMoveFlags & OBJ_MOVE_ON_GROUND)) {
                o->oMoveAngleYaw += 0x200;
                o->oTimer = 0;
                gerik_jump_desire ++;
                if (gerik_jump_desire > 200) {
                    gerik_jump_desire = 0;
                    o->oVelY = 60.0f;
                    cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_JUMP);
                }
            } else {
                o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw, o->oAngleToMario, 8);
                if (o->oTimer > 15) {
                    gerik_jump_desire = 0;
                }
            }
            o->oForwardVel = 50.0f;

            if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
                gerik_step_sound();
            }

            cur_obj_update_floor_and_walls();
            cur_obj_move_standard(78);

            if (o->oDistanceToMario < 250.0f) {
                stop_background_music(SEQUENCE_ARGS(4, SEQ_MASTER_KAAG_BOSS));

                cur_obj_play_sound_2(SOUND_OBJ_GRAB_MARIO);
                o->oAction = GERIK_GRABMARIO;
                o->prevObj = gMarioObject;
                set_mario_action(gMarioState,ACT_CM_CUTSCENE,0);
                set_mario_animation(gMarioState,MARIO_ANIM_DROWNING_PART1);
                cur_obj_init_animation_with_sound(3);
                vec3f_copy(gMarioState->pos,gMarioObject->header.gfx.pos);
            }
            if ((cur_obj_lateral_dist_to_home() > GERIK_PATROL_RADIUS)||(gerik_boredom > 1200)) {
                stop_background_music(SEQUENCE_ARGS(4, SEQ_MASTER_KAAG_BOSS));
                o->oAction = GERIK_LEAVE;
                cur_obj_init_animation_with_sound(4);
            }
            break;
        case GERIK_GRABMARIO:
            o->oForwardVel *= .7f;
            cur_obj_update_floor_and_walls();
            cur_obj_move_standard(78);
            if (o->oTimer == 100) {
                level_trigger_warp(gMarioState, WARP_OP_DEATH);
                o->prevObj = NULL;
            }
            if (o->oTimer > 150) {
                cur_obj_init_animation_with_sound(4);
                o->oAction = GERIK_PATROL;
                vec3f_copy(&o->oPosVec,&o->oHomeVec);
                o->oMoveAngleYaw = 0;
            }
            break;
        case GERIK_LEAVE:
            if (o->oTimer > 15) {
                o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw, cur_obj_angle_to_home(), 8);
            }
            if (o->oTimer == 30) {
                cur_obj_init_animation_with_sound(5);
            }
            if (o->oTimer > 30) {
                o->oForwardVel = 15.0f;
                gerik_step_sound_slow();

                cur_obj_update_floor_and_walls();
                cur_obj_move_standard(78);

                 if (o->oMoveFlags & (OBJ_MOVE_HIT_WALL|OBJ_MOVE_HIT_EDGE) || o->oTimer > 400) {
                    o->oAction = GERIK_PATROL;
                    cur_obj_init_animation_with_sound(4);
                 }
            }
            break;
        case GERIK_PATROL:
            gerik_patrol();
            break;
    }

    if (o->oShotByShotgun > 0) {
        // The gerik is too strong to be beat by the shotgun ツ
        cur_obj_play_sound_2(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL);
        o->oShotByShotgun = 0;

        if (o->oAction == GERIK_PATROL) {
            o->oAction = GERIK_CHASE;
            gerik_boredom = 0;
            cur_obj_init_animation_with_sound(0);
        }
    }

    o->oIntangibleTimer = 0;
    //o->oInteractStatus = 0;
}


Vec3f cardstar_size = {70.0f,70.0f,70.0f};

Vec3f cardstar_verts[10] = {
	{0.0f,  1.0f,  0.1f},
    {1.0f,  0.0f,  0.1f},
    {-1.0f, 0.0f,  0.1f},
    {0.5f , -1.0f, 0.1f},
    {-0.5f, -1.0f, 0.1f},

	{0.0f,  1.0f,  -0.1f},
    {1.0f,  0.0f,  -0.1f},
    {-1.0f, 0.0f,  -0.1f},
    {0.5f , -1.0f, -0.1f},
    {-0.5f, -1.0f, -0.1f},
};

struct MeshInfo cardstar_mesh = {
    cardstar_verts,
    NULL,
    NULL,
    NULL,
    10, // Number of vertices
    0,
    0,
    0
};

void bhv_cardstar_init(void) {
    struct RigidBody *body = allocate_rigid_body_from_object(o, &cardstar_mesh, 0.7f, cardstar_size, FALSE);
}

void bhv_cardstar(void) {
    struct RigidBody *body = o->rigidBody;

    switch(o->oAction) {
        case 0:
            o->oAction = 1;
        break;
        case 1:
            if (o->oDistanceToMario < 100.0f) {
                o->oAction = 2;

                cur_obj_play_sound_2(SOUND_GENERAL_SMALL_BOX_LANDING);
                drop_and_set_mario_action(gMarioState, ACT_JUMP_KICK, 0);

                Vec3f force;
                force[0] = gMarioState->vel[0]*3.0f;
                force[2] = gMarioState->vel[2]*3.0f;
                force[1] = 50.0f*3.0f;
                rigid_body_add_force(body, &gMarioState->pos, force, TRUE);
            }
        break;
        case 2:
            if (body->linearVel[1] < 0.0f) {
                o->oAction = 0;
            }
        break;
    }
}

/* SECRET BOSS CODE */
void bhv_sb_torch(void) {
    switch(o->oAction) {
        case 0:
            if (gMarioState->pos[2] > o->oPosZ-100.0f) {
                o->oAction++;
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_SB_TORCH_2];
                o->prevObj = spawn_object(o,MODEL_RED_FLAME,bhvFlame);
                o->prevObj->oPosX += 500.0f;
                o->prevObj->oPosY += 160.0f;
                o->prevObj = spawn_object(o,MODEL_RED_FLAME,bhvFlame);
                o->prevObj->oPosX -= 500.0f;
                o->prevObj->oPosY += 160.0f;
                cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
            }
            break;
        case 1:

            break;
    }
}

enum {
    SB_ACT_INIT,
    SB_ACT_WAIT,
    SB_ACT_CUTSCENE,
    SB_ACT_BATTLE_MAIN,
    SB_ACT_ATTACK_SPIN,
};

void sb_create_train(Vec3f pos, s16 angle) {
    struct Object * gap = spawn_object(o,MODEL_SB_GAP,bhvSbGap);
    gap->oPosX = pos[0]+(sins(angle)*6000.0f);
    gap->oPosY = pos[1];
    gap->oPosZ = pos[2]+(coss(angle)*6000.0f);
    gap->oFaceAngleYaw = angle+0x8000;
    gap->oHealth = 130;

    gap = spawn_object(o,MODEL_SB_GAP,bhvSbGap);
    gap->oPosX = pos[0]-(sins(angle)*6000.0f);
    gap->oPosY = pos[1];
    gap->oPosZ = pos[2]-(coss(angle)*6000.0f);
    gap->oFaceAngleYaw = angle;
    gap->oHealth = 130;

    //actually train, not gap
    gap = spawn_object(o,MODEL_SB_TRAIN,bhvSbTrain);
    gap->oPosX = pos[0]-(sins(angle)*6000.0f);
    gap->oPosY = pos[1]+400.0f;
    gap->oPosZ = pos[2]-(coss(angle)*6000.0f);
    gap->oFaceAngleYaw = angle;
}

u8 sbsky_envcolor = 0;
extern u8 cm_cutscene_on;
struct Object * gasterObj = NULL;
struct Object * yukariObj = NULL;
void bhv_sb_manager(void) {
    switch(o->oAction) {
        case SB_ACT_INIT:
            sbsky_envcolor = 0;
            o->oAction = SB_ACT_WAIT;
            gasterObj = cur_obj_nearest_object_with_behavior(bhvSbGaster);
            yukariObj = cur_obj_nearest_object_with_behavior(bhvSbYukari);
            break;
        case SB_ACT_WAIT:
            if (o->oDistanceToMario < 2500.0f) {
                struct Object * cutscene = spawn_object(o,MODEL_NONE,bhvCutsceneManager);
                cutscene->oBehParams2ndByte = 2;
                o->oAction = SB_ACT_CUTSCENE;
            }
            break;
        case SB_ACT_CUTSCENE:
            {
                //somewhat lazy way of clearing out the entryway
                struct Object * deleteit;
                deleteit = cur_obj_nearest_object_with_behavior(bhvStaticObject);
                if (deleteit) {
                    obj_mark_for_deletion(deleteit);
                }
                deleteit = cur_obj_nearest_object_with_behavior(bhvSbTorch);
                if (deleteit) {
                    obj_mark_for_deletion(deleteit);
                }
                deleteit = cur_obj_nearest_object_with_behavior(bhvFlame);
                if (deleteit) {
                    obj_mark_for_deletion(deleteit);
                }

                if (o->oTimer > 2 && !cm_cutscene_on) {
                    o->oAction = SB_ACT_BATTLE_MAIN;
                }
            }
            break;
        case SB_ACT_BATTLE_MAIN:

            if (o->oTimer > 30) {
                o->oAction = SB_ACT_ATTACK_SPIN;
            }
            break;
        case SB_ACT_ATTACK_SPIN:
            if (o->oTimer == 0) {

            }
            if (o->oTimer%20==0) {
                for (int i = 0; i < 0xffff; i+=0x800) {
                    s16 timeoffset = 0x10*o->oTimer;
                    Vec3f danmaku_vec = {sins(i+timeoffset)*60.0f,0.0f,coss(i+timeoffset)*60.0f};
                    yukariObj->oPosY += 40.0f;
                    create_danmaku(&yukariObj->oPosVec,danmaku_vec);
                    yukariObj->oPosY -= 40.0f;
                }


                Vec3f train_spawn = {o->oHomeX,SB_Y,o->oHomeZ};
                sb_create_train(train_spawn,gGlobalTimer*0x100);
            }
            break;
    }
    if (o->oAction >= SB_ACT_BATTLE_MAIN) {
        if (sbsky_envcolor < 255) {
            sbsky_envcolor ++;
        }
    }
}

enum {
    SB_ACTOR_IDLE,
    SB_ACTOR_PASSIVE,
    SB_ACTOR_AGGRESSIVE,
};

void bhv_sb_actor(void) {
    switch(o->oAction) {
        case SB_ACTOR_IDLE:

            break;
        case SB_ACTOR_AGGRESSIVE:
            
            break;
        case SB_ACTOR_PASSIVE:

            break;
    }
}

void bhv_sb_gap(void) {
    if (o->oTimer == 0) {
        o->header.gfx.scale[0] = 0.0f;
    }
    if (o->oTimer < o->oHealth) {
        o->header.gfx.scale[0] = approach_f32_asymptotic(o->header.gfx.scale[0],1.0f,0.2f);
    } else {
        o->header.gfx.scale[0] = approach_f32_asymptotic(o->header.gfx.scale[0],0.0f,0.2f);
        if (o->header.gfx.scale[0] < .05f) {
            obj_mark_for_deletion(o);
        }
    }
}

static struct ObjectHitbox sTrainHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 3,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 240,
    /* height:            */ 1200,
    /* hurtboxRadius:     */ 60,
    /* hurtboxHeight:     */ 160,
};


void bhv_sb_train(void) {
    if (o->oTimer < 30) {
        cur_obj_scale(0.01f);
        cur_obj_hide();
    } else {
        if (o->oTimer < 115) {
            o->header.gfx.scale[1] = approach_f32_asymptotic(o->header.gfx.scale[1],1.5f,0.3f);
            o->oPosY = approach_f32_asymptotic(o->oPosY,SB_Y,0.3f);
            load_object_collision_model();
        } else {
            o->header.gfx.scale[1] = approach_f32_asymptotic(o->header.gfx.scale[1],0.01f,0.3f);
            o->oPosY = approach_f32_asymptotic(o->oPosY,SB_Y+400.0f,0.3f);
        }

        obj_set_hitbox(o,&sTrainHitbox);
        
        cur_obj_unhide();

        o->oForwardVel = 140.0f;
        o->oPosX += sins(o->oFaceAngleYaw) * o->oForwardVel;
        o->oPosZ += coss(o->oFaceAngleYaw) * o->oForwardVel;

        if (o->oTimer >  130) {
            obj_mark_for_deletion(o);
        }
        cur_obj_scale(o->header.gfx.scale[1]);
    }
}