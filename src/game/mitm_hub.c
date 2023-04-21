//Menu stuff
#include "actors/common1.h"
#include "area.h"
#include "audio/external.h"
#include "camera.h"
#include "course_table.h"
#include "dialog_ids.h"
#include "engine/math_util.h"
#include "eu_translation.h"
#include "segment_symbols.h"
#include "game_init.h"
#include "gfx_dimensions.h"
#include "ingame_menu.h"
#include "level_update.h"
#include "levels/castle_grounds/header.h"
#include "memory.h"
#include "print.h"
#include "save_file.h"
#include "segment2.h"
#include "segment7.h"
#include "seq_ids.h"
#include "sm64.h"
#include "text_strings.h"
#include "types.h"
#include "config.h"
#include "puppycam2.h"
#include "main.h"
#include "levels/castle_inside/header.h"
//Object stuff
#include "behavior_actions.h"
#include "behavior_data.h"
#include "engine/behavior_script.h"
#include "engine/surface_collision.h"
#include "envfx_bubbles.h"
#include "interaction.h"
#include "level_misc_macros.h"
#include "level_table.h"
#include "mario.h"
#include "mario_actions_cutscene.h"
#include "mario_misc.h"
#include "obj_behaviors.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "rendering_graph_node.h"
#include "spawn_object.h"
#include "spawn_sound.h"
#include "rumble_init.h"
#include "puppylights.h"

s8 hub_level_index = -1;
s8 hub_dma_index = -1;
f32 hub_titlecard_alpha = 0.0f;

void level_pipe_loop(void) {
    if (lateral_dist_between_objects(o, gMarioObject) < 200.0f) {
        hub_level_index = o->oBehParams2ndByte;
    }
}

void render_mitm_hub_hud(void) {
    u8 *texture = segmented_to_virtual(&title_card_placeholder_title_card_rgba16);

    if (hub_level_index > -1) {
        hub_titlecard_alpha = approach_f32_asymptotic(hub_titlecard_alpha,255.0f,0.1f);
    } else {
        hub_titlecard_alpha = approach_f32_asymptotic(hub_titlecard_alpha,0.0f,0.15f);
    }

    if ((hub_level_index != hub_dma_index)&&(hub_level_index > -1)) {
        hub_dma_index = hub_level_index;
        dma_read(texture,(hub_dma_index*65536)+_title_cardSegmentRomStart,(hub_dma_index*65536)+_title_cardSegmentRomStart+65536);
        }

    create_dl_ortho_matrix();

    create_dl_translation_matrix(MENU_MTX_PUSH, 32, 200, 0);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, (u8)hub_titlecard_alpha);
    gSPDisplayList(gDisplayListHead++, title_card_TitleCardMesh_mesh);

    hub_level_index = -1;
}