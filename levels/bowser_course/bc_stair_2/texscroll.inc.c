void scroll_gfx_mat_bc_stair_2_startile_001_layer1() {
	Gfx *mat = segmented_to_virtual(mat_bc_stair_2_startile_001_layer1);

	shift_s(mat, 18, PACK_TILESIZE(0, 1));

};

void scroll_bowser_course_level_geo_bc_stair_2() {
	scroll_gfx_mat_bc_stair_2_startile_001_layer1();
};
