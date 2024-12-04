#pragma once
#import <engine.h>


class audio_manager : public engine::audio_manager
{
private:
    static const std::string MUSIC_DIR = "assets/audio/music";
    static const uint_fast8_t MAX_MUSIC_VOLUME = 100;

    bool is_switching = false;
    TRACK playing_track;

    uint_fast8_t volume_A;
    uint_fast8_t volume_B;

    enum TRACK : uint_fast8_t
    {
        A,
        B
    }

    enum MUSIC : uint_fast8_t
    {
        ONE,
        TWO,
        THREE,
        TENSE,
        VERY_TENSE
        ATTACK
    };

public:
    std::vec foo;

    audio_manager();

private:
    void change_music(MUSIC music);
    void audio_manager::switch_track(TRACK track);

    static std::string enum_to_name(MUSIC music)
    {
        switch (music)
        {
        case MUSIC::ONE: return "1";
        case TILE::TWO: return "2";
        case TILE::THREE: return "3";
        case TILE::TENSE: return "tense";
        case TILE::VERY_TENCE: return "vtense";
        case TILE::ATTACK: return "attack";
        default: return "error_audio";
        }
    }
};
