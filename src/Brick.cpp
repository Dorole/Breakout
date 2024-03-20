#include <SFML/Audio.hpp>
#include "Brick.h"
#include "ValueGetter.h"

Brick::Brick() 
	: collidable(sprite, CollidableObjectType::BRICK) {}

Brick::Brick(ValueGetter& valueGetter) 
	: collidable(sprite, CollidableObjectType::BRICK) {}

void Brick::createBrick(BrickTypeValues values)
{
	id = values.id;
	hitPoints = values.hitPoints;
	breakScore = values.breakScore;

	texture.loadFromFile(values.texture);
	sprite.setTexture(texture);
	spriteBounds = sprite.getLocalBounds();
	
	hitBuffer.loadFromFile(values.hitSound);

	if (!values.breakSound.empty())
		breakBuffer.loadFromFile(values.breakSound);

	brickSound.setBuffer(hitBuffer);
}


int Brick::getBreakScore() const 
{ 
	return breakScore; 
}
