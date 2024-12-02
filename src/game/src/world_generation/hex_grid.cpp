#include "hex_grid.h"
#include <cmath>


hex_grid::hex_grid(float hex_width)
{
    hex_coord::init(hex_width);
}

void hex_grid::add_tile(const hex_coord& coord, ref<prefab_instance> instance, TILE terrain_type)
{
    auto new_hex = hex::create_hex(coord, instance, terrain_type);
    tiles[coord] = new_hex;
    // connect_neighbors(coord, new_hex); // TODO: Consider if there should be a final pass for this so everything gets bound nicely.
}

ref<hex> hex_grid::get_tile(const hex_coord& coord) const
{
    auto it = tiles.find(coord);
    return (it != tiles.end()) ? it->second : nullptr;
}

vector<ref<prefab_instance>> hex_grid::get_all_prefab_instances() const {
    vector<ref<prefab_instance>> instances;
    instances.reserve(tiles.size());

    for (const auto& [coord, hex_tile] : tiles) {
        instances.push_back(hex_tile->get_instance());

        ref<building> building = hex_tile->building_;
        if (building) {
            instances.push_back(building->get_instance());
        }
    }

    return instances;
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
