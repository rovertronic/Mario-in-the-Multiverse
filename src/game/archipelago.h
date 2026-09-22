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
    AP_ITEMS_2,

    AP_END,
};

void archipelago_init(void);
void archipelago_check_location(int id);
u32 archipelago_item_unlocked(int id);

extern u32 gArchipelagoBuffer[];

#endif