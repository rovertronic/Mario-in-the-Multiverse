#ifndef MITM_HUB_H
#define MITM_HUB_H

void level_pipe_loop(void);
void level_pipe_init(void);
void hub_reset_variables(void);
u8 get_hub_level(u8 id);
u8 get_hub_area(u8 id);
u8 get_hub_return_id(u8 id);
void update_hub_star_string(s8 hub_level_index);

extern u8 hub_star_string[]; // For use on the level pause screen
extern s8 hub_level_current_index;

struct mitm_hub_level {
    u8 *author;
    u8 level;
    u8 course;
    u8 star_requirement;
    u8 start_area;
    u8 return_id;
    u8 star_count;
    u8 dream_count;
    char * name;
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
};

extern struct mitm_hub_level hub_levels[];

#endif