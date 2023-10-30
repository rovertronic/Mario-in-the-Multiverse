#define SENTRET_ACT_ROAM 0
#define SENTRET_ACT_CHASE 1
#define SENTRET_ACT_BIG_JUMP 2

static struct ObjectHitbox sSentretHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 0,
    /* numLootCoins:      */ 1,
    /* radius:            */ 100,
    /* height:            */ 300,
    /* hurtboxRadius:     */ 100,
    /* hurtboxHeight:     */ 300,
};

static u8 sSentretAttackHandlers[] = {
        /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_KNOCKBACK,
        /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_KNOCKBACK,
        /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_SQUISHED,
        /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_SQUISHED,
        /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_KNOCKBACK,
        /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_KNOCKBACK,
};
void bhv_sentret_init(void){
    o->oGravity = -2.0f;
    o->oAction = SENTRET_ACT_ROAM;
    o->header.gfx.scale[0] = 0.5f;
    o->header.gfx.scale[1] = 0.5f;
    o->header.gfx.scale[2] = 0.5f;
    obj_set_hitbox(o, &sSentretHitbox);
    cur_obj_init_animation(0);
}

s16 get_home_yaw(void){
    s16 ang;

    ang = atan2s(o->oHomeZ - o->oPosZ, o->oHomeX - o->oPosX);
    return ang;
}

static void sentret_small_jump(void){
    f32 floorY;
    floorY = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
    if (o->oPosY <= floorY){
        o->oVelY = 24.0f;
    }
}

static void sentret_roam(void){
    o->oForwardVel = 5.0f;

        if (cur_obj_lateral_dist_to_home() >= 1000.0f){
            o->oSentretTargetYaw = get_home_yaw();
            o->oSentretWalkTimer = random_linear_offset(30, 60);
        } else {
            if (o->oSentretWalkTimer != 0) {
                        o->oSentretWalkTimer--;
                    } else {
                        o->oSentretTargetYaw = obj_random_fixed_turn(0x2000);
                        o->oSentretWalkTimer = random_linear_offset(100, 100);
                    }
        }

    cur_obj_rotate_yaw_toward(o->oSentretTargetYaw, 0x200);
    sentret_small_jump();
    cur_obj_move_standard(-78);
}

void bhv_sentret_loop(void){
    
    switch (o->oAction){
        case SENTRET_ACT_ROAM:
            sentret_roam();
            break;
    }

    obj_handle_attacks(&sSentretHitbox, o->oAction, sSentretAttackHandlers);
    if (o->oShotByShotgun == 2) {
        obj_mark_for_deletion(o);
    }
    o->oShotByShotgun = 0;
    o->oInteractStatus = INT_STATUS_NONE;
}

