void scroll_bc_bosslanding_vis_001_mesh_layer_1_vtx_3() {
	int i = 0;
	int count = 9;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(bc_bosslanding_vis_001_mesh_layer_1_vtx_3);

	deltaX = (int)(0.5 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_gfx_mat_bc_bosslanding_floorsidingB_layer1() {
	Gfx *mat = segmented_to_virtual(mat_bc_bosslanding_floorsidingB_layer1);

	shift_s(mat, 18, PACK_TILESIZE(0, 1));

};

void scroll_bowser_course_level_geo_bc_bosslanding() {
	scroll_bc_bosslanding_vis_001_mesh_layer_1_vtx_3();
	scroll_gfx_mat_bc_bosslanding_floorsidingB_layer1();
};
