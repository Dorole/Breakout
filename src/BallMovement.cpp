#include "BallMovement.h"
#include "Game.h"
#include "CollisionDirection.h"
#include <iostream>

BallMovement::BallMovement(Game& gameRef)
    : game(gameRef),
    window(game.getWindow()), 
    platformData(game.getLevelDataProvider().getPlatformData()) //check at first use - if not set - set again!
{   
    windowSize = window.getSize();
    init();
}

void BallMovement::init()
{
    //this is set in init() so it might not be available here - maybe some version of lazy init?
    deathZone = platformData.getGlobalSpritePosition().y + platformData.getSpriteLocalBounds().height; //mozda uzmi iz level data providera?
    playingFieldTopBound = game.getGrid().getGridOffset();
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

bool BallMovement::handleWindowCollision(const sf::FloatRect& globalBallBounds)
{
    bool collided = false;

    //top
    if (globalBallBounds.top < playingFieldTopBound)
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

void BallMovement::reflectOffPlatform(float hitPoint, const sf::Vector2f& collidedPosition, const sf::FloatRect& localPlatformSpriteBounds)
{
    float reflectionFactor = hitPoint / (localPlatformSpriteBounds.width / 2.0f);

    ballVelocity = Vector2f(reflectionFactor, -ballVelocity.y);

    float speed = sqrt(ballVelocity.x * ballVelocity.x + ballVelocity.y * ballVelocity.y);
    ballVelocity /= speed;
}

void BallMovement::reflectOffBrick(const sf::FloatRect& ballBounds, const sf::FloatRect& brickBounds)
{
    CollisionDirection collisionDirection = CollisionDirection::BOTTOM;

    float diffX = brickBounds.left + brickBounds.width / 2 - (ballBounds.left + ballBounds.width / 2);
    float diffY = brickBounds.top + brickBounds.height / 2 - (ballBounds.top + ballBounds.height / 2);

    float width = brickBounds.width / 2 + ballBounds.width / 2;
    float height = brickBounds.height / 2 + ballBounds.height / 2;

    float crossWidth = width * diffY;
    float crossHeight = height * diffX;


    if (abs(diffX) <= width && abs(diffY) <= height)
    {
        if (crossWidth > crossHeight)
            collisionDirection = (crossWidth > -crossHeight) ? CollisionDirection::BOTTOM : CollisionDirection::LEFT;
        else
            collisionDirection = (crossWidth > -crossHeight) ? CollisionDirection::RIGHT : CollisionDirection::TOP;
    }

    float adjustedVelX = 1.0f;
    float adjustedVelY = 1.0f;

    switch (collisionDirection)
    {
    case CollisionDirection::TOP:
        adjustedVelY *= -1;
        break;

    case CollisionDirection::BOTTOM:
        adjustedVelY *= -1;
        break;

    case CollisionDirection::LEFT:
        adjustedVelX *= -1;
        break;

    case CollisionDirection::RIGHT:
        adjustedVelX *= -1;
        break;
    }

    Vector2f adjustedBallVel = Vector2f(ballVelocity.x * adjustedVelX, ballVelocity.y * adjustedVelY);
    ballVelocity = adjustedBallVel;
}