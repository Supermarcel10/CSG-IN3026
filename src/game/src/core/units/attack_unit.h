#pragma once
#include "unit.h"
#include "../../world_generation/hex_coord.h"
#include "../../managers/prefab/prefabs.h"


class attack_unit : public unit
{
private:
	uint_fast8_t range_;

public:
	void attack(hex_coord coord)
	{
        //auto audio_manager = engine::audio_manager::instance();

        //audio_manager->load_sound("assets/audio/sound/unit/cannon_shoot.mp3", engine::sound_type::spatialised, "cannon_shoot");
        //audio_manager->play_spatialised_sound("cannon_shoot", vec3(0.f), vec3(0.f));
        std::cout << " attacking!" << std::endl;
	};

    attack_unit(
        UNIT_CLASS unit_class,
        UNIT unit_type,
        ref<prefab_instance> instance,
        ACTOR owner,
        uint_fast8_t range
    )
        : unit(unit_class, unit_type, instance, owner)
        , range_(range)
    {
    }
};
