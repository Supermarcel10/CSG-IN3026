#pragma once


namespace engine
{
    class mesh;

    class rock
    {
    public:
        /// \brief Constructor
        rock(float mean_radius, int subdivisions, float roughness);

        /// \brief Destructor
        ~rock() = default;

        /// \brief Getter methods
        float mean_radius() const { return m_mean_radius; }
        int subdivisions() const { return m_subdivisions; }
        float roughness() const { return m_roughness; }
        ref<engine::mesh> mesh() const { return m_mesh; }

        static ref<rock> create(float mean_radius, int subdivisions, float roughness);

    private:
        /// \brief Fields
        float m_mean_radius;      // Average radius from center to vertices
        int m_subdivisions;       // Level of detail
        float m_roughness;        // How jagged the rock appears
        ref<engine::mesh> m_mesh;
    };
}
