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

float world_generator::generate_noise(float x, float y)
{
    float frequency1 = 4.0f;
    float frequency2 = 8.0f;

    float scaled_x = x / static_cast<float>(size);
    float scaled_y = y / static_cast<float>(size);

    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    float noise1 = std::sin(scaled_x * frequency1 * 3.14159f) *
        std::cos(scaled_y * frequency1 * 3.14159f);

    float noise2 = std::sin(scaled_x * frequency2 * 3.14159f) *
        std::cos(scaled_y * frequency2 * 3.14159f);

    float random_value = dist(rng) * 0.2f;  // Reduced influence
    return (noise1 * 0.7f + noise2 * 0.3f + random_value + 1.0f) * 0.5f;
}

float world_generator::get_terrain_height(const hex_coord& coord)
{
    // Convert hex coordinates to a continuous space
    float x = coord.q + (coord.r % 2) * 0.5f;
    float y = coord.r * 0.866f;

    // Base height
    float height = generate_noise(x, y);

    // Distance from center
    float center_x = size * 0.5f;
    float center_y = size * 0.5f;
    float dx = (x - center_x) / size;
    float dy = (y - center_y) / size;
    float distance_from_center = std::sqrt(dx * dx + dy * dy);

    height = height * (1.0f - distance_from_center * 0.5f);

    return height;
}

terrain_type world_generator::determine_terrain_type(const hex_coord& coord)
{
    float height = get_terrain_height(coord);

    // 30% water/land ratio
    const float WATER_LEVEL = 0.3f;
    const float COAST_THRESHOLD = 0.05f;

    // WATER
    if (height < WATER_LEVEL)
    {
        int water_neighbors = 0;
        auto neighbors = grid.get_neighbors(coord);

        // Check all neighbors for water
        for (const auto& neighbor : neighbors)
        {
            if (neighbor.q <= coord.q && neighbor.r <= coord.r)
            {
                auto neighbor_tile = grid.get_tile(neighbor);
                if (get_terrain_height(neighbor) < WATER_LEVEL)
                {
                    ++water_neighbors;
                }
            }
        }

        // If we have water neighbors or we're well below water level, make it water
        if (water_neighbors > 0 || height < WATER_LEVEL - 0.1f)
        {
            return terrain_type::WATER;
        }
    }

    // COAST
    if (height >= WATER_LEVEL && height < WATER_LEVEL + COAST_THRESHOLD)
    {
        auto neighbors = grid.get_neighbors(coord);
        int water_neighbors = 0;

        // Check all neighbors for water
        for (const auto& neighbor : neighbors)
        {
            float neighbor_height = get_terrain_height(neighbor);
            if (neighbor_height < WATER_LEVEL)
            {
                ++water_neighbors;
            }
        }

        if (water_neighbors > 0)
        {
            return terrain_type::COAST;
        }
    }

    return terrain_type::GRASS;
}

void world_generator::generate_base_terrain()
{
    auto grass_base = prefabs::get(prefabs::TILE::GRASS);
    auto coast_base = prefabs::get(prefabs::TILE::COAST);
    auto water_base = prefabs::get(prefabs::TILE::WATER);

    std::vector<terrain_type> terrain_map;
    terrain_map.reserve(size * size);

    // TODO: Fix coast generation, since it's a bit weird
    // TODO: Use correct coast model.
    // TODO: Add transitions.
    // TODO: Add hills and y level.

    for (auto row = 0; row < size; ++row)
    {
        for (auto col = 0; col < size; ++col)
        {
            hex_coord coord{ col, row };
            terrain_type type = determine_terrain_type(coord);
            terrain_map.push_back(type);

            vec3 world_pos = grid.hex_to_world(coord);

            ref<prefab_instance> instance;
            switch (type)
            {
            case terrain_type::WATER:
                instance = water_base->create_instance(world_pos);
                break;

            case terrain_type::COAST:
                instance = grass_base->create_instance(world_pos);
                break;

            case terrain_type::GRASS:
            default:
                instance = grass_base->create_instance(world_pos);
                break;
            }

            grid.add_tile(coord, instance);
        }
    }
}

void world_generator::generate()
{
    generate_base_terrain();
}
