enum kingJellyActions
{
    KINGJELLY_TURN,
    KINGJELLY_SHOOT,
    KINGJELLY_ATTACKED,
    KINGJELLY_DEATH
};

enum kingJellyAnims
{
    KINGJELLY_ANIM_TURN,
    KINGJELLY_ANIM_SHOOT,
    KINGJELLY_ANIM_ATTACKED
};

static struct ObjectHitbox sKingJellyHitbox = {
    /* interactType:      */ INTERACT_SHOCK,
    /* downOffset:        */ 0,-
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 90,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 90,
    /* hurtboxHeight:     */ 40,
};

static u8 sKingJellyAttackHandlers[] = {
    /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_SET_SPEED_TO_ZERO,
    /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_SET_SPEED_TO_ZERO,
    /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_KNOCKBACK,
};

void king_jellyfish_init(void)
{
    play_secondary_music(SEQ_CUSTOM_KIRBY_BOSS, 0, 127, 5);
}

void king_jellyfish_loop(void)
{   
    s16 hitcount = cur_obj_was_attacked_or_ground_pounded();
    
    switch (o->oAction)
    {
        case KINGJELLY_TURN:
            cur_obj_init_animation(KINGJELLY_ANIM_TURN);
            if (cur_obj_check_if_at_animation_end())
            {
                o->oAction = KINGJELLY_SHOOT;
            }
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x400);
            break;
        case KINGJELLY_SHOOT:
            cur_obj_init_animation(KINGJELLY_ANIM_SHOOT);
            if (o->oTimer == 6)
            {
                spawn_object(o, MODEL_JELLYS, bhvJelly);                
            }

            if (cur_obj_check_if_at_animation_end())
            {
                o->oAction = KINGJELLY_TURN;
            }
            break;
        case KINGJELLY_ATTACKED:
            cur_obj_init_animation(KINGJELLY_ANIM_ATTACKED);
            if (hitcount < 3)
            {
                o->oAction = KINGJELLY_TURN;
            } else if (hitcount >= 3)
            {
                o->oAction = KINGJELLY_DEATH;
            }
            break;
        case KINGJELLY_DEATH:
            obj_mark_for_deletion(o);
            cur_obj_init_animation(KINGJELLY_ANIM_ATTACKED);
            cur_obj_play_sound_2(SOUND_OBJ_ENEMY_DEFEAT_SHRINK);
            if (approach_f32_ptr(&o->header.gfx.scale[0], 1.0f, 0.1f)) {
                spawn_default_star(0.0f, 100.0f, 0.0f);
            }
            cur_obj_scale(o->header.gfx.scale[0]);
            break;
    }
    obj_handle_attacks(&sKingJellyHitbox, o->oAction, sKingJellyAttackHandlers);
    obj_update_standard_actions(1.0f);
}

void king_jellyfish_goo_switch(void)
{   
    switch (o->oAction)
    {
        case 0:
            
            break;
    }
}

void king_jellyfish_shock_throw(void)
{
    o->oForwardVel = 0.0f;
    cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x400);
    cur_obj_move_xz_using_fvel_and_yaw();
}