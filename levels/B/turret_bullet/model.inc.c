Vtx turret_bullet_turret_bullet_mesh_layer_7_vtx_0[7] = {
	{{ {0, 0, -64}, 0, {-16, 1008}, {255, 204, 34, 255} }},
	{{ {17, 5, 7}, 0, {-16, 1008}, {255, 204, 34, 255} }},
	{{ {10, -14, 7}, 0, {-16, 1008}, {255, 204, 34, 255} }},
	{{ {0, 17, 7}, 0, {-16, 1008}, {255, 204, 34, 255} }},
	{{ {-17, 5, 7}, 0, {-16, 1008}, {255, 204, 34, 255} }},
	{{ {-10, -14, 7}, 0, {-16, 1008}, {255, 204, 34, 255} }},
	{{ {0, 0, 28}, 0, {-16, 1008}, {255, 204, 34, 255} }},
};

Gfx turret_bullet_turret_bullet_mesh_layer_7_tri_0[] = {
	gsSPVertex(turret_bullet_turret_bullet_mesh_layer_7_vtx_0 + 0, 7, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(0, 4, 3, 0),
	gsSP1Triangle(0, 5, 4, 0),
	gsSP1Triangle(0, 2, 5, 0),
	gsSP1Triangle(5, 2, 6, 0),
	gsSP1Triangle(2, 1, 6, 0),
	gsSP1Triangle(1, 3, 6, 0),
	gsSP1Triangle(3, 4, 6, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSPEndDisplayList(),
};


Gfx mat_turret_bullet_f3dlite_material_layer7[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPClearGeometryMode(G_LIGHTING),
	gsDPSetRenderMode(G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_turret_bullet_f3dlite_material_layer7[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsDPSetRenderMode(G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2),
	gsSPEndDisplayList(),
};

Gfx turret_bullet_turret_bullet_mesh_layer_7[] = {
	gsSPDisplayList(mat_turret_bullet_f3dlite_material_layer7),
	gsSPDisplayList(turret_bullet_turret_bullet_mesh_layer_7_tri_0),
	gsSPDisplayList(mat_revert_turret_bullet_f3dlite_material_layer7),
	gsSPEndDisplayList(),
};

Gfx turret_bullet_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

