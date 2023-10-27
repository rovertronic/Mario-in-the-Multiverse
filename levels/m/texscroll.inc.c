void scroll_m_dl_A4_Maze_A_mesh_layer_4_vtx_1() {
	int i = 0;
	int count = 32;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(m_dl_A4_Maze_A_mesh_layer_4_vtx_1);

	deltaX = (int)(0.5 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_m_dl_A4_Maze_B_mesh_layer_4_vtx_1() {
	int i = 0;
	int count = 32;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(m_dl_A4_Maze_B_mesh_layer_4_vtx_1);

	deltaX = (int)(0.5 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_m_dl_A4_Maze_C_mesh_layer_4_vtx_1() {
	int i = 0;
	int count = 64;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(m_dl_A4_Maze_C_mesh_layer_4_vtx_1);

	deltaX = (int)(0.5 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_m_dl_A4_Maze_D_mesh_layer_4_vtx_1() {
	int i = 0;
	int count = 32;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(m_dl_A4_Maze_D_mesh_layer_4_vtx_1);

	deltaX = (int)(0.5 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_m_dl_A4_Maze_E_mesh_layer_4_vtx_1() {
	int i = 0;
	int count = 64;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(m_dl_A4_Maze_E_mesh_layer_4_vtx_1);

	deltaX = (int)(0.5 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_m_dl_A4_Room_B_mesh_layer_4_vtx_1() {
	int i = 0;
	int count = 64;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(m_dl_A4_Room_B_mesh_layer_4_vtx_1);

	deltaX = (int)(0.5 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

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
	scroll_m_dl_A4_Maze_A_mesh_layer_4_vtx_1();
	scroll_m_dl_A4_Maze_B_mesh_layer_4_vtx_1();
	scroll_m_dl_A4_Maze_C_mesh_layer_4_vtx_1();
	scroll_m_dl_A4_Maze_D_mesh_layer_4_vtx_1();
	scroll_m_dl_A4_Maze_E_mesh_layer_4_vtx_1();
	scroll_m_dl_A4_Room_B_mesh_layer_4_vtx_1();
	scroll_gfx_mat_m_dl_Water_A_layer5();
	scroll_gfx_mat_m_dl_Water_B_layer5();
};
