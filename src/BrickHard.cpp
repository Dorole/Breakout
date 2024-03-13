#include "BrickHard.h"
#include "Brick.h"
#include "ValueGetter.h"


BrickHard::BrickHard(ValueGetter& valueGetter)
	: Brick(valueGetter)
{
    createBrick(valueGetter.getBrickValuesById("H"));
}

void BrickHard::onHit()
{
	if ((cooldownTimer.getElapsedTime().asSeconds() <= coolDownDuration) || hitPoints <= 0) return;

	hitPoints--;
	std::cout << "Hard hit: " << hitPoints << std::endl;

	if (hitPoints == 0)
	{
		brickSound.setBuffer(breakBuffer);
	}

	brickSound.play();
	cooldownTimer.restart();
};

void BrickHard::reloadBrickValues(ValueGetter& valueGetter)
{
	createBrick(valueGetter.getBrickValuesById("H"));
}