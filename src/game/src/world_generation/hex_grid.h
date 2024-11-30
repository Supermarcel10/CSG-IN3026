#pragma once
#include <map>
#include <vector>
#include <engine.h>
#include <engine/prefabs/prefab.h>
#include "hex.h"


using std::vector;
using std::map;
using glm::vec3;
using engine::ref;
using engine::prefab_instance;

struct hex_coord
{
    uint_fast8_t q;
    uint_fast8_t r;

    bool operator==(const hex_coord& other) const;
    bool operator<(const hex_coord& other) const;
};

class hex_grid
{
private:
    std::map<hex_coord, ref<hex>> tiles;

    const float hex_width;
    const float hex_height;
    const float row_offset;

// Game accessible
public:
    explicit hex_grid(float hex_width = 1.0f);

    ref<hex> get_tile(const hex_coord& coord) const;

    map<NEIGHBOR_LOCATION, ref<hex>> get_current_neighbors(const hex_coord& coord) const;

// Namespace accessible
private:
    friend class world_generator;

    vec3 hex_to_world(const hex_coord& hex) const;
    hex_coord world_to_hex(const vec3& pos) const;

    void add_tile(const hex_coord& coord, ref<prefab_instance> instance, TILE terrain_type);

    void connect_neighbors(const hex_coord& coord, ref<hex> hex) const;
};
