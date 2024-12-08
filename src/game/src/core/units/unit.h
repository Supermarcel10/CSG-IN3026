#pragma once
#include <engine.h>
#include <engine/prefabs/prefab.h>
#include "../properties.h"
#include "../../managers/prefab/prefabs.h"
#include "../../world_generation/hex_coord.h"


using engine::ref;
using engine::prefab_instance;

enum UNIT_CLASS : uint_fast8_t
{
	DEFAULT,
	ATTACK,
	WORKER
};

class unit : public instantiable, protected ownable, public destroyable
{
protected:
	UNIT_CLASS unit_class_;
	UNIT unit_type_;
	//vector<UNIT_TOOL> tools;

public:
	virtual void move(hex_coord new_hex)
	{
		// TODO: Implement!
	}

	virtual void update()
	{
		// TODO: Implement!
	}

	UNIT_CLASS get_class() const { return unit_class_; };
	UNIT get_type() const { return unit_type_; };

	unit(
		UNIT_CLASS unit_class,
		UNIT unit_type,
		ref<prefab_instance> instance,
		ACTOR owner
	)
		: instantiable(instance)
		, ownable(owner)
		, destroyable()
		, unit_class_(unit_class)
		, unit_type_(unit_type)
	{
	}

private:
	void update_health(uint_fast8_t new_health) override
	{
		auto is_alive = destroyable::set_health(new_health);
		// TODO: Handle unit destruction!
	}
};
