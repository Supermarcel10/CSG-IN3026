#pragma once
#include <engine.h>
#include "managers/game_state_manager.h"


class controlled_layer : public engine::layer
{
protected:
	game_state_manager& state_manager;

public:
	controlled_layer(game_state_manager& state_manager)
		: engine::layer()
		, state_manager(state_manager)
	{}
};
