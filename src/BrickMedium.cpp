#include "BrickMedium.h"
#include "Brick.h"
#include "ValueGetter.h"


BrickMedium::BrickMedium(ValueGetter& valueGetter) : Brick(valueGetter)
{
    createBrick(valueGetter.getBrickValuesById("M"));
}

void BrickMedium::onHit()
{
	hitPoints--;

	if (hitPoints <= 0)
	{

		brickSound.setBuffer(breakBuffer);
	}

	brickSound.play();
};

void BrickMedium::reloadBrickValues(ValueGetter& valueGetter)
{
	createBrick(valueGetter.getBrickValuesById("M"));
}
