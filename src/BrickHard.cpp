#include "BrickHard.h"
#include "Brick.h"
#include "ValueGetter.h"

BrickHard::BrickHard(ValueGetter& valueGetter) : Brick(valueGetter)
{
    createBrick(valueGetter.getBrickValuesById("H"));
}