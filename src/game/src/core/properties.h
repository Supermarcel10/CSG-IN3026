#pragma once
#include <engine.h>
#include <engine/prefabs/prefab.h>


using engine::ref;
using engine::prefab_instance;

enum ACTOR : uint_fast8_t
{
	UNOWNED,
	PLAYER,
	ENEMY1
};

class ownable
{
private:
	ACTOR owner_;

public:
	ownable(ACTOR owner)
	{
		owner_ = owner;
	};

	bool is_permitted(ACTOR initiating_actor) const
	{
		return owner_ == initiating_actor;
	};
};

class destroyable
{
private:
	uint_fast8_t max_health;
	uint_fast8_t health;

public:
	destroyable(uint_fast8_t initial_health = 100)
	{
		max_health = initial_health;
		health = initial_health;
	};

	bool set_health(uint_fast8_t new_health) {
		if (health <= 0)
		{
			return false;
		}
		else
		{
			health = new_health;
			return true;
		}
	};

	virtual void update_health(uint_fast8_t new_health) = 0;
};

class instantiable
{
private:
	ref<prefab_instance> instance_;

public:
	instantiable(ref<prefab_instance> instance)
	{
		instance_ = instance;
	}

	ref<prefab_instance> get_instance() { return instance_; };
};
