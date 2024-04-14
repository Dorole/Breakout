#include "Collidable.h"
#include <iostream>

Collidable::Collidable(const sf::Sprite& spriteRef, CollidableObjectType objectTypeInit)
	: sprite(spriteRef), objectType(objectTypeInit)
{
}

void Collidable::setCollidableObjectType(CollidableObjectType type)
{
	objectType = type;
}

void Collidable::setSpritePosition(SpritePosition pos)
{
	spritePosition = pos;
}



