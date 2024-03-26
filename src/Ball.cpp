#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Ball.h"
#include "GameObject.h"
#include "Game.h"
#include "ValueGetter.h"
#include "Platform.h"
#include "BrickGrid.h"
#include "SoundPlayer.h"
#include "PlayerController.h"

using namespace sf;

//mozda napraviti platform i ball u Game?
Ball::Ball(Game& game, Platform& platformRef, std::vector<std::vector<GridData>>& gridDataVectorRef)
    : GameObject(game), 
    grid(game.getGrid()), 
    platform(platformRef), 
    gridVector(gridDataVectorRef), 
    ballMovement(game, platformRef),
    collidable(sprite, CollidableObjectType::BALL)
{
    valueGetter.attachLevelDataObserver(this);
    init();

    collisionManager.attachCollisionObserver(this);
    registerForCollision();
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

void Ball::registerForCollision()
{
    //move to collision or something
    collisionManager.registerBallCollidable(std::make_unique<Collidable>(collidable));
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

void Ball::reflectOffBrick(FloatRect brickBounds)
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

    Vector2f ballVel = ballMovement.getBallVelocity();
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

    Vector2f adjustedBallVel = Vector2f(ballVel.x * adjustedVelX, ballVel.y * adjustedVelY);
    ballMovement.adjustBallVelocity(adjustedBallVel);
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
        checkWindowCollision();
        checkBallLife();
        
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

void Ball::onCollision(Collidable& collidedObject)
{
    if (!shouldBounce) return;

    CollidableObjectType type = collidedObject.getCollidableObjectType();
    Vector2f collidedPosition = collidedObject.getGlobalSpritePosition();

    if (type == CollidableObjectType::PLATFORM)
    {
        //radi al omg what even is this
        //+ ne odbija se lijepo neg skoro ravno

        FloatRect localSpriteBounds = collidedObject.getSpriteLocalBounds();

        float hitPointX = sprite.getPosition().x - collidedPosition.x;
        float reflectionFactor = hitPointX / (localSpriteBounds.width / 2.0f);

        ballMovement.adjustBallVelocity(Vector2f(reflectionFactor, -ballMovement.getBallVelocity().y));
        Vector2f adjustedVel = ballMovement.getBallVelocity();

        float speed = sqrt(adjustedVel.x * adjustedVel.x + adjustedVel.y * adjustedVel.y);
        adjustedVel /= speed;
        ballMovement.adjustBallVelocity(adjustedVel);

        sprite.setPosition(collidedPosition.x + hitPointX, sprite.getPosition().y);

    }
    else if (type == CollidableObjectType::BRICK)
    {
        reflectOffBrick(collidedObject.getSpriteGlobalBounds());
        //brick handle collision
        //brickgrid handle collision?? - prije je islo po row, column, mozda sad moze direktno
    } 
}

void Ball::notifyObservers(int value)
{
    for (const auto& observer : valueObservers)
        observer->onValueChanged(value, ValueType::LIVES);
}

