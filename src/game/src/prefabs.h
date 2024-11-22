#pragma once
#include <engine/prefabs/prefab.h>


namespace prefab
{
    using engine::ref;
    using engine::prefab;


//    ref<prefab> register_prefab(
//            const std::string& name,
//            const std::string& model_path,
//            const std::string& texture_path,
//            const glm::vec3& position = glm::vec3(0.f),
//            const glm::vec3& rotation_axis = glm::vec3(0.f),
//            float rotation_amount = 0.f,
//            float scale_factor = 1.f,
//            bool is_static = true,
//            float shininess = 32.0f,
//            const glm::vec3& ambient = glm::vec3(1.0f),
//            const glm::vec3& diffuse = glm::vec3(1.0f),
//            const glm::vec3& specular = glm::vec3(0.1f),
//            float opacity = 1.0f
//    )

    auto hexagons_texture = hexagons_texture;

    namespace building
    {
        auto building_scale = 1.f;

        // TODO: Fix colors, since prior optimisations removed all building colors but blue
        enum class BUILDING_COLOR {
            BLUE,
            GREEN,
            NEUTRAL,
            RED,
            YELLOW
        };

        std::string color_to_path(BUILDING_COLOR color) {
            switch (color) {
                case BUILDING_COLOR::BLUE:  return "blue";
                case BUILDING_COLOR::GREEN: return "green";
                case BUILDING_COLOR::NEUTRAL: return "neutral";
                case BUILDING_COLOR::RED: return "red";
                case BUILDING_COLOR::YELLOW: return "yellow";
                default: return "yellow";
            }
        }

        inline ref<prefab> archery_range(BUILDING_COLOR color)
        {
            return engine::prefab_manager::instance().register_prefab(
                    "archery_range",
                    "assets/models/buildings/archery_range.fbx",
                    hexagons_texture,
                    glm::vec3(0.f, 0.5f, 0.f),
                    glm::vec3(-1.f, 0.f, 0.f),
                    glm::radians(90.0f),
                    building_scale
            );
        }

        inline ref<prefab> barracks(BUILDING_COLOR color)
        {
            return engine::prefab_manager::instance().register_prefab(
                    "barracks",
                    "assets/models/buildings/barracks.fbx",
                    hexagons_texture,
                    glm::vec3(0.f, 0.5f, 0.f),
                    glm::vec3(-1.f, 0.f, 0.f),
                    glm::radians(90.0f),
                    building_scale
            );
        }

        inline ref<prefab> blacksmith(BUILDING_COLOR color)
        {
            return engine::prefab_manager::instance().register_prefab(
                    "blacksmith",
                    "assets/models/buildings/blacksmith.fbx",
                    hexagons_texture,
                    glm::vec3(0.f, 0.5f, 0.f),
                    glm::vec3(-1.f, 0.f, 0.f),
                    glm::radians(90.0f),
                    building_scale
            );
        }

        inline ref<prefab> castle(BUILDING_COLOR color)
        {
            return engine::prefab_manager::instance().register_prefab(
                    "castle",
                    "assets/models/buildings/castle.fbx",
                    hexagons_texture,
                    glm::vec3(0.f, 0.5f, 0.f),
                    glm::vec3(-1.f, 0.f, 0.f),
                    glm::radians(90.0f),
                    building_scale
            );
        }

        inline ref<prefab> church(BUILDING_COLOR color)
        {
            return engine::prefab_manager::instance().register_prefab(
                    "church",
                    "assets/models/buildings/church.fbx",
                    hexagons_texture,
                    glm::vec3(0.f, 0.5f, 0.f),
                    glm::vec3(-1.f, 0.f, 0.f),
                    glm::radians(90.0f),
                    building_scale
            );
        }

        inline ref<prefab> home_a(BUILDING_COLOR color)
        {
            return engine::prefab_manager::instance().register_prefab(
                    "home_a",
                    "assets/models/buildings/home_A.fbx",
                    hexagons_texture,
                    glm::vec3(0.f, 0.5f, 0.f),
                    glm::vec3(-1.f, 0.f, 0.f),
                    glm::radians(90.0f),
                    building_scale
            );
        }

        inline ref<prefab> home_b(BUILDING_COLOR color)
        {
            return engine::prefab_manager::instance().register_prefab(
                    "home_b",
                    "assets/models/buildings/home_B.fbx",
                    hexagons_texture,
                    glm::vec3(0.f, 0.5f, 0.f),
                    glm::vec3(-1.f, 0.f, 0.f),
                    glm::radians(90.0f),
                    building_scale
            );
        }

        inline ref<prefab> lumbermill(BUILDING_COLOR color)
        {
            return engine::prefab_manager::instance().register_prefab(
                    "lumbermill",
                    "assets/models/buildings/lumbermill.fbx",
                    hexagons_texture,
                    glm::vec3(0.f, 0.5f, 0.f),
                    glm::vec3(-1.f, 0.f, 0.f),
                    glm::radians(90.0f),
                    building_scale
            );
        }

        inline ref<prefab> market(BUILDING_COLOR color)
        {
            return engine::prefab_manager::instance().register_prefab(
                    "market",
                    "assets/models/buildings/market.fbx",
                    hexagons_texture,
                    glm::vec3(0.f, 0.5f, 0.f),
                    glm::vec3(-1.f, 0.f, 0.f),
                    glm::radians(90.0f),
                    building_scale
            );
        }

        inline ref<prefab> mine(BUILDING_COLOR color)
        {
            return engine::prefab_manager::instance().register_prefab(
                    "mine",
                    "assets/models/buildings/mine.fbx",
                    hexagons_texture,
                    glm::vec3(0.f, 0.5f, 0.f),
                    glm::vec3(-1.f, 0.f, 0.f),
                    glm::radians(90.0f),
                    building_scale
            );
        }

        inline ref<prefab> tavern(BUILDING_COLOR color)
        {
            return engine::prefab_manager::instance().register_prefab(
                    "tavern",
                    "assets/models/buildings/tavern.fbx",
                    hexagons_texture,
                    glm::vec3(0.f, 0.5f, 0.f),
                    glm::vec3(-1.f, 0.f, 0.f),
                    glm::radians(90.0f),
                    building_scale
            );
        }

        // tower_A
        // tower_B
        // tower_base
        // tower_catapult

        inline ref<prefab> watermill(BUILDING_COLOR color)
        {
            return engine::prefab_manager::instance().register_prefab(
                    "watermill",
                    "assets/models/buildings/watermill.fbx",
                    hexagons_texture,
                    glm::vec3(0.f, 0.5f, 0.f),
                    glm::vec3(-1.f, 0.f, 0.f),
                    glm::radians(90.0f),
                    building_scale
            );
        }

        inline ref<prefab> wellBUILDING_COLOR color()
        {
            return engine::prefab_manager::instance().register_prefab(
                    "well",
                    "assets/models/buildings/well.fbx",
                    hexagons_texture,
                    glm::vec3(0.f, 0.5f, 0.f),
                    glm::vec3(-1.f, 0.f, 0.f),
                    glm::radians(90.0f),
                    building_scale
            );
        }

        // TODO: Test windmill further, since it seems to be pretty weird.
        inline ref<prefab> windmill(BUILDING_COLOR color)
        {
            return engine::prefab_manager::instance().register_prefab(
                    "windmill",
                    "assets/models/buildings/windmill.fbx",
                    hexagons_texture,
                    glm::vec3(0.f, 0.5f, 0.f),
                    glm::vec3(-1.f, 0.f, 0.f),
                    glm::radians(90.0f),
                    building_scale
            );
        }
    }

    namespace tile
    {
        namespace base
        {
            inline ref<prefab> base()
            {
                return engine::prefab_manager::instance().register_prefab(
                    "base",
                    "assets/models/tiles/base/hex_grass.fbx",
                    hexagons_texture,
                    glm::vec3(-1.5f, -1.5f, -1.5f),
                    glm::vec3(0.f),
                    glm::radians(90.0f),
                    1.f
                );
            }
        }
    }

    namespace decoration
    {
        inline ref<prefab> pine_tree()
        {
            return engine::prefab_manager::instance().register_prefab(
                "pine_tree",
                "assets/models/resources/tree/PineTree1.fbx",
                "assets/models/resources/tree/PineTexture.png",
                glm::vec3(0.f, 0.5f, 0.f),
                glm::vec3(-1.f, 0.f, 0.f),
                glm::radians(90.0f),
                3.f
            );
        }
    };
}
