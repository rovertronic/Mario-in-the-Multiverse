#ifndef MITM_HUB_H
#define MITM_HUB_H

void level_pipe_loop(void);
void hub_reset_variables(void);
u8 get_hub_level(u8 id);
u8 get_hub_area(u8 id);
u8 get_hub_return_id(u8 id);

extern u8 hub_star_string[]; // For use on the level pause screen
extern s8 hub_level_current_index;

struct mitm_hub_level {
    u8 *author;
    u8 level;
    u8 course;
    u8 star_requirement;
    u8 start_area;
    u8 return_id;
};

#endif