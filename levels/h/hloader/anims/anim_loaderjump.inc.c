static const s16 hloader_anim_loaderjump_values[] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 
	0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0x04F6, 
	0x07D5, 0x1076, 0x1F8D, 0x3520, 0x4DBE, 0x6350, 0x7267, 0x7B08, 0x7DE8, 
	0xFFFF, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 
};

static const u16 hloader_anim_loaderjump_indices[] = {
	0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0001, 0x0003, 0x0001, 
	0x0004, 0x0001, 0x0005, 0x000A, 0x0006, 0x000A, 0x0010, 0x000A, 0x001A, 
	0x0001, 0x0024, 0x0001, 0x0025, 0x0001, 0x0026, 0x0001, 0x0027, 0x0001, 
	0x0028, 0x0001, 0x0029, 
};

static const struct Animation hloader_anim_loaderjump = {
	1,
	0,
	0,
	1,
	10,
	ANIMINDEX_NUMPARTS(hloader_anim_loaderjump_indices),
	hloader_anim_loaderjump_values,
	hloader_anim_loaderjump_indices,
	0,
};

