void scroll_o_dl_viscol_mesh_layer_1_vtx_2() {
	int i = 0;
	int count = 91;
	int width = 256 * 0x20;
	int height = 256 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int timeX;
	float amplitudeX = 2.0;
	float frequencyX = 0.10000000149011612;
	float offsetX = 0.0;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(o_dl_viscol_mesh_layer_1_vtx_2);

	deltaX = (int)(amplitudeX * frequencyX * coss((frequencyX * timeX + offsetX) * (1024 * 16 - 1) / 6.28318530718) * 0x20);
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
	currentX += deltaX;	timeX += 1;	currentY += deltaY;
}

void scroll_o_dl_visual_mesh_layer_5_vtx_2() {
	int i = 0;
	int count = 8;
	int width = 256 * 0x20;
	int height = 256 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int timeX;
	float amplitudeX = 2.0;
	float frequencyX = 0.10000000149011612;
	float offsetX = 0.0;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(o_dl_visual_mesh_layer_5_vtx_2);

	deltaX = (int)(amplitudeX * frequencyX * coss((frequencyX * timeX + offsetX) * (1024 * 16 - 1) / 6.28318530718) * 0x20);
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
	currentX += deltaX;	timeX += 1;	currentY += deltaY;
}

void scroll_gfx_mat_o_dl_SwampSand_layer1() {
	Gfx *mat = segmented_to_virtual(mat_o_dl_SwampSand_layer1);

	shift_t(mat, 13, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_o_dl_TransparentSwamp_layer5() {
	Gfx *mat = segmented_to_virtual(mat_o_dl_TransparentSwamp_layer5);

	shift_t(mat, 15, PACK_TILESIZE(0, 1));

};

void scroll_o() {
	scroll_o_dl_viscol_mesh_layer_1_vtx_2();
	scroll_o_dl_visual_mesh_layer_5_vtx_2();
	scroll_gfx_mat_o_dl_SwampSand_layer1();
	scroll_gfx_mat_o_dl_TransparentSwamp_layer5();
};
