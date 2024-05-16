void scroll_n_dl_lime_mesh_layer_1_vtx_3() {
	int i = 0;
	int count = 8;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(n_dl_lime_mesh_layer_1_vtx_3);

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

void scroll_gfx_mat_n_dl_tar_layer1() {
	Gfx *mat = segmented_to_virtual(mat_n_dl_tar_layer1);

	shift_s_down(mat, 12, PACK_TILESIZE(0, 1));

};

void scroll_n() {
	scroll_n_dl_lime_mesh_layer_1_vtx_3();
	scroll_gfx_mat_n_dl_tar_layer1();
};
