#ifndef ABILITY_H
#define ABILITY_H

void render_ability_dpad(s16 x, s16 y, u8 alpha);
void control_ability_dpad(void);
void render_ability_icon(u16 x, u16 y, u8 alpha, u8 index);
u8 using_ability(u8 ability_id);
u8* ability_string(u8 ability_id);

Gfx *geo_ability_material(s32 callContext, struct GraphNode *node, void *context);

enum ability_ids {
    ABILITY_DEFAULT,
    ABILITY_A_,
    ABILITY_B_,
    ABILITY_C_,
    ABILITY_D_,
    ABILITY_E_SHOTGUN,
    ABILITY_F_,
    ABILITY_G_,
    ABILITY_H_,
    ABILITY_I_,
    ABILITY_J_,
    ABILITY_K_,
    ABILITY_L_,
    ABILITY_M_,
    ABILITY_N_,
    ABILITY_ESTEEMED_MORTAL,
};

struct ability {
    Gfx * hand;
    Gfx * hat;
    u8 model_id;
    u8 * string;
};

extern Gfx gfx_ability_hand[2];
extern Gfx gfx_ability_hat[2];
extern u8 ability_slot[4];



//--E

#define E_SGF_LEFT_HAND        (1 << 0)
#define E_SGF_AIM_MODE         (1 << 1)
#define E_SGF_AIM_FIRE         (1 << 2)
#define E_SGF_AIR_SHOT_USED      (1 << 3)

extern struct AnimInfo gE_UpperAnimInfo;
extern u8   gE_UpperAnimType;
extern s16  gE_UpperAnimFrame;
extern u16 *gE_UpperAnimAttribute;
extern s16 *gE_UpperAnimData;

extern s16 gE_UpperAimPitch;
extern s16 gE_UpperAimYaw;

extern s8 gE_ShotgunTimer;
extern u8 gE_ShotgunFlags;



#endif