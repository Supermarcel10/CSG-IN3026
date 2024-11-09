#include "main_menu.h"


main_menu::main_menu(game_state_manager& state_manager)
	: controlled_layer(state_manager)
	, m_2d_camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
	engine::application::window().show_mouse_cursor();

	// Initialise Text Shader
	auto text_shader = engine::renderer::shaders_library()->get("text_2D");

	std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->bind();
	std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->
		set_uniform("projection",
			glm::ortho(0.f, (float) engine::application::window().width(), 0.f,
				(float) engine::application::window().height()));

	m_text_manager = engine::text_manager::create();

	// Set clear color
	//#add8e6 (173, 216, 230)
	engine::render_command::clear_color(
		{
			(float) 173 / 255,
			(float) 216 / 255,
			(float) 230 / 255,
			1.0f
		}
	);

	// Initialise button vector
	buttons.push_back("NEW GAME");
	buttons.push_back("LOAD");
	buttons.push_back("OPTIONS");
	buttons.push_back("EXIT");
}

void main_menu::on_update(const engine::timestep& time_step)
{
	//m_2d_camera.on_update(time_step);
}

void main_menu::on_render()
{
	engine::render_command::clear();

	// RENDER TEXT
	// Setup
	const float window_x = engine::application::window().width();
	const float window_y = engine::application::window().height();

	// 100 x 100 grid for placement simplicity
	const float x = window_x / 100.f;
	const float y = window_y / 100.f;

	//#050a0c (5, 10, 12)
	const glm::vec4 title_color = glm::vec4(
		(float) 5 / 255,
		(float) 10 / 255,
		(float) 12 / 255,
		1.f
	);

    //#050a0c (5, 10, 12)
    const glm::vec4 tooltip_color = glm::vec4(
            (float) 5 / 255,
            (float) 10 / 255,
            (float) 12 / 255,
            1.f
    );

	const glm::vec4 button_unselected_color = glm::vec4(.5f, .5f, .5f, 1.f);
	const glm::vec4 button_selected_color = glm::vec4(0.f, 0.f, 0.f, 1.f);

	// Title
	m_text_manager->render_text("Skyward Citadel", x * 10.f, y * 75.f, 2.f, title_color, "assets/fonts/Regular.ttf");

	// Buttons
	for (size_t i = 0; i < buttons.size(); ++i) {
		const auto is_selected = selected_button == i;

		const auto& button_text =  is_selected ? "> " + buttons[i] : buttons[i];
		const auto& color_to_use = is_selected ? button_selected_color : button_unselected_color;

		const auto y_translate = 55.f - (10.f * i);

		m_text_manager->render_text(button_text, x * 10.f, y * y_translate, 1.f, color_to_use, "assets/fonts/Title.ttf");
	}

    m_text_manager->render_text("W/S - Selection Up/Down", x * 10.f, y * 5.f, .33f, tooltip_color, "assets/fonts/Title.ttf");
    m_text_manager->render_text("SPACE - Select", x * 30.f, y * 5.f, .33f, tooltip_color, "assets/fonts/Title.ttf");

	// TODO: Add mouse support somehow
}

void main_menu::on_event(engine::event& e)
{
	if (auto keyEvent = dynamic_cast<engine::key_pressed_event*>(&e))
	{
		handle_key_event(*keyEvent);
	}
}

void main_menu::handle_key_event(engine::key_pressed_event& e) {
	auto key_code = e.key_code();

	if (key_code == engine::key_codes::KEY_SPACE || key_code == engine::key_codes::KEY_ENTER)
	{
		switch (selected_button)
		{
		case 0: // NEW GAME
			state_manager.set_state(game_state::NEW_GAME_SETUP);
			break;
		case 1: // LOAD
			state_manager.set_state(game_state::LOAD_GAME_SELECTION);
			break;
		case 2: // OPTIONS
			state_manager.set_state(game_state::OPTIONS);
			break;
		case 3: // EXIT
			state_manager.set_state(game_state::EXIT_LOOP);
			break;
		}
	}

	if (key_code == engine::key_codes::KEY_UP || key_code == engine::key_codes::KEY_W)
	{
		if (selected_button != 0) {
			--selected_button;
		}
	}
	else if (key_code == engine::key_codes::KEY_DOWN || key_code == engine::key_codes::KEY_S)
	{
		if (selected_button != buttons.size() - 1)
		{
			++selected_button;
		}
	}
}
