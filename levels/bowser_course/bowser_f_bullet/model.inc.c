Vtx bowser_f_bullet_Cube_mesh_vtx_cull[8] = {
	{{ {-17, -17, -85}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {-17, -17, 15}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {-17, 17, 15}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {-17, 17, -85}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {17, -17, -85}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {17, -17, 15}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {17, 17, 15}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {17, 17, -85}, 0, {-16, -16}, {0, 0, 0, 0} }},
};

Vtx bowser_f_bullet_Cube_mesh_vtx_0[16] = {
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

Gfx bowser_f_bullet_Cube_mesh_tri_0[] = {
	gsSPVertex(bowser_f_bullet_Cube_mesh_vtx_0 + 0, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(3, 0, 4, 0, 5, 6, 7, 0),
	gsSP2Triangles(8, 6, 5, 0, 9, 8, 5, 0),
	gsSP2Triangles(9, 5, 10, 0, 10, 5, 11, 0),
	gsSP2Triangles(12, 9, 10, 0, 12, 10, 13, 0),
	gsSP2Triangles(13, 10, 14, 0, 8, 15, 6, 0),
	gsSPEndDisplayList(),
};

Gfx mat_bowser_f_bullet_muzzle_flash[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE),
	gsSPGeometryMode(G_CULL_BACK | G_LIGHTING, 0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_bowser_f_bullet_muzzle_flash[] = {
	gsDPPipeSync(),
	gsSPGeometryMode(0, G_CULL_BACK | G_LIGHTING),
	gsSPEndDisplayList(),
};

Gfx bowser_f_bullet_Cube_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(bowser_f_bullet_Cube_mesh_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_bowser_f_bullet_muzzle_flash),
	gsSPDisplayList(bowser_f_bullet_Cube_mesh_tri_0),
	gsSPDisplayList(mat_revert_bowser_f_bullet_muzzle_flash),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

