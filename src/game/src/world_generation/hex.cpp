#include "hex.h"
#include "glm/glm.hpp"


using glm::vec3;

hex::hex(hex_coord coord, ref<prefab_instance> instance, TILE terrain_type)
	: coord(coord)
	, instance(instance)
	, terrain_type(terrain_type)
{
}

hex::hex(hex_coord coord, ref<prefab_instance> instance, TILE terrain_type, ref<prefab_instance> building)
	: coord(coord)
	, instance(instance)
	, terrain_type(terrain_type)
	, building(building)
{
}

void hex::build(ref<prefab> new_building)
{
	building = new_building->create_instance(coord.to_world());;
}

void hex::destroy_building()
{
	// TODO: Find a way to remove!
	building = nullptr;
}
