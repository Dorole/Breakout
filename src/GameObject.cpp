#include <SFML/Graphics.hpp>
#include "GameObject.h"

using namespace sf;

void GameObject::setSpriteOriginToCenter()
{
	spriteBounds = sprite.getLocalBounds();
	sprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
}

void GameObject::getSpriteBounds()
{
	spriteBounds = sprite.getLocalBounds();
}

void GameObject::draw(RenderWindow& window)
{
	window.draw(sprite);
}
