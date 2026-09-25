#include "sm64.h"
#include "game_init.h"
#include "archipelago.h"
#include "include/model_ids.h"
#include "area.h"
#include "include/object_constants.h"

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

u32 archipelago_location_checked(int id) {
    int slot = id/32;
    int bit = id%32;
    return (gArchipelagoBuffer[AP_LOCATIONS_CHECKED + slot] & (1 << bit));
}

s32 archipelago_item_model(int id, struct Object * obj) {
    s32 model = MODEL_NONE;
    f32 scale = 1.0f;

    if (!(obj->oFlags & OBJ_FLAG_AP_MODEL_SET)) {
        // Send request if another object isn't already requesting
        if (gArchipelagoBuffer[AP_REQUEST_MODEL_ID] == 0) {
            gArchipelagoBuffer[AP_REQUEST_MODEL_ID] = id;
        } else {
            // Wait for response
            if (gArchipelagoBuffer[AP_RETURN_MODEL_ID] > 0) {
                switch(gArchipelagoBuffer[AP_RETURN_MODEL_ID]) {
                    case 1:
                        model = MODEL_AP_ITEM;
                        break;
                    case 2:
                        model = MODEL_STAR;
                        break;
                    case 3:
                        model = MODEL_NITRO_BOX;
                        break;
                    case 4:
                        model = MODEL_CONCRETE_BLOCK;
                        scale = .5f;
                        break;
                    case 5:
                        model = MODEL_HEART;
                        break;
                    default:
                        model = MODEL_ABILITY;
                        SET_BPARAM4(obj->oBehParams, gArchipelagoBuffer[AP_RETURN_MODEL_ID]-5);
                        obj->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
                        break;
                }
                // Mark this object to not use the model request buffer anymore
                obj->oFlags |= OBJ_FLAG_AP_MODEL_SET;
                gArchipelagoBuffer[AP_REQUEST_MODEL_ID] = 0;
                gArchipelagoBuffer[AP_RETURN_MODEL_ID] = 0;

                obj->header.gfx.sharedChild = gLoadedGraphNodes[model];
            }
        }
    }
    return 0;
}