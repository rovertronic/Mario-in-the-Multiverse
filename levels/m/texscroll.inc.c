void scroll_m_dl_hub_sign_mesh_layer_4_vtx_0() {
	int i = 0;
	int count = 4;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	static int timeY;
	float amplitudeY = 0.699999988079071;
	float frequencyY = 0.699999988079071;
	float offsetY = 0.05000000074505806;
	Vtx *vertices = segmented_to_virtual(m_dl_hub_sign_mesh_layer_4_vtx_0);

	deltaY = (int)(amplitudeY * frequencyY * coss((frequencyY * timeY + offsetY) * (1024 * 16 - 1) / 6.28318530718) * 0x20);

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;	timeY += 1;
}

void scroll_m_dl_A4_Maze_A_mesh_layer_4_vtx_1() {
	int i = 0;
	int count = 64;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(m_dl_A4_Maze_A_mesh_layer_4_vtx_1);

	deltaY = (int)(-2.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_m_dl_A4_Room_B_mesh_layer_4_vtx_1() {
	int i = 0;
	int count = 64;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(m_dl_A4_Room_B_mesh_layer_4_vtx_1);

	deltaY = (int)(-2.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_m_dl_A4_Maze_C_mesh_layer_4_vtx_1() {
	int i = 0;
	int count = 96;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(m_dl_A4_Maze_C_mesh_layer_4_vtx_1);

	deltaY = (int)(-2.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_m_dl_A4_Maze_D_mesh_layer_4_vtx_1() {
	int i = 0;
	int count = 64;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(m_dl_A4_Maze_D_mesh_layer_4_vtx_1);

	deltaY = (int)(-2.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_m_dl_A4_Maze_E_mesh_layer_4_vtx_1() {
	int i = 0;
	int count = 64;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(m_dl_A4_Maze_E_mesh_layer_4_vtx_1);

	deltaY = (int)(-2.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_m_dl_A4_Room_C_mesh_layer_4_vtx_3() {
	int i = 0;
	int count = 184;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(m_dl_A4_Room_C_mesh_layer_4_vtx_3);

	deltaY = (int)(-2.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_gfx_mat_m_dl_Stars_layer5() {
	Gfx *mat = segmented_to_virtual(mat_m_dl_Stars_layer5);
	static int interval_tex_m_dl_Stars_layer5 = 8;
	static int cur_interval_tex_m_dl_Stars_layer5 = 8;

	if (--cur_interval_tex_m_dl_Stars_layer5 <= 0) {
		shift_s(mat, 16, PACK_TILESIZE(0, 2));
		cur_interval_tex_m_dl_Stars_layer5 = interval_tex_m_dl_Stars_layer5;
	}

};

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
	scroll_m_dl_hub_sign_mesh_layer_4_vtx_0();
	scroll_m_dl_A4_Maze_A_mesh_layer_4_vtx_1();
	scroll_m_dl_A4_Room_B_mesh_layer_4_vtx_1();
	scroll_m_dl_A4_Maze_C_mesh_layer_4_vtx_1();
	scroll_m_dl_A4_Maze_D_mesh_layer_4_vtx_1();
	scroll_m_dl_A4_Maze_E_mesh_layer_4_vtx_1();
	scroll_m_dl_A4_Room_C_mesh_layer_4_vtx_3();
	scroll_gfx_mat_m_dl_Stars_layer5();
	scroll_gfx_mat_m_dl_Water_A_layer5();
	scroll_gfx_mat_m_dl_Water_B_layer5();
};
