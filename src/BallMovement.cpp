#include "BallMovement.h"
#include "Game.h"
#include <iostream>

BallMovement::BallMovement(Game& game)
    : window(game.getWindow()), 
    platformData(game.getLevelDataProvider().getPlatformData()) //check at first use - if not set - set again!
{
    deathZone = platformData.getGlobalSpritePosition().y + platformData.getSpriteLocalBounds().height; //mozda uzmi iz level data providera?
    //this is set in init() so it might not be available here - maybe some version of lazy init?
    
    windowSize = window.getSize();
}

void BallMovement::updatePosition(const sf::Vector2f& newPosition)
{
	currentPosition = newPosition;
}

void BallMovement::resetPosition()
{
    currentPosition = Vector2f(platformData.getGlobalSpritePosition().x, platformData.getGlobalSpritePosition().y - platformData.getSpriteLocalBounds().height + 5.0f);
}

void BallMovement::updatePositionAbovePlatform()
{
    targetPosition = Vector2f(platformData.getGlobalSpritePosition().x - currentPosition.x, 0);
}

bool BallMovement::handleWindowCollision(const sf::FloatRect& globalBallBounds, const float& topRenderBound)
{
    bool collided = false;

    //top
    if (globalBallBounds.top < topRenderBound)
    {
        ballVelocity.y = std::abs(ballVelocity.y);
        collided = true;
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

    return collided;
}

bool BallMovement::ballMovedBelowPlatform(const sf::FloatRect& globalBallBounds) 
{
    return (globalBallBounds.top + globalBallBounds.height) > deathZone;
}


Vector2f BallMovement::moveBallAbovePlatform()
{
    updatePositionAbovePlatform();

    return targetPosition * ballSpeed;
}

Vector2f BallMovement::moveBall()
{
    return ballVelocity * ballSpeed;
}