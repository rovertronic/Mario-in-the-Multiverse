static struct ObjectHitbox sBrontoBurtHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 3,
    /* radius:            */ 80,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 70,
    /* hurtboxHeight:     */ 30,
};

static u8 sBrontoBurtAttackHandlers[] = {
    /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_KNOCKBACK,
};

void bhv_g_bronto_burt_init(void) {
    if (o->oBehParams2ndByte % 2 == 0) {
        o->oMoveAngleYaw = o->oFaceAngleYaw + 0x4000 + (0x4000 * o->oBehParams2ndByte);
    }
}

void bhv_g_bronto_burt_loop(void) {
    if (obj_update_standard_actions(1.0f)) {
        if (o->oBehParams2ndByte % 2 == 0) {
            o->oForwardVel = 20.0f*coss(o->oTimer * 0x222);
            cur_obj_move_xz_using_fvel_and_yaw();
            cur_obj_update_floor_and_walls();
        }
        else {
            o->oPosY = o->oHomeY + 50.0f*coss(o->oTimer * 0x222);
        }

        obj_handle_attacks(&sBrontoBurtHitbox, o->oAction, sBrontoBurtAttackHandlers);
    }
    else {
        o->oGravity = -2.5f;
    }
}

