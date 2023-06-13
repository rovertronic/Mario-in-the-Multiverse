Vec3f ball_Size = {100.0f,100.0f,100.0f};

Vec3f ball_Vertices[42] = {
{.0, -.100, .0},
{.43, -.85, .31}, 
{-.16, -.85, .50},
{-.28, -.45, -.85},
{-.69, -.53, -.50},
{-.59, .0, -.81}, 
{-.28, -.45, .85},
{.0, .0, .100},
{-.59, .0, .81},
{.53, .85, .0},
{.69, .53, -.50},
{.16, .85, -.50},
{-.43, .85, -.31},
{-.43, .85, .31}, 
{.0, .100, .0},
{-.26, .53, .81}, 
{.28, .45, .85},
{.16, .85, .50},
{-.72, .45, -.53},
{-.26, .53, -.81},
{-.95, .0, .31},
{-.72, .45, .53}, 
{-.85, .53, .0},
{.95, .0, .31}, 
{.89, .45, .0},
{.69, .53, .50},
{.59, .0, -.81},
{.0, .0, -.100},
{.28, .45, -.85},
{-.95, .0, -.31},
{.26, -.53, .81},
{.72, -.45, .53},
{.59, .0, .81},
{.85, -.53, .0},
{.72, -.45, -.53},
{.95, .0, -.31},
{.43, -.85, -.31},
{-.16, -.85, -.50},
{.26, -.53, -.81},
{-.53, -.85, .0}, 
{-.69, -.53, .50},
{-.89, -.45, .0}, 
};

struct MeshInfo Ball_Mesh = {
    ball_Vertices,
    NULL,
    NULL,
    NULL,
    42, // Number of vertices
    0,
    0,
    0
};

void bhv_marble_init(void) {
    struct RigidBody *body = allocate_rigid_body_from_object(o, &Ball_Mesh, 1.0f, ball_Size, FALSE);
}

void bhv_marble_loop(void) {
    set_mario_action(gMarioState,ACT_MARBLE,0);
    
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

    if ( vec3_mag(o->rigidBody->linearVel) < 20.0f) {
        //rigid_body_add_force(o->rigidBody, push_position, move_force, TRUE);
    }

    o->rigidBody->asleep = FALSE;
    vec3f_add(o->rigidBody->linearVel, move_force);

    vec3f_copy(gMarioState->pos,&o->oPosVec);
    gMarioState->vel[1] = 0;
}