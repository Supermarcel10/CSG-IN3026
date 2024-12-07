#include "unit.h"


void unit::update_health(uint_fast8_t new_health)
{
	auto is_alive = destroyable::set_health(new_health);
	// TODO: Handle unit destruction!
}
