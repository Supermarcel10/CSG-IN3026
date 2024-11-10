#pragma once
#include "engine/core/application.h"


enum class game_progress_state {
    EXIT_LOOP,
    NOT_IN_GAME,
    SAVING,
    PEACE,
    UNDER_ATTACK
};

enum class game_state {
    EXIT_LOOP,
    MAIN_MENU,
    OPTIONS,
    NEW_GAME_SETUP,
    LOAD_GAME_SELECTION,
    LOADING_GAME,
    IN_GAME
};

class game_state_manager {
private:
    game_state current_state;
    game_progress_state current_progress_state;
    bool game_paused;

    engine::application& engine;
    engine::layer* m_current_layer = nullptr;
    engine::layer* m_pause_layer = nullptr;

public:
    game_state_manager(engine::application& engine);
    ~game_state_manager();

    void set_state(game_state new_state);
    void set_progress_state(game_progress_state new_state);

    void toggle_pause();
    bool is_game_paused();

    game_state get_state() const;
    game_progress_state get_progress_state() const;

private:
    void push_new_layer();
    void clear_current_layer();
    void clear_pause_layer();
};
