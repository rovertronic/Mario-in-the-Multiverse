void scroll_cutter_particle_slash_Plane_001_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 11;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(cutter_particle_slash_Plane_001_mesh_layer_5_vtx_0);

	deltaY = (int)(-8.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_actor_geo_cutter_particle_slash() {
	scroll_cutter_particle_slash_Plane_001_mesh_layer_5_vtx_0();
};
