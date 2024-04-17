#ifndef ABILITY_H
#define ABILITY_H

void render_hint_ui(u8 hud_alpha);
void render_ability_dpad(s16 x, s16 y, u8 alpha);
void control_ability_dpad(void);
void change_ability(s8 picked_ability);
void render_ability_icon(u16 x, u16 y, u8 alpha, u8 index);
void load_ability_texture(u8 index);
u8 using_ability(u8 ability_id);
u8* ability_string(u8 ability_id);
u16 ability_is_cooling_down(u8 ability_id);
u8 cool_down_ability(u8 ability_id);
u8 ability_ready(u8 ability_id);
s32 check_if_swap_ability_allowed(void);

extern Vec3f mario_hand_position;
extern s16 check_water_height;
extern Bool8 bd_submerged;

Gfx *geo_ability_material(s32 callContext, struct GraphNode *node, void *context);

enum ability_ids {
    ABILITY_DEFAULT,
    ABILITY_CUTTER,
    ABILITY_BUBBLE_HAT,
    ABILITY_SQUID,
    ABILITY_SHOCK_ROCKET,
    ABILITY_PHASEWALK,
    ABILITY_BIG_DADDY,
    ABILITY_KNIGHT,
    ABILITY_CHRONOS,
    ABILITY_E_SHOTGUN,
    ABILITY_GADGET_WATCH,
    ABILITY_HM_FLY,
    ABILITY_AKU,
    ABILITY_ESTEEMED_MORTAL,
    ABILITY_MARBLE,
    ABILITY_DASH_BOOSTER,
    ABILITY_UTIL_COMPASS,
    ABILITY_UTIL_MILK,
    ABILITY_UTIL_MIRROR,
    ABILITY_NONE,
};

struct ability {
    Gfx * hand;
    Gfx * hat;
    u16 model_id;
    u8 * string;
};

extern Gfx gfx_ability_hand[2];
extern Gfx gfx_ability_hat[3];
extern u8 ability_slot[4];


//--E

#define E_SGF_LEFT_HAND        (1 << 0)
#define E_SGF_AIM_MODE         (1 << 1)
#define E_SGF_AIM_FIRE         (1 << 2)
#define E_SGF_AIR_SHOT_USED    (1 << 3)

extern struct AnimInfo gE_UpperAnimInfo;
extern u8   gE_UpperAnimType;
extern s16  gE_UpperAnimFrame;
extern u16 *gE_UpperAnimAttribute;
extern s16 *gE_UpperAnimData;

extern s16 gE_UpperAimPitch;
extern s16 gE_UpperAimYaw;

extern s8 gE_ShotgunTimer;
extern u8 gE_ShotgunFlags;
extern u8 gE_MaxObjsHitPerShot;


#define ABILITY_CHRONOS_SLOW_SPLIT 3
#define ABILITY_CHRONOS_SLOW_FACTOR 1.0f / ABILITY_CHRONOS_SLOW_SPLIT

u8 ability_chronos_frame_can_progress(void);
f32 ability_chronos_current_slow_factor(void);

// Ability specific variables
extern u16 aku_invincibility;
extern u8 phasewalk_state;
extern u16 phasewalk_timer;
extern u16 chronos_timer;
extern u8 chronos_expended;
extern u8 milk_drunk;
//

extern struct ability ability_struct[];

#endif