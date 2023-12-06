#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

#include "Ball.h"
#include "GameObject.h"
#include "ValueGetter.h"
#include "Platform.h"
#include "BrickGrid.h"
#include "SoundPlayer.h"

using namespace sf;

Ball::Ball(RenderWindow& windowRef, ValueGetter& valueGetterRef, Platform& platformRef, BrickGrid& gridRef, std::vector<std::vector<GridData>>& gridDataVectorRef)
    : GameObject(windowRef, valueGetterRef), platform(platformRef), grid(gridRef), gridVector(gridDataVectorRef)
{
    valueGetter.attachLevelDataObserver(this);
    init();
}

void Ball::init()
{
    texture.loadFromFile(valueGetter.getBallTexturePath());
    sprite.setTexture(texture);
    sprite.setScale(0.4f, 0.4f); 
    windowSize = window.getSize();
    topRenderBound = grid.getGridOffset();

    shouldBounce = false;
    lostLife = false;

    setSpriteOriginToCenter();
    setInitialBallPosition();
    getSpriteBounds();

    soundPlayer.setBuffer(SoundType::BALL_HIT);
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
    initialBallPosition = Vector2f(platform.getInitialPlatformPosition().x, platform.getInitialPlatformPosition().y - platform.getPlatformLocalBounds().height - 1);
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

bool Ball::checkWindowCollision()
{
    FloatRect globalBallBounds = sprite.getGlobalBounds();
    bool collided = false;

    //top
    if (globalBallBounds.top < topRenderBound)
    {
        ballVelocity.y = std::abs(ballVelocity.y);       
        collided = true;
       
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
    {
        ballVelocity.x = std::abs(ballVelocity.x);
        collided = true;
    }

    //right
    if (globalBallBounds.left + globalBallBounds.width > windowSize.x)
    {
        ballVelocity.x = -std::abs(ballVelocity.x);
        collided = true;
    }

    if (collided)
    {
        soundPlayer.playSoundRandomPitch(SoundType::BALL_HIT);
        return true;
    }

    if (lostLife)
    {
        soundPlayer.playSoundRandomPitch(SoundType::BALL_RESET);
        return true;
    }

    return false;

}

bool Ball::checkPlatformCollision()
{
    if (sprite.getGlobalBounds().intersects(platform.getPlatformGlobalBounds()) && ballVelocity.y > 0)
    {
        reflectOffPlatform();
        soundPlayer.playSoundRandomPitch(SoundType::BALL_HIT);
        return true;
    }

    return false;
}

bool Ball::checkBrickCollision()
{     
    for (size_t i = 0; i < valueGetter.getRowCount(); i++)
    {
        for (size_t j = 0; j < valueGetter.getColumnCount(); j++)
        {
            if (gridVector[i][j].shouldRender && gridVector[i][j].getSpriteGlobalBounds().intersects(sprite.getGlobalBounds()))
            {
                if (lastCollidedRow == i && lastCollidedColumn == j) 
                    return false;

                setLastCollided(i, j);
				ballVelocity.y = -ballVelocity.y;
				grid.handleCollision(i, j);	
                return true;
            }
        }
    }

    return false;
}


void Ball::reflectOffPlatform()
{
    float hitPointX = sprite.getPosition().x - platform.getPlatformPosition().x;
    float reflectionFactor = hitPointX / (platform.getPlatformLocalBounds().width / 2.0f);

    ballVelocity.x = reflectionFactor;

    ballVelocity.y = -ballVelocity.y;
    float speed = sqrt(ballVelocity.x * ballVelocity.x + ballVelocity.y * ballVelocity.y);
    ballVelocity /= speed;

    sprite.setPosition(platform.getPlatformPosition().x + hitPointX, platform.getPlatformPosition().y - platform.getPlatformLocalBounds().height / 2.0f);
}


void Ball::setLastCollided(int row, int col)
{
    lastCollidedRow = row;
    lastCollidedColumn = col;
}

void Ball::setLastCollidedToNull()
{
    lastCollidedRow = -1;
    lastCollidedColumn = -1;
}

// ******************** OVERRIDDEN FUNCTIONS ********************

void Ball::update(float deltaTime)
{
    if (!shouldBounce)
    {
        moveIdle(deltaTime);
    }
    else
    {
        if (checkWindowCollision() || checkBrickCollision())
            setLastCollidedToNull();
        
        checkPlatformCollision();
        sprite.move(ballVelocity * ballSpeed * deltaTime);
        
        if (grid.allBricksDestroyed()) 
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

