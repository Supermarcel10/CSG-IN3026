#include "pch.h"
#include "rock.h"
#include <engine.h>
#include <random>


engine::rock::rock(float mean_radius, int subdivisions, float roughness)
        : m_mean_radius(mean_radius)
        , m_subdivisions(subdivisions)
        , m_roughness(roughness)
{
    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-roughness, roughness);

    // Icosahedron base
    const float phi = (1.0f + sqrt(5.0f)) / 2.0f;
    const float len = mean_radius;

    std::vector<mesh::vertex> rock_vertices;

    // Initial icosahedron vertices
    glm::vec3 initial_positions[] = {
            glm::vec3(-len,  0.0f,  phi * len),
            glm::vec3( len,  0.0f,  phi * len),
            glm::vec3(-len,  0.0f, -phi * len),
            glm::vec3( len,  0.0f, -phi * len),

            glm::vec3( 0.0f,  phi * len,  len),
            glm::vec3( 0.0f,  phi * len, -len),
            glm::vec3( 0.0f, -phi * len,  len),
            glm::vec3( 0.0f, -phi * len, -len),

            glm::vec3( phi * len,  len,  0.0f),
            glm::vec3(-phi * len,  len,  0.0f),
            glm::vec3( phi * len, -len,  0.0f),
            glm::vec3(-phi * len, -len,  0.0f)
    };

    // Randomize each vertex height
    for (const auto& pos : initial_positions)
    {
        glm::vec3 random_offset(dis(gen), dis(gen), dis(gen));
        glm::vec3 final_pos = pos + random_offset;

        // Calculate normal (pointing outward from center)
        glm::vec3 normal = glm::normalize(final_pos);

        rock_vertices.push_back({
            final_pos,
            normal,
            glm::vec2(0.0f, 0.0f)
        });
    }

    // Connect icosahedron indecies
    const std::vector<uint32_t> rock_indices = {
            0, 1, 4, 1, 8, 4, 8, 5, 4, 8, 3, 5, 3, 2, 5,
            2, 9, 5, 9, 4, 5, 9, 0, 4, 0, 11, 1, 11, 10, 1,
            10, 8, 1, 10, 3, 8, 3, 7, 2, 7, 6, 2, 6, 9, 2,
            6, 0, 9, 0, 6, 11, 6, 7, 11, 7, 3, 11, 3, 10, 11
    };

    m_mesh = engine::mesh::create(rock_vertices, rock_indices);
}

engine::ref<engine::rock> engine::rock::create(float mean_radius, int subdivisions, float roughness)
{
    return std::make_shared<engine::rock>(mean_radius, subdivisions, roughness);
}
