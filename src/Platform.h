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

    void movePlatform();

public:
    Platform(const sf::Vector2f& position, RenderWindow& windowRef, const std::string& texturePath);
    void update() override;
};

