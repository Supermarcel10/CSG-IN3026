#include "pause_menu.h"


pause_menu::pause_menu(game_state_manager& state_manager)
	: controlled_layer(state_manager)
	, m_2d_camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
	engine::application::window().show_mouse_cursor();

	// Initialise Text Shader
	auto text_shader = engine::renderer::shaders_library()->get("text_2D");

	std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->bind();
	std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->
		set_uniform("projection",
			glm::ortho(0.f, (float)engine::application::window().width(), 0.f,
				(float)engine::application::window().height()));

	m_text_manager = engine::text_manager::create();

	// Set clear color
	//#050a0c (5, 10, 12)
	engine::render_command::clear_color(
		{
			(float)5 / 255,
			(float)10 / 255,
			(float)12 / 255,
			0.4f
		}
	);

	// Initialise button vector
	buttons.push_back("SAVE");
	buttons.push_back("LOAD");
	buttons.push_back("QUIT");
	buttons.push_back("RETURN TO MENU");
}

void pause_menu::on_update(const engine::timestep& time_step)
{
	//m_2d_camera.on_update(time_step);
}

void pause_menu::on_render()
{
	engine::render_command::clear();

	// RENDER TEXT
	// Setup
	const auto window_x = engine::application::window().width();
	const auto window_y = engine::application::window().height();

	// 100 x 100 grid for placement simplicity
	const float x = window_x / 100.f;
	const float y = window_y / 100.f;

	const glm::vec4 title_color = glm::vec4(1.f, 1.f, 1.f, 1.f);

	const glm::vec4 button_unselected_color = glm::vec4(.5f, .5f, .5f, 1.f);
	const glm::vec4 button_selected_color = glm::vec4(0.f, 0.f, 0.f, 1.f);

	// Title
	m_text_manager->render_text("GAME PAUSED", x * 10.f, y * 75.f, 2.f, title_color, "assets/fonts/Title.ttf");

	// Buttons
	for (size_t i = 0; i < buttons.size(); ++i) {
		const auto is_selected = selected_button == i;

		const auto& button_text = is_selected ? "> " + buttons[i] : buttons[i];
		const auto& color_to_use = is_selected ? button_selected_color : button_unselected_color;

		const auto y_translate = 55.f - (10.f * i);

		m_text_manager->render_text(button_text, x * 10.f, y * y_translate, 1.f, color_to_use, "assets/fonts/Title.ttf");
	}

	// TODO: Add mouse support somehow
	// TODO: Add tooltips?
}

void pause_menu::on_event(engine::event& e)
{
	if (auto keyEvent = dynamic_cast<engine::key_pressed_event*>(&e))
	{
		handle_key_event(*keyEvent);
	}
}

void pause_menu::handle_key_event(engine::key_pressed_event& e) {
	auto key_code = e.key_code();

	if (key_code == engine::key_codes::KEY_SPACE || key_code == engine::key_codes::KEY_ENTER)
	{
		switch (selected_button)
		{
		case 0: // SAVE
			break;
		case 1: // LOAD
			break;
		case 2: // EXIT
            // TODO: Save game prior
            state_manager.set_state(GAME_STATE::EXIT_LOOP);
			break;
		case 3: // RETURN TO MENU
            // TODO: Save game prior
            // TODO: Investigate issue where game crashes here
            state_manager.set_state(GAME_STATE::MAIN_MENU);
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

	if (key_code == engine::key_codes::KEY_ESCAPE)
	{
        state_manager.toggle_pause();
	}
}
