#include "Collidable.h"
#include <iostream>

Collidable::Collidable(Sprite& spriteRef, CollidableObjectType objectTypeInit)
	: sprite(spriteRef), objectType(objectTypeInit)
{
	//if (objectType == CollidableObjectType::BALL)
	//	std::cout << "Coll Obj Type BALL" << std::endl;

	//if (objectType == CollidableObjectType::PLATFORM)
	//	std::cout << "Coll Obj Type PLATFORM" << std::endl;
}

void Collidable::setCollidableObjectType(CollidableObjectType type)
{
	objectType = type;
}

void Collidable::setSpritePosition(SpritePosition pos)
{
	spritePosition = pos;
}
