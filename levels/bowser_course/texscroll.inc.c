void scroll_gfx_mat_bowser_course_dl_floorsidingB_layer1() {
	Gfx *mat = segmented_to_virtual(mat_bowser_course_dl_floorsidingB_layer1);

	shift_s(mat, 18, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_bowser_course_dl_rainbowbrick_layer1() {
	Gfx *mat = segmented_to_virtual(mat_bowser_course_dl_rainbowbrick_layer1);

	shift_s(mat, 18, PACK_TILESIZE(0, 1));

};

void scroll_bowser_course() {
	scroll_gfx_mat_bowser_course_dl_floorsidingB_layer1();
	scroll_gfx_mat_bowser_course_dl_rainbowbrick_layer1();
};
