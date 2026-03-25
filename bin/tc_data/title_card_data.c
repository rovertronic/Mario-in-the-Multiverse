#include <ultra64.h>
#include "sm64.h"
#include "make_const_nonconst.h"

ALIGNED8 const u8 title_card_data[] = {
    #include "actors/title_cards/custom_titlecard_G.rgba16.inc.c"
    ,
    #include "actors/title_cards/custom_titlecard_A.rgba16.inc.c"
    ,
    #include "actors/title_cards/custom_titlecard_C.rgba16.inc.c"
    ,
    #include "actors/title_cards/custom_titlecard_I.rgba16.inc.c"
    ,
    #include "actors/title_cards/custom_titlecard_H.rgba16.inc.c"
    ,
    #include "actors/title_cards/custom_titlecard_B.rgba16.inc.c"
    ,
    #include "actors/title_cards/custom_titlecard_L.rgba16.inc.c"
    ,
    #include "actors/title_cards/custom_titlecard_K.rgba16.inc.c"
    ,
    #include "actors/title_cards/custom_titlecard_E.rgba16.inc.c"
    ,
    #include "actors/title_cards/custom_titlecard_F.rgba16.inc.c"
    ,
    #include "actors/title_cards/custom_titlecard_J.rgba16.inc.c"
    ,
    #include "actors/title_cards/custom_titlecard_D.rgba16.inc.c"
    ,
    #include "actors/title_cards/custom_titlecard_O.rgba16.inc.c"
    ,
    #include "actors/title_cards/custom_titlecard_N.rgba16.inc.c"
    ,
    #include "actors/title_cards/custom_titlecard_M.rgba16.inc.c"
};

ALIGNED8 const u8 hint_art_data[] = {
    #include "actors/title_cards/hint_art_1.rgba16.inc.c"
    ,
    #include "actors/title_cards/hint_art_2.rgba16.inc.c"
    ,
    #include "actors/title_cards/hint_art_3.rgba16.inc.c"
    ,
    #include "actors/title_cards/hint_art_4.rgba16.inc.c"
    ,
    #include "actors/title_cards/hint_art_5.rgba16.inc.c"
    ,
    #include "actors/title_cards/hint_art_6.rgba16.inc.c"
    ,
    #include "actors/title_cards/hint_art_7.rgba16.inc.c"
    ,
    #include "actors/title_cards/hint_art_8.rgba16.inc.c"
    ,
    #include "actors/title_cards/hint_art_9.rgba16.inc.c"
    ,
    #include "actors/title_cards/hint_art_10.rgba16.inc.c"
    ,
    #include "actors/title_cards/hint_art_11.rgba16.inc.c"
    ,
    #include "actors/title_cards/hint_art_12.rgba16.inc.c"
    ,
    #include "actors/title_cards/hint_art_13.rgba16.inc.c"
    ,
    #include "actors/title_cards/hint_art_14.rgba16.inc.c"
    ,
    #include "actors/title_cards/hint_art_15.rgba16.inc.c"
};

ALIGNED8 const u8 painting_data[] = {
    #include "actors/title_cards/custom_painting_strip.rgba16.inc.c"
};