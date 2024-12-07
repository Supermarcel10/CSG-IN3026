#pragma once
#include "../properties.h"
#include "../../managers/prefab/prefabs.h"


class building : public instantiable, public ownable, public destroyable
{
private:
    //BUILDING type;

// Game Accessible
public:
    building(ref<prefab_instance> building, ACTOR owner);

 // Friend Accessible
private:
    friend class hex_grid;
    friend class hex;

    void update_health(uint_fast8_t new_health) override;
};
