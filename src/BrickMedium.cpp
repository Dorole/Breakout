#include "BrickMedium.h"
#include "Brick.h"
#include "ValueGetter.h"
#include <iostream>

BrickMedium::BrickMedium(ValueGetter& valueGetter) : Brick(valueGetter)
{
    createBrick(valueGetter.getBrickValuesById("M"));
}

void BrickMedium::onHit()
{
	std::cout << "Medium brick hit." << std::endl;
	hitPoints--;
	std::cout << "Hp: " << hitPoints << std::endl;

	if (hitPoints <= 0)
	{
		std::cout << "Medium brick destroyed." << std::endl;

	}
};
