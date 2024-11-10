#pragma once
#include <engine.h>
#include "engine/events/key_event.h"
#include "../controlled_layer.h"


class main_game : public controlled_layer
{
private:
    std::vector<engine::ref<engine::game_object>> objects{};
    std::vector<engine::ref<engine::game_object>> collidable_objects{}; // TODO: Look into generalising this in a more efficient manner

    engine::ref<engine::skybox>			m_skybox{};
    engine::ref<engine::game_object>	m_terrain{};

    engine::ref<engine::game_object>	m_torch{};

    engine::ref<engine::game_object>	m_ball{};
    engine::ref<engine::material>		ball_material{};

    engine::ref<engine::game_object>	m_mannequin{};
    engine::ref<engine::material>		m_mannequin_material{};

    engine::ref<engine::game_object>    m_tree{};
    engine::ref<engine::material>       tree_material{};

    engine::ref<engine::game_object>    m_rock{};
    engine::ref<engine::material>       rock_material{};


    engine::DirectionalLight            m_directionalLight;

    engine::ref<engine::bullet_manager> m_physics_manager{};
    engine::ref<engine::audio_manager>  m_audio_manager{};
    float								m_prev_sphere_y_vel = 0.f;
    engine::ref<engine::text_manager>	m_text_manager{};

    engine::orthographic_camera       m_2d_camera;
    engine::perspective_camera        m_3d_camera;

public:
    main_game(game_state_manager& state_manager);
    ~main_game() = default;

    void on_update(const engine::timestep& time_step) override;
    void on_render() override;
    void on_event(engine::event& event) override;

private:
    void check_bounce();
    void handle_key_event(engine::key_pressed_event& e);
};
