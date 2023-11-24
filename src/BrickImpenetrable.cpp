#include "BrickImpenetrable.h"
#include "Brick.h"
#include "ValueGetter.h"

BrickImpenetrable::BrickImpenetrable(ValueGetter& valueGetter) : Brick(valueGetter)
{
    createBrick(valueGetter.getBrickValuesById("I"));
}