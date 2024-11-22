#pragma once
#include <engine/prefabs/prefab.h>


namespace prefab
{
    namespace building
    {

    }

    namespace tile
    {

    }

    namespace decoration
    {
        inline engine::ref<engine::prefab> pine_tree()
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
