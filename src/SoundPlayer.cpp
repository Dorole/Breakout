#include "SoundPlayer.h"
#include <random>
#include <SFML/Audio.hpp>

SoundPlayer::SoundPlayer()
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

void SoundPlayer::playSoundRandomPitch(SoundType src)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> distribution(0.8f, 1.1f);

    float randomPitch = distribution(generator);

    setPitch(src, randomPitch);
    playSound(src);
}

void SoundPlayer::playRandomSound(SoundType src)
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

void SoundPlayer::configureBuffer(SoundType src, std::string path)
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

void SoundPlayer::setBuffer(SoundType src)
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

void SoundPlayer::setPitch(SoundType src, float newPitch)
{
    if (src == SoundType::BALL_HIT || src == SoundType::BALL_RESET)
        ballSound.setPitch(newPitch);
}

void SoundPlayer::playSound(SoundType src)
{
    setBuffer(src);

    if (src == SoundType::BALL_HIT || src == SoundType::BALL_RESET)
        ballSound.play();
}

void SoundPlayer::setSoundVolume(SoundType src, float volume)
{
    if (src == SoundType::BALL_HIT || src == SoundType::BALL_RESET)
        ballSound.setVolume(volume);
}