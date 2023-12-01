#include "Brick.h"
#include "ValueGetter.h"

Brick::Brick() {}

Brick::Brick(ValueGetter& valueGetter) {}

void Brick::createBrick(BrickTypeValues values)
{
	id = values.id;
	hitPoints = values.hitPoints;
	breakScore = values.breakScore;

	texture.loadFromFile(values.texture);
	sprite.setTexture(texture);
	spriteBounds = sprite.getLocalBounds();
	//audio
}


int Brick::getBreakScore() const 
{ 
	return breakScore; 
}
