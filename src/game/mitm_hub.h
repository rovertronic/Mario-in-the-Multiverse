#ifndef MITM_HUB_H
#define MITM_HUB_H

void level_pipe_loop(void);
void level_pipe_init(void);
void hub_reset_variables(void);
u8 get_hub_level(u8 id);
u8 get_hub_area(u8 id);
u8 get_hub_return_id(u8 id);
void update_hub_star_string(s8 hub_level_index);
s32 in_vanilla_painting_world(void);

void render_hint_ui(u8 hud_alpha);
void print_mitm_credits(u8 hud_alpha);
void render_painting_ui(f32 alpha);
void render_music_menu_ui(f32 alpha);

extern u8 hub_star_string[]; // For use on the level pause screen
extern s8 hub_level_current_index;

typedef struct mitm_dream_data {
    u8 ability_lock[4];
    u8 dream_star_ct;
} mitm_dream_data;

struct mitm_level_data {
    char * name;
    char * author;
    char * author_abridged;
    u8 level;
    u8 course;
    u8 star_requirement;
    u8 start_area;
    u8 return_id;
    u8 star_count;
    mitm_dream_data * dream_data;
};

struct painting_world {
    char * name;
    u8 level;
};

struct music_data {
    u8 seq;
    u8 dynPhase;
    char * name;
    char * desc;
};

enum mitm_hub_level_ids {
    HUBLEVEL_C1,
    HUBLEVEL_C2,
    HUBLEVEL_C3,
    HUBLEVEL_C4,
    HUBLEVEL_C5,
    HUBLEVEL_C6,
    HUBLEVEL_C7,
    HUBLEVEL_C8,
    HUBLEVEL_C9,
    HUBLEVEL_C10,
    HUBLEVEL_C11,
    HUBLEVEL_C12,
    HUBLEVEL_C13,
    HUBLEVEL_C14,
    HUBLEVEL_C15,
    HUBLEVEL_BOWSER,
    HUBLEVEL_HUB,
    HUBLEVEL_PWORLD,
    HUBLEVEL_SB,
    HUBLEVEL_MC,
    HUBLEVEL_BB,
    HUBLEVEL_COUNT,
};

extern struct mitm_level_data mitm_levels[];
extern struct music_data music_list[];

#endif