#pragma once
#include "hex_grid.h"
#include <string>
#include <random>


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
};
