void scroll_magic_shield_prune_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 40;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(magic_shield_prune_mesh_layer_5_vtx_0);

	deltaY = (int)(1.3299999237060547 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_i_level_geo_magic_shield() {
	scroll_magic_shield_prune_mesh_layer_5_vtx_0();
};
