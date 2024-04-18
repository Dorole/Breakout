#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Ball.h"

using namespace sf;

Ball::Ball(Game& gameRef) 
    : GameObject(gameRef),
    grid(gameRef.getGrid()),
    ballMovement(gameRef),
    renderer(gameRef),
    collidable(renderer.getSprite(), CollidableObjectType::BALL)
{
    valueGetter.attachLevelDataObserver(this);
    //init();

    registerForCollision();
}


void Ball::init()
{
    std::string ballPath = valueGetter.getBallTexturePath();
    
    ballMovement.init();
    renderer.init(ballPath, ballSize);
    resetBallPosition();

    shouldBounce = false;
    lostLife = false;

    collisionManager.attachCollisionObserver(this);
    soundPlayer.setBuffer(SoundType::BALL_HIT);    
    
}

void Ball::registerForCollision()
{
    collisionManager.registerBallCollidable(collidable);
}

void Ball::resetBallPosition() 
{
    ballMovement.resetPosition();  
    renderer.setSpritePosition(ballMovement.getBallPosition());
}

void Ball::toggleBounce()
{
    shouldBounce = !shouldBounce;
}

void Ball::checkWindowCollision()
{   
    FloatRect globalBallBounds = renderer.getSpriteGlobalBounds();
    bool collided = false;

    if (ballMovement.handleWindowCollision(globalBallBounds))
    {
        soundPlayer.playSoundRandomPitch(SoundType::BALL_HIT);
    }
}

void Ball::checkBallLife()
{
    FloatRect globalBallBounds = renderer.getSpriteGlobalBounds();

    if (ballMovement.ballMovedBelowPlatform(globalBallBounds))
    {
		notifyObservers(1);
        soundPlayer.playSoundRandomPitch(SoundType::BALL_RESET);
    }
}


// ******************** OVERRIDDEN FUNCTIONS ********************

void Ball::update(float deltaTime)
{
    if (!shouldBounce)
    {
        ballMovement.updatePosition(renderer.getSpritePosition());
        renderer.moveSprite(ballMovement.moveBallAbovePlatform() * deltaTime);
    }
    else
    {
        checkWindowCollision();
        checkBallLife();

        renderer.moveSprite(ballMovement.moveBall() * deltaTime);

        if (grid.allBricksDestroyed()) //should be an event?
        {
            shouldBounce = false;
            resetBallPosition();
        }
    }
}

void Ball::draw()
{
    renderer.drawSprite();
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

    if (type == CollidableObjectType::PLATFORM && ballMovement.getBallVelocity().y > 0)
    {
        FloatRect localPlatformSpriteBounds = collidedObject.getSpriteLocalBounds();      
        float hitPointX = renderer.getSpritePosition().x - collidedPosition.x;

        ballMovement.reflectOffPlatform(hitPointX, collidedPosition, localPlatformSpriteBounds);
        renderer.setSpritePosition(Vector2f(collidedPosition.x + hitPointX, renderer.getSpritePosition().y));
    }
    else if (type == CollidableObjectType::BRICK)
    {
        ballMovement.reflectOffBrick(renderer.getSpriteGlobalBounds(), collidedObject.getSpriteGlobalBounds());
    } 

    soundPlayer.playSoundRandomPitch(SoundType::BALL_HIT);
}

void Ball::notifyObservers(int value)
{
    for (const auto& observer : valueObservers)
        observer->onValueChanged(value, ValueType::LIVES);
}

