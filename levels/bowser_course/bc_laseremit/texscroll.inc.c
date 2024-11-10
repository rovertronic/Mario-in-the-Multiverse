void scroll_bc_laseremit_Circle_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 28;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bc_laseremit_Circle_mesh_layer_5_vtx_0);

	deltaY = (int)(12.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_bowser_course_level_geo_bc_laseremit() {
	scroll_bc_laseremit_Circle_mesh_layer_5_vtx_0();
};
