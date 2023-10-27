void scroll_g_dl_Circle_006_mesh_layer_1_vtx_0() {
	int i = 0;
	int count = 32;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(g_dl_Circle_006_mesh_layer_1_vtx_0);

	deltaX = (int)(0.4000000059604645 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_g_dl_Circle_006_mesh_layer_1_vtx_1() {
	int i = 0;
	int count = 32;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(g_dl_Circle_006_mesh_layer_1_vtx_1);

	deltaX = (int)(0.6000000238418579 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_g_dl_Circle_006_mesh_layer_1_vtx_2() {
	int i = 0;
	int count = 32;
	int width = 128 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(g_dl_Circle_006_mesh_layer_1_vtx_2);

	deltaX = (int)(0.30000001192092896 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_g_dl_Circle_006_mesh_layer_1_vtx_3() {
	int i = 0;
	int count = 38;
	int width = 256 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(g_dl_Circle_006_mesh_layer_1_vtx_3);

	deltaX = (int)(0.20000000298023224 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_g_dl_Circle_006_mesh_layer_4_vtx_0() {
	int i = 0;
	int count = 32;
	int width = 128 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(g_dl_Circle_006_mesh_layer_4_vtx_0);

	deltaX = (int)(0.15000000596046448 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_gfx_mat_g_dl_cozieswater_001_layer5_area1() {
	Gfx *mat = segmented_to_virtual(mat_g_dl_cozieswater_001_layer5_area1);


	shift_t(mat, 13, PACK_TILESIZE(0, 2));
	shift_s(mat, 18, PACK_TILESIZE(0, 1));
	shift_t(mat, 18, PACK_TILESIZE(0, 3));

};

void scroll_g() {
	scroll_g_dl_Circle_006_mesh_layer_1_vtx_0();
	scroll_g_dl_Circle_006_mesh_layer_1_vtx_1();
	scroll_g_dl_Circle_006_mesh_layer_1_vtx_2();
	scroll_g_dl_Circle_006_mesh_layer_1_vtx_3();
	scroll_g_dl_Circle_006_mesh_layer_4_vtx_0();
	scroll_gfx_mat_g_dl_cozieswater_001_layer5_area1();
};
