#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Platform.h"
#include "GameObject.h"
#include "ValueGetter.h"

using namespace sf;

Platform::Platform(RenderWindow& windowRef, ValueGetter& valueGetter)
    : window(windowRef)
{
    texture.loadFromFile(valueGetter.getPlatformTexturePath());
    sprite.setTexture(texture);

    setSpriteOriginToCenter();
    setInitialPlatformPosition();
    getSpriteBounds();
}

void Platform::setSpriteOriginToCenter()
{
    spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
}

void Platform::getSpriteBounds()
{
    spriteBounds = sprite.getLocalBounds();
}

void Platform::setInitialPlatformPosition()
{
    initialPlatformPosition = Vector2f(window.getSize().x / 2, window.getSize().y - 20);
    sprite.setPosition(initialPlatformPosition);
}

void Platform::movePlatform()
{
    Vector2f lastPos = sprite.getPosition();
    Vector2i localMousePosition = Mouse::getPosition(window); 

    if (localMousePosition.x < (spriteBounds.width / 2)) {
        sprite.setPosition((spriteBounds.width / 2), initialPlatformPosition.y);
        windowBoundReached = true;
    }
    else if (localMousePosition.x > window.getSize().x - (spriteBounds.width / 2)) {
        sprite.setPosition(window.getSize().x - (spriteBounds.width / 2), initialPlatformPosition.y);
        windowBoundReached = true;
    }
    else {
        sprite.setPosition(localMousePosition.x, initialPlatformPosition.y);
        windowBoundReached = false;
    }
}

void Platform::update() 
{
    movePlatform();
}

void Platform::draw()
{
    window.draw(sprite);
}

