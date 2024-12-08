#include "main_game.h"
#include "platform/opengl/gl_shader.h"
#include "../world_generation/hex_grid.h"
#include "../world_generation/world_generator.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "engine/utils/track.h"
#include <engine/prefabs/prefab.h>


const auto DEBUG = true;

main_game::main_game(game_state_manager& state_manager)
    : controlled_layer(state_manager)
    , resource_manager()
    , camera_2d_(-1.6f, 1.6f, -0.9f, 0.9f)
    , camera_3d_((float)engine::application::window().width(), (float)engine::application::window().height())
{
    // engine::input::anchor_mouse(true);
    // TODO: Fix the anchor mouse not existing.
    engine::application::window().show_mouse_cursor();

    // Initialise audio and play background music
    audio_manager = engine::audio_manager::instance();
    audio_manager->init();
    // audio_manager->load_sound("", engine::sound_type::spatialised, "bounce");
    audio_manager->load_sound("assets/audio/music/vtense_A.wav", "assets/audio/music/vtense_B.wav", "music");
    //audio_manager->play_parallel("music");

    // Initialise the shaders, materials and lights
    auto mesh_shader = engine::renderer::shaders_library()->get("mesh");

    // set color texture unit
    std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->bind();
    std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("lighting_on", true);
    std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gColorMap", 0);

    // #c4c4bc (196, 196, 188)
    directional_light_.Color = vec3(
        (float)196 / 255,
        (float)196 / 255,
        (float)188 / 255);

    directional_light_.AmbientIntensity = 0.55f;
    directional_light_.DiffuseIntensity = 0.75f;
    directional_light_.Direction = glm::normalize(vec3(1.f, -.2f, .2f));

    directional_light_.submit(mesh_shader);

    std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gMatSpecularIntensity", 1.f);
    std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gSpecularPower", 10.f);
    std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("transparency", 1.f);

    auto text_shader = engine::renderer::shaders_library()->get("text_2D");

    std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->bind();
    std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->set_uniform("projection",
        glm::ortho(0.f, (float)engine::application::window().width(), 0.f,
            (float)engine::application::window().height()));

    skybox_ = skybox::create(40.f,
        {
            engine::texture_2d::create("assets/textures/skybox/front.jpg", true),
            engine::texture_2d::create("assets/textures/skybox/right.jpg", true),
            engine::texture_2d::create("assets/textures/skybox/back.jpg", true),
            engine::texture_2d::create("assets/textures/skybox/left.jpg", true),
            engine::texture_2d::create("assets/textures/skybox/top.jpg", true),
            engine::texture_2d::create("assets/textures/skybox/bot.jpg", true)
        });

    // TERRAIN
    hex_grid grid(1.0f);
    // TODO: Create optimisations to not display the sides of tiles if they're unseen.
    world_generator generator(grid, "SEED TBD", 10);
    generator.generate();

    instances_ = grid.get_all_prefab_instances();

    // EXAMPLE BUILDINGS

    auto blue_home = prefabs::get(BUILDING::HOME_A);
    auto red_home = prefabs::get(BUILDING::HOME_A, COLOR::RED);
    auto archery = prefabs::get(BUILDING::ARCHERY_RANGE, COLOR::YELLOW);
    auto barracks = prefabs::get(BUILDING::BARRACKS, COLOR::RED);

    grid.get_tile(hex_coord{ 4, 4 })->build(blue_home, ACTOR::PLAYER);
    grid.get_tile(hex_coord{ 8, 4 })->build(red_home, ACTOR::PLAYER);
    grid.get_tile(hex_coord{ 2, 4 })->build(archery, ACTOR::UNOWNED);

    auto barracks_tile = grid.get_tile(hex_coord{ 6, 4 });
    barracks_tile->build(barracks, ACTOR::ENEMY1);
    barracks_tile->destroy_building();

    // EXAMPLE UNITS

    auto red_ship = prefabs::get(UNIT::SHIP, COLOR::RED, UNIT_VARIANT::ACCENT);
    auto blue_unit = prefabs::get(UNIT::BASE_UNIT, COLOR::BLUE, UNIT_VARIANT::ACCENT);
    auto red_unit = prefabs::get(UNIT::BASE_UNIT, COLOR::RED);
    auto catapult = prefabs::get(UNIT::CATAPULT, COLOR::BLUE);
    auto cannon = prefabs::get(UNIT::CANNON, COLOR::BLUE, UNIT_VARIANT::ACCENT);

    grid.get_tile(hex_coord{ 1, 1 })->spawn_unit(blue_unit, ACTOR::PLAYER);
    grid.get_tile(hex_coord{ 2, 1 })->spawn_unit(blue_unit, ACTOR::PLAYER);
    grid.get_tile(hex_coord{ 1, 2 })->spawn_unit(cannon, ACTOR::PLAYER);
    grid.get_tile(hex_coord{ 2, 2 })->spawn_unit(catapult, ACTOR::PLAYER);

    catapult_ = grid.get_tile(hex_coord{ 2, 2 }).get()->get_unit();

    grid.get_tile(hex_coord{ 4, 2 })->spawn_unit(red_unit, ACTOR::ENEMY1);
    grid.get_tile(hex_coord{ 2, 8 })->spawn_unit(red_ship, ACTOR::ENEMY1);

    // ROCK

    //#494949 (73, 73, 73)
    //#898989 rgb(137, 137, 137)
    //#afafaf rgb(175, 175, 175)
    //#c1c1c1 rgb(193, 193, 193)
    rock_material_ = engine::material::create(
            0.0f,
            vec3(
                    (float) 73 / 255,
                    (float) 73 / 255,
                    (float) 73 / 255), // Unlit color
            vec3(
                    (float) 137 / 255,
                    (float) 137 / 255,
                    (float) 137 / 255), // Direct color
            vec3(
                    (float) 193 / 255,
                    (float) 193 / 255,
                    (float) 193 / 255), // Shine
            1.0f
    );

    auto rock_shape = engine::rock::create(.8f, 20, .2f);
    engine::game_object_properties rock_props;
    rock_props.position = { 2.5f, 0.f, 2.5f };
    rock_props.meshes = { rock_shape->mesh() };
    rock_props.bounding_shape = vec3(0.5f);
    rock_props.is_static = true;
    rock_ = game_object::create(rock_props);

    // BINDING OBJECTS

    text_manager = engine::text_manager::create();
}

void main_game::on_update(const engine::timestep& time_step)
{
    camera_3d_.on_update(time_step);

    // physics_manager->dynamics_world_update(objects, double(time_step));

    audio_manager->on_update(time_step);
    audio_manager->update_with_camera(camera_3d_);
}

void main_game::on_render()
{
    engine::render_command::clear();

    // Set up  shader. (renders textures and materials)
    const auto mesh_shader = engine::renderer::shaders_library()->get("mesh");
    engine::renderer::begin_scene(camera_3d_, mesh_shader);

    // Set up some of the scene's parameters in the shader
    std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gEyeWorldPos", camera_3d_.position());

    // Position the skybox centred on the player and render it
    glm::mat4 skybox_tranform(1.0f);
    skybox_tranform = glm::translate(skybox_tranform, camera_3d_.position());
    for (const auto& texture : skybox_->textures())
    {
        texture->bind();
    }
    engine::renderer::submit(mesh_shader, skybox_, skybox_tranform);

    engine::prefab_renderer::render_all(mesh_shader);

    //rock_material_->submit(mesh_shader);
    //engine::renderer::submit(mesh_shader, rock_);


    // RENDER UI
    // Setup
    const auto window_x = engine::application::window().width();
    const auto window_y = engine::application::window().height();

    // 100 x 100 grid for placement simplicity
    const float x = window_x / 100.f;
    const float y = window_y / 100.f;

    //#050a0c (5, 10, 12)
    const glm::vec4 white_color = glm::vec4(
        (float)255 / 255,
        (float)255 / 255,
        (float)255 / 255,
        1.f
    );

    // Resources
    auto gold_count = std::to_string(resource_manager.get_resource_amount(RESOURCE::GOLD));
    text_manager->render_text("Gold: " + gold_count, x * 30.f, y * 95.f, 0.5f, white_color, "assets/fonts/Title.ttf");

    auto wood_count = std::to_string(resource_manager.get_resource_amount(RESOURCE::WOOD));
    text_manager->render_text("Wood: " + wood_count, x * 40.f, y * 95.f, 0.5f, white_color, "assets/fonts/Title.ttf");

    auto stone_count = std::to_string(resource_manager.get_resource_amount(RESOURCE::STONE));
    text_manager->render_text("Stone: " + stone_count, x * 50.f, y * 95.f, 0.5f, white_color, "assets/fonts/Title.ttf");

    auto metal_count = std::to_string(resource_manager.get_resource_amount(RESOURCE::METAL));
    text_manager->render_text("Metal: " + metal_count, x * 60.f, y * 95.f, 0.5f, white_color, "assets/fonts/Title.ttf");

    engine::renderer::end_scene();
}

void main_game::on_event(engine::event& e)
{
    if (auto keyEvent = dynamic_cast<engine::key_pressed_event*>(&e))
    {
        handle_key_event(*keyEvent);
    }
}

void main_game::handle_key_event(engine::key_pressed_event& e) {
    using engine::key_codes;

    auto key_code = e.key_code();

    if (key_code == key_codes::KEY_ESCAPE || key_code == key_codes::KEY_SPACE)
    {
        // TODO: Investigate issue where pause menu is not triggered first time.
        // Debounce issue?
        //state_manager.toggle_pause();
    }

    // TEMPORARY STUFF
    if (key_code == key_codes::KEY_F)
    {
        if (catapult_ == nullptr) {
            return;
        }

        auto catapult = std::dynamic_pointer_cast<attack_unit>(catapult_);
        if (catapult != nullptr)
        {
            catapult->attack(hex_coord{ 0, 0 });
        }
    }

    // ______________________________________________________
    if (!DEBUG) return;

    if (key_code == key_codes::KEY_F1)
    {
        engine::render_command::toggle_wireframe();
    }

    if (key_code == key_codes::KEY_F9)
    {
        audio_manager->set_parallel_crossfade("music", 1.0f, 1.0f);
    }

    if (key_code == key_codes::KEY_F10)
    {
        audio_manager->set_parallel_crossfade("music", 0.0f, 1.0f);
    }
}
