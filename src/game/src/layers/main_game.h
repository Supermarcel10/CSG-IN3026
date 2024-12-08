#pragma once
#include <engine.h>
#include "engine/events/key_event.h"
#include <engine/prefabs/prefab.h>
#include "../controlled_layer.h"
#include "../managers/prefab/prefabs.h"
#include "../managers/resource/resource_manager.h"
#include "../core/units/unit.h"
#include "../core/units/attack_unit.h"


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
    ref<engine::bullet_manager> physics_manager{};
    ref<engine::audio_manager>  audio_manager{};
    ref<engine::text_manager>	text_manager{};

    vector<ref<prefab_instance>> instances_;


    ref<skybox>			skybox_{};

    ref<game_object>	mannequin_{};
    ref<material>		mannequin_material_{};

    ref<game_object>    rock_{};
    ref<material>       rock_material_{};

    ref<unit>           catapult_;

    engine::DirectionalLight            directional_light_;

    engine::orthographic_camera       camera_2d_;
    engine::perspective_camera        camera_3d_;

public:
    main_game(game_state_manager& state_manager);

    void on_update(const engine::timestep& time_step) override;
    void on_render() override;
    void on_event(engine::event& event) override;

private:
    void handle_key_event(engine::key_pressed_event& e);
};
