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
        state_manager.set_state(GAME_STATE::IN_GAME);
    }

    //void on_event(engine::event& event) override
    //{
    //    application::on_event(event);

    //    engine::event_dispatcher dispatcher(event);
    //    // dispatch event on window X pressed
    //    //dispatcher.dispatch<engine::key_pressed_event>(BIND_EVENT_FN(game::on_key_pressed));
    //}

    //PYRO_TRACE("{0}", static_cast<char>(e.key_code()));
};

engine::application* engine::create_application()
{
    return new game();
}
