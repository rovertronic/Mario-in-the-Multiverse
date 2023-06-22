void scroll_sts_mat_e_sg_spark_mat_f3d_layer1() {
	Gfx *mat = segmented_to_virtual(mat_e_sg_spark_mat_f3d_layer1);
	shift_t(mat, 15, PACK_TILESIZE(0, 12));
};

void scroll_actor_dl_e_sg_spark() {
	scroll_sts_mat_e_sg_spark_mat_f3d_layer1();
}
