#ifndef MODEL_IDS_H
#define MODEL_IDS_H

#define MODEL_NONE                             0x00

/* Global models that are loaded for every level */

#define MODEL_MARIO                            0x01        // mario_geo
#define MODEL_LUIGI                            0x02        // unused

/* Various static level geometry, the geo layout differs but terrain object presets treat them the same.*/

#define MODEL_LEVEL_GEOMETRY_03                0x03
#define MODEL_LEVEL_GEOMETRY_04                0x04
#define MODEL_LEVEL_GEOMETRY_05                0x05
#define MODEL_LEVEL_GEOMETRY_06                0x06
#define MODEL_LEVEL_GEOMETRY_07                0x07
#define MODEL_LEVEL_GEOMETRY_08                0x08
#define MODEL_LEVEL_GEOMETRY_09                0x09
#define MODEL_LEVEL_GEOMETRY_0A                0x0A
#define MODEL_LEVEL_GEOMETRY_0B                0x0B
#define MODEL_LEVEL_GEOMETRY_0C                0x0C
#define MODEL_LEVEL_GEOMETRY_0D                0x0D
#define MODEL_LEVEL_GEOMETRY_0E                0x0E
#define MODEL_LEVEL_GEOMETRY_0F                0x0F
#define MODEL_LEVEL_GEOMETRY_10                0x10
#define MODEL_LEVEL_GEOMETRY_11                0x11
#define MODEL_LEVEL_GEOMETRY_12                0x12
#define MODEL_LEVEL_GEOMETRY_13                0x13
#define MODEL_LEVEL_GEOMETRY_14                0x14
#define MODEL_LEVEL_GEOMETRY_15                0x15
#define MODEL_LEVEL_GEOMETRY_16                0x16

#define MODEL_BOB_BUBBLY_TREE                  0x17        // bubbly_tree_geo
#define MODEL_WDW_BUBBLY_TREE                  0x17        // bubbly_tree_geo
#define MODEL_CASTLE_GROUNDS_BUBBLY_TREE       0x17        // bubbly_tree_geo
#define MODEL_WF_BUBBLY_TREE                   0x17        // bubbly_tree_geo
#define MODEL_THI_BUBBLY_TREE                  0x17        // bubbly_tree_geo
#define MODEL_COURTYARD_SPIKY_TREE             0x18        // spiky_tree_geo
#define MODEL_CCM_SNOW_TREE                    0x19        // snow_tree_geo
#define MODEL_SL_SNOW_TREE                     0x19        // snow_tree_geo
#define MODEL_UNKNOWN_TREE_1A                  0x1A        // referenced in special presets, undefined
#define MODEL_SSL_PALM_TREE                    0x1B        // palm_tree_geo
#define MODEL_CASTLE_CASTLE_DOOR_UNUSED        0x1C        // castle_door_geo - unused, original id
#define MODEL_CASTLE_WOODEN_DOOR_UNUSED        0x1D        // wooden_door_geo - unused, original id
#define MODEL_BBH_HAUNTED_DOOR                 0x1D        // haunted_door_geo
#define MODEL_HMC_WOODEN_DOOR                  0x1D        // wooden_door_geo
#define MODEL_UNKNOWN_DOOR_1E                  0x1E        // referenced in special presets, undefined
#define MODEL_HMC_METAL_DOOR                   0x1F        // metal_door_geo
#define MODEL_HMC_HAZY_MAZE_DOOR               0x20        // hazy_maze_door_geo
#define MODEL_UNKNOWN_DOOR_21                  0x21        // referenced in special presets, undefined
#define MODEL_CASTLE_DOOR_0_STARS              0x22        // castle_door_0_star_geo
#define MODEL_CASTLE_DOOR_1_STAR               0x23        // castle_door_1_star_geo
#define MODEL_CASTLE_DOOR_3_STARS              0x24        // castle_door_3_stars_geo
#define MODEL_CASTLE_KEY_DOOR                  0x25        // key_door_geo
#define MODEL_CASTLE_CASTLE_DOOR               0x26        // castle_door_geo - used duplicate
#define MODEL_CASTLE_GROUNDS_CASTLE_DOOR       0x26        // castle_door_geo - used duplicate
#define MODEL_CASTLE_WOODEN_DOOR               0x27        // wooden_door_geo
#define MODEL_COURTYARD_WOODEN_DOOR            0x27        // wooden_door_geo
#define MODEL_CCM_CABIN_DOOR                   0x27        // cabin_door_geo
#define MODEL_UNKNOWN_DOOR_28                  0x28        // referenced in special presets, undefined
#define MODEL_CASTLE_METAL_DOOR                0x29        // metal_door_geo
#define MODEL_CASTLE_GROUNDS_METAL_DOOR        0x29        // metal_door_geo
#define MODEL_UNKNOWN_DOOR_2A                  0x2A        // referenced in special presets, undefined
#define MODEL_UNKNOWN_DOOR_2B                  0x2B        // referenced in special presets, undefined
#define MODEL_WF_TOWER_TRAPEZOID_PLATORM       0x2C        // wf_geo_000AF8 - unused
#define MODEL_WF_TOWER_SQUARE_PLATORM          0x2D        // wf_geo_000B10
#define MODEL_WF_TOWER_SQUARE_PLATORM_UNUSED   0x2E        // wf_geo_000B38 - unused & duplicated
#define MODEL_WF_TOWER_SQUARE_PLATORM_ELEVATOR 0x2F        // wf_geo_000B60 - elevator platorm

// Level model IDs

// bbh
#define MODEL_BBH_STAIRCASE_STEP               0x35        // geo_bbh_0005B0
#define MODEL_BBH_TILTING_FLOOR_PLATFORM       0x36        // geo_bbh_0005C8
#define MODEL_BBH_TUMBLING_PLATFORM            0x37        // geo_bbh_0005E0
#define MODEL_BBH_TUMBLING_PLATFORM_PART       0x38        // geo_bbh_0005F8
#define MODEL_BBH_MOVING_BOOKSHELF             0x39        // geo_bbh_000610
#define MODEL_BBH_MESH_ELEVATOR                0x3A        // geo_bbh_000628
#define MODEL_BBH_MERRY_GO_ROUND               0x3B        // geo_bbh_000640
#define MODEL_BBH_WOODEN_TOMB                  0x3C        // geo_bbh_000658

// ccm
#define MODEL_CCM_ROPEWAY_LIFT                 0x36        // ccm_geo_0003D0
#define MODEL_CCM_SNOWMAN_HEAD                 0x37        // ccm_geo_00040C

// castle
#define MODEL_CASTLE_BOWSER_TRAP               0x35        // castle_geo_000F18
#define MODEL_CASTLE_WATER_LEVEL_PILLAR        0x36        // castle_geo_001940
#define MODEL_CASTLE_CLOCK_MINUTE_HAND         0x37        // castle_geo_001530
#define MODEL_CASTLE_CLOCK_HOUR_HAND           0x38        // castle_geo_001548
#define MODEL_CASTLE_CLOCK_PENDULUM            0x39        // castle_geo_001518

// hmc
#define MODEL_HMC_METAL_PLATFORM               0x36        // hmc_geo_0005A0
#define MODEL_HMC_METAL_ARROW_PLATFORM         0x37        // hmc_geo_0005B8
#define MODEL_HMC_ELEVATOR_PLATFORM            0x38        // hmc_geo_0005D0
#define MODEL_HMC_ROLLING_ROCK                 0x39        // hmc_geo_000548
#define MODEL_HMC_ROCK_PIECE                   0x3A        // hmc_geo_000570 - unused
#define MODEL_HMC_ROCK_SMALL_PIECE             0x3B        // hmc_geo_000588 - unused
#define MODEL_HMC_RED_GRILLS                   0x3C        // hmc_geo_000530

// ssl
#define MODEL_SSL_PYRAMID_TOP                  0x3A        // ssl_geo_000618
#define MODEL_SSL_GRINDEL                      0x36        // ssl_geo_000734
#define MODEL_SSL_SPINDEL                      0x37        // ssl_geo_000764
#define MODEL_SSL_MOVING_PYRAMID_WALL          0x38        // ssl_geo_000794
#define MODEL_SSL_PYRAMID_ELEVATOR             0x39        // ssl_geo_0007AC

// bob
#define MODEL_BOB_CHAIN_CHOMP_GATE             0x36        // bob_geo_000440
#define MODEL_BOB_SEESAW_PLATFORM              0x37        // bob_geo_000458
#define MODEL_BOB_BARS_GRILLS                  0x38        // bob_geo_000470

// sl
#define MODEL_SL_SNOW_TRIANGLE                 0x36        // sl_geo_000390
#define MODEL_SL_CRACKED_ICE                   0x37        // sl_geo_000360 - unused
#define MODEL_SL_CRACKED_ICE_CHUNK             0x38        // sl_geo_000378 - unused

// wdw
#define MODEL_WDW_SQUARE_FLOATING_PLATFORM        0x36        // wdw_geo_000580
#define MODEL_WDW_ARROW_LIFT                      0x37        // wdw_geo_000598
#define MODEL_WDW_WATER_LEVEL_DIAMOND             0x38        // wdw_geo_0005C0
#define MODEL_WDW_HIDDEN_PLATFORM                 0x39        // wdw_geo_0005E8
#define MODEL_WDW_EXPRESS_ELEVATOR                0x3A        // wdw_geo_000610
#define MODEL_WDW_RECTANGULAR_FLOATING_PLATFORM   0x3B        // wdw_geo_000628
#define MODEL_WDW_ROTATING_PLATFORM               0x3C        // wdw_geo_000640

// jrb
#define MODEL_JRB_SHIP_LEFT_HALF_PART             0x35        // jrb_geo_000978
#define MODEL_JRB_SHIP_BACK_LEFT_PART             0x36        // jrb_geo_0009B0
#define MODEL_JRB_SHIP_RIGHT_HALF_PART            0x37        // jrb_geo_0009E8
#define MODEL_JRB_SHIP_BACK_RIGHT_PART            0x38        // jrb_geo_000A00
#define MODEL_JRB_SUNKEN_SHIP                     0x39        // jrb_geo_000990
#define MODEL_JRB_SUNKEN_SHIP_BACK                0x3A        // jrb_geo_0009C8
#define MODEL_JRB_ROCK                            0x3B        // jrb_geo_000930
#define MODEL_JRB_SLIDING_BOX                     0x3C        // jrb_geo_000960
#define MODEL_JRB_FALLING_PILLAR                  0x3D        // jrb_geo_000900
#define MODEL_JRB_FALLING_PILLAR_BASE             0x3E        // jrb_geo_000918
#define MODEL_JRB_FLOATING_PLATFORM               0x3F        // jrb_geo_000948

// thi
#define MODEL_THI_HUGE_ISLAND_TOP                 0x36        // thi_geo_0005B0
#define MODEL_THI_TINY_ISLAND_TOP                 0x37        // thi_geo_0005C8

// ttc
#define MODEL_TTC_ROTATING_CUBE                   0x36        // ttc_geo_000240
#define MODEL_TTC_ROTATING_PRISM                  0x37        // ttc_geo_000258
#define MODEL_TTC_PENDULUM                        0x38        // ttc_geo_000270
#define MODEL_TTC_LARGE_TREADMILL                 0x39        // ttc_geo_000288
#define MODEL_TTC_SMALL_TREADMILL                 0x3A        // ttc_geo_0002A8
#define MODEL_TTC_PUSH_BLOCK                      0x3B        // ttc_geo_0002C8
#define MODEL_TTC_ROTATING_HEXAGON                0x3C        // ttc_geo_0002E0
#define MODEL_TTC_ROTATING_TRIANGLE               0x3D        // ttc_geo_0002F8
#define MODEL_TTC_PIT_BLOCK                       0x3E        // ttc_geo_000310 - has 2 vertical stripes
#define MODEL_TTC_PIT_BLOCK_UNUSED                0x3F        // ttc_geo_000328 - has 3 vertical stripes, unused
#define MODEL_TTC_ELEVATOR_PLATFORM               0x40        // ttc_geo_000340
#define MODEL_TTC_CLOCK_HAND                      0x41        // ttc_geo_000358
#define MODEL_TTC_SPINNER                         0x42        // ttc_geo_000370
#define MODEL_TTC_SMALL_GEAR                      0x43        // ttc_geo_000388
#define MODEL_TTC_LARGE_GEAR                      0x44        // ttc_geo_0003A0

// rr
#define MODEL_RR_SLIDING_PLATFORM                 0x36        // rr_geo_0008C0
#define MODEL_RR_FLYING_CARPET                    0x37        // rr_geo_000848
#define MODEL_RR_OCTAGONAL_PLATFORM               0x38        // rr_geo_0008A8
#define MODEL_RR_ROTATING_BRIDGE_PLATFORM         0x39        // rr_geo_000878
#define MODEL_RR_TRIANGLE_PLATFORM                0x3A        // rr_geo_0008D8 - unused
#define MODEL_RR_CRUISER_WING                     0x3B        // rr_geo_000890
#define MODEL_RR_SEESAW_PLATFORM                  0x3C        // rr_geo_000908
#define MODEL_RR_L_SHAPED_PLATFORM                0x3D        // rr_geo_000940 - unused
#define MODEL_RR_SWINGING_PLATFORM                0x3E        // rr_geo_000860
#define MODEL_RR_DONUT_PLATFORM                   0x3F        // rr_geo_000920
#define MODEL_RR_ELEVATOR_PLATFORM                0x40        // rr_geo_0008F0
#define MODEL_RR_TRICKY_TRIANGLES                 0x41        // rr_geo_000958
#define MODEL_RR_TRICKY_TRIANGLES_FRAME1          0x42        // rr_geo_000970
#define MODEL_RR_TRICKY_TRIANGLES_FRAME2          0x43        // rr_geo_000988
#define MODEL_RR_TRICKY_TRIANGLES_FRAME3          0x44        // rr_geo_0009A0
#define MODEL_RR_TRICKY_TRIANGLES_FRAME4          0x45        // rr_geo_0009B8

// castle grounds

// bitdw
#define MODEL_BITDW_SQUARE_PLATFORM               0x36        // geo_bitdw_000558
#define MODEL_BITDW_SEESAW_PLATFORM               0x37        // geo_bitdw_000540
#define MODEL_BITDW_SLIDING_PLATFORM              0x38        // geo_bitdw_000528
#define MODEL_BITDW_FERRIS_WHEEL_AXLE             0x39        // geo_bitdw_000570
#define MODEL_BITDW_BLUE_PLATFORM                 0x3A        // geo_bitdw_000588
#define MODEL_BITDW_STAIRCASE_FRAME4              0x3B        // geo_bitdw_0005A0
#define MODEL_BITDW_STAIRCASE_FRAME3              0x3C        // geo_bitdw_0005B8
#define MODEL_BITDW_STAIRCASE_FRAME2              0x3D        // geo_bitdw_0005D0
#define MODEL_BITDW_STAIRCASE_FRAME1              0x3E        // geo_bitdw_0005E8
#define MODEL_BITDW_STAIRCASE                     0x3F        // geo_bitdw_000600

// vcutm
#define MODEL_VCUTM_SEESAW_PLATFORM               0x36        // vcutm_geo_0001F0

// bitfs
#define MODEL_BITFS_PLATFORM_ON_TRACK             0x36        // bitfs_geo_000758
#define MODEL_BITFS_TILTING_SQUARE_PLATFORM       0x37        // bitfs_geo_0006C0
#define MODEL_BITFS_SINKING_PLATFORMS             0x38        // bitfs_geo_000770
#define MODEL_BITFS_BLUE_POLE                     0x39        // bitfs_geo_0006A8
#define MODEL_BITFS_SINKING_CAGE_PLATFORM         0x3A        // bitfs_geo_000690
#define MODEL_BITFS_ELEVATOR                      0x3B        // bitfs_geo_000678
#define MODEL_BITFS_STRETCHING_PLATFORMS          0x3C        // bitfs_geo_000708
#define MODEL_BITFS_SEESAW_PLATFORM               0x3D        // bitfs_geo_000788
#define MODEL_BITFS_MOVING_SQUARE_PLATFORM        0x3E        // bitfs_geo_000728
#define MODEL_BITFS_SLIDING_PLATFORM              0x3F        // bitfs_geo_000740
#define MODEL_BITFS_TUMBLING_PLATFORM_PART        0x40        // bitfs_geo_0006D8
#define MODEL_BITFS_TUMBLING_PLATFORM             0x41        // bitfs_geo_0006F0

// sa

// bits
#define MODEL_BITS_SLIDING_PLATFORM               0x36        // bits_geo_0005E0
#define MODEL_BITS_TWIN_SLIDING_PLATFORMS         0x37        // bits_geo_0005F8
#define MODEL_BITS_OCTAGONAL_PLATFORM             0x39        // bits_geo_000610
#define MODEL_BITS_BLUE_PLATFORM                  0x3C        // bits_geo_000628
#define MODEL_BITS_FERRIS_WHEEL_AXLE              0x3D        // bits_geo_000640
#define MODEL_BITS_ARROW_PLATFORM                 0x3E        // bits_geo_000658
#define MODEL_BITS_SEESAW_PLATFORM                0x3F        // bits_geo_000670
#define MODEL_BITS_TILTING_W_PLATFORM             0x40        // bits_geo_000688
#define MODEL_BITS_STAIRCASE                      0x41        // bits_geo_0006A0
#define MODEL_BITS_STAIRCASE_FRAME1               0x42        // bits_geo_0006B8
#define MODEL_BITS_STAIRCASE_FRAME2               0x43        // bits_geo_0006D0
#define MODEL_BITS_STAIRCASE_FRAME3               0x44        // bits_geo_0006E8
#define MODEL_BITS_STAIRCASE_FRAME4               0x45        // bits_geo_000700
#define MODEL_BITS_WARP_PIPE                      0x49        // warp_pipe_geo

// lll
#define MODEL_LLL_DRAWBRIDGE_PART                 0x38        // lll_geo_000B20
#define MODEL_LLL_ROTATING_BLOCK_FIRE_BARS        0x3A        // lll_geo_000B38
#define MODEL_LLL_ROTATING_HEXAGONAL_RING         0x3E        // lll_geo_000BB0
#define MODEL_LLL_SINKING_RECTANGULAR_PLATFORM    0x3F        // lll_geo_000BC8
#define MODEL_LLL_SINKING_SQUARE_PLATFORMS        0x40        // lll_geo_000BE0
#define MODEL_LLL_TILTING_SQUARE_PLATFORM         0x41        // lll_geo_000BF8
#define MODEL_LLL_BOWSER_PIECE_1                  0x43        // lll_geo_bowser_puzzle_piece_1
#define MODEL_LLL_BOWSER_PIECE_2                  0x44        // lll_geo_bowser_puzzle_piece_2
#define MODEL_LLL_BOWSER_PIECE_3                  0x45        // lll_geo_bowser_puzzle_piece_3
#define MODEL_LLL_BOWSER_PIECE_4                  0x46        // lll_geo_bowser_puzzle_piece_4
#define MODEL_LLL_BOWSER_PIECE_5                  0x47        // lll_geo_bowser_puzzle_piece_5
#define MODEL_LLL_BOWSER_PIECE_6                  0x48        // lll_geo_bowser_puzzle_piece_6
#define MODEL_LLL_BOWSER_PIECE_7                  0x49        // lll_geo_bowser_puzzle_piece_7
#define MODEL_LLL_BOWSER_PIECE_8                  0x4A        // lll_geo_bowser_puzzle_piece_8
#define MODEL_LLL_BOWSER_PIECE_9                  0x4B        // lll_geo_bowser_puzzle_piece_9
#define MODEL_LLL_BOWSER_PIECE_10                 0x4C        // lll_geo_bowser_puzzle_piece_10
#define MODEL_LLL_BOWSER_PIECE_11                 0x4D        // lll_geo_bowser_puzzle_piece_11
#define MODEL_LLL_BOWSER_PIECE_12                 0x4E        // lll_geo_bowser_puzzle_piece_12
#define MODEL_LLL_BOWSER_PIECE_13                 0x4F        // lll_geo_bowser_puzzle_piece_13
#define MODEL_LLL_BOWSER_PIECE_14                 0x50        // lll_geo_bowser_puzzle_piece_14
#define MODEL_LLL_MOVING_OCTAGONAL_MESH_PLATFORM  0x36        // lll_geo_000B08
#define MODEL_LLL_SINKING_ROCK_BLOCK              0x37        // lll_geo_000DD0
#define MODEL_LLL_ROLLING_LOG                     0x39        // lll_geo_000DE8
#define MODEL_LLL_WOOD_BRIDGE                     0x35        // lll_geo_000B50
#define MODEL_LLL_LARGE_WOOD_BRIDGE               0x3B        // lll_geo_000B68
#define MODEL_LLL_FALLING_PLATFORM                0x3C        // lll_geo_000B80
#define MODEL_LLL_LARGE_FALLING_PLATFORM          0x3D        // lll_geo_000B98
#define MODEL_LLL_VOLCANO_FALLING_TRAP            0x53        // lll_geo_000EA8

// ddd
#define MODEL_DDD_BOWSER_SUB_DOOR                 0x36        // ddd_geo_000478
#define MODEL_DDD_BOWSER_SUB                      0x37        // ddd_geo_0004A0
#define MODEL_DDD_POLE                            0x38        // ddd_geo_000450

// wf
#define MODEL_WF_BREAKABLE_WALL_RIGHT             0x36        // wf_geo_000B78
#define MODEL_WF_BREAKABLE_WALL_LEFT              0x37        // wf_geo_000B90
#define MODEL_WF_KICKABLE_BOARD                   0x38        // wf_geo_000BA8
#define MODEL_WF_TOWER_DOOR                       0x39        // wf_geo_000BE0
#define MODEL_WF_KICKABLE_BOARD_FELLED            0x3A        // wf_geo_000BC8

// ending

// castle grounds
#define MODEL_CASTLE_GROUNDS_VCUTM_GRILL          0x36        // castle_grounds_geo_00070C
#define MODEL_CASTLE_GROUNDS_FLAG                 0x37        // castle_grounds_geo_000660
#define MODEL_CASTLE_GROUNDS_CANNON_GRILL         0x38        // castle_grounds_geo_000724

// pss

// cotmc

// totwc

// bowser 1

// wmotr

// bowser 2
#define MODEL_BOWSER_2_TILTING_ARENA              0x36        // bowser_2_geo_000170

// bowser 3
#define MODEL_BOWSER_3_FALLING_PLATFORM_1         0x36        // bowser_3_geo_000290
#define MODEL_BOWSER_3_FALLING_PLATFORM_2         0x37        // bowser_3_geo_0002A8
#define MODEL_BOWSER_3_FALLING_PLATFORM_3         0x38        // bowser_3_geo_0002C0
#define MODEL_BOWSER_3_FALLING_PLATFORM_4         0x39        // bowser_3_geo_0002D8
#define MODEL_BOWSER_3_FALLING_PLATFORM_5         0x3A        // bowser_3_geo_0002F0
#define MODEL_BOWSER_3_FALLING_PLATFORM_6         0x3B        // bowser_3_geo_000308
#define MODEL_BOWSER_3_FALLING_PLATFORM_7         0x3C        // bowser_3_geo_000320
#define MODEL_BOWSER_3_FALLING_PLATFORM_8         0x3D        // bowser_3_geo_000338
#define MODEL_BOWSER_3_FALLING_PLATFORM_9         0x3E        // bowser_3_geo_000350
#define MODEL_BOWSER_3_FALLING_PLATFORM_10        0x3F        // bowser_3_geo_000368

// ttm
#define MODEL_TTM_ROLLING_LOG                     0x35        // ttm_geo_000730
#define MODEL_TTM_STAR_CAGE                       0x36        // ttm_geo_000710
#define MODEL_TTM_BLUE_SMILEY                     0x37        // ttm_geo_000D14
#define MODEL_TTM_YELLOW_SMILEY                   0x38        // ttm_geo_000D4C
#define MODEL_TTM_STAR_SMILEY                     0x39        // ttm_geo_000D84
#define MODEL_TTM_MOON_SMILEY                     0x3A        // ttm_geo_000DBC

// actor model IDs

// first set of actor bins (0x54-0x63)
// group 1
#define MODEL_BULLET_BILL                 0x54        // bullet_bill_geo
#define MODEL_YELLOW_SPHERE               0x55        // yellow_sphere_geo
#define MODEL_HOOT                        0x56        // hoot_geo
#define MODEL_YOSHI_EGG                   0x57        // yoshi_egg_geo
#define MODEL_THWOMP                      0x58        // thwomp_geo
#define MODEL_HEAVE_HO                    0x59        // heave_ho_geo

// group 2
#define MODEL_BLARGG                      0x54        // blargg_geo
#define MODEL_BULLY                       0x56        // bully_geo
#define MODEL_BULLY_BOSS                  0x57        // bully_boss_geo

// group 3
#define MODEL_WATER_BOMB                  0x54        // water_bomb_geo
#define MODEL_WATER_BOMB_SHADOW           0x55        // water_bomb_shadow_geo
#define MODEL_KING_BOBOMB                 0x56        // king_bobomb_geo

// group 4
#define MODEL_MANTA_RAY                   0x54        // manta_seg5_geo_05008D14
#define MODEL_UNAGI                       0x55        // unagi_geo
#define MODEL_SUSHI                       0x56        // sushi_geo
#define MODEL_DL_WHIRLPOOL                0x57        // whirlpool_seg5_dl_05013CB8
#define MODEL_CLAM_SHELL                  0x58        // clam_shell_geo

// group 5
#define MODEL_POKEY_HEAD                  0x54        // pokey_head_geo
#define MODEL_POKEY_BODY_PART             0x55        // pokey_body_part_geo
#define MODEL_TWEESTER                    0x56        // tweester_geo
#define MODEL_KLEPTO                      0x57        // klepto_geo
#define MODEL_EYEROK_LEFT_HAND            0x58        // eyerok_left_hand_geo
#define MODEL_EYEROK_RIGHT_HAND           0x59        // eyerok_right_hand_geo

// group 6
#define MODEL_DL_MONTY_MOLE_HOLE          0x54        // monty_mole_hole_seg5_dl_05000840
#define MODEL_MONTY_MOLE                  0x55        // monty_mole_geo
#define MODEL_UKIKI                       0x56        // ukiki_geo
#define MODEL_FWOOSH                      0x57        // fwoosh_geo

// group 7
#define MODEL_SPINDRIFT                   0x54        // spindrift_geo
#define MODEL_MR_BLIZZARD_HIDDEN          0x55        // mr_blizzard_hidden_geo
#define MODEL_MR_BLIZZARD                 0x56        // mr_blizzard_geo
#define MODEL_PENGUIN                     0x57        // penguin_geo

// group 8
#define MODEL_CAP_SWITCH_EXCLAMATION      0x54        // cap_switch_exclamation_seg5_dl_05002E00
#define MODEL_CAP_SWITCH                  0x55        // cap_switch_geo
#define MODEL_CAP_SWITCH_BASE             0x56        // cap_switch_base_seg5_dl_05003120

// group 9
#define MODEL_BOO                         0x54        // boo_geo
#define MODEL_BETA_BOO_KEY                0x55        // small_key_geo
#define MODEL_HAUNTED_CHAIR               0x56        // haunted_chair_geo
#define MODEL_MAD_PIANO                   0x57        // mad_piano_geo
#define MODEL_BOOKEND_PART                0x58        // bookend_part_geo
#define MODEL_BOOKEND                     0x59        // bookend_geo
#define MODEL_HAUNTED_CAGE                0x5A        // haunted_cage_geo

// group 10
#define MODEL_BIRDS                       0x54        // birds_geo
#define MODEL_YOSHI                       0x55        // yoshi_geo

// group 11
#define MODEL_ENEMY_LAKITU                0x54        // enemy_lakitu_geo
#define MODEL_SPINY_BALL                  0x55        // spiny_ball_geo
#define MODEL_SPINY                       0x56        // spiny_geo
#define MODEL_WIGGLER_HEAD                0x57        // wiggler_head_geo
#define MODEL_WIGGLER_BODY                0x58        // wiggler_body_geo
#define MODEL_BUBBA                       0x59        // bubba_geo

// referenced in macro presets. Unknown usage.
#define MODEL_UNKNOWN_54                  0x54
#define MODEL_UNKNOWN_58                  0x58

// second set of actor bins, (0x64-0x73)
// group 12
#define MODEL_BOWSER                      0x64        // bowser_geo
#define MODEL_BOWSER_BOMB_CHILD_OBJ       0x65        // bowser_bomb_geo - Spawns as a chill object in bowser's behavior command, causing an explosion if it touches a bomb
#define MODEL_BOWSER_SMOKE                0x66        // bowser_impact_smoke_geo
#define MODEL_BOWSER_FLAMES               0x67        // bowser_flames_geo
#define MODEL_BOWSER_WAVE                 0x68        // invisible_bowser_accessory_geo
#define MODEL_BOWSER_NO_SHADOW            0x69        // bowser_geo_no_shadow

// group 13
#define MODEL_BUB                         0x64        // cheep_cheep_geo
#define MODEL_TREASURE_CHEST_BASE         0x65        // treasure_chest_base_geo
#define MODEL_TREASURE_CHEST_LID          0x66        // treasure_chest_lid_geo
#define MODEL_CYAN_FISH                   0x67        // cyan_fish_geo
#define MODEL_WATER_RING                  0x68        // water_ring_geo
#define MODEL_SKEETER                     0x69        // skeeter_geo

// group 14
#define MODEL_PIRANHA_PLANT               0x64        // piranha_plant_geo
#define MODEL_WHOMP                       0x67        // whomp_geo
#define MODEL_KOOPA_WITH_SHELL            0x68        // koopa_with_shell_geo
#define MODEL_METALLIC_BALL               0x65        // metallic_ball_geo
#define MODEL_CHAIN_CHOMP                 0x66        // chain_chomp
#define MODEL_KOOPA_FLAG                  0x6A        // koopa_flag_geo
#define MODEL_WOODEN_POST                 0x6B        // wooden_post_geo

// group 15
#define MODEL_MIPS                        0x64        // mips_geo
#define MODEL_BOO_CASTLE                  0x65        // boo_castle_geo
#define MODEL_LAKITU                      0x66        // lakitu_geo

// group 16
#define MODEL_CHILL_BULLY                 0x64        // chilly_chief_geo
#define MODEL_BIG_CHILL_BULLY             0x65        // chilly_chief_big_geo
#define MODEL_MONEYBAG                    0x66        // moneybag_geo

// group 17
#define MODEL_SWOOP                       0x64        // swoop_geo
#define MODEL_SCUTTLEBUG                  0x65        // scuttlebug_geo
#define MODEL_MR_I_IRIS                   0x66        // mr_i_iris_geo
#define MODEL_MR_I_BODY                   0x67        // mr_i_geo
#define MODEL_MR_I MODEL_MR_I_BODY // backwards compatibility
#define MODEL_DORRIE                      0x68        // dorrie_geo

// other models
#define MODEL_YELLOW_COIN                 0x74        // yellow_coin_geo
#define MODEL_YELLOW_COIN_NO_SHADOW       0x75        // yellow_coin_no_shadow_geo
#define MODEL_BLUE_COIN                   0x76        // blue_coin_geo
#define MODEL_BLUE_COIN_NO_SHADOW         0x77        // blue_coin_no_shadow_geo
#define MODEL_HEART                       0x78        // heart_geo
#define MODEL_TRANSPARENT_STAR            0x79        // transparent_star_geo
#define MODEL_STAR                        0x7A        // star_geo
#define MODEL_TTM_SLIDE_EXIT_PODIUM       0x7B        // ttm_geo_000DF4
#define MODEL_WOODEN_SIGNPOST             0x7C        // wooden_signpost_geo
#define MODEL_UNKNOWN_7D                  0x7D        // referenced in macro presets. Unknown usage
#define MODEL_ABILITY_HEART               0x7E        // heart_geo
// find me
#define MODEL_CANNON_BARREL               0x7F        // cannon_barrel_geo
#define MODEL_CANNON_BASE                 0x80        // cannon_base_geo
#define MODEL_BREAKABLE_BOX               0x81        // breakable_box_geo
#define MODEL_BREAKABLE_BOX_NO_SHADOW     0x82        // breakable_box_no_shadow_geo
#define MODEL_BREAKABLE_BOX_SMALL MODEL_BREAKABLE_BOX_NO_SHADOW // backwards compatibility
#define MODEL_EXCLAMATION_BOX_OUTLINE     0x83        // exclamation_box_outline_geo
#define MODEL_EXCLAMATION_POINT           0x84        // exclamation_point_seg8_dl_08025F08
#define MODEL_MARIOS_WINGED_METAL_CAP     0x85        // marios_winged_metal_cap_geo
#define MODEL_MARIOS_METAL_CAP            0x86        // marios_metal_cap_geo
#define MODEL_MARIOS_WING_CAP             0x87        // marios_wing_cap_geo
#define MODEL_MARIOS_CAP                  0x88        // marios_cap_geo
#define MODEL_EXCLAMATION_BOX             0x89        // exclamation_box_geo
#define MODEL_DIRT_ANIMATION              0x8A        // dirt_animation_geo
#define MODEL_CARTOON_STAR                0x8B        // cartoon_star_geo
#define MODEL_BLUE_COIN_SWITCH            0x8C        // blue_coin_switch_geo
// find me
#define MODEL_MIST                        0x8E        // mist_geo
#define MODEL_SPARKLES_ANIMATION          0x8F        // sparkles_animation_geo
#define MODEL_RED_FLAME                   0x90        // red_flame_geo
#define MODEL_BLUE_FLAME                  0x91        // blue_flame_geo
// find me
// find me
#define MODEL_BURN_SMOKE                  0x94        // burn_smoke_geo
#define MODEL_SPARKLES                    0x95        // sparkles_geo
#define MODEL_SMOKE                       0x96        // smoke_geo
// find me
// find me
// find me
// find me
// find me
#define MODEL_BURN_SMOKE_UNUSED           0x9C        // burn_smoke_geo - unused & duplicated
// find me
#define MODEL_WHITE_PARTICLE_DL           0x9E        // white_particle_dl
#define MODEL_SAND_DUST                   0x9F        // sand_seg3_dl_particle
#define MODEL_WHITE_PARTICLE              0xA0        // white_particle_dl
#define MODEL_PEBBLE                      0xA1        // pebble_seg3_dl_0301CB00
#define MODEL_LEAVES                      0xA2        // leaves_geo
#define MODEL_WAVE_TRAIL                  0xA3        // wave_trail_geo
#define MODEL_WHITE_PARTICLE_SMALL        0xA4        // white_particle_small_dl
#define MODEL_SMALL_WATER_SPLASH          0xA5        // small_water_splash_geo
#define MODEL_IDLE_WATER_WAVE             0xA6        // idle_water_wave_geo
#define MODEL_WATER_SPLASH                0xA7        // water_splash_geo
#define MODEL_BUBBLE                      0xA8        // bubble_geo
// find me
#define MODEL_PURPLE_MARBLE               0xAA        // purple_marble_geo
// find me
#define MODEL_UNKNOWN_AC                  0xAC        // according to an special preset, it was the original id of the castle floor trap
#define MODEL_WF_SLIDING_PLATFORM         0xAD        // wf_geo_000A98
#define MODEL_WF_SMALL_BOMP               0xAE        // wf_geo_000A00
#define MODEL_WF_ROTATING_WOODEN_PLATFORM 0xAF        // wf_geo_000A58
#define MODEL_WF_TUMBLING_BRIDGE_PART     0xB0        // wf_geo_000AB0
#define MODEL_WF_LARGE_BOMP               0xB1        // wf_geo_000A40
#define MODEL_WF_TUMBLING_BRIDGE          0xB2        // wf_geo_000AC8
#define MODEL_BOWSER_BOMB                 0xB3        // bowser_bomb_geo
#define MODEL_WATER_MINE                  0xB3        // water_mine_geo
#define MODEL_BOWLING_BALL                0xB4        // bowling_ball_geo
#define MODEL_TRAMPOLINE                  0xB5        // springboard_top_geo (unused)
#define MODEL_TRAMPOLINE_CENTER           0xB6        // springboard_spring_geo (unused)
#define MODEL_TRAMPOLINE_BASE             0xB7        // springboard_bottom_geo (unused)
#define MODEL_UNKNOWN_B8                  0xB8        // referenced in special presets as a static object. Unknown usage
#define MODEL_FISH                        0xB9        // fish_geo - fish without shadow, used
#define MODEL_FISH_SHADOW                 0xBA        // fish_shadow_geo - fish with shadow, unused
#define MODEL_BUTTERFLY                   0xBB        // butterfly_geo
#define MODEL_BLACK_BOBOMB                0xBC        // black_bobomb_geo
// find me
#define MODEL_KOOPA_SHELL                 0xBE        // koopa_shell_geo
#define MODEL_KOOPA_WITHOUT_SHELL         0xBF        // koopa_without_shell_geo
#define MODEL_GOOMBA                      0xC0        // goomba_geo
#define MODEL_SEAWEED                     0xC1        // seaweed_geo
#define MODEL_AMP                         0xC2        // dAmpGeo
#define MODEL_BOBOMB_BUDDY                0xC3        // bobomb_buddy_geo
// find me
// find me
// find me
#define MODEL_SSL_TOX_BOX                 0xC7        // ssl_geo_000630
#define MODEL_BOWSER_KEY_CUTSCENE         0xC8        // bowser_key_cutscene_geo
#define MODEL_DL_CANNON_LID               0xC9        // cannon_closed_seg8_dl_080048E0
#define MODEL_CHECKERBOARD_PLATFORM       0xCA        // checkerboard_platform_geo
#define MODEL_RED_FLAME_SHADOW            0xCB        // red_flame_shadow_geo
#define MODEL_BOWSER_KEY                  0xCC        // bowser_key_geo
#define MODEL_EXPLOSION                   0xCD        // explosion_geo
#define MODEL_SNUFIT                      0xCE        // snufit_geo
#define MODEL_PURPLE_SWITCH               0xCF        // purple_switch_geo
#define MODEL_CASTLE_STAR_DOOR_30_STARS   0xD0        // castle_geo_000F00
#define MODEL_CASTLE_STAR_DOOR_50_STARS   0xD1        // castle_geo_000F00
#define MODEL_CCM_SNOWMAN_BASE            0xD2        // ccm_geo_0003F0
// find me
#define MODEL_1UP                         0xD4        // mushroom_1up_geo
#define MODEL_CASTLE_STAR_DOOR_8_STARS    0xD5        // castle_geo_000F00
#define MODEL_CASTLE_STAR_DOOR_70_STARS   0xD6        // castle_geo_000F00
#define MODEL_RED_COIN                    0xD7        // red_coin_geo
#define MODEL_RED_COIN_NO_SHADOW          0xD8        // red_coin_no_shadow_geo
#define MODEL_METAL_BOX                   0xD9        // metal_box_geo
#define MODEL_METAL_BOX_DL                0xDA        // metal_box_dl
#define MODEL_NUMBER                      0xDB        // number_geo
#define MODEL_FLYGUY                      0xDC        // shyguy_geo
#define MODEL_TOAD                        0xDD        // toad_geo
#define MODEL_PEACH                       0xDE        // peach_geo
#define MODEL_CHUCKYA                     0xDF        // chuckya_geo
#define MODEL_WHITE_PUFF                  0xE0        // white_puff_geo
#define MODEL_TRAJECTORY_MARKER_BALL      0xE1        // bowling_ball_track_geo - duplicate used in SSL Pyramid small sized and as a track ball

#ifdef IA8_30FPS_COINS
#define MODEL_SILVER_COIN                 0xE2        // silver_coin_geo
#define MODEL_SILVER_COIN_NO_SHADOW       0xE3        // silver_coin_no_shadow_geo
#endif

// Menu Models (overwrites Level Geometry IDs)
#define MODEL_MAIN_MENU_MARIO_SAVE_BUTTON         MODEL_LEVEL_GEOMETRY_03   // main_menu_geo_0001D0
#define MODEL_MAIN_MENU_RED_ERASE_BUTTON          MODEL_LEVEL_GEOMETRY_04   // main_menu_geo_000290
#define MODEL_MAIN_MENU_BLUE_COPY_BUTTON          MODEL_LEVEL_GEOMETRY_05   // main_menu_geo_0002B8
#define MODEL_MAIN_MENU_YELLOW_FILE_BUTTON        MODEL_LEVEL_GEOMETRY_06   // main_menu_geo_0002E0
#define MODEL_MAIN_MENU_GREEN_SCORE_BUTTON        MODEL_LEVEL_GEOMETRY_07   // main_menu_geo_000308
#define MODEL_MAIN_MENU_MARIO_SAVE_BUTTON_FADE    MODEL_LEVEL_GEOMETRY_08   // main_menu_geo_000200
#define MODEL_MAIN_MENU_MARIO_NEW_BUTTON          MODEL_LEVEL_GEOMETRY_09   // main_menu_geo_000230
#define MODEL_MAIN_MENU_MARIO_NEW_BUTTON_FADE     MODEL_LEVEL_GEOMETRY_0A   // main_menu_geo_000260
#define MODEL_MAIN_MENU_PURPLE_SOUND_BUTTON       MODEL_LEVEL_GEOMETRY_0B   // main_menu_geo_000330
#define MODEL_MAIN_MENU_GENERIC_BUTTON            MODEL_LEVEL_GEOMETRY_0C   // main_menu_geo_000358

// level model aliases to level geometry IDs. Possibly a relic from an older level
// format that used to rely on level geometry objects. (seen in WF, LLL, etc)
#define MODEL_LLL_ROTATING_HEXAGONAL_PLATFORM     MODEL_LEVEL_GEOMETRY_09   // lll_geo_000A78
#define MODEL_WF_GIANT_POLE                       MODEL_LEVEL_GEOMETRY_0D   // wf_geo_000AE0
#define MODEL_WF_ROTATING_PLATFORM                MODEL_LEVEL_GEOMETRY_10   // wf_geo_0009B8
#define MODEL_BITDW_WARP_PIPE                     MODEL_LEVEL_GEOMETRY_12   // warp_pipe_geo
#define MODEL_THI_WARP_PIPE                       MODEL_LEVEL_GEOMETRY_16   // warp_pipe_geo
#define MODEL_VCUTM_WARP_PIPE                     MODEL_LEVEL_GEOMETRY_16   // warp_pipe_geo
#define MODEL_CASTLE_GROUNDS_WARP_PIPE            MODEL_LEVEL_GEOMETRY_16   // warp_pipe_geo

/* GLOBAL MODEL IDS 0xF0-0x14F */
enum GLOBAL_MODELS {
    MODEL_LEVEL_PIPE=0xF0,
    MODEL_CHECKPOINT_FLAG,
    MODEL_ABILITY,
    MODEL_ABILITY_SIGN,
    MODEL_E__ROCKET,
    MODEL_E__ROCKET_EXPLOSION,
    MODEL_E__ROCKET_BLAST,
    MODEL_E__MUZZLE_FLASH,
    MODEL_E__SHOTGUN_SHELL,
    MODEL_CUTTER_BLADE,
    MODEL_CUTTER_BLAST,
    MODEL_SLASH_PARTICLE,
    MODEL_DRAGONITE,
    MODEL_NITRO_BOX,
    MODEL_NITRO_BOOM,
    MODEL_MARBLE,
    MODEL_SHOCK_ROCKET,
    MODEL_ROCKET_BUTTON_OFF,
    MODEL_ROCKET_BUTTON_ON,
    MODEL_SQUID,
    MODEL_PT_METAL_BOX,
    MODEL_WATCH_AIM,
    MODEL_FLIPSWITCH_1,
    MODEL_FLIPSWITCH_2,
    MODEL_FLIPSWITCH_3,
    MODEL_STAR_PIECE,
    MODEL_NOTEBLOCK,
    MODEL_CONCRETE_BLOCK,
    MODEL_CONCRETE_BLOCK_CRACK1,
    MODEL_CONCRETE_BLOCK_CRACK2,
    MODEL_DBP,//Dash Booster Particle
    MODEL_ATTACHED_ROPE,
    MODEL_ZAP,
    MODEL_F_LASER,
    MODEL_EGADD,
    MODEL_MACHINE,
    MODEL_RED_ARROW,
    MODEL_WEDSER,
    MODEL_SHOPITEM_3, // accident
    MODEL_DREAM_STAR,
    MODEL_CARDBOARD_STAR,
    MODEL_PAINTING,
    MODEL_SPIDERTRON_LIMB_1,

    MODEL_BD_SHIMMER,
    MODEL_BD_SHINE,
    MODEL_BD_STAR,
    MODEL_BD_WAVE,

    // Custom Mario Models
    MODEL_E__MARIO,
    MODEL_MARIO_K,
    MODEL_KNIGHT_MARIO,
    MODEL_SAWAXE_MARIO,
};
/* LEVEL SPECIFIC MODELS 0x150-0x1FF */
//Format: #define MODEL_A_MODELNAME

/* LEVEL INTRO START */
#define MODEL_INTRO_SKYBOX                        0x150
#define MODEL_INTRO_BREAKDOOR                     0x151 // Part of the birthday level data, not intro level data
#define MODEL_INTRO_CLOTH                         0x152
#define MODEL_INTRO_ROCK                          0x153
#define MODEL_INTRO_GMACHINE                      0x154 //not actually the intro, just named this way for consitency's sake
#define MODEL_INTRO_ENDSER                        0x155
/* LEVEL INTRO END */

/* LEVEL A START */
#define MODEL_JELLY                               0x154
#define MODEL_JF_PLATFORM                         0x155
#define MODEL_TAXISTOP                            0x156
#define MODEL_TSBOAT                              0x157
#define MODEL_TIKI_WOOD                           0x158
#define MODEL_TIKI_STONE                          0x159
#define MODEL_TIKI_FLOAT                          0x15A
#define MODEL_TRAMP                               0x15B
#define MODEL_FLOATING_CHECKER_PLATFORM           0x15C
#define MODEL_KING_JELLY                          0x15D
#define MODEL_KING_JELLY_SHOCK                    0x15E
#define MODEL_BUBBLENET_RED_BUTTON                0x15F
#define MODEL_JELLYS                              0x154 //0x160
// I made these objects since whenever I would export them into the level from blender the game would crash.
// I also had an idea for the tables to move around but I dont have enough time to make that happen.
#define MODEL_KKTABLE                             0x161
#define MODEL_KKB                                 0x162
#define MODEL_SQUIDWARD                           0x163
#define MODEL_BHBRIDGE                            0x164
#define MODEL_A_PLANK                             0x165
#define MODEL_GOO_DROP                            0x166
#define MODEL_A_CAGE                              0x167
#define MODEL_PISSWAVE                            0x168
#define MODEL_A_UFO_ROBOT                         0x169
#define MODEL_A_CHUMBUCKET_DOOR                   0x16A
#define MODEL_A_HAM_ROBOT                         0x16B
#define MODEL_A_LAUNCHED_BOX                      0x16C
#define MODEL_A_ROBOT_LAUNCHER                    0x16D
#define MODEL_A_DOG_ROBOT                         0x16E
#define MODEL_A_GAS_CLOUD                         0x16F
#define MODEL_A_CHAINED_CAGE                      0x170
/* LEVEL A END */

/* LEVEL B START */
#define MODEL_BIG_DADDY                          0x151
#define MODEL_FLOATY                             0x152
#define MODEL_LITTLE_SISTER                      0x153
#define MODEL_GAUGE                              0x154
#define MODEL_WATERFALL                          0x155
#define MODEL_DEBRIS                             0x156
#define MODEL_AIRLOCK                            0x157
#define MODEL_AIRLOCK_BUTTON                     0x158
#define MODEL_AIRLOCK_WATER                      0x159
#define MODEL_CRUSHER                            0x15A
#define MODEL_TURRET_BODY                        0x15B
#define MODEL_TURRET_HEAD                        0x15C
#define MODEL_TURRET_BULLET                      0x15D
#define MODEL_TURRET_HEAVY                       0x15E
#define MODEL_TURRET_PLATFORM                    0x15F  
#define MODEL_TURRET_COVER                       0x160
#define MODEL_GATE                               0x161
#define MODEL_ALARM                              0x162
#define MODEL_ALARM_LIT                          0x163
#define MODEL_TURRET_PANEL                       0x164
#define MODEL_MEGACORK                           0x165
#define MODEL_WATERTEMPLE                        0x166
#define MODEL_B_SHOCKWAVE                        0x167

/* LEVEL B END */

/* LEVEL C START */
#define MODEL_CRANE_ARROW           0x36 //crane_arrow_geo
#define MODEL_PAINT_GUN             0x37 //paint_gun_geo
#define MODEL_CRANE_HEAD            0x38 //crane_head_geo
#define MODEL_CRANE                 0x39 //crane_geo
#define MODEL_OCTOBALL              0x3A //octoball_geo
#define MODEL_STAR_BOULDER          0x3B //star_boulder_geo
#define MODEL_PAINT_STAIN           0x3C //paint_stain_geo
#define MODEL_SPLAT_TARGET          0x3D //splat_target_geo
#define MODEL_TARGET_BOX            0x3E //target_box_geo
#define MODEL_OCTOMISSILE           0x3F //octomissle_geo
#define MODEL_FLAG                  0x40 //flag_geo
#define MODEL_INK_MOVING_PLATFORM   0x41 //ink_moving_platform_geo
#define MODEL_PAINT_BULLET          0x42 //ink_paint_bullet_geo
#define MODEL_OCTOZEPPLIN           0x43 //octozepplin_geo
#define MODEL_JELLY_FISH            0x44 //jelly_fish_geo
#define MODEL_OCTOBA                0x45 //octoba_geo
/* LEVEL C END */

/* LEVEL D START */
#define MODEL_D_UKAUKA 0x151
#define MODEL_HMC_DOOR_D 0x152
#define MODEL_D_TREE1 0x153
#define MODEL_D_TREE2 0x154
#define MODEL_D_ELEVATOR 0x155
#define MODEL_D_BRIDGE 0x156
#define MODEL_D_GATE 0x157
#define MODEL_D_PLATFORM 0x158
/* LEVEL D END */

/* LEVEL E START */
enum {
    MODEL_ID_00, MODEL_ID_01, MODEL_ID_02, MODEL_ID_03, MODEL_ID_04, MODEL_ID_05,
    MODEL_ID_06, MODEL_ID_07, MODEL_ID_08, MODEL_ID_09, MODEL_ID_0A, MODEL_ID_0B,
    MODEL_ID_0C, MODEL_ID_0D, MODEL_ID_0E, MODEL_ID_0F, MODEL_ID_10, MODEL_ID_11,
    MODEL_ID_12, MODEL_ID_13, MODEL_ID_14, MODEL_ID_15, MODEL_ID_16, MODEL_ID_17,
    MODEL_ID_18, MODEL_ID_19, MODEL_ID_1A, MODEL_ID_1B, MODEL_ID_1C, MODEL_ID_1D,
    MODEL_ID_1E, MODEL_ID_1F, MODEL_ID_20, MODEL_ID_21, MODEL_ID_22, MODEL_ID_23,
    MODEL_ID_24, MODEL_ID_25
};
/* LEVEL E END */

/* LEVEL F START */
#define MODEL_F_BRIEFCASE 0x151
#define MODEL_F_DOOR 0x152
#define MODEL_F_KEYPAD 0x153
#define MODEL_F_FENCE 0x154
#define MODEL_FTRINKET_1 0x155
#define MODEL_FTRINKET_2 0x156
#define MODEL_FTRINKET_3 0x157
#define MODEL_BLASTWALL_1 0x158
#define MODEL_BLASTWALL_2 0x159
#define MODEL_FDYNAMITE 0x15A
#define MODEL_FSG_KEYPAD 0x15B
#define MODEL_FHIDDEN 0x15C
#define MODEL_GOLD_BTN_ON 0x15D
#define MODEL_GOLD_BTN_OFF 0x15E
#define MODEL_F_SCH_BOARD_1 0x15F
#define MODEL_F_SCH_BOARD_2 0x160
#define MODEL_F_TRAPDOOR 0x161
#define MODEL_F_KEY 0x162
#define MODEL_F_SHOOTER 0x163
#define MODEL_F_KEYDOOR 0x164
#define MODEL_CURTAINPLATFORM1 0x165
#define MODEL_CURTAINPLATFORM2 0x166
#define MODEL_F_MISSILES 0x167
#define MODEL_F_BOAT 0x168
#define MODEL_F_HELI 0x169
#define MODEL_F_HELISHADOW 0x16A
#define MODEL_F_HELIDEAD 0x16B
/* LEVEL F END */

/* LEVEL G START */
#define MODEL_G_SIR_KIBBLE                      0x150
#define MODEL_G_STAR_BLOCK                      0x151
#define MODEL_G_STAR_PROJECTILE                      0x152
#define MODEL_G_CHECKER_BLOCK_1                      0x153
#define MODEL_G_SPRING                      0x154
#define MODEL_G_CUT_ROCK                      0x155
#define MODEL_G_CUT_ROCK2                      0x156
#define MODEL_G_CUT_ROCK3                      0x157
#define MODEL_G_CANNON                      0x158
#define MODEL_MARX                      0x159
#define MODEL_G_MARX_CUTTER                      0x15A
#define MODEL_G_MARX_SEED                      0x15B
#define MODEL_G_MARX_THORNS                     0x15C
#define MODEL_G_MARX_HALF_LEFT              0x15D
#define MODEL_G_MARX_HALF_RIGHT              0x15E
#define MODEL_G_MARX_BLACK_HOLE              0x15F
#define MODEL_G_MARX_ARROW              0x160
#define MODEL_G_MARX_MOUTH_FULL              0x161
#define MODEL_G_MARX_MOUTH_OPEN              0x162
#define MODEL_G_MARX_LASER              0x163
#define MODEL_G_MARX_ICE_BOMB              0x164
#define MODEL_G_MARX_ICE_RING              0x165
#define MODEL_G_MARX_BLACK_HOLE_EFFECT              0x166
#define MODEL_G_BRONTO_BURT              0x167
#define MODEL_G_MOVING_PLATFORM              0x168
#define MODEL_G_MARX_DOOR              0x169
#define MODEL_G_WADDLE_DEE              0x16A
#define MODEL_G_WARP_PIPE              0x16B

/*
Funny story: I'm pretty sure I'm dyslexic.
This whole fucking time, it was * banDANA dee *
However, my dumb ass read the blend file as "banana" dee, so i named
every fucking variable in reference to this NPC as such.
I didn't realize until I looked at the model and realized that he
was wearing a bandana, and then it clicked. I'm a fucking moron. Oops!
Too bad I'm not changing every variable name, especially since the
blend file associated with this NPC is cursed.
*/

#define MODEL_G_BANANA_DEE 0x16C
/* LEVEL G END */

/* LEVEL H START */
#define MODEL_HLOADER 0x150
#define MODEL_HGLASS 0x151
/* LEVEL H END */

/* LEVEL I START */
#define MODEL_HOODBOOMER                0x36        //hoodboomer_geo
#define MODEL_PIGPOT                    0x37        //pigpot_geo
#define MODEL_HOODBOOMER_BOMB           0x38        //hoodboomer_bomb
#define MODEL_WINDMILL                  0x39        //windmill_geo
#define MODEL_GATE                      0x3A        //gate_geo
#define MODEL_WOODEN_LEVER              0x3B        //wooden_lever_geo
#define MODEL_PLUM                      0x3C        //plum
#define MODEL_CAGED_TOAD                0x3D        //caged_toad
#define MODEL_PLANK_ROPE                0x3E        //plank_rope_geo
#define MODEL_BARRIER_ROPE              0x3F        //barrier_rope_geo
#define MODEL_BLACK_PANEL               0x40        //black_panel_geo
#define MODEL_FUNKY_ROAD                0x41        //funky_road_geo
#define MODEL_OPENING_WALL              0x42        //opening_wall_geo
#define MODEL_OPENABLE_WOODEN_GATE      0x43        //openable_wood_gate
#define MODEL_WATERMILL                 0x44        //watermill_geo
#define MODEL_MASTER_KAAG               0x45        //master_kaag_geo
#define MODEL_HOODOO_SORCERER           0x46        //hoodoo_sorcerer
#define MODEL_MAGIC_SHIELD              0x47        //magic_shiel_geo
#define MODEL_HOODMONGER                0x48        //hoodmonger_geo
#define MODEL_HOODMONGER_BULLET         0x49        //hoodmonger_bullet_geo
#define MODEL_STAR_SLOT_EMPTY           0x4A        //star_slot_empty_geo
#define MODEL_STAR_SLOT_FULL            0x4B        //star_slot_full_geo
#define MODEL_DOLLAR                    0x4C        //dollar_geo
#define MODEL_BLACKLUMS                 0x4D        //blacklums_geo
#define MODEL_BOSS_GATE                 0x4E        //model_boss_geo

/* LEVEL I END */

/* LEVEL J START */
#define MODEL_J_FALLING_PLATFORM                0x150
#define MODEL_J_TILTY_HEXAGON                   0x151
#define MODEL_J_SKARMORY                        0x152
#define MODEL_J_YOUNGSTER                       0x153
#define MODEL_J_SPINARAK                        0x154
#define MODEL_J_GEODUDE                         0x155
#define MODEL_BERRY                             0x156
#define MODEL_J_HOOH                            0x157
#define MODEL_J_HOOH_ROCK                       0x158
#define MODEL_J_MILTANK                         0x159
#define MODEL_J_GASTLY                          0x160
#define MODEL_J_HAUNTER                         0x161
#define MODEL_J_GENGAR                          0x162
#define MODEL_J_ELDER                           0x163
#define MODEL_J_KIMONO_GIRL                     0x164
#define MODEL_J_MORTY                           0x165
#define MODEL_J_COWGIRL                         0x166
#define MODEL_J_SENTRET                         0x167
#define MODEL_J_SKIPLOOM                        0x168
#define MODEL_J_OLD_MAN                         0x169
#define MODEL_J_SNORLAX                         0x170
#define MODEL_J_MAGIKARP                        0x171
#define MODEL_J_GRAVELER                 0x39
/* LEVEL J END */

/* LEVEL K START */
enum K_MODELS {
    MODEL_K_STRONG_TERRY=0x150,
    MODEL_K_SKINNY_RICKY,
    MODEL_K_SHIELDO,
    MODEL_K_ELECTROHEAD,
    MODEL_K_JOSH,
    MODEL_K_FAN,
    MODEL_K_BLOOD,
    MODEL_K_BLOOD_2,
    MODEL_K_KAGUYA,
    MODEL_K_DISCO,
    MODEL_K_BARTENDER,
    MODEL_K_TV_1,
    MODEL_K_TV_2,
    MODEL_K_TV_3,
    MODEL_K_TV_4,
    MODEL_K_LITE,
    MODEL_K_POUNDER,
    MODEL_K_SLIGHT,
    MODEL_K_RAQUNA,
    MODEL_K_EARLYEXIT,
    MODEL_K_MARA,
    MODEL_K_ISAAC,
    MODEL_K_STEVE,
    MODEL_K_YICK,
    MODEL_K_RATCHET,
    MODEL_K_VIN,
    MODEL_K_DIXIE,
};
/* LEVEL K END */

/* LEVEL L START */
#define MODEL_L_JOHN                            0x150
#define MODEL_L_JOHNBLOCK                       0x151
#define MODEL_L_CHEESESLIME                     0x152
#define MODEL_L_PEPPERMAN                       0x153
#define MODEL_L_CLOCK                           0x154
#define MODEL_L_PORTAL                          0x155
#define MODEL_L_ANCHOVY                         MODEL_FLYGUY
#define bhvL_Anchovy                            bhvFlyGuy
#define MODEL_L_PSTATUE_1                       0x156
#define MODEL_L_PSTATUE_2                       0x157
#define MODEL_L_PSTATUE_3                       0x158
#define MODEL_L_DEMON                           0x159
#define MODEL_L_PEPPERART                       0x15A
/* LEVEL L END */

/* LEVEL M START */
#define MODEL_M_BOSSELEVATOR                    0x150
#define MODEL_M_CLASSC                          0x151
#define MODEL_M_GATE                            0x152
#define MODEL_M_JELLY                           0x153
#define MODEL_M_ELEVATOR                        0x154
#define MODEL_M_JELLYLASER                      0x155
#define MODEL_M_JELLYLASER_2                    0x156
/* LEVEL M END */

/* LEVEL N START */
#define MODEL_N_BALL 0x150
/* LEVEL N END */

/* LEVEL O START */
#define MODEL_O_ZOMBIE_1  0x151
#define MODEL_O_ZOMBIE_2  0x152
#define MODEL_O_ZOMBIE_3  0x153
#define MODEL_ZOMBLOOD    0x154
#define MODEL_O_TREE      0x155
#define MODEL_O_UVSTAR    0x156
#define MODEL_O_LIFT      0x157
#define MODEL_O_GARAGE    0x158
#define MODEL_O_SPEAKER_1 0x159
#define MODEL_O_SPEAKER_2 0x15A
#define MODEL_O_SPEAKER_3 0x15B
#define MODEL_O_GERIK     0x15C
#define MODEL_O_FLAME     0x15D
/* LEVEL O END */

/* Bowser Level */
enum {
    //bowserlevle
    MODEL_MATPLATFORM=0x150,
    MODEL_BC_TILTING,
    MODEL_BC_WADDLE_DEE,
    MODEL_BC_JELLY,
    MODEL_BC_HOODMONGER,
    MODEL_BC_HOODMONGER_BULLET,
    MODEL_BC_FIRESPINNER,
    MODEL_BC_STAIR,
    MODEL_BC_STAIR_2,
    MODEL_BC_SHOOTER,
    MODEL_BC_SKIPLOOM,
    MODEL_BC_COINPILE,

    //bossfight
    MODEL_BC_ATREUS,
    MODEL_BC_BOWSER_FORM_1,
    MODEL_BC_BOWSER_FORM_2,
    MODEL_BC_BOWSER_FORM_3,
    MODEL_BC_BOWSER_FORM_4,
    MODEL_BC_BOWSER_FORM_5,
    MODEL_BC_BOSSLANDING,
    MODEL_BC_PINGAS_PLANE,
    MODEL_BC_PINGAS_BALL,
    MODEL_BC_PINGAS_PLANE_DMG,
    MODEL_BC_CRYSTAL,
    MODEL_BC_CRYSTALP,
    MODEL_BC_CRYSTALG,
    MODEL_BC_CRYSTALGP,
    // cannibalize the canceled secret boss and steal attacks
    MODEL_SB_TRAIN,
    MODEL_SB_GAP,
    MODEL_SB_BLASTER,
    MODEL_SB_BLAST,

    MODEL_BC_LASER,
    MODEL_BC_LASEREMIT,
    MODEL_BC_ROCK,
};

//HUB
enum {
    MODEL_LAYTON=0x151,
    MODEL_HUBPLATFORM,
    MODEL_SHOPITEM_1,
    MODEL_SHOPITEM_2,
    MODEL_SHOPITEM_4,
    MODEL_HUBSTARGOO,
    MODEL_HUBDOOR,
    MODEL_MORSHU,
    MODEL_HUB_TARGET_BOX,
    MODEL_REDD,
    MODEL_MUMBO_JUMBO,
    MODEL_SYNTHESIZER,
};

//SB (SECRET BOSS)
enum {
    MODEL_SB_STAIRS=0x151,
    MODEL_SB_TORCH_1,
    MODEL_SB_TORCH_2,
    MODEL_SB_GASTER,
    MODEL_SB_YUKARI,
};

#endif // MODEL_IDS_H
