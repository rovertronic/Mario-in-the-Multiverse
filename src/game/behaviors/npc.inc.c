#define NPC_IDLE 0x0
#define NPC_ACT_TURN_TO_TALK 0x2
#define NPC_TALK 0x3
#define NPC_HAS_NOT_TALKED 0x0
#define NPC_HAS_TALKED 0x2

static struct ObjectHitbox sElderHitbox1 = {
    /* interactType:      */ INTERACT_TEXT,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 200,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 200,
    /* hurtboxHeight:     */ 200,
};

static struct ObjectHitbox sElderHitbox2 = {
    /* interactType:      */ INTERACT_TEXT,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 100,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 100,
    /* hurtboxHeight:     */ 100,
};


void bhv_npc_init(void) {
    o->oGravity  = 2.5f;
    o->oFriction = 0.8f;
    o->oBuoyancy = 1.3f;
    o->oInteractionSubtype = INT_SUBTYPE_NPC;
    o->header.gfx.scale[0] = 1.0f;
    o->header.gfx.scale[1] = 1.0f;
    o->header.gfx.scale[2] = 1.0f;
    o->oGraphYOffset = 0.0f;

}

void bhv_youngster_init(void) {
    o->oGravity  = 2.5f;
    o->oFriction = 0.8f;
    o->oBuoyancy = 1.3f;
    o->oInteractionSubtype = INT_SUBTYPE_NPC;
    o->header.gfx.scale[0] = 1.0f;
    o->header.gfx.scale[1] = 1.0f;
    o->header.gfx.scale[2] = 1.0f;
    o->oGraphYOffset = 0.0f;

}

void bhv_elder_init(void) {
    u8 starFlags = save_file_get_course_star_count(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(gCurrCourseNum));
    o->oGravity  = 2.5f;
    o->oFriction = 0.8f;
    o->oBuoyancy = 1.3f;
    o->oInteractionSubtype = INT_SUBTYPE_NPC;
    o->header.gfx.scale[0] = 1.0f;
    o->header.gfx.scale[1] = 1.0f;
    o->header.gfx.scale[2] = 1.0f;
    o->oGraphYOffset = 0.0f;
    obj_set_hitbox(o, &sElderHitbox1);
    if (starFlags >= 7){
        o->oPosX = 3365.0f;
        o->oPosY = 0.0f;
        o->oPosZ = -5175.0f;
        obj_set_hitbox(o, &sElderHitbox2);
    }

}


void bhv_npc_loop(void) {
    u8 starFlags = save_file_get_course_star_count(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(gCurrCourseNum));
    if (obj_has_behavior(o, bhvElder)){
        obj_set_hitbox(o, &sElderHitbox1);
        if (starFlags >= 7){
            o->oPosX = 3365.0f;
            o->oPosY = 0.0f;
            o->oPosZ = -5175.0f;
            obj_set_hitbox(o, &sElderHitbox2);
        }
    }

    npc_actions();

    o->oInteractStatus = 0;
}

void npc_actions(void) {
    switch (o->oAction) {
        case NPC_IDLE:
            npc_idle();
            break;

        case NPC_ACT_TURN_TO_TALK:
            npc_act_turn_to_talk();
            break;

        case NPC_TALK:
            npc_talk();
            break;
    }

    set_object_visibility(o, 3000);
}

void npc_act_turn_to_talk(void) {

    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x1000);
    if ((s16) o->oMoveAngleYaw == (s16) o->oAngleToMario)
        o->oAction = NPC_TALK;

    ///cur_obj_play_sound_2(SOUND_PEACH_DEAR_MARIO);
}

void npc_talk(void) {
    u8 starFlags = save_file_get_course_star_count(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(gCurrCourseNum));
    if (set_mario_npc_dialog(MARIO_DIALOG_LOOK_FRONT) == MARIO_DIALOG_STATUS_SPEAK) {
        o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
            if (obj_has_behavior(o, bhvElder) && starFlags >= 7){
                if (cutscene_object_with_dialog(CUTSCENE_DIALOG, o, DIALOG_ELDER_BELL_TOWER_2)) {
                    set_mario_npc_dialog(MARIO_DIALOG_STOP);

                    o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                    o->oNPCHasTalkedToMario = NPC_HAS_TALKED;
                    o->oInteractStatus = 0;
                    o->oAction = NPC_IDLE;
                }
            } else {
                if (cutscene_object_with_dialog(CUTSCENE_DIALOG, o, o->oBehParams2ndByte)) {
                    set_mario_npc_dialog(MARIO_DIALOG_STOP);

                    o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                    o->oNPCHasTalkedToMario = NPC_HAS_TALKED;
                    o->oInteractStatus = 0;
                    o->oAction = NPC_IDLE;
                    }
            }


        
    }
}

void npc_idle(void) {
    s16 animFrame = o->header.gfx.animInfo.animFrame;

    if (o->oDistanceToMario < 1000.0f)
        o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x140);

    if (o->oInteractStatus == INT_STATUS_INTERACTED)
        o->oAction = NPC_ACT_TURN_TO_TALK;
}