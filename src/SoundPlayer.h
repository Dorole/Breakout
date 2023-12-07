#pragma once
#include <random>
#include <SFML/Audio.hpp>

enum class SoundType
{
    BALL_HIT,
    BALL_RESET,
    BUTTON
};

using namespace sf;


class SoundPlayer
{
private:

    SoundBuffer ballHitBuffer;
    SoundBuffer ballResetBuffer;
    Sound ballSound;

    SoundBuffer buttonBuffer_1;
    SoundBuffer buttonBuffer_2;
    Sound buttonSound;
    std::vector<SoundBuffer> buttonBuffers;
    size_t reservedSize = 2;

    std::string ballHitSoundPath = "resources/audio/ball_hit.wav";
    std::string ballResetSoundPath = "resources/audio/reset.wav";
    std::string butonSoundPath_1 = "resources/audio/button1.wav";
    std::string buttonSoundPath_2 = "resources/audio/button2.wav";

    float defaultBallVolume = 70.0f;
    float defaultButtonVolume = 50.0f;

public:

    SoundPlayer();

    void playSoundRandomPitch(SoundType src);
    void playRandomSound(SoundType src);
    void configureBuffer(SoundType src, std::string path);
    void setBuffer(SoundType src);
    void setPitch(SoundType src, float newPitch);
    void playSound(SoundType src);
    void setSoundVolume(SoundType src, float volume);
};