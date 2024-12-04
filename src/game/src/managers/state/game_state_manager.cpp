#include "game_state_manager.h"

#include "../layers/main_menu.h"
#include "../layers/main_game.h"
#include "../layers/pause_menu.h"


game_state_manager::game_state_manager(engine::application& engine)
    : engine(engine)
    , current_state(GAME_STATE::MAIN_MENU)
    , game_paused(true)
{}

game_state_manager::~game_state_manager() {
    clear_current_layer();
}

void game_state_manager::set_state(GAME_STATE new_state) {
    clear_current_layer();
    clear_pause_layer();
    current_state = new_state;
    push_new_layer();
}

void game_state_manager::toggle_pause()
{
    game_paused = !game_paused;

    if (game_paused)
        engine.push_overlay(m_pause_layer);
    else
        engine.pop_layer(m_pause_layer);
}

bool game_state_manager::is_game_paused()
{
    return game_paused;
}

GAME_STATE game_state_manager::get_state() const {
    return current_state;
}

void game_state_manager::push_new_layer() {
    engine::layer* new_layer = nullptr;

    switch (current_state) {
    case GAME_STATE::MAIN_MENU:
        new_layer = new main_menu(*this);
        break;
    case GAME_STATE::OPTIONS:
        break;
    case GAME_STATE::NEW_GAME_SETUP:
        current_state = GAME_STATE::IN_GAME;
        m_pause_layer = new pause_menu(*this);
        new_layer = new main_game(*this);
        break;
    case GAME_STATE::LOAD_GAME_SELECTION:
        current_state = GAME_STATE::IN_GAME;
        m_pause_layer = new pause_menu(*this);
        new_layer = new main_game(*this);
        break;
    case GAME_STATE::LOADING_GAME:
        break;
    case GAME_STATE::SAVING_GAME:
        break;
    case GAME_STATE::IN_GAME:
        current_state = GAME_STATE::IN_GAME;
        m_pause_layer = new pause_menu(*this);
        new_layer = new main_game(*this);
        break;
    case GAME_STATE::EXIT_LOOP:
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

void game_state_manager::clear_pause_layer() {
    if (m_pause_layer != nullptr && current_state != GAME_STATE::IN_GAME)
    {
        engine.pop_layer(m_pause_layer);
        delete m_pause_layer;
        m_pause_layer = nullptr;
    }
}
