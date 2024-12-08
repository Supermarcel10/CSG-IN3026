#pragma once
#include <engine.h>
#include "../units/unit.h"


using engine::ref;

class projectile
{
private:
	ref<unit> owning_unit;
	hex_coord start_pos;
	hex_coord target_pos;

public:
	projectile()
	{
	}

private:
};


