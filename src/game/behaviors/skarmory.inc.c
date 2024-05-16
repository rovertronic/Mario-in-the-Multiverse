
#define SKARMORY_ACT_VERTICAL_FLY 0
#define SKARMORY_ACT_HORIZONTAL_FLY 2
#define SKARMORY_ACT_CIRCULAR_FLY 1
#define SKARMORY_ACT_DIE 3

static struct ObjectHitbox sSkarmoryHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 200,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 200,
    /* hurtboxHeight:     */ 200,
};

void bhv_skarmory_init(void){
    o->oHomeY = o->oPosY;
    o->oHomeX = o->oPosX;
    o->oHomeZ = o->oPosZ;
    o->oAction = o->oBehParams2ndByte;
    obj_set_hitbox(o, &sSkarmoryHitbox);

    if (o->oBehParams2ndByte == 0){
        cur_obj_init_animation(0);
    } else {
        cur_obj_init_animation(1);
    }
}

void bhv_skarmory_loop(void){

     f32 floorY;

    cur_obj_scale(2.0f);

    if (obj_update_standard_actions(1.0f)) {
        switch (o->oAction) {
            
            case SKARMORY_ACT_VERTICAL_FLY:
                o->oPosY = o->oHomeY + (sins(o->oTimer * 200) * 1024.0f);
                break;
            
            case SKARMORY_ACT_CIRCULAR_FLY:
                o->oPosX = o->oHomeX + (sins(o->oTimer * 200) * 1024.0f);
                o->oPosZ = o->oHomeZ + (coss(o->oTimer * 200) * 1024.0f);
                o->oFaceAngleYaw = 16384.0f + (o->oTimer * 200);
                break;
            
            case SKARMORY_ACT_DIE:
                o->oVelY = -40.0f;
                cur_obj_init_animation(2);
                floorY = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
                if (floorY + 50 > o->oPosY){
                    spawn_mist_particles();
                    o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                }
                
                break;

        }

    }

    if((o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED) || o->oShotByShotgun == 2){
        o->oAction = SKARMORY_ACT_DIE;
    }

    o->oInteractStatus = INT_STATUS_NONE;
    o->oShotByShotgun = 0;

    object_step();
    
}

void bhv_skarmory_star_spawner_init(void){

}

extern void spawn_no_exit_star(f32, f32, f32);

void bhv_skarmory_star_spawner_loop(void){
    if (count_objects_with_behavior(bhvSkarmory) == 0){
        spawn_no_exit_star(o->oPosX, o->oPosY, o->oPosZ);
        spawn_mist_particles();
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}