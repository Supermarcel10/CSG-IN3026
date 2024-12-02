#pragma once
#include <unordered_map>
#include <string>


enum RESOURCE
{
    FOOD,
    GOLD,
    WOOD,
    STONE,
    METAL
};

class resource_manager
{
private:
    std::unordered_map<RESOURCE, int> resources;

public:
    resource_manager();
    resource_manager(std::unordered_map<RESOURCE, int> initialising_resources);

    int get_resource_amount(const RESOURCE resource) const;
    bool has_enough_resource(const RESOURCE resource, int amount) const;

    void add_resource(const RESOURCE resource, int amount);
    bool remove_resource(const RESOURCE resource, int amount);
};
