#include "audio_manager.h"


audio_manager::audio_manager()
    : engine::audio_manager()
{
    instance()->init();
}

void audio_manager::change_music(MUSIC music)
{
    auto inst = instance();
    auto music_name = enum_to_name(music);

    inst->load_sound(
        MUSIC_DIR + "/" + music_name + "_A.wav",
        engine::sound_type::track,
        "music_A"
    );

    inst->load_sound(
        MUSIC_DIR + "/" + music_name + "_B.wav",
        engine::sound_type::track,
        "music_B"
    );

    inst->play("music_A");
    inst->play("music_B");
}

void audio_manager::switch_track(TRACK track)
{
    auto current_track = playing_track;
    is_switching = true;

    // TODO: Switch smoothly between tracks
    for (uint_fast16_t i = 0; i <= 1000; ++i)
    {
        auto parsed = (i / 1000) * MAX_MUSIC_VOLUME;

        if (current_track == TRACK::A)
        {
            instance().volume("music_A", (float) (MAX_MUSIC_VOLUME - parsed));
            instance().volume("music_B", (float) parsed);
        }
        else
        {
            instance().volume("music_A", (float) parsed);
            instance().volume("music_B", (float) (MAX_MUSIC_VOLUME - parsed));
        }
    }

    playing_track = track;
    is_switching = false;
}
