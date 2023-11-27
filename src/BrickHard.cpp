#include "BrickHard.h"
#include "Brick.h"
#include "ValueGetter.h"
#include <iostream>

BrickHard::BrickHard(ValueGetter& valueGetter) : Brick(valueGetter)
{
    createBrick(valueGetter.getBrickValuesById("H"));
}

void BrickHard::onHit()
{
	std::cout << "Hard brick hit." << std::endl;
	hitPoints--;
	std::cout << "Hp: " << hitPoints << std::endl;

	if (hitPoints <= 0)
		std::cout << "Hard brick destroyed." << std::endl;
};