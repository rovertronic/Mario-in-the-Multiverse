void scroll_fsky_sky_mesh_vtx_4() {
	int i = 0;
	int count = 12;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(fsky_sky_mesh_vtx_4);

	deltaX = (int)(0.30000001192092896 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_f_level_dl_fsky() {
	scroll_fsky_sky_mesh_vtx_4();
};
