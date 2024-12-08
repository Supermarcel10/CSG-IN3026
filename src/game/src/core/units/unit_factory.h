#pragma once
#include <engine.h>
#include "../../managers/prefab/prefabs.h"
#include "unit.h"
#include "attack_unit.h"


using std::unordered_map;
using engine::ref;

class unit_factory
{
private:
    static const unordered_map<UNIT, UNIT_CLASS> unit_class_mapping;
    static const unordered_map<UNIT, uint_fast8_t> attack_range_mapping;

    friend class unit_manager;

    static ref<unit> create_unit(
        UNIT unit_type,
        ref<prefab_instance> instance,
        ACTOR owner
    )
    {
        UNIT_CLASS class_type = get_class_for_unit(unit_type);

        if (class_type == UNIT_CLASS::ATTACK)
        {
            return create_attack_unit(unit_type, instance, owner);
        }
        else
        {
            return std::make_shared<unit>(class_type, unit_type, instance, owner);
        }

    };

    static ref<unit> create_attack_unit(
        UNIT unit_type,
        ref<prefab_instance> instance,
        ACTOR owner
    )
    {
        UNIT_CLASS class_type = get_class_for_unit(unit_type);
        uint_fast8_t range = get_range_for_attack_unit(unit_type);

        return std::make_shared<attack_unit>(class_type, unit_type, instance, owner, range);
    };

    static UNIT_CLASS get_class_for_unit(UNIT unit_type)
    {
        auto it = unit_class_mapping.find(unit_type);
        if (it != unit_class_mapping.end())
        {
            return it->second;
        }

        return DEFAULT;
    };

    static uint_fast8_t get_range_for_attack_unit(UNIT unit_type)
    {
        auto it = attack_range_mapping.find(unit_type);
        if (it != attack_range_mapping.end())
        {
            return it->second;
        }

        return 1;
    };
};
