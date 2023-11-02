void scroll_o_spooky_sky_Sphere_001_mesh_vtx_0() {
	int i = 0;
	int count = 229;
	int width = 256 * 0x20;
	int height = 256 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(o_spooky_sky_Sphere_001_mesh_vtx_0);

	deltaX = (int)(0.20000000298023224 * 0x20) % width;
	deltaY = (int)(0.05000000074505806 * 0x20) % height;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}
	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
		vertices[i].n.tc[1] += deltaY;
	}
	currentX += deltaX;	currentY += deltaY;
}

void scroll_gfx_mat_o_spooky_sky_dark_skybox_layer1() {
	Gfx *mat = segmented_to_virtual(mat_o_spooky_sky_dark_skybox_layer1);


	shift_t_down(mat, 12, PACK_TILESIZE(0, 1));
	shift_s(mat, 14, PACK_TILESIZE(0, 1));

};

void scroll_o_level_dl_o_spooky_sky() {
	scroll_o_spooky_sky_Sphere_001_mesh_vtx_0();
	scroll_gfx_mat_o_spooky_sky_dark_skybox_layer1();
};
