#pragma once
#include "hex_grid.h"
#include <string>
#include <random>


enum class terrain_type
{
    GRASS,
    COAST,
    WATER
};

class world_generator
{
private:
    std::mt19937 rng;
    hex_grid& grid;
    int size;
    std::string seed;

public:
    world_generator(hex_grid& grid, const std::string& seed, int size);

    void generate();

    const std::string& get_seed() const { return seed; }
    int get_size() const { return size; }

private:
    void generate_base_terrain();
    terrain_type determine_terrain_type(const hex_coord& coord);

    float generate_noise(float x, float y);
    float get_terrain_height(const hex_coord& coord);
};
