void scroll_J_dl_GymBattleRoom_mesh_layer_1_vtx_0() {
	int i = 0;
	int count = 8;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(J_dl_GymBattleRoom_mesh_layer_1_vtx_0);

	deltaY = (int)(0.1600000262260437 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_J_dl_Plane_001_mesh_layer_1_vtx_4() {
	int i = 0;
	int count = 38;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(J_dl_Plane_001_mesh_layer_1_vtx_4);

	deltaY = (int)(-1.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_J_dl_Plane_001_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 4;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(J_dl_Plane_001_mesh_layer_5_vtx_1);

	deltaX = (int)(2.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_J_dl_Foutain_mesh_layer_1_vtx_2() {
	int i = 0;
	int count = 12;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(J_dl_Foutain_mesh_layer_1_vtx_2);

	deltaY = (int)(-1.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_J_dl_Bell_Tower_001_mesh_layer_1_vtx_2() {
	int i = 0;
	int count = 72;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(J_dl_Bell_Tower_001_mesh_layer_1_vtx_2);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_J() {
	scroll_J_dl_GymBattleRoom_mesh_layer_1_vtx_0();
	scroll_J_dl_Plane_001_mesh_layer_1_vtx_4();
	scroll_J_dl_Plane_001_mesh_layer_5_vtx_1();
	scroll_J_dl_Foutain_mesh_layer_1_vtx_2();
	scroll_J_dl_Bell_Tower_001_mesh_layer_1_vtx_2();
};
