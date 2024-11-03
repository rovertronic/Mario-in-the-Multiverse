void scroll_bc_crystalp_Icosphere_001_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 60;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(bc_crystalp_Icosphere_001_mesh_layer_5_vtx_0);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_bowser_course_level_geo_bc_crystalp() {
	scroll_bc_crystalp_Icosphere_001_mesh_layer_5_vtx_0();
};
