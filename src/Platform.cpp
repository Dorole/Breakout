#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Platform.h"
#include "GameObject.h"
#include "ValueGetter.h"

using namespace sf;

Platform::Platform(RenderWindow& windowRef, ValueGetter& valueGetterRef)
    : GameObject(windowRef, valueGetterRef)
{   
    valueGetter.attachLevelDataObserver(this);
    init();
}

void Platform::init()
{
    texture.loadFromFile(valueGetter.getPlatformTexturePath());
    sprite.setTexture(texture);

    setSpriteOriginToCenter();
    setInitialPlatformPosition();
    getSpriteLocalBounds();
}

void Platform::setSpriteOriginToCenter()
{
    spriteLocalBounds = sprite.getLocalBounds();
    sprite.setOrigin(spriteLocalBounds.width / 2.0f, spriteLocalBounds.height / 2.0f);
}

void Platform::getSpriteLocalBounds()
{
    spriteLocalBounds = sprite.getLocalBounds();
}

void Platform::setInitialPlatformPosition()
{
    initialPlatformPosition = Vector2f(window.getSize().x / 2.0f, window.getSize().y - platformBottomOffset);
    sprite.setPosition(initialPlatformPosition);
}

void Platform::movePlatform(float deltaTime)
{
    Vector2f currentPosition = sprite.getPosition();
    Vector2i localMousePosition = Mouse::getPosition(window);
    Vector2f targetPosition;

    if (localMousePosition.x < (spriteLocalBounds.width / 2)) 
    {
        targetPosition = Vector2f((spriteLocalBounds.width / 2) - currentPosition.x, 0);
        windowBoundReached = true;
    }
    else if (localMousePosition.x > window.getSize().x - (spriteLocalBounds.width / 2)) 
    {
        targetPosition = Vector2f((window.getSize().x - (spriteLocalBounds.width / 2)) - currentPosition.x, 0);
        windowBoundReached = true;
    }
    else 
    {
        targetPosition = Vector2f(localMousePosition.x - currentPosition.x, 0);
        windowBoundReached = false;
    }

    sprite.move(targetPosition * deltaTime * platformSpeed);
}

void Platform::update(float deltaTime) 
{
    movePlatform(deltaTime);
}

void Platform::draw()
{
    window.draw(sprite);
}

//Vector2f Platform::getInitialPosition() const
//{
//    return initialPlatformPosition;
//}
//
//Vector2f Platform::getPosition() const
//{
//    return sprite.getPosition();
//}
//
//bool Platform::getWindowBoundReached() const
//{
//    return windowBoundReached;
//}
//
//FloatRect Platform::getLocalBounds() const
//{
//    return spriteLocalBounds;
//}
//
//FloatRect Platform::getGlobalBounds() const
//{
//    return sprite.getGlobalBounds();
//}

