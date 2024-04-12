void scroll_matplatform_Cube_mesh_layer_4_vtx_0() {
	int i = 0;
	int count = 70;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(matplatform_Cube_mesh_layer_4_vtx_0);

	deltaY = (int)(0.5 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_bowser_course_level_geo_matplatform() {
	scroll_matplatform_Cube_mesh_layer_4_vtx_0();
};
