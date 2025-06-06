const Collision bc_golem_head_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(70),
	COL_VERTEX(0, 84, 47),
	COL_VERTEX(11, 87, 47),
	COL_VERTEX(0, 100, 34),
	COL_VERTEX(9, 98, 35),
	COL_VERTEX(0, 92, 16),
	COL_VERTEX(18, 88, 23),
	COL_VERTEX(32, 84, 37),
	COL_VERTEX(38, 12, 1),
	COL_VERTEX(52, 36, 14),
	COL_VERTEX(54, 16, 24),
	COL_VERTEX(34, 0, 19),
	COL_VERTEX(37, 18, 55),
	COL_VERTEX(25, 13, 75),
	COL_VERTEX(23, 60, 16),
	COL_VERTEX(40, 55, 30),
	COL_VERTEX(35, 48, 8),
	COL_VERTEX(35, 41, 32),
	COL_VERTEX(32, 30, 38),
	COL_VERTEX(0, 73, 48),
	COL_VERTEX(19, 72, 55),
	COL_VERTEX(29, 50, 46),
	COL_VERTEX(-32, 30, 38),
	COL_VERTEX(-29, 50, 46),
	COL_VERTEX(-35, 41, 32),
	COL_VERTEX(0, 69, 15),
	COL_VERTEX(0, 10, 77),
	COL_VERTEX(0, -2, 28),
	COL_VERTEX(-11, 87, 47),
	COL_VERTEX(-9, 98, 35),
	COL_VERTEX(-18, 88, 23),
	COL_VERTEX(-32, 84, 37),
	COL_VERTEX(-38, 12, 1),
	COL_VERTEX(-54, 16, 24),
	COL_VERTEX(-52, 36, 14),
	COL_VERTEX(-34, 0, 19),
	COL_VERTEX(-37, 18, 55),
	COL_VERTEX(-25, 13, 75),
	COL_VERTEX(-23, 60, 16),
	COL_VERTEX(-35, 48, 8),
	COL_VERTEX(-40, 55, 30),
	COL_VERTEX(-19, 72, 55),
	COL_VERTEX(21, 49, -28),
	COL_VERTEX(0, 54, -31),
	COL_VERTEX(0, 80, -18),
	COL_VERTEX(30, 71, -19),
	COL_VERTEX(0, 2, -38),
	COL_VERTEX(25, 26, -33),
	COL_VERTEX(25, 7, 20),
	COL_VERTEX(0, -17, 15),
	COL_VERTEX(-30, 24, -22),
	COL_VERTEX(-24, 52, -17),
	COL_VERTEX(-21, 49, -28),
	COL_VERTEX(-25, 26, -33),
	COL_VERTEX(24, 52, -17),
	COL_VERTEX(30, 24, -22),
	COL_VERTEX(0, 33, -40),
	COL_VERTEX(-25, 7, 20),
	COL_VERTEX(-36, 76, -12),
	COL_VERTEX(-30, 71, -19),
	COL_VERTEX(0, 85, -11),
	COL_VERTEX(36, 76, -12),
	COL_VERTEX(-30, 15, 4),
	COL_VERTEX(-24, 42, 10),
	COL_VERTEX(-36, 66, 14),
	COL_VERTEX(0, 76, 15),
	COL_VERTEX(36, 66, 14),
	COL_VERTEX(24, 42, 10),
	COL_VERTEX(30, 15, 4),
	COL_VERTEX(25, 15, -1),
	COL_VERTEX(-25, 15, -1),
	COL_TRI_INIT(SURFACE_FORCE_SHADOW_NOSLIP, 114),
	COL_TRI(0, 1, 2),
	COL_TRI(2, 3, 4),
	COL_TRI(1, 3, 2),
	COL_TRI(5, 4, 3),
	COL_TRI(1, 6, 3),
	COL_TRI(7, 8, 9),
	COL_TRI(10, 9, 11),
	COL_TRI(10, 7, 9),
	COL_TRI(10, 11, 12),
	COL_TRI(13, 14, 8),
	COL_TRI(13, 8, 15),
	COL_TRI(9, 8, 11),
	COL_TRI(16, 8, 14),
	COL_TRI(17, 8, 16),
	COL_TRI(8, 17, 11),
	COL_TRI(18, 19, 1),
	COL_TRI(18, 1, 0),
	COL_TRI(19, 6, 1),
	COL_TRI(3, 6, 5),
	COL_TRI(14, 13, 5),
	COL_TRI(14, 5, 6),
	COL_TRI(19, 20, 14),
	COL_TRI(19, 14, 6),
	COL_TRI(16, 14, 20),
	COL_TRI(21, 22, 23),
	COL_TRI(20, 17, 16),
	COL_TRI(5, 13, 4),
	COL_TRI(4, 13, 24),
	COL_TRI(7, 15, 8),
	COL_TRI(10, 12, 25),
	COL_TRI(10, 25, 26),
	COL_TRI(0, 2, 27),
	COL_TRI(2, 4, 28),
	COL_TRI(27, 2, 28),
	COL_TRI(29, 28, 4),
	COL_TRI(27, 28, 30),
	COL_TRI(31, 32, 33),
	COL_TRI(34, 35, 32),
	COL_TRI(34, 32, 31),
	COL_TRI(34, 36, 35),
	COL_TRI(37, 38, 33),
	COL_TRI(37, 33, 39),
	COL_TRI(32, 35, 33),
	COL_TRI(23, 39, 33),
	COL_TRI(21, 23, 33),
	COL_TRI(33, 35, 21),
	COL_TRI(11, 17, 20),
	COL_TRI(18, 0, 27),
	COL_TRI(18, 27, 40),
	COL_TRI(40, 27, 30),
	COL_TRI(28, 29, 30),
	COL_TRI(39, 30, 29),
	COL_TRI(39, 29, 37),
	COL_TRI(40, 30, 39),
	COL_TRI(40, 39, 22),
	COL_TRI(23, 22, 39),
	COL_TRI(21, 35, 22),
	COL_TRI(22, 35, 36),
	COL_TRI(22, 36, 40),
	COL_TRI(20, 19, 12),
	COL_TRI(20, 12, 11),
	COL_TRI(18, 25, 12),
	COL_TRI(18, 12, 19),
	COL_TRI(18, 40, 36),
	COL_TRI(18, 36, 25),
	COL_TRI(29, 4, 37),
	COL_TRI(4, 24, 37),
	COL_TRI(31, 33, 38),
	COL_TRI(34, 26, 25),
	COL_TRI(34, 25, 36),
	COL_TRI(41, 42, 43),
	COL_TRI(41, 43, 44),
	COL_TRI(45, 46, 47),
	COL_TRI(45, 47, 48),
	COL_TRI(49, 50, 51),
	COL_TRI(49, 51, 52),
	COL_TRI(53, 54, 46),
	COL_TRI(53, 46, 41),
	COL_TRI(55, 42, 41),
	COL_TRI(55, 41, 46),
	COL_TRI(46, 45, 55),
	COL_TRI(55, 52, 51),
	COL_TRI(55, 51, 42),
	COL_TRI(52, 55, 45),
	COL_TRI(52, 45, 48),
	COL_TRI(52, 48, 56),
	COL_TRI(51, 50, 57),
	COL_TRI(51, 57, 58),
	COL_TRI(59, 60, 44),
	COL_TRI(59, 44, 43),
	COL_TRI(57, 59, 43),
	COL_TRI(57, 43, 58),
	COL_TRI(42, 51, 58),
	COL_TRI(42, 58, 43),
	COL_TRI(53, 41, 44),
	COL_TRI(53, 44, 60),
	COL_TRI(50, 49, 61),
	COL_TRI(50, 61, 62),
	COL_TRI(57, 63, 64),
	COL_TRI(57, 64, 59),
	COL_TRI(59, 64, 65),
	COL_TRI(59, 65, 60),
	COL_TRI(50, 62, 63),
	COL_TRI(50, 63, 57),
	COL_TRI(53, 66, 67),
	COL_TRI(53, 67, 54),
	COL_TRI(60, 65, 66),
	COL_TRI(60, 66, 53),
	COL_TRI(46, 54, 67),
	COL_TRI(46, 67, 68),
	COL_TRI(49, 52, 69),
	COL_TRI(49, 69, 61),
	COL_TRI(31, 38, 15),
	COL_TRI(31, 15, 7),
	COL_TRI_STOP(),
	COL_END()
};
