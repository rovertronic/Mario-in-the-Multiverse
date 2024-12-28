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
        gMarioStates[0].vel[1] = 95.0f + (o->oBehParams2ndByte*10.0f);
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
            if ((gMarioObject->platform == o) && (gMarioStates[0].action == ACT_GROUND_POUND_LAND)) {
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
                // Extend
                cur_obj_move_using_fvel_and_gravity();
            }
            load_object_collision_model();
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
    bhvStarPieceSwitch,
    bhvBriefcase,
    bhvOuvstar,
    bhvHiddenStarTrigger,
    bhvCagedToad,
    bhvFlipswitch,
    bhvHoodmonger,
    bhvHoodboomer,
    bhvElectrohead,
    bhvKbillionare,
    bhvMiltank,
    bhvBoo,
    bhvGengar,
    bhvHaunter,
    bhvSkarmory,
    bhvOspeaker
};

struct Object *mario_find_nearest_object_with_behavior_exclude_used_mission_objects(const BehaviorScript *behavior) {
    uintptr_t *behaviorAddr = segmented_to_virtual(behavior);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;
    struct Object *closestObj = NULL;
    f32 minDist = 30000.0f;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr
            && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED
            // discriminate against used mission objects
            && (!(obj_has_behavior(obj,bhvFlipswitch)&&(obj->oSwitchState == TRUE||tiles_star_spawned)))
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

    o->header.gfx.node.flags |= GRAPH_RENDER_DONT_NORMALIZE_TRANS_LERP;
    if (o->prevObj) {
        transform2 = &o->prevObj->transform;
    }

    switch(o->oAction) {
        case 0:
            o->prevObj = spawn_object(o,MODEL_BC_STAIR_2,bhvStaticObject);
            o->prevObj->header.gfx.node.flags |= GRAPH_RENDER_DONT_NORMALIZE_TRANS_LERP;
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
    u8 have_enough_stars = (gMarioState->numStars >= 80);
    u8 have_artifact = ((save_file_get_flags() & SAVE_FLAG_ARTREUS_ARTIFACT)!= 0);

    if ((have_enough_stars)&&(have_artifact)) {
        o->oFaceAngleYaw = -0x7000;
    } else {
        o->oFaceAngleYaw = 0;
        load_object_collision_model();
    }
}

void bhv_artreus_artifact_on_machine(void) {
    u8 have_artifact = ((save_file_get_flags() & SAVE_FLAG_ARTREUS_ARTIFACT)!= 0);

    if (have_artifact) {
        cur_obj_unhide();
        o->oFaceAnglePitch += ABS(sins(o->oTimer*0x300)*0x300);
    } else {
        cur_obj_hide();
    }
}

void bhv_npc_egadd_loop(void) {
    s32 dialogResponse;
    u8 have_enough_stars = (gMarioState->numStars >= 80);
    u8 have_artifact = ((save_file_get_flags() & SAVE_FLAG_ARTREUS_ARTIFACT)!= 0);

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
    f32 scale = gMarioState->numStars/80.0f;
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
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_O_STH), 0);
            }
            gerik_boredom ++;
            if ((o->oMoveFlags & (OBJ_MOVE_HIT_WALL|OBJ_MOVE_HIT_EDGE))&&(o->oMoveFlags & OBJ_MOVE_ON_GROUND)) {
                o->oMoveAngleYaw += 0x200;
                o->oTimer = 0;
                /*
                gerik_jump_desire ++;
                if (gerik_jump_desire > 200) {
                    gerik_jump_desire = 0;
                    o->oVelY = 60.0f;
                    cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_JUMP);
                }
                */
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

            Vec3f hitPos;
            struct Surface * surf = NULL;
            Vec3f ray_start = {o->oPosX,o->oPosY+100.0f,o->oPosZ};
            Vec3f ray_vector = {gMarioState->pos[0]-o->oPosX,(gMarioState->pos[1]-o->oPosY)+100.0f,gMarioState->pos[2]-o->oPosZ};
            if (o->oDistanceToMario < 6000.0f) {
                find_surface_on_ray(ray_start, ray_vector, &surf, hitPos, (RAYCAST_FIND_FLOOR | RAYCAST_FIND_CEIL | RAYCAST_FIND_WALL));
            }
            if (surf) {
                //cant see, increase boredom faster
                gerik_boredom += 5;
            }

            cur_obj_update_floor_and_walls();
            cur_obj_move_standard(78);

            if (o->oDistanceToMario < 250.0f) {
                stop_background_music(SEQUENCE_ARGS(4, SEQ_O_STH));

                cur_obj_play_sound_2(SOUND_OBJ_GRAB_MARIO);
                o->oAction = GERIK_GRABMARIO;
                o->prevObj = gMarioObject;
                set_mario_action(gMarioState,ACT_CM_CUTSCENE,0);
                set_mario_animation(gMarioState,MARIO_ANIM_DROWNING_PART1);
                cur_obj_init_animation_with_sound(3);
                vec3f_copy(gMarioState->pos,gMarioObject->header.gfx.pos);
            }
            if ((cur_obj_lateral_dist_to_home() > GERIK_PATROL_RADIUS)||(gerik_boredom > 1200)) {
                stop_background_music(SEQUENCE_ARGS(4, SEQ_O_STH));
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
    SB_ATTACK_CIRCLES_BLASTERS,
};

enum {
    SB_ACTOR_IDLE,
    SB_ACTOR_PASSIVE,
    SB_ACTOR_AGGRESSIVE,
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
                o->oAction = SB_ATTACK_CIRCLES_BLASTERS;
            }
            break;
        case SB_ACT_ATTACK_SPIN:
            if (o->oTimer == 0) {
                gasterObj->oAction = SB_ACTOR_AGGRESSIVE;
                yukariObj->oAction = SB_ACTOR_PASSIVE;
            }
            if (o->oTimer%20==0) {
                Vec3f danmaku_vec;
                for (int i = 0; i<5; i++) {
                    vec3f_diff(danmaku_vec,gMarioState->pos,&gasterObj->oPosVec);
                    vec3f_normalize(danmaku_vec);
                    f32 spd = 30.0f+(i*10.f);
                    vec3f_scale(danmaku_vec,danmaku_vec,spd);
                    create_danmaku(&gasterObj->oPosVec,danmaku_vec,1);
                }


                Vec3f train_spawn = {o->oHomeX,SB_Y,o->oHomeZ};
                sb_create_train(train_spawn,gGlobalTimer*0x100);
            }
            break;
        case SB_ATTACK_CIRCLES_BLASTERS:
            if (o->oTimer == 0) {
                gasterObj->oAction = SB_ACTOR_AGGRESSIVE;
                yukariObj->oAction = SB_ACTOR_PASSIVE;
            }
            if (o->oTimer % 30 == 0) {
                for (int i = 0; i < 0xffff; i+=0x800) {
                    s16 timeoffset = 0x10*o->oTimer;
                    Vec3f danmaku_vec = {sins(i+timeoffset)*60.0f,-30.0f,coss(i+timeoffset)*60.0f};
                    create_danmaku(&yukariObj->oPosVec,danmaku_vec,0);
                }
            }
            break;
    }
    if (o->oAction >= SB_ACT_BATTLE_MAIN) {
        if (sbsky_envcolor < 255) {
            sbsky_envcolor ++;
        }
    }
}

//set oF4 to trigger generic danmaku sound
//set oF8 to indicate stunned
void bhv_sb_actor(void) {
    f32 orbit_max;
    f32 orbit_min;
    s16 orbit_dir;
    f32 backoff_speed;

    if (o->oF4) {
        cur_obj_play_sound_2(SOUND_MITM_LEVEL_SB_BULLET);
        o->oF4 = 0;
    }

    if (obj_has_behavior(o,bhvSbYukari)) {
        orbit_dir = -0x200;
        //yukari orbits counter clockwise
    } else {
        //gaster orbits clockwise
        orbit_dir = 0x200;
    }

    switch(o->oAction) {
        case SB_ACTOR_IDLE:
            o->parentObj = cur_obj_nearest_object_with_behavior(bhvSbManager);
            break;
        case SB_ACTOR_AGGRESSIVE:
            {
            orbit_max = 2500.0f;
            orbit_min = 1200.0f;
            backoff_speed = 4.0f;

            o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw,o->oAngleToMario,10);
            o->oFaceAngleYaw = o->oMoveAngleYaw;

            o->oGravity = 0.0f;
            o->oPosY = approach_f32_asymptotic(o->oPosY,gMarioState->pos[1] + 400.0f + sins(o->oTimer*0x200)*200.0f ,0.1f);

            o->oVelX += sins(o->oAngleToMario) * 2.0f;
            o->oVelZ += coss(o->oAngleToMario) * 2.0f;

            //damp vel
            o->oVelX *= .97f;
            o->oVelZ *= .97f;
            if (o->oDistanceToMario > orbit_max) {
                o->oVelX += sins(o->oAngleToMario) * 2.0f;
                o->oVelZ += coss(o->oAngleToMario) * 2.0f;

                //damp vel
                o->oVelX *= .97f;
                o->oVelZ *= .97f;
            }

            //too close, back off a fair bit
            if (o->oDistanceToMario < orbit_min) {
                //damp vel
                o->oVelX *= .97f;
                o->oVelZ *= .97f;

                o->oVelX -= sins(o->oAngleToMario+(o->oTimer*orbit_dir)) * backoff_speed;
                o->oVelZ -= coss(o->oAngleToMario+(o->oTimer*orbit_dir)) * backoff_speed;
            }

            cur_obj_update_floor_and_walls();
            cur_obj_move_standard_classc();
            }
            break;
        case SB_ACTOR_PASSIVE:
            {
            s16 yaw;
            Vec3f target = {o->parentObj->oPosX + sins(o->oTimer*orbit_dir/2)*6000.0f,.0f,o->parentObj->oPosZ + coss(o->oTimer*orbit_dir/2)*6000.0f};
            vec3f_get_yaw(&o->oPosVec,target,&yaw);

            o->oGravity = 0.0f;
            o->oPosY = approach_f32_asymptotic(o->oPosY, SB_Y + 400.0f + sins(o->oTimer*0x200)*200.0f ,0.1f);

            o->oVelX += sins(yaw) * 4.0f;
            o->oVelZ += coss(yaw) * 4.0f;

            //damp vel
            o->oVelX *= .97f;
            o->oVelZ *= .97f;

            cur_obj_update_floor_and_walls();
            cur_obj_move_standard_classc();
            }
            break;
    }
}

void bhv_sb_gap(void) {
    if (o->oTimer == 0) {
        o->header.gfx.scale[0] = 0.0f;
        cur_obj_play_sound_2(SOUND_MENU_ENTER_HOLE);
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
    /* damageOrCoinValue: */ 2,
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
        if (o->oDistanceToMario < 1500.0f && o->oHealth == 0) {
            o->oHealth = 1;
            cur_obj_play_sound_2(SOUND_MITM_LEVEL_SB_TRAIN);
        }

        if (o->oTimer < 115) {
            o->header.gfx.scale[1] = approach_f32_asymptotic(o->header.gfx.scale[1],1.5f,0.3f);
            o->oPosY = approach_f32_asymptotic(o->oPosY,SB_Y+3.0f,0.3f);
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

void bhv_sb_blaster(void) {
    switch(o->oAction) {
        case 0:
            cur_obj_play_sound_2(SOUND_MITM_LEVEL_SB_BLASTER);
            o->oAction = 1;
            o->oPosY = SB_Y + 2000.0f;
            o->oFaceAnglePitch = 0x2000;
            break;
        case 1:
            o->oFaceAnglePitch *= .9f;
            o->oPosY = approach_f32_asymptotic(o->oPosY,SB_Y+200.0f,0.2f);
            o->header.gfx.animInfo.animFrame = 0;
            if (o->oTimer >= 20) {
                o->oAction = 2;
            }
            break;
        case 2:
            if (o->oTimer == 15) {
                create_sound_spawner(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION);
                spawn_object(o,MODEL_SB_BLAST,bhvSbBlast);
            }
            if (o->oTimer > 30) {
                o->oAction = 3;
            }
            break;
        case 3:
            o->oPosY = approach_f32_asymptotic(o->oPosY,SB_Y+2000.0f,0.2f);
            if (o->oTimer > 30) {
                obj_mark_for_deletion(o);
            }
            break;
    }
}

void bhv_sb_blast(void) {
    if (o->oTimer == 0) {
        o->oOpacity = 255;
        o->oFaceAnglePitch = 0;
    }
    if (o->oOpacity > 10) {
        o->oOpacity -= 10;
    } else {
        obj_mark_for_deletion(o);
    }

        Vec3f pointA;
        Vec3f pointB;
        Vec3f pointC;
        Vec3f pointD;

        s16 laserWidth = 120;
        s16 laserLength = 10000 + 20*o->oTimer;

        vec3f_set(pointA, o->oPosX + laserWidth * coss(o->oFaceAngleYaw), o->oPosY, o->oPosZ + laserWidth * sins(o->oFaceAngleYaw + 0x50));
        vec3f_set(pointB, o->oPosX + laserWidth * -coss(o->oFaceAngleYaw), o->oPosY, o->oPosZ + laserWidth * -sins(o->oFaceAngleYaw + 0x50));

        vec3f_set(pointC, pointA[0] + laserLength * sins(o->oFaceAngleYaw), o->oPosY, pointA[2] + laserLength * coss(o->oFaceAngleYaw));
        vec3f_set(pointD, pointB[0] + laserLength * sins(o->oFaceAngleYaw), o->oPosY, pointB[2] + laserLength * coss(o->oFaceAngleYaw));

        if (point_inside_xz_tri(gMarioState->pos, pointA, pointB, pointC) || point_inside_xz_tri(gMarioState->pos, pointA, pointC, pointD)) {
            if (absf(o->oPosY - gMarioState->pos[1]) < 280 && gMarioState->action != ACT_BACKWARD_AIR_KB) {
                gMarioState->action = ACT_BACKWARD_AIR_KB;
                o->oDamageOrCoinValue = 1;
                take_damage_and_knock_back(gMarioState, o);
                gMarioState->vel[1] = 5;
                gMarioState->forwardVel = 0.0f;
                gMarioState->faceAngle[1] = o->oFaceAngleYaw + 0x8000;
            }
        }
}

enum {
    //main & transitional states
    FBOWSER_INIT,
    FBOWSER_DESCEND,
    FBOWSER_TRANSFORM,

    //monogomous fight states
    FBOWSER_EGG_JUMP_IN_MOBILE,
    FBOWSER_GASTER,
    FBOWSER_YUKARI,

    //sephiroth
    FBOWSER_SEPH_CHARGE,
    FBOWSER_SEPH_PARRIED,
    FBOWSER_SEPH_STAGGER,
    FBOWSER_SEPH_SWIPE,
    FBOWSER_SEPH_ARC,
    FBOWSER_SEPH_RSWIPE,
    FBOWSER_SEPH_DEFLECT,

    //hector is the name of the golem from b&s
    FBOWSER_HECTOR_INTRO,
    FBOWSER_HECTOR_SWIPE,
    FBOWSER_HECTOR_GETOFFHEAD,
    FBOWSER_HECTOR_WEAK,
    FBOWSER_HECTOR_DIE,
    FBOWSER_HECTOR_WALK,
    FBOWSER_HECTOR_LASER,
};

f32 lerp_standard(f32 v0, f32 v1, f32 t) {
  return v0 + t * (v1 - v0);
}

u8 first_time_visit = TRUE;

u8 fb_bowser_phase = 0;
u8 fb_bowser_path_index = 0;
Vec3f fb_bowser_path;
extern Vec3f sephisword_impact_vec;
extern struct Object * golem_part[4];

static struct ObjectHitbox sFbBowserHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 100,
    /* height:            */ 250,
    /* hurtboxRadius:     */ 180,
    /* hurtboxHeight:     */ 200,
};

u8 golem_crystals_destroyed = 0;
u8 golem_crystalps_destroyed = 0;
u8 golem_crystal_do_weaken = FALSE;

u8 golem_footsteps = 0;

struct Object * laser_point_1;
struct Object * laser_point_2;

extern Mat4 golem_part_transform[];
extern Vec3f golem_point[];
extern u8 sephisword_did_hit;

s32 hit_by_bowsers_weapon(void) {
    return ((sephisword_did_hit > 0) && (gMarioState->action != ACT_HARD_BACKWARD_AIR_KB) && (gMarioState->action != ACT_HARD_BACKWARD_GROUND_KB) && (gMarioState->action != ACT_SQUID) && (gMarioState->invincTimer == 0) && (aku_invincibility == 0) && ((gMarioState->action & ACT_GROUP_MASK) != ACT_GROUP_CUTSCENE));
}

void hector_general(void) {
    if (cur_obj_check_if_near_animation_end()) {
        u8 desired_next_action = FBOWSER_HECTOR_WALK;

        if (o->oAction == FBOWSER_HECTOR_WEAK) {
            golem_crystal_do_weaken = FALSE;
        }

        if (golem_footsteps > 1) {
            golem_footsteps = 0;
            if (lateral_dist_between_objects(o,gMarioObject) > 2000.0f) {
                desired_next_action = FBOWSER_HECTOR_LASER;
            }
        }

        if (gMarioObject->platform && obj_has_behavior(gMarioObject->platform,bhvBcGolemBody) ) {
            desired_next_action = FBOWSER_HECTOR_SWIPE;
        }
        if (gMarioObject->platform && obj_has_behavior(gMarioObject->platform,bhvBcGolemHead) ) {
            desired_next_action = FBOWSER_HECTOR_GETOFFHEAD;
        }
        if (golem_crystal_do_weaken) {
            desired_next_action = FBOWSER_HECTOR_WEAK;
        }
        if (golem_crystals_destroyed >= 7) {
            desired_next_action = FBOWSER_HECTOR_DIE;
        }

        o->oAction = desired_next_action;
        o->header.gfx.animInfo.animFrame = 0;
        o->oTimer = 0;
        switch(desired_next_action) {
            case FBOWSER_HECTOR_SWIPE:
                cur_obj_init_animation_with_sound(10);
                break;
            case FBOWSER_HECTOR_GETOFFHEAD:
                cur_obj_init_animation_with_sound(11);
                break;
            case FBOWSER_HECTOR_WEAK:
                cur_obj_init_animation_with_sound(12);
                break;
            case FBOWSER_HECTOR_DIE:
                cur_obj_init_animation_with_sound(13);
                break;
            case FBOWSER_HECTOR_WALK:
                golem_footsteps++;
                cur_obj_init_animation_with_sound(14);
                break;
            case FBOWSER_HECTOR_LASER:
                cur_obj_init_animation_with_sound(15);
                break;
        }
    }
    if (hit_by_bowsers_weapon()) {
        gMarioState->hurtCounter += 4;
        drop_and_set_mario_action(gMarioState, ACT_HARD_BACKWARD_AIR_KB, 3);
        create_sound_spawner(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION);
    }
    o->oInteractStatus = 0;

}

void sephiser_general_attack_handler(void) {
    if (hit_by_bowsers_weapon() && o->oTimer > 10) {

        if (sephisword_did_hit == 2) {
            cur_obj_play_sound_2(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL);
            o->oAction = FBOWSER_SEPH_PARRIED;
            //e__sg_spark(sephisword_impact_vec, (0.5f + (random_float() * 3.f)));
            struct Object * spark = spawn_object(o,MODEL_SPARKLES,bhvCoinSparkles);
            vec3f_copy(&spark->oPosVec,sephisword_impact_vec);
        } else {
            gMarioState->hurtCounter += 4;
            drop_and_set_mario_action(gMarioState, ACT_HARD_BACKWARD_AIR_KB, 3);
        }
    }

    if (cur_obj_check_if_at_animation_end()) {
        o->oAction = FBOWSER_SEPH_SWIPE+(random_u16()%3);
        o->oTimer = 0;

        if (lateral_dist_between_objects(gMarioObject,o) > 500.0f) {
            o->oAction = FBOWSER_SEPH_CHARGE;
            cur_obj_init_animation_with_sound(16);
        }
    }

    if ((o->oInteractStatus & INT_STATUS_WAS_ATTACKED) || (o->oShotByShotgun > 0)) {
        o->oAction = FBOWSER_SEPH_DEFLECT;
        cur_obj_init_animation_with_sound(18);
    }
}

Vec3f fb_bowser_home = {0.0f,SB_Y,0.0f};
extern u8 sephisword_deflect_buffer;
void bhv_final_boss_bowser(void) {
    switch(o->oAction) {
        case FBOWSER_INIT:
            o->oInteractStatus = 0;
            cur_obj_hide();
            obj_set_hitbox(o,&sFbBowserHitbox);
            cur_obj_become_intangible();
            fb_bowser_phase = 0;
            fb_bowser_path_index = 0;
            golem_crystals_destroyed = 0;
            golem_crystalps_destroyed = 0;
            golem_crystal_do_weaken = FALSE;
            cur_obj_boss_shimmer_reset();
            break;
        case FBOWSER_DESCEND:
            if (o->oTimer == 0) {
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_FINAL_BOSS), 0);
                gDynamicPhase = 1;
                cur_obj_unhide();
                cur_obj_init_animation_with_sound(4);
            }
            if (o->oTimer == 44 && !first_time_visit) {
                o->oAction = FBOWSER_TRANSFORM;
            }
            break;
        case FBOWSER_SEPH_SWIPE:
            if (o->oTimer == 0) {
                cur_obj_init_animation_with_sound(2);
            }
            o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw,o->oAngleToMario,10);
            sephiser_general_attack_handler();
            break;
        case FBOWSER_SEPH_ARC:
            if (o->oTimer == 0) {
                cur_obj_init_animation_with_sound(3);
            }
            sephiser_general_attack_handler();
            break;
        case FBOWSER_SEPH_RSWIPE:
            if (o->oTimer == 0) {
                cur_obj_init_animation_with_sound(19);
            }
            o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw,o->oAngleToMario,10);
            sephiser_general_attack_handler();
            break;
        case FBOWSER_SEPH_PARRIED:
            o->header.gfx.animInfo.animFrame-=3;
            if (o->header.gfx.animInfo.animFrame < 0) {
                o->header.gfx.animInfo.animFrame=0;
                o->oAction = FBOWSER_SEPH_SWIPE+(random_u16()%3);
                o->oInteractStatus = 0;
                o->oTimer = 0;
                o->oHealth--;

                if (o->oHealth < 1) {
                    sephisword_deflect_buffer = 0;
                    o->oAction = FBOWSER_SEPH_STAGGER;
                    cur_obj_init_animation_with_sound(17);
                }
            }
            break;
        case FBOWSER_SEPH_STAGGER:
            if (o->oTimer == 0) {
                o->oForwardVel = -30.0f;
            }

            struct Surface * floorcheck;
            find_floor(o->oPosX,o->oPosY,o->oPosZ,&floorcheck);
            if (floorcheck && floorcheck->type != SURFACE_DEATH_PLANE) { 
                o->oPosX += sins(o->oFaceAngleYaw)*o->oForwardVel;
                o->oPosZ += coss(o->oFaceAngleYaw)*o->oForwardVel;
                o->oForwardVel *= .9f;
            }

            if (o->oTimer > 60) {
                o->oAction = FBOWSER_TRANSFORM;
            }
            break;
        case FBOWSER_SEPH_CHARGE:
            //chase mario if he's too away
            //move
            {
                o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw,o->oAngleToMario,8);

                f32 base_speed = 50.0f;
                f32 speed = base_speed;
                if (lateral_dist_between_objects(gMarioObject,o)-400.0f < 150.0f) {
                    speed = ((lateral_dist_between_objects(gMarioObject,o)-400.0f)/150.0f)*base_speed;
                }

                struct Surface * floorcheck;
                find_floor(o->oPosX,o->oPosY,o->oPosZ,&floorcheck);

                if (speed < 10.0f && floorcheck && floorcheck->type != SURFACE_DEATH_PLANE) { //TODO: add floor check so he doesnt float
                    o->header.gfx.animInfo.animFrame-=2;
                    if (o->header.gfx.animInfo.animFrame < 0) {
                        o->header.gfx.animInfo.animFrame=0;
                        o->oAction = FBOWSER_SEPH_SWIPE+(random_u16()%3);
                        o->oPosY = SB_Y+32.f;
                    }
                }

                Vec3f govec;
                vec3f_diff(govec,&gMarioState->pos,&o->oPosVec);
                vec3f_normalize(govec);
                vec3_mul_val(govec,speed);
                govec[1] = 0.0f;
                vec3f_sum(&o->oPosVec,&o->oPosVec,govec);

                o->oPosY = approach_f32_asymptotic(o->oPosY,SB_Y+32.f,.1f);

                if ((o->oInteractStatus & INT_STATUS_WAS_ATTACKED) || (o->oShotByShotgun > 0)) {
                    o->oAction = FBOWSER_SEPH_DEFLECT;
                    cur_obj_init_animation_with_sound(18);
                }
                if (hit_by_bowsers_weapon()) {
                    gMarioState->hurtCounter += 4;
                    drop_and_set_mario_action(gMarioState, ACT_HARD_BACKWARD_AIR_KB, 3);
                }
                o->oInteractStatus = 0;
            }
            break;
        case FBOWSER_SEPH_DEFLECT:
            if (o->oTimer == 0) {
                o->oFaceAngleYaw = o->oAngleToMario;
                cur_obj_play_sound_2(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL);
            }
            if (o->oTimer > 15) {
                o->oAction = FBOWSER_SEPH_SWIPE+(random_u16()%3);
            }
            break;
        case FBOWSER_TRANSFORM:
            o->oAnimState = 0;
            o->oFaceAngleYaw +=0x1000;

            if (o->header.gfx.animInfo.animFrame > 0) {
                o->header.gfx.animInfo.animFrame --;
            }
            if (o->oTimer == 0) {
                gDynamicPhase = 1;
                gMarioState->healCounter += 8;
            }
            if (o->oTimer == 24) {
                fb_bowser_phase++;
                spawn_mist_particles_variable(0, 0, 100.0f);
                switch(fb_bowser_phase) {
                    case 1:
                        cur_obj_init_animation_with_sound(5);
                        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_BC_BOWSER_FORM_2];
                        gDynamicPhase = 2;
                        break;
                    case 2:
                        cur_obj_init_animation_with_sound(6);
                        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_BC_BOWSER_FORM_3];
                        gDynamicPhase = 3;
                        break;
                    case 3:
                        cur_obj_init_animation_with_sound(8);
                        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_BC_BOWSER_FORM_4];
                        gDynamicPhase = 4;
                        break;
                    case 4:
                        gDynamicPhase = 5;
                        cur_obj_init_animation_with_sound(16);
                        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_BC_BOWSER_FORM_1];
                        break;
                    case 5:
                        gDynamicPhase = 6;
                        cur_obj_init_animation_with_sound(9);
                        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_BC_BOWSER_FORM_5];
                        o->oPosY = SB_Y;
                        break;
                }
            }

            o->oInteractStatus = 0;
            if (o->oTimer == 48) {
                //end
                switch(fb_bowser_phase) {
                    case 1:
                        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_BC_BOWSER_FORM_2];
                        o->oAction = FBOWSER_EGG_JUMP_IN_MOBILE;
                        break;
                    case 2:
                        o->oAction = FBOWSER_GASTER;
                        o->oHealth = 8;
                        o->oFlags |= OBJ_FLAG_E__SG_CUSTOM;
                        cur_obj_become_tangible();
                        break;
                    case 3:
                        o->oAction = FBOWSER_YUKARI;
                        o->oHealth = 10;
                        o->oFlags |= OBJ_FLAG_E__SG_CUSTOM;
                        cur_obj_become_tangible();
                        o->hitboxRadius = 600.0f;
                        o->hitboxHeight = 800.0f;
                        break;
                    case 4:
                        o->hitboxRadius = 100.0f;
                        o->hitboxHeight = 250.0f;

                        o->oHealth = 10;
                        cur_obj_become_tangible();
                        o->oAction = FBOWSER_SEPH_CHARGE;
                        break;
                    case 5:
                        cur_obj_become_intangible();
                        o->oAction = FBOWSER_HECTOR_INTRO;

                        struct Object * part = spawn_object(o,MODEL_NONE,bhvBcGolemBody);
                        part = spawn_object(o,MODEL_NONE,bhvBcGolemLimb);
                        part->oBehParams2ndByte = 1;
                        part = spawn_object(o,MODEL_NONE,bhvBcGolemLimb);
                        part->oBehParams2ndByte = 2;
                        part = spawn_object(o,MODEL_NONE,bhvBcGolemHead);
                        part->oBehParams2ndByte = 3;
                        part = spawn_object(o,MODEL_NONE,bhvBcGolemLimb);
                        part->oBehParams2ndByte = 4;
                        part = spawn_object(o,MODEL_NONE,bhvBcGolemLimb);
                        part->oBehParams2ndByte = 5;

                        for (int i=1; i<8; i++) {
                            part = spawn_object(o,MODEL_BC_CRYSTAL,bhvBcGolemCrystal);
                            part->oBehParams2ndByte = i;
                        }
                        for (int i=0; i<5; i++) {
                            part = spawn_object(o,MODEL_BC_CRYSTALG,bhvBcGolemCrystalp);
                            part->oPosX = sins((i*2+1)*0x1999)*3000.0f;
                            part->oPosY =SB_Y;
                            part->oPosZ = coss((i*2+1)*0x1999)*3000.0f;
                            part->oBehParams2ndByte = i;
                        }

                        part = spawn_object(o,MODEL_NONE,bhvBcGolemFoot);
                        part->oBehParams2ndByte = 8;
                        part = spawn_object(o,MODEL_NONE,bhvBcGolemFoot);
                        part->oBehParams2ndByte = 9;
                        break;
                }
            }
            break;
        case FBOWSER_EGG_JUMP_IN_MOBILE:
            if (o->oTimer == 0) {
                o->prevObj = spawn_object(o,MODEL_BC_PINGAS_PLANE,bhvBcPingasPlane);
                o->prevObj->oPosY -= 500.0f;
                o->prevObj->oPosX += 1200.0f;
                cur_obj_init_animation_with_sound(7);
            }


            if (o->oTimer == 50) {
                cur_obj_init_animation_with_sound(5);
            }
            if (o->oTimer > 50) {
                vec3f_copy(&o->oPosVec,&o->prevObj->oPosVec);
            } else {
                o->oPosX = lerpf(o->oHomeX,o->prevObj->oPosX,o->oTimer/50.0f);
                o->oPosY = lerpf(o->oHomeY,o->prevObj->oPosY,o->oTimer/50.0f) + sins((o->oTimer*0x8000)/50)*500.0f;
                o->oPosZ = lerpf(o->oHomeZ,o->prevObj->oPosZ,o->oTimer/50.0f);
            }
            o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw,o->prevObj->oFaceAngleYaw-0x4000,8);
            break;
        case FBOWSER_GASTER:
            o->oAnimState = 0;
            o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw,o->oAngleToMario,4);
            if (o->oSubAction == 0) {
                if (o->oTimer == 15) {
                    //gRandomSeed16 = o->oTimer;
                    for (int i = 0; i < 2; i++) {
                        struct Object * blaster = spawn_object(gMarioObject,MODEL_SB_BLASTER,bhvSbBlaster);
                        s16 random_angle = random_u16();
                        blaster->oPosX = o->oPosX + sins(o->oAngleToMario + 0x4000 + (i*0x8000))*500.0f;
                        blaster->oPosZ = o->oPosZ + coss(o->oAngleToMario + 0x4000 + (i*0x8000))*500.0f;
                        blaster->oMoveAngleYaw = o->oAngleToMario - 0x1000 +(random_u16()%0x2000);
                    }
                }
                if (o->oTimer == 30) {
                    vec3f_copy(&o->oHomeVec,&o->oPosVec);
                    fb_bowser_path[0] = sins((fb_bowser_path_index*2+1)*0x1999)*3000.0f;
                    fb_bowser_path[2] = coss((fb_bowser_path_index*2+1)*0x1999)*3000.0f;
                    fb_bowser_path[1] = SB_Y;
                    fb_bowser_path_index++;
                    o->oSubAction = 1;
                    o->oTimer = 0;
                }
            } else {
                if (o->oTimer <= 45) {
                    o->oPosX = lerpf(o->oHomeX,fb_bowser_path[0],o->oTimer/45.0f);
                    o->oPosY = lerpf(o->oHomeY,fb_bowser_path[1],o->oTimer/45.0f) + sins((o->oTimer*0x8000)/45)*1000.0f;
                    o->oPosZ = lerpf(o->oHomeZ,fb_bowser_path[2],o->oTimer/45.0f);

                    if ((o->oTimer == 22)&&(fb_bowser_path_index != 1)) {
                        Vec3f danmaku_vec;
                        for (int i = 0; i<5; i++) {
                            gMarioState->pos[1] -= 200.0f;
                            vec3f_diff(danmaku_vec,gMarioState->pos,&o->oPosVec);
                            gMarioState->pos[1] += 200.0f;
                            vec3f_normalize(danmaku_vec);
                            f32 spd = 30.0f+(i*10.f);
                            vec3f_scale(danmaku_vec,danmaku_vec,spd);
                            create_danmaku(&o->oPosVec,danmaku_vec,1);
                            cur_obj_play_sound_2(SOUND_OBJ_MRI_SHOOT);
                        }
                    }

                } else {
                    o->oSubAction = 0;
                    o->oTimer = 0;
                    cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
                    o->header.gfx.animInfo.animFrame = 0;

                    if (o->oHealth < 1) {
                        o->oAction = FBOWSER_TRANSFORM;
                        cur_obj_play_sound_2(SOUND_OBJ_BOWSER_DEFEATED);
                    }
                }
            }

            if ((o->oInteractStatus & INT_STATUS_WAS_ATTACKED) || (o->oShotByShotgun > 0)) {
                o->oHealth --;
                o->oAnimState = 1;
                o->oIntangibleTimer = 2;
                cur_obj_play_sound_2(SOUND_OBJ_BOWSER_TAIL_PICKUP);
            }

            o->oInteractStatus = 0;
            o->oShotByShotgun = 0;
            break;
        case FBOWSER_YUKARI:
            {
                f32 orbit_max;
                f32 orbit_min;
                s16 orbit_dir = 0x100;
                o->oAnimState = 0;
                o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw,o->oAngleToMario,4);

                //movement

                s16 yaw;
                Vec3f target = {sins(o->oTimer*orbit_dir/2)*3000.0f,.0f,coss(o->oTimer*orbit_dir/2)*3000.0f};
                vec3f_get_yaw(&o->oPosVec,target,&yaw);

                o->oGravity = 0.0f;
                o->oPosY = approach_f32_asymptotic(o->oPosY, SB_Y + 400.0f + sins(o->oTimer*0x200)*200.0f ,0.1f);

                o->oVelX += sins(yaw) * 4.0f;
                o->oVelZ += coss(yaw) * 4.0f;

                //damp vel
                o->oVelX *= .97f;
                o->oVelZ *= .97f;

                cur_obj_move_standard_classc();


                //attack
                if (o->oTimer > 60) {

                    if ((o->oTimer%80==0)&&(o->oHealth < 5)) {
                        Vec3f train_spawn = {0.0f,SB_Y+10.0f,0.0f};
                        sb_create_train(train_spawn,o->oFaceAngleYaw);
                    }

                    if (o->oTimer % 30 == 0) {
                        cur_obj_play_sound_1(SOUND_MITM_LEVEL_SB_BULLET);
                        for (int i = 0; i < 0xffff; i+=0x800) {
                            s16 timeoffset = 0x10*o->oTimer;
                            Vec3f danmaku_vec = {sins(i+timeoffset)*50.0f,-30.0f,coss(i+timeoffset)*50.0f};
                            create_danmaku(&o->oPosVec,danmaku_vec,0);
                        }
                        for (int i = 0; i < 0xffff; i+=0x800) {
                            s16 timeoffset = (0x10*o->oTimer)+0x5;
                            Vec3f danmaku_vec = {sins(i+timeoffset)*35.0f,-30.0f,coss(i+timeoffset)*35.0f};
                            create_danmaku(&o->oPosVec,danmaku_vec,2);
                        }
                    }
                }

                if ((o->oInteractStatus & INT_STATUS_WAS_ATTACKED) || (o->oShotByShotgun > 0)) {
                    o->oHealth --;
                    o->oAnimState = 1;
                    o->oIntangibleTimer = 2;
                    cur_obj_play_sound_2(SOUND_OBJ_BOWSER_TAIL_PICKUP);
                }

                o->oInteractStatus = 0;
                o->oShotByShotgun = 0;

                if (o->oHealth < 1) {
                    o->oAction = FBOWSER_TRANSFORM;
                }
            }
            break;
        case FBOWSER_HECTOR_INTRO:
            if (o->header.gfx.scale[0] < 4.0f) {
                if (o->header.gfx.animInfo.animFrame > 0) {
                    o->header.gfx.animInfo.animFrame --;
                }
                o->header.gfx.scale[0] += .04f;
                cur_obj_scale(o->header.gfx.scale[0]);
            } else {
                switch(o->header.gfx.animInfo.animFrame) {
                    case 26:
                    case 57:
                    case 148:
                        cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
                        break;
                }
                if (o->header.gfx.animInfo.animFrame == 94) {
                    cur_obj_play_sound_2(SOUND_MENU_BOWSER_LAUGH);
                }
            }
            hector_general();
            break;
        case FBOWSER_HECTOR_SWIPE:
            switch(o->header.gfx.animInfo.animFrame) {
                case 70:
                case 112:
                    cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
                    break;
            }
            if (o->header.gfx.animInfo.animFrame == 50) {
                cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_JUMP);
            }
            hector_general();
            break;
        case FBOWSER_HECTOR_GETOFFHEAD:
            switch(o->header.gfx.animInfo.animFrame) {
                case 26:
                case 61:
                    cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
                    break;
            }
            if (o->header.gfx.animInfo.animFrame == 21) {
                cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_JUMP);
            }
            hector_general();
            break;
        case FBOWSER_HECTOR_WEAK:
            if (o->oTimer == 10) {
                cur_obj_play_sound_2(SOUND_OBJ_BOWSER_DEFEATED);
            }
            switch(o->header.gfx.animInfo.animFrame) {
                case 36:
                case 51:
                    cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
                    break;
            }
            if (o->oTimer > 160) {
                cur_obj_play_sound_1(SOUND_ENV_BOWLING_BALL_ROLL);
            }
            hector_general();
            break;
        case FBOWSER_HECTOR_DIE:
            if (o->oTimer == 10) {
                cur_obj_play_sound_2(SOUND_OBJ_BOWSER_DEFEATED);
            }
            switch(o->header.gfx.animInfo.animFrame) {
                case 1:
                case 40:
                    cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_JUMP);
                    break;
            }
            if (o->oTimer > 80) {
                //clean up spawned parts
                struct Object * deleteit;
                deleteit = cur_obj_nearest_object_with_behavior(bhvBcGolemBody);
                if (deleteit) {
                    obj_mark_for_deletion(deleteit);
                }
                deleteit = cur_obj_nearest_object_with_behavior(bhvBcGolemHead);
                if (deleteit) {
                    obj_mark_for_deletion(deleteit);
                }
                deleteit = cur_obj_nearest_object_with_behavior(bhvBcGolemLimb);
                while (deleteit) {
                    obj_mark_for_deletion(deleteit);
                    deleteit = cur_obj_nearest_object_with_behavior(bhvBcGolemLimb);
                }
                deleteit = cur_obj_nearest_object_with_behavior(bhvBcGolemFoot);
                while (deleteit) {
                    obj_mark_for_deletion(deleteit);
                    deleteit = cur_obj_nearest_object_with_behavior(bhvBcGolemFoot);
                }

                if (cur_obj_final_boss_shimmer_death(700.0f,2.5f)) {
                    struct Object * cutscene = spawn_object(o,MODEL_NONE,bhvCutsceneManager);
                    cutscene->oBehParams2ndByte = 6;

                    obj_mark_for_deletion(o);
                }
            }
            break;
        case FBOWSER_HECTOR_WALK:
            switch(o->header.gfx.animInfo.animFrame) {
                case 20:
                case 30:
                case 50:
                case 58:
                    cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
                    break;
            }

            o->oForwardVel = 6.0f;
            if ((o->oTimer < 20)||(o->oTimer > 30 && o->oTimer < 50)) {
                o->oPosX += sins(o->oFaceAngleYaw)*o->oForwardVel;
                o->oPosZ += coss(o->oFaceAngleYaw)*o->oForwardVel;

                f32 dist;
                s16 yaw;
                vec3f_get_dist_and_yaw(fb_bowser_home,&o->oPosVec,&dist,&yaw);
                if (dist < 800.0f) {
                    o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, o->oAngleToMario, 0x80);
                } else {
                    o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, yaw+0x8000, 0x100);
                }
            }

            hector_general();
            break;
        case FBOWSER_HECTOR_LASER:

            o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, o->oAngleToMario, 0x80); 

            if (o->oTimer == 20) {
                struct Object * laser = spawn_object(o,MODEL_BC_LASER,bhvBcGolemLaser);
                vec3f_copy(&laser->oPosVec,golem_point[0]);
                vec3f_copy(&laser->oHomeVec,golem_point[0]);
                laser->oHomeY = SB_Y;

                laser_point_1 = spawn_object(o,MODEL_BC_LASEREMIT,bhvStaticObject);
                obj_set_billboard(laser_point_1);
                vec3f_copy(&laser_point_1->oPosVec,golem_point[0]);

                laser_point_2 = spawn_object(o,MODEL_BC_LASEREMIT,bhvStaticObject);
                obj_set_billboard(laser_point_2);
                vec3f_copy(&laser_point_2->oPosVec,golem_point[0]);
                laser_point_2->oPosZ = SB_Y;
            }

            hector_general();
            break;
    }
    o->oInteractStatus = 0;
    o->oShotByShotgun = 0;
    sephisword_did_hit = 0;
}

enum {
    ATREUS_INIT,
    ATREUS_WAIT,
    ATREUS_CHAT_1,
    ATREUS_WAIT_2,
    ATREUS_BOWSER_AMBUSH,
    ATREUS_WATCHING_FIGHT,
    ATREUS_POST_FIGHT,
    ATREUS_SUCK_MARIO,
    ATREUS_ENTERED,
};


extern u8 cm_end_of_game_signal;
void bhv_atreus_bosscontroller(void) {
    switch(o->oAction) {
        case ATREUS_INIT:
            o->oAction = ATREUS_WAIT;
            break;
        case ATREUS_WAIT:
            o->header.gfx.animInfo.animFrame = 0;
            if (o->oDistanceToMario < 5000.0f) {
                if (first_time_visit) {
                    o->oAction = ATREUS_CHAT_1;
                    struct Object * cutscene = spawn_object(o,MODEL_NONE,bhvCutsceneManager);
                    cutscene->oBehParams2ndByte = 4;
                } else {
                    o->oAction = ATREUS_WATCHING_FIGHT;

                    struct Object * obj;
                    obj = cur_obj_nearest_object_with_behavior(bhvBcBowser);
                    if (obj) {
                        obj->oAction = FBOWSER_DESCEND;
                    }
                    obj = cur_obj_nearest_object_with_behavior(bhvBcBosslanding);
                    if (obj) {
                        obj_mark_for_deletion(obj);
                    }
                }
            }
            break;
        case ATREUS_CHAT_1:
            if (o->oTimer > 2 && !cm_cutscene_on) {
                o->oAction = ATREUS_WAIT_2;
            }
            break;
        case ATREUS_WAIT_2:
            if (o->oDistanceToMario < 4000.0f) {
                o->oAction = ATREUS_BOWSER_AMBUSH;
                struct Object * cutscene = spawn_object(o,MODEL_NONE,bhvCutsceneManager);
                cutscene->oBehParams2ndByte = 5;

                struct Object * obj;
                obj = cur_obj_nearest_object_with_behavior(bhvBcBosslanding);
                if (obj) {
                    obj_mark_for_deletion(obj);
                }
                obj = cur_obj_nearest_object_with_behavior(bhvBcBowser);
                if (obj) {
                    obj->oAction = FBOWSER_DESCEND;
                }
                vec3f_copy(gMarioObject->header.gfx.pos,&obj->oPosVec);
                gMarioObject->header.gfx.pos[2] += 80.0f;

                gMarioState->pos[0] = 0.0f;
                gMarioState->pos[1] = SB_Y;
                gMarioState->pos[2] = -1000.0f;
            }
            break;
        case ATREUS_BOWSER_AMBUSH:
            if (o->oTimer > 2 && !cm_cutscene_on) {
                o->oAction = ATREUS_WATCHING_FIGHT;

                struct Object * obj = cur_obj_nearest_object_with_behavior(bhvBcBowser);
                if (obj) {
                    obj->oInteractStatus = 0;
                    obj->oAction = FBOWSER_TRANSFORM;
                    first_time_visit = FALSE;
                }
            }
            break;
        case ATREUS_WATCHING_FIGHT:
            o->oPosZ = approach_f32_asymptotic(o->oPosZ,o->oHomeZ-4000.0f,0.1f);

            if (!cur_obj_nearest_object_with_behavior(bhvBcBowser)) {
                o->oAction = ATREUS_POST_FIGHT;
                stop_background_music(SEQUENCE_ARGS(4, SEQ_FINAL_BOSS));
            }
            break;
        case ATREUS_POST_FIGHT:
            o->oPosZ = approach_f32_asymptotic(o->oPosZ,o->oHomeZ,0.1f);

            if (o->oDistanceToMario < 3000.0f) {
                set_mario_action(gMarioState,ACT_CUTSCENE_CONTROLLED,0);
                set_mario_animation(gMarioState,MARIO_ANIM_AIRBORNE_ON_STOMACH);
                o->oAction = ATREUS_SUCK_MARIO;
            }
            break;
        case ATREUS_SUCK_MARIO:
            ;s16 mario_angle_to_atreus = obj_angle_to_object(gMarioObject,o);
            gMarioState->pos[0] += sins(mario_angle_to_atreus) * 10.0f;
            gMarioState->pos[2] += coss(mario_angle_to_atreus) * 10.0f;
            gMarioState->faceAngle[1] += 0x200;

            if (gMarioState->pos[1] < o->oPosY) {
                gMarioState->pos[1] += 7.0f;
            } else {
                gMarioState->pos[1] -= 7.0f;
            }

            if (o->oDistanceToMario < 2000.0f) {
                save_file_set_flags(SAVE_FLAG_BEAT_BOWSER);
                save_file_do_save(gCurrSaveFileNum - 1);

                o->oAction = ATREUS_ENTERED;
                play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x10, 0xFF, 0xFF, 0xFF);
            }
            break;
        case ATREUS_ENTERED:
            if (o->oTimer == 90) {
                initiate_warp(LEVEL_BIRTHDAY, 1, 0x02, WARP_FLAGS_NONE);
                cm_end_of_game_signal = TRUE;
            }
            break;
    }
}

u8 pingas_plane_path = 0;
Vec3f pingas_plane_target;

static struct ObjectHitbox sEggHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 8,
    /* numLootCoins:      */ 0,
    /* radius:            */ 320,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 300,
    /* hurtboxHeight:     */ 160,
};

extern Vec3f robodick_pos;
void bhv_pingas_plane(void) {
    switch(o->oAction) {
        case 0:
            o->header.gfx.animInfo.animFrame = 0;
            if (o->oTimer == 0) {
                pingas_plane_path = 0;
                o->prevObj = spawn_object(o,MODEL_BC_PINGAS_BALL,bhvBcPingasBall);
                vec3f_set(pingas_plane_target,0,0,0);
                
            }
            o->oPosY += 15.0f;
            if (o->oPosY > SB_Y+1150.0f) {
                o->oAction = 1;
            }
            break;
        case 1:
            //go
            {
                s16 dud;
                s16 travel_angle;
                f32 dist;
                if (o->oTimer == 0) {
                    obj_set_hitbox(o, &sEggHitbox);
                }

                pingas_plane_target[1] = o->oPosY;

                vec3f_get_angle(&o->oPosVec,pingas_plane_target,&dud,&travel_angle);
                vec3f_get_dist(&o->oPosVec,pingas_plane_target,&dist);

                o->oPosX += sins(travel_angle)*20.0f;
                o->oPosZ += coss(travel_angle)*20.0f;

                if (dist < 40.0f) {
                    pingas_plane_path++;
                    if (pingas_plane_path % 2 == 0) {
                        vec3f_set(pingas_plane_target,0,0,0);
                    } else {
                        pingas_plane_target[0] = sins((pingas_plane_path)*0x1999)*3000.0f;
                        pingas_plane_target[2] = coss((pingas_plane_path)*0x1999)*3000.0f;
                    }
                    
                }
                o->oFaceAngleYaw = approach_s16_asymptotic(o->oFaceAngleYaw, o->oAngleToMario+0x4000, 16);

                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_BC_PINGAS_PLANE];
                if (o->oTimer > 15 && o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
                    o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_BC_PINGAS_PLANE_DMG];
                    o->oTimer = 1;
                    o->oHealth --;
                }

                o->oInteractStatus = 0;

                if (o->oHealth < 1) {
                    o->oAction = 2;
                    cur_obj_play_sound_2(SOUND_OBJ_BOWSER_DEFEATED);
                    vec3f_set(pingas_plane_target,0,SB_Y,0);
                    mark_obj_for_deletion(o->prevObj);
                    o->prevObj = NULL;
                }
            }
            break;
        case 2: //die
            {
                s16 dud;
                s16 travel_angle;
                f32 dist;

                struct Object * bam = spawn_object(o,MODEL_EXPLOSION,bhvExplosionVisual);
                bam->oPosX += (random_float() * 400.0f)-200.0f;
                bam->oPosY += (random_float() * 400.0f)-200.0f;
                bam->oPosZ += (random_float() * 400.0f)-200.0f;

                vec3f_get_angle(&o->oPosVec,pingas_plane_target,&dud,&travel_angle);

                vec3f_get_lateral_dist(&o->oPosVec,pingas_plane_target,&dist);

                if (dist > 40.0f) {
                    o->oPosX += sins(travel_angle)*20.0f;
                    o->oPosZ += coss(travel_angle)*20.0f;
                }
                o->oPosY -= 15.0f;
                if (o->oPosY <= SB_Y) {
                    o->oPosY = SB_Y;
                }

                vec3f_get_dist(&o->oPosVec,pingas_plane_target,&dist);

                if (dist < 40.0f) {
                    o->parentObj->oAction = FBOWSER_TRANSFORM;
                    mark_obj_for_deletion(o);
                    return;
                }
            }
            break;
    }

    if (o->prevObj != NULL) {
        vec3f_copy(&o->prevObj->oPosVec,robodick_pos);
        o->prevObj->oInteractStatus = 0;
    }

    if (o->oShotByShotgun > 0) {
        // The pingas plane is too strong to be beat by the shotgun ツ
        cur_obj_play_sound_2(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL);
        o->oShotByShotgun = 0;
    }
}

void bhv_boss_defeat_star() {
    if (o->oTimer == 0) {
        o->oOpacity = 255;
        o->oBehParams2ndByte = random_u16();
        o->oVelY = 0.0f;

        o->oHomeX = random_float()-.5f;
        o->oHomeY = random_float()-.5f;
        o->oHomeZ = random_float()-.5f;
        vec3f_normalize(&o->oHomeVec);

        //stupid
        o->oHomeX *= 30.0f*o->header.gfx.scale[0];
        o->oHomeY *= 30.0f*o->header.gfx.scale[0];
        o->oHomeZ *= 30.0f*o->header.gfx.scale[0];
    }

    vec3f_sum(&o->oPosVec, &o->oPosVec, &o->oHomeVec);

    o->oPosY += o->oVelY*o->header.gfx.scale[0];
    o->oVelY -= 1.0f;

    if (o->oTimer > 25) {
        o->oOpacity *= .8f;
    }
    if (o->oTimer > 30) {
        mark_obj_for_deletion(o);
    }
}

void bhv_boss_defeat_wave(void) {
    cur_obj_scale(o->oTimer/2.0f);
    if (o->oTimer == 0) {
        o->oOpacity = 255;
    }
    o->oOpacity -= 5;
    if (o->oOpacity < 10) {
        mark_obj_for_deletion(o);
    }
}

void bhv_golem_limb(void) {
    cur_obj_scale(4.0f);
    o->header.gfx.throwMatrix = golem_part_transform[o->oBehParams2ndByte];
    mtxf_copy(o->transform,golem_part_transform[o->oBehParams2ndByte]);
}

static struct ObjectHitbox sGolemCrystalHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 8,
    /* numLootCoins:      */ 0,
    /* radius:            */ 100,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

static struct ObjectHitbox sGolemCrystalpHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 8,
    /* numLootCoins:      */ 0,
    /* radius:            */ 100,
    /* height:            */ 150,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};


static struct SpawnParticlesInfo sGolemBlood = {
    /* behParam:        */ 0,
    /* count:           */ 10,
    /* model:           */ MODEL_BC_CRYSTAL,
    /* offsetY:         */ 90,
    /* forwardVelBase:  */ 4,
    /* forwardVelRange: */ 4,
    /* velYBase:        */ 10,
    /* velYRange:       */ 15,
    /* gravity:         */ -4,
    /* dragStrength:    */ 0,
    /* sizeBase:        */ 2,
    /* sizeRange:       */ 2,
};

void bhv_golem_crystal(void) {
    vec3f_copy(&o->oPosVec,golem_point[o->oBehParams2ndByte]);
    obj_set_hitbox(o, &sGolemCrystalHitbox);

    if (golem_crystalps_destroyed+2 < o->oBehParams2ndByte) {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_BC_CRYSTALP];
    } else {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_BC_CRYSTAL];
        if ((o->oInteractStatus & INT_STATUS_INTERACTED)||(o->oShotByShotgun > 1)) {
            cur_obj_play_sound_2(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL);
            cur_obj_spawn_particles(&sGolemBlood);
            mark_obj_for_deletion(o);
            golem_crystals_destroyed++;
        }
    }

    o->oShotByShotgun = 0;
    o->oInteractStatus = 0;
}

void bhv_golem_crystalp(void) {
    obj_set_hitbox(o, &sGolemCrystalpHitbox);

    if (golem_crystals_destroyed <= o->oBehParams2ndByte) {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_BC_CRYSTALGP];
        if ((o->oInteractStatus & INT_STATUS_INTERACTED)) {

        }
    } else {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_BC_CRYSTALG];
        if (o->oInteractStatus & INT_STATUS_INTERACTED) {
            cur_obj_play_sound_2(SOUND_ACTION_SNUFFIT_BULLET_HIT_METAL);
            cur_obj_spawn_particles(&sGolemBlood);
            mark_obj_for_deletion(o);
            golem_crystalps_destroyed++;
            golem_crystal_do_weaken = TRUE;
        }
    }

    o->oShotByShotgun = 0;
    o->oInteractStatus = 0;
}

static struct ObjectHitbox sGolemFootHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 50,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 200,
    /* height:            */ 150,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

void bhv_golem_foot(void) {
    vec3f_copy(&o->oPosVec,golem_point[o->oBehParams2ndByte]);
    obj_set_hitbox(o, &sGolemFootHitbox);
    o->oInteractStatus = 0;

    if (o->parentObj->oAction == FBOWSER_HECTOR_WEAK) {
        cur_obj_become_intangible();
    } else {
        cur_obj_become_tangible();
    }
}

void bhv_golem_laser(void) {
    cur_obj_play_sound_1(SOUND_GENERAL_FLAME_OUT);

    //visuals pointing
    Vec3f origin;
    Vec3f dir;
    Vec3f hitpos;
    f32 a, b;

    vec3f_copy(&o->oHomeVec,golem_point[0]);
    vec3f_copy(hitpos, &o->oPosVec); // Source
    vec3f_copy(origin,&o->oHomeVec); // Target

    vec3f_copy(&laser_point_1->oPosVec,origin);
    vec3f_copy(&laser_point_2->oPosVec,hitpos);

    dir[0] = hitpos[0] - origin[0];
    dir[1] = hitpos[1] - origin[1];
    dir[2] = hitpos[2] - origin[2];

    o->header.gfx.scale[2] = -(sqrtf(dir[0]*dir[0] + dir[1]*dir[1] + dir[2]*dir[2])/100.0f);

    a=hitpos[0] - origin[0];
    b=hitpos[2] - origin[2];

    o->oFaceAngleYaw = atan2s(b,a);
    o->oFaceAnglePitch = atan2s( sqrtf((a*a) + (b*b)) ,origin[1]-hitpos[1]);

    //move
    f32 base_speed = 50.0f;
    f32 speed = base_speed;
    if (lateral_dist_between_objects(gMarioObject,o) < 200.0f) {
        speed = (lateral_dist_between_objects(gMarioObject,o)/200.0f)*base_speed;
    }
    Vec3f govec;
    vec3f_diff(govec,&gMarioState->pos,&o->oPosVec);
    vec3f_normalize(govec);
    vec3_mul_val(govec,speed);
    vec3f_sum(&o->oPosVec,&o->oPosVec,govec);

    o->oPosY = SB_Y;

    if (o->oTimer > 120) {
        mark_obj_for_deletion(laser_point_1);
        mark_obj_for_deletion(laser_point_2);
        mark_obj_for_deletion(o);
    }

    if (o->oTimer < 1) {
        return;
    }

    //COLLISION (copied from sephisword)
    gMarioState->pos[1] += 50.0f;

    //set points
    Vec3f point1;
    Vec3f point2;

    vec3f_copy(point1,origin);
    vec3f_copy(point2,hitpos);

    //project mario's position to the line segment between p1 and p2
    Vec3f AB;
    Vec3f AP;

    vec3f_diff(AB,point2,point1);
    vec3f_diff(AP,gMarioState->pos,point1);

    f32 AB_length_squared = vec3f_dot(AB,AB);

    f32 t = vec3f_dot(AP,AB) / AB_length_squared;
    if (t > 1.0f) {
        t = 1.0f;
    }
    if (t < 0.0f) {
        t = 0.0f;
    }

    Vec3f closestPoint;
    vec3f_copy(closestPoint,AB);
    vec3_mul_val(closestPoint,t);
    vec3f_sum(closestPoint,point1,closestPoint);

    // calculate distance from mario to closest point on sword
    f32 dist;
    vec3f_get_dist(closestPoint,gMarioState->pos,&dist);

    if (dist < 100.0f) {
        if ((gMarioState->action != ACT_SHOCKED) && (gMarioState->action != ACT_ELECTROCUTION) && (gMarioState->invincTimer == 0)) {
                gMarioState->hurtCounter += 4;
                drop_and_set_mario_action(gMarioState, ACT_SHOCKED, 3);
        }
    }

    gMarioState->pos[1] -= 50.0f;
}

void bhv_final_boss_hint_sign(void) {
    if (fb_bowser_phase > 0) {
        struct Object * sign = spawn_object(o,MODEL_WOODEN_SIGNPOST,bhvMessagePanel);
        sign->oBehParams2ndByte = DIALOG_FB_HINT_1+(fb_bowser_phase-1);
    }
}

static struct ObjectHitbox sCollectablePaintingHitbox = {
    /* interactType:      */ INTERACT_STAR_OR_KEY,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 80,
    /* height:            */ 50,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

extern const u8 painting_data[];
extern u8 collectable_painting_painting_rgba16[];
void bhv_collectable_painting(void) {
    switch(o->oAction) {
        case 0: //decide if i should become active
            if (gSaveBuffer.files[gCurrSaveFileNum - 1][0].paintings_unlocked & (1<<o->oBehParams2ndByte)) {
                mark_obj_for_deletion(o);
            } else {
                o->oAction = 1;
            }
            break;
        case 1: //init
            ;void * texture = segmented_to_virtual(&collectable_painting_painting_rgba16);
            void * rom_location = ((uintptr_t)painting_data)+(o->oBehParams2ndByte*2048);
            dma_read(texture,rom_location,rom_location+2048);
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_PAINTING];
            obj_set_hitbox(o, &sCollectablePaintingHitbox);
            o->oAction = 2;
            break;
        case 2: //loop
            o->oFaceAngleYaw += 0x800;
            if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                cur_obj_become_intangible();
                cur_obj_hide();
                o->oInteractStatus = INT_STATUS_NONE;
                o->oAction = 3;
            }
            break;
    }
}