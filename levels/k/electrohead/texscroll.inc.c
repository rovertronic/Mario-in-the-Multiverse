void scroll_gfx_mat_electrohead_dj() {
	Gfx *mat = segmented_to_virtual(mat_electrohead_dj);
	static int interval_tex_electrohead_dj = 3;
	static int cur_interval_tex_electrohead_dj = 3;

	if (--cur_interval_tex_electrohead_dj <= 0) {
		shift_t(mat, 16, PACK_TILESIZE(0, 64));
		cur_interval_tex_electrohead_dj = interval_tex_electrohead_dj;
	}

};

void scroll_k_level_geo_electrohead() {
	scroll_gfx_mat_electrohead_dj();
};
