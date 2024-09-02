void scroll_gfx_mat_k_tv3_noise_alpha() {
	Gfx *mat = segmented_to_virtual(mat_k_tv3_noise_alpha);

	shift_s(mat, 9, PACK_TILESIZE(0, 64));
	shift_t(mat, 9, PACK_TILESIZE(0, 20));

};

void scroll_k_level_geo_k_tv3() {
	scroll_gfx_mat_k_tv3_noise_alpha();
};
