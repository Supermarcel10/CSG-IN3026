#include "game_state_manager.h"

#include "../layers/main_menu.h"
#include "../layers/main_game.h"
//#include "../layers/pause_menu.h"
//#include "../layers/game_play.h"


game_state_manager::game_state_manager(engine::application& engine)
    : engine(engine)
    , current_state(game_state::MAIN_MENU)
    , current_progress_state(game_progress_state::NOT_IN_GAME)
{}

game_state_manager::~game_state_manager() {
    clear_current_layer();
}

void game_state_manager::set_state(game_state new_state) {
    clear_current_layer();
    current_state = new_state;
    push_new_layer();
}

void game_state_manager::set_progress_state(game_progress_state new_state) {
    current_progress_state = new_state;
    //engine.push_overlay(new pause_menu(*this));
}

game_state game_state_manager::get_state() const {
    return current_state;
}

game_progress_state game_state_manager::get_progress_state() const {
    return current_progress_state;
}

void game_state_manager::push_new_layer() {
    engine::layer* new_layer = nullptr;

    switch (current_state) {
    case game_state::MAIN_MENU:
        new_layer = new main_menu(*this);
        break;
    case game_state::OPTIONS:
        new_layer = new main_game(*this);
        break;
    case game_state::NEW_GAME_SETUP:
        new_layer = new main_game(*this);
        break;
    case game_state::LOAD_GAME_SELECTION:
        new_layer = new main_game(*this);
        break;
    case game_state::LOADING_GAME:
        new_layer = new main_game(*this);
        break;
    case game_state::IN_GAME:
        new_layer = new main_game(*this);
        break;
    case game_state::EXIT_LOOP:
        engine.exit();
        break;
    }

    if (new_layer) {
        m_current_layer = new_layer;
        engine.push_layer(new_layer);
    }
}

void game_state_manager::clear_current_layer() {
    if (m_current_layer) {
        engine.pop_layer(m_current_layer);
        delete m_current_layer;
        m_current_layer = nullptr;
    }
}
