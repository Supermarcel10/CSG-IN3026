#pragma once
#include <engine.h>
#include <engine/prefabs/prefab.h>


using engine::ref;
using engine::prefab_instance;

class building
{
private:
    ref<prefab_instance> instance;

    //std::string owner;
    //building_type;
    uint_fast8_t health;

// Game Accessible
public:
    building(ref<prefab_instance> building);

    void update_health(uint_fast8_t health);

 // Namespace accessible
private:
    friend class hex;

    ref<prefab_instance> get_instance() { return instance; };
};
