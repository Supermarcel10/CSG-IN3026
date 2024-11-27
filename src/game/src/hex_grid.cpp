#include "hex_grid.h"
#include <cmath>


bool hex_coord::operator==(const hex_coord& other) const
{
    return q == other.q && r == other.r;
}

bool hex_coord::operator<(const hex_coord& other) const
{
    if (q != other.q)
    {
        return q < other.q;
    }
    return r < other.r;
}

hex_grid::hex_grid(float hex_width)
    : hex_width(hex_width)
    , hex_height(hex_width * 0.866f)
    , row_offset(hex_width * 0.5f)
{
}

vec3 hex_grid::hex_to_world(const hex_coord& hex) const
{
    float x = hex.q * hex_width + (hex.r % 2) * row_offset;
    float z = hex.r * hex_height * -1.0f;
    return vec3(x, 0.0f, z);
}

hex_coord hex_grid::world_to_hex(const vec3& pos) const
{
    int r = static_cast<int>(round(-pos.z / hex_height));
    int q = static_cast<int>(round((pos.x - (r % 2) * row_offset) / hex_width));
    return { q, r };
}

void hex_grid::add_tile(const hex_coord& coord, ref<prefab_instance> instance)
{
    tiles[coord] = instance;
}

ref<prefab_instance> hex_grid::get_tile(const hex_coord& coord) const
{
    auto it = tiles.find(coord);
    return (it != tiles.end()) ? it->second : nullptr;
}

vector<hex_coord> hex_grid::get_neighbors(const hex_coord& coord) const
{
    using std::pair;

    static const vector<pair<int, int>> even_offsets = {
        {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {0, 1}
    };
    static const vector<pair<int, int>> odd_offsets = {
        {1, 1}, {1, 0}, {0, -1}, {-1, 0}, {-1, 1}, {0, 1}
    };

    vector<hex_coord> neighbors;
    const auto& offsets = (coord.r % 2 == 0) ? even_offsets : odd_offsets;

    for (const auto& [dq, dr] : offsets)
    {
        neighbors.push_back({ coord.q + dq, coord.r + dr });
    }

    return neighbors;
}
