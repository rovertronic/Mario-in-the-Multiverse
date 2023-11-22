void scroll_i_dl_area2_room1_geo_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 68;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(i_dl_area2_room1_geo_mesh_layer_5_vtx_0);

	deltaX = (int)(0.9700000286102295 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_i_dl_area2_room1_geo_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 48;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(i_dl_area2_room1_geo_mesh_layer_5_vtx_1);

	deltaX = (int)(-6.799999713897705 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_i_dl_main_section_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 229;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(i_dl_main_section_mesh_layer_5_vtx_0);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_i_dl_main_section_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 52;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(i_dl_main_section_mesh_layer_5_vtx_1);

	deltaX = (int)(1.5099999904632568 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_i_dl_main_section_mesh_layer_5_vtx_4() {
	int i = 0;
	int count = 48;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(i_dl_main_section_mesh_layer_5_vtx_4);

	deltaX = (int)(0.6100000143051147 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_i_dl_first_section_geo_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 192;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(i_dl_first_section_geo_mesh_layer_5_vtx_1);

	deltaX = (int)(1.2999999523162842 * 0x20) % width;
	deltaY = (int)(0.4000000059604645 * 0x20) % height;

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

void scroll_i_dl_first_section_geo_mesh_layer_5_vtx_3() {
	int i = 0;
	int count = 276;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(i_dl_first_section_geo_mesh_layer_5_vtx_3);

	deltaX = (int)(1.0 * 0x20) % width;
	deltaY = (int)(1.0 * 0x20) % height;

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

void scroll_i_dl_first_section_geo_mesh_layer_5_vtx_5() {
	int i = 0;
	int count = 230;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(i_dl_first_section_geo_mesh_layer_5_vtx_5);

	deltaY = (int)(1.209999918937683 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_i_dl_first_section_geo_mesh_layer_1_vtx_2() {
	int i = 0;
	int count = 460;
	int height = 128 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(i_dl_first_section_geo_mesh_layer_1_vtx_2);

	deltaY = (int)(2.9800000190734863 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_i_dl_first_section_geo_mesh_layer_4_vtx_0() {
	int i = 0;
	int count = 12;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(i_dl_first_section_geo_mesh_layer_4_vtx_0);

	deltaY = (int)(-0.4699999690055847 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_i_dl_first_section_geo_mesh_layer_4_vtx_1() {
	int i = 0;
	int count = 12;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(i_dl_first_section_geo_mesh_layer_4_vtx_1);

	deltaY = (int)(-0.3199999928474426 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_i_dl_first_section_geo_mesh_layer_4_vtx_2() {
	int i = 0;
	int count = 12;
	int width = 128 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int timeX;
	float amplitudeX = 1.3499999046325684;
	float frequencyX = 0.3700000047683716;
	float offsetX = 0.0;
	Vtx *vertices = segmented_to_virtual(i_dl_first_section_geo_mesh_layer_4_vtx_2);

	deltaX = (int)(amplitudeX * frequencyX * coss((frequencyX * timeX + offsetX) * (1024 * 16 - 1) / 6.28318530718) * 0x20);

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;	timeX += 1;
}

void scroll_i() {
	scroll_i_dl_area2_room1_geo_mesh_layer_5_vtx_0();
	scroll_i_dl_area2_room1_geo_mesh_layer_5_vtx_1();
	scroll_i_dl_main_section_mesh_layer_5_vtx_0();
	scroll_i_dl_main_section_mesh_layer_5_vtx_1();
	scroll_i_dl_main_section_mesh_layer_5_vtx_4();
	scroll_i_dl_first_section_geo_mesh_layer_5_vtx_1();
	scroll_i_dl_first_section_geo_mesh_layer_5_vtx_3();
	scroll_i_dl_first_section_geo_mesh_layer_5_vtx_5();
	scroll_i_dl_first_section_geo_mesh_layer_1_vtx_2();
	scroll_i_dl_first_section_geo_mesh_layer_4_vtx_0();
	scroll_i_dl_first_section_geo_mesh_layer_4_vtx_1();
	scroll_i_dl_first_section_geo_mesh_layer_4_vtx_2();
};
