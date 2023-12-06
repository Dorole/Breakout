#include "BrickImpenetrable.h"
#include "Brick.h"
#include "ValueGetter.h"


BrickImpenetrable::BrickImpenetrable(ValueGetter& valueGetter) : Brick(valueGetter)
{
    createBrick(valueGetter.getBrickValuesById("I"));
}

void BrickImpenetrable::onHit()
{
	brickSound.play();
	return;
};

void BrickImpenetrable::reloadBrickValues(ValueGetter& valueGetter)
{
	createBrick(valueGetter.getBrickValuesById("I"));
}