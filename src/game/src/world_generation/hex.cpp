#include "hex.h"
#include "glm/glm.hpp"
#include "../managers/unit/unit_manager.h"


using glm::vec3;

hex::hex(hex_coord coord, ref<prefab_instance> instance, TILE terrain_type)
	: coord(coord)
	, instance(instance)
	, terrain_type(terrain_type)
{
}

bool hex::build(ref<prefab> new_building, ACTOR owner)
{
	if (!is_passable) {
		return false;
	}

	auto building_instance = new_building->create_instance(coord.to_world());
	building_ = ref<building>(new building(building_instance, owner));
	is_passable = false;

	return true;
}

bool hex::destroy_building()
{
	if (building_ == nullptr)
	{
		return false;
	}

	engine::prefab_manager::instance().remove_instance(building_->get_instance());
	building_ = nullptr;
	is_passable = true;

	return true;
}

bool hex::spawn_unit(ref<prefab> new_unit, ACTOR owner)
{
	if (!is_passable)
	{
		return false;
	}

	auto unit_type = UNIT::BASE_UNIT;
	auto unit_instance = new_unit->create_instance(coord.to_world());

	unit_ = unit_manager::add_unit(unit_type, unit_instance, owner);
	is_passable = false;

	return true;
}

bool hex::destroy_unit()
{
	if (unit_ == nullptr)
	{
		return false;
	}

	engine::prefab_manager::instance().remove_instance(unit_->get_instance());
	auto success = unit_manager::remove_unit(unit_);
	if (!success)
	{
		return false;
	}

	unit_ = nullptr;
	is_passable = true;

	return true;
}
