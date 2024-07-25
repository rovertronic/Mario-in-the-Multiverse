void scroll_debris_debris_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 28;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(debris_debris_mesh_layer_5_vtx_0);

	deltaY = (int)(3.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_gfx_mat_debris_waterfall_layer5() {
	Gfx *mat = segmented_to_virtual(mat_debris_waterfall_layer5);

	shift_t(mat, 19, PACK_TILESIZE(0, 4));

};

void scroll_B_level_geo_debris() {
	scroll_debris_debris_mesh_layer_5_vtx_0();
	scroll_gfx_mat_debris_waterfall_layer5();
};
