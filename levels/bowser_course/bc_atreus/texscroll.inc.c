void scroll_bc_atreus_root_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 213;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bc_atreus_root_mesh_layer_5_vtx_0);

	deltaX = (int)(0.20000000298023224 * 0x20) % width;
	deltaY = (int)(0.10000000149011612 * 0x20) % height;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}
	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
		vertices[i].n.tc[1] += deltaY;
	}
	currentX += deltaX;	currentY += deltaY;
}

void scroll_bc_atreus_root_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 213;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bc_atreus_root_mesh_layer_5_vtx_1);

	deltaX = (int)(0.20000000298023224 * 0x20) % width;
	deltaY = (int)(0.10000000149011612 * 0x20) % height;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}
	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
		vertices[i].n.tc[1] += deltaY;
	}
	currentX += deltaX;	currentY += deltaY;
}

void scroll_gfx_mat_bc_atreus_fancy_water() {
	Gfx *mat = segmented_to_virtual(mat_bc_atreus_fancy_water);

	shift_s(mat, 9, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_bc_atreus_fancy_water_aer() {
	Gfx *mat = segmented_to_virtual(mat_bc_atreus_fancy_water_aer);

	shift_s(mat, 9, PACK_TILESIZE(0, 1));

};

void scroll_bowser_course_level_geo_bc_atreus() {
	scroll_bc_atreus_root_mesh_layer_5_vtx_0();
	scroll_bc_atreus_root_mesh_layer_5_vtx_1();
	scroll_gfx_mat_bc_atreus_fancy_water();
	scroll_gfx_mat_bc_atreus_fancy_water_aer();
};
