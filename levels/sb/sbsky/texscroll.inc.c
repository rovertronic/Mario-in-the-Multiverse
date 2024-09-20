void scroll_sbsky_sbsky_mesh_vtx_0() {
	int i = 0;
	int count = 93;
	int height = 256 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(sbsky_sbsky_mesh_vtx_0);

	deltaY = (int)(0.4000000059604645 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_sbsky_sbsky_mesh_vtx_2() {
	int i = 0;
	int count = 48;
	int width = 64 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(sbsky_sbsky_mesh_vtx_2);

	deltaX = (int)(0.10000000149011612 * 0x20) % width;
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

void scroll_gfx_mat_sbsky_matrix_layer1() {
	Gfx *mat = segmented_to_virtual(mat_sbsky_matrix_layer1);

	shift_t_down(mat, 14, PACK_TILESIZE(0, 1));

};

void scroll_sb_level_dl_sbsky() {
	scroll_sbsky_sbsky_mesh_vtx_0();
	scroll_sbsky_sbsky_mesh_vtx_2();
	scroll_gfx_mat_sbsky_matrix_layer1();
};
