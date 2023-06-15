#include "src/game/envfx_snow.h"

const GeoLayout shock_rocket_geo[] = {
    GEO_ROTATION_NODE(0x00, 0, 0x2000, 0),
    GEO_OPEN_NODE(),
        GEO_DISPLAY_LIST(LAYER_OPAQUE, rocket_hand_RaymanMissile_mesh_layer_1),
        GEO_DISPLAY_LIST(LAYER_OPAQUE, rocket_hand_material_revert_render_settings),
    GEO_CLOSE_NODE(),
    GEO_END(),
};
