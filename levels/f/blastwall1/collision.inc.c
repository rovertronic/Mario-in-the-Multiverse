const Collision blastwall1_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(4),
	COL_VERTEX(-126, 569, 98),
	COL_VERTEX(-126, -111, 98),
	COL_VERTEX(586, -111, 98),
	COL_VERTEX(586, 569, 98),
	COL_TRI_INIT(SURFACE_DEFAULT, 2),
	COL_TRI(0, 1, 2),
	COL_TRI(0, 2, 3),
	COL_TRI_STOP(),
	COL_END()
};
