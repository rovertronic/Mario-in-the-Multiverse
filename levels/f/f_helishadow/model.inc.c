Vtx f_helishadow_Plane_001_mesh_layer_5_vtx_0[21] = {
	{{ {50, 0, 444}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {-50, 0, 444}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {0, 0, 455}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {118, 0, 374}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {-50, 0, 444}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {50, 0, 444}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {-118, 0, 374}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {141, 0, 193}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {-141, 0, 193}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {121, 0, 25}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {-121, 0, 25}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {121, 0, -100}, 0, {1008, -16}, {0, 127, 0, 255} }},
	{{ {-121, 0, -100}, 0, {-16, -16}, {0, 127, 0, 255} }},
	{{ {56, 0, -356}, 0, {1008, -16}, {0, 127, 0, 255} }},
	{{ {-56, 0, -356}, 0, {-16, -16}, {0, 127, 0, 255} }},
	{{ {-39, 0, -356}, 0, {-16, -16}, {0, 127, 0, 255} }},
	{{ {39, 0, -356}, 0, {1008, -16}, {0, 127, 0, 255} }},
	{{ {32, 0, -899}, 0, {1008, -16}, {0, 127, 0, 255} }},
	{{ {-32, 0, -899}, 0, {-16, -16}, {0, 127, 0, 255} }},
	{{ {17, 0, -1083}, 0, {1008, -16}, {0, 127, 0, 255} }},
	{{ {-17, 0, -1083}, 0, {-16, -16}, {0, 127, 0, 255} }},
};

Gfx f_helishadow_Plane_001_mesh_layer_5_tri_0[] = {
	gsSPVertex(f_helishadow_Plane_001_mesh_layer_5_vtx_0 + 0, 21, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(3, 6, 4, 0, 7, 6, 3, 0),
	gsSP2Triangles(7, 8, 6, 0, 9, 8, 7, 0),
	gsSP2Triangles(9, 10, 8, 0, 10, 9, 11, 0),
	gsSP2Triangles(10, 11, 12, 0, 12, 11, 13, 0),
	gsSP2Triangles(12, 13, 14, 0, 15, 16, 17, 0),
	gsSP2Triangles(15, 17, 18, 0, 18, 17, 19, 0),
	gsSP1Triangle(18, 19, 20, 0),
	gsSPEndDisplayList(),
};


Gfx mat_f_helishadow_fakeshadow[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, 0, 0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, PRIMITIVE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 178),
	gsSPEndDisplayList(),
};

Gfx f_helishadow_Plane_001_mesh_layer_5[] = {
	gsSPDisplayList(mat_f_helishadow_fakeshadow),
	gsSPDisplayList(f_helishadow_Plane_001_mesh_layer_5_tri_0),
	gsSPEndDisplayList(),
};

Gfx f_helishadow_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

