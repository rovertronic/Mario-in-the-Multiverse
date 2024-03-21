Vtx e_door_light_door_light_mesh_vtx_cull[8] = {
	{{ {-478, 0, 27}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {-478, 0, 959}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {-478, 0, 959}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {-478, 0, 27}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {478, 0, 27}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {478, 0, 959}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {478, 0, 959}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {478, 0, 27}, 0, {-16, -16}, {0, 0, 0, 0} }},
};

Vtx e_door_light_door_light_mesh_vtx_0[4] = {
	{{ {-478, 0, 27}, 0, {-16, 1008}, {255, 255, 255, 255} }},
	{{ {-478, 0, 959}, 0, {-16, 1008}, {255, 255, 255, 255} }},
	{{ {478, 0, 959}, 0, {-16, 1008}, {255, 255, 255, 255} }},
	{{ {478, 0, 27}, 0, {-16, 1008}, {255, 255, 255, 255} }},
};

Gfx e_door_light_door_light_mesh_tri_0[] = {
	gsSPVertex(e_door_light_door_light_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_e_door_light_light_f3d_layer1[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, 1, 0, 0, 0, ENVIRONMENT, 0, 0, 0, 1, 0, 0, 0, ENVIRONMENT),
	gsSPGeometryMode(G_LIGHTING, 0),
	gsDPSetRenderMode(G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetEnvColor(255, 229, 187, 64),
	gsSPEndDisplayList(),
};

Gfx mat_revert_e_door_light_light_f3d_layer1[] = {
	gsDPPipeSync(),
	gsSPGeometryMode(0, G_LIGHTING),
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
	gsSPEndDisplayList(),
};

Gfx e_door_light_door_light_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(e_door_light_door_light_mesh_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_e_door_light_light_f3d_layer1),
	gsSPDisplayList(e_door_light_door_light_mesh_tri_0),
	gsSPDisplayList(mat_revert_e_door_light_light_f3d_layer1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

