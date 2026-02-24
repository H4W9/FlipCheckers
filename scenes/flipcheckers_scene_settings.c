#include "../flipcheckers.h"
#include <lib/toolbox/value_index.h>

#define TEXT_LABEL_ON  "ON"
#define TEXT_LABEL_OFF "OFF"

const char* const haptic_text[2] = {
    TEXT_LABEL_OFF,
    TEXT_LABEL_ON,
};
const uint32_t haptic_value[2] = {
    FlipCheckersHapticOff,
    FlipCheckersHapticOn,
};

const char* const must_jump_text[2] = {
    TEXT_LABEL_OFF,
    TEXT_LABEL_ON,
};
const uint32_t must_jump_value[2] = {
    FlipCheckersMustJumpOff,
    FlipCheckersMustJumpOn,
};

const char* const player_mode_text[4] = {
    "Human",
    "CPU 1",
    "CPU 2",
    "CPU 3",
};
const uint32_t player_mode_value[4] = {
    FlipCheckersPlayerHuman,
    FlipCheckersPlayerAI1,
    FlipCheckersPlayerAI2,
    FlipCheckersPlayerAI3,
};

static void flipcheckers_scene_settings_set_haptic(VariableItem* item) {
    FlipCheckers* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, haptic_text[index]);
    app->haptic = haptic_value[index];
}

static void flipcheckers_scene_settings_set_must_jump(VariableItem* item) {
    FlipCheckers* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, must_jump_text[index]);
    app->must_jump = must_jump_value[index];
}

static void flipcheckers_scene_settings_set_white_mode(VariableItem* item) {
    FlipCheckers* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, player_mode_text[index]);
    app->white_mode = player_mode_value[index];
}

static void flipcheckers_scene_settings_set_black_mode(VariableItem* item) {
    FlipCheckers* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, player_mode_text[index]);
    app->black_mode = player_mode_value[index];
}

void flipcheckers_scene_settings_submenu_callback(void* context, uint32_t index) {
    FlipCheckers* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

void flipcheckers_scene_settings_on_enter(void* context) {
    FlipCheckers* app = context;
    VariableItem* item;
    uint8_t value_index;

    // Red (White) player mode
    item = variable_item_list_add(
        app->variable_item_list, "Red:", 4, flipcheckers_scene_settings_set_white_mode, app);
    value_index = value_index_uint32(app->white_mode, player_mode_value, 4);
    variable_item_set_current_value_index(item, value_index);
    variable_item_set_current_value_text(item, player_mode_text[value_index]);

    // Black player mode
    item = variable_item_list_add(
        app->variable_item_list, "Black:", 4, flipcheckers_scene_settings_set_black_mode, app);
    value_index = value_index_uint32(app->black_mode, player_mode_value, 4);
    variable_item_set_current_value_index(item, value_index);
    variable_item_set_current_value_text(item, player_mode_text[value_index]);

    // Must Jump rule
    item = variable_item_list_add(
        app->variable_item_list, "Must Jump:", 2, flipcheckers_scene_settings_set_must_jump, app);
    value_index = value_index_uint32(app->must_jump, must_jump_value, 2);
    variable_item_set_current_value_index(item, value_index);
    variable_item_set_current_value_text(item, must_jump_text[value_index]);

    // Vibro on/off
    item = variable_item_list_add(
        app->variable_item_list, "Vibro/Haptic:", 2, flipcheckers_scene_settings_set_haptic, app);
    value_index = value_index_uint32(app->haptic, haptic_value, 2);
    variable_item_set_current_value_index(item, value_index);
    variable_item_set_current_value_text(item, haptic_text[value_index]);

    view_dispatcher_switch_to_view(app->view_dispatcher, FlipCheckersViewIdSettings);
}

bool flipcheckers_scene_settings_on_event(void* context, SceneManagerEvent event) {
    FlipCheckers* app = context;
    UNUSED(app);
    bool consumed = false;
    if(event.type == SceneManagerEventTypeCustom) {
    }
    return consumed;
}

void flipcheckers_scene_settings_on_exit(void* context) {
    FlipCheckers* app = context;
    variable_item_list_set_selected_item(app->variable_item_list, 0);
    variable_item_list_reset(app->variable_item_list);
}
