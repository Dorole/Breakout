#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Ball.h"
#include "GameObject.h"
#include "ValueGetter.h"
#include "Platform.h"
#include "BrickGrid.h"
#include "SoundPlayer.h"
#include "PlayerController.h"

using namespace sf;

//consider: storing window, valueGetter, grid, gridDataVector in a dedicated manager - objects could take in only that manager as a ctr param 
//and retrieve other members from there instead of having to take in each object separately in the ctr
Ball::Ball(RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& gridRef, Platform& platformRef, std::vector<std::vector<GridData>>& gridDataVectorRef)
    : GameObject(windowRef, valueGetterRef), 
    grid(gridRef), 
    platform(platformRef), 
    gridVector(gridDataVectorRef), 
    ballMovement(windowRef, platformRef)
{
    valueGetter.attachLevelDataObserver(this);
    init();
}


void Ball::init()
{
    texture.loadFromFile(valueGetter.getBallTexturePath());
    sprite.setTexture(texture);
    sprite.setScale(0.35f, 0.35f); 
    windowSize = window.getSize();
    topRenderBound = grid.getGridOffset();
    deathZone = platform.getPlatformPosition().y + platform.getPlatformLocalBounds().height; //set elsewhere!

    shouldBounce = false;
    lostLife = false;

    setSpriteOriginToCenter();
    resetBallPosition();
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

void Ball::resetBallPosition() 
{
    ballMovement.resetPosition();
    sprite.setPosition(ballMovement.getBallPosition());
}

void Ball::toggleBounce()
{
    shouldBounce = !shouldBounce;
}

bool Ball::checkWindowCollision()
{
    FloatRect globalBallBounds = sprite.getGlobalBounds();
    bool collided = false;

    if (ballMovement.handleWindowCollision(globalBallBounds, topRenderBound))
    {
        soundPlayer.playSoundRandomPitch(SoundType::BALL_HIT);
        setLastCollidedToNull(); //??
        return true;
    }

    return false;
}

bool Ball::checkBallLife()
{
    FloatRect globalBallBounds = sprite.getGlobalBounds();

    if (ballMovement.ballMovedBelowPlatform(globalBallBounds))
    {
		notifyObservers(1);
        soundPlayer.playSoundRandomPitch(SoundType::BALL_RESET);
        setLastCollidedToNull();
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
        setLastCollidedToNull();

        return true;
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

    sprite.setPosition(platform.getPlatformPosition().x + hitPointX, sprite.getPosition().y);
}

void Ball::checkBrickCollision()
{
    bool collisionOccured = false;

    for (size_t i = 0; i < valueGetter.getRowCount(); i++)
    {
        for (size_t j = 0; j < valueGetter.getColumnCount(); j++)
        {
            if (!gridVector[i][j].shouldRender) continue;

            if (gridVector[i][j].getSpriteGlobalBounds().intersects(sprite.getGlobalBounds()))
            {
                FloatRect brickBounds = gridVector[i][j].getSpriteGlobalBounds();
                reflectOffBrick(brickBounds);

                if (lastCollidedRow != i || lastCollidedColumn != j)
                {
                    setLastCollided(i, j);
                    std::cout << "Last collided: " << i << ", " << j << std::endl;

                    grid.handleCollision(i, j);
                }
                
                collisionOccured = true;
                break;
            } 
        }

        if (collisionOccured) break;
    }
}

void Ball::reflectOffBrick(FloatRect& brickBounds)
{
    FloatRect ballBounds = sprite.getGlobalBounds();

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

    switch (collisionDirection)
    {
    case CollisionDirection::TOP:
        ballVelocity.y = -ballVelocity.y;
        break;

    case CollisionDirection::BOTTOM:      
        ballVelocity.y = -ballVelocity.y;
        break;

    case CollisionDirection::LEFT:       
        ballVelocity.x = -ballVelocity.x;
        break;

    case CollisionDirection::RIGHT:       
        ballVelocity.x = -ballVelocity.x;
        break;
    }
}

void Ball::setLastCollided(std::size_t row, std::size_t col)
{
    lastCollidedRow = row;
    lastCollidedColumn = col;   
}

void Ball::setLastCollidedToNull()
{
    lastCollidedRow = -1;
    lastCollidedColumn = -1;

    std::cout << "Last collided: NULL" << std::endl;
}

// ******************** OVERRIDDEN FUNCTIONS ********************

void Ball::update(float deltaTime)
{
    if (!shouldBounce)
    {
        ballMovement.updatePosition(sprite.getPosition());
        sprite.move(ballMovement.moveBallAbovePlatform() * deltaTime);
    }
    else
    {
        checkBrickCollision();
        checkWindowCollision();
        checkBallLife();
        checkPlatformCollision();
        
        sprite.move(ballMovement.moveBall() * deltaTime);
        
        if (grid.allBricksDestroyed()) 
        {
            shouldBounce = false;
            resetBallPosition();
        }
    }
}


void Ball::draw()
{
    window.draw(sprite);
}

void Ball::attachObserver(NumValueObserver* observer)
{
    valueObservers.push_back(observer);
}

void Ball::notifyObservers(int value)
{
    for (const auto& observer : valueObservers)
        observer->onValueChanged(value, ValueType::LIVES);
}

//void Ball::setPlayerController(std::shared_ptr<PlayerController> controller)
//{
//    playerController = controller;
//}

