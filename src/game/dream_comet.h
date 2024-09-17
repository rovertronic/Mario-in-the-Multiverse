#ifndef H_DREAM_COMET
#define H_DREAM_COMET

s32 level_in_dream_comet_mode(void);
s32 dream_comet_unlocked(void);
u8 get_dream_star_flags(int mitm_level_index);
int get_dream_star_count(void);
int get_dream_star_count_file_index(int file);
void render_dream_comet_hud(u8 alpha);
void bhv_dream_catalyst(void);


s32 have_dream_star(int index);
void set_dream_star(int index);

extern u8 dream_comet_enabled;

#endif