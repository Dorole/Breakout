#include "SoundPlayer.h"

const std::string SoundPlayer::BALL_HIT_SOUND = "BallHitSound";
const std::string SoundPlayer::BALL_RESET_SOUND = "BallResetSound";
const std::string SoundPlayer::BUTTON_1 = "ButtonSound1";
const std::string SoundPlayer::BUTTON_2 = "ButtonSound2";

SoundPlayer::SoundPlayer(ValueGetter& valueGetterRef) : valueGetter(valueGetterRef)
{
    valueGetter.attachInitReadyObserver(this);

    for (Sound& sound : sounds)
        sound.setVolume(defaultSoundVolume);
    
    buttonBuffers.reserve(reservedSize);
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
    if (buttonBuffers.empty())
        return;

    std::random_device rd;
    std::mt19937 generator(rd());

    if (src == SoundType::BUTTON)
    {
		std::uniform_int_distribution<size_t> distribution(0, buttonBuffers.size() - 1);
		size_t randomIndex = distribution(generator);

		buttonSound.setBuffer(buttonBuffers[randomIndex]);
		buttonSound.play();   
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

void SoundPlayer::registerBrickSound(const std::string& brickTypeId, const std::string& hitSoundPath, const std::string& breakSoundPath)
{
    if (brickHitBuffers.find(brickTypeId) == brickHitBuffers.end())
    {
        SoundBuffer hitBuffer;
        SoundBuffer breakBuffer;

        if (!hitSoundPath.empty() && !hitBuffer.loadFromFile(hitSoundPath)) {
            std::cerr << brickTypeId << ": Failed to load hit sound file: " << hitSoundPath << std::endl;
        }

        if (!breakSoundPath.empty() && !breakBuffer.loadFromFile(breakSoundPath)) {
            std::cerr << brickTypeId << ": Failed to load break sound file: " << breakSoundPath << std::endl;
        }

        if (hitSoundPath.empty() || breakSoundPath.empty()) //debug 
            std::cout << brickTypeId << ": One or more brick sound paths are empty. Check if intended." << std::endl;

        brickHitBuffers[brickTypeId] = hitBuffer;
        brickBreakBuffers[brickTypeId] = breakBuffer;
    }
}

void SoundPlayer::reloadBrickSound(const std::string& brickTypeId, const std::string& hitSoundPath, const std::string& breakSoundPath)
{
    brickHitBuffers.clear();
    brickBreakBuffers.clear();
    registerBrickSound(brickTypeId, hitSoundPath, breakSoundPath);
}

void SoundPlayer::onInit()
{
    ballHitSoundPath = valueGetter.getGeneralAsset(BALL_HIT_SOUND);
    ballResetSoundPath = valueGetter.getGeneralAsset(BALL_RESET_SOUND);
    butonSoundPath_1 = valueGetter.getGeneralAsset(BUTTON_1);
    buttonSoundPath_2 = valueGetter.getGeneralAsset(BUTTON_2);

    if (!ballHitBuffer.loadFromFile(ballHitSoundPath)) {
        std::cerr << BALL_HIT_SOUND << ": Failed to load sound file: " << ballHitSoundPath << std::endl;
    }

    if (!ballResetBuffer.loadFromFile(ballResetSoundPath)) {
        std::cerr << BALL_RESET_SOUND << ": Failed to load sound file: " << ballResetSoundPath << std::endl;
    }

    if (!buttonBuffer_1.loadFromFile(butonSoundPath_1)) {
        std::cerr << BUTTON_1 << ": Failed to load sound file: " << butonSoundPath_1 << std::endl;
    }

    if (!buttonBuffer_2.loadFromFile(buttonSoundPath_2)) {
        std::cerr << BUTTON_2 << ": Failed to load sound file: " << buttonSoundPath_2 << std::endl;
    }

    buttonBuffers.push_back(buttonBuffer_1);
    buttonBuffers.push_back(buttonBuffer_2);
}

void SoundPlayer::onInteract(InteractionType interactionType)
{
    isSoundOn = !isSoundOn;
    
    for (Sound& sound : sounds) 
        sound.setVolume(isSoundOn ? defaultSoundVolume : 0.0f);   
}

void SoundPlayer::onBrickPlaySound(const std::string& brickId, SoundType soundType)
{
    if (!isSoundOn) return;

    if (soundType == SoundType::BRICK_HIT && brickHitBuffers.count(brickId))
        brickSound.setBuffer(brickHitBuffers[brickId]);

    else if (soundType == SoundType::BRICK_BREAK && brickBreakBuffers.count(brickId))
        brickSound.setBuffer(brickBreakBuffers[brickId]);
    
    brickSound.play();
}

