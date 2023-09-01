void scroll_f_dl_visual_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 149;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(f_dl_visual_mesh_layer_5_vtx_1);

	deltaY = (int)(0.5 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_f_dl_vis2_mesh_layer_1_vtx_17() {
	int i = 0;
	int count = 10;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(f_dl_vis2_mesh_layer_1_vtx_17);

	deltaX = (int)(1.2100000381469727 * 0x20 * random_float() * random_sign()) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_f() {
	scroll_f_dl_visual_mesh_layer_5_vtx_1();
	scroll_f_dl_vis2_mesh_layer_1_vtx_17();
};
