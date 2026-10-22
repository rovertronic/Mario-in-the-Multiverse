#ifndef ARCHIPELAGO_H
#define ARCHIPELAGO_H

enum {
    AP_HEADER_1,
    AP_HEADER_2,
    AP_HEADER_3,
    AP_HEADER_4,
    AP_FOUND_CLIENT,
    AP_CONNECTED,

    AP_SEND_LOCATION,
    
    AP_STAR_TOTAL,

    AP_MESSAGE,

    AP_ITEMS = 20,

    AP_TEXT_TIMER = 22,
    AP_LOCATIONS_CHECKED = 23,
    AP_REQUEST_MODEL_ID = 31,
    AP_RETURN_MODEL_ID = 32,
    AP_KILL_BOWSER = 33,

    AP_50_COIN_PACK = 34,
    AP_STARS_TO_COMPLETE = 35,

    AP_REQUEST_ITEM_NAME = 36,
    AP_ITEM_NAME = 37,
    AP_ITEM_NAME_END = 49,

    AP_END,
};

void archipelago_init(void);
void archipelago_check_location(int id);
u32 archipelago_item_unlocked(int id);
s32 archipelago_item_model(int id, struct Object * obj);
u32 archipelago_location_checked(int id);

extern u32 gArchipelagoBuffer[];
extern u32 gArchipelagoLastLocationChecked;

#endif