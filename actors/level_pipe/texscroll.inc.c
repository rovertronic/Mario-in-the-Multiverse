void scroll_level_pipe_Level_Pipe_Visual_mesh_layer_1_vtx_1() {
	int i = 0;
	int count = 256;
	int width = 128 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(level_pipe_Level_Pipe_Visual_mesh_layer_1_vtx_1);

	deltaX = (int)(0.10000000149011612 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_gfx_mat_level_pipe_MversePipe2_layer1() {
	Gfx *mat = segmented_to_virtual(mat_level_pipe_MversePipe2_layer1);

	shift_s_down(mat, 12, PACK_TILESIZE(0, 1));

};

void scroll_actor_geo_level_pipe() {
	scroll_level_pipe_Level_Pipe_Visual_mesh_layer_1_vtx_1();
	scroll_gfx_mat_level_pipe_MversePipe2_layer1();
};
