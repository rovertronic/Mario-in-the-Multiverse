void scroll_l_dl_MITM02_004_mesh_layer_4_vtx_6() {
	int i = 0;
	int count = 96;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(l_dl_MITM02_004_mesh_layer_4_vtx_6);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_l_dl_pvis_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 40;
	int width = 16 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(l_dl_pvis_mesh_layer_5_vtx_0);

	deltaX = (int)(0.10000000149011612 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_l() {
	scroll_l_dl_MITM02_004_mesh_layer_4_vtx_6();
	scroll_l_dl_pvis_mesh_layer_5_vtx_0();
};
