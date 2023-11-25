#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Ball.h"
#include "GameObject.h"
#include "ValueGetter.h"
#include "Platform.h"

Ball::Ball(RenderWindow& windowRef, ValueGetter& valueGetter, Platform& platformRef)
	: window(windowRef), platform(platformRef)
{
	texture.loadFromFile(valueGetter.getBallTexturePath());
	sprite.setTexture(texture);

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
    initialBallPosition = Vector2f(platform.getInitialPlatformPosition().x, platform.getInitialPlatformPosition().y - 12);
    sprite.setPosition(initialBallPosition);
}

void Ball::moveIdle()
{
    Vector2i localMousePosition = Mouse::getPosition(window);

    if (!platform.platformWindowBoundReached()) {
        sprite.setPosition(localMousePosition.x, initialBallPosition.y);
    }
    else {
        sprite.setPosition(platform.getPlatformPosition().x, initialBallPosition.y);
    }
}


void Ball::update()
{
    moveIdle();
}

void Ball::draw()
{
    window.draw(sprite);
}
