#pragma once
#include <engine.h>
#include <engine/prefabs/prefab.h>
#include "../properties.h"


using engine::ref;
using engine::prefab_instance;

class unit : public instantiable, public ownable, public destroyable
{
private:
	//UNIT type;
	//vector<UNIT_TOOL> tools;

public:

private:
	void update_health(uint_fast8_t new_health) override;
};
