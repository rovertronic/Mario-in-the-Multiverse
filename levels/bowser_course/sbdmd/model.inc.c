
Vtx sbdmd_diamond_mesh_vtx_0[14] = {
	{{ {-54, 0, 0}, 0, {368, 880}, {129, 0, 0, 255} }},
	{{ {0, 27, 0}, 0, {624, 880}, {0, 127, 0, 255} }},
	{{ {0, 0, -153}, 0, {368, 752}, {0, 0, 129, 255} }},
	{{ {0, 0, 153}, 0, {624, 1008}, {0, 0, 127, 255} }},
	{{ {0, -27, 0}, 0, {368, 368}, {0, 129, 0, 255} }},
	{{ {54, 0, 0}, 0, {624, 368}, {127, 0, 0, 255} }},
	{{ {0, 0, 153}, 0, {368, 240}, {0, 0, 127, 255} }},
	{{ {0, 0, -153}, 0, {624, 496}, {0, 0, 129, 255} }},
	{{ {-54, 0, 0}, 0, {112, 368}, {129, 0, 0, 255} }},
	{{ {0, 0, 153}, 0, {112, 240}, {0, 0, 127, 255} }},
	{{ {0, 0, -153}, 0, {368, 496}, {0, 0, 129, 255} }},
	{{ {0, 27, 0}, 0, {880, 368}, {0, 127, 0, 255} }},
	{{ {0, 0, 153}, 0, {624, 240}, {0, 0, 127, 255} }},
	{{ {0, 0, -153}, 0, {880, 496}, {0, 0, 129, 255} }},
};

Gfx sbdmd_diamond_mesh_tri_0[] = {
	gsSPVertex(sbdmd_diamond_mesh_vtx_0 + 0, 14, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 1, 0, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(7, 5, 4, 0),
	gsSP1Triangle(8, 4, 9, 0),
	gsSP1Triangle(10, 4, 8, 0),
	gsSP1Triangle(5, 11, 12, 0),
	gsSP1Triangle(13, 11, 5, 0),
	gsSPEndDisplayList(),
};

Gfx mat_sbdmd_f3dlite_material_001[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLightColor(LIGHT_1, 0xffffffff),
    gsSPLightColor(LIGHT_2, 0x7f7f7fff),
	gsSPEndDisplayList(),
};

Gfx sbdmd_diamond_mesh[] = {
	gsSPDisplayList(mat_sbdmd_f3dlite_material_001),
	gsSPDisplayList(sbdmd_diamond_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

