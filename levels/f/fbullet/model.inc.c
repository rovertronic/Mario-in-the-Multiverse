Vtx fbullet_Cube_mesh_vtx_0[16] = {
	{{ {-11, 0, 4}, 0, {368, 1008}, {255, 226, 166, 255} }},
	{{ {0, 17, -85}, 0, {624, 752}, {83, 69, 46, 0} }},
	{{ {-17, 0, -85}, 0, {368, 752}, {83, 69, 46, 0} }},
	{{ {0, 11, 4}, 0, {624, 1008}, {255, 226, 166, 255} }},
	{{ {0, 0, 15}, 0, {624, 1008}, {255, 252, 202, 255} }},
	{{ {11, 0, 4}, 0, {624, 240}, {255, 226, 166, 255} }},
	{{ {0, 11, 4}, 0, {880, 240}, {255, 226, 166, 255} }},
	{{ {0, 0, 15}, 0, {624, 240}, {255, 252, 202, 255} }},
	{{ {17, 0, -85}, 0, {624, 496}, {183, 162, 118, 0} }},
	{{ {0, -17, -85}, 0, {368, 496}, {83, 69, 46, 0} }},
	{{ {0, -11, 4}, 0, {368, 240}, {255, 226, 166, 255} }},
	{{ {0, 0, 15}, 0, {368, 240}, {255, 252, 202, 255} }},
	{{ {-17, 0, -85}, 0, {112, 496}, {83, 69, 46, 0} }},
	{{ {-11, 0, 4}, 0, {112, 240}, {255, 226, 166, 255} }},
	{{ {0, 0, 15}, 0, {112, 240}, {255, 252, 202, 255} }},
	{{ {0, 17, -85}, 0, {880, 496}, {83, 69, 46, 0} }},
};

Gfx fbullet_Cube_mesh_tri_0[] = {
	gsSPVertex(fbullet_Cube_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(3, 0, 4, 0),
	gsSP1Triangle(5, 6, 7, 0),
	gsSP1Triangle(8, 6, 5, 0),
	gsSP1Triangle(9, 8, 5, 0),
	gsSP1Triangle(9, 5, 10, 0),
	gsSP1Triangle(10, 5, 11, 0),
	gsSP1Triangle(12, 9, 10, 0),
	gsSP1Triangle(12, 10, 13, 0),
	gsSP1Triangle(13, 10, 14, 0),
	gsSP1Triangle(8, 15, 6, 0),
	gsSPEndDisplayList(),
};

Gfx mat_fbullet_muzzle_flash[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE),
	gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_fbullet_muzzle_flash[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK | G_LIGHTING),
	gsSPEndDisplayList(),
};

Gfx fbullet_Cube_mesh[] = {
	gsSPDisplayList(mat_fbullet_muzzle_flash),
	gsSPDisplayList(fbullet_Cube_mesh_tri_0),
	gsSPDisplayList(mat_revert_fbullet_muzzle_flash),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

