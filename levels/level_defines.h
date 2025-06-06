// Define lists for list of level for macros. Each of the following fields are described:
// Argument 1: Internal ROM name of the level.
// Argument 2: Level enumerator for enum used to identify the level ID.
// Argument 3: Course enumerator for enum used to identify the course ID.
// Argument 4: Shorthand name of the level which should be the name of the levels/ folder of the level.
// Argument 5: The shared texture bin used.
// Argument 6: Acoustic reaches for each levels.
// Argument 7, 8, 9: Echo levels for individual areas.  < Clueless hackers should change these for their levels btw
// Argument 10: Specify dynamic music tables for levels, if specified. _ for none.
// Argument 11: Specify level camera table, if specified. _ for none.

// NOTE: Be sure to edit sZoomOutAreaMasks in camera.c, as there isnt a good way to macro those right now.
// TODO: Figure something out for sZoomOutAreaMasks?

STUB_LEVEL("", LEVEL_UNKNOWN_1, COURSE_NONE, 20000, 0x00, 0x00, 0x00, _, _) 
STUB_LEVEL("", LEVEL_UNKNOWN_2, COURSE_NONE, 20000, 0x00, 0x00, 0x00, _, _) 
STUB_LEVEL("", LEVEL_UNKNOWN_3, COURSE_NONE, 20000, 0x00, 0x00, 0x00, _, _) 
DEFINE_LEVEL("COURSE 5 BBH", LEVEL_BBH, COURSE_NONE, bbh, spooky, 28000, 0x28, 0x28, 0x28, sDynBbh, sCamBBH) 
DEFINE_LEVEL("COURSE 4 CCM", LEVEL_CCM, COURSE_NONE, ccm, snow, 17000, 0x10, 0x38, 0x38, _, sCamCCM) 
DEFINE_LEVEL("OW2 IN CASTLE", LEVEL_CASTLE, COURSE_BITFS, castle_inside, inside, 20000, 0x00, 0x00, 0x00, _, sCamCastle) 
DEFINE_LEVEL("COURSE 6 HMC", LEVEL_HMC, COURSE_NONE, hmc, cave, 16000, 0x28, 0x28, 0x28, sDynHmc, sCamHMC) 
DEFINE_LEVEL("COURSE 8 SSL", LEVEL_SSL, COURSE_NONE, ssl, generic, 15000, 0x08, 0x30, 0x30, _, sCamSSL) 
DEFINE_LEVEL("COURSE 1 BOB", LEVEL_BOB, COURSE_NONE, bob, generic, 15000, 0x08, 0x08, 0x08, _, _) 
DEFINE_LEVEL("COURSE 10 SL", LEVEL_SL, COURSE_NONE, sl, snow, 14000, 0x10, 0x28, 0x28, _, sCamSL) 
DEFINE_LEVEL("COURSE 11 WDW", LEVEL_WDW, COURSE_NONE, wdw, grass, 17000, 0x10, 0x18, 0x18, sDynWdw, _) 
DEFINE_LEVEL("COURSE 3 JRB", LEVEL_JRB, COURSE_NONE, jrb, water, 20000, 0x10, 0x18, 0x18, sDynJrb, _) 
DEFINE_LEVEL("COURSE 13 THI", LEVEL_THI, COURSE_NONE, thi, grass, 20000, 0x0c, 0x0c, 0x20, _, sCamTHI) 
DEFINE_LEVEL("COURSE 14 TTC", LEVEL_TTC, COURSE_NONE, ttc, machine, 18000, 0x18, 0x18, 0x18, _, _) 
DEFINE_LEVEL("COURSE 15 RR", LEVEL_RR, COURSE_NONE, rr, sky, 20000, 0x20, 0x20, 0x20, _, sCamRR) 
DEFINE_LEVEL("OW1 C GROUNDS", LEVEL_CASTLE_GROUNDS, COURSE_NONE, castle_grounds, outside, 25000, 0x08, 0x08, 0x08, _, _) 
DEFINE_LEVEL("BC1 BITDW", LEVEL_BITDW, COURSE_BITDW, bitdw, sky, 16000, 0x28, 0x28, 0x28, _, _) 
DEFINE_LEVEL("VCL VCUTM", LEVEL_VCUTM, COURSE_VCUTM, vcutm, outside, 30000, 0x28, 0x28, 0x28, _, _) 
DEFINE_LEVEL("BC2 BITFS", LEVEL_BITFS, COURSE_BITFS, bitfs, sky, 16000, 0x28, 0x28, 0x28, _, _) 
DEFINE_LEVEL("SC1 SEC AQUA", LEVEL_SA, COURSE_SA, sa, inside, 20000, 0x10, 0x10, 0x10, _, _) 
DEFINE_LEVEL("BC3 BITS", LEVEL_BITS, COURSE_BITS, bits, sky, 16000, 0x28, 0x28, 0x28, _, _) 
DEFINE_LEVEL("COURSE 7 LLL", LEVEL_LLL, COURSE_NONE, lll, fire, 22000, 0x08, 0x30, 0x30, _, _) 
DEFINE_LEVEL("COURSE 9 DDD", LEVEL_DDD, COURSE_NONE, ddd, water, 17000, 0x10, 0x20, 0x20, sDynDdd, _) 
DEFINE_LEVEL("COURSE 2 WF", LEVEL_WF, COURSE_NONE, wf, grass, 13000, 0x08, 0x08, 0x08, _, _) 
DEFINE_LEVEL("END CAKE", LEVEL_ENDING, COURSE_CAKE_END, ending, generic, 20000, 0x00, 0x00, 0x00, _, _) 
DEFINE_LEVEL("OW3 C COURTYD", LEVEL_CASTLE_COURTYARD, COURSE_NONE, castle_courtyard, outside, 20000, 0x08, 0x08, 0x08, _, _) 
DEFINE_LEVEL("SIC P SEC SLID", LEVEL_PSS, COURSE_PSS, pss, mountain, 20000, 0x28, 0x28, 0x28, _, _) 
DEFINE_LEVEL("MCL COTMC", LEVEL_COTMC, COURSE_COTMC, cotmc, cave, 18000, 0x28, 0x28, 0x28, _, sCamCotMC) 
DEFINE_LEVEL("WCL TOTWC", LEVEL_TOTWC, COURSE_TOTWC, totwc, sky, 20000, 0x20, 0x20, 0x20, _, _) 
DEFINE_LEVEL("B BATTLE1", LEVEL_BOWSER_1, COURSE_BITDW, bowser_1, generic, 60000, 0x40, 0x40, 0x40, _, _) 
DEFINE_LEVEL("SC2 WMOTR", LEVEL_WMOTR, COURSE_WMOTR, wmotr, generic, 20000, 0x28, 0x28, 0x28, _, _) 
STUB_LEVEL("", LEVEL_UNKNOWN_32, COURSE_NONE, 20000, 0x70, 0x00, 0x00, _, _) 
DEFINE_LEVEL("B BATTLE2", LEVEL_BOWSER_2, COURSE_BITFS, bowser_2, fire, 60000, 0x40, 0x40, 0x40, _, _) 
DEFINE_LEVEL("B BATTLE3", LEVEL_BOWSER_3, COURSE_BITS, bowser_3, generic, 60000, 0x40, 0x40, 0x40, _, _) 
STUB_LEVEL("", LEVEL_UNKNOWN_35, COURSE_NONE, 20000, 0x00, 0x00, 0x00, _, _) 
DEFINE_LEVEL("COURSE 12 TTM", LEVEL_TTM, COURSE_NONE, ttm, mountain, 15000, 0x08, 0x08, 0x08, _, _) 
STUB_LEVEL("", LEVEL_UNKNOWN_37, COURSE_NONE, 20000, 0x00, 0x00, 0x00, _, _) 
STUB_LEVEL("", LEVEL_UNKNOWN_38, COURSE_NONE, 20000, 0x00, 0x00, 0x00, sDynUnk38, _) 
DEFINE_LEVEL("INK_TEST", LEVEL_INK_TEST, COURSE_INK_TEST, ink_test, generic, 20000, 0x00, 0x00, 0x00, _, sCamInkTest) 
DEFINE_LEVEL("X", LEVEL_X, COURSE_X, x, generic, 20000, 0x00, 0x00, 0x00, _, sCamX) 
DEFINE_LEVEL("G", LEVEL_G, COURSE_BOB, g, generic, 20000, 0x00, 0x00, 0x00, _, sCamG) 
DEFINE_LEVEL("B", LEVEL_B, COURSE_HMC, B, generic, 20000, 0x00, 0x00, 0x00, _, sCamB) 
DEFINE_LEVEL("A", LEVEL_A, COURSE_WF, a, generic, 20000, 0x00, 0x00, 0x00, _, sCamA) 
DEFINE_LEVEL("F", LEVEL_F, COURSE_SL, f, generic, 20000, 0x00, 0x00, 0x00, _, sCamF) 
DEFINE_LEVEL("E", LEVEL_E, COURSE_DDD, e, generic, 20000, 0x00, 0x00, 0x00, _, sCamE) 
DEFINE_LEVEL("I", LEVEL_I, COURSE_CCM, i, generic, 20000, 0x00, 0x00, 0x00, _, sCamI) 
DEFINE_LEVEL("J", LEVEL_J, COURSE_WDW, J, generic, 20000, 0x00, 0x00, 0x00, _, sCamJ) 
DEFINE_LEVEL("M", LEVEL_M, COURSE_RR, m, generic, 20000, 0x00, 0x00, 0x00, _, sCamM) 
DEFINE_LEVEL("O", LEVEL_O, COURSE_THI, o, generic, 20000, 0x00, 0x00, 0x00, _, sCamO) 
DEFINE_LEVEL("D", LEVEL_D, COURSE_TTM, d, generic, 20000, 0x00, 0x00, 0x01, _, sCamD) 
DEFINE_LEVEL("N", LEVEL_N, COURSE_TTC, n, generic, 20000, 0x00, 0x00, 0x00, _, sCamN) 
DEFINE_LEVEL("H", LEVEL_H, COURSE_BBH, h, generic, 20000, 0x00, 0x00, 0x00, _, sCamH) 
DEFINE_LEVEL("C", LEVEL_C, COURSE_JRB, c, generic, 20000, 0x00, 0x00, 0x00, _, sCamC) 
DEFINE_LEVEL("BIRTHDAY", LEVEL_BIRTHDAY, COURSE_NONE, birthday, generic, 20000, 0x00, 0x00, 0x00, _, sCamBirthday) 
DEFINE_LEVEL("L", LEVEL_L, COURSE_LLL, l, generic, 20000, 0x00, 0x00, 0x00, _, sCamL) 
DEFINE_LEVEL("BOWSER_COURSE", LEVEL_BOWSER_COURSE, COURSE_BITDW, bowser_course, generic, 20000, 0x00, 0x00, 0x00, _, sCamBowserCourse) 
DEFINE_LEVEL("K", LEVEL_K, COURSE_SSL, k, generic, 20000, 0x00, 0x00, 0x00, _, sCamK) 
DEFINE_LEVEL("SB", LEVEL_SB, COURSE_NONE, sb, generic, 20000, 0x00, 0x00, 0x00, _, sCamSb) 
DEFINE_LEVEL("MC", LEVEL_MC, COURSE_PSS, mc, generic, 20000, 0x00, 0x00, 0x00, _, sCamMc) 
DEFINE_LEVEL("BB", LEVEL_BB, COURSE_WMOTR, bb, generic, 20000, 0x00, 0x00, 0x00, _, sCamBb) 