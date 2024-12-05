#pragma once
#include <unordered_map>
#include <string>


enum RESOURCE : uint_fast8_t
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
    std::unordered_map<RESOURCE, uint_fast64_t> resources;

public:
    resource_manager();
    resource_manager(std::unordered_map<RESOURCE, uint_fast64_t> initialising_resources);

    uint_fast64_t get_resource_amount(const RESOURCE resource) const;
    bool has_enough_resource(const RESOURCE resource, uint_fast64_t amount) const;

    void add_resource(const RESOURCE resource, uint_fast64_t amount);
    bool remove_resource(const RESOURCE resource, uint_fast64_t amount);
};
