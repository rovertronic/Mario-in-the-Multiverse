Vtx bd_shine_Circle_mesh_layer_5_vtx_0[9] = {
	{{ {0, 0, 0}, 0, {-16, 1008}, {255, 255, 255, 255} }},
	{{ {0, 100, 0}, 0, {-16, 1008}, {255, 255, 255, 0} }},
	{{ {-71, 71, 0}, 0, {-16, 1008}, {255, 255, 255, 0} }},
	{{ {71, 71, 0}, 0, {-16, 1008}, {255, 255, 255, 0} }},
	{{ {100, 0, 0}, 0, {-16, 1008}, {255, 255, 255, 0} }},
	{{ {71, -71, 0}, 0, {-16, 1008}, {255, 255, 255, 1} }},
	{{ {0, -100, 0}, 0, {-16, 1008}, {255, 255, 255, 0} }},
	{{ {-71, -71, 0}, 0, {-16, 1008}, {255, 255, 255, 0} }},
	{{ {-100, 0, 0}, 0, {-16, 1008}, {255, 255, 255, 0} }},
};

Gfx bd_shine_Circle_mesh_layer_5_tri_0[] = {
	gsSPVertex(bd_shine_Circle_mesh_layer_5_vtx_0 + 0, 9, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(0, 4, 3, 0),
	gsSP1Triangle(0, 5, 4, 0),
	gsSP1Triangle(0, 6, 5, 0),
	gsSP1Triangle(0, 7, 6, 0),
	gsSP1Triangle(0, 8, 7, 0),
	gsSP1Triangle(0, 2, 8, 0),
	gsSPEndDisplayList(),
};


Gfx mat_bd_shine_shimmer[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, ENVIRONMENT, 0, SHADE, 0, 0, 0, 0, SHADE, ENVIRONMENT, 0, SHADE, 0),
	gsSPClearGeometryMode(G_ZBUFFER | G_LIGHTING),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_bd_shine_shimmer[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_ZBUFFER | G_LIGHTING),
	gsSPEndDisplayList(),
};

Gfx bd_shine_Circle_mesh_layer_5[] = {
	gsSPDisplayList(mat_bd_shine_shimmer),
	gsSPDisplayList(bd_shine_Circle_mesh_layer_5_tri_0),
	gsSPDisplayList(mat_revert_bd_shine_shimmer),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

