#include "hex.h"
#include "glm/glm.hpp"


using glm::vec3;

hex::hex(hex_coord coord, ref<prefab_instance> instance, TILE terrain_type)
	: coord(coord)
	, instance(instance)
	, terrain_type(terrain_type)
{
}

void hex::build(ref<prefab> new_building, ACTOR owner)
{
	auto building_instance = new_building->create_instance(coord.to_world());
	building_ = ref<building>(new building(building_instance, owner));
	is_passable = false;
}

void hex::destroy_building()
{
	engine::prefab_manager::instance().remove_instance(building_->get_instance());
	building_ = nullptr;
	is_passable = true;
}
