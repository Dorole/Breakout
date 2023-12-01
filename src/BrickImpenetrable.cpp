#include "BrickImpenetrable.h"
#include "Brick.h"
#include "ValueGetter.h"
#include <iostream>

BrickImpenetrable::BrickImpenetrable(ValueGetter& valueGetter) : Brick(valueGetter)
{
    createBrick(valueGetter.getBrickValuesById("I"));
}

void BrickImpenetrable::onHit()
{
	std::cout << "Impenetrable brick hit." << std::endl;
	return;
};

void BrickImpenetrable::reloadBrickValues(ValueGetter& valueGetter)
{
	createBrick(valueGetter.getBrickValuesById("I"));
}