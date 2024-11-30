#pragma once
#include "engine/core/application.h"


enum class GAME_STATE : uint_fast8_t
{
    EXIT_LOOP,
    MAIN_MENU,
    OPTIONS,
    NEW_GAME_SETUP,
    LOAD_GAME_SELECTION,
    LOADING_GAME,
    SAVING_GAME,
    IN_GAME
};

class game_state_manager
{
private:
    GAME_STATE current_state;
    bool game_paused;

    engine::application& engine;
    engine::layer* m_current_layer = nullptr;
    engine::layer* m_pause_layer = nullptr;

public:
    game_state_manager(engine::application& engine);
    ~game_state_manager();

    void set_state(GAME_STATE new_state);
    GAME_STATE get_state() const;

    void toggle_pause();
    bool is_game_paused();

private:
    void push_new_layer();
    void clear_current_layer();
    void clear_pause_layer();
};
