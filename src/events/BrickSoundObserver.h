#pragma once
#include "audio/SoundType.h"

class BrickSoundObserver
{
public:
    virtual void onBrickPlaySound(const std::string& brickId, SoundType soundType) = 0;
};
