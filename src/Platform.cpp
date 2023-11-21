#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Platform.h"
#include "GameObject.h"

using namespace sf;

Platform::Platform(const sf::Vector2f& position, RenderWindow& windowRef, const std::string& texturePath)
    : window(windowRef)
{
    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
    setSpriteOriginToCenter();
    sprite.setPosition(position);

    initialPlatformPosition = sprite.getPosition();
    getSpriteBounds();
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

