#include "Platform.h"
#include <SFML/Window.hpp>

using namespace sf;

Platform::Platform(Game& game)
    : GameObject(game), collidable(sprite, CollidableObjectType::PLATFORM),
    collisionManager(game.getCollisionManager())
{   
    valueGetter.attachLevelDataObserver(this);
    init();

    collisionManager.addCollidable(std::make_unique<Collidable>(collidable));
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


