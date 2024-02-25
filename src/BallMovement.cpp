#include "BallMovement.h"
#include <iostream>

BallMovement::BallMovement(RenderWindow& windowRef, Platform& platformRef)
    : window(windowRef), platform(platformRef)
{
    deathZone = platform.getPlatformPosition().y + platform.getPlatformLocalBounds().height; //set elsewhere (maybe get from platform)?
    windowSize = window.getSize();

    resetPosition();
}

void BallMovement::updatePosition(const sf::Vector2f& newPosition)
{
	currentPosition = newPosition;
}

void BallMovement::resetPosition()
{
    currentPosition = Vector2f(platform.getInitialPlatformPosition().x, platform.getInitialPlatformPosition().y - platform.getPlatformLocalBounds().height + 5.0f);
}

void BallMovement::updatePositionAbovePlatform()
{
    Vector2i localMousePosition = Mouse::getPosition(window);

    if (!platform.platformWindowBoundReached()) {
        targetPosition = Vector2f(localMousePosition.x - currentPosition.x, 0);
    }
    else {
        targetPosition = Vector2f(platform.getPlatformPosition().x - currentPosition.x, 0);
    }
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