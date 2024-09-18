Vtx k_lite_Plane_011_mesh_layer_6_vtx_0[8] = {
	{{ {-124, 0, 124}, 0, {82, 910}, {0, 127, 0, 83} }},
	{{ {-200, 0, -200}, 0, {-16, -16}, {0, 127, 0, 0} }},
	{{ {-200, 0, 200}, 0, {-16, 1008}, {0, 127, 0, 0} }},
	{{ {-124, 0, -124}, 0, {82, 82}, {0, 127, 0, 47} }},
	{{ {124, 0, -124}, 0, {910, 82}, {0, 127, 0, 83} }},
	{{ {124, 0, 124}, 0, {910, 910}, {0, 127, 0, 83} }},
	{{ {200, 0, 200}, 0, {1008, 1008}, {0, 127, 0, 0} }},
	{{ {200, 0, -200}, 0, {1008, -16}, {0, 127, 0, 0} }},
};

Gfx k_lite_Plane_011_mesh_layer_6_tri_0[] = {
	gsSPVertex(k_lite_Plane_011_mesh_layer_6_vtx_0 + 0, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(0, 4, 3, 0),
	gsSP1Triangle(0, 5, 4, 0),
	gsSP1Triangle(5, 0, 2, 0),
	gsSP1Triangle(5, 2, 6, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(3, 4, 7, 0),
	gsSP1Triangle(3, 7, 1, 0),
	gsSPEndDisplayList(),
};


Gfx mat_k_lite_redlite[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, ENVIRONMENT, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, ENVIRONMENT, 0, SHADE, 0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 0, 26, 255),
	gsSPEndDisplayList(),
};

Gfx k_lite_Plane_011_mesh_layer_6[] = {
	gsSPDisplayList(mat_k_lite_redlite),
	gsSPDisplayList(k_lite_Plane_011_mesh_layer_6_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

