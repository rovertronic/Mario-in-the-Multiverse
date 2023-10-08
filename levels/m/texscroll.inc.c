void scroll_gfx_mat_m_dl_Water_A_layer5() {
	Gfx *mat = segmented_to_virtual(mat_m_dl_Water_A_layer5);


	shift_s_down(mat, 15, PACK_TILESIZE(0, 1));
	shift_t_down(mat, 15, PACK_TILESIZE(0, 1));
	shift_s(mat, 17, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_m_dl_Water_B_layer5() {
	Gfx *mat = segmented_to_virtual(mat_m_dl_Water_B_layer5);


	shift_s_down(mat, 15, PACK_TILESIZE(0, 1));
	shift_s(mat, 17, PACK_TILESIZE(0, 1));
	shift_t_down(mat, 17, PACK_TILESIZE(0, 1));

};

void scroll_m() {
	scroll_gfx_mat_m_dl_Water_A_layer5();
	scroll_gfx_mat_m_dl_Water_B_layer5();
};
