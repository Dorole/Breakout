#include "BrickMedium.h"
#include "Brick.h"
#include "ValueGetter.h"


BrickMedium::BrickMedium(ValueGetter& valueGetter) : Brick(valueGetter)
{
    createBrick(valueGetter.getBrickValuesById("M"));
}

void BrickMedium::onHit()
{
	if ((cooldownTimer.getElapsedTime().asSeconds() <= coolDownDuration ) || hitPoints <= 0) return;

	hitPoints--;
	std::cout << "Medium hit: " << hitPoints << std::endl;

	if (hitPoints <= 0)
	{
		brickSound.setBuffer(breakBuffer);
	}

	brickSound.play();
	cooldownTimer.restart();
};

void BrickMedium::reloadBrickValues(ValueGetter& valueGetter)
{
	createBrick(valueGetter.getBrickValuesById("M"));
}
