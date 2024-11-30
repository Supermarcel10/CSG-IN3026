#pragma once
#include <map>
#include <vector>
#include <engine.h>
#include <engine/prefabs/prefab.h>


using std::vector;
using std::map;
using glm::vec3;
using engine::ref;
using engine::prefab_instance;

struct hex_coord
{
    int q;
    int r;

    bool operator==(const hex_coord& other) const;
    bool operator<(const hex_coord& other) const;
};

class hex_grid
{
private:
    std::map<hex_coord, ref<prefab_instance>> tiles;

    const float hex_width;
    const float hex_height;
    const float row_offset;

public:
    explicit hex_grid(float hex_width = 1.0f);

    vec3 hex_to_world(const hex_coord& hex) const;
    hex_coord world_to_hex(const vec3& pos) const;

    void add_tile(const hex_coord& coord, ref<prefab_instance> instance);
    ref<prefab_instance> get_tile(const hex_coord& coord) const;
    vector<hex_coord> get_neighbors(const hex_coord& coord) const;
};
