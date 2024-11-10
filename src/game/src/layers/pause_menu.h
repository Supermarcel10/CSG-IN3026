#pragma once
#include <engine.h>
#include "engine/events/key_event.h"
#include "../controlled_layer.h"


class pause_menu : public controlled_layer
{
private:
	// TODO: Find a good way of passing these around as references to each layer?
	engine::ref<engine::text_manager> m_text_manager{};

	engine::orthographic_camera m_2d_camera;

	std::vector<std::string> buttons;
	uint8_t selected_button = 0;

public:
	pause_menu(game_state_manager& state_manager);

	void on_update(const engine::timestep& time_step) override;
	void on_render() override;
	void on_event(engine::event& e) override;

private:
	void handle_key_event(engine::key_pressed_event& e);
};
