#include "hex_coord.h"
#include <cmath>


// Static init
float hex_coord::hex_width = 1.0f;
float hex_coord::hex_height = 0.866f;
float hex_coord::row_offset = 0.5f;

void hex_coord::init(float width) {
    hex_width = width;
    hex_height = width * 0.866f;
    row_offset = width * 0.5f;
}

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

glm::vec3 hex_coord::to_world() const
{
    float x = q * hex_width + (r % 2) * row_offset;
    float z = r * hex_height * -1.0f;
    return glm::vec3(x, 0.0f, z);
}

hex_coord hex_coord::from_world(const glm::vec3& pos)
{
    uint_fast8_t r = static_cast<uint_fast8_t>(round(-pos.z / hex_height));
    uint_fast8_t q = static_cast<uint_fast8_t>(round((pos.x - (r % 2) * row_offset) / hex_width));
    return { q, r };
}
