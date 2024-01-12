void scroll_hsky_Sphere_mesh_vtx_1() {
	int i = 0;
	int count = 8;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(hsky_Sphere_mesh_vtx_1);

	deltaX = (int)(0.20000000298023224 * 0x20) % width;
	deltaY = (int)(0.10000000149011612 * 0x20) % height;

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

void scroll_gfx_mat_hsky_fancy_water_layer1() {
	Gfx *mat = segmented_to_virtual(mat_hsky_fancy_water_layer1);

	shift_s(mat, 10, PACK_TILESIZE(0, 1));

};

void scroll_h_level_dl_hsky() {
	scroll_hsky_Sphere_mesh_vtx_1();
	scroll_gfx_mat_hsky_fancy_water_layer1();
};
