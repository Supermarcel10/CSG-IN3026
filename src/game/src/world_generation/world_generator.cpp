#include "world_generator.h"
#include "../managers/prefabs.h"


world_generator::world_generator(hex_grid& grid, const std::string& seed, uint16_t size)
    : grid(grid)
    , seed(seed)
    , size(size)
{
    std::seed_seq seed_seq(seed.begin(), seed.end());
    rng.seed(seed_seq);

    std::uniform_real_distribution<float> water_dist(-0.25f, 0.05f);
    rng.seed(std::hash<std::string>{}(seed + "water_level"));
    water_level = water_dist(rng);;
}

float world_generator::generate_noise(float x, float y) {
    float scaled_x = x / static_cast<float>(size);
    float scaled_y = y / static_cast<float>(size);

    const uint_fast8_t control_points = (size / 4) + 1;

    uint_fast8_t grid_x = static_cast<int>(scaled_x * (control_points - 1));
    uint_fast8_t grid_y = static_cast<int>(scaled_y * (control_points - 1));

    // Calculate local coordinates within the cell
    float local_x = (scaled_x * (control_points - 1)) - grid_x;
    float local_y = (scaled_y * (control_points - 1)) - grid_y;

    // Generate stable random heights for grid points
    auto get_height = [this](uint_fast8_t x, uint_fast8_t y, uint_fast8_t control_points) -> float {
        std::uniform_real_distribution<float> dist(-0.5f, 0.5f);
        rng.seed(std::hash<std::string>{}(seed + std::to_string(x) + "," + std::to_string(y)));
        float base = dist(rng);

        // Reduce height variation at edges to prevent extreme terrain at borders
        float edge_factor = 1.0f;
        if (x == 0 || x == control_points - 1 || y == 0 || y == control_points - 1) {
            edge_factor = 0.7f;
        }

        return base * edge_factor;
    };

    // Get heights for the four corners of the current grid cell
    float h00 = get_height(grid_x, grid_y, control_points);
    float h10 = get_height(grid_x + 1, grid_y, control_points);
    float h01 = get_height(grid_x, grid_y + 1, control_points);
    float h11 = get_height(grid_x + 1, grid_y + 1, control_points);

    // Bilinear interpolation
    float x1 = h00 * (1 - local_x) + h10 * local_x;
    float x2 = h01 * (1 - local_x) + h11 * local_x;

    return x1 * (1 - local_y) + x2 * local_y;
}

float world_generator::get_terrain_height(const hex_coord& coord)
{
    // Convert hex coordinates to world coordinates
    float x = coord.q + (coord.r % 2) * 0.5f;
    float y = coord.r * 0.866f;

    float height = generate_noise(x, y);

    // Small variation
    std::uniform_real_distribution<float> small_noise(-0.05f, 0.05f);
    rng.seed(std::hash<std::string>{}(seed + std::to_string(x) + "," + std::to_string(y)));
    height += small_noise(rng);

    return height;
}

TILE world_generator::determine_terrain_type(const hex_coord& coord)
{
    float height = get_terrain_height(coord);

    const float COAST_THRESHOLD = 0.05f;

    // WATER
    if (height < water_level)
    {
        return TILE::WATER;
    }

    // COAST
    //if (height >= WATER_LEVEL && height < WATER_LEVEL + COAST_THRESHOLD)
    //{
    //    auto neighbors = current_hex->get_neighbors();
    //    int water_neighbors = 0;

    //    // Check all neighbors for water
    //    for (const auto& neighbor : neighbors)
    //    {
    //        float neighbor_height = get_terrain_height(neighbor);
    //        if (neighbor_height < WATER_LEVEL)
    //        {
    //            ++water_neighbors;
    //        }
    //    }

    //    if (water_neighbors > 0)
    //    {
    //        return terrain_type::COAST;
    //    }
    //}

    return TILE::GRASS;
}

void world_generator::generate_base_terrain()
{
    // TODO: Find a better solution for this!
    map<TILE, ref<prefab>> bases =
    {
        {TILE::GRASS, prefabs::get(TILE::GRASS)},
        {TILE::COAST, prefabs::get(TILE::COAST)},
        {TILE::WATER, prefabs::get(TILE::WATER)},
    };

    // TODO: Fix coast generation, since it's a bit weird
    // TODO: Use correct coast model.
    // TODO: Add transitions.
    // TODO: Add hills and y level.

    for (uint_fast8_t row = 0; row < size; ++row)
    {
        for (uint_fast8_t col = 0; col < size; ++col)
        {
            hex_coord coord{ col, row };
            vec3 world_pos = coord.to_world();

            auto terrain_type = determine_terrain_type(coord);
            ref<prefab_instance> instance = bases[terrain_type]->create_instance(world_pos);

            grid.add_tile(coord, instance, terrain_type);
        }
    }
}

void world_generator::generate()
{
    generate_base_terrain();
}
