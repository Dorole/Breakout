#include "Platform.h"
#include <SFML/Window.hpp>

using namespace sf;

Platform::Platform(Game& game)
    : GameObject(game), 
    renderer(game),
    collidable(renderer.getSprite(), CollidableObjectType::PLATFORM),
    platformData(renderer.getSprite())
{  
    valueGetter.attachLevelDataObserver(this);
    //init();

    registerForCollision();
    levelDataProvider.registerPlatformData(platformData);
}

void Platform::init()
{
    std::string platformPath = valueGetter.getPlatformTexturePath();
    renderer.init(platformPath); 

    setInitialPlatformPosition();

    levelDataProvider.setDeathZone(renderer.getSpritePosition().y + renderer.getSpriteLocalBounds().height);
}

void Platform::setInitialPlatformPosition()
{
    initialPlatformPosition = Vector2f(window.getSize().x / 2.0f, window.getSize().y - platformBottomOffset);
    renderer.setSpritePosition(initialPlatformPosition);
}

void Platform::movePlatform(float deltaTime)
{
    Vector2f currentPosition = renderer.getSpritePosition();
    FloatRect spriteLocalBounds = renderer.getSpriteLocalBounds();
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

    renderer.moveSprite(targetPosition * deltaTime * platformSpeed);
}

void Platform::update(float deltaTime) 
{
    movePlatform(deltaTime);
}

void Platform::draw()
{
    renderer.drawSprite();
}

void Platform::registerForCollision()
{
    collisionManager.addCollidable(collidable);
}

