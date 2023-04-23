#ifndef MITM_HUB_H
#define MITM_HUB_H

void level_pipe_loop(void);
u8 get_hub_level(u8 id);

struct mitm_hub_level {
    u8 *author;
    u8 level;
    u8 course;
    u8 star_requirement;
};

#endif