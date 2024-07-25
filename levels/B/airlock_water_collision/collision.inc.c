const Collision airlock_water_collision_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(4),
	COL_VERTEX(-989, 748, -534),
	COL_VERTEX(989, 748, -534),
	COL_VERTEX(989, 748, 534),
	COL_VERTEX(-989, 748, 534),
	COL_TRI_INIT(SURFACE_NEW_WATER, 2),
	COL_TRI(0, 1, 2),
	COL_TRI(0, 2, 3),
	COL_TRI_STOP(),
	COL_END()
};
