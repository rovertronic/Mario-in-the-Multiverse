void scroll_e_candelabra_o_model_2_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 96;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(e_candelabra_o_model_2_mesh_layer_5_vtx_0);

	deltaY = (int)(-1.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_sts_mat_e_candelabra_o_flame_f3d_layer5() {
	Gfx *mat = segmented_to_virtual(mat_e_candelabra_o_flame_f3d_layer5);
	shift_t(mat, 15, PACK_TILESIZE(0, 6));
};

void scroll_e_level_geo_e_candelabra_o() {
	scroll_e_candelabra_o_model_2_mesh_layer_5_vtx_0();
	scroll_sts_mat_e_candelabra_o_flame_f3d_layer5();
}
