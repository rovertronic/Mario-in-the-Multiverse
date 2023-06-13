Vec3f ball_Size = {100.0f,100.0f,100.0f};

Vec3f ball_Vertices[62] = {
{.0, -.95, -.31}, 
{.0, -.81, -.59}, 
{.35, -.81, -.48}, 
{.18, -.95, -.25}, 
{.56, -.31, -.77}, 
{.48, -.59, -.65},  
{.59, .0, -.81}, 
{.95, .0, -.31}, 
{.90, -.31, -.29},   
{.77, -.59, -.25}, 
{.56, -.81, -.18}, 
{.29, -.95, -.10},  
{.56, -.81, .18}, 
{.29, -.95, .10},   
{.90, -.31, .29}, 
{.77, -.59, .25},   
{.48, -.59, .65}, 
{.35, -.81, .48},  
{.95, .0, .31}, 
{.59, .0, .81}, 
{.56, -.31, .77}, 
{.18, -.95, .25},  
{.0, -.81, .59}, 
{.0, -.95, .31}, 
{.0, -.31, .95}, 
{.0, -.59, .81}, 
{-.48, -.59, .65}, 
{-.35, -.81, .48}, 
{0, -.31, .95},
{0, 0, 1.00},
{-.59, .0, .81},
{-.56, -.31, .77},   
{-.90, -.31, .29}, 
{-.77, -.59, .25}, 
{-.18, -.95, .25},  
{-.56, -.81, .18}, 
{-.29, -.95, .10}, 
{-.95, 0, .31},
{-.95, 0, -.31},
{-.90, -.31, -.29},
{-.77, -.59, -.25},
{-.56, -.81, -.18},
{-.29, -.95, -.10},
{-.35, -.81, -.48},
{-.18, -.95, -.25},
{-.48, -.59, -.65},
{.0, -.59, -.81},
{.0, -.81, -.59},
{-.56, -.31, -.77},
{-.59, 0, -.81},
{.0, 0, -1.00},
{.0, -.31, -.95},
{.59, .81, 0},
{.95, .31, 0},
{.0, .31, .95},
{.0, .81, .59},
{-.95, .31, 0},
{-.59, .81, 0},
{.0, .81, -.59},
{.0, .31, -.95},
{0.0f,-0.999f,0.0f},
{0.0f,0.999f,0.0f},
};

struct MeshInfo Ball_Mesh = {
    ball_Vertices,
    NULL,
    NULL,
    NULL,
    62, // Number of vertices
    0,
    0,
    0
};

static struct ObjectHitbox sMarbleHitbox = {
    /* interactType:      */ INTERACT_NONE,
    /* downOffset:        */ 50,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 60,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 100,
    /* hurtboxHeight:     */ 100,
};

void bhv_marble_init(void) {
    struct RigidBody *body = allocate_rigid_body_from_object(o, &Ball_Mesh, 1.0f, ball_Size, FALSE);
    vec3f_copy(body->linearVel,gMarioState->vel);
}

u8 underwater = FALSE;
void bhv_marble_loop(void) {    
    Vec3f move_force = {
        (sins(gMarioState->intendedYaw) * gMarioState->intendedMag)/10.0f,
        0.0f,
        (coss(gMarioState->intendedYaw) * gMarioState->intendedMag)/10.0f,
    };
    Vec3f push_position = {
        o->oPosX + (sins(gMarioState->intendedYaw+0x8000) * 50.0f),
        0.0f,
        o->oPosZ + (coss(gMarioState->intendedYaw+0x8000) * 50.0f),
    };

    //if ( vec3_mag(o->rigidBody->linearVel) < 20.0f) {
        //rigid_body_add_force(o->rigidBody, push_position, move_force, TRUE);
    //}

    o->rigidBody->asleep = FALSE;
    vec3f_add(o->rigidBody->linearVel, move_force);

    struct Surface *floor;
    f32 water_level = find_water_level_and_floor(o->oPosX,o->oPosY,o->oPosZ, &floor);

    if (water_level > o->oPosY) {
        o->rigidBody->linearVel[1] += 5.0f;//buoyancy
        vec3_mul_val(o->rigidBody->linearVel,0.94f);//drag
        vec3_mul_val(o->rigidBody->angularVel,0.94f);
        if (!underwater) {
            underwater = TRUE;
            if (o->rigidBody->linearVel[1] < -4.0f) {
                cur_obj_play_sound_2(SOUND_ACTION_WATER_PLUNGE);
            }
        }
    } else {
        underwater = FALSE;
    }

    //break upon contact with lava / quicksand
    f32 fheight = find_floor(o->oPosX,o->oPosY,o->oPosZ, &floor);
    if (floor && fheight+120.0f > o->oPosY && (floor->type == SURFACE_BURNING || floor->type == SURFACE_INSTANT_QUICKSAND || floor->type == SURFACE_DEATH_PLANE)) {
        gMarioState->abilityId = ABILITY_DEFAULT;
    }


    vec3f_copy(&gMarioObject->oPosVec,&o->oPosVec);
    vec3f_copy(gMarioState->pos,&o->oPosVec);
    vec3f_copy(gMarioState->vel,&o->rigidBody->linearVel);

    obj_set_hitbox(o, &sMarbleHitbox);
    o->oInteractStatus = 0;
    o->oIntangibleTimer = 0;

    for (int i = 0; i < o->numCollidedObjs; i++) {
        struct Object *other = o->collidedObjs[i];
        if (other != gMarioObject) {
            cur_obj_play_sound_2(SOUND_GENERAL_EXPLOSION7);
            attack_object(other, 2);
        }
    }
}