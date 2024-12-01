#include "building.h"


building::building(ref<prefab_instance> building)
	: instance(building)
{
	health = 100;
}

void building::update_health(uint_fast8_t new_health)
{
	health = new_health;
}
