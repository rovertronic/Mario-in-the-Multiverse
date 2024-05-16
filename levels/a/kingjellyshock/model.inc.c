Vtx kingjellyshock_Circle_mesh_layer_5_vtx_0[16] = {
	{{ {-100, 0, 0}, 0, {-16, 1008}, {249, 255, 0, 0} }},
	{{ {-34, 6, -34}, 0, {-16, 1008}, {249, 255, 0, 138} }},
	{{ {-71, 0, -71}, 0, {-16, 1008}, {249, 255, 0, 0} }},
	{{ {-48, 6, 0}, 0, {-16, 1008}, {249, 255, 0, 138} }},
	{{ {-71, 0, 71}, 0, {-16, 1008}, {249, 255, 0, 0} }},
	{{ {-34, 6, 34}, 0, {-16, 1008}, {249, 255, 0, 138} }},
	{{ {0, 0, 100}, 0, {-16, 1008}, {249, 255, 0, 0} }},
	{{ {0, 6, 48}, 0, {-16, 1008}, {249, 255, 0, 138} }},
	{{ {71, 0, 71}, 0, {-16, 1008}, {249, 255, 0, 0} }},
	{{ {34, 6, 34}, 0, {-16, 1008}, {249, 255, 0, 138} }},
	{{ {100, 0, 0}, 0, {-16, 1008}, {249, 255, 0, 0} }},
	{{ {48, 6, 0}, 0, {-16, 1008}, {249, 255, 0, 138} }},
	{{ {71, 0, -71}, 0, {-16, 1008}, {249, 255, 0, 0} }},
	{{ {34, 6, -34}, 0, {-16, 1008}, {249, 255, 0, 138} }},
	{{ {0, 0, -100}, 0, {-16, 1008}, {249, 255, 0, 0} }},
	{{ {0, 6, -48}, 0, {-16, 1008}, {249, 255, 0, 138} }},
};

Gfx kingjellyshock_Circle_mesh_layer_5_tri_0[] = {
	gsSPVertex(kingjellyshock_Circle_mesh_layer_5_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 3, 0, 0),
	gsSP1Triangle(4, 5, 3, 0),
	gsSP1Triangle(6, 5, 4, 0),
	gsSP1Triangle(6, 7, 5, 0),
	gsSP1Triangle(8, 7, 6, 0),
	gsSP1Triangle(8, 9, 7, 0),
	gsSP1Triangle(10, 9, 8, 0),
	gsSP1Triangle(10, 11, 9, 0),
	gsSP1Triangle(12, 11, 10, 0),
	gsSP1Triangle(12, 13, 11, 0),
	gsSP1Triangle(14, 13, 12, 0),
	gsSP1Triangle(14, 15, 13, 0),
	gsSP1Triangle(2, 15, 14, 0),
	gsSP1Triangle(2, 1, 15, 0),
	gsSP1Triangle(15, 1, 3, 0),
	gsSP1Triangle(15, 3, 7, 0),
	gsSP1Triangle(3, 5, 7, 0),
	gsSP1Triangle(7, 11, 15, 0),
	gsSP1Triangle(7, 9, 11, 0),
	gsSP1Triangle(11, 13, 15, 0),
	gsSPEndDisplayList(),
};


Gfx mat_kingjellyshock_f3dlite_material_001[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(SHADE, 0, SHADE, 0, SHADE, 0, PRIMITIVE, 0, SHADE, 0, SHADE, 0, SHADE, 0, PRIMITIVE, 0),
	gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_kingjellyshock_f3dlite_material_001[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK | G_LIGHTING),
	gsSPEndDisplayList(),
};

Gfx kingjellyshock_Circle_mesh_layer_5[] = {
	gsSPDisplayList(mat_kingjellyshock_f3dlite_material_001),
	gsSPDisplayList(kingjellyshock_Circle_mesh_layer_5_tri_0),
	gsSPDisplayList(mat_revert_kingjellyshock_f3dlite_material_001),
	gsSPEndDisplayList(),
};

Gfx kingjellyshock_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

