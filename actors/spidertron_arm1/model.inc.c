Vtx spidertron_arm1_Cube_mesh_layer_1_vtx_0[24] = {
	{{ {10, 10, -600}, 0, {624, 496}, {0, 127, 0, 255} }},
	{{ {-10, 10, -600}, 0, {880, 496}, {0, 127, 0, 255} }},
	{{ {-10, 10, 0}, 0, {880, 240}, {0, 127, 0, 255} }},
	{{ {10, 10, 0}, 0, {624, 240}, {0, 127, 0, 255} }},
	{{ {10, -10, 0}, 0, {368, 240}, {0, 0, 127, 255} }},
	{{ {10, 10, 0}, 0, {624, 240}, {0, 0, 127, 255} }},
	{{ {-10, 10, 0}, 0, {624, -16}, {0, 0, 127, 255} }},
	{{ {-10, -10, 0}, 0, {368, -16}, {0, 0, 127, 255} }},
	{{ {-10, -10, 0}, 0, {368, 1008}, {129, 0, 0, 255} }},
	{{ {-10, 10, 0}, 0, {624, 1008}, {129, 0, 0, 255} }},
	{{ {-10, 10, -600}, 0, {624, 752}, {129, 0, 0, 255} }},
	{{ {-10, -10, -600}, 0, {368, 752}, {129, 0, 0, 255} }},
	{{ {-10, -10, -600}, 0, {112, 496}, {0, 129, 0, 255} }},
	{{ {10, -10, -600}, 0, {368, 496}, {0, 129, 0, 255} }},
	{{ {10, -10, 0}, 0, {368, 240}, {0, 129, 0, 255} }},
	{{ {-10, -10, 0}, 0, {112, 240}, {0, 129, 0, 255} }},
	{{ {10, -10, -600}, 0, {368, 496}, {127, 0, 0, 255} }},
	{{ {10, 10, -600}, 0, {624, 496}, {127, 0, 0, 255} }},
	{{ {10, 10, 0}, 0, {624, 240}, {127, 0, 0, 255} }},
	{{ {10, -10, 0}, 0, {368, 240}, {127, 0, 0, 255} }},
	{{ {-10, -10, -600}, 0, {368, 752}, {0, 0, 129, 255} }},
	{{ {-10, 10, -600}, 0, {624, 752}, {0, 0, 129, 255} }},
	{{ {10, 10, -600}, 0, {624, 496}, {0, 0, 129, 255} }},
	{{ {10, -10, -600}, 0, {368, 496}, {0, 0, 129, 255} }},
};

Gfx spidertron_arm1_Cube_mesh_layer_1_tri_0[] = {
	gsSPVertex(spidertron_arm1_Cube_mesh_layer_1_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(spidertron_arm1_Cube_mesh_layer_1_vtx_0 + 16, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSPEndDisplayList(),
};


Gfx mat_spidertron_arm1_f3dlite_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 1, 0, 0, 0, PRIMITIVE, 0, 0, 0, 1),
	gsSPClearGeometryMode(G_SHADE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 30, 16, 3, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_spidertron_arm1_f3dlite_material[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_SHADE),
	gsSPEndDisplayList(),
};

Gfx spidertron_arm1_Cube_mesh_layer_1[] = {
	gsSPDisplayList(mat_spidertron_arm1_f3dlite_material),
	gsSPDisplayList(spidertron_arm1_Cube_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_revert_spidertron_arm1_f3dlite_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

