void scroll_bb_dl_Big_Blue_mesh_layer_1_vtx_1() {
	int i = 0;
	int count = 576;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(bb_dl_Big_Blue_mesh_layer_1_vtx_1);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_bb_dl_Big_Blue_mesh_layer_1_vtx_2() {
	int i = 0;
	int count = 62;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bb_dl_Big_Blue_mesh_layer_1_vtx_2);

	deltaY = (int)(0.5 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_bb_dl_Big_Blue_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 8;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bb_dl_Big_Blue_mesh_layer_5_vtx_0);

	deltaY = (int)(0.25 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_bb_dl_Big_Blue_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 16;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bb_dl_Big_Blue_mesh_layer_5_vtx_1);

	deltaY = (int)(-1.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_bb_dl_Big_Blue_mesh_layer_5_vtx_2() {
	int i = 0;
	int count = 8;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bb_dl_Big_Blue_mesh_layer_5_vtx_2);

	deltaY = (int)(-1.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_bb_dl_Big_Blue_mesh_layer_5_vtx_3() {
	int i = 0;
	int count = 8;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bb_dl_Big_Blue_mesh_layer_5_vtx_3);

	deltaY = (int)(-1.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_bb() {
	scroll_bb_dl_Big_Blue_mesh_layer_1_vtx_1();
	scroll_bb_dl_Big_Blue_mesh_layer_1_vtx_2();
	scroll_bb_dl_Big_Blue_mesh_layer_5_vtx_0();
	scroll_bb_dl_Big_Blue_mesh_layer_5_vtx_1();
	scroll_bb_dl_Big_Blue_mesh_layer_5_vtx_2();
	scroll_bb_dl_Big_Blue_mesh_layer_5_vtx_3();
};
