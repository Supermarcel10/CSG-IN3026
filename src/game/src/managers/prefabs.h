#pragma once
#include <engine/prefabs/prefab.h>


using engine::ref;
using engine::prefab;

class prefabs
{
private:
    static const std::string hexagons_texture;

    static const std::string building_base_path;
    static const float building_scale;

    static const std::string tile_base_path;
    static const float tile_scale;

public:
    // TODO: Fix colors, since prior optimisations removed all building colors but blue
    enum class BUILDING_COLOR
    {
        BLUE,
        GREEN,
        NEUTRAL,
        RED,
        YELLOW
    };

    enum class BUILDING
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

    enum class TILE
    {
        GRASS,
        WATER,
        COAST,
        RIVER,
        ROAD
    };

    enum class DECORATION
    {
        PINE_TREE
    };

    static ref<prefab> get(BUILDING building, BUILDING_COLOR color = BUILDING_COLOR::BLUE);
    static ref<prefab> get(TILE tile);
    static ref<prefab> get(DECORATION decoration);

private:
    static std::string color_to_name(BUILDING_COLOR color)
    {
        switch (color)
        {
        case BUILDING_COLOR::BLUE:  return "blue";
        case BUILDING_COLOR::GREEN: return "green";
        case BUILDING_COLOR::NEUTRAL: return "neutral";
        case BUILDING_COLOR::RED: return "red";
        case BUILDING_COLOR::YELLOW: return "yellow";
        default: return "yellow";
        }
    }

    static std::string enum_to_name(BUILDING color)
    {
        switch (color)
        {
        case BUILDING::ARCHERY_RANGE: return "archery_range";
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
        }
    }

    static std::string enum_to_name(DECORATION decoration)
    {
        switch (decoration)
        {
        case DECORATION::PINE_TREE: return "pine_tree";
        }
    }
};
