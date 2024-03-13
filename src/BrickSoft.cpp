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
	if (hitPoints <= 0) return;

	hitPoints--;
	std::cout << "Soft hit: " << hitPoints << std::endl;

	if (hitPoints == 0)
		brickSound.setBuffer(breakBuffer);

	brickSound.play();
};

void BrickSoft::reloadBrickValues(ValueGetter& valueGetter) 
{
	createBrick(valueGetter.getBrickValuesById("S"));
}
