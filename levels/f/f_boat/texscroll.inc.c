void scroll_f_boat_Boat_NEEDS_KEY_DRIVEABLE_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 23;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(f_boat_Boat_NEEDS_KEY_DRIVEABLE_mesh_layer_5_vtx_1);

	deltaX = (int)(0.4000000059604645 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_f_level_geo_f_boat() {
	scroll_f_boat_Boat_NEEDS_KEY_DRIVEABLE_mesh_layer_5_vtx_1();
};
