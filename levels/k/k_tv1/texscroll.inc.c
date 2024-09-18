void scroll_gfx_mat_k_tv1_noise() {
	Gfx *mat = segmented_to_virtual(mat_k_tv1_noise);

	shift_s(mat, 8, PACK_TILESIZE(0, 64));
	shift_t(mat, 8, PACK_TILESIZE(0, 20));

};

void scroll_k_level_geo_k_tv1() {
	scroll_gfx_mat_k_tv1_noise();
};
