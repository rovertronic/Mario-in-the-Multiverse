#include "sm64.h"
#include "game_init.h"
#include "archipelago.h"

u32 gArchipelagoBuffer[AP_END];

void archipelago_init(void) {
    sprintf(&gArchipelagoBuffer,"MITM AP BUFFER  ");
}

void archipelago_check_location(int id) {
    gArchipelagoBuffer[AP_SEND_LOCATION] = id;
}

u32 archipelago_item_unlocked(int id) {
    int slot = id/32;
    int bit = id%32;
    return (gArchipelagoBuffer[AP_ITEMS + slot] & (1 << bit));
}