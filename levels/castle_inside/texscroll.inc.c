void scroll_castle_inside_dl_machine_mesh_layer_1_vtx_5() {
	int i = 0;
	int count = 8;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(castle_inside_dl_machine_mesh_layer_1_vtx_5);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_castle_inside_dl_Map_mesh_layer_1_vtx_7() {
	int i = 0;
	int count = 72;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(castle_inside_dl_Map_mesh_layer_1_vtx_7);

	deltaX = (int)(0.4000000059604645 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_castle_inside_dl_Map_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 72;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(castle_inside_dl_Map_mesh_layer_5_vtx_0);

	deltaY = (int)(0.3499999940395355 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_castle_inside_dl_Map_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 464;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(castle_inside_dl_Map_mesh_layer_5_vtx_1);

	deltaY = (int)(0.3499999940395355 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_gfx_mat_castle_inside_dl_acid_f3d_layer5() {
	Gfx *mat = segmented_to_virtual(mat_castle_inside_dl_acid_f3d_layer5);


	shift_t(mat, 11, PACK_TILESIZE(0, 16));
	shift_t(mat, 13, PACK_TILESIZE(0, 19));

};

void scroll_castle_inside() {
	scroll_castle_inside_dl_machine_mesh_layer_1_vtx_5();
	scroll_castle_inside_dl_Map_mesh_layer_1_vtx_7();
	scroll_castle_inside_dl_Map_mesh_layer_5_vtx_0();
	scroll_castle_inside_dl_Map_mesh_layer_5_vtx_1();
	scroll_gfx_mat_castle_inside_dl_acid_f3d_layer5();
};
