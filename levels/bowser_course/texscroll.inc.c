void scroll_bowser_course_dl_vis_mesh_layer_1_vtx_7() {
	int i = 0;
	int count = 28;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(bowser_course_dl_vis_mesh_layer_1_vtx_7);

	deltaX = (int)(0.5 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_gfx_mat_bowser_course_dl_startile_001_layer1() {
	Gfx *mat = segmented_to_virtual(mat_bowser_course_dl_startile_001_layer1);

	shift_s(mat, 18, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_bowser_course_dl_rainbowbrick_layer1() {
	Gfx *mat = segmented_to_virtual(mat_bowser_course_dl_rainbowbrick_layer1);

	shift_s(mat, 18, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_bowser_course_dl_floorsidingB_layer1() {
	Gfx *mat = segmented_to_virtual(mat_bowser_course_dl_floorsidingB_layer1);

	shift_s(mat, 18, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_bowser_course_dl_arrow() {
	Gfx *mat = segmented_to_virtual(mat_bowser_course_dl_arrow);
	static int interval_tex_bowser_course_dl_arrow = 4;
	static int cur_interval_tex_bowser_course_dl_arrow = 4;

	if (--cur_interval_tex_bowser_course_dl_arrow <= 0) {
		shift_s(mat, 8, PACK_TILESIZE(0, 64));
		cur_interval_tex_bowser_course_dl_arrow = interval_tex_bowser_course_dl_arrow;
	}

};

void scroll_bowser_course() {
	scroll_bowser_course_dl_vis_mesh_layer_1_vtx_7();
	scroll_gfx_mat_bowser_course_dl_startile_001_layer1();
	scroll_gfx_mat_bowser_course_dl_rainbowbrick_layer1();
	scroll_gfx_mat_bowser_course_dl_floorsidingB_layer1();
	scroll_gfx_mat_bowser_course_dl_arrow();
};
