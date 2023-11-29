#include "BrickSoft.h"
#include "Brick.h"
#include "ValueGetter.h"

BrickSoft::BrickSoft(ValueGetter& valueGetter) : Brick(valueGetter) 
{
    createBrick(valueGetter.getBrickValuesById("S"));
}

void BrickSoft::onHit()
{
	if (hitPoints == 0)
		return;

	std::cout << "Soft brick hit." << std::endl;
	hitPoints--;
	std::cout << "Hp: " << hitPoints << std::endl;

	if (hitPoints == 0)
	{
		std::cout << "Soft brick destroyed." << std::endl;
	}

};
