#include "BrickSoft.h"
#include "Brick.h"
#include "ValueGetter.h"
#include <SFML/Audio.hpp>

BrickSoft::BrickSoft(ValueGetter& valueGetter) : Brick(valueGetter) 
{
    createBrick(valueGetter.getBrickValuesById("S"));
}

void BrickSoft::onHit()
{
	hitPoints--;

	if (hitPoints == 0)
		brickSound.setBuffer(breakBuffer);

	brickSound.play();
};

void BrickSoft::reloadBrickValues(ValueGetter& valueGetter) 
{
	createBrick(valueGetter.getBrickValuesById("S"));
}
