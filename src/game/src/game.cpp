// --------- Entry Point ---------------
#include "layers/example_layer.h"
#include "engine/core/entry_point.h"
#include "engine/events/key_event.h"


class game : public engine::application 
{
public: 
    game()
    {
        push_layer(new example_layer());
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
                application::exit(); 
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
