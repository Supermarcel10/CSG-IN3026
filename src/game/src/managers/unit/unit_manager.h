#pragma once
#include <engine.h>
#include "../../core/units/unit_factory.h"


using std::vector;
using engine::ref;

// TODO: Look into making this into a singleton rather than static!
class unit_manager
{
private:
    static vector<ref<unit>> units;

public:
    static ref<unit> add_unit(
        UNIT unit_type,
        ref<prefab_instance> instance,
        ACTOR owner
    )
    {
        auto created_unit = unit_factory::create_unit(unit_type, instance, owner);
        units.push_back(created_unit);

        return created_unit;
    }

    static bool remove_unit(ref<unit> u)
    {
        if (!u)
        {
            return false;
        }

        auto it = std::find_if(units.begin(), units.end(),
            [&u](const ref<unit>& current_unit)
            {
                return current_unit.get() == u.get();
            });

        if (it != units.end())
        {
            units.erase(it);
            return true;
        }

        return false;
    }
};
