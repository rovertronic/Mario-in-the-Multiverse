void scroll_sb_train__000_farm_item_09_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 8;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(sb_train__000_farm_item_09_mesh_layer_5_vtx_1);

	deltaY = (int)(5.5 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_sb_level_geo_sb_train() {
	scroll_sb_train__000_farm_item_09_mesh_layer_5_vtx_1();
};
