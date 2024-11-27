#include "world_generator.h"
#include "managers/prefabs.h"


world_generator::world_generator(hex_grid& grid, const std::string& seed, int size)
    : grid(grid)
    , seed(seed)
    , size(size)
{
    std::seed_seq seed_seq(seed.begin(), seed.end());
    rng.seed(seed_seq);
}

void world_generator::generate_base_terrain()
{
    auto base = prefabs::get(prefabs::TILE::GRASS);

    for (auto row = 0; row < size; ++row)
    {
        for (auto col = 0; col < size; ++col)
        {
            hex_coord coord{ col, row };
            vec3 world_pos = grid.hex_to_world(coord);

            auto instance = base->create_instance(world_pos);
            grid.add_tile(coord, instance);
        }
    }
}

void world_generator::generate()
{
    generate_base_terrain();
}
