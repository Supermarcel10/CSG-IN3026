#pragma once
#include <engine/prefabs/prefab.h>


using engine::ref;
using engine::prefab;

enum class COLOR : uint_fast8_t
{
    BLUE,
    GREEN,
    RED,
    YELLOW
};

enum class UNIT : uint_fast8_t
{
    // BANNER?
    // PROJECTILE_ARROW
    // CART_MERCHANT
    SHIP,
    CANNON,
    CATAPULT,
    CART,
    HORSE,
    BASE_UNIT
};

enum class UNIT_TOOL : uint_fast8_t
{
    HELMET,
    BOW,
    SHIELD,
    SWORD,
    SPEAR
};

enum class UNIT_VARIANT : uint_fast8_t
{
    FULL,
    ACCENT
};

enum class PROJECTILE : uint_fast8_t
{
    ARROW,
    CANNON_BALL,
    CATAPULT
};

enum class BUILDING : uint_fast8_t
{
    ARCHERY_RANGE,
    BARRACKS,
    BLACKSMITH,
    CASTLE,
    CHURCH,
    HOME_A,
    HOME_B,
    LUMBERMILL,
    MARKET,
    MINE,
    TAVERN,
    //TOWER_A,
    //TOWER_B,
    //TOWER_BASE,
    //TOWER_CATAPULT,
    WATERMILL,
    WELL,
    WINDMILL // TODO: Test windmill further, since the texture seems malformed.
};

enum class TILE : uint_fast8_t
{
    GRASS,
    WATER,
    COAST,
    RIVER,
    ROAD
};

enum class SEASON : uint_fast8_t
{
    SUMMER,
    SPRING,
    WINTER,
    FALL
};

enum class DECORATION : uint_fast8_t
{
    PINE_TREE
};

class prefabs
{
private:
    static const std::string base_texture;

    static const std::string unit_base_path;
    static const float prefabs::unit_scale;

    static const std::string building_base_path;
    static const float building_scale;

    static const std::string tile_base_path;
    static const float tile_scale;

public:
    static ref<prefab> get(
        UNIT unit,
        COLOR color = COLOR::BLUE,
        UNIT_VARIANT variant = UNIT_VARIANT::FULL
    );

    // TODO: For support of tools later on
    //static ref<prefab> get(
    //    vector<UNIT_TOOL> tools,
    //    COLOR color = COLOR::BLUE,
    //    UNIT_VARIANT variant = UNIT_VARIANT::FULL
    //);

    static ref<prefab> get(
        BUILDING building,
        COLOR color = COLOR::BLUE
    );

    static ref<prefab> get(TILE tile, SEASON season = SEASON::SPRING);
    static ref<prefab> get(DECORATION decoration);

private:
    static std::string color_to_name(COLOR color)
    {
        switch (color)
        {
        case COLOR::BLUE:  return "blue";
        case COLOR::GREEN: return "green";
        case COLOR::RED: return "red";
        case COLOR::YELLOW: return "yellow";
        default: return "yellow";
        }
    }

    static std::string enum_to_name(UNIT unit)
    {
        switch (unit)
        {
        case UNIT::SHIP:  return "ship";
        case UNIT::CANNON: return "cannon";
        case UNIT::CATAPULT: return "catapult";
        case UNIT::CART: return "cart";
        case UNIT::HORSE: return "horse";
        case UNIT::BASE_UNIT: return "unit";
        default: return "error_texture";
        }
    }

    static std::string enum_to_name(UNIT_TOOL tool)
    {
        switch (tool)
        {
        case UNIT_TOOL::HELMET:  return "helmet";
        case UNIT_TOOL::BOW: return "bow";
        case UNIT_TOOL::SHIELD: return "shield";
        case UNIT_TOOL::SWORD: return "sword";
        case UNIT_TOOL::SPEAR: return "spear";
        default: return "error_texture";
        }
    }

    static std::string enum_to_name(UNIT_VARIANT variant)
    {
        switch (variant)
        {
        case UNIT_VARIANT::FULL:  return "_full";
        case UNIT_VARIANT::ACCENT: return "_accent";
        default: return "_full";
        }
    }

    static std::string enum_to_name(PROJECTILE projectile)
    {
        switch (projectile)
        {
        case PROJECTILE::ARROW:  return "arrow";
        case PROJECTILE::CANNON_BALL: return "cannonball";
        case PROJECTILE::CATAPULT: return "catapult";
        default: return "error_texture";
        }
    }

    static std::string enum_to_name(BUILDING building)
    {
        switch (building)
        {
        case BUILDING::ARCHERY_RANGE: return "archeryrange";
        case BUILDING::BARRACKS: return "barracks";
        case BUILDING::BLACKSMITH: return "blacksmith";
        case BUILDING::CASTLE: return "castle";
        case BUILDING::CHURCH: return "church";
        case BUILDING::HOME_A: return "home_a";
        case BUILDING::HOME_B: return "home_b";
        case BUILDING::LUMBERMILL: return "lumbermill";
        case BUILDING::MARKET: return "market";
        case BUILDING::MINE:return "mine";
        case BUILDING::TAVERN: return "tavern";
        //case BUILDING::TOWER_A: return "tower_a";
        //case BUILDING::TOWER_B: return "tower_b";
        //case BUILDING::TOWER_BASE: return "tower_base";
        //case BUILDING::TOWER_CATAPULT: return "tower_catapult";
        case BUILDING::WATERMILL: return "watermill";
        case BUILDING::WELL: return "well";
        case BUILDING::WINDMILL: return "windmill";
        default: return "error_texture";
        }
    }

    static std::string get_season_texture(SEASON season)
    {
        switch (season)
        {
        case SEASON::SUMMER: return "assets/textures/hexagons_medieval_Summer.png";
        case SEASON::SPRING: return "assets/textures/hexagons_medieval_Spring.png";
        case SEASON::WINTER: return "assets/textures/hexagons_medieval_Winter.png";
        case SEASON::FALL: return "assets/textures/hexagons_medieval_Fall.png";
        default: return "assets/textures/hexagons_medieval_Fall.png";
        }
    }

    static std::string enum_to_name(TILE tile)
    {
        switch (tile)
        {
        case TILE::GRASS: return "grass";
        case TILE::WATER: return "water";
        case TILE::COAST: return "coast_waterless_A";
        case TILE::RIVER: return "river";
        case TILE::ROAD: return "road";
        default: return "error_texture";
        }
    }

    static std::string enum_to_name(DECORATION decoration)
    {
        switch (decoration)
        {
        case DECORATION::PINE_TREE: return "pine_tree";
        default: return "error_texture";
        }
    }
};
