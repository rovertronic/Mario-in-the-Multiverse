void scroll_k_dl_Cube_002_mesh_layer_1_vtx_1() {
	int i = 0;
	int count = 275;
	int height = 128 * 0x20;

	static int currentY = 0;
	int deltaY;
	static int timeY;
	float amplitudeY = 1.0;
	float frequencyY = 0.5;
	float offsetY = 0.0;
	Vtx *vertices = segmented_to_virtual(k_dl_Cube_002_mesh_layer_1_vtx_1);

	deltaY = (int)(amplitudeY * frequencyY * coss((frequencyY * timeY + offsetY) * (1024 * 16 - 1) / 6.28318530718) * 0x20);

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;	timeY += 1;
}

void scroll_k_dl_z_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 118;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(k_dl_z_mesh_layer_5_vtx_0);

	deltaX = (int)(-1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_gfx_mat_k_dl_rainbowlight() {
	Gfx *mat = segmented_to_virtual(mat_k_dl_rainbowlight);

	shift_s(mat, 12, PACK_TILESIZE(0, 50));

};

void scroll_gfx_mat_k_dl_rainbowlight_op() {
	Gfx *mat = segmented_to_virtual(mat_k_dl_rainbowlight_op);

	shift_s(mat, 12, PACK_TILESIZE(0, 5));

};

void scroll_gfx_mat_k_dl_FloorGlow() {
	Gfx *mat = segmented_to_virtual(mat_k_dl_FloorGlow);
	static int interval_tex_k_dl_FloorGlow = 5;
	static int cur_interval_tex_k_dl_FloorGlow = 5;

	if (--cur_interval_tex_k_dl_FloorGlow <= 0) {
		shift_s(mat, 13, PACK_TILESIZE(0, 64));
		shift_t(mat, 13, PACK_TILESIZE(0, 32));
		cur_interval_tex_k_dl_FloorGlow = interval_tex_k_dl_FloorGlow;
	}

};

void scroll_gfx_mat_k_dl_Floor() {
	Gfx *mat = segmented_to_virtual(mat_k_dl_Floor);
	static int interval_tex_k_dl_Floor = 5;
	static int cur_interval_tex_k_dl_Floor = 5;

	if (--cur_interval_tex_k_dl_Floor <= 0) {
		shift_s(mat, 13, PACK_TILESIZE(0, 64));
		shift_t(mat, 13, PACK_TILESIZE(0, 32));
		cur_interval_tex_k_dl_Floor = interval_tex_k_dl_Floor;
	}

};

void scroll_k() {
	scroll_k_dl_Cube_002_mesh_layer_1_vtx_1();
	scroll_k_dl_z_mesh_layer_5_vtx_0();
	scroll_gfx_mat_k_dl_rainbowlight();
	scroll_gfx_mat_k_dl_rainbowlight_op();
	scroll_gfx_mat_k_dl_FloorGlow();
	scroll_gfx_mat_k_dl_Floor();
};
