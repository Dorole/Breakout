#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Ball.h"
#include "GameObject.h"
#include "ValueGetter.h"
#include "Platform.h"
#include "BrickGrid.h"

using namespace sf;

Ball::Ball(RenderWindow& windowRef, ValueGetter& valueGetterRef, Platform& platformRef, BrickGrid& gridRef, std::vector<std::vector<GridData>>& gridDataVectorRef)
    : window(windowRef), platform(platformRef), valueGetter(valueGetterRef), grid(gridRef), gridVector(gridDataVectorRef)
{
    valueGetter.attachLevelDataObserver(this);
    init();
}

void Ball::init()
{
    texture.loadFromFile(valueGetter.getBallTexturePath());
    sprite.setTexture(texture);
    windowSize = window.getSize();

    shouldBounce = false;
    lostLife = false;

    setSpriteOriginToCenter();
    setInitialBallPosition();
    getSpriteBounds();
}

void Ball::setSpriteOriginToCenter()
{
    spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
}

void Ball::getSpriteBounds()
{
    spriteBounds = sprite.getLocalBounds();
}

void Ball::setInitialBallPosition()
{
    initialBallPosition = Vector2f(platform.getInitialPlatformPosition().x, platform.getInitialPlatformPosition().y - 15);
    sprite.setPosition(initialBallPosition);
}

void Ball::moveIdle(float deltaTime)
{
    Vector2i localMousePosition = Mouse::getPosition(window);
    Vector2f currentPosition = sprite.getPosition();
    Vector2f targetPosition;

    if (!platform.platformWindowBoundReached()) {
        targetPosition = Vector2f(localMousePosition.x - currentPosition.x, 0);
    }
    else {
       targetPosition = Vector2f(platform.getPlatformPosition().x - currentPosition.x, 0);
    }

    sprite.move(targetPosition * deltaTime * ballSpeed);
}

void Ball::toggleBounce()
{
    shouldBounce = !shouldBounce;
}

void Ball::checkWindowCollision()
{
    FloatRect globalBallBounds = sprite.getGlobalBounds();

    //top
    if (globalBallBounds.top < grid.getGridOffset()) //cache offset!
    {
        ballVelocity.y = std::abs(ballVelocity.y);
    }


    //bottom
    if (globalBallBounds.top + globalBallBounds.height > windowSize.y)
    {
        if (!lostLife)
        {
			notifyObservers(1);
            lostLife = true;
        }
    }
    else
    {
        lostLife = false;
    }

    //left
    if (globalBallBounds.left < 0)
        ballVelocity.x = std::abs(ballVelocity.x);

    //right
    if (globalBallBounds.left + globalBallBounds.width > windowSize.x)
        ballVelocity.x = -std::abs(ballVelocity.x);

}

//should return bool
void Ball::checkPlatformCollision()
{
    if (sprite.getGlobalBounds().intersects(platform.getPlatformGlobalBounds()) && ballVelocity.y > 0)
    {
        ballVelocity.y = -ballVelocity.y;
        return;
    }
}

//should return bool?
//cache previous brick and check if it's the same - if it is return - idk how else to prevent multiple hits at the same time :(
//if it hits anything else (like, platform or window) set previous brick to null or something
void Ball::checkBrickCollision()
{     
    for (size_t i = 0; i < valueGetter.getRowCount(); i++)
    {
        for (size_t j = 0; j < valueGetter.getColumnCount(); j++)
        {
            if (gridVector[i][j].shouldRender && gridVector[i][j].getSpriteGlobalBounds().intersects(sprite.getGlobalBounds()))
            {
                if (!isInCollision)
                {
					ballVelocity.y = -ballVelocity.y;
					grid.handleCollision(i, j);
					isInCollision = true;
                }
                return;
            }
        }
    }


    isInCollision = false;
}

//***************************************************
void Ball::update(float deltaTime)
{
    if (!shouldBounce)
        moveIdle(deltaTime);
    else
    {
        checkWindowCollision();
        checkPlatformCollision();
        checkBrickCollision();
        
        sprite.move(ballVelocity * ballSpeed * deltaTime);

        if (grid.allBricksDestroyed()) //callback to event?? Maybe like a stateObserver (true, false)
        {
            shouldBounce = false;
            setInitialBallPosition();
        }
    }
}

void Ball::draw()
{
    window.draw(sprite);
}

void Ball::attachObserver(NumValueObserver* observer)
{
    observers.push_back(observer);
}

void Ball::notifyObservers(int value)
{
    for (const auto& observer : observers)
        observer->onValueChanged(value, ValueType::LIVES);
}

void Ball::onLevelChanged()
{
    init();
}
