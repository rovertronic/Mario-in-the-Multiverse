static const s16 pepperman_anim_admiration_values[] = {
	0x0000, 0xFFF4, 0xFFF4, 0xFFF3, 0xFFF2, 0xFFF2, 0xFFF2, 0xFFF3, 0xFFF3, 
	0xFFF4, 0x0000, 0x0000, 0x0000, 0x0000, 0x2C27, 0x0B44, 0xD8D8, 0x0868, 
	0x12B5, 0xF9FE, 0x1B82, 0x1328, 0xDD46, 0x2BDC, 0x0D1E, 0x564C, 0x0500, 
	0xF2FC, 0x0570, 0x5C34, 0xD120, 0xDB2A, 0x0000, 0xFA77, 0x0000, 0x8000, 
	0xFFFF, 0xFFFF, 0xF7F6, 0xF7AF, 0xF6F5, 0xF5ED, 0xF4E0, 0xF45E, 0xF51D, 
	0xF678, 0xF78A, 0xF7F6, 0xFFFF, 0xFDA4, 0xF7FA, 0xF132, 0xEB91, 0xE93C, 
	0xECBE, 0xF495, 0xFC74, 0xFFFF, 0xFFFF, 0x0039, 0x00D6, 0x01C0, 0x02B7, 
	0x0330, 0x027E, 0x0144, 0x0058, 0xFFFF, 0xD76F, 0x00C2, 0x4829, 0x0000, 
	0x0000, 0xDEC1, 0x0036, 0x009E, 0x0E94, 0xFFEB, 0x0001, 0xEF2B, 0xED71, 
	0xE9A3, 0xE5D5, 0xE41C, 0xE541, 0xE800, 0xEB47, 0xEE05, 0xEF2B, 0x004D, 
	0x004C, 0x004A, 0x0047, 0x0046, 0x0047, 0x0049, 0x004B, 0x004D, 0x0005, 
	0x0005, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0005, 0x2D8B, 
	0x2FF6, 0x3550, 0x3AAA, 0x3D16, 0x3B7A, 0x379F, 0x3302, 0x2F27, 0x2D8B, 
	0xFFB8, 0xFFBD, 0xE216, 
};

static const u16 pepperman_anim_admiration_indices[] = {
	0x0001, 0x0000, 0x0009, 0x0001, 0x0001, 0x000A, 0x0001, 0x000B, 0x0001, 
	0x000C, 0x0001, 0x000D, 0x0001, 0x000E, 0x0001, 0x000F, 0x0001, 0x0010, 
	0x0001, 0x0011, 0x0001, 0x0012, 0x0001, 0x0013, 0x0001, 0x0014, 0x0001, 
	0x0015, 0x0001, 0x0016, 0x0001, 0x0017, 0x0001, 0x0018, 0x0001, 0x0019, 
	0x0001, 0x001A, 0x0001, 0x001B, 0x0001, 0x001C, 0x0001, 0x001D, 0x0001, 
	0x001E, 0x0001, 0x001F, 0x0001, 0x0020, 0x0001, 0x0021, 0x0001, 0x0022, 
	0x0001, 0x0023, 0x0001, 0x0024, 0x0001, 0x0025, 0x000A, 0x0026, 0x000A, 
	0x0030, 0x000A, 0x003A, 0x0001, 0x0044, 0x0001, 0x0045, 0x0001, 0x0046, 
	0x0001, 0x0047, 0x0001, 0x0048, 0x0001, 0x0049, 0x0001, 0x004A, 0x0001, 
	0x004B, 0x0001, 0x004C, 0x0001, 0x004D, 0x0001, 0x004E, 0x000A, 0x004F, 
	0x0009, 0x0059, 0x0009, 0x0062, 0x000A, 0x006B, 0x0001, 0x0075, 0x0001, 
	0x0076, 0x0001, 0x0077, 
};

static const struct Animation pepperman_anim_admiration = {
	0,
	0,
	0,
	1,
	10,
	ANIMINDEX_NUMPARTS(pepperman_anim_admiration_indices),
	pepperman_anim_admiration_values,
	pepperman_anim_admiration_indices,
	0,
};

