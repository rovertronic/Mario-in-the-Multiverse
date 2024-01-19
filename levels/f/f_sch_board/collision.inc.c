const Collision f_sch_board_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(4),
	COL_VERTEX(0, 179, 305),
	COL_VERTEX(0, 179, -310),
	COL_VERTEX(0, -179, -308),
	COL_VERTEX(0, -179, 307),
	COL_TRI_INIT(SURFACE_DEFAULT, 2),
	COL_TRI(0, 1, 2),
	COL_TRI(0, 2, 3),
	COL_TRI_STOP(),
	COL_END()
};
