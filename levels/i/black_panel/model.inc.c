
Vtx black_panel_Plane_mesh_layer_1_vtx_0[4] = {
	{{ {-1159, -1159, 0}, 0, {-16, 1008}, {0, 0, 127, 255} }},
	{{ {1159, -1159, 0}, 0, {1008, 1008}, {0, 0, 127, 255} }},
	{{ {1159, 1159, 0}, 0, {1008, -16}, {0, 0, 127, 255} }},
	{{ {-1159, 1159, 0}, 0, {-16, -16}, {0, 0, 127, 255} }},
};

Gfx black_panel_Plane_mesh_layer_1_tri_0[] = {
	gsSPVertex(black_panel_Plane_mesh_layer_1_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};


Gfx mat_black_panel_f3dlite_material_001[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLightColor(LIGHT_1, 0xff),
    gsSPLightColor(LIGHT_2, 0xff),
	gsSPEndDisplayList(),
};

Gfx black_panel_Plane_mesh_layer_1[] = {
	gsSPDisplayList(mat_black_panel_f3dlite_material_001),
	gsSPDisplayList(black_panel_Plane_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx black_panel_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

