#pragma once
#include "unit.h"
#include "../../world_generation/hex_coord.h"
#include "../../managers/prefab/prefabs.h"


class attack_unit : public unit
{
private:
	uint_fast8_t range_;

public:
	void attack(hex_coord coord)
	{
		std::cout << "Attacking!" << std::endl;
	};

    attack_unit(
        UNIT_CLASS unit_class,
        UNIT unit_type,
        ref<prefab_instance> instance,
        ACTOR owner,
        uint_fast8_t range
    )
        : unit(unit_class, unit_type, instance, owner)
        , range_(range)
    {
    }
};
