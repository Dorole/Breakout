#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ValueGetter.h"

using namespace sf;

//odvojiti vizual od logike

class Platform : public GameObject
{
private:
    Vector2f initialPlatformPosition;
    RenderWindow& window;

    void setInitialPlatformPosition();
    void movePlatform();

public:
    Platform(RenderWindow& windowRef, ValueGetter& valueGetter);
    void update() override;
};

