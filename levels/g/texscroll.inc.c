void scroll_gfx_mat_g_dl_cozieswater_001_layer5_area1() {
	Gfx *mat = segmented_to_virtual(mat_g_dl_cozieswater_001_layer5_area1);


	shift_t(mat, 13, PACK_TILESIZE(0, 2));
	shift_s(mat, 18, PACK_TILESIZE(0, 1));
	shift_t(mat, 18, PACK_TILESIZE(0, 3));

};

void scroll_gfx_mat_g_dl_f3dlite_material_058_layer5() {
	Gfx *mat = segmented_to_virtual(mat_g_dl_f3dlite_material_058_layer5);

	shift_s(mat, 15, PACK_TILESIZE(0, 1));

};

void scroll_g() {
	scroll_gfx_mat_g_dl_cozieswater_001_layer5_area1();
	scroll_gfx_mat_g_dl_f3dlite_material_058_layer5();
};
