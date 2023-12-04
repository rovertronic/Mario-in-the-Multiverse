void scroll_sts_mat_e_rocket_blast_e_f3d_layer5() {
	Gfx *mat = segmented_to_virtual(mat_e_rocket_blast_e_f3d_layer5);
	shift_t(mat, 10, PACK_TILESIZE(0, 6));
	shift_t(mat, 15, PACK_TILESIZE(0, 2));
};

void scroll_actor_geo_e_rocket_blast() {
	scroll_sts_mat_e_rocket_blast_e_f3d_layer5();
}
