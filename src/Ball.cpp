#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Ball.h"
#include "GameObject.h"
#include "ValueGetter.h"
#include "Platform.h"

using namespace sf;

Ball::Ball(RenderWindow& windowRef, ValueGetter& valueGetter, Platform& platformRef)
	: window(windowRef), platform(platformRef)
{
	texture.loadFromFile(valueGetter.getBallTexturePath());
	sprite.setTexture(texture);
    windowSize = window.getSize();

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
    if (globalBallBounds.top < 0)
        ballVelocity.y = std::abs(ballVelocity.y);

    //bottom
    if (globalBallBounds.top + globalBallBounds.height > windowSize.y)
        std::cout << "LOST LIFE / GAME OVER" << std::endl;

    //left
    if (globalBallBounds.left < 0)
        ballVelocity.x = std::abs(ballVelocity.x);

    //right
    if (globalBallBounds.left + globalBallBounds.width > windowSize.x)
        ballVelocity.x = -std::abs(ballVelocity.x);

}

void Ball::checkPlatformCollision()
{
    if (sprite.getGlobalBounds().intersects(platform.getPlatformGlobalBounds()))
        ballVelocity.y = -ballVelocity.y;
}

//***************************************************
void Ball::update(float deltaTime)
{
    if (!shouldBounce)
        moveIdle(deltaTime);
    else
    {
        sprite.move(ballVelocity * ballSpeed * deltaTime);
        
        checkWindowCollision();
        checkPlatformCollision();

    }
}

void Ball::draw()
{
    window.draw(sprite);
}
