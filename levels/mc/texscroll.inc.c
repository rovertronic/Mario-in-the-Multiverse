void scroll_mc_dl_Mute_City_1_mesh_layer_1_vtx_5() {
	int i = 0;
	int count = 551;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(mc_dl_Mute_City_1_mesh_layer_1_vtx_5);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_mc_dl_Mute_City_1_mesh_layer_1_vtx_6() {
	int i = 0;
	int count = 44;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(mc_dl_Mute_City_1_mesh_layer_1_vtx_6);

	deltaY = (int)(-0.5 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_mc_dl_Mute_City_1_mesh_layer_1_vtx_14() {
	int i = 0;
	int count = 92;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(mc_dl_Mute_City_1_mesh_layer_1_vtx_14);

	deltaY = (int)(1.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_mc_dl_Mute_City_1_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 68;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(mc_dl_Mute_City_1_mesh_layer_5_vtx_0);

	deltaY = (int)(-1.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_mc_dl_Mute_City_1_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 88;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(mc_dl_Mute_City_1_mesh_layer_5_vtx_1);

	deltaY = (int)(-1.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_mc_dl_Mute_City_1_mesh_layer_5_vtx_2() {
	int i = 0;
	int count = 8;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(mc_dl_Mute_City_1_mesh_layer_5_vtx_2);

	deltaY = (int)(-1.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_mc_dl_Mute_City_1_mesh_layer_5_vtx_3() {
	int i = 0;
	int count = 16;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(mc_dl_Mute_City_1_mesh_layer_5_vtx_3);

	deltaY = (int)(-1.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_mc() {
	scroll_mc_dl_Mute_City_1_mesh_layer_1_vtx_5();
	scroll_mc_dl_Mute_City_1_mesh_layer_1_vtx_6();
	scroll_mc_dl_Mute_City_1_mesh_layer_1_vtx_14();
	scroll_mc_dl_Mute_City_1_mesh_layer_5_vtx_0();
	scroll_mc_dl_Mute_City_1_mesh_layer_5_vtx_1();
	scroll_mc_dl_Mute_City_1_mesh_layer_5_vtx_2();
	scroll_mc_dl_Mute_City_1_mesh_layer_5_vtx_3();
};
