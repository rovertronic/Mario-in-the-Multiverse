void scroll_i_dl_level_rocket_room_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 28;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(i_dl_level_rocket_room_mesh_layer_5_vtx_0);

	deltaX = (int)(0.9700000286102295 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_i_dl_level_rocket_room_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 48;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(i_dl_level_rocket_room_mesh_layer_5_vtx_1);

	deltaX = (int)(-6.799999713897705 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_i_dl_Plane_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 80;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(i_dl_Plane_mesh_layer_5_vtx_1);

	deltaX = (int)(0.40000003576278687 * 0x20) % width;
	deltaY = (int)(0.9699999690055847 * 0x20) % height;

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
	currentX += deltaX;	currentY += deltaY;
}

void scroll_i() {
	scroll_i_dl_level_rocket_room_mesh_layer_5_vtx_0();
	scroll_i_dl_level_rocket_room_mesh_layer_5_vtx_1();
	scroll_i_dl_Plane_mesh_layer_5_vtx_1();
};
