#ifndef ABILITY_H
#define ABILITY_H

void render_ability_dpad(s16 x, s16 y, u8 alpha);
void control_ability_dpad(void);
u8 using_ability(u8 ability_id);

enum ability_ids {
    ABILITY_DEFAULT,
    ABILITY_A_,
    ABILITY_B_,
    ABILITY_C_,
    ABILITY_D_,
    ABILITY_E_,
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
};

extern Gfx gfx_ability_hand[2];

#endif