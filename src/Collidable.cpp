#include "Collidable.h"

Collidable::Collidable(CollidableObjectType collidableType) 
	: objectType(collidableType)
{
}

bool Collidable::checkCollision(Ball& ball)
{
	return getSprite().getGlobalBounds().intersects(ball.getBallSpriteGlobalBounds());
}

void Collidable::setQuadrant(Quadrant q)
{
	quadrant = q;
}
