#pragma once
#include "hex_grid.h"
#include <string>
#include <random>
#include "../managers/prefab/prefabs.h"


class world_generator
{
private:
    std::mt19937 rng;
    hex_grid& grid;
    uint_fast16_t size;
    std::string seed;
    float water_level;

public:
    world_generator(hex_grid& grid, const std::string& seed, uint16_t size);

    void generate();

    const std::string& get_seed() const { return seed; }
    uint16_t get_size() const { return size; }

private:
    void generate_base_terrain();
    TILE determine_terrain_type(const hex_coord& coord);

    float generate_noise(float x, float y);
    float get_terrain_height(const hex_coord& coord);

    static ref<prefab> get_base(TILE type) { return prefabs::get(type); };
};
