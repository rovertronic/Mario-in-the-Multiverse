static const s16 keydoor_anim_fkeydoorAction_values[] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 
	0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 
	0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFC7, 0xFF25, 
	0xFE1E, 0xFCB6, 0xFAF3, 0xF8D8, 0xF669, 0xF3AC, 0xF0A8, 0xED62, 0xE9E4, 
	0xE639, 0xE26B, 0xDE89, 0xDAA0, 0xD6BE, 0xD2F0, 0xCF45, 0xCBC7, 0xC881, 
	0xC57C, 0xC2C0, 0xC051, 0xBE36, 0xBC73, 0xBB0B, 0xBA04, 0xB962, 0xB92A, 
	0xB941, 0xB97F, 0xB9DC, 0xBA4B, 0xBAC5, 0xBB3F, 0xBBAF, 0xBC0B, 0xBC4A, 
	0xBC61, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 
	0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0xFFFF, 
	0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 
	0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 
	0x0000, 0x0049, 0x011E, 0x027E, 0x0468, 0x06E1, 0x09EF, 0x0D98, 0x11E4, 
	0x16D8, 0x1C75, 0x22B3, 0x2983, 0x30C7, 0x3856, 0x4000, 0x4790, 0x4ED3, 
	0x55A3, 0x5BE1, 0x617E, 0x6672, 0x6ABE, 0x6E67, 0x7175, 0x73EE, 0x75D8, 
	0x7738, 0x780E, 0x7856, 0x7834, 0x77D6, 0x774C, 0x76A4, 0x75ED, 0x7536, 
	0x748E, 0x7404, 0x73A6, 0x7384, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 
	0xFFFF, 0x0000, 
};

static const u16 keydoor_anim_fkeydoorAction_indices[] = {
	0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0001, 0x0003, 0x0001, 
	0x0004, 0x0001, 0x0005, 0x0024, 0x0006, 0x0028, 0x002A, 0x0025, 0x0052, 
	0x0019, 0x0077, 0x0028, 0x0090, 0x0019, 0x00B8, 
};

static const struct Animation keydoor_anim_fkeydoorAction = {
	1,
	0,
	0,
	1,
	40,
	ANIMINDEX_NUMPARTS(keydoor_anim_fkeydoorAction_indices),
	keydoor_anim_fkeydoorAction_values,
	keydoor_anim_fkeydoorAction_indices,
	0,
};

