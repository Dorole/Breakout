#include "Collidable.h"


Collidable::Collidable(sf::Sprite& spriteRef, CollidableObjectType objectTypeInit)
	: sprite(spriteRef), objectType(objectTypeInit)
{
	id = UIDGenerator::GetUniqueId();
}

void Collidable::setCollidableObjectType(CollidableObjectType type)
{
	objectType = type;
}

void Collidable::setSpritePosition(SpritePosition pos)
{
	spritePosition = pos;
}
