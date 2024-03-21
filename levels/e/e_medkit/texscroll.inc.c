void scroll_sts_mat_e_medkit_glow_floor_f3d_layer6() {
	Gfx *mat = segmented_to_virtual(mat_e_medkit_glow_floor_f3d_layer6);
	shift_s(mat, 15, PACK_TILESIZE(0, 3));
};

void scroll_e_level_geo_e_medkit() {
	scroll_sts_mat_e_medkit_glow_floor_f3d_layer6();
}
