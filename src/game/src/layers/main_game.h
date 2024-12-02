#pragma once
#include <engine.h>
#include "engine/events/key_event.h"
#include <engine/prefabs/prefab.h>
#include "../controlled_layer.h"
#include "../managers/prefabs.h"
#include "../managers/resource_manager.h"


using std::vector;
using glm::vec3;
using engine::skybox;
using engine::game_object;
using engine::material;
using engine::prefab_instance;

class main_game : public controlled_layer
{
private:
    prefabs prefabs;
    resource_manager resource_manager;

    vector<ref<prefab_instance>> instances;


    ref<skybox>			m_skybox{};

    ref<game_object>	m_mannequin{};
    ref<material>		m_mannequin_material{};

    ref<game_object>    m_rock{};
    ref<material>       rock_material{};


    engine::DirectionalLight            m_directionalLight;

    ref<engine::bullet_manager> m_physics_manager{};
    ref<engine::audio_manager>  m_audio_manager{};
    ref<engine::text_manager>	m_text_manager{};

    engine::orthographic_camera       m_2d_camera;
    engine::perspective_camera        m_3d_camera;

public:
    main_game(game_state_manager& state_manager);
    ~main_game() = default;

    void on_update(const engine::timestep& time_step) override;
    void on_render() override;
    void on_event(engine::event& event) override;

private:
    void handle_key_event(engine::key_pressed_event& e);
};
