#include "main_game.h"
#include "platform/opengl/gl_shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "engine/utils/track.h"
#include <engine/prefabs/prefab.h>


main_game::main_game(game_state_manager& state_manager)
        : controlled_layer(state_manager)
        , m_2d_camera(-1.6f, 1.6f, -0.9f, 0.9f)
        , m_3d_camera((float)engine::application::window().width(), (float)engine::application::window().height())
{
//    engine::input::anchor_mouse(true);
// TODO: Fix the anchor mouse not existing.
    engine::application::window().show_mouse_cursor();

    // Initialise audio and play background music
    m_audio_manager = engine::audio_manager::instance();
    m_audio_manager->init();
//    m_audio_manager->load_sound("", engine::sound_type::spatialised, "bounce");
    m_audio_manager->load_sound("assets/audio/music/peace/2-uplifting.wav", engine::sound_type::track, "music");
    m_audio_manager->play("music");
    m_audio_manager->volume("music", .0f);
// TODO: Expand the audio manager to support layering and transition.

    // Initialise the shaders, materials and lights
    auto mesh_shader = engine::renderer::shaders_library()->get("mesh");

    // set color texture unit
    std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->bind();
    std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("lighting_on", true);
    std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gColorMap", 0);

    // #c4c4bc (196, 196, 188)
    m_directionalLight.Color = glm::vec3(
            (float) 196 / 255,
            (float) 196 / 255,
            (float) 188 / 255);

    m_directionalLight.AmbientIntensity = 0.55f;
    m_directionalLight.DiffuseIntensity = 0.75f;
    m_directionalLight.Direction = glm::normalize(glm::vec3(1.f, -.2f, .2f));

    m_directionalLight.submit(mesh_shader);

    std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gMatSpecularIntensity", 1.f);
    std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gSpecularPower", 10.f);
    std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("transparency", 1.f);

    auto text_shader = engine::renderer::shaders_library()->get("text_2D");

    std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->bind();
    std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->set_uniform("projection",
                                                                           glm::ortho(0.f, (float)engine::application::window().width(), 0.f,
                                                                                      (float)engine::application::window().height()));

    m_mannequin_material = engine::material::create(1.0f, glm::vec3(0.5f, 0.5f, 0.5f),
                                                    glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 1.0f);

    m_skybox = engine::skybox::create(50.f,
                                      { engine::texture_2d::create("assets/textures/skybox/front.jpg", true),
                                        engine::texture_2d::create("assets/textures/skybox/right.jpg", true),
                                        engine::texture_2d::create("assets/textures/skybox/back.jpg", true),
                                        engine::texture_2d::create("assets/textures/skybox/left.jpg", true),
                                        engine::texture_2d::create("assets/textures/skybox/top.jpg", true),
                                        engine::texture_2d::create("assets/textures/skybox/bot.jpg", true)
                                      });

    // Orc warrior from https://sketchfab.com/3d-models/orc-warrior-4f8e272891a449c8935285eab8a3a2f9
    std::vector<engine::ref<engine::texture_2d>> mannequin_textures;
    mannequin_textures.push_back(engine::texture_2d::create("assets/textures/warrior_DefaultMaterial_BaseColor.png", false));
    mannequin_textures.push_back(engine::texture_2d::create("assets/textures/weapon_DefaultMaterial_BaseColor.png", false));
    engine::ref<engine::skinned_mesh> m_skinned_mesh = engine::skinned_mesh::create("assets/models/animated/warrior/warrior_animation.fbx");
    m_skinned_mesh->switch_root_movement(false);
    m_skinned_mesh->set_textures(mannequin_textures);

    engine::game_object_properties mannequin_props;
    mannequin_props.animated_mesh = m_skinned_mesh;
    mannequin_props.scale = glm::vec3(0.7f);
    mannequin_props.position = glm::vec3(2.0f, 0.5f, -5.0f);
    mannequin_props.textures = mannequin_textures;
    mannequin_props.type = 0;
    mannequin_props.bounding_shape = m_skinned_mesh->size() / 2.f * mannequin_props.scale.x;
    m_mannequin = engine::game_object::create(mannequin_props);

    // Load the terrain texture and create a terrain mesh. Create a terrain object. Set its properties
    auto terrain_textures = { engine::texture_2d::create("assets/textures/terrain.bmp", false) };
    engine::ref<engine::terrain> terrain_shape = engine::terrain::create(5.f, 0.5f, 5.f);
    engine::game_object_properties terrain_props;
    terrain_props.meshes = { terrain_shape->mesh() };
    terrain_props.textures = terrain_textures;
    terrain_props.is_static = true;
    terrain_props.type = 0;
    terrain_props.bounding_shape = glm::vec3(5.f, 0.5f, 5.f);
    terrain_props.restitution = 0.92f;
    m_terrain = engine::game_object::create(terrain_props);

//    glm::mat4 terrain_transform(1.0f);
//    terrain_transform = glm::translate(terrain_transform, glm::vec3(0.f, -0.5f, 0.f));

    // CLOUD
    // TODO: See if the cloud can be made into a primitive instead to hit the requirements for Milestone 2.

    // TODO: Fix issue where only one type of prefab can be loaded at once!
    //auto home =  prefabs::get(prefabs::BUILDING::HOME_A);
    //home->create_instance(glm::vec3(4.f, 0.5f, -5.0f));

    auto tree = prefabs::get(prefabs::DECORATION::PINE_TREE);
    tree->create_instance(glm::vec3(4.f, 0.5f, -5.0f));
    tree->create_instance(glm::vec3(4.f, 0.5f, -3.0f));
    tree->create_instance(glm::vec3(4.f, 0.5f, 0.0f));

    // Base
    // TODO: Test why base does not show
//    auto base = prefabs::get(prefabs::TILE::GRASS);
//    base->create_instance(glm::vec3(0.f, 0.5f, 0.f));

    // ROCK

    //#494949 (73, 73, 73)
    //#898989 rgb(137, 137, 137)
    //#afafaf rgb(175, 175, 175)
    //#c1c1c1 rgb(193, 193, 193)
    rock_material = engine::material::create(
            0.0f,
            glm::vec3(
                    (float) 73 / 255,
                    (float) 73 / 255,
                    (float) 73 / 255), // Unlit color
            glm::vec3(
                    (float) 137 / 255,
                    (float) 137 / 255,
                    (float) 137 / 255), // Direct color
            glm::vec3(
                    (float) 193 / 255,
                    (float) 193 / 255,
                    (float) 193 / 255), // Shine
            1.0f
    );

    auto rock_shape = engine::rock::create(.8f, 20, .2f);
    engine::game_object_properties rock_props;
    rock_props.position = { 2.5f, 0.f, 2.5f };
    rock_props.meshes = { rock_shape->mesh() };
    rock_props.bounding_shape = glm::vec3(0.5f);
    rock_props.is_static = true;
    m_rock = engine::game_object::create(rock_props);


    // BINDING OBJECTS
    objects.push_back(m_terrain);
    collidable_objects.push_back(m_terrain);
    objects.push_back(m_rock);

    m_physics_manager = engine::bullet_manager::create(collidable_objects);

    m_text_manager = engine::text_manager::create();

    m_skinned_mesh->switch_animation(6);
}

void main_game::on_update(const engine::timestep& time_step)
{
    m_3d_camera.on_update(time_step);

    m_physics_manager->dynamics_world_update(objects, double(time_step));

    m_mannequin->animated_mesh()->on_update(time_step);

    m_audio_manager->update_with_camera(m_3d_camera);
}

void main_game::on_render()
{
    engine::render_command::clear_color({0.2f, 0.3f, 0.3f, 1.0f});
    engine::render_command::clear();

    // Set up  shader. (renders textures and materials)
    const auto mesh_shader = engine::renderer::shaders_library()->get("mesh");
    engine::renderer::begin_scene(m_3d_camera, mesh_shader);

    // Set up some of the scene's parameters in the shader
    std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gEyeWorldPos", m_3d_camera.position());

    // Position the skybox centred on the player and render it
    glm::mat4 skybox_tranform(1.0f);
    skybox_tranform = glm::translate(skybox_tranform, m_3d_camera.position());
    for (const auto& texture : m_skybox->textures())
    {
        texture->bind();
    }
    engine::renderer::submit(mesh_shader, m_skybox, skybox_tranform);

    engine::renderer::submit(mesh_shader, m_terrain);

    engine::prefab_renderer::render_all(mesh_shader);

    rock_material->submit(mesh_shader);
    engine::renderer::submit(mesh_shader, m_rock);

    m_mannequin_material->submit(mesh_shader);
    engine::renderer::submit(mesh_shader, m_mannequin);

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
    auto key_code = e.key_code();

    if (key_code == engine::key_codes::KEY_ESCAPE || key_code == engine::key_codes::KEY_SPACE)
    {
        // TODO: Investigate issue where pause menu is not triggered first time.
        // Debounce issue?
        state_manager.toggle_pause();
    }
}
