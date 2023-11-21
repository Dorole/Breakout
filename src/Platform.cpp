#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Platform.h"
#include "GameObject.h"

using namespace sf;

Platform::Platform(RenderWindow& windowRef, const std::string& texturePath)
    : window(windowRef)
{
    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);

    setSpriteOriginToCenter();
    setInitialPlatformPosition();
    getSpriteBounds();
}

void Platform::setInitialPlatformPosition()
{
    initialPlatformPosition = Vector2f(window.getSize().x / 2, window.getSize().y - 20);
    sprite.setPosition(initialPlatformPosition);
}

void Platform::movePlatform()
{
    Vector2i localMousePosition = Mouse::getPosition(window); 

    if (localMousePosition.x < (spriteBounds.width / 2)) {
        sprite.setPosition((spriteBounds.width / 2), initialPlatformPosition.y);
    }
    else if (localMousePosition.x > window.getSize().x - (spriteBounds.width / 2)) {
        sprite.setPosition(window.getSize().x - (spriteBounds.width / 2), initialPlatformPosition.y);
    }
    else {
        sprite.setPosition(localMousePosition.x, initialPlatformPosition.y);
    }
}

void Platform::update() 
{
    movePlatform();
}

