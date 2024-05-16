void scroll_hubsky2_1Solar_Winds_002_mesh_vtx_0() {
	int i = 0;
	int count = 292;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(hubsky2_1Solar_Winds_002_mesh_vtx_0);

	deltaY = (int)(0.10000000149011612 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_castle_inside_level_dl_hubsky2() {
	scroll_hubsky2_1Solar_Winds_002_mesh_vtx_0();
};
