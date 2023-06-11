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
    ABILITY_E_,
    ABILITY_F_,
    ABILITY_CUTTER,
    ABILITY_H_,
    ABILITY_I_,
    ABILITY_HM_FLY,
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

#endif