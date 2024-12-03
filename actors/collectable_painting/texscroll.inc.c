void scroll_collectable_painting_rainbow_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 18;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int timeX;
	float amplitudeX = 1.0;
	float frequencyX = 0.699999988079071;
	float offsetX = 0.0;
	Vtx *vertices = segmented_to_virtual(collectable_painting_rainbow_mesh_layer_5_vtx_1);

	deltaX = (int)(amplitudeX * frequencyX * coss((frequencyX * timeX + offsetX) * (1024 * 16 - 1) / 6.28318530718) * 0x20);

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;	timeX += 1;
}

void scroll_collectable_painting_rainbow_mesh_layer_5_vtx_2() {
	int i = 0;
	int count = 15;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int timeX;
	float amplitudeX = 3.0;
	float frequencyX = 0.30000001192092896;
	float offsetX = 0.0;
	Vtx *vertices = segmented_to_virtual(collectable_painting_rainbow_mesh_layer_5_vtx_2);

	deltaX = (int)(amplitudeX * frequencyX * coss((frequencyX * timeX + offsetX) * (1024 * 16 - 1) / 6.28318530718) * 0x20);

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;	timeX += 1;
}

void scroll_gfx_mat_collectable_painting_rainboo_alt_center_layer5() {
	Gfx *mat = segmented_to_virtual(mat_collectable_painting_rainboo_alt_center_layer5);

	shift_s(mat, 10, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_collectable_painting_rainboo_layer5() {
	Gfx *mat = segmented_to_virtual(mat_collectable_painting_rainboo_layer5);

	shift_s(mat, 10, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_collectable_painting_rainboo_alt_001_layer5() {
	Gfx *mat = segmented_to_virtual(mat_collectable_painting_rainboo_alt_001_layer5);

	shift_s(mat, 10, PACK_TILESIZE(0, 1));

};

void scroll_actor_geo_collectable_painting() {
	scroll_collectable_painting_rainbow_mesh_layer_5_vtx_1();
	scroll_collectable_painting_rainbow_mesh_layer_5_vtx_2();
	scroll_gfx_mat_collectable_painting_rainboo_alt_center_layer5();
	scroll_gfx_mat_collectable_painting_rainboo_layer5();
	scroll_gfx_mat_collectable_painting_rainboo_alt_001_layer5();
};
