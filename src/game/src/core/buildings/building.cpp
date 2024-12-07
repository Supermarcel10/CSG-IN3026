#include "building.h"


building::building(
	ref<prefab_instance> building,
	ACTOR owner
)
	: instantiable(building)
	, destroyable()
	, ownable(owner)
{
}


void building::update_health(uint_fast8_t new_health)
{
	auto is_alive = destroyable::set_health(new_health);
	// TODO: Handle building destruction!
}
