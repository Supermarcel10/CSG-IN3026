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
    uint_fast8_t r = static_cast<uint_fast8_t>(round(-pos.z / hex_height));
    uint_fast8_t q = static_cast<uint_fast8_t>(round((pos.x - (r % 2) * row_offset) / hex_width));
    return { q, r };
}

void hex_grid::add_tile(const hex_coord& coord, ref<prefab_instance> instance, TILE terrain_type)
{
    auto new_hex = std::make_shared<hex>(instance, terrain_type);
    tiles[coord] = new_hex;
    // connect_neighbors(coord, new_hex); // TODO: Consider if there should be a final pass for this so everything gets bound nicely.
}

ref<hex> hex_grid::get_tile(const hex_coord& coord) const
{
    auto it = tiles.find(coord);
    return (it != tiles.end()) ? it->second : nullptr;
}

map<NEIGHBOR_LOCATION, ref<hex>> hex_grid::get_current_neighbors(const hex_coord& coord) const
{
    using std::pair;

    static const vector<pair<int_fast8_t, int_fast8_t>> even_offsets = {
        {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {0, 1}
    };
    static const vector<pair<int8_t, int8_t>> odd_offsets = {
        {1, 1}, {1, 0}, {0, -1}, {-1, 0}, {-1, 1}, {0, 1}
    };

    const auto& offsets = (coord.r % 2 == 0) ? even_offsets : odd_offsets;

    map<NEIGHBOR_LOCATION, ref<hex>> neighbors;
    for (uint_fast8_t i = 0; i < 6; ++i)
    {
        const auto& [dq, dr] = offsets[i];
        hex_coord neighbor_coord{ coord.q + dq, coord.r + dr };

        auto neighbor = get_tile(neighbor_coord);
        if (!neighbor) continue;

        auto loc = static_cast<NEIGHBOR_LOCATION>(i);
        neighbors[loc] = neighbor;
    }

    return neighbors;
}

void hex_grid::connect_neighbors(const hex_coord& coord, ref<hex> hex) const
{
    auto neighbors = get_current_neighbors(coord);
    hex->set_neighbors(neighbors);
}
