#pragma once
#include <engine.h>
#include <engine/prefabs/prefab.h>
#include "managers/prefabs.h"


using std::map;
using engine::ref;
using engine::prefab_instance;

//class building
//{
//private:
//    std::string owner;
//    //building_type;
//
//public:
//    building();
//    ~building();
//};

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
    //hex_coord coord;
    ref<prefab_instance> instance;
    TILE terrain_type;
    map<NEIGHBOR_LOCATION, ref<hex>> neighbors;
    //building building;
    //bool is_selected = false;
    //bool is_passable = true;

public:
    hex(ref<prefab_instance> instance, TILE terrain_type);

    ref<prefab_instance> get_instance() const { return instance; }

    TILE get_terrain_type() const { return terrain_type; }

    const ref<hex> get_neighbor(NEIGHBOR_LOCATION location) { return neighbors[location]; }
    const map<NEIGHBOR_LOCATION, ref<hex>> get_neighbors() { return neighbors; }
    void set_neighbors(map<NEIGHBOR_LOCATION, ref<hex>> n) { neighbors = n; }
};
