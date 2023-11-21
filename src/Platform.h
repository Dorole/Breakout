#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

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
    Platform(RenderWindow& windowRef, const std::string& texturePath);
    void update() override;
};

