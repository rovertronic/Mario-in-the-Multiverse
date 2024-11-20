void scroll_airlock_water_Cube_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 8;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(airlock_water_Cube_mesh_layer_5_vtx_0);

	deltaY = (int)(-0.25 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_B_level_geo_airlock_water() {
	scroll_airlock_water_Cube_mesh_layer_5_vtx_0();
};
