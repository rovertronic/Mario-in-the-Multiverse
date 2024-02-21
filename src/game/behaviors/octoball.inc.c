
static struct ObjectHitbox sOctoballHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 3,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 65,
    /* height:            */ 113,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

void bhv_octoball_init(void) {
    o->oGravity = 2.5f;
    o->oFriction = 0.8f;
    o->oBuoyancy = 1.3f;
    o->oFloatF4 = 0.0f;
}

static void octoball_spawn_coin(void) {
    if (!((o->oBehParams >> 8) & 0x01)) {
        obj_spawn_yellow_coins(o, 3);
        o->oBehParams = 0x100;
        set_object_respawn_info_bits(o, 1);
    }
}

static void try_create_octoball_respawner(void) {
    if(GET_BPARAM1(o->oBehParams) != 3) {
        create_respawner(MODEL_OCTOBALL, bhvOctoball, 3000);
    }
}

static void octoball_act_explode(void) {
    if (o->oTimer < 5) {
        cur_obj_scale(1.0 + (f32) o->oTimer / 5.0);
    } else {
        struct Object *explosion = spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
        explosion->oGraphYOffset += 100.0f;

        octoball_spawn_coin();
        try_create_octoball_respawner();

        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

static s32 octoball_attack_collided_from_other_object() {
    if (o->numCollidedObjs != 0) {
        struct Object *other = o->collidedObjs[0];
        if(other == gMarioObject){
            o->oInteractStatus |= INT_STATUS_TOUCHED_MARIO;
        } else if (obj_has_behavior(other, bhvOctoball)) {
            return FALSE;
        }
        //other->oInteractStatus |= INT_STATUS_TOUCHED_MARIO | INT_STATUS_WAS_ATTACKED | INT_STATUS_INTERACTED;
        return TRUE;
    }

    return FALSE;
}

static void octoball_check_interactions(void) {
    obj_set_hitbox(o, &sOctoballHitbox);

    if (octoball_attack_collided_from_other_object()) {
        if(o->oInteractStatus & INT_STATUS_TOUCHED_MARIO || o->oInteractStatus & INT_STATUS_WAS_ATTACKED){
            o->oAction = BOBOMB_ACT_EXPLODE;
        }
    }
}

static void octoball_act_patrol(void) {
    s16 collisionFlags;

    o->oForwardVel = 8.0f;
    o->oFloatF4 = 0.4f;
    collisionFlags = object_step_without_floor_orient();

    if ((obj_return_home_if_safe(o, o->oHomeX, o->oHomeY, o->oHomeZ, 400) == TRUE)
        && (obj_check_if_facing_toward_angle(o->oMoveAngleYaw, o->oAngleToMario, 0x2000) == TRUE)) {
        o->oBobombFuseLit = 1;
        o->oAction = BOBOMB_ACT_CHASE_MARIO;
    }

    obj_check_floor_death(collisionFlags, o->oFloor);
}

static void octoball_act_chase_mario(void) {
    s16 animFrame = ++o->header.gfx.animInfo.animFrame; 
    s16 collisionFlags;

    o->oForwardVel = 30.0f;
    o->oFloatF4 = 1.2f;
    collisionFlags = object_step_without_floor_orient();

    if (animFrame == 5 || animFrame == 16) {
        cur_obj_play_sound_2(SOUND_OBJ_BOBOMB_WALK);
    }

    if(o->oTimer % 10 == 0) {
        spawn_object(o, MODEL_YELLOW_COIN, bhvYellowCoin);
    }

    obj_turn_toward_object(o, gMarioObject, 16, 0x800);
    obj_check_floor_death(collisionFlags, o->oFloor);
}

static void octoball_free_loop(void) {

    // = initial_value + ((coss((speed * factor) * timer)) * (max_value_modifier * factor))
    // initial_value = 1.0f
    // factor = 0.4 in patrol so very little movement, 1.2 in chase so bigger movement
    // max_value_modifier = if 0.2f, so max can be 1.2f and min 0.8f
    o->header.gfx.scale[0] = 1.0f + (coss((3000 * o->oFloatF4) * o->oTimer) * (0.12f * o->oFloatF4));
    o->header.gfx.scale[1] = 1.0f + (coss((2500 * o->oFloatF4) * o->oTimer) * (0.23f * o->oFloatF4));
    o->header.gfx.scale[2] = 1.0f + (coss((1000 * o->oFloatF4) * o->oTimer) * (0.08f * o->oFloatF4));

    switch (o->oAction) {
        case BOBOMB_ACT_PATROL:
            octoball_act_patrol();
            break;

        case BOBOMB_ACT_CHASE_MARIO:
            octoball_act_chase_mario();
            break;

        case BOBOMB_ACT_EXPLODE:
            octoball_act_explode();
            break;

        case OBJ_ACT_LAVA_DEATH:
            if (obj_lava_death() == TRUE) {
                try_create_octoball_respawner();
            }
            break;

        case OBJ_ACT_DEATH_PLANE_DEATH:
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            try_create_octoball_respawner();
            break;
    }

    octoball_check_interactions();

    //--E
    if (o->oShotByShotgun > 1) {
            octoball_act_explode();
        o->oShotByShotgun = 0;
    }

    if (o->oBobombFuseTimer > 150) {
        o->oAction = 3;
    }
}

void bhv_octoball_loop(void) {

    o->oFaceAnglePitch += (s16)(o->oForwardVel * (100.0f));

    if (dist_between_objects(o, gMarioObject) < 4000) {
        
        octoball_free_loop();

        if (o->oBobombFuseLit == 1) {
            cur_obj_play_sound_1(SOUND_AIR_BOBOMB_LIT_FUSE);
            o->oBobombFuseTimer++;
        }
    }
}