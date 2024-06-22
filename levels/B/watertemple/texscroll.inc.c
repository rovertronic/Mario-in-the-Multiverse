void scroll_watertemple_watertemple_mesh_layer_7_vtx_0() {
	int i = 0;
	int count = 6;
	int width = 128 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(watertemple_watertemple_mesh_layer_7_vtx_0);

	deltaX = (int)(0.10000000149011612 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_watertemple_watertemple_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 6;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(watertemple_watertemple_mesh_layer_5_vtx_0);

	deltaY = (int)(-0.25 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_gfx_mat_watertemple_water_2_layer7() {
	Gfx *mat = segmented_to_virtual(mat_watertemple_water_2_layer7);


	shift_t_down(mat, 13, PACK_TILESIZE(0, 1));
	shift_s(mat, 15, PACK_TILESIZE(0, 1));
	shift_t(mat, 15, PACK_TILESIZE(0, 1));

};

void scroll_B_level_geo_watertemple() {
	scroll_watertemple_watertemple_mesh_layer_7_vtx_0();
	scroll_watertemple_watertemple_mesh_layer_5_vtx_0();
	scroll_gfx_mat_watertemple_water_2_layer7();
};
