// --------- Entry Point ---------------
#include "engine/core/entry_point.h"
#include "engine/events/key_event.h"
#include "managers/game_state_manager.h"
#include <engine/key_codes.h>


class game : public engine::application 
{
private:
    game_state_manager state_manager;

public: 
    game()
        : state_manager(*this)
    {
        state_manager.set_state(game_state::MAIN_MENU);
        //state_manager.set_state(game_state::IN_GAME);
    }

    // TODO: Seems like a good potential for creating event managers for different layers, doing different things
    void on_event(engine::event& event) override
    { 
        application::on_event(event); 

        engine::event_dispatcher dispatcher(event); 
        // dispatch event on window X pressed 
        dispatcher.dispatch<engine::key_pressed_event>(BIND_EVENT_FN(game::on_key_pressed)); 
    } 

    bool on_key_pressed(engine::key_pressed_event& event) 
    { 
        if (event.event_type() == engine::event_type_e::key_pressed) 
        { 
            if (event.key_code() == engine::key_codes::KEY_ESCAPE) 
            { 
                state_manager.set_state(game_state::EXIT_LOOP);
            } 
            //PYRO_TRACE("{0}", static_cast<char>(e.key_code())); 
        } 
        return false; 
    } 
}; 

engine::application* engine::create_application() 
{ 
    return new game(); 
}
