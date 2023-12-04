void scroll_o_flame_Plane_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 18;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(o_flame_Plane_mesh_layer_5_vtx_0);

	deltaY = (int)(0.6000000238418579 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_o_level_geo_o_flame() {
	scroll_o_flame_Plane_mesh_layer_5_vtx_0();
};
