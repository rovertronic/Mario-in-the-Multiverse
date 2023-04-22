#ifdef ABILITY_H
#define ABILITY_H

void render_ability_dpad(u16 x, u16 y, u8 alpha);
void control_ability_dpad(void);

enum ability_ids {
    ABILITY_DEFAULT,
    ABILITY_A,
    ABILITY_B,
    ABILITY_C,
    ABILITY_D,
    ABILITY_E,
    ABILITY_F,
    ABILITY_G,
    ABILITY_H,
    ABILITY_I,
    ABILITY_J,
    ABILITY_K,
    ABILITY_L,
    ABILITY_M,
    ABILITY_N,
    ABILITY_ESTEEMED_MORTAL
};

#endif