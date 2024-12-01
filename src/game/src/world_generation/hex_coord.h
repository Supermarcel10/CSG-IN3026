#pragma once
#include <glm/vec3.hpp>
#include <cstdint>


using glm::vec3;

struct hex_coord
{
    uint_fast8_t q;
    uint_fast8_t r;

    static float hex_width;
    static float hex_height;
    static float row_offset;

    static void init(float width);
    bool operator==(const hex_coord& other) const;
    bool operator<(const hex_coord& other) const;

    vec3 to_world() const;
    static hex_coord from_world(const glm::vec3& pos);
};
