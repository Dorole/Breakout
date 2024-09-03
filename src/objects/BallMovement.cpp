#include "BallMovement.h"
#include "game/Game.h"
#include <iostream>

const sf::Vector2f BallMovement::STARTING_BALL_VELOCITY { -0.2f, -1.0f }; 
const float BallMovement::BALL_SPEED{ 500.0f };

BallMovement::BallMovement(Game& gameRef)
    : window(gameRef.getWindow()),
    brickGrid(gameRef.getGrid()),
    levelDataProvider(gameRef.getLevelDataProvider())
{
    windowSize = window.getSize();
    init();
}

void BallMovement::init()
{
    ballVelocity = STARTING_BALL_VELOCITY;
    ballSpeed = BALL_SPEED;
    
    deathZone = levelDataProvider.getDeathZone();
    playingFieldTopBound = brickGrid.getGridOffset();
}

void BallMovement::updatePosition(const sf::Vector2f& newPosition)
{
    currentPosition = newPosition;
}

void BallMovement::resetPosition()
{
    if (!platformData) 
        platformData = &levelDataProvider.getPlatformData(); 
    
    currentPosition = Vector2f(platformData->getGlobalSpritePosition().x, platformData->getGlobalSpritePosition().y - platformData->getSpriteLocalBounds().height + 5.0f);
}

void BallMovement::updatePositionAbovePlatform()
{
    if (!platformData)
        platformData = &levelDataProvider.getPlatformData();

    targetPosition = Vector2f(platformData->getGlobalSpritePosition().x - currentPosition.x, 0);
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
    CollisionDirection collisionDirection = determineCollisionDirection(ballBounds, brickBounds);

    float adjustedVelX = 1.0f;
    float adjustedVelY = 1.0f;

    switch (collisionDirection)
    {
    case CollisionDirection::TOP:
    case CollisionDirection::BOTTOM:
        adjustedVelY *= -1;
        break;

    case CollisionDirection::LEFT:
    case CollisionDirection::RIGHT:
        adjustedVelX *= -1;
        break;
    }

    ballVelocity = Vector2f(ballVelocity.x * adjustedVelX, ballVelocity.y * adjustedVelY);
}

CollisionDirection BallMovement::determineCollisionDirection(const sf::FloatRect& ballBounds, const sf::FloatRect& brickBounds)
{
    //The differences between the centers of the ball and the brick
    float diffX = (ballBounds.left + ballBounds.width / 2) - (brickBounds.left + brickBounds.width / 2);
    float diffY = (ballBounds.top + ballBounds.height / 2) - (brickBounds.top + brickBounds.height / 2);

    //the half-widths and half-heights of the ball and the brick 
    float combinedHalfWidths = (ballBounds.width / 2) + (brickBounds.width / 2);
    float combinedHalfHeights = (ballBounds.height / 2) + (brickBounds.height / 2);

    //determine the amount of overlap in each direction
    float overlapX = combinedHalfWidths - abs(diffX);
    float overlapY = combinedHalfHeights - abs(diffY);

    if (overlapX <= 0 || overlapY <= 0) 
        return CollisionDirection::NONE;
    
    if (overlapX < overlapY) 
        return (diffX > 0) ? CollisionDirection::LEFT : CollisionDirection::RIGHT;
    else 
        return (diffY > 0) ? CollisionDirection::TOP : CollisionDirection::BOTTOM;
}
