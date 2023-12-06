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

    SoundPlayer()
    {
        buttonBuffers.reserve(reservedSize);

        ballHitBuffer.loadFromFile(ballHitSoundPath);
        ballResetBuffer.loadFromFile(ballResetSoundPath);
        buttonBuffer_1.loadFromFile(butonSoundPath_1);
        buttonBuffer_2.loadFromFile(buttonSoundPath_2);

        buttonBuffers.push_back(buttonBuffer_1);
        buttonBuffers.push_back(buttonBuffer_2);

        ballSound.setVolume(defaultBallVolume);
        buttonSound.setVolume(defaultButtonVolume);
    }

    void playSoundRandomPitch(SoundType src)
    {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_real_distribution<float> distribution(0.8f, 1.1f);

        float randomPitch = distribution(generator);

        setPitch(src, randomPitch);
        playSound(src);
    }

    void playRandomSound(SoundType src)
    {
        std::random_device rd;
        std::mt19937 generator(rd());

        if (src == SoundType::BUTTON)
        {
            if (!buttonBuffers.empty())
            {
                std::uniform_int_distribution<size_t> distribution(0, buttonBuffers.size() - 1);
                size_t randomIndex = distribution(generator);

                buttonSound.setBuffer(buttonBuffers[randomIndex]);
                buttonSound.play();
            }
        }
    }

    void configureBuffer(SoundType src, std::string path)
    {
        switch (src)
        {
        case SoundType::BALL_HIT:
            ballHitBuffer.loadFromFile(path);
            break;
        case SoundType::BALL_RESET:
            ballResetBuffer.loadFromFile(path);
            break;
        default:
            break;
        }
    }

    void setBuffer(SoundType src)
    {
        switch (src)
        {
        case SoundType::BALL_HIT:
            if (ballSound.getBuffer() != &ballHitBuffer)
                ballSound.setBuffer(ballHitBuffer);
            break;
        case SoundType::BALL_RESET:
            if (ballSound.getBuffer() != &ballResetBuffer)
                ballSound.setBuffer(ballResetBuffer);
            break;
        default:
            break;
        }
    }

    void setPitch(SoundType src, float newPitch)
    {
        if (src == SoundType::BALL_HIT || src == SoundType::BALL_RESET)
            ballSound.setPitch(newPitch);
    }

    void playSound(SoundType src)
    {
        setBuffer(src);

        if (src == SoundType::BALL_HIT || src == SoundType::BALL_RESET)
            ballSound.play();
    }

    void setSoundVolume(SoundType src, float volume)
    {
        if (src == SoundType::BALL_HIT || src == SoundType::BALL_RESET)
            ballSound.setVolume(volume);
    }
};