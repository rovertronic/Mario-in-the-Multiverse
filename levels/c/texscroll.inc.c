void scroll_c_dl_level_c_mesh_layer_1_vtx_4() {
	int i = 0;
	int count = 26;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(c_dl_level_c_mesh_layer_1_vtx_4);

	deltaY = (int)(1.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_c() {
	scroll_c_dl_level_c_mesh_layer_1_vtx_4();
};
