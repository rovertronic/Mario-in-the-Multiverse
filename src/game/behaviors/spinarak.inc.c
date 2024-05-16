#define SPINARAK_ACT_IDLE 0
#define SPINARAK_ACT_ALERT 1
#define SPINARAK_ACT_CHASE 2
#define SPINARAK_ACT_RETURN 3


struct ObjectHitbox sSpinarakHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 1,
    /* numLootCoins:      */ 3,
    /* radius:            */ 90,
    /* height:            */ 80,
    /* hurtboxRadius:     */ 80,
    /* hurtboxHeight:     */ 70,
};

void bhv_spinarak_init(void){
    o->oAction = SPINARAK_ACT_IDLE;
    obj_set_hitbox(o, &sSpinarakHitbox);
    o->header.gfx.scale[0] = 0.75f;
    o->header.gfx.scale[1] = 0.75f;
    o->header.gfx.scale[2] = 0.75f;
}

void bhv_spinarak_loop(void){

    static struct Surface *sObjFloor;
    f32 floorY;

    switch (o->oAction){
        case SPINARAK_ACT_IDLE:
            o->oMoveAngleRoll += 0x50;

            if (o->oDistanceToMario <= 1500 && o->oTimer > 30) {
                o->oAction = SPINARAK_ACT_ALERT;
                o->oTimer = 0;
            }
            break;
        case SPINARAK_ACT_ALERT:
            obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_ROLL_INDEX, 0x400);
            if (o->oDistanceToMario > 1500) {
                o->oAction = SPINARAK_ACT_IDLE;
                o->oTimer = 0;
            }

            if (o->oTimer > 60){
                o->oTimer = 0;
                o->oAction = SPINARAK_ACT_CHASE;
            }
            break;
        case SPINARAK_ACT_CHASE:
            o->oVelX = sins(o->oMoveAngleRoll) * 50.0f;
            o->oVelY = coss(o->oMoveAngleRoll) * -50.0f;

            if ((o->oDistanceToMario < 90.0f)&&(gMarioState->action == ACT_SQUID)) {
                cur_obj_play_sound_2(SOUND_MARIO_OOOF);
                obj_set_model(gMarioObject, MODEL_MARIO);
                set_mario_action(gMarioState, ACT_IDLE, 0);
            }
            if (o->oTimer > 15){
                o->oAction = SPINARAK_ACT_RETURN;
                o->oTimer = 0;
            }
            break;
        case SPINARAK_ACT_RETURN:
            if (o->oTimer < 30){
                o->oVelX = 0.0f;
                o->oVelY = 0.0f;
            } else {
                o->oVelX = sins(o->oMoveAngleRoll) * -12.5f;
                o->oVelY = coss(o->oMoveAngleRoll) * 12.5f;
            }

            if (o->oTimer > 90){
                o->oAction = SPINARAK_ACT_IDLE;
                o->oTimer = 0;
                o->oVelX = 0.0f;
                o->oVelY = 0.0f;
                o->oPosX = o->oHomeX;
                o->oPosY = o->oHomeY;
                o->oPosZ = o->oHomeZ;
            }
            break;

    }

    if((o->oInteractStatus & INT_STATUS_INTERACTED && o->oInteractStatus & INT_STATUS_WAS_ATTACKED) || o->oShotByShotgun == 2){
        spawn_mist_particles();
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }

    o->oInteractStatus = INT_STATUS_NONE;
    o->oShotByShotgun = 0;
    o->oPosX += o->oVelX;
    o->oPosY += o->oVelY;

}