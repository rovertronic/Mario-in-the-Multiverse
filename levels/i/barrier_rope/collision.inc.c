const Collision barrier_rope_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(8),
	COL_VERTEX(-1015, 0, 50),
	COL_VERTEX(1015, 0, 50),
	COL_VERTEX(1015, 418, 50),
	COL_VERTEX(1015, 0, -50),
	COL_VERTEX(1015, 418, -50),
	COL_VERTEX(-1015, 418, 50),
	COL_VERTEX(-1015, 0, -50),
	COL_VERTEX(-1015, 418, -50),
	COL_TRI_INIT(SURFACE_DEFAULT, 12),
	COL_TRI(0, 1, 2),
	COL_TRI(3, 4, 2),
	COL_TRI(3, 2, 1),
	COL_TRI(2, 5, 0),
	COL_TRI(4, 6, 7),
	COL_TRI(6, 4, 3),
	COL_TRI(6, 3, 1),
	COL_TRI(6, 1, 0),
	COL_TRI(7, 6, 0),
	COL_TRI(7, 0, 5),
	COL_TRI(4, 7, 5),
	COL_TRI(4, 5, 2),
	COL_TRI_STOP(),
	COL_END()
};
