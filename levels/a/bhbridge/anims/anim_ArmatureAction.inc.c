static const s16 bhbridge_anim_ArmatureAction_values[] = {
	0x0000, 0x0000, 0x0000, 0x18E3, 0x0000, 0xDC71, 
};

static const u16 bhbridge_anim_ArmatureAction_indices[] = {
	0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0001, 0x0003, 0x0001, 
	0x0004, 0x0001, 0x0005, 
};

static const struct Animation bhbridge_anim_ArmatureAction = {
	0,
	0,
	0,
	1,
	1,
	ANIMINDEX_NUMPARTS(bhbridge_anim_ArmatureAction_indices),
	bhbridge_anim_ArmatureAction_values,
	bhbridge_anim_ArmatureAction_indices,
	0,
};

