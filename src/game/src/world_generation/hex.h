#pragma once
#include <engine.h>
#include <engine/prefabs/prefab.h>
#include "../managers/prefab/prefabs.h"
#include "hex_coord.h"
#include "../core/buildings/building.h"
#include "../core/units/unit.h"


using std::map;
using engine::ref;
using engine::prefab_instance;

enum NEIGHBOR_LOCATION : uint_fast8_t
{
    TR,
    R,
    BR,
    BL,
    L,
    TL
};

class hex
{
private:
    hex_coord coord;
    ref<prefab_instance> instance;
    TILE terrain_type;
    map<NEIGHBOR_LOCATION, ref<hex>> neighbors;
    ref<building> building_;
    ref<unit> unit;

    bool is_selected = false;
    bool is_passable = true;

// Game accessible
public:
    void set_is_selected(bool new_value)
    {
        std::cout << "Selected " << static_cast<int>(terrain_type) << std::endl;
        is_selected = new_value;
    };

    void build(ref<prefab> new_building, ACTOR owner);
    void destroy_building();

// Friend Accessible
private:
    friend class hex_grid;

    // Factory class for friend
    static ref<hex> create_hex(hex_coord coord, ref<prefab_instance> instance, TILE terrain_type) {
        return ref<hex>(new hex(coord, instance, terrain_type));
    }

    hex(hex_coord coord, ref<prefab_instance> instance, TILE terrain_type);

    ref<prefab_instance> get_instance() const { return instance; }
    TILE get_terrain_type() const { return terrain_type; }

    const ref<hex> get_neighbor(NEIGHBOR_LOCATION location) { return neighbors[location]; }
    const map<NEIGHBOR_LOCATION, ref<hex>> get_neighbors() { return neighbors; }
    void set_neighbors(map<NEIGHBOR_LOCATION, ref<hex>> n) { neighbors = n; }
};
