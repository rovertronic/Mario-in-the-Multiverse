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

void scroll_k_dl_Cube_002_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 20;
	int width = 1024 * 0x20;
	int height = 1 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int timeX;
	float amplitudeX = 100.0;
	float frequencyX = 0.20000000298023224;
	float offsetX = 0.0;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(k_dl_Cube_002_mesh_layer_5_vtx_0);

	deltaX = (int)(amplitudeX * frequencyX * coss((frequencyX * timeX + offsetX) * (1024 * 16 - 1) / 6.28318530718) * 0x20);
	deltaY = (int)(0.0 * 0x20) % height;

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
	currentX += deltaX;	timeX += 1;	currentY += deltaY;
}

void scroll_k() {
	scroll_k_dl_Cube_002_mesh_layer_1_vtx_1();
	scroll_k_dl_Cube_002_mesh_layer_5_vtx_0();
};
