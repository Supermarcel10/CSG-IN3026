#include "prefabs.h"


using glm::vec3;
using glm::radians;

const std::string prefabs::hexagons_texture = "assets/textures/hexagons_medieval_texture.png";

const std::string prefabs::building_base_path = "assets/models/buildings/";
const float prefabs::building_scale = .6f;

const float prefabs::tile_scale = 1.2f;

ref<prefab> prefabs::get(BUILDING building, BUILDING_COLOR color)
{
    auto building_name = enum_to_name(building);
    std::cout << building_name << std::endl;

    return engine::prefab_manager::instance().register_prefab(
        building_name,
        building_base_path + building_name + ".fbx",
        hexagons_texture,
        vec3(0.f, 0.5f, 0.f),
        vec3(-1.f, 0.f, 0.f),
        radians(90.0f),
        building_scale
    );
}

// TODO: Implement properly
ref<prefab> prefabs::get(TILE tile)
{
    std::cout << "Tile " + enum_to_name(tile) << std::endl;

    return engine::prefab_manager::instance().register_prefab(
        "base", // TODO: Make this unique
        "assets/models/tiles/base/hex_grass.fbx",
        hexagons_texture,
        vec3(0.f),
        vec3(-1.f, 0.f, 0.f),
        radians(90.f),
        tile_scale
    );
}

// TODO: Implement properly
ref<prefab> prefabs::get(DECORATION decoration)
{
    auto decoration_name = enum_to_name(decoration);

    return engine::prefab_manager::instance().register_prefab(
        decoration_name,
        "assets/models/resources/tree/PineTree1.fbx",
        "assets/models/resources/tree/PineTexture.png",
        vec3(0.f, 0.5f, 0.f),
        vec3(-1.f, 0.f, 0.f),
        radians(90.0f),
        3.f
    );
}