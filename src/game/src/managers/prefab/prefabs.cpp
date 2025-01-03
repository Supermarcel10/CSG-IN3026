#include "prefabs.h"


using glm::vec3;
using glm::radians;

const std::string prefabs::base_texture = prefabs::get_season_texture(SEASON::SPRING);

const std::string prefabs::unit_base_path = "assets/models/units/";
const float prefabs::unit_scale = .6f;

const std::string prefabs::building_base_path = "assets/models/buildings/";
const float prefabs::building_scale = .6f;

const std::string prefabs::tile_base_path = "assets/models/tiles";
const float prefabs::tile_scale = 1.2f;

ref<prefab> prefabs::get(
    UNIT unit,
    COLOR color,
    UNIT_VARIANT variant
)
{
    auto unit_name = enum_to_name(unit);
    auto unit_color = color_to_name(color);
    auto unit_variant = enum_to_name(variant);

    auto name = unit_color + "/" + unit_name + unit_variant;

    // TODO: Debug why offset isn't actually being applied in any of these cases
    vec3 offset = vec3(0.f, 0.5f, 0.f);
    if (unit == UNIT::SHIP)
    {
        offset = vec3(0.f, -0.5f, 0.f);
    }

    return engine::prefab_manager::instance().register_prefab(
        name,
        unit_base_path + name + ".fbx",
        base_texture,
        offset,
        vec3(-1.f, 0.f, 0.f),
        radians(90.0f),
        unit_scale
    );
}

ref<prefab> prefabs::get(
    BUILDING building,
    COLOR color
)
{
    auto building_name = enum_to_name(building);
    auto building_color = color_to_name(color);

    auto name = building_color + "/" + building_name;

    return engine::prefab_manager::instance().register_prefab(
        name,
        building_base_path + name + ".fbx",
        base_texture,
        vec3(0.f, 0.5f, 0.f),
        vec3(-1.f, 0.f, 0.f),
        radians(90.0f),
        building_scale
    );
}

ref<prefab> prefabs::get(TILE tile, SEASON season)
{
    auto tile_name = enum_to_name(tile);
    auto season_texture = get_season_texture(season);

    auto name = tile_name + std::to_string(std::underlying_type_t<SEASON>(season));

    return engine::prefab_manager::instance().register_prefab(
        tile_name,
        tile_base_path + "/base/" + tile_name + ".fbx",
        season_texture,
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
