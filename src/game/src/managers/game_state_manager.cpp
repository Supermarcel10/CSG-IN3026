#include "game_state_manager.h"

#include "../layers/example_layer.h"
#include "../layers/main_menu.h"


game_state_manager::game_state_manager(engine::application& engine)
    : engine(engine), current_state(game_state::MAIN_MENU), current_progress_state(game_progress_state::NOT_IN_GAME)
{
}

void game_state_manager::set_state(game_state new_state) {
    current_state = new_state;
    push_new_layer();
}

void game_state_manager::set_progress_state(game_progress_state new_state) {
    current_progress_state = new_state;
}

game_state game_state_manager::get_state() const {
    return current_state;
}

game_progress_state game_state_manager::get_progress_state() const {
    return current_progress_state;
}

void game_state_manager::push_new_layer() {
    switch (current_state) {
    case game_state::MAIN_MENU:
        engine.push_layer(new main_menu(*this));
        break;
    case game_state::OPTIONS:
        engine.push_layer(new example_layer(*this));
        break;
    case game_state::NEW_GAME_SETUP:
        engine.push_layer(new example_layer(*this));
        break;
    case game_state::LOAD_GAME_SELECTION:
        engine.push_layer(new example_layer(*this));
        break;
    case game_state::LOADING_GAME:
        engine.push_layer(new example_layer(*this));
        break;
    case game_state::IN_GAME:
        engine.push_layer(new example_layer(*this));
        break;
    case game_state::EXIT_LOOP:
        // TODO: Exit cleanup
        engine.exit();
        break;
    }
}
