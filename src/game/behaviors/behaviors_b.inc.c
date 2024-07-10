#include "src/game/interaction.h"

    struct ObjectHitbox sConcreteBlockHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */   0,
    /* damageOrCoinValue: */   0,
    /* health:            */   1,
    /* numLootCoins:      */   0,
    /* radius:            */ 150,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 150,
    /* hurtboxHeight:     */ 200,
    };

void bhv_concrete_block_init(void){
    f32 Scale = GET_BPARAM2(o->oBehParams);; 
    sConcreteBlockHitbox.radius = 150 + (Scale/100.0);
    sConcreteBlockHitbox.height = 200 + (Scale/100.0) - 3;
    sConcreteBlockHitbox.hurtboxHeight = 200 + (Scale/100.0) - 3;
    cur_obj_scale(1.0 + Scale/100.0);
    obj_set_hitbox(o, &sConcreteBlockHitbox);
    if (GET_BPARAM1(o->oBehParams) >= 3){
        o->oHealth = 2;
    } else {
    o->oHealth = GET_BPARAM1(o->oBehParams);
    }
}

void bhv_concrete_block_loop(void) {
    if (o->oHealth == 2){
        cur_obj_set_model(MODEL_CONCRETE_BLOCK);
    }else if (o->oHealth == 1){
        cur_obj_set_model(MODEL_CONCRETE_BLOCK_CRACK1);
    }else if (o->oHealth == 0){
        cur_obj_set_model(MODEL_CONCRETE_BLOCK_CRACK2);
    }
    if (using_ability(ABILITY_BIG_DADDY)){
        if (gMarioState->action == ACT_PUNCHING || gMarioState->action == ACT_MOVE_PUNCHING || gMarioState->action == ACT_JUMP_KICK){
            if ((o->oInteractStatus & INT_STATUS_INTERACTED) && (o->oInteractStatus & INT_STATUS_WAS_ATTACKED)) {
                if (o->oTimer >= 10){
                    o->oTimer = 0;
                    if (o->oHealth > 0){
                        o->oHealth -= 1;
                    } else {
                        obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
                        create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
                    }
                }
            }
        }
    }
    if (o->oShotByShotgun > 0) {
        o->oShotByShotgun = 0;

        if (o->oHealth > 0){
            o->oHealth -= 1;
        } else {
            obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
            create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
        }
    }
    o->oInteractStatus = INT_STATUS_NONE;
}

    


