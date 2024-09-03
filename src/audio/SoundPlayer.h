#pragma once
#include <random>
#include <SFML/Audio.hpp>
#include <functional>
#include "SoundType.h"
#include "utils/ValueGetter.h"
#include "events/InitReadyObserver.h"
#include "events/InteractionObserver.h"
#include "events/BrickSoundObserver.h"

using namespace sf;

class SoundPlayer : public InitReadyObserver, public InteractionObserver, public BrickSoundObserver
{
private:

    ValueGetter& valueGetter;
    SoundBuffer ballHitBuffer;
    SoundBuffer ballResetBuffer;
    Sound ballSound;

    SoundBuffer buttonBuffer_1;
    SoundBuffer buttonBuffer_2;
    std::vector<SoundBuffer> buttonBuffers;
    Sound buttonSound;

    std::map<std::string, SoundBuffer> brickHitBuffers;
    std::map<std::string, SoundBuffer> brickBreakBuffers;
    Sound brickSound;

    std::vector<std::reference_wrapper<Sound>> sounds
    {
        std::ref(ballSound), 
        std::ref(buttonSound),
        std::ref(brickSound)
    };

    size_t reservedSize = 2;

    static const std::string BALL_HIT_SOUND;
    static const std::string BALL_RESET_SOUND;
    static const std::string BUTTON_1;
    static const std::string BUTTON_2;

    std::string ballHitSoundPath = "";
    std::string ballResetSoundPath = "";
    std::string butonSoundPath_1 = "";
    std::string buttonSoundPath_2 = "";

    float defaultSoundVolume = 70.0f;
    bool isSoundOn = true;

public:

    SoundPlayer(ValueGetter& valueGetterRef);

    void playSoundRandomPitch(SoundType src);
    void playRandomSound(SoundType src);
    void configureBuffer(SoundType src, std::string path);
    void setBuffer(SoundType src);
    void setPitch(SoundType src, float newPitch);
    void playSound(SoundType src);
    void setSoundVolume(SoundType src, float volume);
    void registerBrickSound(const std::string& brickTypeId, const std::string& hitSoundPath, const std::string& breakSoundPath);
    void reloadBrickSound(const std::string& brickTypeId, const std::string& hitSoundPath, const std::string& breakSoundPath);

    // Inherited via InitReadyObserver
    virtual void onInit() override;

    // Inherited via InteractionObserver
    virtual void onInteract(InteractionType interactionType) override;

    // Inherited via BrickSoundObserver
    virtual void onBrickPlaySound(const std::string& brickId, SoundType soundType) override;

};
