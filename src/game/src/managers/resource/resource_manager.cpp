#include "resource_manager.h"


resource_manager::resource_manager()
{
    resources[FOOD] = 100;
    resources[GOLD] = 100;
    resources[WOOD] = 200;
    resources[STONE] = 100;
    resources[METAL] = 100;
}

resource_manager::resource_manager(std::unordered_map<RESOURCE, int> initialising_resources)
{
    resources = initialising_resources;
}

int resource_manager::get_resource_amount(const RESOURCE resource_type) const
{
    auto it = resources.find(resource_type);
    if (it != resources.end())
    {
        return it->second;
    }

    return 0;
}

void resource_manager::add_resource(const RESOURCE resource_type, int amount)
{
    resources[resource_type] += amount;
}

bool resource_manager::remove_resource(const RESOURCE resource_type, int amount)
{
    if (amount < 0 || !has_enough_resource(resource_type, amount))
    {
        return false;
    }

    resources[resource_type] -= amount;
    return true;
}

bool resource_manager::has_enough_resource(const RESOURCE resource_type, int amount) const
{
    return get_resource_amount(resource_type) >= amount;
}
