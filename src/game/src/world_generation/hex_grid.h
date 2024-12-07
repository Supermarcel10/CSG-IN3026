#pragma once
#include <map>
#include <vector>
#include <engine.h>
#include <engine/prefabs/prefab.h>
#include "hex_coord.h"
#include "hex.h"


using std::map;
using std::vector;
using engine::ref;
using engine::prefab_instance;

class hex_grid
{
private:
    std::map<hex_coord, ref<hex>> tiles;

// Game Accessible
public:
    explicit hex_grid(float hex_width = 1.0f);

    ref<hex> get_tile(const hex_coord& coord) const;

    vector<ref<prefab_instance>> get_all_prefab_instances() const;

// Friend Accessible
private:
    friend class world_generator;

    void add_tile(const hex_coord& coord, ref<prefab_instance> instance, TILE terrain_type);

    map<NEIGHBOR_LOCATION, ref<hex>> get_current_neighbors(const hex_coord& coord) const;
    void connect_neighbors(const hex_coord& coord, ref<hex> hex) const;
};
