void bhv_dash_booster_particle(void) {
    if (o->oTimer%2 == 1) {
        o->oAnimState ++;
    }
    if (o->oAnimState >= 4) {
        mark_obj_for_deletion(o);
    }
}

void bhv_m_boss_elevator(void) {
    switch(o->oBehParams2ndByte) {
        case 0:
            switch(o->oAction) {
                case 0:
                    if ((o->oDistanceToMario < 700.0f)&&(save_file_check_ability_unlocked(ABILITY_DASH_BOOSTER))) {
                        cur_obj_play_sound_2(SOUND_GENERAL_STAR_DOOR_OPEN);
                        o->oAction = 1;
                    }
                    break;
                case 1:
                    if (o->oTimer < 70) {
                        o->oPosZ += 10.0f;
                    }
                    break;
            }
            break;
        case 1:
            switch(o->oAction) {
                case 0:
                    if (!cur_obj_nearest_object_with_behavior(bhvM_Jelly)) {
                        cur_obj_play_sound_2(SOUND_GENERAL_STAR_DOOR_OPEN);
                        o->oAction = 1;
                    }
                    break;
                case 1:
                    if (o->oTimer < 70) {
                        o->oPosZ += 10.0f;
                    }
                    break;
            }
            break;
    }
}

struct ObjectHitbox sClassCHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 15,
    /* numLootCoins:      */ 0,
    /* radius:            */ 150,
    /* height:            */ 400,
    /* hurtboxRadius:     */ 140,
    /* hurtboxHeight:     */ 300,
};

extern void cur_obj_move_standard_classc(void);

void bhv_m_classc(void) {
    o->oAnimState = 0;

    switch(o->oAction) {
        case 0: // Wait for Mario to come
            if (lateral_dist_between_objects(gMarioObject,o) < 1300.0f) {
                o->prevObj = spawn_object(o, MODEL_ZAP, bhvKingJellyZap);
                obj_scale(o->prevObj,4.0f);
                o->oAction = 1;
                obj_set_hitbox(o, &sClassCHitbox);
                o->oGravity = -4.0f;
                o->oBounciness = -0.3f;
                o->oWallHitboxRadius = 200.0f;
                magic_mirror_disable = TRUE;
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_CUSTOM_KIRBY_BOSS), 0);
                o->oHealth = 15;
                esa_hp = 15;
                esa_mhp = 15;
                esa_str = "Class C Guardian";
            }
            break;
        case 1: // Deactivate and attackable
            o->oAnimState = 1;
            cur_obj_update_floor_and_walls();
            cur_obj_move_standard_classc();

            o->oVelX *= .9f;
            o->oVelZ *= .9f;

            if (o->oHealth < 1) {
                o->oAction = 2;
            }

            if (o->oTimer > 85) {
                if (o->oTimer % 2 == 0) {
                    o->oAnimState = 0;
                }
            }

            if (o->oTimer > 100) {
                o->oAction = 3;
                o->oInteractStatus = INTERACT_DAMAGE;
                o->prevObj->oAnimState = 1;
                // Attacl
            }

            if ((o->oInteractStatus & INT_STATUS_WAS_ATTACKED)||(o->oShotByShotgun > 1)) {
                o->oAnimState = 2;
                o->oHealth --;
                o->oIntangibleTimer = 15;
                esa_hp = o->oHealth;

                if (esa_hp < 0) {
                    esa_hp = 0;
                }
            }
            break;
        case 2: // Die
            o->oIntangibleTimer = 0;
            o->oInteractType = INTERACT_NONE;
            if (o->oTimer % 2 == 0) {
                struct Object * bam = spawn_object(o,MODEL_EXPLOSION,bhvExplosionVisual);
                bam->oPosX += (random_float() * 400.0f)-200.0f;
                bam->oPosY += (random_float() * 400.0f)-200.0f;
                bam->oPosZ += (random_float() * 400.0f)-200.0f;
            }
            if (o->oTimer == 60) {
                struct Object * abilityspawn = spawn_object(o,MODEL_ABILITY,bhvAbilityUnlock);
                vec3f_set(&abilityspawn->oPosVec,-1900, 1700, -13700);
                abilityspawn->oBehParams2ndByte = ABILITY_DASH_BOOSTER;
                magic_mirror_disable = FALSE;
                esa_mhp = -1;
                stop_background_music(SEQUENCE_ARGS(4, SEQ_CUSTOM_KIRBY_BOSS));
                mark_obj_for_deletion(o);
            }
            break;
        case 3:
            vec3f_copy(&o->prevObj->oPosVec,&o->oPosVec);
            o->prevObj->oPosY += 200.0f;

            o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw,o->oAngleToMario,10);
            o->oFaceAngleYaw = o->oMoveAngleYaw;

            if (o->oTimer % 30 == 29) {
                cur_obj_play_sound_2(SOUND_OBJ2_EYEROK_SOUND_LONG);
                o->oFaceAnglePitch = obj_turn_pitch_toward_mario(0.0f, 0x7000);
                struct Object * bullet = spawn_object(o,MODEL_BOWLING_BALL,bhvHeliBalls);
                bullet->oMoveAnglePitch = o->oFaceAnglePitch;
                bullet->oMoveAngleYaw = o->oAngleToMario;
                o->oFaceAnglePitch = 0;
            }
            o->oGravity = 0.0f;
            o->oPosY = approach_f32_asymptotic(o->oPosY,gMarioState->pos[1] + 400.0f + sins(o->oTimer*0x200)*200.0f ,0.1f);

            o->oVelX += sins(o->oAngleToMario) * 2.0f;
            o->oVelZ += coss(o->oAngleToMario) * 2.0f;

            if (o->oTimer > 200) {
                o->oAction = 1;
                o->oGravity = -4.0f;
                o->oInteractStatus = INTERACT_BOUNCE_TOP;
                o->prevObj->oAnimState = 0;
            }

            cur_obj_update_floor_and_walls();
            cur_obj_move_standard_classc();
            break;
    }

    if (o->oMoveFlags & OBJ_MOVE_LANDED) {
        cur_obj_play_sound_2(SOUND_OBJ_BULLY_METAL);
    }

    o->oShotByShotgun = 0;
    o->oInteractStatus = INTERACT_NONE;

    if ((gMarioState->action == ACT_DEATH_EXIT_LAND)&&(o->oAction!=0)) {
        //reset state upon death
        o->oAction = 0;
        vec3f_copy(&o->oPosVec,&o->oHomeVec);
        mark_obj_for_deletion(o->prevObj);
    }
}

void bhv_m_gate(void) {
    //lazy programming lol
    if (o->oBehParams2ndByte == 1) {
        struct Object *rocketbutton = cur_obj_nearest_object_with_behavior(bhvRocketButton);
        if ((rocketbutton) && (rocketbutton->oAction > 0)) {
            play_puzzle_jingle();
            mark_obj_for_deletion(o);
        }
        return;
    }

    struct Object * class_c_guardian = cur_obj_nearest_object_with_behavior(bhvM_ClassC);

    if ((class_c_guardian)&&class_c_guardian->oAction>0) {
        //shut
        o->oPosY = approach_f32_asymptotic(o->oPosY,o->oHomeY,0.1f);
    } else {
        //open
        o->oPosY = approach_f32_asymptotic(o->oPosY,o->oHomeY+500.0f,0.1f);
    }
}