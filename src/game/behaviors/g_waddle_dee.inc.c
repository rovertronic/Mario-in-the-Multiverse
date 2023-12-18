static struct ObjectHitbox sWaddleDeeHitbox = {
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

static u8 sWaddleDeeAttackHandlers[] = {
    /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_SQUISHED,
    /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_KNOCKBACK,
};


void bhv_g_waddle_dee_init(void) {
    o->oGravity = 2.5f;
    o->oFriction = 0.8f;
    o->oBuoyancy = 1.3f;
    o->oHomeX = o->oPosX;
    o->oHomeZ = o->oPosZ;
}

void bhv_g_waddle_dee_loop(void) {
    if (obj_update_standard_actions(1.0f)) {
        o->oForwardVel = 5.0f;

        object_step();
        cur_obj_update_floor_and_walls();
        obj_return_home(o, o->oHomeX, o->oHomeY, o->oHomeZ, 400);

        obj_handle_attacks(&sWaddleDeeHitbox, o->oAction, &sWaddleDeeAttackHandlers);
    }
    else {
        o->oGravity = -2.5f;
    }
}

