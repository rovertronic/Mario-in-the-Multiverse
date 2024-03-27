void scroll_l_dl_MITM02_004_mesh_layer_4_vtx_3() {
	int i = 0;
	int count = 144;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(l_dl_MITM02_004_mesh_layer_4_vtx_3);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_l() {
	scroll_l_dl_MITM02_004_mesh_layer_4_vtx_3();
};
