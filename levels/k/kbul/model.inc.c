Vtx kbul_kbul_mesh_vtx_0[8] = {
	{{ {-10, 0, 100}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {10, 0, 100}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {10, 0, -100}, 0, {1008, -16}, {0, 127, 0, 0} }},
	{{ {-10, 0, -100}, 0, {-16, -16}, {0, 127, 0, 0} }},
	{{ {0, 10, 100}, 0, {-16, 1008}, {127, 0, 0, 255} }},
	{{ {0, -10, 100}, 0, {1008, 1008}, {127, 0, 0, 255} }},
	{{ {0, -10, -100}, 0, {1008, -16}, {127, 0, 0, 49} }},
	{{ {0, 10, -100}, 0, {-16, -16}, {127, 0, 0, 0} }},
};

Gfx kbul_kbul_mesh_tri_0[] = {
	gsSPVertex(kbul_kbul_mesh_vtx_0 + 0, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSPEndDisplayList(),
};

Gfx mat_kbul_bullet[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, SHADE, 0, 0, 0, PRIMITIVE, 0, 0, 0, SHADE),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 211, 0, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_kbul_bullet[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx kbul_kbul_mesh[] = {
	gsSPDisplayList(mat_kbul_bullet),
	gsSPDisplayList(kbul_kbul_mesh_tri_0),
	gsSPDisplayList(mat_revert_kbul_bullet),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

