void scroll_e_dl__model2_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 1467;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(e_dl__model2_mesh_layer_5_vtx_1);

	deltaX = (int)(0.5 * 0x20) % width;
	deltaY = (int)(1.0 * 0x20) % height;

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

void scroll_gfx_mat_e_dl_acid_f3d_layer5() {
	Gfx *mat = segmented_to_virtual(mat_e_dl_acid_f3d_layer5);


	shift_t(mat, 11, PACK_TILESIZE(0, 16));
	shift_t(mat, 13, PACK_TILESIZE(0, 19));

};

void scroll_gfx_mat_e_dl_acid_f_f3d_layer5() {
	Gfx *mat = segmented_to_virtual(mat_e_dl_acid_f_f3d_layer5);


	shift_s(mat, 12, PACK_TILESIZE(0, 2));
	shift_t(mat, 14, PACK_TILESIZE(0, 3));

};

void scroll_e() {
	scroll_e_dl__model2_mesh_layer_5_vtx_1();
	scroll_gfx_mat_e_dl_acid_f3d_layer5();
	scroll_gfx_mat_e_dl_acid_f_f3d_layer5();
};
