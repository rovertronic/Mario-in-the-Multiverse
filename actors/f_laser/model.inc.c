Vtx f_laser_Plane_mesh_layer_1_vtx_0[8] = {
	{{ {-7, 0, 106}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {7, 0, 106}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {7, 0, 0}, 0, {1008, -16}, {0, 127, 0, 255} }},
	{{ {-7, 0, 0}, 0, {-16, -16}, {0, 127, 0, 255} }},
	{{ {0, 7, 106}, 0, {-16, 1008}, {127, 0, 0, 255} }},
	{{ {0, -7, 106}, 0, {1008, 1008}, {127, 0, 0, 255} }},
	{{ {0, -7, 0}, 0, {1008, -16}, {127, 0, 0, 255} }},
	{{ {0, 7, 0}, 0, {-16, -16}, {127, 0, 0, 255} }},
};

Gfx f_laser_Plane_mesh_layer_1_tri_0[] = {
	gsSPVertex(f_laser_Plane_mesh_layer_1_vtx_0 + 0, 8, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSPEndDisplayList(),
};


Gfx mat_f_laser_laser[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 1, 0, 0, 0, PRIMITIVE, 0, 0, 0, 1),
	gsSPGeometryMode(G_CULL_BACK, 0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 0, 0, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_f_laser_laser[] = {
	gsDPPipeSync(),
	gsSPGeometryMode(0, G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx f_laser_Plane_mesh_layer_1[] = {
	gsSPDisplayList(mat_f_laser_laser),
	gsSPDisplayList(f_laser_Plane_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_revert_f_laser_laser),
	gsSPEndDisplayList(),
};

Gfx f_laser_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

