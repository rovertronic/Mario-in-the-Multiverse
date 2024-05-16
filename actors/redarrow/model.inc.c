Vtx redarrow_Plane_mesh_layer_1_vtx_0[4] = {
	{{ {0, 52, 211}, 0, {496, 1008}, {255, 255, 255, 255} }},
	{{ {100, 52, 69}, 0, {1008, -16}, {255, 255, 255, 255} }},
	{{ {0, 52, 138}, 0, {496, -16}, {255, 255, 255, 255} }},
	{{ {-100, 52, 69}, 0, {-16, 1008}, {255, 255, 255, 255} }},
};

Gfx redarrow_Plane_mesh_layer_1_tri_0[] = {
	gsSPVertex(redarrow_Plane_mesh_layer_1_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
	gsSPEndDisplayList(),
};


Gfx mat_redarrow_red[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, PRIMITIVE, 0, 0, 0, ENVIRONMENT),
	gsSPGeometryMode(G_CULL_BACK | G_LIGHTING, 0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 0, 0, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_redarrow_red[] = {
	gsDPPipeSync(),
	gsSPGeometryMode(0, G_CULL_BACK | G_LIGHTING),
	gsSPEndDisplayList(),
};

Gfx redarrow_Plane_mesh_layer_1[] = {
	gsSPDisplayList(mat_redarrow_red),
	gsSPDisplayList(redarrow_Plane_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_revert_redarrow_red),
	gsSPEndDisplayList(),
};

Gfx redarrow_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

