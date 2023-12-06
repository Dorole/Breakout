#include "BrickHard.h"
#include "Brick.h"
#include "ValueGetter.h"


BrickHard::BrickHard(ValueGetter& valueGetter) : Brick(valueGetter)
{
    createBrick(valueGetter.getBrickValuesById("H"));
}

void BrickHard::onHit()
{
	if (hitPoints == 0)
		return;

	hitPoints--;

	if (hitPoints == 0)
	{

	}
};

void BrickHard::reloadBrickValues(ValueGetter& valueGetter)
{
	createBrick(valueGetter.getBrickValuesById("H"));
}